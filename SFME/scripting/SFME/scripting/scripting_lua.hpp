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
    protected:
        ScriptingLua() noexcept
        {
            _state.open_libraries();
        }

        template <typename T>
        void registerType() noexcept
        {
            const auto table = std::tuple_cat(
                std::make_tuple(T::className()),
                T::reflectedFunctions(),
                T::reflectedMembers());

            std::apply(
                [this](auto &&...params) {
                    this->_state.new_usertype<T>(std::forward<decltype(params)>(params)...);
                }, table);
        }

        template <typename Entity, typename EntityManager>
        void registerEntityManager(EntityManager &&ettMgr)
        {
            _state.set_function("createEntity", [&ettMgr]() { return ettMgr.createEntity(); });
            _state.set_function("getEntity", [&ettMgr](typename Entity::ID id) -> Entity & {
                return std::ref(ettMgr.getEntity(id));
            });
            _state.set_function("getEntityConst", [&ettMgr](typename Entity::ID id) -> const Entity & {
                return std::ref(ettMgr.getEntityConst(id));
            });
        }

        template <typename T, typename Entity>
        void registerComponent()
        {
            using namespace std::string_literals;

            _state[Entity::className()]["get"s + T::className() + "Component"s] = [](Entity &self) {
                return std::ref(self.template getComponent<T>());
            };

            _state[Entity::className()]["remove"s + T::className() + "Component"s] = [](Entity &self) {
                self.template removeComponent<T>();
            };
        }

        template <typename Entity, typename ...Types>
        void registerComponents(meta::TypeList<Types...>) noexcept
        {
            (registerType<Types>(), ...);
            (registerComponent<Types, Entity>(), ...);
        }

        template <typename SystemType, typename SystemManager>
        void registerSystem(SystemManager &&systemMgr) noexcept
        {
            using namespace std::string_literals;
            _state.set_function("get"s + SystemType::className() + "System",
                                [&systemMgr]() {
                                    return std::ref(systemMgr.template getSystem<SystemType>());
                                });
        };

        template <typename SystemManager, typename ...Types>
        void registerSystems(SystemManager &&systemMgr, meta::TypeList<Types...>) noexcept
        {
            (registerSystem<Types>(systemMgr), ...);
        }

    private:
        sol::state _state;
    };
}
