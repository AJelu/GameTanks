#include "engine.h"

void Engine::EngineInpute() {
    if (status_server_ == StatusServer::SERVER) {
        //Point_level.InputKeyboard(bool, key);
        //Point_level.InputMouse(event_type, mouse_position);
        Point_level_->InputEnemy();

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) &&
            !sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
            Point_level_->InputKeyboard(0, sf::Keyboard::Up);
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) &&
            !sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            Point_level_->InputKeyboard(0, sf::Keyboard::Left);
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) &&
            !sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            Point_level_->InputKeyboard(0, sf::Keyboard::Right);
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) &&
            !sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
            Point_level_->InputKeyboard(0, sf::Keyboard::Down);
        }
    }
    //Point_level_->InputKeyboard(0, sf::Keyboard::Space);
    else if (status_server_ == StatusServer::CLIENT) {
        sf::Packet send_packet;

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) &&
            !sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
            send_message = "Up";
            ClientSendMessageToServer(send_packet << send_message);
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) &&
            !sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            send_message = "Left";
            ClientSendMessageToServer(send_packet << send_message);
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) &&
            !sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            send_message = "Right";
            ClientSendMessageToServer(send_packet << send_message);
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) &&
            !sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
            send_message = "Down";
            ClientSendMessageToServer(send_packet << send_message);
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
            send_message = "Space";
            ClientSendMessageToServer(send_packet << send_message);
        }  
        send_packet.clear();
    }

    /* Testing restart connect server: */
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::R)) 
        status_server_ = StatusServer::NOT_DETERMINED;
    /*---------------------------------*/

    sf::Event event;
    while (Main_window_.pollEvent(event)) {
        Point_level_->InputMouse(event.type,
            sf::Vector2i(sf::Mouse::getPosition(Main_window_).x,
                sf::Mouse::getPosition(Main_window_).y));
        if (event.type == sf::Event::KeyReleased)
            Point_level_->InputKeyboard(0, event.key.code);
    }
}