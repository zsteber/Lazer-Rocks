#pragma once
#include "Renderer.h"
#include <vector>
#include <string>

namespace neu
{
	class Model
	{
	public:
		Model() = default;
		Model(const std::vector< neu::Vector2>& points, const neu::Color& color) : m_points{ points }, m_color{ color } {}
		Model(const std::string& filename) { 
			Load(filename); 
			m_radius = CalculateRadius();
		}

		void Draw(Renderer& renderer, const Vector2& position, float angle, float sclae = 1);

		void Load(const std::string& filename);
		float CalculateRadius();

		float GetRadius() { return m_radius; }


	private:
		neu::Color m_color { 0, 0, 0, 0 };
		std::vector<neu::Vector2> m_points;

		float m_radius = 0;
	};
}