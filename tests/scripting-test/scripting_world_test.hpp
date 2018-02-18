//
// Created by sztergbaum roman on 2/18/2018.
//

#pragma once

#include <SFME/world/world.hpp>

namespace sfme::example::components
{
     struct PV
     {
         reflect_class(pv);

         static constexpr auto reflectedFunctions() noexcept
         {
             return meta::makeMap();
         }

         static constexpr auto reflectedMembers() noexcept
         {
             return meta::makeMap(reflect_member(&PV::pv));
         }

         int pv;
     };
}

namespace sfme::example
{
    using Components = meta::TypeList<components::PV>;
    using GameTraits = sfme::world::Traits<Components, sfme::scripting::ScriptingLua>;
    using EntityManager = GameTraits::TEntityManager;
}

namespace sfme::example::system
{
    struct Logical : public sfme::ecs::LogicUpdateSystem<Logical>
    {
        reflect_class(Logical);
     
        Logical(sfme::mediator::EventManager &evtMgr, EntityManager &ettMgr) noexcept :
            System(evtMgr),
            _ettMgr(ettMgr)
        {
        }

        void update() noexcept override
        {
            std::cout << __FUNCTION__ << std::endl;
        }

        ~Logical() noexcept override = default;

        static constexpr auto reflectedFunctions() noexcept
        {
            return meta::makeMap(reflect_function(&Logical::update));
        }

        static constexpr auto reflectedMembers() noexcept
        {
            return meta::makeMap();
        }
        
        EntityManager &_ettMgr;
    };
}

namespace sfme::example
{
    using SystemList = meta::TypeList<system::Logical>;
}