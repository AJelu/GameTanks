#pragma once

#include "objects.h"

class RedTank : public TankObject {
protected:
	virtual MovebleObject* Shot() override;
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