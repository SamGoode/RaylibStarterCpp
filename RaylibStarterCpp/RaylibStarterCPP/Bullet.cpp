#include "Bullet.h"
#include "raylib.h"

Bullet::Bullet() {
    size = 5;
    speed = 5;
    vel = { 0, 0, 0 };
}

Bullet::Bullet(MathClasses::Vector3 _pos, float _rot) {
    setPos(_pos);
    setRot(_rot);
    size = 5;
    speed = 5;
    vel = { 0, 0, 0 };
}

Bullet::Bullet(const Bullet& copy) {
    setPos(copy.getPos());
    setRot(copy.getRot());
    size = copy.size;
    speed = copy.speed;
    vel = copy.vel;
}

Bullet& Bullet::operator=(const Bullet& copy) {
    setPos(copy.getPos());
    setRot(copy.getRot());
    size = copy.size;
    speed = copy.speed;
    vel = copy.vel;

    return *this;
}

void Bullet::bounce(float wallAngle) {
    rotate(2 * (wallAngle - vel.Angle2D()));
}

void Bullet::setSpeed(float newSpeed) {
    speed = newSpeed;
}

void Bullet::update() {
    vel = getUnitDir() * speed;
    move(vel);
}

void Bullet::draw() {
    MathClasses::Vector3 pos = getWorldPos();
    DrawCircle(pos.x, pos.y, size, BLACK);
}