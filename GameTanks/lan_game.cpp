#include "engine.h"

void Engine::LanGame() {
	while (lan_thread_work_) {
		if (Status_server_ == StatusServer::SERVER) this->ServerManager();
		else if (Status_server_ == StatusServer::CLIENT) this->ClientManager();
	}
}

bool Engine::ServerManager() {
	//Cleaning
	Ip_client_connect_ = "";
	client_id_object_ = 0;

	//Start Server Work
	Server_.listen(7777);
	Tcp_selector_.add(Server_);
	//std::cout << "Server started. Port: 7777" << std::endl;
	while (Status_server_ == StatusServer::SERVER) {
		if (Tcp_selector_.wait()) {
			if (Tcp_selector_.isReady(Server_)) ConnectNewClient(Server_);
			PacketReceivingServer();
			CheckingDisconnectedClients();
		}
	}
	return true;
}

void Engine::CheckingDisconnectedClients() {
	for (int client = 0; client < (int)List_clients_.size(); client++) {
		sf::Packet get_connect_packet;
		if ((*List_clients_[client]).send(get_connect_packet) == sf::Socket::Disconnected) {
			std::cout << "CLIENT DISCONNECT: " << "\t IP: "
				<< (*List_clients_[client]).getRemoteAddress() << std::endl;
			get_connect_packet.clear();
			Tcp_selector_.remove((*List_clients_[client]));
			delete List_clients_[client];
			List_clients_.erase(List_clients_.begin() + client);
			Point_level_->DeleteClientPlayer(client + 1);
		}
	}
}

void Engine::ConnectNewClient(sf::TcpListener& server) {
	sf::TcpSocket* socket = new sf::TcpSocket;
	if (server.accept(*socket) == sf::Socket::Done) {
		std::cout << "NEW CLIENT CONNECTED! \t IP: "
			<< socket->getRemoteAddress() << std::endl;

		//Sending packet with ID
		sf::Packet send_id_packet;
		send_id_packet << (Point_level_->AddPlayerFromLan());
		socket->send(send_id_packet);
		send_id_packet.clear();

		List_clients_.push_back(socket);
		Tcp_selector_.add(*socket);
	}
	else delete socket;
}

void Engine::PacketReceivingServer() {
	int key, type_key;
	for (int i = 0; i < (int)List_clients_.size(); i++) {
		if (Tcp_selector_.isReady(*List_clients_[i])) {
			sf::Packet get_packet;
			if (List_clients_[i]->receive(get_packet) == sf::Socket::Done) {				
				while (get_packet.getDataSize() > 0 && !get_packet.endOfPacket()) {
					key = type_key = 0;
					get_packet >> key;
					get_packet >> type_key;
					Point_level_->InputKeyboard(i + 1, 
						(sf::Keyboard::Key)key, (sf::Event::EventType)type_key);
					/*std::cout << "Package received successfully <" << ">: \t ip: "
						<< (*list_clients_[i]).getRemoteAddress() << std::endl; */
				}
				get_packet.clear();
			}
		}
	}
}

void Engine::ClientManager() {
	sf::Packet resieve_id_packet;
	if (Tcp_socket_.connect(Ip_client_connect_, 7777) == sf::Socket::Done) {
		client_id_object_ = 0;

		//Reseiving packet with ID
		Tcp_socket_.receive(resieve_id_packet);
		resieve_id_packet >> client_id_object_;

		// Receive packets: 
		RecvMessageFromServer();
	}
	else Status_server_ = StatusServer::NOT_DETERMINED;
	Tcp_socket_.disconnect();
}

void Engine::ServerMailingMessageToClients() {
	sf::Packet mailings_Packet;
	for (int client = 0; client < (int)List_clients_.size(); client++) {
		mailings_Packet = Point_level_->GetPacketToSendAllClient(client + 1, true);
		if (mailings_Packet.getDataSize() > 0) {
			List_clients_[client]->send(mailings_Packet);
			/*std::cout << "Mailing packet to client <" << client << ">" << std::endl;*/
		}
		mailings_Packet.clear();
	}
}

void Engine::ClientSendMessageToServer(sf::Packet& mailings_Packet) {
	Tcp_socket_.send(mailings_Packet);
}

bool Engine::RecvMessageFromServer() {
	sf::Packet packet;
	while (Status_server_ == StatusServer::CLIENT) {
		if (!pause_client_recv_) {
			std::this_thread::sleep_for(std::chrono::milliseconds(10));
			if (Tcp_socket_.receive(packet) == sf::Socket::Done) {
				Point_level_->RecvPacketFromServer(packet);
				/*std::cout << std::endl << "Recieve packet from server ip: "
					<< tcp_socket_.getRemoteAddress() << std::endl; */
			}
			packet.clear();
		}
	}
	return true;
}

void Engine::CleaningClients() {
	for (int i = 0; i < (int)List_clients_.size(); i++) {
		List_clients_[i]->disconnect();
		delete List_clients_[i];
	}
}