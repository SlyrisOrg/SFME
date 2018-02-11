//
// Created by milerius on 11/02/18.
//

#include <SFME/ecs/ecs.hpp>
#include "ecs_common_example.hpp"

int main()
{
    //! Managers
    sfme::mediator::EventManager evtMgr;
    sfme::example::EntityManager ettMgr;
    sfme::ecs::SystemManager<sfme::example::EntityManager> systemMgr{evtMgr, ettMgr};

    //! System Loading
    systemMgr.loadSystems<sfme::example::system::PostUpdate,
        sfme::example::system::PreUpdate,
        sfme::example::system::Logic>();

    //! Game Loop
    for (int i = 0; i < 50000; ++i) {
        systemMgr.update();
    }
    return 0;
}