//
// Created by sztergbaum roman on 2/17/2018.
//

#pragma once

#include <memory>
#include <type_traits>
#include <core/meta/TupleForEach.hpp>
#include <core/meta/List.hpp>
#include <core/reflection/Reflection.hpp>

namespace sfme::ecs::details
{
    template <typename CompsList, template <typename> typename CompsAlloc>
    class Entity
    {
    private:
        using ComponentsList = CompsList;
        using ComponentsPtr = meta::list::Transform<ComponentsList, std::add_pointer_t>;
        using ComponentsPtrTuple = meta::list::Convert<ComponentsPtr, std::tuple>;

        template <typename T>
        using AllocTraits = std::allocator_traits<CompsAlloc<T>>;

    public:
        using AllocatorsList = meta::list::Transform<ComponentsList, CompsAlloc>;
        using AllocatorsTuple = meta::list::Convert<AllocatorsList, std::tuple>;
        using ID = size_t;

        explicit Entity(ID id, AllocatorsTuple &t) noexcept : _id(id), _allocators(t)
        {
            meta::tuple_for_each(_components, [](auto &p) {
                p = nullptr;
            });
        }

        ~Entity() noexcept
        {
            meta::tuple_for_each(_components, [](auto &p) {
                delete p;
                p = nullptr;
            });
        }

        ID getID() const noexcept
        {
            return _id;
        }

        void mark() noexcept
        {
            _marked = true;
        }

        void unmark() noexcept
        {
            _marked = false;
        }

        bool isMarked() const noexcept
        {
            return _marked;
        }

        template <typename T>
        T &getComponent() noexcept
        {
            using namespace meta::list;
            return *std::get<Position<ComponentsList, T>::value>(_components);
        }

        template <typename T>
        const T &getComponent() const noexcept
        {
            using namespace meta::list;
            return *std::get<Position<ComponentsList, T>::value>(_components);
        }

        template <typename ...Args>
        std::tuple<std::add_lvalue_reference_t<Args>...>

        getComponents() noexcept
        {
            return {getComponent<Args>()...};
        }

        template <typename ...Args>
        std::tuple<std::add_lvalue_reference_t<std::add_const_t<Args>>...>

        getComponents() const noexcept
        {
            return {getComponent<Args>()...};
        }

        template <typename T>
        bool hasComponent() const noexcept
        {
            using namespace meta::list;
            return std::get<Position<ComponentsList, T>::value>(_components) != nullptr;
        }

        template <typename T, typename ...Args>
        bool hasComponents() const noexcept
        {
            if constexpr (sizeof...(Args) > 0) {
                return hasComponent<T>() && hasComponents<Args...>();
            }
            return hasComponent<T>();
        }

        bool hasComponents(const std::string &component)
        {
            return std::any_of(_componentsMemoisation.begin(), _componentsMemoisation.end(),
                               [&component](const std::string &componentName) {
                                   return componentName == component;
                               });
        }

        template <typename... Components>
        bool hasComponents(const std::string &cmp, Components &&...components)
        {
            return hasComponents(cmp) && hasComponents(std::forward<Components>(components)...);
        }

        template <typename T, typename ...Args>
        T &addComponent(Args &&...args)
        {
            using namespace meta::list;
            constexpr size_t pos = Position<ComponentsList, T>::value;
            auto &al = std::get<pos>(_allocators);

            std::get<pos>(_components) = AllocTraits<T>::allocate(al, 1);
            AllocTraits<T>::construct(al, std::get<pos>(_components), args...);
            _componentsMemoisation.push_back(T::className());
            return getComponent<T>();
        }

        template <typename T>
        void removeComponent()
        {
            using namespace meta::list;
            constexpr size_t pos = Position<ComponentsList, T>::value;
            auto &al = std::get<pos>(_allocators);

            AllocTraits<T>::destroy(al, std::get<pos>(_components));
            AllocTraits<T>::deallocate(al, std::get<pos>(_components), 1);
            std::get<pos>(_components) = nullptr;
            algo::erase_if(_componentsMemoisation, [](auto &&componentName) {
                return T::className() == componentName;
            });
        }

        reflect_class(Entity)

        static constexpr auto reflectedFunctions() noexcept
        {
            return meta::makeMap(reflect_function(&Entity::getID));
        }

    private:
        ID _id;
        AllocatorsTuple &_allocators;
        ComponentsPtrTuple _components;
        bool _marked{false};
        std::vector<std::string> _componentsMemoisation;

    public:
        static constexpr auto reflectedMembers() noexcept
        {
            return meta::makeMap(reflect_member(&Entity::_id), reflect_member(&Entity::_marked));
        }
    };
}
