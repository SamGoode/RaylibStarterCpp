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
#include "MathHeaders/Vector3.h"
#include "GameObject.h"
#include "Tank.h"
#include "Turret.h"

#pragma warning( push , 0)
#include <raylib.h>

#define RAYGUI_IMPLEMENTATION
#define RAYGUI_SUPPORT_ICONS
#include <raygui.h>

#pragma warning(pop)

class Bullet : public GameObject {
private:
    float size;
    float speed;
    MathClasses::Vector3 vel;

public:
    Bullet() {
        size = 5;
        speed = 5;
        vel = { 0, 0, 0 };
    }

    Bullet(MathClasses::Vector3 pos, float rot) {
        setPos(pos);
        setRot(rot);
        size = 5;
        speed = 5;
        vel = { 0, 0, 0 };
    }

    Bullet(const Bullet& copy) {
        setPos(copy.getPos());
        setRot(copy.getRot());
        size = copy.size;
        speed = copy.speed;
        vel = copy.vel;
    }

    Bullet& operator=(const Bullet& copy) {
        setPos(copy.getPos());
        setRot(copy.getRot());
        size = copy.size;
        speed = copy.speed;
        vel = copy.vel;

        return *this;
    }

    void bounce(float wallAngle) {
        float newAngle = vel.Angle2D() - 2 * (vel.Angle2D() - wallAngle);

        setRot(newAngle);
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
        vel = getUnitDir() * speed;
        move(vel);
    }

    void draw() {
        MathClasses::Vector3 pos = getWorldPos();
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
        active = true;
    }

    Brick(MathClasses::Vector3 pos, float width, float height) {
        this->pos = pos;
        this->width = width;
        this->height = height;
        active = true;
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

    MathClasses::Vector3 getCentrePos() {
        return { pos.x + (width / 2), pos.y + (height / 2), 1 };
    }

    void destroy() {
        active = false;
    }

    bool checkCollision(MathClasses::Vector3 bulletPos) {
        if (!active) {
            return false;
        }

        return (bulletPos.x > pos.x && bulletPos.x < pos.x + width && bulletPos.y > pos.y && bulletPos.y < pos.y + height);
    }
    
    void draw() {
        if (!active) {
            return;
        }

        DrawRectangleLines(pos.x, pos.y, width, height, BLACK);
    }
};

class Game {
private:
    int screenWidth;
    int screenHeight;

    int score;

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

        score = 0;

        tank = Tank({ (float)screenWidth / 2, (float)screenHeight * 0.80f, 1 }, 0, 20);

        bulletCount = 0;
        bullets = nullptr;

        bricksWide = 20;
        bricksTall = 20;

        bricks = new Brick * [bricksTall];
        for (int i = 0; i < bricksTall; i++) {
            bricks[i] = new Brick[bricksWide];
            for (int n = 0; n < bricksWide; n++) {
                bricks[i][n] = Brick(MathClasses::Vector3(n * brickWidth, (i+1) * brickHeight, 1), brickWidth, brickHeight);
            }
        }
    }

    Game(int screenWidth, int screenHeight) {
        this->screenWidth = screenWidth;
        this->screenHeight = screenHeight;

        score = 0;

        tank = Tank({ (float)screenWidth / 2, (float)screenHeight * 0.80f, 1 }, 0, 20);

        bulletCount = 0;
        bullets = nullptr;

        bricksWide = 20;
        bricksTall = 20;

        bricks = new Brick * [bricksTall];
        for (int i = 0; i < bricksTall; i++) {
            bricks[i] = new Brick[bricksWide];
            for (int n = 0; n < bricksWide; n++) {
                bricks[i][n] = Brick(MathClasses::Vector3(n * brickWidth, (i+2) * brickHeight, 1), brickWidth, brickHeight);
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
        if (IsKeyDown(KEY_W)) {
            tank.setSpeed(4);
        }
        else if (IsKeyDown(KEY_S)) {
            tank.setSpeed(-2);
        }
        else {
            tank.setSpeed(0);
        }
        
        if (IsKeyDown(KEY_A)) {
            tank.steer(-5 * (acos(-1) / 180));
        }
        if (IsKeyDown(KEY_D)) {
            tank.steer(5 * (acos(-1) / 180));
        }

        if (IsKeyDown(KEY_Q)) {
            tank.getTurret().turn(-5 * (acos(-1) / 180));
        }
        if (IsKeyDown(KEY_E)) {
            tank.getTurret().turn(5 * (acos(-1) / 180));
        }

        if (IsKeyPressed(KEY_SPACE)) {
            tank.getTurret().fire();
        }
    }

    void spawnBullet(MathClasses::Vector3 pos, float rot) {
        Bullet* oldPtr = bullets;

        bulletCount++;
        bullets = new Bullet[bulletCount];
        for (int i = 0; i < bulletCount - 1; i++) {
            bullets[i] = oldPtr[i];
        }
        delete[] oldPtr;

        bullets[bulletCount - 1] = Bullet(pos, rot);
    }

    void despawnBullet(int index) {
        Bullet* oldPtr = bullets;

        bulletCount--;
        bullets = new Bullet[bulletCount];
        for (int i = 0, j = 0; i < bulletCount; i++, j++) {
            if (j == index) {
                j++;
            }
            
            bullets[i] = oldPtr[j];
        }
        delete[] oldPtr;
    }

    void processCollisions() {
        MathClasses::Vector3 tankPos = tank.getWorldPos();
        MathClasses::Vector3 bulletPos;

        int count = 0;
        int* despawnQueue = nullptr;

        for (int i = 0; i < bulletCount; i++) {
            bulletPos = bullets[i].getWorldPos();

            if ((tankPos - bulletPos).Magnitude() < 20) {
                int* oldPtr = despawnQueue;
                count++;
                despawnQueue = new int[count];
                for (int i = 0; i < count - 1; i++) {
                    despawnQueue[i] = oldPtr[i];
                }
                delete[] oldPtr;
                despawnQueue[count - 1] = i;

                tank.destroy();
            }

            if (bulletPos.x < 0 || bulletPos.x > screenWidth) {
                bullets[i].bounce(acos(-1) / 2);
            }

            if (bulletPos.y < 0) {
                bullets[i].bounce(0);
            }

            if (bulletPos.y > screenHeight) {
                int* oldPtr = despawnQueue;
                count++;
                despawnQueue = new int[count];
                for (int i = 0; i < count - 1; i++) {
                    despawnQueue[i] = oldPtr[i];
                }
                delete[] oldPtr;
                despawnQueue[count - 1] = i;
            }

            for (int j = 0; j < bricksTall; j++) {
                for (int n = 0; n < bricksWide; n++) {
                    if (bricks[j][n].checkCollision(bulletPos)) {
                        bricks[j][n].destroy();
                        score += 80;

                        MathClasses::Vector3 v = bulletPos - bricks[j][n].getCentrePos();

                        if (abs(v.y / v.x) < 1) {
                            bullets[i].bounce(acos(-1) / 2);
                        }
                        else {
                            bullets[i].bounce(0);
                        }
                    }
                }
            }
        }

        for (int i = 0; i < count; i++) {
            despawnBullet(despawnQueue[i]);
        }
        delete[] despawnQueue;
    }

    void update() {
        Turret& turret = tank.getTurret();

        if (turret.isFiring()) {
            spawnBullet(turret.getWorldPos() + (turret.getWorldUnitDir() * turret.getLength()), turret.getWorldRot());
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

        DrawText(std::string("Score: " + std::to_string(score)).c_str(), 20, 10, 20, LIGHTGRAY);

        DrawText(std::string("Bullets: " + std::to_string(bulletCount)).c_str(), 200, 10, 20, LIGHTGRAY);
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