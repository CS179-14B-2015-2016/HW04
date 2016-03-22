#include "Main.h"

#define FPS	60.0f
#define SPF sf::seconds(1.0f/FPS)

const double PI = std::acos(-1);
const auto window_height = 600;
const auto window_width = 600;

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

/* Entity */
sf::Transformable* Entity::getForm() {
	return &form;
}

sf::Vector2f Entity::getPosition() const {
	return form.getPosition();
}

void Entity::setPosition(float x, float y) {
	form.setPosition(x, y);
}

float Entity::getRadius() const {
	return form.getRadius();
}

bool Entity::isKeyDown(const int& key) const {
	short state = GetAsyncKeyState(MapVirtualKey(key, MAPVK_VSC_TO_VK_EX));
	return state >> 15 != 0;
}

void Entity::render(sf::RenderTarget& g) {
	g.draw(form);
}

/* Move Behaviors */
void MoveNowhere::behave(sf::Transformable* form, float dt) {
	
}

void MoveStraight::behave(sf::Transformable* form, float dt) {
	form->move(speed*dt*direction);
}

void MoveAndBounce::behave(sf::Transformable* form, float dt) {
	form->move(speed*dt*direction);
	
	sf::Vector2f position = form->getPosition();
	
	if (position.x - radius < 0) {
		position.x = radius;
		direction.x *= -1;
	} else if (position.x + radius > window_width) {
		position.x = window_width - radius;
		direction.x *= -1;
	}
	
	if (position.y - radius < 0) {
		position.y = radius;
		direction.y *= -1;
	}
}

/* Shoot Behaviors */
void ShootStraight::behave(sf::Transformable* form, float dt) {
	sf::Vector2f position = form->getPosition();
	float rotation = form->getRotation();
	
	timer += dt;
	if (timer >= 1/firing_rate) {
		em.enemyShoot(position, new MoveStraight(bullet_speed, sf::Vector2f(std::cos(rotation*PI/180), std::sin(rotation*PI/180))));
		timer = 0;
	}
}

void ShootRadial::behave(sf::Transformable* form, float dt) {
	sf::Vector2f position = form->getPosition();
	float rotation = form->getRotation();
	
	timer += dt;
	if (timer >= 1/firing_rate) {
		for (float i = rotation; i < rotation + 360.0; i += 360.0/bullets_radial) {
			em.enemyShoot(position, new MoveStraight(bullet_speed, sf::Vector2f(std::cos(i*PI/180), std::sin(i*PI/180))));
		}
		timer = 0;
	}
}

void ShootSpeedChange::behave(sf::Transformable* form, float dt) {
	sf::Vector2f position = form->getPosition();
	float rotation = form->getRotation();
	
	timer += dt;
	if (timer >= 1/firing_rate) {
		for (float j = bullet_speed; j < bullet_speed + bullet_speed_increment*bullets_straight; j += bullet_speed_increment) {
			for (float i = rotation; i < rotation + 360.0; i += 360.0/bullets_radial) {
				em.enemyShoot(position, new MoveStraight(j, sf::Vector2f(std::cos(i*PI/180), std::sin(i*PI/180))));
			}
		}
		timer = 0;
	}
}

void ShootBurstSpread::behave(sf::Transformable* form, float dt) {
	sf::Vector2f position = form->getPosition();
	float rotation = form->getRotation();
	
	timer += dt;
	if (timer >= 1/firing_rate) {
		for (float j = bullet_speed; j < bullet_speed + bullet_speed_increment*bullets_straight; j += bullet_speed_increment) {
			for (float i = rotation - spread_angle/2; i < rotation + spread_angle/2; i += spread_angle/bullets_radial) {
				em.enemyShoot(position, new MoveStraight(j, sf::Vector2f(std::cos(i*PI/180), std::sin(i*PI/180))));
			}
		}
		timer = 0;
	}
}

void ShootRadialBurst::behave(sf::Transformable* form, float dt) {
	sf::Vector2f position = form->getPosition();
	float rotation = form->getRotation();
	
	timer += dt;
	if (timer >= 1/firing_rate) {
		for (float j = bullet_speed; j < bullet_speed + bullet_speed_increment*bullets_straight; j += bullet_speed_increment) {
			for (float i = rotation; i < rotation + 360.0; i += 360.0/bullets_radial) {
				em.enemyShoot(position, new MoveAndBounce(j, sf::Vector2f(std::cos(i*PI/180), std::sin(i*PI/180)), bullet_radius));
			}
		}
		timer = 0;
	}
}

void ShootCorkSign::behave(sf::Transformable* form, float dt) {
	shoot1->behave(form, dt);
	
	float orig_rotation = form->getRotation();
	
	form->rotate(rotation*dt);
	shoot2->behave(form, dt);
	form->setRotation(orig_rotation);
	
	form->rotate(-rotation*dt);
	shoot3->behave(form, dt);
	form->setRotation(orig_rotation);
	
	
	rotation += rotational_speed;
}

/* Rotate Behaviors */
void RotateNone::behave(sf::Transformable* form, float dt) {
	
}

void RotateConstantly::behave(sf::Transformable* form, float dt) {
	form->rotate(rotational_speed*dt);
}

void RotateHoming::behave(sf::Transformable* form, float dt) {
	sf::Vector2f position_origin = form->getPosition();
	sf::Vector2f position_target = target->getPosition();
	
	float rotation_origin = form->getRotation();
	float rotation_target = atan2(position_target.y - position_origin.y, position_target.x - position_origin.x)*180/PI;
	
	float angle = rotation_origin - rotation_target;
	if (angle > 180) {
		angle -= 360;
	}
	
	if (std::abs(angle) < rotational_speed*dt) {
		form->setRotation(rotation_target);
	} else if (angle > 0) {
		form->rotate(-rotational_speed*dt);
	} else if (angle < 0) {
		form->rotate(rotational_speed*dt);
	}
}

/* Bullets */
void Bullet::initialize(const sf::Vector2f& start_pos, MoveBehavior* _move_behavior) {
	form.setPosition(start_pos);
	move_behavior = _move_behavior;
}
	
void Bullet::update(float dt) {
	move_behavior->behave(&form, dt);
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
	score.add();
}

void Player::renderScore(sf::RenderTarget& g) {
	score.draw(g);
}

/* Enemy */
void Enemy::update(float dt) {
	timer += dt;
	
	move_behavior->behave(&form, dt);
	if (timer < 10) {
		shoot_behaviors[0]->behave(&form, dt);
	} else {
		shoot_behaviors[1]->behave(&form, dt);
	}
	rotate_behavior->behave(&form, dt);
}

/* Pool */
Bullet* Pool::getBullet() {
	if (!bQueue.empty()) {
		Bullet* tmp = bQueue.front();
		bQueue.pop();
		return tmp;
	} else {
		return new Bullet();;
	}
}

void Pool::returnBullet(Bullet* bull) {
	bQueue.push(bull);
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

void Pool::initialize() {
	for (int i = 0; i < 2000; ++i) {
		bQueue.push(new Bullet());
	}
}

/* Entity Manager */
bool EntityManager::circleCollision(const Entity& c1, const Entity& c2) {
	const auto c1p = c1.getPosition();
	const auto c2p = c2.getPosition();
	const auto c1r = c1.getRadius();
	const auto c2r = c2.getRadius();
	
	return (c1p.x - c2p.x)*(c1p.x - c2p.x) + (c1p.y - c2p.y)*(c1p.y - c2p.y) <= (c1r + c2r)*(c1r + c2r);
}

void EntityManager::handleInput() {
	player->handleInput();
}

void EntityManager::update(float dt) {
	player->update(dt);
	for (auto bullet : ebullets) {
		bullet->update(dt);
	}
	for (auto enemy : enemies) {
		enemy->update(dt);
	}
	// std::cout << "Num of bullets: " << ebullets.size() << "\n";
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
	/* for (auto bullet : pbullets) {
		for (auto enemy : enemies) {
			if (circleCollision(*bullet, *enemy)) {
				//destroy enemy
			}
		}
	} */
}

void EntityManager::render(sf::RenderTarget& g) {
	player->render(g);
	player->renderScore(g);
	
	for (auto bullet : ebullets) {
		bullet->render(g);
	}
	for (auto enemy : enemies) {
		enemy->render(g);
	}
}

void EntityManager::enemyShoot(const sf::Vector2f &startpos, MoveBehavior* move_behavior) {
	Bullet* bullet = pool.getBullet();
	bullet->initialize(startpos, move_behavior);
	ebullets.push_back(bullet);
}

bool EntityManager::recycle(Bullet* bullet) {
	const auto bp = bullet->getPosition();
	const auto br = bullet->getRadius();
	
	return (bp.x - br > window_width) || (bp.x + br < 0) || (bp.y + br < 0) || (bp.y - br > window_height);
}

void EntityManager::resolveWallCollision() {
	auto player_pos = player->getPosition();
	auto player_rad = player->getRadius();
	
	if (player_pos.y + player_rad > window_height) {
		player->setPosition(player_pos.x, window_height - player_rad);
	} else if (player_pos.y - player_rad < 0) {
		player->setPosition(player_pos.x, player_rad);
	}
	
	player_pos = player->getPosition();
	player_rad = player->getRadius();
	
	if (player_pos.x + player_rad > window_width) {
		player->setPosition(window_width - player_rad, player_pos.y);
	} else if (player_pos.x - player_rad < 0) {
		player->setPosition(player_rad, player_pos.y);
	}
}

void EntityManager::initialize() {
	player = new Player(sf::Vector2f(window_width/2, window_height*3.0/4.0));
	
	pool.initialize();
	
	/* enemies.push_back(
		new Enemy(sf::Vector2f(window_width/2, window_height/4),
		new MoveNowhere(),
		new ShootRadialBurst(FiringRates::ENEMY, Speeds::BULLET, Colors::EBULLET, BulletBurstNumberRadial::ENEMY, BulletBurstNumberStraight::ENEMY, BulletSpeedIncrements::ENEMY, Radii::EBULLET),
		new RotateNone())
	); */
	
	/* enemies.push_back(
		new Enemy(sf::Vector2f(window_width/2, window_height/4),
		new MoveNowhere(),
		new ShootSpeedChange(FiringRates::ENEMY, Speeds::BULLET, Colors::EBULLET, BulletBurstNumberRadial::ENEMY, BulletBurstNumberStraight::ENEMY, BulletSpeedIncrements::ENEMY),
		new RotateConstantly(RotationalSpeeds::ENEMY))
	); */
	
	/* enemies.push_back(
		new Enemy(sf::Vector2f(window_width/2, window_height/4),
		new MoveNowhere(),
		new ShootBurstSpread(FiringRates::ENEMY, Speeds::BULLET, Colors::EBULLET, BulletBurstNumberRadial::ENEMY, BulletBurstNumberStraight::ENEMY, BulletSpeedIncrements::ENEMY, SpreadAngles::ENEMY),
		new RotateHoming(RotationalSpeeds::ENEMY, player->getForm()))
	); */
	
	/* enemies.push_back(
		new Enemy(sf::Vector2f(window_width/2, window_height/4),
		new MoveNowhere(),
		new ShootStraight(FiringRates::ENEMY, Speeds::BULLET, Colors::EBULLET),
		new RotateHoming(RotationalSpeeds::ENEMY, player->getForm()))
	); */
	
	std::vector<ShootBehavior*> enemy1;
	enemy1.push_back(new ShootRadial(FiringRates::ENEMY, Speeds::BULLET, Colors::EBULLET, BulletBurstNumberRadial::ENEMY));
	enemy1.push_back(new ShootCorkSign(
		new ShootRadial(FiringRates::ENEMY_1, Speeds::BULLET_1, Colors::EBULLET, BulletBurstNumberRadial::ENEMY_1),
		new ShootRadial(FiringRates::ENEMY_2, Speeds::BULLET_2, Colors::EBULLET, BulletBurstNumberRadial::ENEMY_2),
		new ShootRadial(FiringRates::ENEMY_2, Speeds::BULLET_2, Colors::EBULLET, BulletBurstNumberRadial::ENEMY_2),
		RotationalSpeeds::ENEMY_1
	));
	
	enemies.push_back(
		new Enemy(sf::Vector2f(window_width/2, window_height/4),
		new MoveNowhere(),
		enemy1,
		new RotateConstantly(RotationalSpeeds::ENEMY))
	);
	
	/* enemies.push_back(
		new Enemy(sf::Vector2f(window_width/2, window_height/4),
		new MoveNowhere(),
		new ShootCorkSign(
			new ShootRadial(FiringRates::ENEMY_1, Speeds::BULLET_1, Colors::EBULLET, BulletBurstNumberRadial::ENEMY_1),
			new ShootRadial(FiringRates::ENEMY_2, Speeds::BULLET_2, Colors::EBULLET, BulletBurstNumberRadial::ENEMY_2),
			new ShootRadial(FiringRates::ENEMY_2, Speeds::BULLET_2, Colors::EBULLET, BulletBurstNumberRadial::ENEMY_2),
			RotationalSpeeds::ENEMY_1
		),
		new RotateNone())
	); */
}