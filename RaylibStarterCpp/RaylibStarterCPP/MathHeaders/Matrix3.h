#pragma once
#include "Vector3.h"

namespace MathClasses {
    struct Matrix3 {
    private:
        float m1, m2, m3, m4, m5, m6, m7, m8, m9;
        float mm[3][3];

    public:
        Matrix3() {
            m1 = 0, m4 = 0, m7 = 0;
            m2 = 0, m5 = 0, m8 = 0;
            m3 = 0, m6 = 0, m9 = 0;

            mm[0][0] = m1, mm[1][0] = m4, mm[2][0] = m7;
            mm[0][1] = m2, mm[1][1] = m5, mm[2][1] = m8;
            mm[0][2] = m3, mm[1][2] = m6, mm[2][2] = m9;
        }

        Matrix3(float a1, float a2, float a3, float a4, float a5, float a6, float a7, float a8, float a9) {
            m1 = a1, m4 = a4, m7 = a7;
            m2 = a2, m5 = a5, m8 = a8;
            m3 = a3, m6 = a6, m9 = a9;

            mm[0][0] = m1, mm[1][0] = m4, mm[2][0] = m7;
            mm[0][1] = m2, mm[1][1] = m5, mm[2][1] = m8;
            mm[0][2] = m3, mm[1][2] = m6, mm[2][2] = m9;
        }

        Matrix3(float fp[]) {
            m1 = fp[0], m4 = fp[3], m7 = fp[6];
            m2 = fp[1], m5 = fp[4], m8 = fp[7];
            m3 = fp[2], m6 = fp[5], m9 = fp[8];

            mm[0][0] = m1, mm[1][0] = m4, mm[2][0] = m7;
            mm[0][1] = m2, mm[1][1] = m5, mm[2][1] = m8;
            mm[0][2] = m3, mm[1][2] = m6, mm[2][2] = m9;
        }

        Matrix3(const Matrix3& copy) {
            m1 = copy.m1, m4 = copy.m4, m7 = copy.m7;
            m2 = copy.m2, m5 = copy.m5, m8 = copy.m8;
            m3 = copy.m3, m6 = copy.m6, m9 = copy.m9;

            mm[0][0] = m1, mm[1][0] = m4, mm[2][0] = m7;
            mm[0][1] = m2, mm[1][1] = m5, mm[2][1] = m8;
            mm[0][2] = m3, mm[1][2] = m6, mm[2][2] = m9;
        }

        friend bool operator==(Matrix3 m1, Matrix3 m2) {
            for (int c = 0; c < 3; c++) {
                for (int r = 0; r < 3; r++) {
                    if (abs(m1.mm[c][r] - m2.mm[c][r]) > 0.001) {
                        return false;
                    }
                }
            }

            return true;
        }

        const std::string ToString() const {
            std::string out;

            for (int r = 0; r < 3; r++) {
                for (int c = 0; c < 3; c++) {
                    out += std::to_string(mm[c][r]) + ", ";
                }
                out += "\n";
            }

            return out;
        }

        float operator[](int index) {
            return mm[index / 3][index % 3];
        }

        friend Vector3 operator*(Matrix3 m, Vector3 v) {
            return {
                m.m1 * v.x + m.m4 * v.y + m.m7 * v.z,
                m.m2 * v.x + m.m5 * v.y + m.m8 * v.z,
                m.m3 * v.x + m.m6 * v.y + m.m9 * v.z
            };
        }

        friend Matrix3 operator*(Matrix3 m1, Matrix3 m2) {
            return {
                (m1.m1 * m2.m1 + m1.m4 * m2.m2 + m1.m7 * m2.m3), (m1.m2 * m2.m1 + m1.m5 * m2.m2 + m1.m8 * m2.m3), (m1.m3 * m2.m1 + m1.m6 * m2.m2 + m1.m9 * m2.m3),
                (m1.m1 * m2.m4 + m1.m4 * m2.m5 + m1.m7 * m2.m6), (m1.m2 * m2.m4 + m1.m5 * m2.m5 + m1.m8 * m2.m6), (m1.m3 * m2.m4 + m1.m6 * m2.m5 + m1.m9 * m2.m6),
                (m1.m1 * m2.m7 + m1.m4 * m2.m8 + m1.m7 * m2.m9), (m1.m2 * m2.m7 + m1.m5 * m2.m8 + m1.m8 * m2.m9), (m1.m3 * m2.m7 + m1.m6 * m2.m8 + m1.m9 * m2.m9)
            };
        }

        static Matrix3 MakeIdentity() {
            return {
                1, 0, 0,
                0, 1, 0,
                0, 0, 1
            };
        }

        static Matrix3 MakeTranslation(float x, float y, float w) {
            return {
                1, 0, 0,
                0, 1, 0,
                x, y, w
            };
        }

        static Matrix3 MakeTranslation(Vector3 v) {
            return {
                1,   0,   0,
                0,   1,   0,
                v.x, v.y, v.z
            };
        }

        static Matrix3 MakeRotateX(float radians) {
            return {
                1, 0,                   0,
                0, (float)cos(radians), (float)-sin(radians),
                0, (float)sin(radians), (float)cos(radians)
            };
        }

        static Matrix3 MakeRotateY(float radians) {
            return {
                (float)cos(radians),  0, (float)sin(radians),
                0,                    1, 0,
                (float)-sin(radians), 0, (float)cos(radians)
            };
        }

        static Matrix3 MakeRotateZ(float radians) {
            return {
                (float)cos(radians),  (float)sin(radians), 0,
                (float)-sin(radians), (float)cos(radians), 0,
                0,                    0,                   1
            };
        }

        static Matrix3 MakeEuler(float rotX, float rotY, float rotZ) {
            return {
                (float)(cos(rotY) * cos(rotZ)),                                      (float)(cos(rotY) * sin(rotZ)),                                      (float)sin(rotY),
                (float)(sin(rotX) * sin(rotY) * cos(rotZ) - cos(rotX) * sin(rotZ)),  (float)(sin(rotX) * sin(rotY) * sin(rotZ) + cos(rotX) * cos(rotZ)),  (float)(-sin(rotX) * cos(rotY)),
                (float)(-cos(rotX) * sin(rotY) * cos(rotZ) - sin(rotX) * sin(rotZ)), (float)(-cos(rotX) * sin(rotY) * sin(rotZ) + sin(rotX) * cos(rotZ)), (float)(cos(rotX) * cos(rotY))
            };
        }

        static Matrix3 MakeEuler(Vector3 v) {
            return {
                (float)(cos(v.y) * cos(v.z)),                                   (float)(cos(v.y) * sin(v.z)),                                   (float)sin(v.y),
                (float)(sin(v.x) * sin(v.y) * cos(v.z) - cos(v.x) * sin(v.z)),  (float)(sin(v.x) * sin(v.y) * sin(v.z) + cos(v.x) * cos(v.z)),  (float)(-sin(v.x) * cos(v.y)),
                (float)(-cos(v.x) * sin(v.y) * cos(v.z) - sin(v.x) * sin(v.z)), (float)(-cos(v.x) * sin(v.y) * sin(v.z) + sin(v.x) * cos(v.z)), (float)(cos(v.x) * cos(v.y))
            };
        }

        static Matrix3 MakeScale(float x, float y) {
            return {
                x, 0, 0,
                0, y, 0,
                0, 0, 1
            };
        }

        static Matrix3 MakeScale(float x, float y, float z) {
            return {
                x, 0, 0,
                0, y, 0,
                0, 0, z
            };
        }

        static Matrix3 MakeScale(Vector3 v) {
            return {
                v.x, 0,   0,
                0,   v.y, 0,
                0,   0,   v.z
            };
        }

        Matrix3 Transposed() {
            return {
                m1, m4, m7,
                m2, m5, m8,
                m3, m6, m9
            };
        }

        operator float*() {
            float* fp;
            fp = new float[9];
            
            for (int i = 0; i < 9; i++) {
                fp[i] = mm[i / 3][i % 3];
            }

            return fp;
        }
	};
}