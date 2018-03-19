#include <Entity.hpp>
#include <Component.hpp>
#include <EntityManager.hpp>

namespace ElysionEngine
{
    Entity::Entity(EntityManager& manager) : m_manager(manager)
    {

    }

    void Entity::update(float dt)
    {
        for (auto& c : m_components)
        {
            c->update(dt);
        }
    }

    void Entity::draw()
    {
        for (auto& c : m_components)
        {
            c->draw();
        }
    }

    bool Entity::is_alive() const
    {
        return m_alive;
    }

    void Entity::destroy()
    {
        m_alive = false;
    }

    void Entity::add_group(Group group) noexcept
    {
        m_group_bitset[group] = true;
        m_manager.add_to_group(this, group);
    }

    void Entity::remove_group(Group group) noexcept
    {
        m_group_bitset[group] = false;
    }
}
