#include "BasicPlayerBullet.h"
#include "PlayerShoot.h"
#include "BulletStage.h"

PlayerShoot PlayerShoot::getInstance() {
    static PlayerShoot shoot;
    return shoot;
}

void PlayerShoot::operator() (BulletStage* stage, vec2f position) {
    vec2f bulletA = position;
    vec2f bulletB = position + vec2f(12, 0);
    vec2f bulletC = position + vec2f(-12, 0);
    vec2f tiltA(0, -1);
    vec2f tiltB(1, -7);
    vec2f tiltC(-1, -7);

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)) {
        tiltC = tiltB = tiltA;
    }
    //std::cout << "final pos: " << bulletB.x << ", " << bulletC.x << std::endl;
    stage->addPlayerBullet(new BasicPlayerBullet(stage, bulletA, tiltA));
    stage->addPlayerBullet(new BasicPlayerBullet(stage, bulletB, tiltB));
    stage->addPlayerBullet(new BasicPlayerBullet(stage, bulletC, tiltC));
}
