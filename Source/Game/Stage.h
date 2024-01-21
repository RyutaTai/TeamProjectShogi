#pragma once

#include "GameObject.h"

class Stage : public GameObject
{
public:
	Stage(const char* fileName, bool triangulate = false, bool usedAsCollider = false);
	Stage(){}
	~Stage();

	//	唯一のインスタンス取得
	static Stage& Instance()
	{
		static Stage instance_;
		return instance_;
	}

	void Render();		//	描画処理
	void DrawDebug();	//	デバッグ描画

};