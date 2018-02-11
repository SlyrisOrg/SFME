//
// Created by milerius on 09/02/18.
//

#pragma once

#include <memory>
#include <SFME/timer/timer.hpp>
#include <SFME/mediator/common_events.hpp>
#include <SFME/ecs/system_base.hpp>
#include <SFME/ecs/system_type.hpp>
#include <SFME/ecs/details/system_type_traits.hpp>

namespace sfme::ecs
{
    class SystemManager final : public sfme::mediator::Receiver<SystemManager>
    {
    private:
        //! Typedefs
        using SystemPtr = std::shared_ptr<BaseSystem>;
        using SystemMap = std::unordered_map<typeID, SystemPtr>;
        using SystemArray = std::array<SystemMap, SystemType::Size>;
    public:
        //! Constructor
        SystemManager(sfme::mediator::EventManager &evtMgr) noexcept : _evtMgr(evtMgr)
        {
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
        void update() noexcept
        {
            auto updateSystem = [this](SystemType sysType) noexcept {
                for (auto &&curSystem : _systems[sysType]) {
                    curSystem.second->update();
                }
            };

            updateSystem(SystemType::PreUpdate);
            _timeStep.startFrame();
            while (_timeStep.isUpdateRequired() && size(SystemType::LogicUpdate) > 0) {
                updateSystem(SystemType::LogicUpdate);
                _timeStep.performUpdate();
            }
            updateSystem(SystemType::PostUpdate);
            if (_needToSweep)
                sweepSystems();
        }

        template <typename ...Systems>
        void loadSystems() noexcept
        {
            (createSystem<Systems>(), ...);
        }

        size_t size() const noexcept
        {
            return _systems.at(SystemType::PreUpdate).size() + _systems.at(SystemType::LogicUpdate).size() +
                   _systems.at(SystemType::PostUpdate).size();
        }

        size_t size(SystemType sysType) const noexcept
        {
            assert(sysType < SystemType::Size);
            return _systems.at(sysType).size();
        }

        template <typename System>
        const System &getSystem() const noexcept
        {
            static_assert(details::is_system_v<System>,
                          "The System type given as template parameter doesn't seems to be valid");
            return static_cast<System &>(*_systems.at(System::getSystemType()).at(details::generateID<System>()));
        }

        template <typename System>
        System &getSystem() noexcept
        {
            static_assert(details::is_system_v<System>,
                          "The System type given as template parameter doesn't seems to be valid");
            return static_cast<System &>(*_systems[System::getSystemType()].at(details::generateID<System>()));
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

        template <typename System, typename ...Args>
        System &createSystem(Args &&...args) noexcept
        {
            static_assert(details::is_system_v<System>,
                          "The System type given as template parameter doesn't seems to be valid");
            if (hasSystem<System>())
                return getSystem<System>();
            return static_cast<System &>(addSystem<System>(std::make_shared<System>(_evtMgr,
                                                                                    std::forward<Args>(args)...)));
        }

        template <typename System>
        bool hasSystem() const noexcept
        {
            static_assert(details::is_system_v<System>,
                          "The System type given as template parameter doesn't seems to be valid");
            auto &&curSystems = _systems[System::getSystemType()];
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
                _needToSweep = true;
                return true;
            }
            _needToSweep = false;
            return false;
        }

        template <typename ... Systems>
        bool markSystems() noexcept
        {
            return (markSystem<Systems>() && ...);
        }

        void sweepSystems() noexcept
        {
            for (auto &&curSystem : _systems) {
                for (auto it = curSystem.begin(); it != curSystem.end();) {
                    if (it->second->isMarked()) {
                        it = curSystem.erase(it);
                    } else {
                        ++it;
                    }
                }
            }
            _needToSweep = false;
        }

    private:
        template <typename System>
        BaseSystem &addSystem(SystemPtr system) noexcept
        {
            return *_systems[System::getSystemType()].emplace(details::generateID<System>(), system).first->second;
        }

    private:
        //! Private members
        bool _needToSweep{false};
        timer::TimeStep _timeStep;
        sfme::mediator::EventManager &_evtMgr;
        SystemArray _systems{{}};
    };
}