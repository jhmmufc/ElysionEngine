#pragma once

#include <cstdint>
#include "Maths.hpp"
#include <ostream>

namespace ElysionEngine
{
    namespace Maths
    {
        template<class T>
        struct tVector4
        {
            T x, y, z, w;

            constexpr static T epsilon = std::numeric_limits<T>::epsilon();

            constexpr tVector4() noexcept
                = default;

            ~tVector4() noexcept
                = default;

            constexpr tVector4(const T value) noexcept
                : x(value), y(value), z(value), w(value)
            {}

            constexpr tVector4(const T x, const T y, const T z, const T w) noexcept
                : x(x), y(y), z(z), w(w)
            {}

            constexpr tVector4(const tVector4& rhs) noexcept
                : tVector4(rhs.x, rhs.y, rhs.z, rhs.w)
            {}

            constexpr tVector4(tVector4&& rhs) noexcept
                : tVector4(rhs.x, rhs.y, rhs.z, rhs.w)
            {}

            constexpr T& operator [](const int i) noexcept
            {
                Util::clamp(i, 0, 3);
                return ((&x)[i]);
            }

            constexpr tVector4& operator = (const tVector4& rhs) noexcept
            {
                x = rhs.x;
                y = rhs.y;
                z = rhs.z;
                w = rhs.w;
                return *this;
            }

            constexpr tVector4& operator = (tVector4&& rhs) noexcept
            {
                x = rhs.x;
                y = rhs.y;
                z = rhs.z;
                w = rhs.w;
                return *this;
            }

            constexpr tVector4& operator *= (const T s) noexcept
            {
                x *= s;
                y *= s;
                z *= s;
                w *= s;
                return *this;
            }

            constexpr tVector4& operator /= (const T s) noexcept
            {
                x /= s;
                y /= s;
                z /= s;
                w /= s;
                return *this;
            }

            constexpr T squared_magnitude() const noexcept
            {
                return tVector4::squared_magnitude(*this);
            }

            constexpr static T squared_magnitude(const tVector4& vector) noexcept
            {
                return vector.x * vector.x + vector.y * vector.y + vector.z * vector.z + vector.w * vector.w;
            }

            constexpr T magnitude() const noexcept
            {
                return Util::square_root(squared_magnitude());
            }

            constexpr tVector4 normalized() const noexcept
            {
                return *this / magnitude();
            }

            constexpr tVector4& operator += (const tVector4& v) noexcept
            {
                x += v.x;
                y += v.y;
                z += v.z;
                w += v.w;
                return *this;
            }

            constexpr tVector4& operator -= (const tVector4& v) noexcept
            {
                return *this += -v;
            }

            constexpr static T dot(const tVector4& lhs, const tVector4& rhs) noexcept
            {
                return (lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z + lhs.w * rhs.w);
            }

            constexpr static tVector4 zero() noexcept
            {
                return { 0 };
            }

            constexpr static tVector4 one() noexcept
            {
                return { 1 };
            }

            constexpr static tVector4 infinity() noexcept
            {
                return { std::numeric_limits<T>::infinity() };
            }

            constexpr static tVector4 negative_infinity() noexcept
            {
                return { -std::numeric_limits<T>::infinity() };
            }
        };

        template<class T>
        std::ostream& operator << (std::ostream& lhs, const tVector4<T>& rhs) noexcept
        {
            return lhs << "{ " << rhs.x << ", " << rhs.y << ", " << rhs.z << ", " << rhs.w << " }";
        }

        template<class T>
        constexpr tVector4<T> operator - (const tVector4<T>& rhs) noexcept
        {
            return { -rhs.x, -rhs.y, -rhs.z, -rhs.w };
        }

        template<class T>
        constexpr tVector4<T> operator + (const tVector4<T>& lhs, const tVector4<T>& rhs) noexcept
        {
            return { lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z, lhs.w + rhs.w };
        }

        template<class T>
        constexpr tVector4<T> operator - (const tVector4<T>& lhs, const tVector4<T>& rhs) noexcept
        {
            return lhs + (-rhs);
        }

        template<class T>
        constexpr tVector4<T> operator * (const tVector4<T>& lhs, const T rhs) noexcept
        {
            return { lhs.x * rhs, lhs.y * rhs, lhs.z * rhs, lhs.w * rhs };
        }

        template<class T>
        constexpr tVector4<T> operator / (const tVector4<T>& lhs, const T rhs) noexcept
        {
            return { lhs.x / rhs, lhs.y / rhs, lhs.z / rhs, lhs.w / rhs };
        }

        template<class T>
        constexpr bool operator == (const tVector4<T>& lhs, const tVector4<T>& rhs) noexcept
        {
            return tVector4<T>::squared_magnitude(lhs - rhs) < tVector4<T>::epsilon * tVector4<T>::epsilon;
        }

        template<>
        constexpr bool operator == (const tVector4<int32_t>& lhs, const tVector4<int32_t>& rhs) noexcept
        {
            return lhs.x == rhs.x && lhs.y == rhs.y && lhs.x == rhs.x && lhs.w == rhs.w;
        }

        template<class T>
        constexpr bool operator != (const tVector4<T>& lhs, const tVector4<T>& rhs) noexcept
        {
            return !(lhs == rhs);
        }
    }

    using Vector4 = Maths::tVector4<float>;
    using Vector4Double = Maths::tVector4<double>;
    using Vector4Int = Maths::tVector4<int32_t>;
}