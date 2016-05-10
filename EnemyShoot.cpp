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
  
    else
    {
		float rotateRate = 360 / 20.0 + 5;

		bluePos += rotateRate * dt;
		if (bluePos>360)
			bluePos -= 360;

		float jumpRate = 5000 / 10.0;

		vec2f basePos(0, 10);
		vec2f baseDir(0, 1);

		float baseSpeed = 1;
		float speed1 = baseSpeed;

		sf::Color blue(0, 170, 255);

		for (int i = 0; i <= 1; i++)
		{
			float speed1 = baseSpeed * ((i + 100));
			if (i != 0)
			{
				speed1 = speed1*(i * 200);
			}
			for (int j = 0; j < 30; j++)
			{
				float blueAngle = bluePos + (j*jumpRate);
				vec2f actualBluePos = rotate(basePos, blueAngle);
				vec2f actualBlueDir = rotate(baseDir, blueAngle);
				stage->addEnemyBullet(new BasicEnemyBullet(stage, position + actualBluePos, actualBlueDir, speed1, blue, vec2f(10, 1)));

			}
        }
    }

}
