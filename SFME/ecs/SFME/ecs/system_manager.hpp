//
// Created by milerius on 09/02/18.
//

#pragma once

#include <algorithm>
#include <memory>
#include <cassert>
#include <core/lib/Lib.hpp>
#include <core/algorithm/erase_if.hpp>
#include <SFME/timer/timer.hpp>
#include <SFME/mediator/common_events.hpp>
#include <SFME/ecs/system_base.hpp>
#include <SFME/ecs/system.hpp>
#include <SFME/ecs/system_type.hpp>
#include <SFME/ecs/details/system_type_traits.hpp>
#include <SFME/ecs/details/utils.hpp>

namespace sfme::ecs
{
    template <typename EntityManager>
    class SystemManager final : public sfme::mediator::Receiver<SystemManager<EntityManager>>
    {
    public:
        using CreatorFunc = std::shared_ptr<BaseSystem> (*)(sfme::mediator::EventManager &, EntityManager &);
    private:
        //! Typedefs
        using SystemPtr = std::shared_ptr<BaseSystem>;
        using SystemMap = std::unordered_map<typeID, SystemPtr>;
        using SystemArray = std::array<SystemMap, SystemType::Size>;
    public:
        //! Constructor
        SystemManager(sfme::mediator::EventManager &evtMgr, EntityManager &ettMgr,
                      fs::path pluginPath = fs::current_path() / fs::path("systems")) noexcept :
            _evtMgr(evtMgr),
            _ettMgr(ettMgr),
            _pluginPath(std::move(pluginPath))
        {
#ifdef SILENT_SYSTEMS_MANAGER_LOGGING
            _log.setLevel(logging::Silent);
#endif
            _evtMgr.subscribe<sfme::mediator::evt::GameStarted>(*this);
        }

    public:
        //! Public mediator callbacks
        void receive([[maybe_unused]] const sfme::mediator::evt::GameStarted &evt) noexcept
        {
            _timeStep.start();
        }

    public:
        //! Public member functions
        size_t update() noexcept
        {
            size_t nbSystemsUpdated = 0;
            auto updateSystem = [this, &nbSystemsUpdated](SystemType sysType) noexcept {
                for (auto &&curSystem : _systems[sysType]) {
                    auto &&system = curSystem.second;
                    if (system->isEnabled()) {
                        system->update();
                        nbSystemsUpdated++;
                    }
                }
            };

            updateSystem(SystemType::PreUpdate);
            _timeStep.startFrame();
            while (_timeStep.isUpdateRequired() && size(SystemType::LogicUpdate) > 0) {
                updateSystem(SystemType::LogicUpdate);
                _timeStep.performUpdate();
            }
            updateSystem(SystemType::PostUpdate);
            if (_needToSweepSystems)
                _sweepSystems();
            _ettMgr.sweepEntities();
            return nbSystemsUpdated;
        }

        template <typename System, typename ...Args>
        System &createSystem(Args &&...args) noexcept
        {
            static_assert(details::is_system_v<System>,
                          "The System type given as template parameter doesn't seems to be valid");
            if (hasSystem<System>())
                return getSystem<System>();
            return static_cast<System &>(_addSystem<System>(std::make_shared<System>(_evtMgr, _ettMgr,
                                                                                     std::forward<Args>(args)...)));
        }

        template <typename ...Systems>
        void loadSystems() noexcept
        {
            (createSystem<Systems>(), ...);
        }

        bool loadPlugin(std::string pluginName, std::string &&creatorFunc = "createSystem") noexcept
        {
            try {
                auto &&creator = _plugins.emplace_back(lib::getSymbol<CreatorFunc>(_pluginPath / fs::path(pluginName),
                                                                                   creatorFunc,
                                                                                   lib::LoadingMode::Default));
                auto ptr = (*creator)(_evtMgr, _ettMgr);
                if (std::any_of(begin(_libMemoisation), end(_libMemoisation), [&ptr](auto &&id) {
                    return ptr->getType() == id.second;
                })) {
                    _log(logging::Info) << pluginName << " system already loaded" << std::endl;
                    return true;
                }
                _libMemoisation[ptr->getName()] = ptr->getType();
                _systems[ptr->getSystemTypeRTTI()].emplace(ptr->getType(),
                                                           ptr).first->second;
                _log(logging::Debug) << pluginName << " has been successfully loaded." << std::endl;
            }
            catch (const std::exception &error) {
                _log(logging::Debug) << error.what() << std::endl;
                return false;
            }
            return true;
        }

        bool loadPlugins(std::string &&creatorFunc = "createSystem")
        {
            bool res = true;
            fs::recursive_directory_iterator endit;

            for (fs::recursive_directory_iterator it(_pluginPath); it != endit; ++it) {
                if (!fs::is_regular_file(*it)) {
                    continue;
                }
				if (details::is_shared_library(it->path())) {
					res &= loadPlugin(it->path().filename().string(), std::move(creatorFunc));
				}

            }
            return res;
        }

        void setPluginPath(fs::path pluginPath) noexcept
        {
            _pluginPath = std::move(pluginPath);
        }

        size_t size() const noexcept
        {
            return _systems.at(SystemType::PreUpdate).size() +
                   _systems.at(SystemType::LogicUpdate).size() +
                   _systems.at(SystemType::PostUpdate).size();
        }

        size_t size(SystemType sysType) const noexcept
        {
            assert(sysType < SystemType::Size);
            return _systems.at(sysType).size();
        }

        size_t nbPlugins() const noexcept
        {
            return _libMemoisation.size();
        }

        template <typename System>
        bool disableSystem() noexcept
        {
            static_assert(details::is_system_v<System>,
                          "The System type given as template parameter doesn't seems to be valid");
            if (hasSystem<System>()) {
                getSystem<System>().disable();
                _log(logging::Debug) << System::className() << " has been disabled" << std::endl;
                return true;
            }
            return false;
        }

        template <typename ... Systems>
        bool disableSystems() noexcept
        {
            return (disableSystem<Systems>() && ...);
        }

        template <typename System>
        bool enableSystem() noexcept
        {
            static_assert(details::is_system_v<System>,
                          "The System type given as template parameter doesn't seems to be valid");
            if (hasSystem<System>()) {
                getSystem<System>().enable();
                _log(logging::Debug) << System::className() << " has been enabled" << std::endl;
                return true;
            }
            return false;
        }

        template <typename ... Systems>
        bool enableSystems() noexcept
        {
            return (enableSystem<Systems>() && ...);
        }

        template <typename System>
        const System &getSystem() const noexcept
        {
            static_assert(details::is_system_v<System>,
                          "The System type given as template parameter doesn't seems to be valid");
            if constexpr (System::is_plugged_system_v)
                return static_cast<System &>(*_systems.at(System::getSystemType()).at(
                    _libMemoisation.at(System::className())));
            else
                return static_cast<System &>(*_systems.at(System::getSystemType()).at(details::generateID<System>()));
        }

        template <typename System>
        System &getSystem() noexcept
        {
            static_assert(details::is_system_v<System>,
                          "The System type given as template parameter doesn't seems to be valid");
            if constexpr (System::is_plugged_system_v)
                return static_cast<System &>(*_systems.at(System::getSystemType()).at(
                    _libMemoisation.at(System::className())));
            else
                return static_cast<System &>(*_systems.at(System::getSystemType()).at(details::generateID<System>()));
        }

        template <typename ...Systems>
        std::tuple<std::add_lvalue_reference_t<Systems>...> getSystems() noexcept
        {
            return {getSystem<Systems>()...};
        }

        template <typename ...Systems>
        std::tuple<std::add_lvalue_reference_t<std::add_const_t<Systems>>...> getSystems() const noexcept
        {
            return {getSystem<Systems>()...};
        }

        template <typename System>
        bool hasSystem() const noexcept
        {
            static_assert(details::is_system_v<System>,
                          "The System type given as template parameter doesn't seems to be valid");
            auto &&curSystems = _systems[System::getSystemType()];
            if constexpr (System::is_plugged_system_v)
                return curSystems.find(_libMemoisation.at(System::className())) != curSystems.end();
            else
                return curSystems.find(details::generateID<System>()) != curSystems.end();
        }

        template <typename ... Systems>
        bool hasSystems() const noexcept
        {
            return (hasSystem<Systems>() && ...);
        }

        template <typename System>
        bool markSystem() noexcept
        {
            static_assert(details::is_system_v<System>,
                          "The System type given as template parameter doesn't seems to be valid");
            if (hasSystem<System>()) {
                getSystem<System>().mark();
                _needToSweepSystems = true;
                if constexpr (System::is_plugged_system_v)
                    _libMemoisation.erase(System::className());
                _log(logging::Debug) << System::className() << " has been marked" << std::endl;
                return true;
            }
            _needToSweepSystems = false;
            return false;
        }

        template <typename ... Systems>
        bool markSystems() noexcept
        {
            return (markSystem<Systems>() && ...);
        }

    private:
        template <typename System>
        BaseSystem &_addSystem(SystemPtr system) noexcept
        {
            return *_systems[System::getSystemType()].emplace(details::generateID<System>(), system).first->second;
        }

        void _sweepSystems() noexcept
        {
            for (auto &&curSystem : _systems) {
                algo::erase_if(curSystem, [](auto &&pair) {
                    return pair.second->isMarked();
                });
            }
            _needToSweepSystems = false;
        }

    private:
        //! Private members
        logging::Logger _log{"system_manager", logging::Debug};
        bool _needToSweepSystems{false};
        std::vector<lib::Symbol<CreatorFunc>> _plugins;
        std::unordered_map<std::string, typeID> _libMemoisation;
        timer::TimeStep _timeStep;
        sfme::mediator::EventManager &_evtMgr;
        EntityManager &_ettMgr;
        SystemArray _systems{{}};
        fs::path _pluginPath;
    };
}