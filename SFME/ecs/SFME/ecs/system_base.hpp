//
// Created by milerius on 09/02/18.
//

#pragma once

#include <core/utils/NonCopyable.hpp>
#include <SFME/mediator/mediator.hpp>
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

    protected:
        mediator::EventManager &_evtMgr;
        bool _marked{false};
    };

    template <typename SystemDerived>
    class System : public BaseSystem
    {
    public:
        template <typename ...Args>
        explicit System(Args &&...args) : BaseSystem(std::forward<Args>(args)...)
        {
        }

        ~System() noexcept override = default;

        void update() noexcept override = 0;

        typeID getType() const noexcept final
        {
            return details::generateID<SystemDerived>();
        }
    };
}