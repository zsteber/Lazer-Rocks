#pragma once
#include <Engine.h>

class Rocket : public neu::Actor
{
public:
	Rocket() = default;
	Rocket(const neu::Model& model, const neu::Transform& transform, float damage = 1) : Actor{ model, transform }, r_damage{ damage } {}

	void Update() override;
	void onCollision(Actor* other) override;

	virtual float getDamage() { return r_damage; }

private:
	float r_damage = 5;
	float m_rhealth = 100;

	float r_firetimer = 0;
	float r_speed = 500;
	float m_lifespan = 50;
};