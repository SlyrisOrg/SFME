//
// Created by milerius on 07/02/18.
//

#include <iostream>
#include <SFME/mediator/mediator.hpp>

namespace example::evt
{
    struct KeyPressed : public sfme::mediator::BaseEvent
    {
        explicit KeyPressed(char _keycode) noexcept : keycode(_keycode)
        {
            showEvents("KeyPressed");
        }

        static std::string_view className() noexcept
        {
            return "KeyPressed";
        }

        char keycode;
    };

    struct StartGame : public sfme::mediator::BaseEvent
    {
        StartGame() noexcept
        {
            showEvents("StartGame");
        }

        static std::string_view className() noexcept
        {
            return "StartGame";
        }
    };
}

namespace example
{
    class GameScene : public sfme::mediator::Receiver<GameScene>
    {
    public:
        explicit GameScene(sfme::mediator::EventManager &evtMgr) noexcept : _evtMgr(evtMgr)
        {
            _evtMgr.subscribe<evt::KeyPressed>(*this);
            _evtMgr.subscribe<evt::StartGame>(*this);
        }

        void receive(const evt::KeyPressed &evt) noexcept
        {
            _log(logging::Info) << "keycode : " << evt.keycode << std::endl;
        }

        void receive([[maybe_unused]] const evt::StartGame &evt) noexcept
        {
            _log(logging::Info) << "Game will start now" << std::endl;
        }

    private:
        sfme::mediator::EventManager &_evtMgr;
        logging::Logger _log{"game-scene", logging::Debug};
    };

    class PauseScene : public sfme::mediator::Receiver<PauseScene>
    {
    public:
        explicit PauseScene(sfme::mediator::EventManager &evtMgr) noexcept : _evtMgr(evtMgr)
        {
            _evtMgr.subscribe<evt::KeyPressed>(*this);
        }

        void receive(const evt::KeyPressed &evt) noexcept
        {
            _log(logging::Info) << "keycode : " << evt.keycode << std::endl;
        }

    private:
        sfme::mediator::EventManager &_evtMgr;
        logging::Logger _log{"pause-scene", logging::Debug};
    };

    class HandleEveryEvents : public sfme::mediator::Receiver<HandleEveryEvents>
    {
    public:
        explicit HandleEveryEvents(sfme::mediator::EventManager &evtMgr) noexcept : _evtMgr(evtMgr)
        {
            _evtMgr.subscribe<evt::KeyPressed>(*this);
            _evtMgr.subscribe<evt::StartGame>(*this);
        }

        template <typename EventType>
        void receive([[maybe_unused]] const EventType &evt) noexcept
        {
            _log(logging::Info) << "Handle event: " << EventType::className() << std::endl;
        }

    private:
        sfme::mediator::EventManager &_evtMgr;
        logging::Logger _log{"handle-every-events", logging::Debug};
    };
}

int main()
{
    sfme::mediator::EventManager evtMgr;

    //! Example fake scenes.
    example::GameScene scene(evtMgr);
    example::PauseScene pauseScene(evtMgr);

    //! Handle every events
    example::HandleEveryEvents handleEveryEvents(evtMgr);

    //! Two Subscriber
    evtMgr.emit<example::evt::KeyPressed>('a');

    //! One Subscriber
    evtMgr.emit<example::evt::StartGame>();
    return 0;
}
