//
// Created by milerius on 09/02/18.
//

#pragma once

#include <memory>
#include <SFME/ecs/system_base.hpp>
#include <SFME/ecs/system_type.hpp>
#include <SFME/timer/timer.hpp>
#include <SFME/mediator/common_events.hpp>

namespace sfme::ecs
{
    class SystemManager final : public sfme::mediator::Receiver<SystemManager>
    {
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
                    curSystem->update();
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

    public:
        template <typename System>
        static constexpr bool is_system_v = std::is_base_of_v<BaseSystem, System> &&
                                            refl::has_reflectible_class_name_v<System>;

        //! Helpers
        template <typename System>
        const System &getSystem(SystemType sysType) const noexcept
        {
            static_assert(SystemManager::is_system_v<System>,
                          "The System type given as template parameter doesn't seems to be valid");
            assert(sysType < SystemType::Sentinelle);
            for (auto &&curSystem : _systems.at(sysType)) {
                if (curSystem->getName() == System::className())
                    return static_cast<System &>(*curSystem);
            }
            return static_cast<System &>(*_systems.at(sysType).begin()->get());
        }

        template <typename System>
        System &getSystem(SystemType sysType) noexcept
        {
            static_assert(SystemManager::is_system_v<System>,
                          "The System type given as template parameter doesn't seems to be valid");
            assert(sysType < SystemType::Sentinelle);
            for (auto &&curSystem : _systems.at(sysType)) {
                if (curSystem->getName() == System::className())
                    return static_cast<System &>(*curSystem);
            }
            return static_cast<System &>(*_systems.at(sysType).begin()->get());
        }

        template <typename System, typename ...Args>
        System &createSystem(SystemType sysType, Args &&...args) noexcept
        {
            static_assert(SystemManager::is_system_v<System>,
                          "The System type given as template parameter doesn't seems to be valid");
            assert(sysType < SystemType::Sentinelle);
            auto res = _systems[sysType].emplace_back(std::make_shared<System>(_evtMgr, std::forward<Args>(args)...));
            return static_cast<System &>(*res);
        }

    private:
        //! Typedefs
        using SystemPtr = std::shared_ptr<BaseSystem>;
        using SystemArray = std::vector<SystemPtr>;

    private:
        //! Private members
        timer::TimeStep _timeStep;
        sfme::mediator::EventManager &_evtMgr;
        std::unordered_map<SystemType, SystemArray> _systems;
    };
}