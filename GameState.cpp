#include "StateSubclass.h"
#include <iostream>

GameState::GameState(StateManager* sm): sm(sm) {
    sf::Color color(214, 153, 255);

    topBorder.setSize(vec2f(700, 5));
    bottomBorder.setSize(vec2f(700, 5));
    leftBorder.setSize(vec2f(5, 700));
    rightBorder.setSize(vec2f(205, 700));

    topBorder.setPosition(0, 0);
    bottomBorder.setPosition(0, 695);
    leftBorder.setPosition(0, 0);
    rightBorder.setPosition(495, 0);

    topBorder.setFillColor(color);
    bottomBorder.setFillColor(color);
    leftBorder.setFillColor(color);
    rightBorder.setFillColor(color);

    deathFont.loadFromFile("asset/font/yuyuko.ttf");
    countFont.loadFromFile("asset/font/CFSamuraiBob.ttf");

    deathText.setFont(countFont);
    deathText.setString("LIVES LOST");
    deathText.setCharacterSize(40);
    deathText.setOrigin(deathText.getLocalBounds().width/2 , 25);
    deathText.setPosition(600, 50);

    countText.setFont(deathFont);
    countText.setString("0");
    countText.setCharacterSize(30);
    countText.setOrigin(countText.getLocalBounds().width/2 , 25);
    countText.setPosition(600, 100);

    deathText.setColor(sf::Color::Black);
    countText.setColor(sf::Color::Black);
}

void GameState::onActivate(std::string pass) {

}

void GameState::handleInput(const vec2i& mouse) {
    stage.handleInput(mouse);
}

void GameState::update(float dt) {
    stage.update(dt);
}

void GameState::render(sf::RenderWindow& window) {
    stage.render(window);

    window.draw(topBorder);
    window.draw(bottomBorder);
    window.draw(leftBorder);
    window.draw(rightBorder);

    window.draw(deathText);
    window.draw(countText);
}
