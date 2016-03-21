#include "BasicEnemyBullet.h"
#include "EnemyShoot.h"
#include "BulletStage.h"
EnemyShoot EnemyShoot::getInstance(float dt)
{
    static EnemyShoot shoot(dt);
    return shoot;
}

void EnemyShoot::operator() (BulletStage* stage, vec2f position)
{


    if(stage->isFirstStage)
    {
        float rotateRate = 360/15.0 + 5;
        greenPos -= rotateRate * dt;

        if(greenPos<0)
            greenPos += 360;
        bluePos += rotateRate * dt;
        if(bluePos>360)
            bluePos -= 360;

        float jumpRate = 360/8.0;

        vec2f basePos(0, 20);
        vec2f baseDir(0, 1);

        float baseSpeed = 240;
        float speed1 = baseSpeed;
        float speed2 = baseSpeed / 5 * 4;
        float speed3 = baseSpeed / 3 * 2;
        float speed4 = speed2 / 4 * 3;

        sf::Color blue(0, 170, 255);
        sf::Color green(170, 255, 0);

        for(int i=0; i<8; i++)
        {
            float blueAngle = bluePos + (i*jumpRate);
            vec2f actualBluePos = rotate(basePos, blueAngle);
            vec2f actualBlueDir = rotate(baseDir, blueAngle);

            float greenAngle = greenPos + (i*jumpRate);
            vec2f actualGreenPos = rotate(basePos, greenAngle);
            vec2f actualGreenDir = rotate(baseDir, greenAngle);

            stage->addEnemyBullet(new BasicEnemyBullet(stage, position+actualBluePos, actualBlueDir, speed1, blue,vec2f(10, 10)));
            stage->addEnemyBullet(new BasicEnemyBullet(stage, position+actualGreenPos, actualGreenDir, speed2, green,vec2f(10, 10)));
            stage->addEnemyBullet(new BasicEnemyBullet(stage, position+actualBluePos, actualBlueDir, speed3, blue,vec2f(10, 10)));
            stage->addEnemyBullet(new BasicEnemyBullet(stage, position+actualGreenPos, actualGreenDir, speed4, green,vec2f(10, 10)));
        }
    }
    //Spiriting Away
    else
    {
        float jumpRate = 360/30.0;

        vec2f basePos(0, 0);
        vec2f baseDir(0, 1);

        float baseSpeed = 240;

        sf::Color blue(0, 170, 255);
        sf::Color green(170, 255, 0);
        sf::Color red(255,0,0);
        sf::Color violet(249,192,255);

        //Circle Bullet creation
        for(int i = 0; i <= 4; i++)
        {
            float speed1 = baseSpeed/((i+1));
            if(i != 0)
            {
                speed1 = speed1*(i*2);
            }
            for(int j = 0; j < 30; j++)
            {
                float blueAngle = bluePos + (j*jumpRate);
                vec2f actualBluePos = rotate(basePos, blueAngle);
                vec2f actualBlueDir = rotate(baseDir, blueAngle);
                stage->addEnemyBullet(new BasicEnemyBullet(stage, position+actualBluePos, actualBlueDir, speed1, blue,vec2f(10, 10)));

            }
        }
        //Trinity Force Bullet creation
        for(int i = 0; i < 3; i++)
        {
            //0, 120, 240
            float trinPos = 120*i;

            //mini slow bullets
            for(int j = 1; j <= 2; j++)
            {
                float trinAngle = trinPos;
                vec2f actualTrinAngle = rotate(basePos, trinAngle);
                stage->addEnemyBullet(new BasicEnemyBullet(stage, position+actualTrinAngle, rotate(baseDir, trinAngle+5), 180*j, green,vec2f(15, 15)));
                stage->addEnemyBullet(new BasicEnemyBullet(stage, position+actualTrinAngle, rotate(baseDir, trinAngle+2), 210*j, green,vec2f(15, 15)));
                stage->addEnemyBullet(new BasicEnemyBullet(stage, position+actualTrinAngle, rotate(baseDir, trinAngle+3), 190*j, green,vec2f(15, 15)));
                stage->addEnemyBullet(new BasicEnemyBullet(stage, position+actualTrinAngle, rotate(baseDir, trinAngle+1), 180*j, green,vec2f(15, 15)));
                stage->addEnemyBullet(new BasicEnemyBullet(stage, position+actualTrinAngle, rotate(baseDir, trinAngle), 150*j, green,vec2f(15, 15)));
                stage->addEnemyBullet(new BasicEnemyBullet(stage, position+actualTrinAngle, rotate(baseDir, trinAngle+-2),160*j, green,vec2f(15, 15)));
                stage->addEnemyBullet(new BasicEnemyBullet(stage, position+actualTrinAngle, rotate(baseDir, trinAngle-4), 230*j, green,vec2f(15, 15)));
                stage->addEnemyBullet(new BasicEnemyBullet(stage, position+actualTrinAngle, rotate(baseDir, trinAngle+3), 195*j, green,vec2f(15, 15)));
            }



             //medium bullets
            for(int j = 0; j < 1; j++)
            {
                float trinAngle = trinPos;
                vec2f actualTrinAngle = rotate(baseDir, trinAngle);
                stage->addEnemyBullet(new BasicEnemyBullet(stage, position+actualTrinAngle, rotate(baseDir, trinAngle+15), 180, violet,vec2f(30, 30)));
                stage->addEnemyBullet(new BasicEnemyBullet(stage, position+actualTrinAngle, rotate(baseDir, trinAngle+12), 210, violet,vec2f(30, 30)));
                stage->addEnemyBullet(new BasicEnemyBullet(stage, position+actualTrinAngle, rotate(baseDir, trinAngle+13), 190, violet,vec2f(30, 30)));
                stage->addEnemyBullet(new BasicEnemyBullet(stage, position+actualTrinAngle, rotate(baseDir, trinAngle+11), 180, violet,vec2f(30, 30)));
                stage->addEnemyBullet(new BasicEnemyBullet(stage, position+actualTrinAngle, rotate(baseDir, trinAngle+0), 150, violet,vec2f(30, 30)));
                stage->addEnemyBullet(new BasicEnemyBullet(stage, position+actualTrinAngle, rotate(baseDir, trinAngle+-12),160, violet,vec2f(30, 30)));
                stage->addEnemyBullet(new BasicEnemyBullet(stage, position+actualTrinAngle, rotate(baseDir, trinAngle-14), 230, violet,vec2f(30, 30)));
                stage->addEnemyBullet(new BasicEnemyBullet(stage, position+actualTrinAngle, rotate(baseDir, trinAngle+13), 195, violet,vec2f(30, 30)));
            }

            //Huge bullet
            for(int j = 0; j < 1; j++)
            {
                float trinAngle = trinPos;
                vec2f actualTrinAngle = rotate(basePos, trinAngle);
                vec2f actualTrinDir = rotate(baseDir, trinAngle);
                stage->addEnemyBullet(new BasicEnemyBullet(stage, position+actualTrinAngle, actualTrinDir, 300, red,vec2f(50, 50)));
            }

        }
    }

}
