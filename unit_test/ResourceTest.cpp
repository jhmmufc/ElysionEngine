#include <catch/catch.hpp>
#include <ResourceManagement/UniqueResource.hpp>

int resource_count = 0;

namespace Test
{
    template<typename T>
    auto free_store_new(T* ptr)
    {
        return ptr;
    }

    template<typename T>
    void free_store_delete(T* ptr)
    {
        delete ptr;
    }

    template<typename T>
    struct free_store_b
    {
        using handle_type = T*;

        handle_type null_handle()
        {
            return nullptr;
        }

        handle_type init(T* ptr)
        {
            return free_store_new(ptr);
        }

        void deinit(const handle_type& handle)
        {
            free_store_delete(handle);
        }
    };
}

struct Resource
{
    Resource() { ++resource_count; }
    ~Resource() { --resource_count; };
};

TEST_CASE("Test unique resource")
{
    {
        using B = Test::free_store_b<Resource>;
        using R = ElysionEngine::UniqueResource<B>;
        
        // Initialise owner
        R r{ B{}.init(new Resource) };

        REQUIRE(resource_count == 1);

        // Change owner
        auto r1(std::move(r));

        REQUIRE(resource_count == 1);

        // Delete when scopes out
    }

    REQUIRE(resource_count == 0);
}