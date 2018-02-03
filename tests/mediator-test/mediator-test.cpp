
#include <gtest/gtest.h>
#include <SFME/mediator/mediator.hpp>

struct FooEvents : sfme::mediator::InsideEvents
{
    FooEvents()
    {
        showEvents("FooEvents");
    }

    std::string str{"Good"};
};

class Foo : public sfme::mediator::Receiver<Foo>
{
public:
    Foo(sfme::mediator::EventManager& evtMgr) : _evtMgr(evtMgr)
    {
        _evtMgr.subscribe<FooEvents>(*this);
    }

public:
    void receive([[maybe_unused]] const FooEvents& evt) noexcept
    {
        using namespace std::string_literals;
        ASSERT_EQ("Good"s, evt.str);
    }
private:
    sfme::mediator::EventManager& _evtMgr;
};

class NotRegister : public sfme::mediator::Receiver<NotRegister>
{

};

TEST(Mediator, Subscribe)
{
    sfme::mediator::EventManager manager;
    Foo subjectFoo(manager);
    NotRegister subjectBar;
    ASSERT_FALSE(manager.isRegister(subjectBar));
    ASSERT_TRUE(manager.isRegister(subjectFoo));
}

TEST(Mediator, Emit)
{
    sfme::mediator::EventManager manager;
    Foo subjectFoo(manager);
    //testing::internal::CaptureStderr();
    manager.emit<FooEvents>();
    //ASSERT_EQ(1, 1);
}