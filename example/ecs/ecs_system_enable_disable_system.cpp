//
// Created by sztergbaum roman on 2/17/2018.
//

#include "ecs_common_example.hpp"

int main()
{
    sfme::mediator::EventManager evtMgr;
    sfme::example::EntityManager ettMgr;
    sfme::ecs::SystemManager<sfme::example::EntityManager> systemMgr{evtMgr, ettMgr};

    systemMgr.loadSystems<sfme::example::system::PostUpdate, sfme::example::system::Logic,
        sfme::example::system::PreUpdate>();
    systemMgr.update();
    systemMgr.disableSystem<sfme::example::system::PreUpdate>();
    systemMgr.update();
    systemMgr.enableSystem<sfme::example::system::PreUpdate>();
    systemMgr.update();
    systemMgr.disableSystems<sfme::example::system::PreUpdate, sfme::example::system::PostUpdate>();
    systemMgr.update();
    systemMgr.enableSystems<sfme::example::system::PreUpdate, sfme::example::system::PostUpdate>();
    systemMgr.update();
    return 0;
}