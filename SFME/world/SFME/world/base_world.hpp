//
// Created by sztergbaum roman on 2/17/2018.
//

#pragma once

#include <SFME/world/details/world_traits.hpp>

namespace sfme
{
    template <typename WorldTraits>
    class World
    {
    private:
        using Components = typename WorldTraits::TComponents;
        using EventManager = typename WorldTraits::TEventManager;
        using EntityManager = typename WorldTraits::TEntityManager;
        using SystemManager = typename WorldTraits::TSystemManager;

    protected:
        EventManager _evtMgr;
        EntityManager _ettMgr;
        SystemManager _sysMgr{_evtMgr, _ettMgr};
    };
}