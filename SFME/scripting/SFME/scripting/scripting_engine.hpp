//
// Created by sztergbaum roman on 2/17/2018.
//

#pragma once

#include <core/meta/List.hpp>
namespace sfme::scripting
{
    template <typename GameTraits>
    class ScriptingEngine : private GameTraits::TScriptingLanguage
    {
    public:
        using TScriptLang = typename GameTraits::TScriptingLanguage;
        using TComponents = typename GameTraits::TComponents;
        using TEntityManager = typename GameTraits::TEntityManager;
        using TSystemManager = typename GameTraits::TSystemManager;
        using TEntity = typename GameTraits::TEntity;
    public:
        ScriptingEngine(TEntityManager &ettMgr, TSystemManager &systemMgr) noexcept :
            TScriptLang(), _ettMgr(ettMgr), _systemMgr(systemMgr)
        {
            registerType<TEntity>();
            TScriptLang::template registerEntityManager<TEntity>(_ettMgr);
            TScriptLang::template registerComponents<TEntity>(TComponents{});
        }

        template <typename Type>
        void registerType() noexcept
        {
            TScriptLang::template registerType<Type>();
        }

        template<typename ...Types>
        void registerTypeList(meta::TypeList<Types...>) noexcept
        {
            (registerType<Types>(), ...);
        }

        template <typename TypeList>
        void registerSystems() noexcept
        {
            registerTypeList(TypeList{});
            TScriptLang::registerSystems(_systemMgr, TypeList{});
        }

    private:
        TEntityManager &_ettMgr;
        TSystemManager &_systemMgr;
    };
}