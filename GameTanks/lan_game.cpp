#include "engine.h"

void Engine::LanGame() { //Test work with connection:
	//game_restart_ = true;

	//while (Main_window_.isOpen()) {
		//game_restart_ = false;

		//Show IP address:
		sf::IpAddress ip_local_ = sf::IpAddress::getLocalAddress();
		sf::IpAddress ip_public_ = sf::IpAddress::getPublicAddress(); //Get local IP
		std::cout << "Address local: " << ip_local_
			<< "; Address public: " << ip_public_ << std::endl << std::endl;

		/* Determining the type of connection: */
		std::string connect_type;
		do {
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
	//}
}

void Engine::ServerManager() {
	
	sf::TcpListener server;
	
	std::this_thread::sleep_for(std::chrono::milliseconds(250));
	server.listen(7777);
	tcp_selector_.add(server);
	std::cout << "I'm listening port 7777..." << std::endl;

	while (Main_window_.isOpen()) {
		if (tcp_selector_.wait()) {
			if (tcp_selector_.isReady(server)) {
				sf::TcpSocket* socket = new sf::TcpSocket;
				server.accept(*socket);

				sf::Packet get_packet;
				std::string connect_message;

				//New connect
				if (socket->receive(get_packet) == sf::Socket::Done) 
					get_packet >> connect_message;

				std::cout << "New client connect! \t ip: "
					<< socket->getRemoteAddress() << std::endl
					<< "Server recieve connect packet from client: " 
					<< connect_message
					<< std::endl;

				list_clients_.push_back(socket);
				tcp_selector_.add(*socket);
				
				get_packet.clear();
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

							get_packet.clear();

							//Send packet: ->SendMessageToClient()
							mailings_Packet << connect_message;
							for (int j = 0; j < (int)list_clients_.size(); j++) {
								std::cout << "Mailing packets to all clients!" << std::endl;
								list_clients_[j]->send(mailings_Packet); 
							} 

							mailings_Packet.clear();
						}
					}
				}
			}
		}
	}
} //Receive input and send BaseLevel

void Engine::ClientManager() {
	int index_packet = 0; /* Testing index packet */

	do {
		std::cout << "Connect to ip address: ";
		std::cin >> ip_enter_;

		if (tcp_socket_.connect(ip_enter_, 7777) == sf::Socket::Done) {
			tcp_socket_.setBlocking(false);

			sf::Packet send_packet;
			std::string connect_message = "connect packet " + std::to_string(index_packet);
			send_packet << connect_message;
			tcp_socket_.send(send_packet);
			send_packet.clear();

			break;
		}
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

void Engine::SendMessageToClient(sf::Packet& send_packet) {
	if (tcp_socket_.send(send_packet) == sf::Socket::Done)
		std::cout << "Package sent successfully!" << std::endl;
	else std::cout << "Package was not sent!" << std::endl;
}

bool Engine::RecvMessageFromServer() {
	//tcp_socket_.receive(packet_);
	//data unpack: packet >> data
	return false;
}
