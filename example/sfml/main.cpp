//
// Created by sztergbaum roman on 2/23/2018.
//

#include <SFME/ecs/common_components.hpp>
#include <SFME/world/world.hpp>
#include <SFME/scripting/scripting.hpp>
#include <SFME/scripting/scripting_lua.hpp>
#include <SFME/sfml/sfml.hpp>
#include <SFME/sfml/resource_manager.hpp>
#include <SFME/resource_manager/base_resource_manager.hpp>

namespace
{
    using Components = meta::list::Concat<sfme::ecs::components::CommonComponents, sfme::sfml::components::CommonComponents>;
    using GameTraits = sfme::world::Traits<Components, sfme::scripting::LuaSystem>;
    using EntityManager = GameTraits::TEntityManager;
    using Entity = GameTraits::TEntity;
    using ScriptingSystem = sfme::scripting::ScriptedSystem<GameTraits>;
    using GraphicalSystem = sfme::sfml::systems::Graphical<GameTraits>;
    using EventSystem = sfme::sfml::systems::Event<GameTraits>;
    using SystemList = meta::TypeList<ScriptingSystem, GraphicalSystem, EventSystem>;
    using ResourceManager = sfme::resource::ResourceManager<sfme::sfml::ResourceManager, std::string>;
}

class World : public sfme::World<GameTraits>, public sfme::mediator::Receiver<World>
{
public:
    World()
    {
        _evtMgr.subscribe<sfme::mediator::evt::GameShutdown>(*this);
        _evtMgr.subscribe<sfme::mediator::evt::KeyPressed>(*this);
        auto &window = _sysMgr.createSystem<GraphicalSystem>().getWindow();
        _sysMgr.createSystem<EventSystem>(window);
        _sysMgr.createSystem<ScriptingSystem>().registerSystems<SystemList>(_sysMgr);
        ResourceManager resourceManager;
        resourceManager.loadTexture(fs::path("zelda"));
        resourceManager.unloadTexture("zelda");
    }

    void run() noexcept
    {
        _running = true;
        _evtMgr.emit<sfme::mediator::evt::GameStarted>();
        while (_running) {
            _sysMgr.update();
        }
    }

public:
    //! Callback
    void receive([[maybe_unused]] const sfme::mediator::evt::GameShutdown &evt) noexcept
    {
        _running = false;
    }

    void receive(const sfme::mediator::evt::KeyPressed &evt) noexcept
    {
        if (evt.key == sfme::input::keyboard::Key::Escape)
            receive(sfme::mediator::evt::GameShutdown{});
    }

private:
    bool _running{false};
};

int main()
{
    fs::copy(fs::current_path().parent_path() / "example/sfml/assets", fs::current_path() / "assets",
             fs::copy_options::recursive | fs::copy_options::update_existing);
    World world;
    world.run();
    return 0;
}