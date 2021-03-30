#include "engine.h"

void Engine::LanGame() { //Test work with connection:
	game_restart_ = true;

	while (game_restart_) {
		game_restart_ = false; /*+++*/

		//Show IP address:
		sf::IpAddress ip_local_ = sf::IpAddress::getLocalAddress();
		sf::IpAddress ip_public_ = sf::IpAddress::getPublicAddress(); //Get local IP
		std::cout << "Address local: " << ip_local_
			<< "; Address public: " << ip_public_ << std::endl << std::endl;

		/* Determining the type of connection: */
		std::string connect_type;
		do {
			if (game_restart_) break; /*++++++++*/
			std::cout << "Select type to connect: (s): server; (c): client; "
				<< "(q) - quit game; ";
			std::cin >> connect_type;
			system("cls");

			if (connect_type == "s") { im_server_ = true; break; }
			else if (connect_type == "c") { im_server_ = false; break; }
			else if (connect_type == "q") exit(0);
			else std::cout << "The wrong type is selected!" << std::endl;
		} while (true);

		/* Establishing a connection: */
		if (im_server_) this->ServerManager();
		else this->ClientManager();
	}
}

void Engine::ServerManager() {
	
	sf::TcpListener server;
	server.listen(7777);
	tcp_selector_.clear();
	tcp_selector_.add(server);
	std::cout << "Server started. Port: 7777" << std::endl;

	while (Main_window_.isOpen()) {
		if (tcp_selector_.wait()) {
			CheckingDisconnectedClients();
			if (tcp_selector_.isReady(server)) {
				sf::TcpSocket* socket = new sf::TcpSocket;
				if (server.accept(*socket) == sf::Socket::Done) {

					//New connect
					sf::Packet get_connect_packet;
					if (socket->receive(get_connect_packet) == sf::Socket::Done) {
						std::cout << "NEW CLIENT CONNECTED! \t IP: "
							<< socket->getRemoteAddress() << std::endl;
						//here send packet to client with id
					}
					list_clients_.push_back(socket);
					tcp_selector_.add(*socket);
					get_connect_packet.clear();
				}
				else delete socket;
			}
			else {
				for (int i = 0; i < (int)list_clients_.size(); i++) {
					if (tcp_selector_.isReady(*list_clients_[i])) {
						sf::Packet get_packet, mailings_Packet;

						//Receive packet:
						if (list_clients_[i]->receive(get_packet) == sf::Socket::Done) {

							std::string connect_message;
							get_packet >> connect_message; //unpack packet
							std::cout << "Package received successfully <" << i 
								<< ">: " << connect_message << "\t ip: " 
								<< (*list_clients_[i]).getRemoteAddress() << std::endl;

							//processing packet on server
							get_packet.clear();

							//Test mailing packet to client
							ServerMailingMessageToClients(mailings_Packet << connect_message);
						}
					}
				}
			}
		}
	}
}

void Engine::CheckingDisconnectedClients() {
	for (int client = 0; client < (int)list_clients_.size(); client++) {
		sf::Packet get_connect_packet;
		if ((*list_clients_[client]).send(get_connect_packet) == sf::Socket::Disconnected) {
			std::cout << "CLIENT DISCONNECT: " << "\t IP: "
				<< (*list_clients_[client]).getRemoteAddress() << std::endl;
			get_connect_packet.clear();
			tcp_selector_.remove((*list_clients_[client]));
			delete list_clients_[client];
			list_clients_.erase(list_clients_.begin() + client);
		}
	}
}

void Engine::ClientManager() {
	do {
		std::cout << "Connect to ip address: ";
		std::cin >> ip_enter_;

		if (tcp_socket_.connect(ip_enter_, 7777) == sf::Socket::Done) {
			tcp_socket_.setBlocking(false);

			sf::Packet send_connect_packet;
			tcp_socket_.send(send_connect_packet);
			send_connect_packet.clear();

			/* Receive packets: */
			RecvMessageFromServer();
		}
		//else if (game_restart_) break; /*++++++++*/

		else if (tcp_socket_.connect(ip_enter_, 7777) != sf::Socket::Done) {
			std::cout << "Cannot connect to the server... Try again? Enter (y): yes; (n): no; ";
			std::string connect;
			std::cin >> connect;
			if (connect == "n") break;
			system("cls");
		}
	} while (true);
}

//Get Intafomration to go client: BaseLevel->GetObjectToSendClient

void Engine::ServerMailingMessageToClients(sf::Packet& mailings_Packet) {
	for (int client = 0; client < (int)list_clients_.size(); client++) {
		std::cout << "Mailing packet to client <" << client << ">" << std::endl;
		if (list_clients_[client]->send(mailings_Packet) == sf::Socket::Done)
			std::cout << "Mailing packages sent successfully!" << std::endl;
		else std::cout << "Packages were not sent!" << std::endl;
	}
	mailings_Packet.clear();
}

void Engine::ClientSendMessageToServer(sf::Packet& mailings_Packet) {
	if (tcp_socket_.send(mailings_Packet) == sf::Socket::Done)
		std::cout << "Package sent successfully!" << std::endl;
	else std::cout << "Package was not sent!" << std::endl;
}

bool Engine::RecvMessageFromServer() {
	
	while (!game_restart_) {
		sf::Packet get_packet;
		if (tcp_socket_.receive(get_packet) == sf::Socket::Done) {
			std::string recieve_message;

			get_packet >> recieve_message; //unpack packet -<<-------<<------
			std::cout << std::endl <<  "Recieve packet from server (" << recieve_message 
				<< ") ip: " << tcp_socket_.getRemoteAddress() << std::endl;

			get_packet.clear();
		}
	}
	tcp_socket_.disconnect();
	return true;
}