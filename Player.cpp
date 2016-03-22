#include "Player.h"
#include "BulletStage.h"
#include "PlayerMove.h"
#include <iostream>
#include <cstdlib>
#include <SFML/Graphics.hpp>

Player::Player(BulletStage* stage):
    Entity(stage),
    shootGap(1/10.0),
    shootCount(0),
    move(PlayerMove::getInstance()),
    shoot(PlayerShoot::getInstance()),
    position(stage->getPosition()+vec2f(0, 200)),
    dimension(vec2f(20, 30)), speed(300),
    deathCount(0),
    invulTime(0)
{
    this->stage = stage;

    hitbox.setRadius(3);
    hitbox.setOrigin(3, 3);
    hitbox.setFillColor(sf::Color::White);

    showbox.setSize(dimension);
    showbox.setOrigin(dimension/(float)2.0);
    showbox.setFillColor(sf::Color::Blue);
}

void Player::update(float dt) {
    static int ticker = -1;
    ticker = (ticker+1)%3;
    if(isInvul() && ticker==0)
        showbox.setFillColor(sf::Color(128, 128, 255));
    else
        showbox.setFillColor(sf::Color::Blue);

    invulTime = std::max(0.0f, invulTime-dt);
    shootCount = std::min(shootGap, shootCount+dt);
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Z) && shootCount==shootGap)
    {
        shoot(stage, position);
        shootCount = 0;
    }

    move(this, dt);
    position = this->stage->clamp(position, dimension);
    hitbox.setPosition(position);
    showbox.setPosition(position);
}

void Player::draw(sf::RenderWindow& window) const {
    window.draw(showbox);
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
        window.draw(hitbox);
}

void Player::die() {
    deathCount++;
    invulTime = 2.5;
    position = stage->getPosition()+vec2f(0, 200);
}

bool Player::checkCollission (const vec2f& position, const vec2f& dimension) const {
    vec2f disp = this->position-position;
    float dist = mag(disp);
    float selfDist = hitbox.getRadius()/2;
    float otherDist = dimension.x/2;

    return ((selfDist+otherDist)>dist);
}
