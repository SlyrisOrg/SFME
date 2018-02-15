//
// Created by milerius on 12/02/18.
//

#include <core/lib/Alias.hpp>
#include "ecs_plugin_bar.hpp"

namespace sfme::testing::plugins
{

    void BarSystem::update() noexcept
    {
        (void)_ettMgr;
    }

    BarSystem::BarSystem(sfme::mediator::EventManager &evtMgr, EntityManager &ettMgr) noexcept :
        System(evtMgr),
        _ettMgr(ettMgr)
    {
    }

    std::shared_ptr<sfme::ecs::BaseSystem>
    BarSystem::createSystem(sfme::mediator::EventManager &evtMgr, EntityManager &ettMgr) noexcept
    {
        return std::make_shared<BarSystem>(evtMgr, ettMgr);
    }

    lib_alias_function(BarSystem::createSystem, createSystem);
}