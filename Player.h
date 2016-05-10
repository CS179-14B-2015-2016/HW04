#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED

#include "Entity.h"
#include "PlayerMove.h"
#include "PlayerShoot.h"

class BulletStage;
class Player: public Entity {
    friend class MoveBehavior;
private:
    float shootGap;
    float shootCount;
    BulletStage* stage;
    PlayerMove move;
    PlayerShoot shoot;
    sf::CircleShape hitbox;
    sf::RectangleShape showbox;
    vec2f position, dimension, direction;
    float speed;
public:
    Player(BulletStage* stage);
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

#endif // PLAYER_H_INCLUDED
