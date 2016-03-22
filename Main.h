#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <Windows.h>

#include <string>
#include <vector>
#include <queue>
#include <cmath>
#include <iostream> /* error-checking */

namespace Fonts {
	const std::string SCORE = "fonts/ShareTechMono-Regular.ttf";
}

namespace Keys {
	const auto UP = 0x11;		/* w */
	const auto DOWN = 0x1f;		/* s */
	const auto LEFT = 0x1e;		/* a */
	const auto RIGHT = 0x20;	/* d */
	const auto FIRE = 0x39;		/* spacebar */
}

namespace Colors {
	const auto PLAYER = sf::Color::Blue;
	const auto PBULLET = sf::Color::White;
	const auto ENEMY = sf::Color::Red;
	const auto EBULLET = sf::Color::Magenta;
}

namespace Speeds { /* pixels per second */
	const auto PLAYER = 200.0f;
	const auto BULLET = 110.0f;
	const auto BULLET_1 = 70.0f;
	const auto BULLET_2 = 110.0f;
	const auto ENEMY = 200.0f;
}

namespace Radii {
	const auto PLAYER = 10.0f;
	const auto ENEMY = 15.0f;
	const auto EBULLET = 5.0f;
	const auto PBULLET = 5.0f;
}

namespace FiringRates { /* bullets per second */
	const auto PLAYER = 5.0f;
	const auto ENEMY = 10.0f;
	const auto ENEMY_1 = 0.5f;
	const auto ENEMY_2 = 4.0f;
}

namespace RotationalSpeeds {
	const auto ENEMY = 40.0f;
	const auto ENEMY_1 = 10.0f;
}

namespace BulletSpeedIncrements {
	const auto ENEMY = 30.0f;
}

namespace BulletBurstNumberRadial {
	const auto ENEMY = 4;
	const auto ENEMY_1 = 50;
	const auto ENEMY_2 = 10;
}

namespace BulletBurstNumberStraight {
	const auto ENEMY = 5;
}

namespace SpreadAngles { /* in degress */
	const auto ENEMY = 45.0f;
}

class Score {
private:
	const int CHAR_SIZE = 16;
	const std::string SCORE = "Score: ";
	sf::Text text;
	sf::Font font;
	int score;
	
public:
	Score() : score(0) {
		if (!font.loadFromFile(Fonts::SCORE)) {
			/* font loading error */
		}
		text.setFont(font);
		text.setCharacterSize(CHAR_SIZE);
		text.setColor(sf::Color::White);
		text.setPosition(0, 0);
	}
	void setPosition();
	void add();
	void draw(sf::RenderTarget& g);
};

/* entity */
class Entity {
protected:
	sf::CircleShape form;

public:
	Entity() {}
	Entity(const sf::Vector2f& start_pos, float radius, const sf::Color& col) : form(radius) {
		form.setFillColor(col);
		form.setOrigin(radius, radius);
		form.setPosition(start_pos);
	}
	sf::Transformable* getForm();
	sf::Vector2f getPosition() const;
	void setPosition(float x, float y);
	float getRadius() const;
	bool isKeyDown(const int& key) const;
	virtual void update(float dt) = 0;
	void render(sf::RenderTarget& g);
};

/* behaviors */
class Behavior {
public:
	Behavior() {}
	virtual void behave(sf::Transformable* form, float dt) = 0;
};

/* move behaviors */
class MoveBehavior : public Behavior {
protected:
	float speed;
	sf::Vector2f direction;
	
public:
	MoveBehavior() {}
	MoveBehavior(float speed, const sf::Vector2f& direction) : speed(speed), direction(direction) {}
};

class MoveNowhere : public MoveBehavior {
public:
	MoveNowhere() : MoveBehavior() {}
	void behave(sf::Transformable* form, float dt) override;
};

class MoveStraight : public MoveBehavior {
public:
	MoveStraight(float speed, const sf::Vector2f& direction) : MoveBehavior(speed, direction) {}
	void behave(sf::Transformable* form, float dt) override;
};

class MoveAndBounce : public MoveBehavior {
private:
	float radius;
	
public:
	MoveAndBounce(float speed, const sf::Vector2f& direction, float radius) : MoveBehavior(speed, direction), radius(radius) {}
	void behave(sf::Transformable* form, float dt) override;
};

/* shoot behaviors */
class ShootBehavior : public Behavior {
protected:
	float firing_rate; /* in bullets per second */
	float timer; /* in seconds */
	float bullet_speed;
	const sf::Color& bullet_color;
	
public:
	ShootBehavior(float firing_rate, float bullet_speed, const sf::Color& bullet_color) : firing_rate(firing_rate), timer(1/firing_rate), bullet_speed(bullet_speed), bullet_color(bullet_color) {}
};

class ShootStraight : public ShootBehavior {
public:
	ShootStraight(float firing_rate, float bullet_speed, const sf::Color& bullet_color) : ShootBehavior(firing_rate, bullet_speed, bullet_color) {}
	void behave(sf::Transformable* form, float dt) override;
};

class ShootRadial : public ShootBehavior {
private:
	int bullets_radial;
	
public:
	ShootRadial(float firing_rate, float bullet_speed, const sf::Color& bullet_color, int bullets_radial) : ShootBehavior(firing_rate, bullet_speed, bullet_color), bullets_radial(bullets_radial) {}
	void behave(sf::Transformable* form, float dt) override;
};

class ShootSpeedChange : public ShootBehavior {
private:
	int bullets_radial;
	int bullets_straight;
	float bullet_speed_increment;
	
public:
	ShootSpeedChange(float firing_rate, float bullet_speed, const sf::Color& bullet_color, int bullets_radial, int bullets_straight, float bullet_speed_increment) : ShootBehavior(firing_rate, bullet_speed, bullet_color), bullets_radial(bullets_radial), bullets_straight(bullets_straight), bullet_speed_increment(bullet_speed_increment) {}
	void behave(sf::Transformable* form, float dt) override;
};

class ShootBurstSpread : public ShootBehavior {
private:
	int bullets_radial;
	int bullets_straight;
	float bullet_speed_increment;
	float spread_angle;

public:
	ShootBurstSpread(float firing_rate, float bullet_speed, const sf::Color& bullet_color, int bullets_radial, int bullets_straight, float bullet_speed_increment, float spread_angle) : ShootBehavior(firing_rate, bullet_speed, bullet_color), bullets_radial(bullets_radial), bullets_straight(bullets_straight), bullet_speed_increment(bullet_speed_increment), spread_angle(spread_angle) {}
	void behave(sf::Transformable* form, float dt) override;
};

class ShootRadialBurst : public ShootBehavior {
private:
	int bullets_radial;
	int bullets_straight;
	float bullet_speed_increment;
	float bullet_radius;
	
public:
	ShootRadialBurst(float firing_rate, float bullet_speed, const sf::Color& bullet_color, int bullets_radial, int bullets_straight, float bullet_speed_increment, float bullet_radius) : ShootBehavior(firing_rate, bullet_speed, bullet_color), bullets_radial(bullets_radial), bullets_straight(bullets_straight), bullet_speed_increment(bullet_speed_increment), bullet_radius(bullet_radius) {}
	void behave(sf::Transformable* form, float dt) override;
};

class ShootCorkSign : public ShootBehavior {
private:
	ShootBehavior *shoot1, *shoot2, *shoot3;
	float rotation;
	float rotational_speed;

public:
	ShootCorkSign(ShootBehavior* shoot1, ShootBehavior* shoot2, ShootBehavior* shoot3, float rotational_speed) : shoot1(shoot1), shoot2(shoot2), shoot3(shoot3), rotation(0), rotational_speed(rotational_speed), ShootBehavior(0, 0, Colors::EBULLET) {}
	void behave(sf::Transformable* form, float dt) override;
};

/* rotate behavior */
class RotateBehavior : public Behavior {
protected:
	float rotational_speed; /* in degrees per second */
	
public:
	RotateBehavior() {}
	RotateBehavior(float rotational_speed) : rotational_speed(rotational_speed) {}
};

class RotateNone : public RotateBehavior {
public:
	RotateNone() : RotateBehavior() {}
	void behave(sf::Transformable* form, float dt) override;
};

class RotateConstantly : public RotateBehavior {
public:
	RotateConstantly(float rotational_speed) : RotateBehavior(rotational_speed) {}
	void behave(sf::Transformable* form, float dt) override;
};

class RotateHoming : public RotateBehavior {
private:
	sf::Transformable* target;

public:
	RotateHoming(float rotational_speed, sf::Transformable* target) : RotateBehavior(rotational_speed), target(target) {}
	void behave(sf::Transformable* form, float dt) override;
};

/* entities */
class Bullet : public Entity {
private:
	MoveBehavior* move_behavior;
	
public:
	Bullet() : Entity(sf::Vector2f(0, 0), Radii::EBULLET, Colors::EBULLET) {}
	~Bullet() {
		delete move_behavior;
	}
	void initialize(const sf::Vector2f& start_pos, MoveBehavior* _move_behavior);
	void update(float dt) override;
};

class Player : public Entity {
private:
	/* int spf; // shots per frame */
	sf::Vector2f direction;
	Score score;
	
public:
	Player(const sf::Vector2f& start_pos) : Entity(start_pos, Radii::PLAYER, Colors::PLAYER), direction(0, 0) {
		form.setOrigin(Radii::PLAYER, Radii::PLAYER);
	}
	void handleInput();
	void fire();
	void takeDamage();
	void update(float dt) override;
	void renderScore(sf::RenderTarget& g);
};

class Enemy : public Entity {
private:
	MoveBehavior* move_behavior;
	// ShootBehavior* shoot_behavior;
	std::vector<ShootBehavior*> shoot_behaviors;
	RotateBehavior* rotate_behavior;
	float timer;
	
public:
	Enemy() : Entity(sf::Vector2f(0, 0), Radii::ENEMY, Colors::ENEMY) {}
	/* Enemy(const sf::Vector2f& start_pos, MoveBehavior* move_behavior, ShootBehavior* shoot_behavior, RotateBehavior* rotate_behavior) : Entity(start_pos, Radii::ENEMY, Colors::ENEMY), move_behavior(move_behavior), shoot_behavior(shoot_behavior), rotate_behavior(rotate_behavior) {
		form.setOrigin(Radii::ENEMY, Radii::ENEMY);
		form.setRotation(90.0);
	} */
	Enemy(const sf::Vector2f& start_pos, MoveBehavior* move_behavior, std::vector<ShootBehavior*> shoot_behaviors, RotateBehavior* rotate_behavior) : Entity(start_pos, Radii::ENEMY, Colors::ENEMY), move_behavior(move_behavior), shoot_behaviors(shoot_behaviors), rotate_behavior(rotate_behavior), timer(0) {
		form.setOrigin(Radii::ENEMY, Radii::ENEMY);
		form.setRotation(90.0);
	}
	~Enemy() {
		delete move_behavior;
		// delete shoot_behavior;
		delete rotate_behavior;
	}
	void update(float dt) override;
};

/* object pool */
class Pool {
private:
	std::queue<Bullet*> bQueue;
	std::queue<Enemy*> eQueue;

public:
	Bullet* getBullet();
	Enemy* getEnemy();

	void returnBullet(Bullet* bull);
	void returnEnemy(Enemy* enem);

	void initialize();
};

/* entity manager */
class EntityManager {
private:
	Player* player;
	std::vector<Bullet*> pbullets;
	std::vector<Bullet*> ebullets;
	std::vector<Enemy*> enemies;
	Pool pool;
	bool circleCollision(const Entity& c1, const Entity& c2);
	
public:
	EntityManager() {}
	void enemyShoot(const sf::Vector2f& startpos, MoveBehavior* move_behavior);
	void handleInput();
	void update(float dt);
	void logic();
	void render(sf::RenderTarget& g);
	void resolveWallCollision();
	void initialize();
	bool recycle(Bullet* bull);
} em;

/* class StageDirector {

}; */