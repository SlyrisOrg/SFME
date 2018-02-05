//
// Created by milerius on 05/02/18.
//

#include <SFME/mediator/mediator.hpp>

struct FooEvents : public sfme::mediator::BaseEvent
{

};

class FooSubject : public sfme::mediator::Receiver<FooSubject>
{
public:
    FooSubject(sfme::mediator::EventManager& evtMgr)
    {
        evtMgr.subscribe<FooEvents>(*this);
    }

    void receive([[maybe_unused]] const FooEvents& evt)
    {

    }
};

int main()
{
    sfme::mediator::EventManager evtMgr;
    FooSubject foo(evtMgr);
}