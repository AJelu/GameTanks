#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <thread>
#include "settings.h"
#include "run_game.h"
#include "levels.h"
#include "objects.h"

class Engine {
private:
	sf::Clock Game_clock_;
	sf::RenderWindow Main_window_;
	BaseLevel* Point_level_;

	void GameTimer(float& timer);
	void GameSpeed(float& timer);

	void CreateResolutionWindowMode();

	void EngineInpute();
	void EngineUpdate(float& timer);
	void LanGame();
	void EngineDraw();
	
	/* Network block code: */
	std::thread* Thread_lan_;
	std::string Ip_client_connect_;
	sf::Packet Send_packet_;
	sf::SocketSelector Tcp_selector_;
	sf::TcpSocket Tcp_socket_;
	sf::TcpListener Server_;
	std::vector<sf::TcpSocket*> List_clients_;

	enum class StatusServer { NOT_DETERMINED, SERVER, CLIENT };
	StatusServer Status_server_;

	int client_id_object_;
	bool pause_client_recv_;
	bool lan_thread_work_;

	bool ServerManager();
	void CleaningClients();
	void ConnectNewClient(sf::TcpListener& server);
	void PacketReceivingServer();
	void CheckingDisconnectedClients();
	void ServerMailingMessageToClients();

	void ClientManager();
	void ClientSendMessageToServer(sf::Packet& mailings_Packet);
	bool RecvMessageFromServer();

public:
	Engine();

	int Processing();

	void StartLanServer();
	void StopLanServer();
	void ConnectLanToIp(std::string const& ip_to_connect); //set status CLIENT and connect to ip
	int GetRecvIdFromServer(); //return 0 if not recv or engine is server
	void PauseClientRecv(bool const& pause_client_recv);
	bool ServerIsWork();
	
	void ChangeLevel(BaseLevel* level);

	~Engine();
};