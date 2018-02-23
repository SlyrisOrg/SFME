//
// Created by sztergbaum roman on 2/23/2018.
//

#pragma once

#include <SFML/Graphics.hpp>
#include <SFME/ecs/system.hpp>

namespace sfme::sfml::systems
{
    template <typename GameTraits>
    class Graphical : public sfme::ecs::PostUpdateSystem<Graphical<GameTraits>>
    {
    public:
        //! Typedefs
        using TEntityManager = typename GameTraits::TEntityManager;
        using TSystem = sfme::ecs::PostUpdateSystem<Graphical<GameTraits>>;

    public:
        //! Constructor/Destructor
        Graphical(sfme::mediator::EventManager &evtMgr, TEntityManager &ettMgr) noexcept :
            TSystem::System(evtMgr),
            _ettMgr(ettMgr)
        {
        }

        ~Graphical() noexcept override
        {
        }

    public:
        //! Member function override
        void update() noexcept override
        {
            _win.clear();
            //TODO: Write here the rest of this function
            _win.display();
        }

    public:
        //! Property
        const sf::RenderWindow &getWindow() const noexcept
        {
            return _win;
        }

        sf::RenderWindow &getWindow() noexcept
        {
            return _win;
        }

    public:
        //! Reflection
        reflect_class(Graphical)

        static constexpr auto reflectedFunctions() noexcept
        {
            return meta::makeMap();
        }

        static constexpr auto reflectedMembers() noexcept
        {
            return meta::makeMap();
        }

    private:
        //TODO: Write a system configuration for the  SFML module
        sf::RenderWindow _win{sf::VideoMode(1920, 1080), "SFML window"};
        TEntityManager &_ettMgr;
    };
}