#pragma once

#include "ECSDefines.hpp"

#include <array>
#include <memory>
#include <vector>

namespace ElysionEngine
{
    class Entity;

    class EntityManager
    {
    public:
        void update(float dt);
        void draw();
        
        void add_to_group(Entity* entity, Group group);

        std::vector<Entity*>& get_entities_by_group(Group group);

        void refresh();

        Entity& add_entity();

    private:
        std::vector<std::unique_ptr<Entity>> m_entities{};
        std::array<std::vector<Entity*>, max_groups> m_groupedEntities{};
    };
}
