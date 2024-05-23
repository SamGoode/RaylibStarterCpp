#pragma once
#include "string"

namespace MathClasses {
    struct Vector4 {
    public:
        float x, y, z, w;

    public:
        Vector4() {
            x = 0;
            y = 0;
            z = 0;
            w = 0;
        }

        Vector4(float x, float y, float z, float w) {
            this->x = x;
            this->y = y;
            this->z = z;
            this->w = w;
        }

        friend bool operator==(Vector4 v1, Vector4 v2) {
            return (abs(v1.x - v2.x) < 0.001) && (abs(v1.y - v2.y) < 0.001) && (abs(v1.z - v2.z) < 0.001) && (abs(v1.w - v2.w) < 0.001);
        }

        const std::string ToString() const {
            return "x:" + std::to_string(x) + ", y:" + std::to_string(y) + ", z:" + std::to_string(z) + ", w:" + std::to_string(w);
        }

        float& operator[](int index) {
            switch (index) {
            case 0:
                return x;
                break;
            case 1:
                return y;
                break;
            case 2:
                return z;
                break;
            case 3:
                return w;
                break;
            }
        }

        const float& operator[](int index) const {
            switch (index) {
            case 0:
                return x;
                break;
            case 1:
                return y;
                break;
            case 2:
                return z;
                break;
            case 3:
                return w;
                break;
            }
        }

        friend Vector4 operator+(Vector4 v1, Vector4 v2) {
            return { v1.x + v2.x, v1.y + v2.y, v1.z + v2.z, v1.w + v2.w };
        }

        friend Vector4 operator-(Vector4 v1, Vector4 v2) {
            return { v1.x - v2.x, v1.y - v2.y, v1.z - v2.z, v1.w - v2.w };
        }

        friend Vector4 operator*(Vector4 v, float scalar) {
            return { v.x * scalar, v.y * scalar, v.z * scalar, v.w };
        }

        friend Vector4 operator*(float scalar, Vector4 v) {
            return { v.x * scalar, v.y * scalar, v.z * scalar, v.w };
        }

        friend Vector4 operator/(Vector4 v, float scalar) {
            if (scalar == 0) {
                return { 0, 0, 0, 0 };
            }

            return { v.x / scalar, v.y / scalar, v.z / scalar, v.w / scalar };
        }

        float Dot(Vector4 v) {
            return x * v.x + y * v.y + z * v.z;
        }

        Vector4 Cross(Vector4 v) {
            return { y * v.z - z * v.y, -(x * v.z - z * v.x), x * v.y - y * v.x, w };
        }

        float Magnitude() {
            return (float)sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2));
        }

        void Normalise() {
            float mag = Magnitude();

            if (mag == 0) {
                return;
            }

            x = x / mag;
            y = y / mag;
            z = z / mag;
            w = w / mag;
        }

        Vector4 Normalised() {
            float mag = Magnitude();

            if (mag == 0) {
                return { 0, 0, 0, w };
            }

            return { x / mag, y / mag, z / mag, w / mag};
        }

        operator float*() {
            float* fp;
            fp = new float[4];
            fp[0] = x, fp[1] = y, fp[2] = z, fp[3] = w;

            return fp;
        }
	};
}