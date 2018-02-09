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
    class SystemManager : public sfme::mediator::Receiver<SystemManager>
    {
    public:
        SystemManager(sfme::mediator::EventManager &evtMgr)
        {
            evtMgr.subscribe<sfme::mediator::evt::GameStarted>(*this);
        }

    public:
        //! Public mediator callbacks
        void receive([[maybe_unused]] const sfme::mediator::evt::GameStarted &evt) noexcept
        {
            _timeStep.start();
        }

    public:
        //! Public member functions
        void execute() noexcept
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
            }
            updateSystem(SystemType::PostUpdate);
        }

    private:
        //! Typedefs
        using SystemPtr = std::unique_ptr<BaseSystem>;
        using SystemArray = std::vector<SystemPtr>;

    private:
        //! Private members
        timer::TimeStep _timeStep;
        std::unordered_map<SystemType, SystemArray> _systems;
    };
}