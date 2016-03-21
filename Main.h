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
	const auto RINGONE_1 = sf::Color::Green;
	const auto RINGTWO_1 = sf::Color::Magenta;
	const auto RINGTHREE_1 = sf::Color::Blue;
	const auto RINGONE_2 = sf::Color::Green;
	const auto RINGTWO_2 = sf::Color::Yellow;
	const auto RINGTHREE_2 = sf::Color::Cyan;

}

namespace Speeds { /* pixels per second */
	const auto PLAYER = 200.0f;
	const auto EBULLET = 50.0f;
	const auto ENEMY = 3.0f;
}

namespace Radii {
	const auto PLAYER = 10.0f;
	const auto ENEMY = 15.0f;
	const auto EBULLET = 4.0f;
	const auto PBULLET = 5.0f;
}

namespace FiringRates {
	const auto PLAYER = 5.0f;
	const auto ENEMY = 1.0f;
}

namespace RotationalSpeeds {
	const auto ENEMY = 50.0f;
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

/* behaviors */
class Behavior {
public:
	virtual void behave(sf::CircleShape& form, float dt) = 0;
};

/* move behaviors */
class MoveBehavior : public Behavior {
protected:
	float speed;
	sf::Vector2f direction;
public:
	MoveBehavior(float speed, const sf::Vector2f& direction) : speed(speed), direction(direction) {}
	MoveBehavior(){}
	virtual void init(float speed, const sf::Vector2f &direction) = 0;
};

class MoveStraight : public MoveBehavior {
public:
	MoveStraight(float speed, const sf::Vector2f& direction) : MoveBehavior(speed, direction) {}
	void behave(sf::CircleShape& form, float dt) override;
	void init(float speed, const sf::Vector2f &direction) override;
};


class MoveDelay : public MoveBehavior {
	float delay;
public:
	MoveDelay(float speed, const sf::Vector2f& direction, const float &delay) : MoveBehavior(speed, direction), delay(delay) {
	}
	void behave(sf::CircleShape& form, float dt) override;
	void init(float speed, const sf::Vector2f &direction) override;
	void setDelay(float sec);
};



/* shoot behaviors */
class ShootBehavior : public Behavior {
protected:
	float firing_rate; /* in bullets per second */
	float timer; /* in seconds */
	const sf::Color& bullet_color;
	
public:
	ShootBehavior(float firing_rate, const sf::Color& bullet_color) : firing_rate(firing_rate), bullet_color(bullet_color), timer(0) {}
};

class ShootStraight : public ShootBehavior {
public:
	ShootStraight(float firing_rate, const sf::Color& bullet_color) : ShootBehavior(firing_rate, bullet_color) {}
	void behave(sf::CircleShape& form, float dt) override;
};


class ShootHell : public ShootBehavior{
	int numCircles;
	int numRings;
	int numBulls;
	int currBull;
	int currRing;
	bool fire;
	bool spawn;
	bool phase1;
	float circleAngle;
	float spawnTimer;
	float fireTimer;
	float incAngBull;
	float incSpaceRad;
	float incBull;
	float delayCompen;
	float delaySpawn;
	float angStart;
	float currAng;
	float angEnd;
	float fireTime;
	float delayBetweenPhases;
public:
	ShootHell(float firing_rate, const sf::Color& bullet_color, int numCircles, int numRings, int numBulls, float incrementingSpace, float incBull, float delaySpawn,float fireTime, float delayBetweenPhases)
		: ShootBehavior(firing_rate, bullet_color), numCircles(numCircles), numRings(numRings), numBulls(numBulls),
		incSpaceRad(incrementingSpace), incBull(incBull), delaySpawn(delaySpawn),fireTime(fireTime), delayBetweenPhases(delayBetweenPhases) {
		circleAngle = 360.0f/numCircles;
		incAngBull = 360.0f/numBulls;
		fire = false;
		currBull = 1;
		delayCompen = 0;
		angStart = currAng = 180;
		currRing = 0;
		spawnTimer = 0;
		fireTimer = 0;
		angEnd = 360;
		spawn = true;
		phase1 = true;
	}
	void behave(sf::CircleShape& form, float dt) override;
};

/* rotate behavior */
class RotateBehavior : public Behavior {
protected:
	float rotational_speed; /* in degrees per second */
	
public:
	RotateBehavior(float rotational_speed) : rotational_speed(rotational_speed) {}
};

class RotateConstantly : public RotateBehavior {
public:
	RotateConstantly(float rotational_speed) : RotateBehavior(rotational_speed) {}
	void behave(sf::CircleShape& form, float dt) override;
};

/* entities */
class Entity {
protected:
	sf::CircleShape form;

public:
	Entity() {}
	Entity(const sf::Vector2f& start_pos, float radius, const sf::Color& col) : form(radius) {
		form.setFillColor(col);
		form.setPosition(start_pos);
	}
	sf::Vector2f getPos() const;
	void setPos(float x, float y);
	float getRad() const;
	bool isKeyDown(const int& key);
	virtual void update(float dt) = 0;
	void render(sf::RenderTarget& g);
};

class Bullet : public Entity {
	
public:
	MoveBehavior* move_behavior;
	Bullet() : Entity(sf::Vector2f(0, 0), Radii::EBULLET, Colors::EBULLET) {}
	~Bullet() {
		delete move_behavior;
	}
	void init(const sf::Vector2f& start_pos, MoveBehavior* _move_behavior,const sf::Color &col) {
		form.setPosition(start_pos);
		form.setOrigin(Radii::EBULLET, Radii::EBULLET);
		form.setFillColor(col);
		move_behavior = _move_behavior;
	}
	void update(float dt) override;
};

class Player : public Entity {
private:
	/* int spf; // shots per frame */
	sf::Vector2f direction;
	//Score score;
	
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
	MoveBehavior* move; 
	ShootBehavior* shoot_behavior;
	RotateBehavior* rotate_behavior;
	
public:
	Enemy(const sf::Vector2f& start_pos, RotateBehavior* rotate_behavior, ShootBehavior* shoot_behavior) : Entity(start_pos, Radii::ENEMY, Colors::ENEMY), shoot_behavior(shoot_behavior), rotate_behavior(rotate_behavior) {
		form.setOrigin(Radii::ENEMY, Radii::ENEMY);
		form.setRotation(90.0);
	}
	void update(float dt) override;
	void changeShootingBehavior(ShootBehavior* sb);
};

/* object pool */
class Pool {
private:
	std::queue<Bullet*> bQueue;
	std::queue<Enemy*> eQueue;
	std::queue<MoveStraight*> msQ;
	std::queue<MoveDelay*> mdQ;
public:
	Bullet* getBullet();
	Enemy* getEnemy();
	MoveStraight* getMSQ();
	MoveDelay* getMDQ();

	void returnBullet(Bullet* bull);
	void returnEnemy(Enemy* enem);
	void returnMSQ(MoveStraight* ms);
	void returnMDQ(MoveDelay* md);
	void Init();
};

/* entity manager */
class EntityManager {
private:
	Player* player;
	std::vector<Bullet*> pbullets;
	std::vector<Bullet*> ebullets;
	Enemy* enemies;
	bool switched;
	bool circleCollision(const Entity& c1, const Entity& c2);
	float switchPattern;
	float tTime;
public:
	EntityManager(float switchPattern): switchPattern(switchPattern) {
		tTime = 0;
		switched = false;
	}
	void addPlayer(Entity* player);
	void enemyShoot(Bullet*);
	void handleInput();
	void update(float dt);
	void logic();
	void render(sf::RenderTarget& g);
	void resolveWallCollision();
	void initialize();
	bool recycle(Bullet* bull);
};
