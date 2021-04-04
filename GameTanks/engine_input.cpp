#include "engine.h"

void Engine::EngineInpute() {
    Point_level_->InputEnemy();
    sf::Event event;
    while (Main_window_.pollEvent(event)) {
        Point_level_->InputMouse(event.type,
            sf::Vector2i(sf::Mouse::getPosition(Main_window_).x,
                sf::Mouse::getPosition(Main_window_).y));
        if (status_server_ == StatusServer::SERVER)
            Point_level_->InputKeyboard(0, event.key.code, event.type);
        else {
            send_packet << event.key.code;
            send_packet << event.type;
        }
    }
    if (status_server_ == StatusServer::CLIENT) {
        if (send_packet.getDataSize() > 0) ClientSendMessageToServer(send_packet);
        send_packet.clear();
    }
}