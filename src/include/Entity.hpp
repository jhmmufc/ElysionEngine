#pragma once

#include "ECSDefines.hpp"

#include <cassert>
#include <array>
#include <bitset>
#include <memory>
#include <vector>

namespace ElysionEngine
{
    class Component;
    class EntityManager;

    class Entity
    {
    public:
        Entity(EntityManager& manager);

        void update(float dt);
        void draw();

        bool is_alive() const;
        void destroy();

        template<typename T>
        bool has_component() const
        {
            return m_component_bitset[get_component_type_id<T>()];
        }

        bool has_group(Group group) const noexcept
        {
            return m_group_bitset[group];
        }

        void add_group(Group group) noexcept;
        void remove_group(Group group) noexcept;

        template <typename T, typename... Args>
        T& add_component(Args&&... args)
        {
            assert(!has_component<T>());

            T* c(new T(std::forward<Args>(args)...));
            c->entity = this;
            std::unique_ptr<Component> uPtr{ c };
            m_components.emplace_back(std::move(uPtr));

            m_component_array[get_component_type_id<T>()] = c;
            m_component_bitset[get_component_type_id<T>()] = true;

            return *c;
        }

        template <typename T>
        T& get_component() const
        {
            assert(has_component<T>());
            auto ptr(m_component_array[get_component_type_id<T>()]);
            return *reinterpret_cast<T*>(ptr);
        }

    private:
        EntityManager& m_manager;

        bool m_alive{ true };
        std::vector<std::unique_ptr<Component>> m_components{};
        ComponentArray m_component_array{};
        ComponentBitset m_component_bitset{};
        GroupBitset m_group_bitset{};
    };
}
