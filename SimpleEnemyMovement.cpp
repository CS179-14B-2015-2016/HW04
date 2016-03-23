#include "SimpleEnemyMovement.h"
#include "Vector2Plus.h"
#include <SFML/Graphics.hpp>
#include "Entity.h"
#include <iostream>
#include <algorithm>

SimpleEnemyMovement SimpleEnemyMovement::getInstance() {
    static SimpleEnemyMovement move;
    return move;
}

void SimpleEnemyMovement::operator() (Entity* ent, float dt) {
    if(wait>0) {
        wait = std::max(0.0f, wait-dt);
        if(wait==0)
            time = 3;
    }
    else if (time>0) {
        vec2f orig = ent->getPosition();
        orig += (1/91.f) * direction;
        ent->setPosition(orig);
        time = std::max(0.0f, time-dt);
        if(time==0)
        {
			std::cout<<"Turn: " << turn <<std::endl;
            wait = 2;
            switch(turn){
            case 0:
				direction = vec2f(88, 310);
                break;
            case 1:
                direction = vec2f(272, -631);
                break;
            case 2:
                direction = vec2f(90, 321);
                break;
            case 3:
                direction = vec2f(-80, 310);
                break;
            case 4:
                direction = vec2f(-340, -631);
                break;
            case 5:
				direction = vec2f(-30, 321);
                break;
            }
            turn++;
            if(turn == 6) turn = 0;
            std::cout<<"X: " << orig.x<<std::endl;
            std::cout<<"Y: " << orig.y<<std::endl;
        }
    }
}
