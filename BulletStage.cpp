#include "BulletStage.h"
#include <cmath>
#include <iostream>

BulletStage::BulletStage(): dimension(vec2f(490, 690)), position(vec2f(5, 5) + dimension/2.0f), player(this), enemy(this) {
    innerBox.setFillColor(sf::Color::Black);
    innerBox.setSize(dimension);
    innerBox.setOrigin(dimension/2.0f);
    innerBox.setPosition(position);
}

void BulletStage::reset() {

    player = Player(this);
    enemy = Enemy(this);

    while(player_bullet.size()>0) {
        delete player_bullet[0];
        player_bullet.erase(player_bullet.begin());
    }

    while(enemy_bullet.size()>0) {
        delete enemy_bullet[0];
        enemy_bullet.erase(enemy_bullet.begin());
    }

    std::vector<PlayerBullet*> player_bullet;
    std::vector<EnemyBullet*> enemy_bullet;

    innerBox.setFillColor(sf::Color::Black);
    innerBox.setSize(dimension);
    innerBox.setOrigin(dimension/2.0f);
    innerBox.setPosition(position);
}

void BulletStage::handleInput(const vec2i& mouse) {

}

void BulletStage::update(float dt) {
    enemy.update(dt);
    player.update(dt);
    for(int i=0; i<player_bullet.size(); i++)
    {
        PlayerBullet* pb = player_bullet[i];
        pb->update(dt);
        vec2f pos = pb->getPosition();
        vec2f margin = pb->getDimension() * -2.0f;

        bool hitEnemy = enemy.checkCollission(pb->getPosition(), pb->getDimension());
        if(hitEnemy)
            enemy.getDamaged(pb->getDamage());

        if(hitEnemy || clamp(pos, margin)!=pos) {
            delete player_bullet[i];
            player_bullet.erase(player_bullet.begin()+i);
            i--;
        }
    }

    bool died = false;
    bool deathRecorded = false;
    for(int i=0; i<enemy_bullet.size(); i++)
    {
        EnemyBullet* eb = enemy_bullet[i];
        eb->update(dt);
        vec2f pos = eb->getPosition();
        vec2f margin = eb->getDimension() * -2.0f;

        if(!deathRecorded) {
            bool died = player.checkCollission(eb->getPosition(), eb->getDimension()) && !player.isInvul();
            if(died) {
                deathRecorded = true;
                player.die();
            }
        }

        if(clamp(pos, margin)!=pos) {
            delete enemy_bullet[i];
            enemy_bullet.erase(enemy_bullet.begin()+i);
            i--;
        }
    }
    if(deathRecorded)
    {
        while(enemy_bullet.size()>0) {
            delete enemy_bullet[0];
            enemy_bullet.erase(enemy_bullet.begin());
        }
    }
}

void BulletStage::render(sf::RenderWindow& window) const {
    window.draw(innerBox);

    for(PlayerBullet* pb: player_bullet)
        pb->draw(window);

    player.draw(window);

    for(EnemyBullet* eb: enemy_bullet)
        eb->draw(window);

    enemy.draw(window);
}


vec2f BulletStage::clamp(const vec2f point, const vec2f dimension) const {
    vec2f boxDim = this->dimension;
    float top = position.y -(boxDim.y/2.0) + dimension.y/2.0;
    float bottom = position.y + (boxDim.y/2.0) - dimension.y/2.0;
    float left = position.x - (boxDim.x/2.0) + dimension.x/2.0;
    float right = position.x + (boxDim.x/2.0) - dimension.x/2.0;
    float trueX = std::min(right, std::max(left, point.x));
    float trueY = std::min(bottom, std::max(top, point.y));
    return vec2f(trueX, trueY);
}

void BulletStage::addPlayerBullet(PlayerBullet* pb) {
    player_bullet.push_back(pb);
}

void BulletStage::addEnemyBullet(EnemyBullet* pb) {
    enemy_bullet.push_back(pb);
}
