#pragma once

#include <bitset>

namespace ElysionEngine
{
    class Component;

    using ComponentID = std::size_t;
    using Group = std::size_t;

    constexpr std::size_t max_components{ 32 };
    using ComponentBitset = std::bitset<max_components>;
    using ComponentArray = std::array<Component*, max_components>;

    constexpr std::size_t max_groups{ 32 };
    using GroupBitset = std::bitset<max_groups>;

    namespace Internal
    {
        inline ComponentID get_unique_component_id() noexcept
        {
            static ComponentID last_id{ 0u };
            return last_id++;
        }
    }

    template <typename T>
    inline ComponentID get_component_type_id() noexcept
    {
        static_assert(std::is_base_of<Component, T>::value,
            "T must inherit from Component");

        static ComponentID type_id{ Internal::get_unique_component_id() };
        return type_id;
    }
}
