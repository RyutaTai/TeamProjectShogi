#pragma once

#include "Character.h"

class Enemy :public Character
{
public:
	Enemy(const char* fileName, bool triangulate = false, bool usedAsCollider = false);
	Enemy() {}

protected:
	void ChoisePiece()	;			//	���I��
	void MovePiece()	override;	//	�I�񂾋�𓮂���

};

