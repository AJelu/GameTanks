#pragma once

#include "objects.h"

class RedTank : public TankObject {
protected:
	virtual MovebleObject* Shot() override;
public:
	RedTank(int const& id_object, float const& spawn_x, float const& spawn_y);

	virtual void PlayAnimateDie() override;
	virtual void PlayAnimateLife() override;
	virtual void PlayAnimateMovePlus() override;
	virtual void PlayAnimateMoveMinus() override;
	virtual void PlayAnimateRotate—lockwise() override;
	virtual void PlayAnimateRotate—ounterclockwise() override;
};