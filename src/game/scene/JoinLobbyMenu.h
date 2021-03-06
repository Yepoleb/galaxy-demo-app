#ifndef GALAXY_DEMO_SCENE_JOIN_LOBBY_MENU_H
#define GALAXY_DEMO_SCENE_JOIN_LOBBY_MENU_H

#include "GameState.h"
#include <engine/system/GUIElement.h>
#include <galaxy/GalaxyApi.h>
#include <vector>

namespace galaxy::demo
{
	namespace scene
	{

		class JoinLobbyMenu
			: public GameState
			, public galaxy::api::GlobalLobbyListListener
		{
		public:

			JoinLobbyMenu(const IGamePtr& _game);

			virtual bool Init() override;
			virtual bool Release() override;

			virtual void OnMouseDown(std::uint32_t x, std::uint32_t y) override;
			virtual void OnMouseMotion(std::uint32_t x, std::uint32_t y) override;
			virtual void OnKeyDown(SDL_Keysym key) override;
			virtual void OnLobbyEvent(const networking::LobbyEvent& lobbyEvent) override;

			virtual bool Update() override;
			virtual bool Display(const renderer::OGLRendererPtr& renderEngine) override;

		private:

			virtual void OnLobbyList(uint32_t lobbyCount, bool ioFailure) override;

			system::GUIElementPtr backButton;
			std::vector<system::GUIElementPtr> guiElements;
			bool anyLobbies;
		};

	}
}

#endif