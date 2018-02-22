//
// Created by sztergbaum roman on 2/17/2018.
//

#pragma once

#include <utility>
#include <experimental/filesystem>
#include <sol.hpp>
#include <core/meta/List.hpp>
#include <core/reflection/Reflection.hpp>
#include <core/log/Logger.hpp>
#include <SFME/input/input.hpp>

namespace fs = std::experimental::filesystem;

namespace sfme::scripting
{
    class LuaSystem
    {
    public:
        reflect_class(LuaSystem)

    protected:
        LuaSystem(fs::path path = fs::current_path() / fs::path("lua_scripts")) noexcept :
            _directoryScriptPath(std::move(path))
        {
            _state.open_libraries();
            registerBasicFunctions();
            registerBasicTables();
        }

        void registerBasicTables() noexcept
        {
            _log(logging::Debug) << "Register Keyboard Table" << std::endl;
            _state["Keyboard"] = _state.create_table_with(
                input::keyboard::Key::toString(input::keyboard::Key::A), input::keyboard::Key::A,
                input::keyboard::Key::toString(input::keyboard::Key::B), input::keyboard::Key::B,
                input::keyboard::Key::toString(input::keyboard::Key::C), input::keyboard::Key::C,
                input::keyboard::Key::toString(input::keyboard::Key::D), input::keyboard::Key::D,
                input::keyboard::Key::toString(input::keyboard::Key::E), input::keyboard::Key::E,
                input::keyboard::Key::toString(input::keyboard::Key::F), input::keyboard::Key::F,
                input::keyboard::Key::toString(input::keyboard::Key::G), input::keyboard::Key::G,
                input::keyboard::Key::toString(input::keyboard::Key::H), input::keyboard::Key::H,
                input::keyboard::Key::toString(input::keyboard::Key::I), input::keyboard::Key::I,
                input::keyboard::Key::toString(input::keyboard::Key::J), input::keyboard::Key::J,
                input::keyboard::Key::toString(input::keyboard::Key::K), input::keyboard::Key::K,
                input::keyboard::Key::toString(input::keyboard::Key::L), input::keyboard::Key::L,
                input::keyboard::Key::toString(input::keyboard::Key::M), input::keyboard::Key::M,
                input::keyboard::Key::toString(input::keyboard::Key::N), input::keyboard::Key::N,
                input::keyboard::Key::toString(input::keyboard::Key::O), input::keyboard::Key::O,
                input::keyboard::Key::toString(input::keyboard::Key::P), input::keyboard::Key::P,
                input::keyboard::Key::toString(input::keyboard::Key::Q), input::keyboard::Key::Q,
                input::keyboard::Key::toString(input::keyboard::Key::R), input::keyboard::Key::R,
                input::keyboard::Key::toString(input::keyboard::Key::S), input::keyboard::Key::S,
                input::keyboard::Key::toString(input::keyboard::Key::T), input::keyboard::Key::T,
                input::keyboard::Key::toString(input::keyboard::Key::U), input::keyboard::Key::U,
                input::keyboard::Key::toString(input::keyboard::Key::V), input::keyboard::Key::V,
                input::keyboard::Key::toString(input::keyboard::Key::W), input::keyboard::Key::W,
                input::keyboard::Key::toString(input::keyboard::Key::X), input::keyboard::Key::X,
                input::keyboard::Key::toString(input::keyboard::Key::Y), input::keyboard::Key::Y,
                input::keyboard::Key::toString(input::keyboard::Key::Z), input::keyboard::Key::Z,
                input::keyboard::Key::toString(input::keyboard::Key::Num0), input::keyboard::Key::Num0,
                input::keyboard::Key::toString(input::keyboard::Key::Num1), input::keyboard::Key::Num1,
                input::keyboard::Key::toString(input::keyboard::Key::Num2), input::keyboard::Key::Num2,
                input::keyboard::Key::toString(input::keyboard::Key::Num3), input::keyboard::Key::Num3,
                input::keyboard::Key::toString(input::keyboard::Key::Num4), input::keyboard::Key::Num4,
                input::keyboard::Key::toString(input::keyboard::Key::Num5), input::keyboard::Key::Num5,
                input::keyboard::Key::toString(input::keyboard::Key::Num6), input::keyboard::Key::Num6,
                input::keyboard::Key::toString(input::keyboard::Key::Num7), input::keyboard::Key::Num7,
                input::keyboard::Key::toString(input::keyboard::Key::Num8), input::keyboard::Key::Num8,
                input::keyboard::Key::toString(input::keyboard::Key::Num9), input::keyboard::Key::Num9,
                input::keyboard::Key::toString(input::keyboard::Key::Escape), input::keyboard::Key::Escape,
                input::keyboard::Key::toString(input::keyboard::Key::LControl), input::keyboard::Key::LControl,
                input::keyboard::Key::toString(input::keyboard::Key::LShift), input::keyboard::Key::LShift,
                input::keyboard::Key::toString(input::keyboard::Key::LAlt), input::keyboard::Key::LAlt,
                input::keyboard::Key::toString(input::keyboard::Key::LSystem), input::keyboard::Key::LSystem,
                input::keyboard::Key::toString(input::keyboard::Key::RControl), input::keyboard::Key::RControl,
                input::keyboard::Key::toString(input::keyboard::Key::RShift), input::keyboard::Key::RShift,
                input::keyboard::Key::toString(input::keyboard::Key::RAlt), input::keyboard::Key::RAlt,
                input::keyboard::Key::toString(input::keyboard::Key::RSystem), input::keyboard::Key::RSystem,
                input::keyboard::Key::toString(input::keyboard::Key::Menu), input::keyboard::Key::Menu,
                input::keyboard::Key::toString(input::keyboard::Key::LBracket), input::keyboard::Key::LBracket,
                input::keyboard::Key::toString(input::keyboard::Key::LBracket), input::keyboard::Key::RBracket,
                input::keyboard::Key::toString(input::keyboard::Key::SemiColon), input::keyboard::Key::SemiColon,
                input::keyboard::Key::toString(input::keyboard::Key::Comma), input::keyboard::Key::Comma,
                input::keyboard::Key::toString(input::keyboard::Key::Period), input::keyboard::Key::Period,
                input::keyboard::Key::toString(input::keyboard::Key::Quote), input::keyboard::Key::Quote,
                input::keyboard::Key::toString(input::keyboard::Key::Slash), input::keyboard::Key::Slash,
                input::keyboard::Key::toString(input::keyboard::Key::BackSlash), input::keyboard::Key::BackSlash,
                input::keyboard::Key::toString(input::keyboard::Key::Tilde), input::keyboard::Key::Tilde,
                input::keyboard::Key::toString(input::keyboard::Key::Equal), input::keyboard::Key::Equal,
                input::keyboard::Key::toString(input::keyboard::Key::Dash), input::keyboard::Key::Dash,
                input::keyboard::Key::toString(input::keyboard::Key::Space), input::keyboard::Key::Space,
                input::keyboard::Key::toString(input::keyboard::Key::Return), input::keyboard::Key::Return,
                input::keyboard::Key::toString(input::keyboard::Key::BackSpace), input::keyboard::Key::BackSpace,
                input::keyboard::Key::toString(input::keyboard::Key::Tab), input::keyboard::Key::Tab,
                input::keyboard::Key::toString(input::keyboard::Key::PageUp), input::keyboard::Key::PageUp,
                input::keyboard::Key::toString(input::keyboard::Key::PageDown), input::keyboard::Key::PageDown,
                input::keyboard::Key::toString(input::keyboard::Key::End), input::keyboard::Key::End,
                input::keyboard::Key::toString(input::keyboard::Key::Home), input::keyboard::Key::Home,
                input::keyboard::Key::toString(input::keyboard::Key::Insert), input::keyboard::Key::Insert,
                input::keyboard::Key::toString(input::keyboard::Key::Delete), input::keyboard::Key::Delete,
                input::keyboard::Key::toString(input::keyboard::Key::Add), input::keyboard::Key::Add,
                input::keyboard::Key::toString(input::keyboard::Key::Subtract), input::keyboard::Key::Subtract,
                input::keyboard::Key::toString(input::keyboard::Key::Multiply), input::keyboard::Key::Multiply,
                input::keyboard::Key::toString(input::keyboard::Key::Divide), input::keyboard::Key::Divide,
                input::keyboard::Key::toString(input::keyboard::Key::Left), input::keyboard::Key::Left,
                input::keyboard::Key::toString(input::keyboard::Key::Subtract), input::keyboard::Key::Right,
                input::keyboard::Key::toString(input::keyboard::Key::Up), input::keyboard::Key::Up,
                input::keyboard::Key::toString(input::keyboard::Key::Down), input::keyboard::Key::Down,
                input::keyboard::Key::toString(input::keyboard::Key::Numpad0), input::keyboard::Key::Numpad0,
                input::keyboard::Key::toString(input::keyboard::Key::Numpad1), input::keyboard::Key::Numpad1,
                input::keyboard::Key::toString(input::keyboard::Key::Numpad2), input::keyboard::Key::Numpad2,
                input::keyboard::Key::toString(input::keyboard::Key::Numpad3), input::keyboard::Key::Numpad3,
                input::keyboard::Key::toString(input::keyboard::Key::Numpad4), input::keyboard::Key::Numpad4,
                input::keyboard::Key::toString(input::keyboard::Key::Numpad5), input::keyboard::Key::Numpad5,
                input::keyboard::Key::toString(input::keyboard::Key::Numpad6), input::keyboard::Key::Numpad6,
                input::keyboard::Key::toString(input::keyboard::Key::Numpad7), input::keyboard::Key::Numpad7,
                input::keyboard::Key::toString(input::keyboard::Key::Numpad8), input::keyboard::Key::Numpad8,
                input::keyboard::Key::toString(input::keyboard::Key::Numpad9), input::keyboard::Key::Numpad9,
                input::keyboard::Key::toString(input::keyboard::Key::F1), input::keyboard::Key::F1,
                input::keyboard::Key::toString(input::keyboard::Key::F2), input::keyboard::Key::F2,
                input::keyboard::Key::toString(input::keyboard::Key::F3), input::keyboard::Key::F3,
                input::keyboard::Key::toString(input::keyboard::Key::F4), input::keyboard::Key::F4,
                input::keyboard::Key::toString(input::keyboard::Key::F5), input::keyboard::Key::F5,
                input::keyboard::Key::toString(input::keyboard::Key::F6), input::keyboard::Key::F6,
                input::keyboard::Key::toString(input::keyboard::Key::F7), input::keyboard::Key::F7,
                input::keyboard::Key::toString(input::keyboard::Key::F8), input::keyboard::Key::F8,
                input::keyboard::Key::toString(input::keyboard::Key::F9), input::keyboard::Key::F9,
                input::keyboard::Key::toString(input::keyboard::Key::F10), input::keyboard::Key::F10,
                input::keyboard::Key::toString(input::keyboard::Key::F11), input::keyboard::Key::F11,
                input::keyboard::Key::toString(input::keyboard::Key::F12), input::keyboard::Key::F12,
                input::keyboard::Key::toString(input::keyboard::Key::F11), input::keyboard::Key::F13,
                input::keyboard::Key::toString(input::keyboard::Key::F14), input::keyboard::Key::F14,
                input::keyboard::Key::toString(input::keyboard::Key::F15), input::keyboard::Key::F15,
                input::keyboard::Key::toString(input::keyboard::Key::Pause), input::keyboard::Key::Pause
            );
        }

        void registerBasicFunctions() noexcept
        {
            _state.set_function("log_info", [this](const std::string &message) {
                this->_log(logging::Info) << message << std::endl;
            });
            _state.set_function("log_error", [this](const std::string &message) {
                this->_log(logging::Error) << message << std::endl;
            });
            _state.set_function("log_debug", [this](const std::string &message) {
                this->_log(logging::Debug) << message << std::endl;
            });
            _state.set_function("log_warning", [this](const std::string &message) {
                this->_log(logging::Warning) << message << std::endl;
            });
        }

        template <typename Entity, typename EntityManager>
        void registerEntityManager(EntityManager &&ettMgr)
        {
            _state["entityManager"] = std::ref(ettMgr);
            auto ov = sol::overload(
                [](EntityManager &self, const std::string &component) {
                    return self.getEntitiesWithComponents(component);
                },
                [](EntityManager &self, const std::string &component, const std::string &component2) {
                    return self.getEntitiesWithComponents(component, component2);
                },
                [](EntityManager &self, const std::string &component, const std::string &component2,
                   const std::string &component3) {
                    return self.getEntitiesWithComponents(component, component2, component3);
                },
                [](EntityManager &self, const std::string &component, const std::string &component2,
                   const std::string &component3, const std::string &component4) {
                    return self.getEntitiesWithComponents(component, component2, component3, component4);
                },
                [](EntityManager &self, const std::string &component, const std::string &component2,
                   const std::string &component3, const std::string &component4, const std::string &component5) {
                    return self.getEntitiesWithComponents(component, component2, component3, component4, component5);
                });
            using namespace std::string_literals;
            _state["EntityManager"]["getEntitiesWithComponents"s] = ov;
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

        template <typename Component, typename Entity, typename EntityManager>
        void registerComponent(EntityManager &&ettMgr)
        {
            using namespace std::string_literals;
            _log(logging::Debug) << "register component: " << Component::className() << std::endl;
            _state[Entity::className()]["get"s + Component::className() + "Component"s] = [](Entity &self) {
                return std::ref(self.template getComponent<Component>());
            };

            _state[Entity::className()]["remove"s + Component::className() + "Component"s] = [](Entity &self) {
                self.template removeComponent<Component>();
            };

            _state[Entity::className()]["has"s + Component::className() + "Component"s] = [](Entity &self) {
                return self.template hasComponent<Component>();
            };

            _state[Entity::className()]["add"s + Component::className() + "Component"s] = [](
                [[maybe_unused]] Entity &self) {
                if constexpr (std::is_default_constructible_v<Component>)
                    return std::ref(self.template addComponent<Component>());
            };

            _state[ettMgr.className()]["getEntityWith"s + Component::className() + "Component"s] = [](
                EntityManager &self) {
                return self.template getEntitiesWithComponent<Component>();
            };
        }

        template <typename Entity, typename EntityManager, typename ...Types>
        void registerComponents(EntityManager &&ettMgr, meta::TypeList<Types...>) noexcept
        {
            (registerType<Types>(), ...);
            (registerComponent<Types, Entity>(std::forward<EntityManager>(ettMgr)), ...);
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
                _state.script_file((_directoryScriptPath / fs::path(fileName)).string());
                _log(logging::Debug) << "Successfully register script: " << fileName << std::endl;
            } catch (const std::exception &e) {
                _log(logging::Error) << fileName << ": " << e.what() << std::endl;
            }
        }

        template <typename Entity, typename ScriptComponent, typename EntityManager>
        void loadAllEntitiesScript(EntityManager &&ettMgr) noexcept
        {
            ettMgr.template for_each<ScriptComponent>([this](const Entity &et) {
                const std::string &fileName = et.template getComponent<ScriptComponent>().scriptName;
                LuaSystem::loadScript(fileName);
            });
        };

#ifdef USING_UNIX
        template <typename ReturnType = void, typename ...Args>
        ReturnType executeGlobalFunction(const std::string &funcName, Args &&...args)
        {
            if constexpr (std::is_void_v<ReturnType>) {
                _state[funcName](std::forward<Args>(args)...);
            } else {
                return _state[funcName](std::forward<Args>(args)...);
            }
        }
#elif defined(USING_MSVC)
        //Bug: This is a workaround for MSVC 15.6, switch to if constexpr in the future
        template <typename ...Args>
        void executeGlobalFunction(const std::string &funcName, Args &&...args)
        {
            _state[funcName](std::forward<Args>(args)...);
        }

        template <typename ReturnType, typename ... Args>
        ReturnType executeGlobalFunction(const std::string &funcName, Args &&...args)
        {
            return _state[funcName](std::forward<Args>(args)...);
        }

#endif

        // ReSharper disable CppNotAllPathsReturnValue
        template <typename ReturnType = void, typename ...Args>
        ReturnType executeScopedFunction(const std::string &scopName, const std::string &funcName, Args &&...args)
        {
            if constexpr (std::is_void_v<ReturnType>) {
                _state[scopName][funcName](std::forward<Args>(args)...);
            } else {
                return _state[scopName][funcName](std::forward<Args>(args)...);
            }
        }

    private:
        sol::state _state;
        fs::path _directoryScriptPath;
        logging::Logger _log{"lua-system", logging::Debug};
    };
}
