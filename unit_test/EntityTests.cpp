#include <catch.hpp>
#include "Component.hpp"
#include "Entity.hpp"
#include "EntityManager.hpp"

template<typename T, typename... Args>
auto make_component(Args&&... args)
{
    return std::make_unique<T>(std::forward<Args>(args)...);
}

class TestComponent : public ElysionEngine::Component
{
    
};

TEST_CASE("Create an component")
{
    auto testComponent = make_component<TestComponent>();

    REQUIRE(testComponent != nullptr);
    REQUIRE_NOTHROW(testComponent->update(1.0f));
    REQUIRE_NOTHROW(testComponent->draw());
}

TEST_CASE("Create an entity")
{
    ElysionEngine::EntityManager manager{ };

    ElysionEngine::Entity entity{ manager };

    REQUIRE(entity.is_alive());

    entity.destroy();

    REQUIRE_FALSE(entity.is_alive());

    entity.add_component<TestComponent>();

    REQUIRE(entity.has_component<TestComponent>());

    entity.add_group(10);

    REQUIRE(entity.has_group(10));
}

TEST_CASE("Test EntityManager")
{
    ElysionEngine::EntityManager manager{};

    auto& entity = manager.add_entity();

    REQUIRE(entity.is_alive());

    manager.refresh();

    REQUIRE(entity.is_alive());

    entity.add_group(10);

    auto& entities = manager.get_entities_by_group(10);

    REQUIRE(entities.size() == 1);

    entity.destroy();

    manager.refresh();

    REQUIRE(entities.empty());
}