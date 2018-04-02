#pragma once
#include <algorithm>

namespace ElysionEngine
{
    namespace Maths
    {
        namespace Util
        {
            template <typename T>
            constexpr T clamp(const T& n, const T& lower, const T& upper) noexcept
            {
                return std::max(lower, std::min(n, upper));
            }

            template <typename T, typename D>
            constexpr T lerp(const T& start, const T& end, const D& percent) noexcept
            {
                return(start + percent * (end - start));
            }

            constexpr uint8_t normalised_float_to_byte(const float val) noexcept
            {
                return static_cast<uint8_t>(clamp(val, 0.0f, 1.0f) * 0xFF);
            }

            /**
             * \brief Find the square root of \p x using a binary search.
             * \tparam T The type of \p x.
             * \param x The value you want to find the square root of.
             * \param lo The lower bound of the search.
             * \param hi The upper bound of the search.
             * \return The square root of \p x.
             */
            template <typename T>
            constexpr T square_root_helper(const T x, const T lo, const T hi) noexcept
            {
                if (lo == hi)
                {
                    return lo;
                }

                const T mid = (lo + hi + 1) / 2;

                if (x / mid < mid)
                {
                    return sqrt_helper<T>(x, lo, mid - 1);
                }
                return sqrt_helper(x, mid, hi);
            }

            /**
             * \brief Calculate the square root of \p x.
             * Based on "Compile integer Square Roots at compile-time in C++" by Baptiste Wicht.
             * Accessed 01/04/18
             * \tparam T The type of \p x.
             * \param x The value you want to find the square root of.
             * \return The square root of \p x.
             */
            template <typename T>
            constexpr T square_root(const T x) noexcept
            {
                return sqrt_helper(x, 0, x / 2 + 1);
            }
        }
    }
}