#include "BrickMap.h"
#include "raylib.h"

BrickMap::BrickMap() {}

BrickMap::BrickMap(MathClasses::Vector3 _pos, int _width, int _height, float _brickWidth, float _brickHeight) {
    pos = _pos;
    width = _width;
    height = _height;
    brickWidth = _brickWidth;
    brickHeight = _brickHeight;
    mapState = BitMap(width, height);
}

BrickMap::BrickMap(const BrickMap& copy) {
    pos = copy.pos;
    width = copy.width;
    height = copy.height;
    brickWidth = copy.brickWidth;
    brickHeight = copy.brickHeight;
    mapState = copy.mapState;
}

BrickMap& BrickMap::operator=(const BrickMap& copy) {
    pos = copy.pos;
    width = copy.width;
    height = copy.height;
    brickWidth = copy.brickWidth;
    brickHeight = copy.brickHeight;
    mapState = copy.mapState;

    return *this;
}

bool BrickMap::isWithinBounds(MathClasses::Vector3 vec) {
    return (vec.x > pos.x && vec.x < pos.x + width * brickWidth && vec.y > pos.y && vec.y < pos.y + height * brickHeight);
}

bool BrickMap::isWithinBrick(MathClasses::Vector3 vec) {
    return mapState.getBit((vec.x - pos.x) / brickWidth, (vec.y - pos.y) / brickHeight);
}

void BrickMap::destroyBrick(MathClasses::Vector3 vec) {
    mapState.getBit((vec.x - pos.x) / brickWidth, (vec.y - pos.y) / brickHeight) = false;
}

//void BrickMap::checkCollision(Bullet& bullet) {
//    MathClasses::Vector3 check = bullet.getWorldPos();
//    if (!isWithinBounds(check)) {
//        return;
//    }
//
//    if (!isWithinBrick(check)) {
//        return;
//    }
//
//    destroyBrick(check);
//    bullet.bounce(0);
//
//    MathClasses::Vector3 brickCentre = { pos.x + (x * brickWidth + brickWidth / 2), pos.y + (y * brickHeight + brickHeight / 2), 0 };
//    float angle = (check - brickCentre).Angle2D();
//    if (angle >= MathClasses::pi * 0.25 && angle <= MathClasses::pi * 0.75) {
//        bullet.bounce(0);
//        return;
//    }
//    if (angle >= MathClasses::pi * -0.75 && angle <= MathClasses::pi * -0.25) {
//        bullet.bounce(0);
//        return;
//    }
//    if (angle > MathClasses::pi * -0.25 && angle < MathClasses::pi * 0.25) {
//        bullet.bounce(MathClasses::pi / 2);
//        return;
//    }
//    bullet.bounce(MathClasses::pi / 2);
//}

void BrickMap::draw() {
    for (int i = 0; i < height; i++) {
        for (int n = 0; n < width; n++) {
            if (!mapState.getBit(n, i)) {
                continue;
            }

            DrawRectangle((int)pos.x + brickWidth * n, (int)pos.y + brickHeight * i, (int)brickWidth, (int)brickHeight, BLUE);
            DrawRectangleLines((int)pos.x + brickWidth * n, (int)pos.y + brickHeight * i, (int)brickWidth, (int)brickHeight, RAYWHITE);
        }
    }
}