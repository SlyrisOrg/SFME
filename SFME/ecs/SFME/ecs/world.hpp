//
// Created by milerius on 11/02/18.
//

#pragma once

#include <SFME/mediator/event_manager.hpp>
#include <SFME/ecs/entity_manager.hpp>
#include <SFME/ecs/system_manager.hpp>

namespace sfme::ecs
{
    template<typename ECS>
    class World
    {
    private:
        using EntityManager = sfme::ecs::EntityManager<ECS>;
        using SystemManager = sfme::ecs::SystemManager<EntityManager>;
    protected:
        sfme::mediator::EventManager _evtMgr;
        EntityManager _ettMgr;
        SystemManager _sysMgr{_evtMgr, _ettMgr};
    };
}
