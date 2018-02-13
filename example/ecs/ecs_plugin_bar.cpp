//
// Created by milerius on 13/02/18.
//

#include <core/lib/Alias.hpp>
#include "ecs_plugin_bar.hpp"

namespace sfme::example::plugins
{
    void BarSystem::update() noexcept
    {
        (void)_ettMgr;
        std::cout << __FUNCTION__ << std::endl;
    }

    BarSystem::BarSystem(sfme::mediator::EventManager &evtMgr, EntityManager &ettMgr) noexcept :
        System(evtMgr),
        _ettMgr(ettMgr)
    {
    }

    std::shared_ptr<sfme::ecs::BaseSystem>
    BarSystem::createSystem(sfme::mediator::EventManager &evtMgr, EntityManager &ettMgr) noexcept
    {
        std::cout << __FUNCTION__ << std::endl;
        return std::make_shared<BarSystem>(evtMgr, ettMgr);
    }

    lib_alias_function(BarSystem::createSystem, createSystem);
}
