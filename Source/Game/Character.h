#pragma once

#include "GameObject.h"

class Character :public GameObject
{
public:
	Character(const char* fileName, bool triangulate = false, bool usedAsCollider = false);
	Character() {}
	virtual ~Character() {}

protected:
	//virtual void ChoisePiece() {}	//	‹î‚ð‘I‘ð
	virtual void MovePiece() {}		//	‘I‚ñ‚¾‹î‚ð“®‚©‚·

};

