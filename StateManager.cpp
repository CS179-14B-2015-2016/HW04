#include "StateManager.h"
#include <cassert>

StateManager::~StateManager() {
    while(!on_stack.empty())
        on_stack.pop_back();
    while(!game_states.empty()) {
        State* s = game_states.back();
        game_states.pop_back();
        delete s;
    }
}

void StateManager::push(unsigned int id, std::string pass) {
    if(!on_stack.empty())
        on_stack.back()->onDeactivate();
    on_stack.push_back( game_states[id] );
    on_stack.back()->onActivate( pass );
}

void StateManager::pop(unsigned int level, std::string pass) {
    if(on_stack.empty()) return;
    on_stack.back()->onDeactivate();
    unsigned int count = level;
    while(count-->0 && !on_stack.empty())
    {
        on_stack.pop_back();
    }
    if(!on_stack.empty())
        on_stack.back()->onActivate( pass );
}

void StateManager::handleInput(const vec2i& mouse) {
    assert(!on_stack.empty());
    on_stack.back()->handleInput(mouse);
}

void StateManager::update(float dt) {
    assert(!on_stack.empty());
    on_stack.back()->update(dt);
}

void StateManager::render(sf::RenderWindow& window) {
    assert(!on_stack.empty());
    on_stack.back()->render(window);
}

void StateManager::addState(State* s) {
    if(s==0) return;
    game_states.push_back(s);
}
