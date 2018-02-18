//
// Created by sztergbaum roman on 2/17/2018.
//

#pragma once

#include <experimental/filesystem>
#include <sol.hpp>
#include <core/meta/List.hpp>
#include <core/reflection/Reflection.hpp>
#include <core/log/Logger.hpp>

namespace fs = std::experimental::filesystem;

namespace sfme::scripting
{
    class ScriptingLua
    {
    protected:
        ScriptingLua(fs::path path = fs::current_path() / fs::path("lua_scripts")) noexcept :
            _pathScriptDirectory(std::move(path))
        {
            _state.open_libraries();
        }

        template <typename T>
        void registerType() noexcept
        {
            _log(logging::Debug) << "register Type: " << T::className() << std::endl;

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
            _log(logging::Debug) << "register EntityManager" << std::endl;
            _state.set_function("createEntity", [&ettMgr]() { return ettMgr.createEntity(); });
            _state.set_function("getEntity", [&ettMgr](typename Entity::ID id) -> Entity & {
                return std::ref(ettMgr.getEntity(id));
            });
            _state.set_function("getEntityConst", [&ettMgr](typename Entity::ID id) -> const Entity & {
                return std::ref(ettMgr.getEntityConst(id));
            });
        }

        template <typename Component, typename Entity>
        void registerComponent()
        {
            using namespace std::string_literals;
            _log(logging::Debug) << "register component: " << Component::className() << std::endl;
            _state[Entity::className()]["get"s + Component::className() + "Component"s] = [](Entity &self) {
                return std::ref(self.template getComponent<Component>());
            };

            _state[Entity::className()]["remove"s + Component::className() + "Component"s] = [](Entity &self) {
                self.template removeComponent<Component>();
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
            _log(logging::Debug) << "register system: " << SystemType::className() << std::endl;
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

        void loadScript(const std::string &fileName) noexcept
        {
            try {
                _state.script_file((_pathScriptDirectory / fs::path(fileName)).string());
                _log(logging::Debug) << "Successfully register script: " << fileName << std::endl;
            } catch (const std::exception &e) {
                _log(logging::Error) << fileName << ": " << e.what() << std::endl;
            }
        }

        template<typename Entity, typename ScriptComponent, typename EntityManager>
        void loadAllEntitiesScript(EntityManager&& ettMgr) noexcept
        {
            ettMgr.template for_each<ScriptComponent>([this](const Entity& et) {
                const std::string &fileName = et.template getComponent<ScriptComponent>().scriptName;
                const std::string &self = et.template getComponent<ScriptComponent>().selfName;
                ScriptingLua::loadScript(fileName);
            });
        };

        template <typename ReturnType = void, typename ...Args>
        ReturnType executeGlobalFunction(const std::string &funcName, Args &&...args)
        {
            if constexpr (std::is_void_v<ReturnType>) {
                _state[funcName](std::forward<Args>(args)...);
            } else {
                return _state[funcName](std::forward<Args>(args)...);
            }
        }

        template <typename ReturnType = void, typename ...Args>
        ReturnType executeScopedFunction(const std::string& scopName, const std::string &funcName, Args &&...args)
        {
            if constexpr (std::is_void_v<ReturnType>) {
                _state[scopName][funcName](std::forward<Args>(args)...);
            } else {
                return _state[scopName][funcName](std::forward<Args>(args)...);
            }
        }

    private:
        sol::state _state;
        fs::path _pathScriptDirectory;
        using Logger = logging::Logger;
        Logger _log{"lua-engine", logging::Debug};
    };
}
