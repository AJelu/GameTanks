#include "engine.h"

void Engine::LanGame() {
	while (true) {
		if (status_server_ == StatusServer::SERVER) this->ServerManager();
		else if (status_server_ == StatusServer::CLIENT) this->ClientManager();
		//maybe sleep to N ms????
	}
}

bool Engine::ServerManager() {
	
	//Cleaning
	this->CleaningClients();
	tcp_selector_.clear();
	list_clients_.clear();
	ip_client_connect_ = "";
	client_id_object_ = 0;

	//Start Server Work
	sf::TcpListener server;
	server.listen(7777);
	tcp_selector_.add(server);
	std::cout << "Server started. Port: 7777" << std::endl;

	while (status_server_ == StatusServer::SERVER) {
		if (tcp_selector_.wait()) {
			if (tcp_selector_.isReady(server)) ConnectNewClient(server);
			else {
				PacketReceivingServer();
				ServerMailingMessageToClients();
			}
			CheckingDisconnectedClients();
		}
	}
	return false;
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

void Engine::ConnectNewClient(sf::TcpListener& server) {
	sf::TcpSocket* socket = new sf::TcpSocket;
	if (server.accept(*socket) == sf::Socket::Done) {
		sf::Packet get_connect_packet;
		if (socket->receive(get_connect_packet) == sf::Socket::Done) {
			std::cout << "NEW CLIENT CONNECTED! \t IP: "
				<< socket->getRemoteAddress() << std::endl;

			//Sending packet with ID
			sf::Packet send_id_packet;
			send_id_packet << (Point_level_->AddPlayerFromLan());
			socket->send(send_id_packet);
			send_id_packet.clear();

			/*send_id_packet << (Point_level_->GetPacketToSendAllClient(true));
			socket->send(send_id_packet);
			send_id_packet.clear();*/
		}
		list_clients_.push_back(socket);
		tcp_selector_.add(*socket);
		get_connect_packet.clear();
	}
	else delete socket;
}

void Engine::PacketReceivingServer() {
	for (int i = 0; i < (int)list_clients_.size(); i++) {
		if (tcp_selector_.isReady(*list_clients_[i])) {
			sf::Packet get_packet;
			if (list_clients_[i]->receive(get_packet) == sf::Socket::Done) {

				//Point_level_->InputKeyboard(i + 1, (*get_packet?)); <<<<<<<

				std::string connect_message;
				get_packet >> connect_message; //unpack packet
				std::cout << "Package received successfully <" << i
					<< ">: " << connect_message << "\t ip: "
					<< (*list_clients_[i]).getRemoteAddress() << std::endl;

				get_packet.clear();
			}
		}
	}
}

void Engine::ClientManager() {
	if (tcp_socket_.connect(ip_client_connect_, 7777) == sf::Socket::Done) {
		client_id_object_ = 0;

		sf::Packet send_connect_packet;
		tcp_socket_.send(send_connect_packet);
		send_connect_packet.clear();

		//Reseiving packet with ID
		sf::Packet resieve_id_packet;
		tcp_socket_.receive(resieve_id_packet);
		resieve_id_packet >> client_id_object_;
		resieve_id_packet.clear();

		// Receive packets: 
		RecvMessageFromServer();
	}
	else status_server_ = StatusServer::NOT_DETERMINED;
}

//Get Intafomration to go client: BaseLevel->GetObjectToSendClient

void Engine::ServerMailingMessageToClients() {
	sf::Packet mailings_Packet;
	mailings_Packet << Point_level_->GetPacketToSendAllClient(); /* with this client does not receive packets... */
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

	while (status_server_ == StatusServer::CLIENT) {
		if (!pause_client_recv_) {
			std::this_thread::sleep_for(std::chrono::milliseconds(250));

			sf::Packet send_connect_packet;
			tcp_socket_.send(send_connect_packet);
			send_connect_packet.clear();

			sf::Packet get_packet;
			if (tcp_socket_.receive(get_packet) == sf::Socket::Done) {
				Point_level_->RecvPacketFromServer(get_packet); /* with this client does not receive packets... */
				std::cout << std::endl << "Recieve packet from server ip: "
					<< tcp_socket_.getRemoteAddress() << std::endl;
				get_packet.clear();
			}
		}
	}
	tcp_socket_.disconnect();
	return true;
}

void Engine::CleaningClients() {
	for (std::vector<sf::TcpSocket*>::iterator it = list_clients_.begin();
		it != list_clients_.end(); it++)
		delete* it;
}