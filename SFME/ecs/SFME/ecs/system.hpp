//
// Created by milerius on 12/02/18.
//

#pragma once

#include <SFME/ecs/system_base.hpp>
#include <SFME/ecs/details/system_type_traits.hpp>

namespace sfme::ecs
{
    template <typename SystemDerived, typename KindSystem, typename isPlugin>
    class System : public BaseSystem
    {
    private:
        template <typename T>
        using is_kind_system = std::is_same<KindSystem, T>;

    public:
        static constexpr bool is_plugged_system_v = details::is_plugged_system_v<isPlugin>();
    public:
        template <typename ...Args>
        explicit System(Args &&...args) noexcept : BaseSystem(std::forward<Args>(args)...)
        {
        }

        ~System() noexcept override = default;

        void update() noexcept override = 0;

        static constexpr SystemType getSystemType() noexcept
        {
            using is_same_list = meta::list::Transform<details::KindSystemList, is_kind_system>;
            static_assert(details::is_valid_system_v(is_same_list{}), "KindSystem is an invalid template parameter");
            if constexpr (std::is_same_v<KindSystem, TLogicUpdate>)
                return SystemType::LogicUpdate;
            else if constexpr (std::is_same_v<KindSystem, TPreUpdate>)
                return SystemType::PreUpdate;
            else if constexpr (std::is_same_v<KindSystem, TPostUpdate>)
                return SystemType::PostUpdate;
        }

        typeID getType() const noexcept final
        {
            return details::generateID<SystemDerived>();
        }

        SystemType getSystemTypeRTTI() const noexcept final
        {
            return System::getSystemType();
        }

        const std::string &getName() const noexcept final
        {
            return SystemDerived::className();
        }
    };

    template <typename SystemDerived>
    using LogicUpdateSystem = System<SystemDerived, TLogicUpdate, details::NoPluginSystem>;

    template <typename SystemDerived>
    using PreUpdateSystem = System<SystemDerived, TPreUpdate, details::NoPluginSystem>;

    template <typename SystemDerived>
    using PostUpdateSystem = System<SystemDerived, TPostUpdate, details::NoPluginSystem>;

    template <typename SystemDerived>
    using PlugLogicUpdateSystem = System<SystemDerived, TLogicUpdate, details::PluginSystem>;

    template <typename SystemDerived>
    using PlugPreUpdateSystem = System<SystemDerived, TPreUpdate, details::PluginSystem>;

    template <typename SystemDerived>
    using PlugPostUpdateSystem = System<SystemDerived, TPostUpdate, details::PluginSystem>;
}
