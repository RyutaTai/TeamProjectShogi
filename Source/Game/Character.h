#pragma once

#include "GameObject.h"

class Character :public GameObject
{
public:
	Character(const char* fileName, bool triangulate = false, bool usedAsCollider = false);
	Character() {}
	virtual ~Character() {}

protected:
	//virtual void ChoisePiece() {}	//	���I��
	virtual void MovePiece() {}		//	�I�񂾋�𓮂���

};

