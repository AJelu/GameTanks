#include "objects.h"


BaseObject::BaseObject() { id_object_ = 0; }

BaseObject::BaseObject(int const& id_object) { this->SetIdObject(id_object); }

int BaseObject::GetIdObject() { return id_object_; }

void BaseObject::SetIdObject(int const& id_object) { id_object_ = id_object; }

std::string BaseObject::ClassName() { return "BaseObject"; }

bool BaseObject::CreatePacket(sf::Packet& Packet) {
    Packet << id_object_;
    return false;
}

bool BaseObject::SetDataFromPacket(sf::Packet& Packet) {
    return false;
}

BaseObject::~BaseObject() {}