#pragma once
#include "FrameWork/Actor.h"

class Player : public neu::Actor
{
public:
	Player() = default;
	Player(const neu::Model& model, const neu::Transform& transform) : Actor{ model, transform } {}

	void Update() override;
	void onCollision(Actor* other) override;
	float m_health = 5;

private:
	

	float m_speed{ 0 };
	float m_maxSpeed{ 150 };
};