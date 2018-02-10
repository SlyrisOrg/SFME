//
// Created by milerius on 09/02/18.
//

#pragma once

#include <core/utils/NonCopyable.hpp>
#include <SFME/mediator/mediator.hpp>

namespace sfme::ecs
{
    class BaseSystem
    {
    public:
        explicit BaseSystem(mediator::EventManager &evtMgr) noexcept : _evtMgr(evtMgr)
        {
        }

        virtual ~BaseSystem() noexcept = default;

    public:
        virtual void update() noexcept = 0;
        virtual const std::string &getName() const noexcept = 0;
    protected:
        mediator::EventManager &_evtMgr;
    };
}
