#ifndef BASICENEMYBULLET_H_INCLUDED
#define BASICENEMYBULLET_H_INCLUDED

#include "EnemyBullet.h"
#include "StraightMovement.h"
#include <SFML/Graphics.hpp>

class BasicEnemyBullet: public EnemyBullet {
    friend class MoveBehavior;
private:
    BulletStage* stage;
    StraightMovement move;
    vec2f position;
    vec2f dimension;
    vec2f direction;
    float speed, damage;
    sf::CircleShape bullet;
public:
    BasicEnemyBullet(BulletStage* stage, vec2f position, vec2f direction, float speed, sf::Color color);
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
};

#endif // BASICENEMYBULLET_H_INCLUDED
