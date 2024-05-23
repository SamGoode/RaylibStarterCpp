#pragma once
#include "Vector4.h"

namespace MathClasses {
    struct Matrix4 {
    private:
        float m1, m2, m3, m4, m5, m6, m7, m8, m9, m10, m11, m12, m13, m14, m15, m16;
        float mm[4][4];

    public:
        Matrix4() {
            m1 = 0, m5 = 0, m9 = 0, m13 = 0;
            m2 = 0, m6 = 0, m10 = 0, m14 = 0;
            m3 = 0, m7 = 0, m11 = 0, m15 = 0;
            m4 = 0, m8 = 0, m12 = 0, m16 = 0;

            mm[0][0] = m1, mm[1][0] = m5, mm[2][0] = m9, mm[3][0] = m13;
            mm[0][1] = m2, mm[1][1] = m6, mm[2][1] = m10, mm[3][1] = m14;
            mm[0][2] = m3, mm[1][2] = m7, mm[2][2] = m11, mm[3][2] = m15;
            mm[0][3] = m4, mm[1][3] = m8, mm[2][3] = m12, mm[3][3] = m16;
        }

        Matrix4(float a1, float a2, float a3, float a4, float a5, float a6, float a7, float a8, float a9, float a10, float a11, float a12, float a13, float a14, float a15, float a16) {
            m1 = a1, m5 = a5, m9 = a9, m13 = a13;
            m2 = a2, m6 = a6, m10 = a10, m14 = a14;
            m3 = a3, m7 = a7, m11 = a11, m15 = a15;
            m4 = a4, m8 = a8, m12 = a12, m16 = a16;

            mm[0][0] = m1, mm[1][0] = m5, mm[2][0] = m9, mm[3][0] = m13;
            mm[0][1] = m2, mm[1][1] = m6, mm[2][1] = m10, mm[3][1] = m14;
            mm[0][2] = m3, mm[1][2] = m7, mm[2][2] = m11, mm[3][2] = m15;
            mm[0][3] = m4, mm[1][3] = m8, mm[2][3] = m12, mm[3][3] = m16;
        }

        Matrix4(float fp[]) {
            m1 = fp[0], m5 = fp[4], m9 = fp[8], m13 = fp[12];
            m2 = fp[1], m6 = fp[5], m10 = fp[9], m14 = fp[13];
            m3 = fp[2], m7 = fp[6], m11 = fp[10], m15 = fp[14];
            m4 = fp[3], m8 = fp[7], m12 = fp[11], m16 = fp[15];

            mm[0][0] = m1, mm[1][0] = m5, mm[2][0] = m9, mm[3][0] = m13;
            mm[0][1] = m2, mm[1][1] = m6, mm[2][1] = m10, mm[3][1] = m14;
            mm[0][2] = m3, mm[1][2] = m7, mm[2][2] = m11, mm[3][2] = m15;
            mm[0][3] = m4, mm[1][3] = m8, mm[2][3] = m12, mm[3][3] = m16;
        }

        Matrix4(const Matrix4& copy) {
            m1 = copy.m1, m5 = copy.m5, m9 = copy.m9, m13 = copy.m13;
            m2 = copy.m2, m6 = copy.m6, m10 = copy.m10, m14 = copy.m14;
            m3 = copy.m3, m7 = copy.m7, m11 = copy.m11, m15 = copy.m15;
            m4 = copy.m4, m8 = copy.m8, m12 = copy.m12, m16 = copy.m16;

            mm[0][0] = m1, mm[1][0] = m5, mm[2][0] = m9,  mm[3][0] = m13;
            mm[0][1] = m2, mm[1][1] = m6, mm[2][1] = m10, mm[3][1] = m14;
            mm[0][2] = m3, mm[1][2] = m7, mm[2][2] = m11, mm[3][2] = m15;
            mm[0][3] = m4, mm[1][3] = m8, mm[2][3] = m12, mm[3][3] = m16;
        }

        friend bool operator==(Matrix4 m1, Matrix4 m2) {
            for (int c = 0; c < 4; c++) {
                for (int r = 0; r < 4; r++) {
                    if (abs(m1.mm[c][r] - m2.mm[c][r]) > 0.001) {
                        return false;
                    }
                }
            }

            return true;
        }

        const std::string ToString() const {
            std::string out;

            for (int r = 0; r < 4; r++) {
                for (int c = 0; c < 4; c++) {
                    out += std::to_string(mm[c][r]) + ", ";
                }
                out += "\n";
            }

            return out;
        }

        float operator[](int index) {
            return mm[index / 4][index % 4];
        }

        friend Vector4 operator*(Matrix4 m, Vector4 v) {
            return {
                m.m1 * v.x + m.m5 * v.y + m.m9  * v.z + m.m13 * v.w,
                m.m2 * v.x + m.m6 * v.y + m.m10 * v.z + m.m14 * v.w,
                m.m3 * v.x + m.m7 * v.y + m.m11 * v.z + m.m15 * v.w,
                m.m4 * v.x + m.m8 * v.y + m.m12 * v.z + m.m16 * v.w
            };
        }

        friend Matrix4 operator*(Matrix4 m1, Matrix4 m2) {
            return {
                (m1.m1 * m2.m1  + m1.m5 * m2.m2  + m1.m9 * m2.m3  + m1.m13 * m2.m4),  (m1.m2 * m2.m1  + m1.m6 * m2.m2  + m1.m10 * m2.m3 + m1.m14  * m2.m4),  (m1.m3 * m2.m1  + m1.m7 * m2.m2  + m1.m11 * m2.m3  + m1.m15 * m2.m4),  (m1.m4 * m2.m1  + m1.m8 * m2.m2  + m1.m12 * m2.m3  + m1.m16 * m2.m4),
                (m1.m1 * m2.m5  + m1.m5 * m2.m6  + m1.m9 * m2.m7  + m1.m13 * m2.m8),  (m1.m2 * m2.m5  + m1.m6 * m2.m6  + m1.m10 * m2.m7 + m1.m14  * m2.m8),  (m1.m3 * m2.m5  + m1.m7 * m2.m6  + m1.m11 * m2.m7  + m1.m15 * m2.m8),  (m1.m4 * m2.m5  + m1.m8 * m2.m6  + m1.m12 * m2.m7  + m1.m16 * m2.m8),
                (m1.m1 * m2.m9  + m1.m5 * m2.m10 + m1.m9 * m2.m11 + m1.m13 * m2.m12), (m1.m2 * m2.m9  + m1.m6 * m2.m10 + m1.m10 * m2.m11 + m1.m14 * m2.m12), (m1.m3 * m2.m9  + m1.m7 * m2.m10 + m1.m11 * m2.m11 + m1.m15 * m2.m12), (m1.m4 * m2.m9  + m1.m8 * m2.m10 + m1.m12 * m2.m11 + m1.m16 * m2.m12),
                (m1.m1 * m2.m13 + m1.m5 * m2.m14 + m1.m9 * m2.m15 + m1.m13 * m2.m16), (m1.m2 * m2.m13 + m1.m6 * m2.m14 + m1.m10 * m2.m15 + m1.m14 * m2.m16), (m1.m3 * m2.m13 + m1.m7 * m2.m14 + m1.m11 * m2.m15 + m1.m15 * m2.m16), (m1.m4 * m2.m13 + m1.m8 * m2.m14 + m1.m12 * m2.m15 + m1.m16 * m2.m16)
            };
        }

        static Matrix4 MakeIdentity() {
            return {
                1, 0, 0, 0,
                0, 1, 0, 0,
                0, 0, 1, 0,
                0, 0, 0, 1
            };
        }

        static Matrix4 MakeTranslation(float x, float y, float z) {
            return {
                1, 0, 0, 0,
                0, 1, 0, 0,
                0, 0, 1, 0,
                x, y, z, 1
            };
        }

        static Matrix4 MakeTranslation(Vector3 v) {
            return {
                1,   0,   0,   0,
                0,   1,   0,   0,
                0,   0,   1,   0,
                v.x, v.y, v.z, 1
            };
        }

        static Matrix4 MakeRotateX(float radians) {
            return {
                1, 0,             0,             0,
                0, (float)cos(radians),  (float)-sin(radians), 0,
                0, (float)sin(radians),  (float)cos(radians),  0,
                0, 0,             0,             1
            };
        }

        static Matrix4 MakeRotateY(float radians) {
            return {
                (float)cos(radians),  0, (float)sin(radians), 0,
                0,             1, 0,            0,
                (float)-sin(radians), 0, (float)cos(radians), 0,
                0,             0, 0,            1
            };
        }

        static Matrix4 MakeRotateZ(float radians) {
            return {
                (float)cos(radians),  (float)sin(radians), 0, 0,
                (float)-sin(radians), (float)cos(radians), 0, 0,
                0,             0,            1, 0,
                0,             0,            0, 1
            };
        }

        static Matrix4 MakeScale(float x, float y, float z) {
            return {
                x, 0, 0, 0,
                0, y, 0, 0,
                0, 0, z, 0,
                0, 0, 0, 1
            };
        }

        static Matrix4 MakeScale(Vector3 v) {
            return {
                v.x, 0,   0,   0,
                0,   v.y, 0,   0,
                0,   0,   v.z, 0,
                0,   0,   0,   1
            };
        }

        operator float*() {
            float* fp;
            fp = new float[16];

            for (int i = 0; i < 16; i++) {
                fp[i] = mm[i / 4][i % 4];
            }

            return fp;
        }
	};
}