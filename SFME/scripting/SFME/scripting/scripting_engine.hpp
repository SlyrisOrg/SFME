//
// Created by sztergbaum roman on 2/17/2018.
//

#pragma once

#include <experimental/filesystem>
#include <core/meta/List.hpp>
#include <SFME/ecs/ecs.hpp>

namespace fs = std::experimental::filesystem;

namespace sfme::scripting
{
    template <typename GameTraits>
    class ScriptedSystem : public sfme::ecs::LogicUpdateSystem<ScriptedSystem<GameTraits>>,
                           private GameTraits::TScriptingSystem
    {
    public:
        static const std::string &className() noexcept
        {
            return GameTraits::TScriptingSystem::className();
        }

    public:
        using TScriptingSystem = typename GameTraits::TScriptingSystem;
        using TComponents = typename GameTraits::TComponents;
        using TEntityManager = typename GameTraits::TEntityManager;
        using TSystemManager = typename GameTraits::TSystemManager;
        using TEntity = typename GameTraits::TEntity;
        using TEventManager = typename GameTraits::TEventManager;
        using TSystem = sfme::ecs::LogicUpdateSystem<ScriptedSystem<GameTraits>>;

    public:
        ScriptedSystem(TEventManager &evtMgr, TEntityManager &ettMgr) noexcept :
            TSystem::System(evtMgr),
            TScriptingSystem(),
            _ettMgr(ettMgr)
        {
            registerType<TEntity>();
			registerType<TEntityManager>();
            TScriptingSystem::template registerEntityManager<TEntity>(_ettMgr);
            TScriptingSystem::template registerComponents<TEntity>(_ettMgr, TComponents{});
        }

        template <typename Type>
        void registerType() noexcept
        {
            TScriptingSystem::template registerType<Type>();
        }

        template <typename ...Types>
        void registerTypeList(meta::TypeList<Types...>) noexcept
        {
            (registerType<Types>(), ...);
        }

        template <typename TypeList, typename SystemManager>
        void registerSystems(SystemManager &&systemMgr) noexcept
        {
            registerTypeList(TypeList{});
            TScriptingSystem::registerSystems(systemMgr, TypeList{});
        }

        template <typename ScriptComponent>
        void loadEntitiesScript() noexcept
        {
            TScriptingSystem::template loadAllEntitiesScript<TEntity, ScriptComponent>(_ettMgr);
        };

        void loadScript(const std::string& fileName) noexcept
        {
            TScriptingSystem::loadScript(fileName);
        }

        template<typename ReturnType = void, typename ...Args>
        ReturnType executeGlobalFunction(const std::string &funcName, Args&& ...args) noexcept
        {
            return TScriptingSystem::template executeGlobalFunction<ReturnType>(funcName, std::forward<Args>(args)...);
        }

        template<typename ReturnType = void, typename ...Args>
        ReturnType executeScopedFunction(const std::string &scopName, const std::string &funcName, Args&& ...args) noexcept
        {
            return TScriptingSystem::template executeScopedFunction<ReturnType>(scopName, funcName, std::forward<Args>(args)...);
        }

        void update() noexcept override
        {
        }

        ~ScriptedSystem() noexcept override = default;

    public:
        static constexpr auto reflectedFunctions() noexcept
        {
            return meta::makeMap();
        }

        static constexpr auto reflectedMembers() noexcept
        {
            return meta::makeMap();
        }

    private:
        TEntityManager &_ettMgr;
    };
}