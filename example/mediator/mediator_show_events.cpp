//
// Created by milerius on 05/02/18.
//

#include <SFME/mediator/base_event.hpp>

struct FooEvents : public sfme::mediator::BaseEvent
{
    FooEvents()
    {
        showEvents("FooEvents");
    }
};

int main()
{
    FooEvents evt;
    return 0;
}