//
// Created by sztergbaum roman on 2/23/2018.
//

#pragma once

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include <SFME/mediator/mediator.hpp>
#include <SFME/ecs/ecs.hpp>
#include <SFME/world/world_traits.hpp>

namespace sfme::sfml::systems
{
    template<typename GameTraits>
    class Event : public sfme::ecs::PreUpdateSystem<Event<GameTraits>>
    {
    public:
        using TEntityManager = typename GameTraits::TEntityManager;
        using TSystem = sfme::ecs::PreUpdateSystem<Event<GameTraits>>;
    public:
        Event(sfme::mediator::EventManager &evtMgr,  TEntityManager &ettMgr, sf::RenderWindow &win) noexcept :
            TSystem::System(evtMgr),
            _ettMgr(ettMgr),
            _win(win)
        {
        }

    public:
        //! Reflection
        reflect_class(Event)

        static constexpr auto reflectedFunctions() noexcept
        {
            return meta::makeMap();
        }

        static constexpr auto reflectedMembers() noexcept
        {
            return meta::makeMap();
        }

    public:
        //! Override
        void update() noexcept override
        {
            sf::Event evt;
            while (_win.pollEvent(evt)) {
                //ImGui::SFML::ProcessEvent(evt);
                switch (evt.type) {
                    case sf::Event::Closed:
                        this->_evtMgr.template emit<sfme::mediator::evt::GameShutdown>();
                        break;
                    case sf::Event::Resized:
                        break;
                    case sf::Event::LostFocus:
                        break;
                    case sf::Event::GainedFocus:
                        break;
                    case sf::Event::TextEntered:
                        break;
                    case sf::Event::KeyPressed:
                        this->_evtMgr.template emit<sfme::mediator::evt::KeyPressed>(
                            static_cast<sfme::input::keyboard::Key::EnumType>(evt.key.code));
                        break;
                    case sf::Event::KeyReleased:
                        this->_evtMgr.template emit<sfme::mediator::evt::KeyRelease>(
                            static_cast<sfme::input::keyboard::Key::EnumType>(evt.key.code));
                        break;
                    case sf::Event::MouseWheelMoved:
                        break;
                    case sf::Event::MouseWheelScrolled:
                        break;
                    case sf::Event::MouseButtonPressed:
                        break;
                    case sf::Event::MouseButtonReleased:
                        break;
                    case sf::Event::MouseMoved:
                        break;
                    case sf::Event::MouseEntered:
                        break;
                    case sf::Event::MouseLeft:
                        break;
                    case sf::Event::JoystickButtonPressed:
                        break;
                    case sf::Event::JoystickButtonReleased:
                        break;
                    case sf::Event::JoystickMoved:
                        break;
                    case sf::Event::JoystickConnected:
                        break;
                    case sf::Event::JoystickDisconnected:
                        break;
                    case sf::Event::TouchBegan:
                        break;
                    case sf::Event::TouchMoved:
                        break;
                    case sf::Event::TouchEnded:
                        break;
                    case sf::Event::SensorChanged:
                        break;
                    case sf::Event::Count:
                        break;
                }
            }
        //    ImGui::SFML::Update(_win, sf::seconds(1.f));
        }

    private:
        TEntityManager &_ettMgr;
        sf::RenderWindow &_win;
    };
}