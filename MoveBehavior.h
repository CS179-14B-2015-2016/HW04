#ifndef MOVEBEHAVIOR_H_INCLUDED
#define MOVEBEHAVIOR_H_INCLUDED

class Entity;
class MoveBehavior {
public:
    virtual void operator() (Entity* ent, float dt) = 0;
};



#endif // MOVEBEHAVIOR_H_INCLUDED
