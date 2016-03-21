#include "Main.h"

#define FPS	60.0f
#define SPF sf::seconds(1.0f/FPS)

const double PI = std::acos(-1);
const auto DTR = PI / 180;
const auto window_height = 800;
const auto window_width = 800;
EntityManager em;
Pool pool;

int main() {
	sf::RenderWindow window(sf::VideoMode(window_width,window_height), "My Window");
	sf::Clock clock;
	sf::Time lag = sf::seconds(0);
	
	em.initialize();
	
	/* run the program as long as the window is open */
	while (window.isOpen()) {
		/* check all the window's events that were triggered since the last iteration of the loop */
		sf::Event event;
		while (window.pollEvent(event)) {
			/* "close requested" event: we close the window */
			if (event.type == sf::Event::Closed) {
				window.close();
			}
		}
		/* handle input */
		em.handleInput();
		
		/* update entities */
		em.update(SPF.asSeconds());
		/* collision detection */
		em.logic();
		window.clear();
		
		/* render */
		em.render(window);
		
		window.display();
		
		const auto time_elapsed = clock.getElapsedTime() + lag;
		if (time_elapsed < SPF) {
			sf::sleep(SPF - time_elapsed);
			lag = sf::seconds(0);
		} else {
			lag = time_elapsed - SPF;
		}
		clock.restart();
	}
	return 0;
}

void Score::add() {
	++score;
}

void Score::draw(sf::RenderTarget& g) {
	text.setString(SCORE + std::to_string(score));
	g.draw(text);
}

/* Move Behaviors */
void MoveStraight::behave(sf::CircleShape& form, float dt) {
	form.move(speed*dt*direction);
}

void MoveStraight::init(float speed, const sf::Vector2f &dir)  {
	
}

void MoveDelay::behave(sf::CircleShape& form, float dt) {
	if (delay <= 0) {
		form.move(speed*dt*direction);
	}
	else {
		delay -= dt;
	}
}

void MoveDelay::init(float speed, const sf::Vector2f &dir) {
	this->speed = speed;
	this->direction = dir;
}


void MoveDelay::setDelay(float time) {
	delay = time;
}

/* Shoot Behaviors */
void ShootStraight::behave(sf::CircleShape& form, float dt) {
	timer += dt;
	if (timer >= firing_rate*dt) {
		float rotation = form.getRotation();
		sf::Vector2f direction(std::cos(rotation*PI/180), std::sin(rotation*PI/180));
		Bullet* temp = pool.getBullet();
		temp->init(form.getPosition(), new MoveStraight(Speeds::EBULLET, Speeds::EBULLET*dt*direction),Colors::EBULLET);//change this
		em.enemyShoot(temp);
		timer = 0;
	}
}


void ShootHell::behave(sf::CircleShape& form, float dt) {
	spawnTimer += dt;
	fireTimer += dt;
	if (spawnTimer >= delaySpawn && spawn && phase1) {//phase 1
		delayCompen += dt;
		sf::Vector2f enemypos = form.getPosition(); //center of the entire bullet pattern
		currAng += incAngBull;
		for (int i = 0; i < numCircles; i++) {
			sf::Vector2f dirToCir(cos(i*circleAngle*DTR)*incSpaceRad*currRing, sin(i*circleAngle*DTR)*incSpaceRad*currRing);
			sf::Vector2f centerCircle = enemypos + dirToCir;
			sf::Vector2f dirToBull(cos(currAng*DTR)*incBull*currRing, sin(currAng*DTR)*incBull*currRing);
			sf::Vector2f centerBull = centerCircle + dirToBull;
			sf::Vector2f dir = centerCircle - centerBull;
			dir /= sqrt(dir.x * dir.x + dir.y + dir.y);
			Bullet* temp = pool.getBullet();
			MoveDelay* md = pool.getMDQ();
			md->init(Speeds::EBULLET,dir);
			md->setDelay(fireTime - (delayCompen));
			sf::Color c = Colors::EBULLET;
			switch (currRing) {
			case 1:
				c = Colors::RINGONE_1;
				break;
			case 2:
				c = Colors::RINGTWO_1;
				break;
			case 3:
				c = Colors::RINGTHREE_1;
				break;
			}
			temp->init(centerBull, md,c);
			em.enemyShoot(temp);
		}
		currBull++;
		if (currAng >= angEnd) {
			currAng = 0;
			delayCompen = 0;
			currBull = 1;
			currRing++;
			if (currRing >= numRings + 1) {
				currRing = 1;
				spawn = false;
				phase1 = false;
			}
		}
	}
	else if (spawnTimer >= delaySpawn && spawn && !phase1) {//phase 2


	}
	else {
		delayCompen += dt;
		if (delayCompen >= delayBetweenPhases) {
			delayCompen = 0;
			spawn = true;
			phase1 = true;
		}
	}
}


/* Rotate Behaviors */
void RotateConstantly::behave(sf::CircleShape& form, float dt) {
	form.setRotation(form.getRotation() + rotational_speed*dt);
}

/* Entity */
sf::Vector2f Entity::getPos() const {
	return form.getPosition();
}

void Entity::setPos(float x, float y) {
	form.setPosition(x, y);
}

float Entity::getRad() const {
	return form.getRadius();
}

bool Entity::isKeyDown(const int& key) {
	short state = GetAsyncKeyState(MapVirtualKey(key, MAPVK_VSC_TO_VK_EX));
	return state >> 15 != 0;
}

void Entity::render(sf::RenderTarget& g) {
	g.draw(form);
}

/* Bullets */
void Bullet::update(float dt) {
	move_behavior->behave(form, dt);
}

/* Player */
void Player::update(float dt) {
	form.move(Speeds::PLAYER*dt*direction);
}

void Player::handleInput() {
	direction.x = 0;
	direction.y = 0;
	if (isKeyDown(Keys::UP)) {
		direction.y -= 1;
	}
	if (isKeyDown(Keys::DOWN)) {
		direction.y += 1;
	}
	if (isKeyDown(Keys::LEFT)) {
		direction.x -= 1;
	}
	if (isKeyDown(Keys::RIGHT)) {
		direction.x += 1;
	}
	direction.x *= 1 - std::abs(direction.y)*(std::sqrt(2) - 1)/std::sqrt(2);
	direction.y *= 1 - std::abs(direction.x)*(std::sqrt(2) - 1)/std::sqrt(2);
}

void Player::fire() {
	if (isKeyDown(Keys::FIRE)) {
		
	}
}

void Player::takeDamage() {
	//score.add();
}

void Player::renderScore(sf::RenderTarget& g) {
	//score.draw(g);
}

/* Enemy */
void Enemy::update(float dt) {
	//rotate_behavior->behave(form, dt);
	shoot_behavior->behave(form, dt);
}

/* Pool */
Bullet* Pool::getBullet() {
	if (!bQueue.empty()) {
		Bullet* tmp = bQueue.front();
		bQueue.pop();
		return tmp;
	} else {
		return nullptr;
	}
}

void Pool::returnBullet(Bullet* bull) {
	bQueue.push(bull);
	if (auto move = dynamic_cast<MoveStraight*>(bull->move_behavior)) {
		std::cout << "RETURN MSQ" << std::endl;
		msQ.push(dynamic_cast<MoveStraight*>(bull->move_behavior));
	}
	else if (auto move = dynamic_cast<MoveDelay*>(bull->move_behavior)) {
		std::cout << "RETURN MDQ" << std::endl;
		mdQ.push(dynamic_cast<MoveDelay*>(bull->move_behavior));
	}
	bull->move_behavior = nullptr;
}

Enemy* Pool::getEnemy() {
	if (!eQueue.empty()) {
		Enemy* tmp = eQueue.front();
		eQueue.pop();
		return tmp;
	} else {
		return nullptr;
	}
}

void Pool::returnEnemy(Enemy* enem) {
	eQueue.push(enem);
}


MoveStraight* Pool::getMSQ() {
	if (!msQ.empty()) {
		MoveStraight* tmp = msQ.front();
		msQ.pop();
		return tmp;
	}
	else {
		return nullptr;
	}
}

void Pool::returnMSQ(MoveStraight* m) {
	msQ.push(m);
}

MoveDelay* Pool::getMDQ() {
	if (!msQ.empty()) {
		MoveDelay* tmp = mdQ.front();
		mdQ.pop();
		return tmp;
	}
	else {
		return nullptr;
	}
}

void Pool::returnMDQ(MoveDelay* m) {
	mdQ.push(m);
}

void Pool::Init() {
	for (int i = 0; i < 5000; i++) {
		bQueue.push(new Bullet());
		msQ.push(new MoveStraight(0, sf::Vector2f(0, 0)));
		mdQ.push(new MoveDelay(0,sf::Vector2f(0,0),0));
	}
	
}
	//push also the bullet patterns


/* Entity Manager */
bool EntityManager::circleCollision(const Entity& c1, const Entity& c2) {
	const auto c1p = c1.getPos();
	const auto c2p = c2.getPos();
	return ((c1p.x - c2p.x)*(c1p.x - c2p.x) + (c1p.y - c2p.y)*(c1p.y - c2p.y)) <= ((c1.getRad() + c2.getRad())*(c1.getRad() + c2.getRad()));
}

void EntityManager::addPlayer(Entity* player) {
	this->player = dynamic_cast<Player*>(player);
}

void EntityManager::handleInput() {
	player->handleInput();
}

void EntityManager::update(float dt) {
	player->update(dt);
	for (auto enemy : enemies) {
		enemy->update(dt);
	}
	for (auto bullet : ebullets) {
		bullet->update(dt);
	}

}

void EntityManager::logic() {
	resolveWallCollision();
	for (int i = ebullets.size() - 1; i >= 0; i--) {
		Bullet* bullet = ebullets[i];
			if (circleCollision(*bullet, *player)) {
				player->takeDamage();
				ebullets.erase(ebullets.begin() + i);
				pool.returnBullet(bullet);
			}
			if (recycle(bullet)) {
				ebullets.erase(ebullets.begin() + i);
				pool.returnBullet(bullet);
			}
	}

	for (auto bullet : pbullets) {
		for (auto enemy : enemies) {
			if (circleCollision(*bullet, *enemy)) {
				//damage enemy
			}
		}
	}
}

void EntityManager::render(sf::RenderTarget& g) {
	player->render(g);
	//player->renderScore(g);
	
	for (auto bullet : ebullets) {
		bullet->render(g);
	}
	for (auto enemy : enemies) {
		enemy->render(g);
	}
}

void EntityManager::enemyShoot(Bullet* bull) {
	ebullets.push_back(bull);
}


bool EntityManager::recycle(Bullet* bull) {
	return (bull->getPos().x - bull->getRad() > window_width + 50) || (bull->getPos().x + bull->getRad() < -50) || (bull->getPos().y + bull->getRad() < -50) || (bull->getPos().y - bull->getRad() > window_height + 50);
}

void EntityManager::resolveWallCollision() {
	if (player->getPos().x + player->getRad() > window_width) {
		player->setPos(window_width - player->getRad(), player->getPos().y);
	} else if (player->getPos().x - player->getRad() < 0) {
		player->setPos(player->getRad(), player->getPos().y);
	}
	if (player->getPos().y + player->getRad() > window_height) {
		player->setPos(player->getPos().x, window_height - player->getRad());
	} else if (player->getPos().y - player->getRad() < 0) {
		player->setPos(player->getPos().x, player->getRad());
	}
}

void EntityManager::initialize() {
	addPlayer(new Player(sf::Vector2f(window_width/2, window_height*3.0/4.0)));
	pool.Init();
	enemies.push_back(new Enemy(sf::Vector2f(window_width/2, window_height/3), new ShootHell(0.2,Colors::PBULLET,5,3,64,50,50,0.2f,6,5)));
}