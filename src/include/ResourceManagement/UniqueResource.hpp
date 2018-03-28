#pragma once

#include <algorithm>

namespace ElysionEngine
{
    template<typename TBehavior>
    class UniqueResource : TBehavior
    {
    public:
        using behaviour_type = TBehavior;
        using handle_type = typename behaviour_type::handle_type;
    private:
        handle_type m_handle;

        behaviour_type& as_behaviour() noexcept;
        const behaviour_type& as_behaviour() const noexcept;
    public:
        UniqueResource() noexcept;
        ~UniqueResource() noexcept;

        UniqueResource(const UniqueResource&) = delete;
        UniqueResource& operator=(const UniqueResource&) = delete;

        explicit UniqueResource(const handle_type& handle) noexcept;

        UniqueResource(UniqueResource&& rhs) noexcept;
        UniqueResource& operator=(UniqueResource&&) noexcept;

        handle_type release() noexcept;

        void reset() noexcept;
        void reset(const handle_type& handle) noexcept;

        void swap(UniqueResource& rhs) noexcept;

        handle_type get() const noexcept;

        explicit operator bool() const noexcept;

        friend bool operator==(const UniqueResource& lhs, const UniqueResource& rhs) noexcept;
        friend bool operator!=(const UniqueResource& lhs, const UniqueResource& rhs) noexcept;
        friend void swap(UniqueResource& lhs, UniqueResource& rhs) noexcept;
    };

    template <typename TBehavior>
    typename UniqueResource<TBehavior>::behaviour_type& UniqueResource<TBehavior>::as_behaviour() noexcept
    {
        return static_cast<behaviour_type&>(*this);
    }

    template <typename TBehavior>
    const typename UniqueResource<TBehavior>::behaviour_type& UniqueResource<TBehavior>::as_behaviour() const noexcept
    {
        return static_cast<const behaviour_type&>(*this);
    }

    template <typename TBehavior>
    UniqueResource<TBehavior>::UniqueResource() noexcept : m_handle{ as_behaviour().null_handle() }
    {
    }

    template <typename TBehavior>
    UniqueResource<TBehavior>::~UniqueResource() noexcept
    {
        reset();
    }

    template <typename TBehavior>
    UniqueResource<TBehavior>::UniqueResource(const handle_type& handle) noexcept
        : m_handle{ handle }
    {
    }

    template <typename TBehavior>
    UniqueResource<TBehavior>::UniqueResource(UniqueResource&& rhs) noexcept 
        : m_handle{ rhs.release() }
    {
    }

    template <typename TBehavior>
    UniqueResource<TBehavior>& UniqueResource<TBehavior>::operator=(UniqueResource&& rhs) noexcept
    {
        reset(rhs.release());
        return *this;
    }

    template <typename TBehavior>
    typename UniqueResource<TBehavior>::handle_type UniqueResource<TBehavior>::release() noexcept
    {
        auto temp_handle(m_handle);
        m_handle = as_behaviour().null_handle();
        return temp_handle;
    }

    template <typename TBehavior>
    void UniqueResource<TBehavior>::reset() noexcept
    {
        as_behaviour().deinit(m_handle);
        m_handle = as_behaviour().null_handle();
    }

    template <typename TBehavior>
    void UniqueResource<TBehavior>::reset(const handle_type& handle) noexcept
    {
        as_behaviour().deinit(m_handle);
        m_handle = handle;
    }

    template <typename TBehavior>
    void UniqueResource<TBehavior>::swap(UniqueResource& rhs) noexcept
    {
        using std::swap;
        swap(m_handle, rhs.m_handle);
    }

    template <typename TBehavior>
    typename UniqueResource<TBehavior>::handle_type UniqueResource<TBehavior>::get() const noexcept
    {
        return m_handle;
    }

    template <typename TBehavior>
    UniqueResource<TBehavior>::operator bool() const noexcept
    {
        return m_handle != as_behaviour().null_handle();
    }

    template <typename TBehavior>
    bool operator==(const UniqueResource<TBehavior>& lhs, const UniqueResource<TBehavior>& rhs) noexcept
    {
        return lhs._handle == rhs._handle;
    }

    template <typename TBehavior>
    bool operator!=(const UniqueResource<TBehavior>& lhs, const UniqueResource<TBehavior>& rhs) noexcept
    {
        return !(lhs == rhs);
    }

    template <typename TBehavior>
    void swap(UniqueResource<TBehavior>& lhs, UniqueResource<TBehavior>& rhs) noexcept
    {
        lhs.swap(rhs);
    }
}