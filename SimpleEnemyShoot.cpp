#include "BasicEnemyBullet.h"
#include "SimpleEnemyShoot.h"
#include "BulletStage.h"
#include <cmath>

SimpleEnemyShoot SimpleEnemyShoot::getInstance(float dt) {
    static SimpleEnemyShoot shoot(dt);
    return shoot;
}

void SimpleEnemyShoot::operator() (BulletStage* stage, vec2f position) {

    float jumpRate = 360/30.0;

    vec2f basePos(0, 20);
    vec2f baseDir(0, 1);

    float baseSpeed = 240;
    float speed1 = baseSpeed;
    float speed2 = baseSpeed / 5 * 4;
    float speed3 = baseSpeed * 1.5;
    float speed4 = speed2 * 2.5;
    //float speed5 = speed3 / 2;

    sf::Color blue(0, 170, 255);
    sf::Color green(170, 255, 0);

    for(int i=0; i<30; i++)
    {
        float blueAngle = bluePos + (i*jumpRate);
        vec2f actualBluePos = rotate(basePos, blueAngle);
        vec2f actualBlueDir = rotate(baseDir, blueAngle);

        float greenAngle = greenPos + (i*jumpRate);
        vec2f actualGreenPos = rotate(basePos, greenAngle);
        vec2f actualGreenDir = rotate(baseDir, greenAngle);

        stage->addEnemyBullet(new BasicEnemyBullet(stage, position+actualBluePos, actualBlueDir, speed1, blue));
        stage->addEnemyBullet(new BasicEnemyBullet(stage, position+actualBluePos, actualBlueDir, speed2, blue));
        stage->addEnemyBullet(new BasicEnemyBullet(stage, position+actualBluePos, actualBlueDir, speed3, green));
        stage->addEnemyBullet(new BasicEnemyBullet(stage, position+actualBluePos, actualBlueDir, speed4, green));
        //stage->addEnemyBullet(new BasicEnemyBullet(stage, position+actualGreenPos, actualGreenDir, speed2, green));
        //stage->addEnemyBullet(new BasicEnemyBullet(stage, position+actualBluePos, actualBlueDir, speed3, blue));
        //stage->addEnemyBullet(new BasicEnemyBullet(stage, position+actualGreenPos, actualGreenDir, speed4, green));
    }

}
