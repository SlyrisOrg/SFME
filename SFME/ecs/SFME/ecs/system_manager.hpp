//
// Created by milerius on 09/02/18.
//

#pragma once

#include <memory>
#include <SFME/ecs/system_base.hpp>
#include <SFME/ecs/system_type.hpp>
#include <SFME/timer/timer.hpp>
#include <SFME/mediator/common_events.hpp>
#include <SFME/ecs/details/system_type_traits.hpp>

namespace sfme::ecs
{
    class SystemManager final : public sfme::mediator::Receiver<SystemManager>
    {
    private:
        //! Typedefs
        using SystemPtr = std::shared_ptr<BaseSystem>;
        using SystemMap = std::unordered_map<typeID, SystemPtr>;
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
            while (_timeStep.isUpdateRequired()) {
                updateSystem(SystemType::LogicUpdate);
                _timeStep.performUpdate();
            }
            updateSystem(SystemType::PostUpdate);
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
            assert(sysType < SystemType::Sentinelle);
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
            std::cout << details::generateID<System>() << std::endl;
            return static_cast<System &>(*_systems[System::getSystemType()].at(details::generateID<System>()));
        }

        template <typename System, typename ...Args>
        System &createSystem(Args &&...args) noexcept
        {
            static_assert(details::is_system_v<System>,
                          "The System type given as template parameter doesn't seems to be valid");
            return static_cast<System &>(addSystem<System>(std::make_shared<System>(_evtMgr,
                                                                                    std::forward<Args>(args)...)));
        }

        template <typename System>
        bool hasSystem() const noexcept
        {
            static_assert(details::is_system_v<System>,
                          "The System type given as template parameter doesn't seems to be valid");
            auto &&curSystems = _systems.at(System::getSystemType());
            return curSystems.find(details::generateID<System>()) != curSystems.end();
        }

    private:
        template <typename System>
        BaseSystem &addSystem(SystemPtr system) noexcept
        {
            return *_systems[System::getSystemType()].emplace(details::generateID<System>(), system).first->second;
        }

    private:
        //! Private members
        timer::TimeStep _timeStep;
        sfme::mediator::EventManager &_evtMgr;
        std::unordered_map<SystemType, SystemMap> _systems
            {
                {SystemType::PreUpdate,   {}},
                {SystemType::LogicUpdate, {}},
                {SystemType::PostUpdate,  {}}
            };
    };
}