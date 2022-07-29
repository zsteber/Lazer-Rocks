#pragma once
#include "FrameWork/Actor.h"

class Enemy : public neu::Actor
{
public:
	Enemy() = default;
	Enemy(const neu::Model& model, const neu::Transform& transform, float health = 1) : Actor{ model, transform }, m_health { health } {
		Initialize();
	}
	
	void Initialize();
	void Update() override;
	
	void onCollision(Actor* other) override;

private:
	float m_health = 2;
	float m_speed = 70;
	float m_firetimer = 0;

};