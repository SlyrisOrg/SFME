//
// Created by Doom on 2/17/2018.
// Maintained by Roman Sztergbaum
//

#include <gtest/gtest.h>
#include <core/meta/List.hpp>
#include <SFME/ecs/entity_manager.hpp>

struct Box
{
	reflect_class(Box);
    Box(unsigned int x, unsigned int y, unsigned int width, unsigned int height) noexcept :
        x(x), y(y), width(width), height(height)
    {
    }

    unsigned int x;
    unsigned int y;
    unsigned int width;
    unsigned int height;
};

struct Lol
{
	reflect_class(Lol);
    int i{2};
    int j{3};
};

struct Lul
{
	reflect_class(Lul);
};

using Components = meta::TypeList<Box, Lol, Lul>;

using EntityManagerTest = sfme::ecs::EntityManager<Components>;
using EntityTest = EntityManagerTest::Entity;

TEST(ECS, EntityManager)
{
    EntityManagerTest em;
    EntityTest::ID id = em.createEntity();

    ASSERT_FALSE(em[id].hasComponent<Box>());
    ASSERT_FALSE(em[id].hasComponent<Lol>());
    ASSERT_FALSE(em[id].hasComponent<Lul>());

    em[id].addComponent<Box>(1, 2, 3, 4);
    ASSERT_TRUE(em[id].hasComponent<Box>());
    Box &box = em[id].getComponent<Box>();
    ASSERT_EQ(box.x, 1u);
    ASSERT_EQ(box.y, 2u);
    ASSERT_EQ(box.width, 3u);
    ASSERT_EQ(box.height, 4u);

    em[id].addComponent<Lol>();
    ASSERT_TRUE(em[id].hasComponent<Box>());
    Box &box2 = em[id].getComponent<Box>();
    ASSERT_EQ(box2.x, 1u);
    ASSERT_EQ(box2.y, 2u);
    ASSERT_EQ(box2.width, 3u);
    ASSERT_EQ(box2.height, 4u);
    ASSERT_TRUE(em[id].hasComponent<Lol>());
    Lol &lol = em[id].getComponent<Lol>();
    ASSERT_EQ(lol.i, 2);
    ASSERT_EQ(lol.j, 3);
	ASSERT_TRUE(em[id].hasComponents("Box", "Lol"));
	ASSERT_FALSE(em[id].hasComponents("Box", "Lol", "Lul"));

    em[id].removeComponent<Lol>();
    ASSERT_FALSE(em[id].hasComponent<Lol>());
    ASSERT_TRUE(em[id].hasComponent<Box>());
    Box &box3 = em[id].getComponent<Box>();
    ASSERT_EQ(box3.x, 1u);
    ASSERT_EQ(box3.y, 2u);
    ASSERT_EQ(box3.width, 3u);
    ASSERT_EQ(box3.height, 4u);
	ASSERT_TRUE(em[id].hasComponents("Box"));
	ASSERT_FALSE(em[id].hasComponents("Lol"));
}

TEST(ECS, SimpleForEach)
{
    EntityManagerTest em;

    for (size_t i = 0; i < 10; ++i) {
        auto id = em.createEntity();
        em[id].addComponent<Lol>();
    }
    size_t nbMatched = 0;
    em.for_each<Lol>([&nbMatched](auto &) {
        nbMatched += 1;
    });
    ASSERT_EQ(nbMatched, 10u);

    nbMatched = 0;
    em.for_each<Box>([&nbMatched](auto &) {
        nbMatched += 1;
    });
    ASSERT_EQ(nbMatched, 0u);
}

TEST(ECS, MultipleForEach)
{
    EntityManagerTest em;

    for (size_t i = 0; i < 10; ++i) {
        auto id = em.createEntity();
        em[id].addComponent<Lol>();
        em[id].addComponent<Box>(1, 2, 3, 4);
    }
    size_t nbMatched = 0;
    em.for_each<Lol, Box>([&nbMatched](auto &) {
        nbMatched += 1;
    });
    ASSERT_EQ(nbMatched, 10u);

    nbMatched = 0;
    em.for_each<Box, Lul>([&nbMatched](auto &) {
        nbMatched += 1;
    });
    ASSERT_EQ(nbMatched, 0u);
}

TEST(ECS, Sweeping)
{
    EntityManagerTest em;

    for (size_t i = 0; i < 10; ++i) {
        auto id = em.createEntity();
        if (i % 2)
            em[id].addComponent<Lol>();
        em[id].addComponent<Lul>();
    }

    em.for_each<Lol>([](auto &et) {
        et.mark();
    });
    em.sweepEntities();
    ASSERT_EQ(em.nbEntities(), 5u);
}

//Tiny std::allocator-conformant allocator :D
template <typename T>
struct CustomAllocator : std::allocator<T>
{
};

using CustomAllocEntityMgr = sfme::ecs::EntityManager<Components, CustomAllocator>;
using CAEntity = CustomAllocEntityMgr::Entity;

TEST(ECS, CustomAllocator)
{
    CustomAllocEntityMgr em;
    CAEntity::ID id = em.createEntity();

    ASSERT_FALSE(em[id].hasComponent<Box>());
    ASSERT_FALSE(em[id].hasComponent<Lol>());
    ASSERT_FALSE(em[id].hasComponent<Lul>());

    em[id].addComponent<Box>(1, 2, 3, 4);
    ASSERT_TRUE(em[id].hasComponent<Box>());
    Box &box = em[id].getComponent<Box>();
    ASSERT_EQ(box.x, 1u);
    ASSERT_EQ(box.y, 2u);
    ASSERT_EQ(box.width, 3u);
    ASSERT_EQ(box.height, 4u);

    em[id].addComponent<Lol>();
    ASSERT_TRUE(em[id].hasComponent<Box>());
    Box &box2 = em[id].getComponent<Box>();
    ASSERT_EQ(box2.x, 1u);
    ASSERT_EQ(box2.y, 2u);
    ASSERT_EQ(box2.width, 3u);
    ASSERT_EQ(box2.height, 4u);
    ASSERT_TRUE(em[id].hasComponent<Lol>());
    Lol &lol = em[id].getComponent<Lol>();
    ASSERT_EQ(lol.i, 2);
    ASSERT_EQ(lol.j, 3);

    em[id].removeComponent<Lol>();
    ASSERT_FALSE(em[id].hasComponent<Lol>());
    ASSERT_TRUE(em[id].hasComponent<Box>());
    Box &box3 = em[id].getComponent<Box>();
    ASSERT_EQ(box3.x, 1u);
    ASSERT_EQ(box3.y, 2u);
    ASSERT_EQ(box3.width, 3u);
    ASSERT_EQ(box3.height, 4u);
}

TEST(ECS, StructuredBinding)
{
    EntityManagerTest em;
    EntityTest::ID id = em.createEntity();

    em[id].addComponent<Box>(1, 2, 3, 4);
    em[id].addComponent<Lol>();
    auto[box, lol] = em[id].getComponents<Box, Lol>();
    box.x = 200;
    ASSERT_EQ(em[id].getComponent<Box>().x, 200);
    ASSERT_EQ(&lol, &em[id].getComponent<Lol>());
}