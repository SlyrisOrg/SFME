//
// Created by milerius on 09/02/18.
//

#pragma once

#include <core/utils/NonCopyable.hpp>
#include <SFME/mediator/mediator.hpp>
#include <SFME/ecs/system_type.hpp>
#include <SFME/ecs/details/system_type_id.hpp>

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
        virtual typeID getType() const noexcept = 0;
        virtual const std::string &getName() const noexcept = 0;
        virtual SystemType getSystemTypeRTTI() const noexcept = 0;
    public:
        void mark() noexcept
        {
            _marked = true;
        }

        void unmark() noexcept
        {
            _marked = false;
        }

        bool isMarked() const noexcept
        {
            return _marked;
        }

        void enable() noexcept
        {
            _enable = true;
        }

        void disable() noexcept
        {
            _enable = false;
        }

        bool isEnabled() const noexcept
        {
            return _enable;
        }

    protected:
        mediator::EventManager &_evtMgr;
        bool _marked{false};
        bool _enable{true};
    };
}