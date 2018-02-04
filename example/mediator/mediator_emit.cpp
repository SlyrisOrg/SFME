//
// Created by milerius on 04/02/18.
//

#include <SFME/mediator/mediator.hpp>

//! User Event with non empty constructor
struct InputEvent : sfme::mediator::BaseEvent
{
    InputEvent(char _keycode) noexcept : keycode(_keycode)
    {
    }

    char keycode;
};

//! User Event default constructible.
struct ShutdownEvent : sfme::mediator::BaseEvent
{
};

int main()
{
    sfme::mediator::EventManager evtMgr;
    evtMgr.emit<InputEvent>('a');
    evtMgr.emit<ShutdownEvent>();
    return 0;
}