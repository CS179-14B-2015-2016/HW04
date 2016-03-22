#include "BasicEnemyBullet.h"
#include "BulletStage.h"
#include "Vector2Plus.h"

BasicEnemyBullet::BasicEnemyBullet(BulletStage* stage, vec2f position, vec2f direction, vec2f dimension, float speed, sf::Color color):
    EnemyBullet(stage),
    move(StraightMovement::getInstance()),
    position(position),
    dimension(dimension),
    direction(direction),
    speed(speed)
    {
    this->position = position;
    this->stage = stage;

    bullet.setRadius(dimension.x/2.0f);
    bullet.setOrigin(dimension/2.0f);
    bullet.setFillColor(color);
}

void BasicEnemyBullet::update(float dt) {
    move(this, dt);
    bullet.setPosition(position);
}

void BasicEnemyBullet::draw(sf::RenderWindow& window) const {
    window.draw(bullet);
}
