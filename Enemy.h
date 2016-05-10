#ifndef ENEMY_H_INCLUDED
#define ENEMY_H_INCLUDED

#include "Entity.h"
#include "EnemyShoot.h"
#include "BasicEnemyMove.h"

class BulletStage;
class Enemy: public Entity {
    friend class MoveBehavior;
private:
    float shootGap;
    float shootCount;
    BulletStage* stage;
    EnemyShoot shoot;
    BasicEnemyMove move;
    sf::RectangleShape showbox;
    sf::RectangleShape healthBar;
    vec2f position, dimension, direction;
    float speed, remHP, maxHP;
public:
    Enemy(BulletStage* stage);
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
    float getRemainingHP() const {
        return remHP;
    }
    float getTotalHP() const {
        return maxHP;
    }
    void getDamaged(float d) {
        remHP -= d;
    }
};

#endif // ENEMY_H_INCLUDED
