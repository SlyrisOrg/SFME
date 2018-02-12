#include "ecs_plugin_foo.hpp"
#include "ecs_common_example.hpp"

int main()
{
    sfme::mediator::EventManager evtMgr;
    sfme::example::EntityManager ettMgr;
    sfme::ecs::SystemManager<sfme::example::EntityManager> systemMgr{evtMgr, ettMgr};
    systemMgr.createSystem<sfme::example::system::Logic>();
    systemMgr.createSystem<sfme::example::system::WithUserData>(1, 2);
    systemMgr.loadPlugin<sfme::example::plugins::FooSystem>("sfme_ecs_foo_plugin_example");
    systemMgr.update();
    return 0;
}