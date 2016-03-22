#include "BasicEnemyBullet.h"
#include "SpellCardShoot.h"
#include "Enemy.h"
#include "BulletStage.h"

SpellCardShoot* SpellCardShoot::getInstance(float dt, Enemy* e) {
    static SpellCardShoot shoot(dt, e);
    return &shoot;
}

void SpellCardShoot::operator() (BulletStage* stage, vec2f position) {
    float maxHP = e->getTotalHP();
    float remHP = e->getRemainingHP();
    float percentage = remHP/maxHP;
    vec2f spawnPos = position;
    float baseSpeed = 160;

    if(percentage <= 1.00) {
        float jumpRate = (360/3.0);
        bulletDeg[0] += dt*(jumpRate-18);
        if(bulletDeg[0]>360) bulletDeg[0] -= 360;

        sf::Color color(102, 194, 255);
        float speed = baseSpeed;
        vec2f direction(0, -1);
        for(int i=0; i<7; i++) {
            float deg = bulletDeg[0] - (i*dt*jumpRate);
            if(deg<0) deg += 360;
            vec2f thisDir = rotate(direction, deg);
            stage->addEnemyBullet(new BasicEnemyBullet(stage, position, thisDir,  vec2f(8, 8), speed, color));
        }
    }
    if(percentage <= 0.90) {

    }
    if(percentage <= 0.70) {

    }
    if(percentage <= 0.50) {
    }

    if(percentage <= 0.40) {

    }
    if(percentage <= 0.20) {

    }
    if(percentage <= 0.10) {

    }
}
