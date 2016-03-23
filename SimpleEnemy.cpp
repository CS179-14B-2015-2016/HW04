#include "SimpleEnemy.h"
#include "BulletStage.h"
#include <iostream>
#include <cstdlib>
#include <SFML/Graphics.hpp>

SimpleEnemy::SimpleEnemy(BulletStage* stage):
    Entity(stage),
    shootGap(3),
    shootCount(0),
    move(SimpleEnemyMovement::getInstance()),
    shoot(SimpleEnemyShoot::getInstance(shootGap)),
    position(stage->getPosition()+vec2f(-200, -331)),
    dimension(vec2f(20, 30)), speed(50),
    maxHP(1000), doubShot(true), appear(false),
    nextShot(50)
{
    this->stage = stage;
    remHP = maxHP;

    showbox.setSize(dimension);
    showbox.setOrigin(dimension/(float)2.0);
    showbox.setFillColor(sf::Color::Black);

    healthBar.setPosition(10, 10);
    healthBar.setFillColor(sf::Color::White);
}

void SimpleEnemy::update(float dt) {
    if(stage->timer > 30)
    {
        showbox.setFillColor(sf::Color::Yellow);
        float ratioHP = (1.0f*remHP)/maxHP;

        healthBar.setSize(vec2f(480.0*ratioHP, 10));
        shootCount = std::min(shootGap, shootCount+dt);
        int xPos = (int) this->getPosition().x;
        if(xPos == nextShot)
        {
            switch(nextShot)
            {
                case 50: nextShot = 20;
                    break;
                case 20: nextShot = 108;
                    break;
                case 108: nextShot = 380;
                    break;
                case 380: nextShot = 470;
                    break;
                case 470: nextShot = 390;
                    break;
                case 390: nextShot = 50;
                    break;
            }
            if(doubShot)
            {
                shoot(stage, position);
                doubShot = false;
            }
        }
        else
        {
            doubShot = true;
        }
        move(this, dt);
        position = this->stage->clamp(position, dimension);
        showbox.setPosition(position);
    }

}

void SimpleEnemy::draw(sf::RenderWindow& window) const {
    window.draw(showbox);
    window.draw(healthBar);
}
