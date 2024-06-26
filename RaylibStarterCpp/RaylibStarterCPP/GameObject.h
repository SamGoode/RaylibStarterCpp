#pragma once
#include "MathHeaders/Matrix3.h"
#include "MathHeaders/Vector3.h"

class GameObject {
private:
    class Game* level;
    GameObject* parent;

    //local values
    MathClasses::Vector3 pos;
    float rot;

public:
    GameObject();

    Game* getLevel();

    const Game* getLevel() const;

    void setLevel(Game* _level);

    GameObject* getParent();

    const GameObject* getParent() const;

    void setParent(GameObject* parent);

    const MathClasses::Vector3& getPos() const;

    MathClasses::Vector3 getWorldPos();

    const float& getRot() const;

    float getWorldRot();

    MathClasses::Vector3 getUnitDir();

    MathClasses::Vector3 getWorldUnitDir();

    void setPos(MathClasses::Vector3 pos);

    void move(MathClasses::Vector3 vec);

    void setRot(float radians);

    void rotate(float radians);
};