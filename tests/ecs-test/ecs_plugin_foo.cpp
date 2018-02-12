//
// Created by milerius on 12/02/18.
//

#include <core/lib/Alias.hpp>
#include "ecs_plugin_foo.hpp"

namespace sfme::testing::plugins
{

    void FooSystem::update() noexcept
    {
        (void)_ettMgr;
    }

    FooSystem::FooSystem(sfme::mediator::EventManager &evtMgr, EntityManager &ettMgr) noexcept :
        System(evtMgr),
        _ettMgr(ettMgr)
    {
    }

    std::shared_ptr<sfme::ecs::BaseSystem>
    FooSystem::createSystem(sfme::mediator::EventManager &evtMgr, EntityManager &ettMgr) noexcept
    {
        return std::make_shared<FooSystem>(evtMgr, ettMgr);
    }

    lib_alias_function(FooSystem::createSystem, createSystem);
}

