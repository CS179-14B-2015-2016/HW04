#ifndef BASICPLAYERBULLET_H_INCLUDED
#define BASICPLAYERBULLET_H_INCLUDED

#include "PlayerBullet.h"
#include "StraightMovement.h"
#include <SFML/Graphics.hpp>

class BasicPlayerBullet: public PlayerBullet {
    friend class MoveBehavior;
private:
    BulletStage* stage;
    StraightMovement move;
    vec2f position;
    vec2f dimension;
    vec2f direction;
    float speed, damage, spin;
    sf::RectangleShape box;
public:
    BasicPlayerBullet(BulletStage* stage, vec2f position, vec2f direction);
    void update(float dt) override;
    void draw(sf::RenderWindow& window) const override;
    virtual void setDirection(const vec2f direction) {
        this->direction = direction;
    }
    virtual float getSpeed() const {
        return speed;
    }
    virtual vec2f getPosition() const {
        return position;
    }
    virtual void setPosition(const vec2f position) {
        this->position = position;
    }
    virtual vec2f getDirection() const {
        return direction;
    }
    virtual vec2f getDimension() const {
        return dimension;
    }
    virtual float getDamage() const override {
        return damage;
    }
};

#endif // BASICPLAYERBULLET_H_INCLUDED
