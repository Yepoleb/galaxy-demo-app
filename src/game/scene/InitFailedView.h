#ifndef GOGTRON_SCENE_INIT_FAILED_VIEW_H
#define GOGTRON_SCENE_INIT_FAILED_VIEW_H

#include "GameState.h"
#include <engine/system/GUIElement.h>
#include <vector>

namespace gogtron
{
	namespace scene
	{

		class InitFailedView : public GameState
		{
		public:

			InitFailedView(const IGamePtr& _game);

			virtual bool Init() override;
			virtual bool Release() override;

			virtual void OnMouseDown(std::uint32_t x, std::uint32_t y) override;
			virtual void OnMouseMotion(std::uint32_t x, std::uint32_t y) override;
			virtual void OnKeyDown(SDL_Keysym key) override;
			virtual void OnLobbyEvent(const networking::LobbyEvent& lobbyEvent) override;

			virtual bool Update() override;
			virtual bool Display(const renderer::OGLRendererPtr& engine) override;

		private:

			std::vector<system::GUIElementPtr> guiElements;
		};

	}
}

#endif