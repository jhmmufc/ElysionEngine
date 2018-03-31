#pragma once

#include "Util.hpp"

namespace ElysionEngine
{
    namespace Graphics
    {
        /**
         * \brief 32-bit colour class. Packs all data down to an unsigned 32 bit for space efficiency.
         */
        class Colour
        {
            uint32_t m_packed_colour; // ARGB Colour

        public:
            /**
             * \brief Construct a colour from an unsigned 32-bit integer value.
             * \param packed_color An ARGB unsigned integer value to create our colour from.
             */
            explicit constexpr Colour(const uint32_t packed_color) noexcept
                : m_packed_colour(packed_color)
            {}

            /**
             * \brief Construct a colour from 0.0f - 1.0f range floats.
             * \param r The red colour component.
             * \param g The green colour component.
             * \param b The blue colour component.
             */
            constexpr Colour(const float r, const float g, const float b) noexcept
                : Colour(r, g, b, 1.0f)
            {}

            /**
             * \brief Construct a colour from 0 - 255 range integers.
             * \param r The red colour component.
             * \param g The green colour component.
             * \param b The blue colour component.
             */
            constexpr Colour(const int r, const int g, const int b) noexcept
                : Colour(r, g, b, 255)
            {}

            /**
             * \brief Construct a colour from 0.0f - 1.0f range floats.
             * \param r The red colour component.
             * \param g The green colour component.
             * \param b The blue colour component.
             * \param a The alpha colour component.
             */
            constexpr Colour(const float r, const float g, const float b, const float a) noexcept
                : m_packed_colour(uint32_t(
                    Util::normalised_float_to_byte(a) << 24) |
                    Util::normalised_float_to_byte(r) << 16 |
                    Util::normalised_float_to_byte(g) << 8 |
                    Util::normalised_float_to_byte(b))
            {}

            /**
             * \brief Construct a colour from 0 - 255 range integers.
             * \param r The red colour component.
             * \param g The green colour component.
             * \param b The blue colour component.
             * \param a The alpha colour component.
             */
            constexpr Colour(const int r, const int g, const int b, const int a) noexcept
                : Colour(static_cast<uint8_t>(r), 
                         static_cast<uint8_t>(g), 
                         static_cast<uint8_t>(b), 
                         static_cast<uint8_t>(a))
            {}

            /**
             * \brief Construct a colour from bytes.
             * \param r The red colour component.
             * \param g The green colour component.
             * \param b The blue colour component.
             * \param a The alpha colour component.
             */
            constexpr Colour(const uint8_t r, const uint8_t g, const uint8_t b, const uint8_t a) noexcept
                : m_packed_colour(uint32_t(a << 24) | r << 16 | g << 8 | b)
            {}

            constexpr Colour() noexcept
                : m_packed_colour(0)
            {}

            ~Colour() noexcept = default;

            /**
             * \brief Construct a colour from another instance of Colour.
             * \param rhs The original instance you want to copy.
             */
            constexpr Colour(const Colour& rhs) noexcept
            = default;

            /**
             * \brief Construct a colour from another instance of Colour.
             * \param rhs The original instance you want to copy.
             */
            constexpr Colour(const Colour&& rhs) noexcept
                : m_packed_colour(rhs.m_packed_colour)
            {}

            /**
             * \brief Construct a colour through copy assignment.
             * \param rhs The original instance you want to copy.
             */
            constexpr Colour& operator = (const Colour& rhs) noexcept
            = default;

            /**
             * \brief Construct a colour through move assignment.
             * \param rhs The original instance you want to move.
             */
            constexpr Colour& operator = (Colour&& rhs) noexcept
            = default;

            /**
             * \brief Get the red colour component as a 0.0f - 1.0f range float.
             * \return The red colour component.
             */
            constexpr float r() const noexcept
            {
                const auto byte = m_packed_colour >> 16 & 0xFF;
                return static_cast<float>(byte) / 0xFF;
            }

            /**
             * \brief Get the green colour component as a 0.0f - 1.0f range float.
             * \return The green colour component.
             */
            constexpr float g() const noexcept
            {
                const auto byte = m_packed_colour >> 8 & 0xFF;
                return static_cast<float>(byte) / 0xFF;
            }

            /**
             * \brief Get the blue colour component as a 0.0f - 1.0f range float.
             * \return The blue colour component.
             */
            constexpr float b() const noexcept
            {
                const auto byte = m_packed_colour & 0xFF;
                return static_cast<float>(byte) / 0xFF;
            }

            /**
             * \brief Get the alpha colour component as a 0.0f - 1.0f range float.
             * \return The alpha colour component.
             */
            constexpr float a() const noexcept
            {
                const auto byte = m_packed_colour >> 24 & 0xFF;
                return static_cast<float>(byte) / 0xFF;
            }

            /**
             * \brief Multiply each colour component by a scalar value.
             * \param rhs The scalar value.
             * \return The resulting colour.
             */
            constexpr Colour operator * (const float rhs) const noexcept
            {
                return
                {
                    r() * rhs,
                    g() * rhs,
                    b() * rhs,
                    a() * rhs
                };
            }

            /**
             * \brief Divide each colour component by a scalar value.
             * \param rhs The scalar value.
             * \return The resulting colour.
             */
            constexpr Colour operator / (const float rhs) const noexcept
            {
                return *this * (1 / rhs);
            }

            /**
             * \brief Compare against another colour for equality.
             * \param rhs The second colour.
             * \return The result of the comparison.
             */
            constexpr bool operator == (const Colour& rhs) const noexcept
            {
                return m_packed_colour == rhs.m_packed_colour;
            }

            /**
             * \brief Compare against another colour for inequality.
             * \param rhs The second colour.
             * \return The result of the comparison.
             */
            constexpr bool operator != (const Colour& rhs) const noexcept
            {
                return !(*this == rhs);
            }

            static constexpr Colour lerp(const Colour& value1, const Colour& value2, float amount) noexcept
            {
                using namespace Util;
                return
                { 
                    normalised_float_to_byte(Util::lerp(value1.r(), value2.r(), amount)),
                    normalised_float_to_byte(Util::lerp(value1.g(), value2.g(), amount)),
                    normalised_float_to_byte(Util::lerp(value1.b(), value2.b(), amount)),
                    normalised_float_to_byte(Util::lerp(value1.a(), value2.a(), amount))
                };
            }

            /**
             * \brief Transparent Black
             * \return {R:0 G:0 B:0 A:0}
             */
            static constexpr Colour transparent_black() noexcept
            {
                return Colour(0);
            }

            /**
             * \brief Transparent White
             * \return{R:255 G:255 B:255 A:0}
             */
            static constexpr Colour transparent_white() noexcept
            {
                return Colour(0xffffff);
            }

            /**
             * \brief Alice Blue
             * \return {R:240 G:248 B:255 A:255}
             */
            static constexpr Colour alice_blue() noexcept
            {
                return Colour(0xfff0f8ff);
            }

            /**
             * \brief Antique White
             * \return {R:250 G:235 B:215 A:255}
             */
            static constexpr Colour antique_white() noexcept
            {
                return Colour(0xfffaebd7);
            }

            /**
             * \brief Aqua
             * \return {R:0 G:255 B:255 A:255}
             */
            static constexpr Colour aqua() noexcept
            {
                return Colour(0xff00ffff);
            }

            /**
             * \brief Aquamarine
             * \return {R:127 G:255 B:212 A:255}
             */
            static constexpr Colour aquamarine() noexcept
            {
                return Colour(0xff7fffd4);
            }

            /**
             * \brief Azure
             * \return {R:240 G:255 B:255 A:255}
             */
            static constexpr Colour azure() noexcept
            {
                return Colour(0xfff0ffff);
            }

            /**
             * \brief Beige
             * \return {R:245 G:245 B:220 A:255}
             */
            static constexpr Colour beige() noexcept
            {
                return Colour(0xfff5f5dc);
            }

            /**
             * \brief Bisque
             * \return {R:255 G:228 B:196 A:255}
             */
            static constexpr Colour bisque() noexcept
            {
                return Colour(0xffffe4c4);
            }

            /**
             * \brief Black
             * \return {R:0 G:0 B:0 A:255}
             */
            static constexpr Colour black() noexcept
            {
                return Colour(0xff000000);
            }

            /**
             * \brief Blanched Almond
             * \return {R:255 G:235 B:205 A:255}
             */
            static constexpr Colour blanched_almond() noexcept
            {
                return Colour(0xffffebcd);
            }

            /**
             * \brief Blue
             * \return {R:0 G:0 B:255 A:255}
             */
            static constexpr Colour blue() noexcept
            {
                return Colour(0xff0000ff);
            }

            /**
             * \brief Blue Violet
             * \return {R:138 G:43 B:226 A:255}
             */
            static constexpr Colour blue_violet() noexcept
            {
                return Colour(0xff8a2be2);
            }

            /**
             * \brief Brown
             * \return {R:165 G:42 B:42 A:255}
             */
            static constexpr Colour brown() noexcept
            {
                return Colour(0xffa52a2a);
            }

            /**
             * \brief Burly Wood
             * \return {R:222 G:184 B:135 A:255}
             */
            static constexpr Colour burly_wood() noexcept
            {
                return Colour(0xffdeb887);
            }

            /**
             * \brief CadetBlue
             * \return {R:95 G:158 B:160 A:255}
             */
            static constexpr Colour cadet_blue() noexcept
            {
                return Colour(0xff5f9ea0);
            }

            /**
             * \brief Chartreuse
             * \return {R:127 G:255 B:0 A:255}
             */
            static constexpr Colour chartreuse() noexcept
            {
                return Colour(0xff7fff00);
            }

            /**
             * \brief Chocolate
             * \return {R:210 G:105 B:30 A:255}
             */
            static constexpr Colour chocolate() noexcept
            {
                return Colour(0xffd2691e);
            }

            /**
             * \brief Coral
             * \return {R:255 G:127 B:80 A:255}
             */
            static constexpr Colour coral() noexcept
            {
                return Colour(0xffff7f50);
            }

            /**
             * \brief Cornflower Blue
             * \return {R:100 G:149 B:237 A:255}
             */
            static constexpr Colour cornflower_blue() noexcept
            {
                return Colour(0xff6495ed);
            }

            /**
             * \brief Cornsilk
             * \return {R:255 G:248 B:220 A:255}
             */
            static constexpr Colour cornsilk() noexcept
            {
                return Colour(0xfffff8dc);
            }

            /**
             * \brief Crimson
             * \return {R:220 G:20 B:60 A:255}
             */
            static constexpr Colour crimson() noexcept
            {
                return Colour(0xffdc143c);
            }

            /**
             * \brief Cyan
             * \return {R:0 G:255 B:255 A:255}
             */
            static constexpr Colour cyan() noexcept
            {
                return Colour(0xff00ffff);
            }

            /**
             * \brief Dark Blue
             * \return {R:0 G:0 B:139 A:255}
             */
            static constexpr Colour dark_blue() noexcept
            {
                return Colour(0xff00008b);
            }

            /**
             * \brief Dark Cyan
             * \return {R:0 G:139 B:139 A:255}
             */
            static constexpr Colour dark_cyan() noexcept
            {
                return Colour(0xff008b8b);
            }

            /**
             * \brief Dark Goldenrod
             * \return {R:184 G:134 B:11 A:255}
             */
            static constexpr Colour dark_goldenrod() noexcept
            {
                return Colour(0xffb8860b);
            }

            /**
             * \brief Dark Gray
             * \return {R:169 G:169 B:169 A:255}
             */
            static constexpr Colour dark_gray() noexcept
            {
                return Colour(0xffa9a9a9);
            }

            /**
             * \brief Dark Green
             * \return {R:0 G:100 B:0 A:255}
             */
            static constexpr Colour dark_green() noexcept
            {
                return Colour(0xff006400);
            }

            /**
             * \brief Dark Khaki
             * \return {R:189 G:183 B:107 A:255}
             */
            static constexpr Colour dark_khaki() noexcept
            {
                return Colour(0xffbdb76b);
            }

            /**
             * \brief Dark Magenta
             * \return {R:139 G:0 B:139 A:255}
             */
            static constexpr Colour dark_magenta() noexcept
            {
                return Colour(0xff8b008b);
            }

            /**
             * \brief Dark Olive Green
             * \return {R:85 G:107 B:47 A:255}
             */
            static constexpr Colour dark_olive_green() noexcept
            {
                return Colour(0xff556b2f);
            }

            /**
             * \brief Dark Orange
             * \return {R:255 G:140 B:0 A:255}
             */
            static constexpr Colour dark_orange() noexcept
            {
                return Colour(0xffff8c00);
            }

            /**
             * \brief Dark Orchid
             * \return {R:153 G:50 B:204 A:255}
             */
            static constexpr Colour dark_orchid() noexcept
            {
                return Colour(0xff9932cc);
            }

            /**
             * \brief Dark Red
             * \return {R:139 G:0 B:0 A:255}
             */
            static constexpr Colour dark_red() noexcept
            {
                return Colour(0xff8b0000);
            }

            /**
             * \brief Dark Salmon
             * \return {R:233 G:150 B:122 A:255}
             */
            static constexpr Colour dark_salmon() noexcept
            {
                return Colour(0xffe9967a);
            }

            /**
             * \brief Dark Sea Green
             * \return {R:143 G:188 B:139 A:255}
             */
            static constexpr Colour dark_sea_green() noexcept
            {
                return Colour(0xff8fbc8b);
            }

            /**
             * \brief Dark Slate Blue
             * \return {R:72 G:61 B:139 A:255}
             */
            static constexpr Colour dark_slate_blue() noexcept
            {
                return Colour(0xff483d8b);
            }

            /**
             * \brief Dark Slate Gray
             * \return {R:47 G:79 B:79 A:255}
             */
            static constexpr Colour dark_slate_gray() noexcept
            {
                return Colour(0xff2f4f4f);
            }

            /**
             * \brief Dark Turquoise
             * \return {R:0 G:206 B:209 A:255}
             */
            static constexpr Colour dark_turquoise() noexcept
            {
                return Colour(0xff00ced1);
            }

            /**
             * \brief Dark Violet
             * \return {R:148 G:0 B:211 A:255}
             */
            static constexpr Colour dark_violet() noexcept
            {
                return Colour(0xff9400d3);
            }

            /**
             * \brief Deep Pink
             * \return {R:255 G:20 B:147 A:255}
             */
            static constexpr Colour deep_pink() noexcept
            {
                return Colour(0xffff1493);
            }

            /**
             * \brief Deep Sky Blue
             * \return {R:0 G:191 B:255 A:255} 
             */
            static constexpr Colour deep_sky_blue() noexcept
            {
                return Colour(0xff00bfff);
            }

            /**
             * \brief Dim Gray
             * \return {R:105 G:105 B:105 A:255}
             */
            static constexpr Colour dim_gray()
            {
                return Colour(0xff696969);
            }

            /**
             * \brief Dodger Blue
             * \return {R:30 G:144 B:255 A:255}
             */
            static constexpr Colour dodger_blue() noexcept
            {
                return Colour(0xff1e90ff);
            }

            /**
             * \brief Firebrick
             * \return {R:178 G:34 B:34 A:255}
             */
            static constexpr Colour firebrick() noexcept
            {
                return Colour(0xffb22222);
            }

            /**
             * \brief Floral White
             * \return {R:255 G:250 B:240 A:255}
             */
            static constexpr Colour floral_white() noexcept
            {
                return Colour(0xfffffaf0);
            }

            /**
             * \brief Forest Green
             * \return {R:34 G:139 B:34 A:255}
             */
            static constexpr Colour forest_green() noexcept
            {
                return Colour(0xff228b22);
            }

            /**
             * \brief Fuchsia
             * \return {R:255 G:0 B:255 A:255}
             */
            static constexpr Colour fuchsia() noexcept
            {
                return Colour(0xffff00ff);
            }

            /**
             * \brief Gainsboro
             * \return {R:220 G:220 B:220 A:255}
             */
            static constexpr Colour gainsboro() noexcept
            {
                return Colour(0xffdcdcdc);
            }

            /**
             * \brief Ghost White
             * \return {R:248 G:248 B:255 A:255}
             */
            static constexpr Colour ghost_white() noexcept
            {
                return Colour(0xfff8f8ff);
            }

            /**
             * \brief Gold
             * \return {R:255 G:215 B:0 A:255}
             */
            static constexpr Colour gold() noexcept
            {
                return Colour(0xffffd700);
            }

            /**
             * \brief Goldenrod
             * \return {R:218 G:165 B:32 A:255}
             */
            static constexpr Colour goldenrod() noexcept
            {
                return Colour(0xffdaa520);
            }

            /**
             * \brief Gray
             * \return {R:128 G:128 B:128 A:255}
             */
            static constexpr Colour gray() noexcept
            {
                return Colour(0xff808080);
            }

            /**
             * \brief Green
             * \return {R:0 G:128 B:0 A:255}
             */
            static constexpr Colour green() noexcept
            {
                return Colour(0xff008000);
            }

            /**
             * \brief Green Yellow
             * \return {R:173 G:255 B:47 A:255}
             */
            static constexpr Colour green_yellow() noexcept
            {
                return Colour(0xffadff2f);
            }

            /**
             * \brief Honeydew
             * \return {R:240 G:255 B:240 A:255}
             */
            static constexpr Colour honeydew() noexcept
            {
                return Colour(0xfff0fff0);
            }

            /**
             * \brief Hot Pink
             * \return {R:255 G:105 B:180 A:255}
             */
            static constexpr Colour hot_pink() noexcept
            {
                return Colour(0xffff69b4);
            }

            /**
             * \brief Indian Red
             * \return {R:205 G:92 B:92 A:255}
             */
            static constexpr Colour indian_red() noexcept
            {
                return Colour(0xffcd5c5c);
            }

            /**
             * \brief Indigo
             * \return {R:75 G:0 B:130 A:255}
             */
            static constexpr Colour indigo() noexcept
            {
                return Colour(0xff4b0082);
            }

            /**
             * \brief Ivory
             * \return {R:255 G:255 B:240 A:255}
             */
            static constexpr Colour ivory() noexcept
            {
                return Colour(0xfffffff0);
            }

            /**
             * \brief Khaki
             * \return {R:240 G:230 B:140 A:255}
             */
            static constexpr Colour khaki() noexcept
            {
                return Colour(0xfff0e68c);
            }

            /**
             * \brief Lavender
             * \return {R:230 G:230 B:250 A:255}
             */
            static constexpr Colour lavender() noexcept
            {
                return Colour(0xffe6e6fa);
            }

            /**
             * \brief Lavender Blush
             * \return {R:255 G:240 B:245 A:255}
             */
            static constexpr Colour lavender_blush() noexcept
            {
                return Colour(0xfffff0f5);
            }

            /**
             * \brief Lawn Green
             * \return {R:124 G:252 B:0 A:255}
             */
            static constexpr Colour lawn_green() noexcept
            {
                return Colour(0xff7cfc00);
            }

            /**
             * \brief Lemon Chiffon
             * \return {R:255 G:250 B:205 A:255}
             */
            static constexpr Colour lemon_chiffon() noexcept
            {
                return Colour(0xfffffacd);
            }

            /**
             * \brief Light Blue
             * \return {R:173 G:216 B:230 A:255}
             */
            static constexpr Colour light_blue() noexcept
            {
                return Colour(0xffadd8e6);
            }

            /**
             * \brief Light Coral
             * \return {R:240 G:128 B:128 A:255}
             */
            static constexpr Colour light_coral() noexcept
            {
                return Colour(0xfff08080);
            }

            /**
             * \brief Light Cyan
             * \return {R:224 G:255 B:255 A:255}
             */
            static constexpr Colour light_cyan() noexcept
            {
                return Colour(0xffe0ffff);
            }

            /**
             * \brief Light Goldenrod Yellow
             * \return {R:250 G:250 B:210 A:255}
             */
            static constexpr Colour light_goldenrod_yellow() noexcept
            {
                return Colour(0xfffafad2);
            }

            /**
             * \brief Light Green
             * \return {R:144 G:238 B:144 A:255}
             */
            static constexpr Colour light_green() noexcept
            {
                return Colour(0xff90ee90);
            }

            /**
             * \brief Light Gray
             * \return {R:211 G:211 B:211 A:255}
             */
            static constexpr Colour light_gray() noexcept
            {
                return Colour(0xffd3d3d3);
            }

            /**
             * \brief Light Pink
             * \return {R:255 G:182 B:193 A:255}
             */
            static constexpr Colour light_pink() noexcept
            {
                return Colour(0xffffb6c1);
            }

            /**
             * \brief Light Salmon
             * \return {R:255 G:160 B:122 A:255}
             */
            static constexpr Colour light_salmon() noexcept
            {
                return Colour(0xffffa07a);
            }

            /**
             * \brief Light Sea Green
             * \return {R:32 G:178 B:170 A:255}
             */
            static constexpr Colour light_sea_green() noexcept
            {
                return Colour(0xff20b2aa);
            }

            /**
             * \brief Light Sky Blue
             * \return {R:135 G:206 B:250 A:255}
             */
            static constexpr Colour light_sky_blue() noexcept
            {
                return Colour(0xff87cefa);
            }

            /**
             * \brief Light Slate Gray
             * \return {R:119 G:136 B:153 A:255}
             */
            static constexpr Colour light_slate_gray() noexcept
            {
                return Colour(0xff778899);
            }

            /**
             * \brief Light Steel Blue
             * \return {R:176 G:196 B:222 A:255}
             */
            static constexpr Colour light_steel_blue() noexcept
            {
                return Colour(0xffb0c4de);
            }

            /**
             * \brief Light Yellow
             * \return {R:255 G:255 B:224 A:255}
             */
            static constexpr Colour light_yellow() noexcept
            {
                return Colour(0xffffffe0);
            }

            /**
             * \brief Lime
             * \return {R:0 G:255 B:0 A:255}
             */
            static constexpr Colour lime() noexcept
            {
                return Colour(0xff00ff00);
            }

            /**
             * \brief Lime Green
             * \return {R:50 G:205 B:50 A:255}
             */
            static constexpr Colour lime_green() noexcept
            {
                return Colour(0xff32cd32);
            }

            /**
             * \brief Linen
             * \return {R:250 G:240 B:230 A:255}
             */
            static constexpr Colour linen() noexcept
            {
                return Colour(0xfffaf0e6);
            }

            /**
             * \brief Magenta
             * \return {R:255 G:0 B:255 A:255}
             */
            static constexpr Colour magenta() noexcept
            {
                return Colour(0xffff00ff);
            }

            /**
             * \brief Maroon
             * \return {R:128 G:0 B:0 A:255}
             */
            static constexpr Colour maroon() noexcept
            {
                return Colour(0xff800000);
            }

            /**
             * \brief Medium Aquamarine
             * \return {R:102 G:205 B:170 A:255}
             */
            static constexpr Colour medium_aquamarine() noexcept
            {
                return Colour(0xff66cdaa);
            }

            /**
             * \brief Medium Blue
             * \return {R:0 G:0 B:205 A:255}
             */
            static constexpr Colour medium_blue() noexcept
            {
                return Colour(0xff0000cd);
            }

            /**
             * \brief Medium Orchid
             * \return {R:186 G:85 B:211 A:255}
             */
            static constexpr Colour medium_orchid() noexcept
            {
                return Colour(0xffba55d3);
            }

            /**
             * \brief Medium Purple
             * \return {R:147 G:112 B:219 A:255}
             */
            static constexpr Colour medium_purple() noexcept
            {
                return Colour(0xff9370db);
            }

            /**
             * \brief Medium Sea Green
             * \return {R:60 G:179 B:113 A:255}
             */
            static constexpr Colour medium_sea_green() noexcept
            {
                return Colour(0xff3cb371);
            }

            /**
             * \brief Medium Slate Blue
             * \return {R:123 G:104 B:238 A:255}
             */
            static constexpr Colour medium_slate_blue() noexcept
            {
                return Colour(0xff7b68ee);
            }

            /**
             * \brief Medium Spring Green
             * \return {R:0 G:250 B:154 A:255}
             */
            static constexpr Colour medium_spring_green() noexcept
            {
                return Colour(0xff00fa9a);
            }

            /**
             * \brief Medium Turquoise
             * \return {R:72 G:209 B:204 A:255}
             */
            static constexpr Colour medium_turquoise() noexcept
            {
                return Colour(0xff48d1cc);
            }

            /**
             * \brief Medium Violet Red
             * \return {R:199 G:21 B:133 A:255}
             */
            static constexpr Colour medium_violet_red() noexcept
            {
                return Colour(0xffc71585);
            }

            /**
             * \brief Midnight Blue
             * \return {R:25 G:25 B:112 A:255}
             */
            static constexpr Colour midnight_blue() noexcept
            {
                return Colour(0xff191970);
            }

            /**
             * \brief Mint Cream
             * \return {R:245 G:255 B:250 A:255}
             */
            static constexpr Colour mint_cream() noexcept
            {
                return Colour(0xfff5fffa);
            }

            /**
             * \brief Misty Rose
             * \return {R:255 G:228 B:225 A:255}
             */
            static constexpr Colour misty_rose() noexcept
            {
                return Colour(0xffffe4e1);
            }

            /**
             * \brief Moccasin
             * \return {R:255 G:228 B:181 A:255}
             */
            static constexpr Colour moccasin() noexcept
            {
                return Colour(0xffffe4b5);
            }

            /**
             * \brief Navajo White
             * \return {R:255 G:222 B:173 A:255}
             */
            static constexpr Colour navajo_white() noexcept
            {
                return Colour(0xffffdead);
            }

            /**
             * \brief Navy
             * \return {R:0 G:0 B:128 A:255}
             */
            static constexpr Colour navy() noexcept
            {
                return Colour(0xff000080);
            }

            /**
             * \brief Old Lace
             * \return {R:253 G:245 B:230 A:255}
             */
            static constexpr Colour old_lace() noexcept
            {
                return Colour(0xfffdf5e6);
            }

            /**
             * \brief Olive
             * \return {R:128 G:128 B:0 A:255}
             */
            static constexpr Colour olive() noexcept
            {
                return Colour(0xff808000);
            }

            /**
             * \brief Olive Drab
             * \return {R:107 G:142 B:35 A:255}
             */
            static constexpr Colour olive_drab() noexcept
            {
                return Colour(0xff6b8e23);
            }

            /**
             * \brief Orange
             * \return {R:255 G:165 B:0 A:255}
             */
            static constexpr Colour orange() noexcept
            {
                return Colour(0xffffa500);
            }

            /**
             * \brief Orange Red
             * \return {R:255 G:69 B:0 A:255}
             */
            static constexpr Colour orange_red() noexcept
            {
                return Colour(0xffff4500);
            }

            /**
             * \brief Orchid
             * \return {R:218 G:112 B:214 A:255}
             */
            static constexpr Colour orchid() noexcept
            {
                return Colour(0xffda70d6);
            }

            /**
             * \brief Pale Goldenrod
             * \return {R:238 G:232 B:170 A:255}
             */
            static constexpr Colour pale_goldenrod() noexcept
            {
                return Colour(0xffeee8aa);
            }

            /**
             * \brief Pale Green
             * \return {R:152 G:251 B:152 A:255}
             */
            static constexpr Colour pale_green() noexcept
            {
                return Colour(0xff98fb98);
            }

            /**
             * \brief Pale Turquoise
             * \return {R:175 G:238 B:238 A:255}
             */
            static constexpr Colour pale_turquoise() noexcept
            {
                return Colour(0xffafeeee);
            }

            /**
             * \brief Pale Violet Red
             * \return {R:219 G:112 B:147 A:255}
             */
            static constexpr Colour pale_violet_red() noexcept
            {
                return Colour(0xffdb7093);
            }

            /**
             * \brief Papaya Whip
             * \return {R:255 G:239 B:213 A:255}
             */
            static constexpr Colour papaya_whip() noexcept
            {
                return Colour(0xffffefd5);
            }

            /**
             * \brief Peach Puff
             * \return {R:255 G:218 B:185 A:255}
             */
            static constexpr Colour peach_puff() noexcept
            {
                return Colour(0xffffdab9);
            }

            /**
             * \brief Peru
             * \return {R:205 G:133 B:63 A:255}
             */
            static constexpr Colour peru() noexcept
            {
                return Colour(0xff87cefa);
            }

            /**
             * \brief Pink
             * \return {R:255 G:192 B:203 A:255}
             */
            static constexpr Colour pink() noexcept
            {
                return Colour(0xffffc0cb);
            }

            /**
             * \brief Plum
             * \return {R:221 G:160 B:221 A:255}
             */
            static constexpr Colour plum() noexcept
            {
                return Colour(0xffdda0dd);
            }

            /**
             * \brief Powder Blue
             * \return {R:176 G:224 B:230 A:255}
             */
            static constexpr Colour powder_blue() noexcept
            {
                return Colour(0xffb0e0e6);
            }

            /**
             * \brief Purple
             * \return {R:128 G:0 B:128 A:255}
             */
            static constexpr Colour purple() noexcept
            {
                return Colour(0xff800080);
            }

            /**
             * \brief Red
             * \return {R:255 G:0 B:0 A:255}
             */
            static constexpr Colour red() noexcept
            {
                return Colour(0xffff0000);
            }

            /**
             * \brief Rosy Brown
             * \return {R:188 G:143 B:143 A:255}
             */
            static constexpr Colour rosy_brown() noexcept
            {
                return Colour(0xffbc8f8f);
            }

            /**
             * \brief Royal Blue
             * \return {R:65 G:105 B:225 A:255}
             */
            static constexpr Colour royal_blue() noexcept
            {
                return Colour(0xff4169e1);
            }

            /**
             * \brief Saddle Brown
             * \return {R:139 G:69 B:19 A:255}
             */
            static constexpr Colour saddle_brown() noexcept
            {
                return Colour(0xff8b4513);
            }

            /**
             * \brief Salmon
             * \return {R:250 G:128 B:114 A:255}
             */
            static constexpr Colour salmon() noexcept
            {
                return Colour(0xfffa8072);
            }

            /**
             * \brief Sandy Brown
             * \return {R:244 G:164 B:96 A:255}
             */
            static constexpr Colour sandy_brown() noexcept
            {
                return Colour(0xfff4a460);
            }

            /**
             * \brief Sea Green
             * \return {R:46 G:139 B:87 A:255}
             */
            static constexpr Colour sea_green() noexcept
            {
                return Colour(0xff2e8b57);
            }

            /**
             * \brief Sea Shell
             * \return {R:255 G:245 B:238 A:255}
             */
            static constexpr Colour sea_shell() noexcept
            {
                return Colour(0xfffff5ee);
            }

            /**
             * \brief Sienna
             * \return {R:160 G:82 B:45 A:255}
             */
            static constexpr Colour sienna() noexcept
            {
                return Colour(0xffa0522d);
            }

            /**
             * \brief Silver
             * \return {R:192 G:192 B:192 A:255}
             */
            static constexpr Colour silver() noexcept
            {
                return Colour(0xffc0c0c0);
            }

            /**
             * \brief Sky Blue
             * \return {R:135 G:206 B:235 A:255}
             */
            static constexpr Colour sky_blue() noexcept
            {
                return Colour(0xff87ceeb);
            }

            /**
             * \brief Slate Blue
             * \return {R:106 G:90 B:205 A:255}
             */
            static constexpr Colour slate_blue() noexcept
            {
                return Colour(0xff6a5acd);
            }

            /**
             * \brief Slate Gray
             * \return {R:112 G:128 B:144 A:255}
             */
            static constexpr Colour slate_gray() noexcept
            {
                return Colour(0xff708090);
            }

            /**
             * \brief Snow
             * \return {R:255 G:250 B:250 A:255}
             */
            static constexpr Colour snow() noexcept
            {
                return Colour(0xfffffafa);
            }

            /**
             * \brief Spring Green
             * \return {R:0 G:255 B:127 A:255}
             */
            static constexpr Colour spring_green() noexcept
            {
                return Colour(0xff00ff7f);
            }

            /**
             * \brief Steel Blue
             * \return {R:70 G:130 B:180 A:255}
             */
            static constexpr Colour steel_blue() noexcept
            {
                return Colour(0xff4682b4);
            }

            /**
             * \brief Tan
             * \return {R:210 G:180 B:140 A:255}
             */
            static constexpr Colour tan() noexcept
            {
                return Colour(0xffd2b48c);
            }

            /**
             * \brief Teal
             * \return {R:0 G:128 B:128 A:255}
             */
            static constexpr Colour teal() noexcept
            {
                return Colour(0xff008080);
            }

            /**
             * \brief Thistle
             * \return {R:216 G:191 B:216 A:255}
             */
            static constexpr Colour thistle() noexcept
            {
                return Colour(0xffd8bfd8);
            }

            /**
             * \brief Tomato
             * \return {R:255 G:99 B:71 A:255}
             */
            static constexpr Colour tomato() noexcept
            {
                return Colour(0xffff6347);
            }

            /**
             * \brief Turquoise
             * \return {R:64 G:224 B:208 A:255}
             */
            static constexpr Colour turquoise() noexcept
            {
                return Colour(0xff40e0d0);
            }

            /**
             * \brief Violet
             * \return {R:238 G:130 B:238 A:255}
             */
            static constexpr Colour violet() noexcept
            {
                return Colour(0xffee82ee);
            }

            /**
             * \brief Wheat
             * \return {R:245 G:222 B:179 A:255}
             */
            static constexpr Colour wheat() noexcept
            {
                return Colour(0xfff5deb3);
            }

            /**
             * \brief White
             * \return {R:255 G:255 B:255 A:255}
             */
            static constexpr Colour white() noexcept
            {
                return Colour(std::numeric_limits<uint32_t>::max());
            }

            /**
             * \brief White Smoke
             * \return {R:245 G:245 B:245 A:255}
             */
            static constexpr Colour white_smoke() noexcept
            {
                return Colour(0xfff5f5f5);
            }

            /**
             * \brief Yellow
             * \return {R:255 G:255 B:0 A:255}
             */
            static constexpr Colour yellow() noexcept
            {
                return Colour(0xffffff00);
            }

            /**
             * \brief Yellow Green
             * \return {R:154 G:205 B:50 A:255}
             */
            static constexpr Colour yellow_green() noexcept
            {
                return Colour(0xff9acd32);
            }
        };
    }
}