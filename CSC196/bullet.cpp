#include "bullet.h"
#include "Player.h"
#include "Enemy.h"
#include "Engine.h"

void Bullet::Update()
{

	m_lifespan -= neu::timer.deltaTime;
	if (m_lifespan <= 0) m_destroy = true;


	neu::Vector2 direction{ 1, 0 };
	direction = neu::Vector2::Rotate(direction, m_transform.rotation);

	neu::Vector2 velocity = direction * m_speed * neu::timer.deltaTime;

	m_transform.position += velocity;
}

void Bullet::onCollision(Actor* other)
{
	if (dynamic_cast<Player*>(other) && m_tag != "player")
	{
		m_destroy = true;
	}
	if (dynamic_cast<Enemy*>(other) && m_tag != "enemy")
	{
		m_destroy = true;
	}
}