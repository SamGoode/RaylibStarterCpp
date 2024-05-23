/*******************************************************************************************
*
*   raylib [core] example - Basic window
*
*   Welcome to raylib!
*
*   To test examples, just press F6 and execute raylib_compile_execute script
*   Note that compiled executable is placed in the same folder as .c file
*
*   You can find all basic examples on C:\raylib\raylib\examples folder or
*   raylib official webpage: www.raylib.com
*
*   Enjoy using raylib. :)
*
*   This example has been created using raylib 1.0 (www.raylib.com)
*   raylib is licensed under an unmodified zlib/libpng license (View raylib.h for details)
*
*   Copyright (c) 2014 Ramon Santamaria (@raysan5)
*
********************************************************************************************/

#include "MathHeaders/Colour.h"
#include "MathHeaders/Matrix3.h"
#include "MathHeaders/Matrix4.h"
#include "MathHeaders/Vector3.h"
#include "MathHeaders/Vector4.h"

#pragma warning( push , 0)
#include <raylib.h>

#define RAYGUI_IMPLEMENTATION
#define RAYGUI_SUPPORT_ICONS
#include <raygui.h>

#pragma warning(pop)

class Turret {
private:
    float length;
    float rotation;
    MathClasses::Vector3 pos;

    //temp solution for implementing firing
    bool firing;

public:
    Turret() {
        length = 0;
        rotation = 0;
        pos = { 0, 0, 1 };

        firing = false;
    }

    Turret(float length, float rotation, MathClasses::Vector3 pos) {
        this->length = length;
        this->rotation = rotation;
        this->pos = pos;

        firing = false;
    }

    Turret(const Turret& copy) {
        length = copy.length;
        rotation = copy.rotation;
        pos = copy.pos;

        firing = copy.firing;
    }

    Turret& operator=(const Turret& copy) {
        length = copy.length;
        rotation = copy.rotation;
        pos = copy.pos;

        firing = copy.firing;

        return *this;
    }

    const MathClasses::Vector3& getPos() const {
        return pos;
    }

    const float& getLength() const {
        return length;
    }

    MathClasses::Vector3 getDirection() {
        return MathClasses::Matrix3::MakeRotateZ(rotation) * MathClasses::Vector3(1, 0, 1);
    }

    void fire() {
        firing = true;
    }

    bool isFiring() {
        return firing;
    }

    void rotate(float radians) {
        rotation += radians;
    }

    void update(MathClasses::Vector3 pos) {
        this->pos = pos;

        firing = false;
    }

    void draw() {
        MathClasses::Vector3 endpoint = MathClasses::Vector3(pos + (getDirection() * length * 1.5));
        DrawLineEx({ pos.x, pos.y }, { endpoint.x, endpoint.y }, 6.f, DARKGRAY);
    }
};

class Tank {
private:
    float size;
    float rotation;
    float speed;
    MathClasses::Vector3 pos;
    MathClasses::Vector3 vel;
    Turret turret;

public:
    Tank() {
        size = 20;
        rotation = 0;
        speed = 0;
        pos = { 0, 0, 1 };
        vel = { 0, 0, 1 };

        turret = Turret(size, rotation, pos);
    }

    Tank(MathClasses::Vector3 pos) {
        size = 20;
        rotation = 0;
        speed = 0;
        this->pos = pos;
        vel = { 0, 0, 1 };

        turret = Turret(size, rotation, pos);
    }

    Tank(float rotation, MathClasses::Vector3 pos) {
        size = 20;
        this->rotation = rotation;
        speed = 0;
        this->pos = pos;
        vel = { 0, 0, 1 };

        turret = Turret(size, rotation, pos);
    }

    Tank(const Tank& copy) {
        size = copy.size;
        rotation = copy.rotation;
        speed = copy.speed;
        pos = copy.pos;
        vel = copy.vel;

        turret = copy.turret;
    }

    Tank& operator=(const Tank& copy) {
        size = copy.size;
        rotation = copy.rotation;
        speed = copy.speed;
        pos = copy.pos;
        vel = copy.vel;

        turret = copy.turret;

        return *this;
    }

    const MathClasses::Vector3& getPos() const {
        return pos;
    }

    const float& getRotation() const {
        return rotation;
    }

    MathClasses::Vector3 getDirection() {
        return MathClasses::Matrix3::MakeRotateZ(rotation) * MathClasses::Vector3(1, 0, 1);
    }

    Turret& getTurret() {
        return turret;
    }

    void setSpeed(float speed) {
        this->speed = speed;
    }

    void steer(float radians) {
        rotation += radians;
        turret.rotate(radians);
    }

    void update() {
        vel = getDirection() * speed;
        pos = pos + vel;

        turret.update(pos);
    }

    void draw() {
        DrawCircle(pos.x, pos.y, size, GREEN);
        MathClasses::Vector3 corners[4] = {
            MathClasses::Vector3(pos + (MathClasses::Matrix3::MakeRotateZ(-acos(-1) / 4) * getDirection() * size * 1.3)),
            MathClasses::Vector3(pos + (MathClasses::Matrix3::MakeRotateZ(acos(-1) / 4) * getDirection() * size * 1.3)),
            MathClasses::Vector3(pos + (MathClasses::Matrix3::MakeRotateZ(acos(-1) * 0.75) * getDirection() * size * 1.3)),
            MathClasses::Vector3(pos + (MathClasses::Matrix3::MakeRotateZ(-acos(-1) * 0.75) * getDirection() * size * 1.3))
        };

        DrawLineEx({ corners[0].x, corners[0].y}, {corners[3].x, corners[3].y}, 8.f, DARKGREEN);
        DrawLineEx({ corners[1].x, corners[1].y }, { corners[2].x, corners[2].y }, 8.f, DARKGREEN);
        
        turret.draw();
    }
};

class Bullet {
private:
    float size;
    float speed;
    MathClasses::Vector3 pos;
    MathClasses::Vector3 vel;

public:
    Bullet() {
        size = 5;
        speed = 5;
        pos = { 0, 0, 1 };
        vel = { 0, 0, 1 };
    }

    Bullet(MathClasses::Vector3 vel, MathClasses::Vector3 pos) {
        size = 5;
        speed = 5;
        this->pos = pos;
        this->vel = vel;
    }

    Bullet(const Bullet& copy) {
        size = copy.size;
        speed = copy.speed;
        pos = copy.pos;
        vel = copy.vel;
    }

    Bullet& operator=(const Bullet& copy) {
        size = copy.size;
        speed = copy.speed;
        pos = copy.pos;
        vel = copy.vel;

        return *this;
    }

    const MathClasses::Vector3& getPos() {
        return pos;
    }

    void reflectX() {
        vel.y = -vel.y;
    }

    void reflectY() {
        vel.x = -vel.x;
    }

    void setSpeed(float speed) {
        this->speed = speed;
    }

    void update() {
        pos = pos + (vel * speed);
    }

    void draw() {
        DrawCircle(pos.x, pos.y, size, BLACK);
    }
};

class Brick {
private:
    MathClasses::Vector3 pos;
    float width;
    float height;
    bool active;

public:
    Brick() {
        pos = { 0, 0, 1 };
        width = 0;
        height = 0;
        active = false;
    }

    Brick(MathClasses::Vector3 pos, float width, float height) {
        this->pos = pos;
        this->width = width;
        this->height = height;
        active = false;
    }

    Brick(const Brick& copy) {
        pos = copy.pos;
        width = copy.width;
        height = copy.height;
        active = copy.active;
    }

    Brick& operator=(const Brick& copy) {
        pos = copy.pos;
        width = copy.width;
        height = copy.height;
        active = copy.active;

        return *this;
    }

    bool checkCollision(MathClasses::Vector3 bulletPos) {
        return (bulletPos.x > pos.x && bulletPos.x < pos.x + width && bulletPos.y > pos.y && bulletPos.y < pos.y + height);
    }
    
    void draw() {
        DrawRectangleLines(pos.x, pos.y, width, height, BLACK);
    }
};

class Game {
private:
    int screenWidth;
    int screenHeight;

    Tank tank;
    int bulletCount;
    Bullet* bullets;

    int bricksWide;
    int bricksTall;
    Brick** bricks;
    //temp workaround
    int brickWidth = 50;
    int brickHeight = 25;

public:
    Game() {
        screenWidth = 400;
        screenHeight = 400;

        tank = Tank({ (float)screenWidth / 2, (float)screenHeight * 0.80f, 1 });

        bulletCount = 0;
        bullets = nullptr;

        bricksWide = 20;
        bricksTall = 20;

        bricks = new Brick*[bricksTall];
        for (int i = 0; i < bricksTall; i++) {
            bricks[i] = new Brick[bricksWide];
            for (int n = 0; n < bricksWide; n++) {
                bricks[i][n] = Brick(MathClasses::Vector3(i * brickWidth, 0, 1), brickWidth, brickHeight);
            }
        }
    }

    Game(int screenWidth, int screenHeight) {
        this->screenWidth = screenWidth;
        this->screenHeight = screenHeight;

        tank = Tank({ (float)screenWidth / 2, (float)screenHeight * 0.80f, 1 });

        bulletCount = 0;
        bullets = nullptr;

        bricksWide = 20;
        bricksTall = 20;

        bricks = new Brick * [bricksTall];
        for (int i = 0; i < bricksTall; i++) {
            bricks[i] = new Brick[bricksWide];
            for (int n = 0; n < bricksWide; n++) {
                bricks[i][n] = Brick(MathClasses::Vector3(n * brickWidth, i * brickHeight, 1), brickWidth, brickHeight);
            }
        }
    }

    ~Game() {
        delete[] bullets;

        for (int i = 0; i < bricksTall; i++) {
            delete[] bricks[i];
        }
        delete[] bricks;
    }

    void processInputs() {
        if (IsKeyDown(KEY_A)) {
            tank.steer(-5 * (acos(-1) / 180));
        }
        if (IsKeyDown(KEY_D)) {
            tank.steer(5 * (acos(-1) / 180));
        }

        if (IsKeyDown(KEY_W)) {
            tank.setSpeed(4);
        }
        else if (IsKeyDown(KEY_S)) {
            tank.setSpeed(-2);
        }
        else {
            tank.setSpeed(0);
        }

        if (IsKeyDown(KEY_Q)) {
            tank.getTurret().rotate(-5 * (acos(-1) / 180));
        }
        if (IsKeyDown(KEY_E)) {
            tank.getTurret().rotate(5 * (acos(-1) / 180));
        }

        if (IsKeyPressed(KEY_SPACE)) {
            tank.getTurret().fire();
        }
    }

    void spawnBullet(MathClasses::Vector3 vel, MathClasses::Vector3 pos) {
        Bullet* oldPtr = bullets;

        bulletCount++;
        bullets = new Bullet[bulletCount];
        for (int i = 0; i < bulletCount - 1; i++) {
            bullets[i] = oldPtr[i];
        }
        delete[] oldPtr;

        bullets[bulletCount - 1] = Bullet(vel, pos);
    }

    void processCollisions() {
        for (int i = 0; i < bulletCount; i++) {
            if (bullets[i].getPos().x < 0 || bullets[i].getPos().x > screenWidth) {
                bullets[i].reflectY();
            }

            if (bullets[i].getPos().y < 0 || bullets[i].getPos().y > screenHeight) {
                bullets[i].reflectX();
            }

            for (int j = 0; j < bricksTall; j++) {
                for (int n = 0; n < bricksWide; n++) {
                    if (bricks[j][n].checkCollision(bullets[i].getPos())) {
                        bullets[i].reflectX();
                    }
                }
            }
        }
    }

    void update() {
        Turret& turret = tank.getTurret();

        if (turret.isFiring()) {
            spawnBullet(turret.getDirection(), turret.getPos() + (turret.getDirection() * turret.getLength()));
        }
        
        processCollisions();

        tank.update();

        for (int i = 0; i < bulletCount; i++) {
            bullets[i].update();
        }
    }

    void draw() {
        for (int i = 0; i < bricksTall; i++) {
            for (int n = 0; n < bricksWide; n++) {
                bricks[i][n].draw();
            }
        }

        tank.draw();

        for (int i = 0; i < bulletCount; i++) {
            bullets[i].draw();
        }
    }
};

int main(int argc, char* argv[])
{
    // Initialization
    //--------------------------------------------------------------------------------------
    int screenWidth = 1000;
    int screenHeight = 800;

    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");

    SetTargetFPS(60);
    //--------------------------------------------------------------------------------------

    float pi = acos(-1);

    //Tank tank = Tank({ screenWidth / 2.f, screenHeight / 2.f, 1 });
    Game game = Game(screenWidth, screenHeight);

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        game.processInputs();
        game.update();

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

        ClearBackground(RAYWHITE);

        //DrawText("Congrats! You created your first window!", 190, 200, 20, LIGHTGRAY);
        //DrawRectangle(20, 20, 100, 100, VIOLET);
        //DrawCircle(100, 100, 5, GREEN);
        //DrawTriangle({ 100.0f, 100.0f }, { 100.0f, 200.0f }, { 200.0f, 100.0f }, LIGHTGRAY);
        //DrawRectangle()

        game.draw();

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------   
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}