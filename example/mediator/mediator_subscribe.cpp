//
// Created by milerius on 04/02/18.
//

#include <SFME/mediator/mediator.hpp>

struct InputEvent : sfme::mediator::BaseEvent
{
};

class Example : public sfme::mediator::Receiver<Example>
{
public:
    Example(sfme::mediator::EventManager &evtMgr) noexcept
    {
        evtMgr.subscribe<InputEvent>(*this);
    }

    void receive([[maybe_unused]] const InputEvent& evt) noexcept
    {

    }
};

int main()
{
    sfme::mediator::EventManager evtMgr;
    Example ex(evtMgr);
    return 0;
}