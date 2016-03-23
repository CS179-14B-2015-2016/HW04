#ifndef ENTITY_H_INCLUDED
#define ENTITY_H_INCLUDED

#include <SFML/Graphics.hpp>
#include "Vector2Plus.h"
#include "MoveBehavior.h"
#include "ShootBehavior.h"
#include <iostream>

class BulletStage;
class Entity {
    friend class MoveBehavior;
protected:
    BulletStage* stage;
    vec2f position;
    vec2f dimension;
    vec2f direction;
    float speed;
public:
    Entity(BulletStage* stage): stage(stage) {}
    virtual void update(float dt) = 0;
    virtual void draw(sf::RenderWindow& window) const = 0;
    virtual void setDirection(const vec2f direction) {
        this->direction = direction;
    }
    virtual float getSpeed() const = 0;
    virtual vec2f getPosition() const = 0;
    virtual void setPosition(const vec2f position) = 0;
    virtual vec2f getDirection() const = 0;
    virtual vec2f getDimension() const = 0;
};

#endif // ENTITY_H_INCLUDED
