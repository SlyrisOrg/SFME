//
// Created by milerius on 12/02/18.
//

#pragma once

#include <SFME/ecs/system_base.hpp>

namespace sfme::ecs
{
    template <typename SystemDerived, typename KindSystem>
    class System : public BaseSystem
    {
    private:
        template <typename T>
        using is_kind_system = std::is_same<KindSystem, T>;
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
    };

    template <typename SystemDerived>
    using LogicUpdateSystem = System<SystemDerived, TLogicUpdate>;

    template <typename SystemDerived>
    using PreUpdateSystem = System<SystemDerived, TPreUpdate>;

    template <typename SystemDerived>
    using PostUpdateSystem = System<SystemDerived, TPostUpdate>;
}
