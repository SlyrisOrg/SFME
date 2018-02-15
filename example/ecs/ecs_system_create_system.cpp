#include "ecs_common_example.hpp"

namespace fs = std::experimental::filesystem;

int main()
{
    sfme::mediator::EventManager evtMgr;
    sfme::example::EntityManager ettMgr;
    sfme::ecs::SystemManager<sfme::example::EntityManager> systemMgr{evtMgr, ettMgr,
                                                                     fs::current_path() / "example/systems"};

    //! Simple system creation
    systemMgr.createSystem<sfme::example::system::Logic>();

    //! Simple system creation with user data.
    systemMgr.createSystem<sfme::example::system::WithUserData>(1, 2);

    //! Multiple systems creation
    systemMgr.loadSystems<sfme::example::system::PostUpdate, sfme::example::system::PreUpdate>();

    //! Simple plugged system creation
    systemMgr.loadPlugin("sfme_ecs_foo_plugin_example");

    //! Multiple plugged system creation
    systemMgr.loadPlugins();
    return 0;
}