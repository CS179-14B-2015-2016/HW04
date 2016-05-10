#include "StateSubclass.h"

SplashState::SplashState(StateManager* sm): sm(sm) {
    titleFont.loadFromFile("asset/font/yuyuko.ttf");
    subtitleFont.loadFromFile("asset/font/CFSamuraiBob.ttf");

    titleText.setFont(titleFont);
    titleText.setString("Touhou Clone");
    titleText.setCharacterSize(80);
    titleText.setOrigin(titleText.getLocalBounds().width/2 , 40);
    titleText.setPosition(350, 230);

    subtitleText.setFont(subtitleFont);
    subtitleText.setString("HIGH SCORE");
    subtitleText.setCharacterSize(50);
    subtitleText.setOrigin(subtitleText.getLocalBounds().width/2 , 25);
    subtitleText.setPosition(350, 290);

    highScore.setFont(subtitleFont);
    highScore.setString("0");
    highScore.setCharacterSize(50);
    highScore.setOrigin(highScore.getLocalBounds().width/2 , 25);
    highScore.setPosition(350, 320);

    playText.setFont(subtitleFont);
    playText.setString("PRESS SPACE TO PLAY");
    playText.setCharacterSize(40);
    playText.setOrigin(playText.getLocalBounds().width/2 , 20);
    playText.setPosition(350, 500);
}

void SplashState::onActivate(std::string pass) {

}

void SplashState::handleInput(const vec2i& mouse) {
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
        sm->push(1);
}

void SplashState::update(float dt) {

}

void SplashState::render(sf::RenderWindow& window) {
    window.draw(titleText);
    window.draw(subtitleText);
    window.draw(highScore);
    window.draw(playText);
}
