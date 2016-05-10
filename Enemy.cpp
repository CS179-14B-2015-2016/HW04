#include "Enemy.h"
#include "BulletStage.h"
#include <iostream>
#include <cstdlib>
#include <SFML/Graphics.hpp>

Enemy::Enemy(BulletStage* stage):
    Entity(stage),
    shootGap(1/10.0f),
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

void Enemy::update(float dt)
{
    float ratioHP = (1.0f*remHP)/maxHP;
    healthBar.setSize(vec2f(480.0*ratioHP, 10));
    shootCount = std::min(shootGap, shootCount+dt);
    if(shootCount==shootGap && move.counter <4)
    {
        stage->isFirstStage = true;
        shoot(stage, position);
        shootCount = 0;
    }
    else if (shootCount == shootGap && move.counter>=4)
    {
        stage->isFirstStage = false;
        shoot(stage,position);
		shootCount = 0;
    }
    move(this, dt);


    position = this->stage->clamp(position, dimension);
    showbox.setPosition(position);
}

void Enemy::draw(sf::RenderWindow& window) const
{
    window.draw(showbox);
    window.draw(healthBar);
}
