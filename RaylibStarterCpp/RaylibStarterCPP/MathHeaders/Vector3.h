#pragma once
#include "string"

namespace MathClasses {
    const float pi = acos(-1);

    struct Vector3 {
    public:
        float x, y, z;

    public:
        Vector3() {
            x = 0;
            y = 0;
            z = 0;
        }

        Vector3(float x, float y, float z) {
            this->x = x;
            this->y = y;
            this->z = z;
        }

        friend bool operator==(Vector3 v1, Vector3 v2) {
            return (abs(v1.x - v2.x) < 0.001) && (abs(v1.y - v2.y) < 0.001) && (abs(v1.z - v2.z) < 0.001);
        }

        const std::string& ToString() const {
            return "x:" + std::to_string(x) + ", y:" + std::to_string(y) + ", z:" + std::to_string(z);
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
            }
        }

        friend Vector3 operator+(Vector3 v1, Vector3 v2) {
            return { v1.x + v2.x, v1.y + v2.y, v1.z + v2.z };
        }

        friend Vector3 operator-(Vector3 v1, Vector3 v2) {
            return { v1.x - v2.x, v1.y - v2.y, v1.z - v2.z };
        }

        friend Vector3 operator*(Vector3 v, float scalar) {
            return { v.x * scalar, v.y * scalar, v.z * scalar };
        }

        friend Vector3 operator*(float scalar, Vector3 v) {
            return { v.x * scalar, v.y * scalar, v.z * scalar };
        }

        friend Vector3 operator/(Vector3 v, float scalar) {
            return { v.x / scalar, v.y / scalar, v.z / scalar };
        }

        float Dot(Vector3 v) {
            return x * v.x + y * v.y + z * v.z;
        }

        Vector3 Cross(Vector3 v) {
            return { y * v.z - z * v.y, -(x * v.z - z * v.x), x * v.y - y * v.x };
        }

        float Magnitude() {
            return (float)sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2));
        }

        void SetMagnitude(float newMag) {
            Normalise();

            x = x * newMag;
            y = y * newMag;
            z = z * newMag;
        }

        void Normalise() {
            float mag = Magnitude();

            if (mag == 0) {
                return;
            }

            x = x / mag;
            y = y / mag;
            z = z / mag;
        }

        Vector3 Normalised() {
            float mag = Magnitude();

            if (mag == 0) {
                return { 0, 0, 0 };
            }

            return { x / mag, y / mag, z / mag };
        }

        float Angle2D() {
            Vector3 unitVec = Normalised();

            if (unitVec.y >= 0) {
                return (float)acos(unitVec.x);
            }
            else {
                return (float)-acos(unitVec.x);
            }
        }

        operator float*() {
            float* fp;
            fp = new float[3];
            fp[0] = x, fp[1] = y, fp[2] = z;

            return fp;
        }
	};
}