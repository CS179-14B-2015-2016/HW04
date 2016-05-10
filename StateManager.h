#ifndef STATEMANAGER_H_INCLUDED
#define STATEMANAGER_H_INCLUDED

#include <vector>
#include "State.h"
#include "Vector2Plus.h"

class StateManager {
private:
    std::vector<State*> game_states;
    std::vector<State*> on_stack;
public:
    StateManager() {}
    ~StateManager();
    void push(unsigned int id, std::string pass="");
    void pop(unsigned int level=1, std::string pass="");
    void handleInput(const vec2i& mouse);
    void update(float dt);
    void render(sf::RenderWindow& window);
    void addState(State* s);
};

#endif // STATEMANAGER_H_INCLUDED
