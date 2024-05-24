#include "GameObject.h"

GameObject::GameObject() {
    parent = nullptr;
    pos = { 0, 0, 0 };
    rot = 0;
}

GameObject::GameObject(MathClasses::Vector3 pos, float rot) {
    parent = nullptr;
    this->pos = pos;
    this->rot = rot;
}

GameObject::GameObject(GameObject* parent, MathClasses::Vector3 pos, float rot) {
    this->parent = parent;
    this->pos = pos;
    this->rot = rot;
}

GameObject* GameObject::getParent() {
    return parent;
}

const GameObject* GameObject::getParent() const {
    return parent;
}

void GameObject::setParent(GameObject* newParent) {
    parent = newParent;
}

const MathClasses::Vector3& GameObject::getPos() const {
    return pos;
}

MathClasses::Vector3 GameObject::getWorldPos() {
    if (parent) {
        return parent->getWorldPos() + pos;
    }

    return pos;
}

const float& GameObject::getRot() const {
    return rot;
}

float GameObject::getWorldRot() {
    if (parent) {
        return parent->getWorldRot() + rot;
    }

    return rot;
}

MathClasses::Vector3 GameObject::getUnitDir() {
    return MathClasses::Matrix3::MakeRotateZ(rot) * MathClasses::Vector3(1, 0, 0);
}

MathClasses::Vector3 GameObject::getWorldUnitDir() {
    return MathClasses::Matrix3::MakeRotateZ(getWorldRot()) * MathClasses::Vector3(1, 0, 0);
}

void GameObject::setPos(MathClasses::Vector3 pos) {
    this->pos = pos;
}

void GameObject::move(MathClasses::Vector3 vec) {
    pos = pos + vec;
}

void GameObject::setRot(float radians) {
    rot = radians;
}

void GameObject::rotate(float radians) {
    rot += radians;
}