# SFME
Simple and Fast Multimedia Engine

Built with SFML and love.

## Table of contents

 - [Description](#description)
 - [Installation](#install)
 - [Documentation](#doc)


## Description<a name="description"></a>

SFME (Simple and Fast Multimedia Engine) is an engine divided into several modules which do not necessarily depend on each other.
 
Therefore, you can use the whole engine or only one module, it just depends on your needs.


## Installation<a name="install"></a>

```git clone git@github.com:Milerius/SFME.git```


## Documentation<a name="doc"></a>

See this repository's wiki for more info

[SFME's wiki](https://github.com/Milerius/SFME/wiki)

## Getting Started (SFML)
This snippet of code will allow you to have a basic window and start your project.

```cpp
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

//! Game type traits
namespace
{
    using Components = meta::list::Concat<sfme::ecs::components::CommonComponents, sfme::sfml::components::CommonComponents>;

    //We configure our game using the selected components and a scripting language.
    using GameTraits = sfme::world::Traits<Components, sfme::scripting::LuaSystem>;

    //A few aliases for convenience
    using EntityManager = GameTraits::TEntityManager;
    using Entity = GameTraits::TEntity;
    using ScriptingSystem = sfme::scripting::ScriptedSystem<GameTraits>;
    using GraphicalSystem = sfme::sfml::systems::Graphical<GameTraits>;
    using EventSystem = sfme::sfml::systems::Event<GameTraits>;
    using SystemList = meta::TypeList<ScriptingSystem, GraphicalSystem, EventSystem>;
    using ResourceManager = sfme::resource::ResourceManager<sfme::sfml::ResourceManager, std::string>;
}

//! Our game world.
class World : public sfme::World<GameTraits>, public sfme::mediator::Receiver<World>
{
public:
    World()
    {
        //We subscribe to the events we want to handle
        _evtMgr.subscribe<sfme::mediator::evt::GameShutdown>(*this);
        _evtMgr.subscribe<sfme::mediator::evt::KeyPressed>(*this);
        auto &window = _sysMgr.createSystem<GraphicalSystem>().getWindow();
        _sysMgr.createSystem<EventSystem>(window);
        _sysMgr.createSystem<ScriptingSystem>().registerSystems<SystemList>(_sysMgr);
    }

    void run() noexcept
    {
        _running = true;
        _evtMgr.emit<sfme::mediator::evt::GameStarted>();
        //! Main game loop, running each systems, we take care of the deltaTime for you
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
    World world;

    world.run();
    return 0;
}
```
