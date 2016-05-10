#include "BasicEnemyMove.h"
#include "Vector2Plus.h"
#include <SFML/Graphics.hpp>
#include "Entity.h"
#include <iostream>
#include <algorithm>

BasicEnemyMove BasicEnemyMove::getInstance()
{
    static BasicEnemyMove move;
    return move;
}


void BasicEnemyMove::operator() (Entity* ent, float dt)
{
    if(counter < 4)
    {
        if(first)
        {
          direction = vec2f(1,0);
          first = false;
        }
        if(wait>0)
        {
            wait = std::max(0.0f, wait-dt);
            if(wait==0)
                time = 6;
            isWaiting = false;
        }
        else if (time>0)
        {
            vec2f orig = ent->getPosition();
            orig += ent->getSpeed()*dt*direction;
            ent->setPosition(orig);
            time = std::max(0.0f, time-dt);
            if(time==0)
            {
                wait = 1;
                isWaiting = true;
                direction = direction*-1.0f;
                counter++;
                if(counter >=4)
                {
                    first = true;
                }
            }
        }
    }
    else
    {

        if(first)
        {
          direction = vec2f(1,2);
          first = false;
        }


        if(counter >= 8)
        {
            counter = 0;
            first = true;
        }



        if(wait>0)
        {
            wait = std::max(0.0f, wait-dt);
            if(wait==0)
                time = 3;
            isWaiting = false;
        }

        else if (time>0)
        {
            vec2f orig = ent->getPosition();
            orig += ent->getSpeed()*dt*direction;
            ent->setPosition(orig);
            time = std::max(0.0f, time-dt);
            if(time==0)
            {
                wait = 1;
                isWaiting = true;
                direction = direction*-1.0f;
                counter++;
            }
        }


    }
}
