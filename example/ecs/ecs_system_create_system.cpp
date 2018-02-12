#include "ecs_common_example.hpp"

template<typename Derived>
class Foo
{
public:
    static int getInt()
    {
        return 42;
    }
};

class Bar : public Foo<Bar>
{

};

template<typename T>
void showInt()
{
    std::cout << T::getInt() << std::endl;
}

int main()
{
    showInt<Bar>();
    /*sfme::mediator::EventManager evtMgr;
    sfme::example::EntityManager ettMgr;
    sfme::ecs::SystemManager<sfme::example::EntityManager> systemMgr{evtMgr, ettMgr};
    systemMgr.createSystem<sfme::example::system::Logic>();
    systemMgr.createSystem<sfme::example::system::WithUserData>(1, 2);*/
    return 0;
}