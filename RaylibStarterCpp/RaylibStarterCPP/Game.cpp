#include "Game.h"
#include "raylib.h"

Game::Game(int screenWidth, int screenHeight) {
    this->screenWidth = screenWidth;
    this->screenHeight = screenHeight;

    score = 0;
    gameover = false;
    tank = Tank({ (float)screenWidth / 2, (float)screenHeight * 0.90f, 0 }, 0, 20);
    tank.setLevel(this);
    brickMap = BrickMap({ 0, 50, 0 }, 20, 20, 50, 25);
}

void Game::processInputs() {
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
        tank.steer(-5 * (MathClasses::pi / 180));
    }
    if (IsKeyDown(KEY_D)) {
        tank.steer(5 * (MathClasses::pi / 180));
    }

    if (IsKeyDown(KEY_Q)) {
        tank.getTurret().turn(-5 * (MathClasses::pi / 180));
    }
    if (IsKeyDown(KEY_E)) {
        tank.getTurret().turn(5 * (MathClasses::pi / 180));
    }

    if (IsKeyPressed(KEY_SPACE)) {
        tank.getTurret().fire();
    }
}

void Game::spawnBullet(MathClasses::Vector3 pos, float rot) {
    bullets.append(Bullet(pos, rot));
}

void Game::despawnBullet(int index) {
    bullets.remove(index);
}

void Game::processCollisions() {
    MathClasses::Vector3 tankPos = tank.getWorldPos();
    MathClasses::Vector3 bulletPos;

    for (int i = 0; i < bullets.getCount(); i++) {
        bulletPos = bullets[i].getWorldPos();

        if (bulletPos.x < 0 || bulletPos.x > screenWidth) {
            bullets[i].bounce(MathClasses::pi / 2);
        }
        if (bulletPos.y < 0) {
            bullets[i].bounce(0);
        }
        else if (bulletPos.y > screenHeight) {
            despawnQueue.append(i);
        }

        if (tank.isWithinBounds(bulletPos)) {
            despawnQueue.append(i);
            tank.destroy();
        }

        if (brickMap.isWithinBounds(bulletPos) && brickMap.isWithinBrick(bulletPos)) {
            brickMap.destroyBrick(bulletPos);
            bullets[i].bounce(0);
            score += 5;
        }
    }

    for (int i = 0; i < despawnQueue.getCount(); i++) {
        despawnBullet(despawnQueue[i]);
    }
    despawnQueue.clear();
}

void Game::update() {
    if (gameover) {
        return;
    }

    processInputs();
    tank.update();

    for (int i = 0; i < bullets.getCount(); i++) {
        bullets[i].update();
    }
    processCollisions();

    if (!tank.isActive()) {
        gameover = true;
    }
}

void Game::draw() {
    brickMap.draw();
    tank.draw();

    for (int i = 0; i < bullets.getCount(); i++) {
        bullets[i].draw();
    }

    DrawText(std::string("Score: " + std::to_string(score)).c_str(), 20, 10, 20, LIGHTGRAY);
    DrawText(std::string("Bullets Active: " + std::to_string(bullets.getCount())).c_str(), 200, 10, 20, LIGHTGRAY);

    if (gameover) {
        DrawText("YOU DIED GAME OVER", (screenWidth - MeasureText("YOU DIED GAME OVER", 70)) / 2, (screenHeight - 70)/ 2, 70, BLACK);
    }
}