#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <thread>
#include "settings.h"
#include "run_game.h"
#include "levels.h"
#include "objects.h"

/*
	Engine includes the following files :
		engine.cpp
		engine_draw.cpp
		engine_input.cpp
		engine_update.cpp
		lan_game.cpp
*/

class Engine {
private:
	sf::Clock Game_clock_;
	sf::RenderWindow Main_window_; // this object is responsible for all render
	BaseLevel* Point_level_;

	//for lan:
	std::thread thread_lan_;
	std::string ip_client_connect_;
	int client_id_object_;
	bool pause_client_recv_;

	enum class StatusServer { NOT_DETERMINED, SERVER, CLIENT };
	StatusServer status_server_;

	void GameTimer(float& timer); // create main game timer
	void GameSpeed(float& timer); // regulates the speed of the game
	void ForcedResetGameTimer(float& timer); // forced timer reset (may be needed if the reset does not work)

	void CreateResolutionWindowMode();
	
	void EngineInpute();
	void EngineUpdate(float& timer);
	

	/* Block work with a network: */
	sf::IpAddress ip_local_, ip_public_, ip_enter_;
	sf::SocketSelector tcp_selector_;
	sf::TcpSocket tcp_socket_;
	std::vector<sf::TcpSocket*> list_clients_;

	std::string send_message;

	bool ServerManager();
	void CleaningClients();
	void ConnectNewClient(sf::TcpListener& server);
	void PacketReceivingServer();
	void CheckingDisconnectedClients();
	void ServerMailingMessageToClients();

	void ClientManager();
	void ClientSendMessageToServer(sf::Packet& mailings_Packet);
	bool RecvMessageFromServer();
	/*-----------------------------*/

public:
	Engine();

	void LanGame();
	void EngineDraw(); //public->private

	int Start();
	void Stop();

	//void SetStatusServer(std::string status_game_server); ///?????

	//int GetStatusServer(); ///??????

	void StartServer();
	void StopServer();
	void ConnectLanToIp(std::string const& ip_to_connect); //set status CLIENT and connect to ip
	int GetRecvIdFromServer(); // return 0 if not recv or engine is server
	void PauseClientRecv(bool const& pause_client_recv);
	bool ServerIsWork();
	
	void ChangeLevel(BaseLevel* level);

	~Engine();
};