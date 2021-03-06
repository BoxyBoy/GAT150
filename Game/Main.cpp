#include "pch.h"
#include "Core/Json.h"
#include "Graphics/Texture.h"
#include "Sources Files/TileMap.h"
#include "Objects/Scene.h"
#include "Objects/GameObject.h"
#include "Objects/ObjectFactory.h"
#include "PlayerComponent.h"

nc::Engine engine;
nc::Scene scene;

int main(int, char**)
{
	engine.Startup();
	scene.Create(&engine);

	nc::ObjectFactory::Instance().Initialize();
	nc::ObjectFactory::Instance().Register("PlayerComponent", new nc::Creator<nc::PlayerComponent, nc::Object>);

	rapidjson::Document document;
	nc::json::Load("scene.txt", document);
	scene.Read(document); 

	nc::json::Load("tileMap.txt", document);
	nc::TileMap tileMap;
	tileMap.Read(document);
	tileMap.Create(&scene);

	//for (size_t i = 0; i < 10; i++)
	//{
	//	nc::GameObject* gameObject = nc::ObjectFactory::Instance().Create<nc::GameObject>("ProtoCoin");
	//	gameObject->m_transform.position = { nc::random(0, 800), nc::random(350, 500) };
	//	//gameObject->m_transform.angle = nc::random(0, 360);
	//	scene.AddGameObject(gameObject);
	//}

	IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG);

	SDL_Event event;
	bool quit = false;
	while (!quit)
	{
		SDL_PollEvent(&event);
		switch (event.type)
		{
		case SDL_QUIT:
			quit = true;
			break;
		}

		//update
		engine.Update();
		scene.Update();
		
		if (engine.GetSystem<nc::InputSystem>()->GetButtonState(SDL_SCANCODE_ESCAPE) == nc::InputSystem::eButtonState::PRESSED)
		{
			quit = true;
		}

		// draw
		engine.GetSystem<nc::Renderer>()->BeginFrame();

		scene.Draw();

		engine.GetSystem<nc::Renderer>()->EndFrame();
	}

	scene.Destroy();
	engine.Shutdown();
	IMG_Quit();
	

	return 0;
}
