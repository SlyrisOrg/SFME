//
// Created by sztergbaum roman on 2/17/2018.
//

#pragma once

#include <SFME/ecs/entity_manager.hpp>
#include <SFME/ecs/system_manager.hpp>

namespace sfme::world
{
    template <typename Components, typename ScriptingLanguage>
    struct Traits
    {
        using TEventManager = sfme::mediator::EventManager;
        using TComponents = Components;
        using TEntityManager = sfme::ecs::EntityManager<TComponents>;
        using TScriptingSystem = ScriptingLanguage;
        using TEntity = typename TEntityManager::Entity;
        using TSystemManager = sfme::ecs::SystemManager<TEntityManager>;
    };
}
