//
// Created by sztergbaum roman on 2/17/2018.
//

#pragma once

#include <SFME/ecs/entity_manager.hpp>
#include <SFME/ecs/system_manager.hpp>
#include <SFME/scripting/scripting_lua.hpp>
#include <SFME/scripting/scripting.hpp>

namespace sfme::world
{
    template <typename Components, typename ScriptingLanguage = sfme::scripting::ScriptingLua>
    struct Traits
    {
        using TEventManager = sfme::mediator::EventManager;
        using TComponents = Components;
        using TEntityManager = sfme::ecs::EntityManager<TComponents>;
        using TScriptingLanguage = ScriptingLanguage;
        using TEntity = typename TEntityManager::Entity;
        using TSystemManager = sfme::ecs::SystemManager<TEntityManager>;
    };

    template<typename Traits>
    using TScriptingEngine = sfme::scripting::ScriptingEngine<Traits>;
}
