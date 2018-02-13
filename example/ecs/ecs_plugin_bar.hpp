//
// Created by milerius on 13/02/18.
//

#pragma once

#include <SFME/ecs/ecs.hpp>
#include "ecs_common_example.hpp"

namespace sfme::example::plugins
{
    class BarSystem : public sfme::ecs::PlugPostUpdateSystem<BarSystem>
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
