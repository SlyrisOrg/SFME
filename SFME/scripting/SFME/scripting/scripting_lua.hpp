//
// Created by sztergbaum roman on 2/17/2018.
//

#pragma once

#include <sol.hpp>
#include <core/meta/List.hpp>
#include <core/reflection/Reflection.hpp>

namespace sfme::scripting
{
    class ScriptingLua
    {
    public:
        using State = sol::state;
    public:
        static void openLibraries(State &state)
        {
            state.open_libraries();
        }

        template <typename T>
        static void registerType(State &state)
        {
            const auto table = std::tuple_cat(
                std::make_tuple(T::className()),
                T::reflectedFunctions(),
                T::reflectedMembers());

            std::apply(
                [&state](auto &&...params) {
                    state.new_usertype<T>(std::forward<decltype(params)>(params)...);
                }, table);
        }

        template<typename T, typename EntityManager>
        static void registerComponent(State& state, EntityManager& ettMgr)
        {
            using namespace std::string_literals;
            state["Entity"]["get"s + T::className() + "Component"s] = [](typename EntityManager::Entity &self) {
                return std::ref(self.template getComponent<T>());
            };
            state["Entity"]["remove"s + T::className() + "Component"s] = [](typename EntityManager::Entity &self) {
                return std::ref(self.template removeComponent<T>());
            };
        }

        template <typename EntityManager, typename ...Types>
        static void registerComponents(State& state, EntityManager& ettMgr, meta::TypeList<Types...>)
        {
            (registerType<Types>(state), ...);
            (registerComponent<Types>(state, ettMgr), ...);
        }
    };
}
