#include "engine.h"

void Engine::LanGame() {
	while (lan_thread_work_) {
		if (status_server_ == StatusServer::SERVER) this->ServerManager();
		else if (status_server_ == StatusServer::CLIENT) this->ClientManager();
	}
}

bool Engine::ServerManager() {
	
	//Cleaning
	ip_client_connect_ = "";
	client_id_object_ = 0;

	//Start Server Work
	server.listen(7777);
	tcp_selector_.add(server);
	std::cout << "Server started. Port: 7777" << std::endl;

	while (status_server_ == StatusServer::SERVER) {
		if (tcp_selector_.wait()) {
			if (tcp_selector_.isReady(server)) ConnectNewClient(server);
			PacketReceivingServer();
			CheckingDisconnectedClients();
		}
	}
	return true;
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
			Point_level_->DeleteClientPlayer(client + 1);
		}
	}
}

void Engine::ConnectNewClient(sf::TcpListener& server) {
	sf::TcpSocket* socket = new sf::TcpSocket;
	if (server.accept(*socket) == sf::Socket::Done) {
		sf::Packet get_connect_packet;
		//if (socket->receive(get_connect_packet) == sf::Socket::Done) {
			std::cout << "NEW CLIENT CONNECTED! \t IP: "
				<< socket->getRemoteAddress() << std::endl;

			//Sending packet with ID
			sf::Packet send_id_packet;
			sf::Packet recv_id_packet;
			sf::Packet send_time_packet;
			send_id_packet << (Point_level_->AddPlayerFromLan());
			//<<<<<<<<<<<<<<<<<get start time
			socket->send(send_id_packet);
			//recv packet
			socket->receive(recv_id_packet);
			//<<<<<<<<<<<<<<<<<get end time
			//<<<<<<<<<<<<<<<<<calculate ping (end - start)
			//<<<<<<<<<<<<<<<<<get game_time + ping and sent to client
			socket->send(send_id_packet);
			send_id_packet.clear();
			recv_id_packet.clear();
			send_time_packet.clear();
		//}
		list_clients_.push_back(socket);
		tcp_selector_.add(*socket);
		get_connect_packet.clear();
	}
	else delete socket;
}

void Engine::PacketReceivingServer() {
	int key, type_key;
	for (int i = 0; i < (int)list_clients_.size(); i++) {
		if (tcp_selector_.isReady(*list_clients_[i])) {
			sf::Packet get_packet;
			if (list_clients_[i]->receive(get_packet) == sf::Socket::Done) {				
				while (get_packet.getDataSize() > 0 && !get_packet.endOfPacket()) {
					key = type_key = 0;
					get_packet >> key;
					get_packet >> type_key;
					Point_level_->InputKeyboard(i + 1, 
						(sf::Keyboard::Key)key, (sf::Event::EventType)type_key);
					/*std::cout << "Package received successfully <" << key
						<< ">: \t ip: "
						<< (*list_clients_[i]).getRemoteAddress() << std::endl;*/
				}
				get_packet.clear();
			}
		}
	}
}

void Engine::ClientManager() {
	sf::Packet resieve_id_packet;
	sf::Packet resieve_time_packet;
	if (tcp_socket_.connect(ip_client_connect_, 7777) == sf::Socket::Done) {
		client_id_object_ = 0;

		//Reseiving packet with ID
		tcp_socket_.receive(resieve_id_packet);
		resieve_id_packet >> client_id_object_;
		//Send packet for calculate ping
		tcp_socket_.send(resieve_id_packet);
		resieve_id_packet.clear();
		
		//Reseiving packet with level_time
		tcp_socket_.receive(resieve_time_packet);
		//<<<<<<<<<<<<<<<<< resieve_time_packet >> client_id_object_;

		// Receive packets: 
		RecvMessageFromServer();
	}
	else status_server_ = StatusServer::NOT_DETERMINED;

	tcp_socket_.disconnect();
}

//Get Intafomration to go client: BaseLevel->GetObjectToSendClient

void Engine::ServerMailingMessageToClients() {
	sf::Packet mailings_Packet;
	for (int client = 0; client < (int)list_clients_.size(); client++) {
		mailings_Packet = Point_level_->GetPacketToSendAllClient(client + 1, true);
		if (mailings_Packet.getDataSize() > 0) {
			/*std::cout << "Mailing packet to client <" << client << ">" << std::endl;*/
			if (list_clients_[client]->send(mailings_Packet) == sf::Socket::Done) {
				/*std::cout << "Mailing packages sent successfully!" << std::endl;*/
			}
			/*else std::cout << "Packages were not sent!" << std::endl;*/
		}
		mailings_Packet.clear();
	}
}

void Engine::ClientSendMessageToServer(sf::Packet& mailings_Packet) {
	if (tcp_socket_.send(mailings_Packet) == sf::Socket::Done) {}
		/*std::cout << "Package sent successfully!" << mailings_Packet.getDataSize() << std::endl;
	else std::cout << "Package was not sent!" << std::endl;*/
}

bool Engine::RecvMessageFromServer() {
	sf::Packet packet;
	while (status_server_ == StatusServer::CLIENT) {
		if (!pause_client_recv_) {
			std::this_thread::sleep_for(std::chrono::milliseconds(10));

			packet.clear();
			if (tcp_socket_.receive(packet) == sf::Socket::Done) {
				Point_level_->RecvPacketFromServer(packet);
				/*std::cout << std::endl << "Recieve packet from server ip: "
					<< tcp_socket_.getRemoteAddress() << std::endl;*/
				packet.clear();
			}
		}
	}
	return true;
}

void Engine::CleaningClients() {
	for (int i = 0; i < (int)list_clients_.size(); i++) {
		list_clients_[i]->disconnect();
		delete list_clients_[i];
	}
}