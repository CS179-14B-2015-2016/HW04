#include "PlayerMove.h"
#include "Vector2Plus.h"
#include <SFML/Graphics.hpp>
#include "Entity.h"
#include <iostream>

PlayerMove PlayerMove::getInstance() {
    static PlayerMove move;
    return move;
}

void PlayerMove::operator() (Entity* ent, float dt) {
    vec2f direction(0, 0);
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        direction += vec2f(0, -1);
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        direction += vec2f(0, 1);
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        direction += vec2f(-1, 0);
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        direction += vec2f(1, 0);
    float magn = mag<float>(direction);
    if(magn>0)
        direction /= magn;
    ent->setDirection(direction);
    float speed = ent->getSpeed();

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)) {
        speed /= 2.0;
    }

    direction *= speed;
    vec2f position = ent->getPosition() + (direction*dt);
    ent->setPosition(position);
}
