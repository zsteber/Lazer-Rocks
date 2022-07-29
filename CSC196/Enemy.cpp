#include "Enemy.h"
#include "Engine.h"
#include "bullet.h"
#include "Player.h"
#include "Rocket.h"

#include <iostream>

void Enemy::Initialize()
{
	m_firetimer = neu::randomf(10, 0);
	m_speed = neu::randomf(150, 0);
}

void Enemy::Update()
{
	m_firetimer -= neu::timer.deltaTime;
	if (m_firetimer <= 0)
	{
		m_firetimer = neu::randomf(10, 0);
		neu::Transform transform = m_transform;
		std::unique_ptr<Bullet> bullet = std::make_unique<Bullet>(neu::Model{ "Models/bullet.txt" }, transform);
		bullet->getTag() = "enemy";
		scene->Add(std::move(bullet));

	}
	

	// set rotation towards player
	Player* player = scene->GetActor<Player>();
	if (player)
	{
		neu::Vector2 direction = player->m_transform.position - m_transform.position;
		m_transform.rotation = direction.GetAngle();

	}

	// calculate velocity
	neu::Vector2 direction{ 1 , 0 };
	direction = neu::Vector2::Rotate(direction, m_transform.rotation);

	neu::Vector2 velocity = direction * m_speed * neu::timer.deltaTime;

	// move
	m_transform.position += velocity;

	// screen wrap
	if (m_transform.position.x > neu::g_renderer.GetWidth()) m_transform.position.x = 0;
	if (m_transform.position.x < 0) m_transform.position.x = (float)neu::g_renderer.GetWidth();

	if (m_transform.position.y > neu::g_renderer.GetHeight()) m_transform.position.y = 0;
	if (m_transform.position.y < 0) m_transform.position.y = (float)neu::g_renderer.GetHeight();

}

void Enemy::onCollision(Actor* other)
{
	if (dynamic_cast<Rocket*>(other) && other->getTag() == "player")
	{
		m_health -= dynamic_cast<Rocket*>(other)->getDamage();

		if (m_health <= 0) m_destroy = true;
		if (m_health <= 0) neu::g_audioSystem.PlayAudio("EnExplosion");
	}

	if (dynamic_cast<Bullet*>(other) && other->getTag() == "player")
	{
		m_health -= dynamic_cast<Bullet*>(other)->getDamage();

		if (m_health <= 0) m_destroy = true;
		if (m_health <= 0) neu::g_audioSystem.PlayAudio("EnExplosion");
	}
}