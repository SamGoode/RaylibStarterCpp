#pragma once
#include "string"

namespace MathClasses {
    using Byte = unsigned char;

    struct Colour {
    public:
        //0xFFFFFFFF = rgba(255, 255, 255, 255)
        unsigned int colour;

    public:
        Colour() {
            colour = 0x000000FF;
        }

        Colour(Byte r, Byte g, Byte b, Byte a) {
            colour = 0x00000000;
            colour += r;
            colour <<= 8;
            colour += g;
            colour <<= 8;
            colour += b;
            colour <<= 8;
            colour += a;
        }

        friend bool operator==(Colour clr1, Colour clr2) {
            return (clr1.colour == clr2.colour);
        }

        void SetRed(Byte value) {
            colour = colour & 0x00FFFFFF;
            unsigned int r = value;
            r <<= 24;
            colour += r;
        }

        void SetGreen(Byte value) {
            colour = colour & 0xFF00FFFF;
            unsigned int g = value;
            g <<= 16;
            colour += g;
        }

        void SetBlue(Byte value) {
            colour = colour & 0xFFFF00FF;
            unsigned int b = value;
            b <<= 8;
            colour += b;
        }

        void SetAlpha(Byte value) {
            colour = colour & 0xFFFFFF00;
            unsigned int a = value;
            colour += a;
        }

        const Byte GetRed() const {
            unsigned int r = (colour & 0xFF000000);
            r >>= 24;

            return r;
        }

        const Byte GetGreen() const {
            unsigned int g = (colour & 0x00FF0000);
            g >>= 16;

            return g;
        }

        const Byte GetBlue() const {
            unsigned int b = (colour & 0x0000FF00);
            b >>= 8;

            return b;
        }

        const Byte GetAlpha() const {
            unsigned int a = (colour & 0x000000FF);

            return a;
        }
    };
}