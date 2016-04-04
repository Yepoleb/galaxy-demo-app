#include "StartMenu.h"
#include <game/IGame.h>
#include <engine/system/Button.h>
#include <engine/core/SDLResourceManager.h>
#include <SDL_opengl.h>

using namespace gogtron;
using namespace gogtron::system;
using namespace gogtron::scene;
using namespace gogtron::networking;

StartMenu::StartMenu(const IGamePtr& _game)
	: GameState(_game)
{
}

bool StartMenu::Init()
{
	glViewport(0, 0, 1280, 720);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0, 1280, 720, 1.0, -1.0, 1.0);

	glClearColor(0.0, 0.0, 0.0, 0.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0, 1280, 720, 1.0, -1.0, 1.0);

	glEnable(GL_BLEND);
	glEnable(GL_TEXTURE_2D);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


	if (!core::SDLResourceManager::GetInstance().LoadTexture("res//images//button.png", "button"))
		return false;

	if (!core::SDLResourceManager::GetInstance().LoadTexture("res//images//selectedbutton.png", "selectedbutton"))
		return false;

	if (!core::SDLResourceManager::GetInstance().LoadFont("res//fonts//FreeSans.ttf", "FreeSans"))
		return false;

	GUIElementPtr playButton(std::make_shared<Button>(
		"button",
		"selectedbutton",
		renderer::Sprite(1280 / 2 - 150, 50, 300, 100),
		/*Sprite(400, 100, 400, 224),*/
		[&](){ game->SetGameState(GameState::State::LOBBY_MENU); }));

	guiElements.push_back(playButton);

	GUIElementPtr statsButton(std::make_shared<Button>(
		"button",
		"selectedbutton",
		renderer::Sprite(1280 / 2 - 150, 200, 300, 100),
		[&]() { game->SetGameState(GameState::State::STATS_VIEW); }));
	guiElements.push_back(statsButton);

	GUIElementPtr leaderboardsButton(std::make_shared<Button>(
		"button",
		"selectedbutton",
		renderer::Sprite(1280 / 2 - 150, 350, 300, 100),
		[&]() { game->SetGameState(GameState::State::LEADERBOARDS_VIEW); }));
	guiElements.push_back(leaderboardsButton);

	GUIElementPtr quitButton(std::make_shared<Button>(
		"button",
		"selectedbutton",
		renderer::Sprite(1280 / 2 - 150, 500, 300, 100),
		/*Sprite(400, 400, 400, 224),*/
		[&](){ game->Close(); }));

	guiElements.push_back(quitButton);

	return true;
}

bool StartMenu::Release()
{
	return true;
}

void StartMenu::OnMouseDown(std::uint32_t x, std::uint32_t y)
{
	for (const auto& element : guiElements)
	{
		element->OnMouseDown(x, y);
	}
}

void StartMenu::OnMouseMotion(std::uint32_t x, std::uint32_t y)
{
	for (const auto& element : guiElements)
	{
		element->OnMouseMotion(x, y);
	}
}

void StartMenu::OnKeyDown(SDL_Keysym key)
{
	switch (key.sym)
	{
	case SDLK_UP:
		guiElements[0]->OnMouseMotion(450, 150);
		break;

	case SDLK_DOWN:
		break;

	case SDLK_KP_ENTER:
		guiElements[0]->OnMouseDown(450, 150);
		break;

	default:
		break;
	}
}

void StartMenu::OnLobbyEvent(const LobbyEvent& lobbyEvent)
{
}

bool StartMenu::Update()
{
	return true;
}

bool StartMenu::Display(const renderer::OGLRendererPtr& renderEngine)
{
	glViewport(0, 0, 1280, 720);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0, 1280, 720, 1.0, -1.0, 1.0);

	glClearColor(0.0, 0.0, 0.0, 0.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0, 1280, 720, 1.0, -1.0, 1.0);

	glEnable(GL_BLEND);
	glEnable(GL_TEXTURE_2D);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	renderEngine->StartScene();

	for (const auto& element : guiElements)
	{
		element->Display(renderEngine);
	}

	renderEngine->DisplayText("PLAY", renderer::Sprite(1280 / 2 - 50, 50, 100, 100), "FreeSans_Play", SDL_Color{ 255, 0, 0, 255 });
	renderEngine->DisplayText("STATS", renderer::Sprite(1280 / 2 - 50, 200, 100, 100), "FreeSans_Stats", SDL_Color{ 255, 0, 0, 255 });
	renderEngine->DisplayText("LEADERBOARDS", renderer::Sprite(1280 / 2 - 100, 350, 200, 100), "FreeSans_Leaderboards", SDL_Color{ 255, 0, 0, 255 });
	renderEngine->DisplayText("QUIT", renderer::Sprite(1280 / 2 - 50, 500, 100, 100), "FreeSans_Quit", SDL_Color{ 255, 0, 0, 255 });
	renderEngine->EndScene();
	return true;
}