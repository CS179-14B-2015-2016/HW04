#ifndef STATE_H_INCLUDED
#define STATE_H_INCLUDED
#include <SFML/Graphics.hpp>
#include "Vector2Plus.h"

class StateManager;
class State
{
protected:
    StateManager* sm;
    bool is_active;

    void popSelf(unsigned int level=1, std::string pass="");
public:
    State(StateManager* sm): sm(sm) {}
    virtual ~State() {};
    virtual void handleInput(const vec2i& mouse) = 0;
    virtual void update(float dt) = 0;
    virtual void render(sf::RenderWindow& window) = 0;

    // after getting on top
    virtual void onActivate(std::string pass=""){}
    // before getting out of top
    virtual void onDeactivate(){}
};

#endif // STATE_H_INCLUDED
