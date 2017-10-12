#include "InitFailedView.h"
#include <game/IGame.h>
#include <engine/system/Button.h>
#include <SDL_opengl.h>
#include <algorithm>

using namespace gogtron;
using namespace gogtron::system;
using namespace gogtron::scene;

InitFailedView::InitFailedView(const IGamePtr& _game)
	: GameState(_game)
{
}

bool InitFailedView::Init()
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

	guiElements.emplace_back(std::make_shared<Button>(
		"EXIT", 1280 / 2 - 150, 500, 300, 100,
		[&]() { game->Close(); }));
	return true;
}

bool InitFailedView::Release()
{
	return true;
}

void InitFailedView::OnMouseDown(std::uint32_t x, std::uint32_t y)
{
	for (const auto& element : guiElements)
	{
		element->OnMouseDown(x, y);
	}
}

void InitFailedView::OnMouseMotion(std::uint32_t x, std::uint32_t y)
{
	for (const auto& element : guiElements)
	{
		element->OnMouseMotion(x, y);
	}
}

void InitFailedView::OnKeyDown(SDL_Keysym key)
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

void InitFailedView::OnLobbyEvent(const networking::LobbyEvent& lobbyEvent)
{
}

bool InitFailedView::Update()
{
	return true;
}

bool InitFailedView::Display(const renderer::OGLRendererPtr& renderEngine)
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

	renderEngine->DisplayText("FAILED TO INITIALIZE", renderer::Sprite(1280 / 2 - 200, 100, 400, 100), "FailedToInit", SDL_Color{255, 0, 0, 255});

	renderEngine->EndScene();
	return true;
}
