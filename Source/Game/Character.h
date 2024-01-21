#pragma once

#include "GameObject.h"

class Character :public GameObject
{
public:
	Character(const char* fileName, bool triangulate = false, bool usedAsCollider = false);
	Character() {}
	virtual ~Character() {}

protected:
	//virtual void ChoisePiece() {}	//	駒を選択
	virtual void MovePiece() {}		//	選んだ駒を動かす

};

