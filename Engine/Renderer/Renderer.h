#pragma once
#include "../Math/Vector2.h"
#include "../Math/Color.h"

struct SDL_Renderer;
struct SDL_Window;

namespace neu
{
	class Renderer
	{
	public:
		Renderer() = default;
		~Renderer() = default;

		void Initialize();
		void ShutDown();

		void CreateWindow(const char* name, int width, int height);
		void BeginFrame();
		void EndFrame();
		void SetClearColor(Color color) { m_clearColor = color; }

		void DrawLine(float x1, float y1, float x2, float y2);
		void DrawLine(const Vector2& v1, const Vector2& v2, const Color& color);
		void DrawPoint(float x, float y);
		void DrawPoint(const Vector2& v, const Color& color); //

		int GetWidth() { return m_width; }
		int GetHeight() { return m_height; }


		SDL_Renderer* m_renderer = nullptr;
	private:

		int m_width = 0;
		int m_height = 0;

		Color m_clearColor{ 0, 0, 0, 255 };
		
		SDL_Window* m_window = nullptr;
	};
}