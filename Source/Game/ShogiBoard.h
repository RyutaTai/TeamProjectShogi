#pragma once

#include "GameObject.h"

class ShogiBoard : public GameObject
{
public:
	ShogiBoard(const char* filename, bool triangulate = false);
	ShogiBoard() {}
	~ShogiBoard();

	//	唯一のインスタンス取得
	static ShogiBoard& Instance()
	{
		static ShogiBoard instance_;
		return instance_;
	}

	void Render();
	void DrawDebug();

};