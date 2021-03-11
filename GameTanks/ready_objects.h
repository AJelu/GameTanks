#pragma once

#include "objects.h"

class RedTank : public TankObject {
protected:
	MovebleObject* Shot() override;

public:
	RedTank(int const& id_object, float const& spawn_x, float const& spawn_y, GameObject* Parrent = nullptr);

	void PlayAnimateDie() override;
	void PlayAnimateLife() override;
	void PlayAnimateMovePlus() override;
	void PlayAnimateMoveMinus() override;
	void PlayAnimateRotate—lockwise() override;
	void PlayAnimateRotate—ounterclockwise() override;
	void RestoreLife() override;
};

class Bullet : public MovebleObject {
private:
	void PlayAnimateDie() override;
	void PlayAnimateLife() override;
	void RestoreLife() override;

public:
	Bullet(int const& id_object, float const& spawn_x, float const& spawn_y, GameObject* Parrent = nullptr);
};