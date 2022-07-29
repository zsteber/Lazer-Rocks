#include "Player.h"
#include "Engine.h"
#include "Bullet.h"
#include "Rocket.h"

void Player::Update()
{
	if (m_speed < 0) {
		m_speed++;
	}
	else if (m_speed > 0) {
		m_speed--;
	}
	if (neu::g_inputSystem.GetKeyState(neu::key_left) == neu::InputSystem::KeyState::Held)
	{
		m_transform.rotation -= (2.0f * neu::timer.deltaTime);
	};

	if (neu::g_inputSystem.GetKeyState(neu::key_right) == neu::InputSystem::KeyState::Held)
	{
		m_transform.rotation += (2.0f * neu::timer.deltaTime);
	};

	m_speed = 0;
	if (neu::g_inputSystem.GetKeyState(neu::key_up) == neu::InputSystem::KeyState::Held)
	{
		m_speed = m_maxSpeed;
	};

	// fire bullets
	if (neu::g_inputSystem.GetKeyState(neu::key_space) == neu::InputSystem::KeyState::Press)
	{
		neu::Transform transform = m_transform;
		transform.scale = 1;
		std::unique_ptr<Bullet> bullet = std::make_unique<Bullet>(neu::Model{ "Models/Bullet.txt" }, transform);
		bullet->getTag() = "player";
		scene->Add(std::move(bullet));
		neu::g_audioSystem.PlayAudio("laser");
	}

	//fire rockets
	if (neu::g_inputSystem.GetKeyState(neu::key_rocket) == neu::InputSystem::KeyState::Press)
	{
		// r_firetimer -= neu::timer.deltaTime;
		neu::Transform transform = m_transform;
		transform.scale = 3;
		std::unique_ptr<Bullet> rocket = std::make_unique<Bullet>(neu::Model{ "Models/Rocket.txt" }, transform);
		rocket->getTag() = "player";
		scene->Add(std::move(rocket));
		neu::g_audioSystem.PlayAudio("Rocket");
	}

	// screen wrap
	if (m_transform.position.x > neu::g_renderer.GetWidth()) m_transform.position.x = 0;
	if (m_transform.position.x < 0) m_transform.position.x = (float)neu::g_renderer.GetWidth();

	if (m_transform.position.y > neu::g_renderer.GetHeight()) m_transform.position.y = 0;
	if (m_transform.position.y < 0) m_transform.position.y = (float)neu::g_renderer.GetHeight();
	
	// face target
	// neu::Vector2 target = neu::g_inputSystem.GetMousePosition();
	// target = target - m_transform.position; // direction vector towards target from ship
	// m_transform.rotation = target.GetAngle();


	// calculate force
	neu::Vector2 direction{ 1, 0 };
	direction = neu::Vector2::Rotate(direction, m_transform.rotation);
	neu::Vector2 force = direction * (m_speed * neu::timer.deltaTime);

	// apply force to velocity
	m_velocity += force;

	// apply drag
	m_velocity *= 1.0f / (1.0f + m_damping * neu::timer.deltaTime);

	// move
	m_transform.position += m_velocity * neu::timer.deltaTime;
}

void Player::onCollision(Actor* other)
{
	if (dynamic_cast<Bullet*>(other) && other->getTag() == "enemy")
	{
		m_health -= dynamic_cast<Bullet*>(other)->getDamage();
		if (m_health <= 0) m_destroy = true;
		if(m_health <= 0) neu::g_audioSystem.PlayAudio("Explosion");
	}
}