//
// Created by milerius on 12/02/18.
//

#pragma once

#include <SFME/ecs/ecs.hpp>
#include "ecs_common_example.hpp"

namespace sfme::example::plugins
{
    class FooSystem : public sfme::ecs::PlugPreUpdateSystem<FooSystem>
    {
    public:
        reflect_class(FooSystem);
        FooSystem(sfme::mediator::EventManager &evtMgr, EntityManager &ettMgr) noexcept;
        void update() noexcept override;
        ~FooSystem() noexcept override = default;

        static std::shared_ptr<sfme::ecs::BaseSystem> createSystem(sfme::mediator::EventManager &evtMgr,
                                                                   EntityManager &ettMgr) noexcept;
    private:
        EntityManager &_ettMgr;
    };
}
