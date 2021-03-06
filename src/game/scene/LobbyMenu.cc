#include "LobbyMenu.h"
#include <game/IGame.h>
#include <game/networking/Lobby.h>
#include <engine/system/Button.h>
#include <engine/core/SDLResourceManager.h>
#include <SDL_opengl.h>

using namespace galaxy::demo;
using namespace galaxy::demo::system;
using namespace galaxy::demo::scene;
using namespace galaxy::demo::networking;

LobbyMenu::LobbyMenu(const IGamePtr& _game)
	: GameState(_game)
{
}

bool LobbyMenu::Init()
{
	guiElements.emplace_back(std::make_shared<Button>(
		"CREATE LOBBY", 1280 / 2 - 150, 100, 300, 100,
		[&]()
	{
		if (!galaxy::api::User()->IsLoggedOn())
		{
			errorMessage = "Not logged on Galaxy";
			return;
		}

		ILobbyPtr lobby = std::make_shared<Lobby>(game);
		game->SetLobby(lobby);

		try
		{
			galaxy::api::Matchmaking()->CreateLobby(galaxy::api::LOBBY_TYPE_PUBLIC, 4, true, galaxy::api::LOBBY_TOPOLOGY_TYPE_FCM_OWNERSHIP_TRANSITION);
		}
		catch (const galaxy::api::IError& /*error*/)
		{
			return;
		}

		game->SetGameState(GameState::State::IN_LOBBY_MENU);
	}));

	guiElements.emplace_back(std::make_shared<Button>(
		"JOIN LOBBY", 1280 / 2 - 150, 300, 300, 100,
		[&]()
	{
		if (!galaxy::api::User()->IsLoggedOn())
		{
			errorMessage = "Not logged on Galaxy";
			return;
		}

		game->SetGameState(GameState::State::JOIN_LOBBY_MENU);
	}));

	guiElements.emplace_back(std::make_shared<Button>(
		"BACK", 1280 / 2 - 150, 500, 300, 100,
		[&]() { game->SetGameState(GameState::State::START_MENU); }));

	game->SetClient(nullptr);
	game->SetServer(nullptr);
	game->SetLobby(nullptr);

	return true;
}

bool LobbyMenu::Release()
{
	return true;
}

void LobbyMenu::OnMouseDown(std::uint32_t x, std::uint32_t y)
{
	for (const auto& element : guiElements)
	{
		element->OnMouseDown(x, y);
	}
}

void LobbyMenu::OnMouseMotion(std::uint32_t x, std::uint32_t y)
{
	for (const auto& element : guiElements)
	{
		element->OnMouseMotion(x, y);
	}
}

void LobbyMenu::OnKeyDown(SDL_Keysym key)
{
}

void LobbyMenu::OnLobbyEvent(const LobbyEvent& lobbyEvent)
{
}

bool LobbyMenu::Update()
{
	return true;
}

bool LobbyMenu::Display(const renderer::OGLRendererPtr& renderEngine)
{
	for (const auto& element : guiElements)
	{
		element->Display(renderEngine);
	}

	if (!errorMessage.empty())
	{
		renderEngine->DisplayText(errorMessage.c_str(), renderer::Sprite(50, 100, 300, 100), "LobbyMenuErrorMessage", SDL_Color{255, 0, 0, 255});
	}

	return true;
}