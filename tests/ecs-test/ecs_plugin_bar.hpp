//
// Created by milerius on 12/02/18.
//

#pragma once

#include <SFME/ecs/ecs.hpp>
#include "common_ecs_test.hpp"

namespace sfme::testing::plugins
{
    class BarSystem : public sfme::ecs::PlugPreUpdateSystem<BarSystem>
    {
    public:
        reflect_class(BarSystem);
        BarSystem(sfme::mediator::EventManager &evtMgr, EntityManager &ettMgr) noexcept;
        void update() noexcept override;
        ~BarSystem() noexcept override = default;

        static std::shared_ptr<sfme::ecs::BaseSystem> createSystem(sfme::mediator::EventManager &evtMgr,
                                                                   EntityManager &ettMgr) noexcept;
    private:
        EntityManager &_ettMgr;
    };
}
