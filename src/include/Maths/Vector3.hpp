#pragma once

#include <cstdint>
#include "Maths.hpp"
#include <ostream>

namespace ElysionEngine
{
    namespace Maths
    {
        template<class T>
        struct tVector3
        {
            T x, y, z;

            constexpr static T epsilon = std::numeric_limits<T>::epsilon();

            constexpr tVector3() noexcept
                = default;

            ~tVector3() noexcept
                = default;

            constexpr tVector3(const T value) noexcept
                : x(value), y(value), z(value)
            {}

            constexpr tVector3(const T x, const T y, const T z) noexcept
                : x(x), y(y), z(z)
            {}

            constexpr tVector3(const tVector3& rhs) noexcept
                : tVector3(rhs.x, rhs.y, rhs.z)
            {}

            constexpr tVector3(tVector3&& rhs) noexcept
                : tVector3(rhs.x, rhs.y, rhs.z)
            {}

            constexpr T& operator [](const int i) noexcept
            {
                if (i <= 0) return x;
                if (i >= 2) return z;
                return ((&x)[i]);
            }

            constexpr tVector3& operator = (const tVector3& rhs) noexcept
            {
                x = rhs.x;
                y = rhs.y;
                z = rhs.z;
                return *this;
            }

            constexpr tVector3& operator = (tVector3&& rhs) noexcept
            {
                x = rhs.x;
                y = rhs.y;
                z = rhs.z;
                return *this;
            }

            constexpr tVector3& operator *= (const T s) noexcept
            {
                x *= s;
                y *= s;
                z *= s;
                return *this;
            }

            constexpr tVector3& operator /= (const T s) noexcept
            {
                x /= s;
                y /= s;
                z /= s;
                return *this;
            }

            constexpr T squared_magnitude() const noexcept
            {
                return tVector3::squared_magnitude(*this);
            }

            constexpr static T squared_magnitude(const tVector3& vector) noexcept
            {
                return vector.x * vector.x + vector.y * vector.y + vector.z * vector.z;
            }

            constexpr T magnitude() const noexcept
            {
                return Util::square_root(squared_magnitude());
            }

            constexpr tVector3 normalized() const noexcept
            {
                return *this / magnitude();
            }

            constexpr tVector3& operator += (const tVector3& v) noexcept
            {
                x += v.x;
                y += v.y;
                z += v.z;
                return *this;
            }

            constexpr tVector3& operator -= (const tVector3& v) noexcept
            {
                return *this += -v;
            }

            constexpr static T dot(const tVector3& lhs, const tVector3& rhs) noexcept
            {
                return (lhs.x * rhs.x + lhs.y * rhs.y * lhs.z * rhs.z);
            }

            constexpr static tVector3 cross(const tVector3& lhs, const tVector3& rhs) noexcept
            {
                return
                {
                    lhs.y * rhs.z - lhs.z * rhs.y,
                    lhs.z * rhs.x - lhs.x * rhs.z,
                    lhs.x * rhs.y - lhs.y * rhs.x
                };
            }

            constexpr static tVector3 zero() noexcept
            {
                return { 0 };
            }

            constexpr static tVector3 one() noexcept
            {
                return { 1 };
            }

            constexpr static tVector3 up() noexcept
            {
                return { 0, 1, 0 };
            }

            constexpr static tVector3 down() noexcept
            {
                return { 0, -1, 0 };
            }

            constexpr static tVector3 left() noexcept
            {
                return { -1, 0, 0 };
            }

            constexpr static tVector3 right() noexcept
            {
                return { 1, 0, 0 };
            }

            constexpr static tVector3 forward() noexcept
            {
                return { 0, 0, 1 };
            }

            constexpr static tVector3 backward() noexcept
            {
                return { 0, 0, -1 };
            }

            constexpr static tVector3 infinity() noexcept
            {
                return { std::numeric_limits<T>::infinity() };
            }

            constexpr static tVector3 negative_infinity() noexcept
            {
                return { -std::numeric_limits<T>::infinity() };
            }
        };

        template<class T>
        std::ostream& operator<<(std::ostream& lhs, const tVector3<T>& rhs) noexcept
        {
            return lhs << "{ " << rhs.x << ", " << rhs.y << ", " << rhs.z << " }";
        }

        template<class T>
        constexpr tVector3<T> operator - (const tVector3<T>& rhs) noexcept
        {
            return { -rhs.x, -rhs.y, -rhs.z };
        }

        template<class T>
        constexpr tVector3<T> operator + (const tVector3<T>& lhs, const tVector3<T>& rhs) noexcept
        {
            return { lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z };
        }

        template<class T>
        constexpr tVector3<T> operator - (const tVector3<T>& lhs, const tVector3<T>& rhs) noexcept
        {
            return lhs + (-rhs);
        }

        template<class T>
        constexpr tVector3<T> operator * (const tVector3<T>& lhs, const T rhs) noexcept
        {
            return { lhs.x * rhs, lhs.y * rhs, lhs.z * rhs };
        }

        template<class T>
        constexpr tVector3<T> operator / (const tVector3<T>& lhs, const T rhs) noexcept
        {
            return { lhs.x / rhs, lhs.y / rhs, lhs.z / rhs };
        }

        template<class T>
        constexpr bool operator == (const tVector3<T>& lhs, const tVector3<T>& rhs) noexcept
        {
            return tVector3<T>::squared_magnitude(lhs - rhs) < tVector3<T>::epsilon * tVector3<T>::epsilon;
        }

        template<>
        constexpr bool operator == (const tVector3<int32_t>& lhs, const tVector3<int32_t>& rhs) noexcept
        {
            return lhs.x == rhs.x && lhs.y == rhs.y && lhs.x == rhs.x;
        }

        template<class T>
        constexpr bool operator != (const tVector3<T>& lhs, const tVector3<T>& rhs) noexcept
        {
            return !(lhs == rhs);
        }
    }

    using Vector3 = Maths::tVector3<float>;
    using Vector3Double = Maths::tVector3<double>;
    using Vector3Int = Maths::tVector3<int32_t>;
}