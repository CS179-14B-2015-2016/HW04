#include "BasicPlayerBullet.h"
#include "BulletStage.h"
#include "Vector2Plus.h"

BasicPlayerBullet::BasicPlayerBullet(BulletStage* stage, vec2f position, vec2f direction):
    PlayerBullet(stage),
    move(StraightMovement::getInstance()),
    position(position),
    dimension(vec2f(15, 15)),
    direction(direction),
    speed(500),
    spin(0) {
    this->position = position;
    this->stage = stage;

    box.setSize(dimension);
    box.setOrigin(dimension/2.0f);
    box.setFillColor(sf::Color::Red);
}

void BasicPlayerBullet::update(float dt) {
    spin += dt*360.0*2;
    if(spin-360>-EPS) spin -= 360;
    move(this, dt);
    box.setRotation(spin);
    box.setPosition(position);
}

void BasicPlayerBullet::draw(sf::RenderWindow& window) const {
    window.draw(box);
}
