//
// Created by sztergbaum roman on 2/17/2018.
//

#pragma once

#include <SFME/scripting/scripting_lua.hpp>
#include <SFME/ecs/system_manager.hpp>
#include <SFME/ecs/entity_manager.hpp>

namespace sfme::scripting
{
    template <typename Components, typename ScriptingLanguage = ScriptingLua>
    class ScriptingEngine
    {
    public:
        using ScriptLang = ScriptingLanguage;
        using ScriptState = typename ScriptingLanguage::State;
        using TComponents = Components;
        using EntityManager = sfme::ecs::EntityManager<Components>;
        using SystemManager = sfme::ecs::SystemManager<EntityManager>;
        using Entity = typename EntityManager::Entity;
    public:
        ScriptingEngine(EntityManager& ettMgr, SystemManager &systemMgr) : _ettMgr(ettMgr), _systemMgr(systemMgr)
        {
            ScriptingLanguage::openLibraries(_state);
            ScriptingLanguage::template registerType<Entity>(_state);
            ScriptingLanguage::registerComponents(_state, _ettMgr, Components{});
        }

    private:
        ScriptState _state;
        EntityManager& _ettMgr;
        SystemManager& _systemMgr;
    };
}