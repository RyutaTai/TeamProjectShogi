#pragma once

#include "GameObject.h"

class Stage : public GameObject
{
public:
	Stage(const char* fileName, bool triangulate = false, bool usedAsCollider = false);
	Stage(){}
	~Stage();

	//	�B��̃C���X�^���X�擾
	static Stage& Instance()
	{
		static Stage instance_;
		return instance_;
	}

	void Render();		//	�`�揈��
	void DrawDebug();	//	�f�o�b�O�`��

};