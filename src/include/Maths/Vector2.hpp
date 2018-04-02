#pragma once

#include <cstdint>
#include "Maths.hpp"
#include <ostream>

namespace ElysionEngine
{
    namespace Maths
    {
        template<class T>
        struct tVector2
        {
            T x, y;

            constexpr static T epsilon = std::numeric_limits<T>::epsilon();

            constexpr tVector2() noexcept
                = default;

            ~tVector2() noexcept
                = default;

            constexpr tVector2(const T value) noexcept
                : x(value), y(value)
            {}

            constexpr tVector2(const T x, const T y) noexcept
                : x(x), y(y)
            {}

            constexpr tVector2(const tVector2& rhs) noexcept
                : tVector2(rhs.x, rhs.y)
            {}

            constexpr tVector2(tVector2&& rhs) noexcept
                : tVector2(rhs.x, rhs.y)
            {}

            constexpr T& operator [](const int i) noexcept
            {
                Util::clamp(i, 0, 1);
                return ((&x)[i]);
            }

            constexpr tVector2& operator = (const tVector2& rhs) noexcept
            {
                x = rhs.x;
                y = rhs.y;
                return *this;
            }

            constexpr tVector2& operator = (tVector2&& rhs) noexcept
            {
                x = rhs.x;
                y = rhs.y;
                return *this;
            }

            constexpr tVector2& operator *= (const T s) noexcept
            {
                x *= s;
                y *= s;
                return *this;
            }

            constexpr tVector2& operator /= (const T s) noexcept
            {
                x /= s;
                y /= s;
                return *this;
            }

            constexpr T squared_magnitude() const noexcept
            {
                return tVector2::squared_magnitude(*this);
            }

            constexpr static T squared_magnitude(const tVector2& vector) noexcept
            {
                return vector.x * vector.x + vector.y * vector.y;
            }

            constexpr T magnitude() const noexcept
            {
                return Util::square_root(squared_magnitude());
            }

            constexpr tVector2 normalized() const noexcept
            {
                return *this / magnitude();
            }

            constexpr tVector2& operator += (const tVector2& v) noexcept
            {
                x += v.x;
                y += v.y;
                return *this;
            }

            constexpr tVector2& operator -= (const tVector2& v) noexcept
            {
                return *this += -v;
            }

            constexpr static T dot(const tVector2& lhs, const tVector2& rhs) noexcept
            {
                return (lhs.x * rhs.x + lhs.y * rhs.y);
            }

            constexpr static tVector2 zero() noexcept
            {
                return { 0 };
            }

            constexpr static tVector2 one() noexcept
            {
                return { 1 };
            }

            constexpr static tVector2 up() noexcept
            {
                return { 0, 1 };
            }

            constexpr static tVector2 down() noexcept
            {
                return { 0, -1 };
            }

            constexpr static tVector2 left() noexcept
            {
                return { -1, 0 };
            }

            constexpr static tVector2 right() noexcept
            {
                return { 1, 0 };
            }

            constexpr static tVector2 infinity() noexcept
            {
                return { std::numeric_limits<T>::infinity() };
            }

            constexpr static tVector2 negative_infinity() noexcept
            {
                return { -std::numeric_limits<T>::infinity() };
            }
        };

        template<class T>
        std::ostream& operator<<(std::ostream& lhs, const tVector2<T>& rhs) noexcept
        {
            return lhs << "{ " << rhs.x << ", " << rhs.y << " }";
        }

        template<class T>
        constexpr tVector2<T> operator - (const tVector2<T>& rhs) noexcept
        {
            return { -rhs.x, -rhs.y };
        }

        template<class T>
        constexpr tVector2<T> operator + (const tVector2<T>& lhs, const tVector2<T>& rhs) noexcept
        {
            return { lhs.x + rhs.x, lhs.y + rhs.y };
        }

        template<class T>
        constexpr tVector2<T> operator - (const tVector2<T>& lhs, const tVector2<T>& rhs) noexcept
        {
            return lhs + (-rhs);
        }

        template<class T>
        constexpr tVector2<T> operator * (const tVector2<T>& lhs, const T rhs) noexcept
        {
            return { lhs.x * rhs, lhs.y * rhs };
        }

        template<class T>
        constexpr tVector2<T> operator / (const tVector2<T>& lhs, const T rhs) noexcept
        {
            return { lhs.x / rhs, lhs.y / rhs };
        }

        template<class T>
        constexpr bool operator == (const tVector2<T>& lhs, const tVector2<T>& rhs) noexcept
        {
            return tVector2<T>::squared_magnitude(lhs - rhs) < tVector2<T>::epsilon * tVector2<T>::epsilon;
        }

        template<>
        constexpr bool operator == (const tVector2<int32_t>& lhs, const tVector2<int32_t>& rhs) noexcept
        {
            return lhs.x == rhs.x && lhs.y == rhs.y;
        }

        template<class T>
        constexpr bool operator != (const tVector2<T>& lhs, const tVector2<T>& rhs) noexcept
        {
            return !(lhs == rhs);
        }
    }

    using Vector2 = Maths::tVector2<float>;
    using Vector2Double = Maths::tVector2<double>;
    using Vector2Int = Maths::tVector2<int32_t>;
}