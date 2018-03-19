#include "EntityManager.hpp"
#include "Component.hpp"
#include "Entity.hpp"

namespace ElysionEngine
{
    void EntityManager::update(float dt)
    {
        for(auto& e : m_entities)
        {
            e->update(dt);
        }
    }

    void EntityManager::draw()
    {
        for (auto& e : m_entities)
        {
            e->draw();
        }
    }

    void EntityManager::add_to_group(Entity* entity, Group group)
    {
        m_groupedEntities[group].emplace_back(entity);
    }

    std::vector<Entity*>& EntityManager::get_entities_by_group(Group group)
    {
        return m_groupedEntities[group];
    }

    void EntityManager::refresh()
    {
        for (auto i(0u); i < max_groups; ++i)
        {
            auto& v(m_groupedEntities[i]);

            v.erase(std::remove_if(std::begin(v), std::end(v),
                [i](Entity* mEntity)
                {
                    return !mEntity->is_alive() ||
                        !mEntity->has_group(i);
                }),
                std::end(v));
        }

        m_entities.erase(
            std::remove_if(std::begin(m_entities), std::end(m_entities),
                [](const std::unique_ptr<Entity>& entity)
                {
                    return !entity->is_alive();
                }),
            std::end(m_entities));
    }

    Entity& EntityManager::add_entity()
    {
        auto* e(new Entity(*this));
        std::unique_ptr<Entity> uPtr{ e };
        m_entities.emplace_back(std::move(uPtr));
        return *e;
    }
}
