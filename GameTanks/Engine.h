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
	sf::Font Main_font_;

	std::thread thread_lan_;

	bool im_server_;// game_restart_;

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

	void ServerManager();
	void ClientManager();

	void SendMessageToClient(sf::Packet& send_packet);
	bool RecvMessageFromServer();
	/*-----------------------------*/

	void Font();

public:
	Engine();

	void LanGame();
	void EngineDraw(); //public->private

	int Start();
	void Stop();

	void ChangeLevel(BaseLevel* level);

	~Engine();
};