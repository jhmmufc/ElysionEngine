#pragma once
#include <algorithm>

namespace ElysionEngine
{
    namespace Graphics
    {
        namespace Util
        {
            template <typename T>
            constexpr T clamp(const T& n, const T& lower, const T& upper) noexcept
            {
                return std::max(lower, std::min(n, upper));
            }

            template <typename T, typename D>
            constexpr T lerp(const T& start, const T& end, const D& percent)
            {
                return(start + percent * (end - start));
            }

            constexpr uint8_t normalised_float_to_byte(const float val) noexcept
            {
                return clamp(val, 0.0f, 1.0f) * 0xFF;
            }
        }
    }
}
