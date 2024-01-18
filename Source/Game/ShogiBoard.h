#pragma once

#include "GameObject.h"

class ShogiBoard : public GameObject
{
public:
	ShogiBoard(const char* filename, bool triangulate = false);
	ShogiBoard() {}
	~ShogiBoard();

	//	�B��̃C���X�^���X�擾
	static ShogiBoard& Instance()
	{
		static ShogiBoard instance_;
		return instance_;
	}

	void Render();
	void DrawDebug();

};