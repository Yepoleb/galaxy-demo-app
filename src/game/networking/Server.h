#ifndef GOGTRON_SERVER_H
#define GOGTRON_SERVER_H

#include "IServer.h"

namespace gogtron
{
	namespace networking
	{

		class Server : public IServer
		{
		public:

			Server(const IGamePtr& game);

			virtual bool SendMessageToAll(const std::string& message) const override;

			virtual bool RetrievedReadyFromEachClient() const override;
			virtual bool SendInitGame() override;
			virtual bool SendGameTick(const std::vector<PlayerPtr>& players) override;
			virtual bool SendGameResults(const std::vector<PlayerPtr>& players, int gameTime) override;

		private:

			virtual void OnServerP2PPacketAvailable(uint32_t msgSize, uint8_t channel) override;

			bool CreateInitGame(std::string& message);
		};

	}
}

#endif