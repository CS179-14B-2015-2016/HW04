#include "Enemy.h"
#include "BulletStage.h"
#include <iostream>
#include <cstdlib>
#include <SFML/Graphics.hpp>

Enemy::Enemy(BulletStage* stage):
    Entity(stage),
    shootGap(1/10.0),
    shootCount(0),
    move(BasicEnemyMove::getInstance()),
    shoot(EnemyShoot::getInstance(shootGap)),
    position(stage->getPosition()+vec2f(0, -200)),
    dimension(vec2f(20, 30)), speed(50),
    maxHP(1000)
{
    this->stage = stage;
    remHP = maxHP;

    showbox.setSize(dimension);
    showbox.setOrigin(dimension/(float)2.0);
    showbox.setFillColor(sf::Color::Magenta);

    healthBar.setPosition(10, 10);
    healthBar.setFillColor(sf::Color::White);
}

void Enemy::update(float dt) {
    float ratioHP = (1.0f*remHP)/maxHP;

    healthBar.setSize(vec2f(480.0*ratioHP, 10));
    shootCount = std::min(shootGap, shootCount+dt);
    if(shootCount==shootGap)
    {
        shoot(stage, position);
        shootCount = 0;
    }

    move(this, dt);
    position = this->stage->clamp(position, dimension);
    showbox.setPosition(position);
}

void Enemy::draw(sf::RenderWindow& window) const {
    window.draw(showbox);
    window.draw(healthBar);
}


bool Enemy::checkCollission (const vec2f& position, const vec2f& dimension) const {
    vec2f disp = this->position-position;

    float farthestX = std::min(std::max(position.x, (float)(this->position.x+(this->dimension.x/4.0))), (float) (this->position.x-(this->dimension.x/4.0)));
    float dist = mag(disp);
    float farthestY = std::min(std::max(position.y, (float)(this->position.y+(this->dimension.y/4.0))), (float) (this->position.y-(this->dimension.y/4.0)));

    float selfDist = mag(vec2f(farthestX, farthestY)-this->position);
    float otherDist = dimension.x;

    return ((selfDist+otherDist)>dist);
}
