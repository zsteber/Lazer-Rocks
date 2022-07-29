#include "Player.h"
#include "Enemy.h"
#include "Engine.h"
#include <Renderer/Text.h>
#include <Renderer/Font.h>


using namespace std;


int main()
{
	neu::InitializeMemory();
	neu::SetFilePath("../Assets");

	// create systems
	neu::g_renderer.Initialize();
	neu::g_inputSystem.Initialize();
	neu::g_audioSystem.Initialize();

	// create window
	neu::g_renderer.CreateWindow("Chicken Pot Pie", 800, 600);
	neu::g_renderer.SetClearColor(neu::Color{ 50, 50, 50, 255 });

	neu::Scene scene;


	
	// ** CREATE ACTOR **
	// transform
	neu::Transform transform;
	transform.position = neu::Vector2{ 400, 300 };
	transform.rotation = 0;
	transform.scale = 3;

	//Set Title and fonts
	neu::Font* font = new neu::Font("Fonts/IMMORTAL.ttf", 36);

	neu::Text title(font);
	title.Create(neu::g_renderer, "Lazer Rocks", { 0, 0, 255, 255 });


	std::unique_ptr<Player> player = std::make_unique<Player>(neu::Model( "Models/Model.txt" ), transform);
	scene.Add(std::move(player));



	neu::g_audioSystem.AddAudio("laser", "Audio/laser.wav");
	neu::g_audioSystem.AddAudio("Rocket", "Audio/Rocket.wav");
	neu::g_audioSystem.AddAudio("Explosion", "Audio/Explosion.wav");
	neu::g_audioSystem.AddAudio("EnExplosion", "Audio/EnExplosion.wav");
	neu::g_audioSystem.AddAudio("Space", "Audio/Space.wav");

	neu::g_audioSystem.PlayAudio("Space");

	

	


	float spawnTimer = 2;


	bool quit = false;

	while (!quit)
	{
		// update
		neu::g_inputSystem.Update();
		neu::g_audioSystem.Update();
		neu::timer.Tick();


		if (neu::g_inputSystem.GetKeyState(neu::key_escape)) quit = true;


		// render
		neu::g_renderer.BeginFrame();

		//spawn enemies
		spawnTimer -= neu::timer.deltaTime;
		if (spawnTimer <= 0)
		{
			spawnTimer = neu::randomf(5, 0);
			transform.position.x = neu::randomf(800);
			transform.position.y = neu::randomf(600);
			std::unique_ptr<Enemy> enemy = std::make_unique<Enemy>(neu::Model("Models/Enemy.txt"), transform);
			enemy->getTag() = "enemy";
			scene.Add(std::move(enemy));
		}

		scene.Update();

		title.Draw(neu::g_renderer, { 0, 15 });
		scene.Draw(neu::g_renderer);


		neu::g_renderer.EndFrame();
	}

	delete font;
	neu::g_audioSystem.Shutdown();
	neu::g_renderer.ShutDown();
}
