#pragma once
#include "MathHeaders/Vector3.h"
#include "BitMap.h"

class BrickMap {
private:
    MathClasses::Vector3 pos;
    int width;
    int height;
    float brickWidth;
    float brickHeight;
    BitMap mapState;

public:
    BrickMap();

    BrickMap(MathClasses::Vector3 _pos, int _width, int _height, float _brickWidth, float _brickHeight);

    BrickMap(const BrickMap& copy);

    BrickMap& operator=(const BrickMap& copy);

    bool isWithinBounds(MathClasses::Vector3 vec);

    bool isWithinBrick(MathClasses::Vector3 vec);

    void destroyBrick(MathClasses::Vector3 vec);

    void draw();
};