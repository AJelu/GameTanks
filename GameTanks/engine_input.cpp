#include "engine.h"

void Engine::EngineInpute() {
    if (Status_server_ != StatusServer::CLIENT)
        Point_level_->InputEnemy();
    sf::Event event;
    while (Main_window_.pollEvent(event)) {
        Point_level_->InputMouse(event.type,
            sf::Vector2i(sf::Mouse::getPosition(Main_window_).x,
                sf::Mouse::getPosition(Main_window_).y));

        if (event.type == sf::Event::KeyPressed 
                || event.type == sf::Event::KeyReleased) {
            Point_level_->InputKeyboard(0, event.key.code, event.type);
            if (Status_server_ != StatusServer::SERVER) {
                Send_packet_ << event.key.code;
                Send_packet_ << event.type;
            }
        }
    }
    if (Status_server_ == StatusServer::CLIENT)
        if (Send_packet_.getDataSize() > 0) ClientSendMessageToServer(Send_packet_);
    Send_packet_.clear();
}