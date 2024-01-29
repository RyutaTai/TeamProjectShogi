#pragma once

#include "Character.h"

class Enemy :public Character
{
public:
	Enemy(const char* fileName, bool triangulate = false, bool usedAsCollider = false);
	Enemy() {}

protected:
	void ChoisePiece()	;			//	駒を選択
	void MovePiece()	override;	//	選んだ駒を動かす

};

