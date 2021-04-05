#include "objects.h"


BaseObject::BaseObject() { id_object_ = 0; }

BaseObject::BaseObject(int const& id_object) { this->SetIdObject(id_object); }

int BaseObject::GetIdObject() { return id_object_; }

void BaseObject::SetIdObject(int const& id_object) { id_object_ = id_object; }

std::string BaseObject::ClassName() { return "BaseObject"; }

bool BaseObject::CreatePacket(sf::Packet& Packet) {
    Packet << id_object_ << this->ClassName();
    return true;
}

bool BaseObject::SetDataFromPacket(sf::Packet& Packet) {
    return true;
}

bool BaseObject::GetNeedSynchByLan() { return need_synch_by_lan_; }

void BaseObject::SetNeedSynchByLan(bool const& need_synch_by_lan) {
    need_synch_by_lan_ = need_synch_by_lan;
}

BaseObject::~BaseObject() {}