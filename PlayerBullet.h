#ifndef PLAYERBULLET_H_INCLUDED
#define PLAYERBULLET_H_INCLUDED

#include "Entity.h"

class PlayerBullet: public Entity {
    friend class MoveBehavior;
protected:
    BulletStage* stage;
    vec2f position;
    vec2f dimension;
    vec2f direction;
    float speed, damage;
public:
    PlayerBullet(BulletStage* stage): Entity(stage) {}
    virtual void update(float dt) override = 0;
    virtual void draw(sf::RenderWindow& window) const override = 0;

    virtual float getSpeed() const = 0;
    virtual vec2f getPosition() const = 0;
    virtual void setPosition(const vec2f position) = 0;
    virtual vec2f getDirection() const = 0;
    virtual vec2f getDimension() const = 0;
};


#endif // PLAYERBULLET_H_INCLUDED
