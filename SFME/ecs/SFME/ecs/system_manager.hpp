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
        void loadSystems(SystemType sysType) noexcept
        {
            (createSystem<Systems>(sysType), ...);
        }

    public:
        //! Helpers
        template <typename System>
        const System &getSystem(SystemType sysType) const noexcept
        {
            static_assert(details::is_system_v<System>,
                          "The System type given as template parameter doesn't seems to be valid");
            assert(sysType < SystemType::Sentinelle);
            return static_cast<System &>(*_systems.at(sysType).at(details::generateID<System>()));
        }

        template <typename System>
        System &getSystem(SystemType sysType) noexcept
        {
            static_assert(details::is_system_v<System>,
                          "The System type given as template parameter doesn't seems to be valid");
            assert(sysType < SystemType::Sentinelle);
            return static_cast<System &>(*_systems.at(sysType).at(details::generateID<System>()));
        }

        template <typename System, typename ...Args>
        System &createSystem(SystemType sysType, Args &&...args) noexcept
        {
            static_assert(details::is_system_v<System>,
                          "The System type given as template parameter doesn't seems to be valid");
            assert(sysType < SystemType::Sentinelle);
            return static_cast<System &>(addSystem(sysType,
                                                   std::make_shared<System>(_evtMgr, std::forward<Args>(args)...)));
        }

    private:
        BaseSystem &addSystem(SystemType sysType, SystemPtr system) noexcept
        {
            return *_systems[sysType].emplace(system->getType(), system).first->second;
        }

    private:
        //! Private members
        timer::TimeStep _timeStep;
        sfme::mediator::EventManager &_evtMgr;
        std::unordered_map<SystemType, SystemMap> _systems;
    };
}