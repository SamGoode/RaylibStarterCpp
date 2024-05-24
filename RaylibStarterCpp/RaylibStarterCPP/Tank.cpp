#include "Tank.h"
#include "Raylib.h"

Tank::Tank() {
    size = 0;
    speed = 0;
    vel = { 0, 0, 0 };

    turret = Turret({ 0, 0, 0 }, 0, size * 1.5);
    turret.setParent(this);

    active = true;
}

Tank::Tank(MathClasses::Vector3 pos, float rot, float size) {
    setPos(pos);
    setRot(rot);
    this->size = size;
    speed = 0;
    vel = { 0, 0, 0 };

    turret = Turret({ 0, 0, 0 }, 0, size * 1.5);
    turret.setParent(this);

    active = true;
}

Tank::Tank(const Tank& copy) {
    //setParent(copy.getParent());
    setPos(copy.getPos());
    setRot(copy.getRot());
    size = copy.size;
    speed = copy.speed;
    vel = copy.vel;

    turret = copy.turret;

    active = copy.active;
}

Tank& Tank::operator=(const Tank& copy) {
    //setParent(copy.getParent());
    setPos(copy.getPos());
    setRot(copy.getRot());
    size = copy.size;
    speed = copy.speed;
    vel = copy.vel;

    turret = copy.turret;

    active = copy.active;

    return *this;
}

const float& Tank::getSize() const {
    return size;
}

Turret& Tank::getTurret() {
    return turret;
}

void Tank::destroy() {
    active = false;
}

void Tank::setSpeed(float speed) {
    this->speed = speed;
}

void Tank::steer(float radians) {
    if (!active) {
        return;
    }

    rotate(radians);
}

void Tank::update() {
    if (!active) {
        return;
    }

    vel = getUnitDir() * speed;
    move(vel);

    turret.update();
}

void Tank::draw() {
    MathClasses::Vector3 pos = getWorldPos();
    MathClasses::Vector3 dir = getWorldUnitDir();

    if (!active) {
        DrawCircle(pos.x, pos.y, size + 5, RED);

        return;
    }

    DrawCircle(pos.x, pos.y, size, GREEN);
    MathClasses::Vector3 corners[4] = {
        MathClasses::Vector3(pos + (MathClasses::Matrix3::MakeRotateZ(-acos(-1) / 4) * dir * size * 1.3)),
        MathClasses::Vector3(pos + (MathClasses::Matrix3::MakeRotateZ(acos(-1) / 4) * dir * size * 1.3)),
        MathClasses::Vector3(pos + (MathClasses::Matrix3::MakeRotateZ(acos(-1) * 0.75) * dir * size * 1.3)),
        MathClasses::Vector3(pos + (MathClasses::Matrix3::MakeRotateZ(-acos(-1) * 0.75) * dir * size * 1.3))
    };

    DrawLineEx({ corners[0].x, corners[0].y }, { corners[3].x, corners[3].y }, 8.f, DARKGREEN);
    DrawLineEx({ corners[1].x, corners[1].y }, { corners[2].x, corners[2].y }, 8.f, DARKGREEN);

    turret.draw();
}
