#pragma once

#include <memory>

#include "Scene.h"
#include "../Resources/Sprite.h"
#include "../Audio/Audio.h"

class SceneTitle : public Scene
{
public:
	SceneTitle(){}
	~SceneTitle()override{}

	void Initialize()						override;
	void Finalize()							override;

	void Update(const float& elapsedTime, HWND hwnd)	override;
	void Render()							override;
	void DrawDebug()						override;

private:	//	�X�v���C�g
	enum class SPRITE_TITLE
	{
		BACK,		//	�w�i�摜
		TEXT_KEY,	//	Push to ����Key �̕\��
		MAX,		//	�X�v���C�g�̏����
	};
	std::unique_ptr<Sprite> sprite_[static_cast<int>(SPRITE_TITLE::MAX)];
	
private:	//	�I�[�f�B�I
	Audio audioInstance_ = Audio::Instance();
	enum class AUDIO_SE_TITLE
	{
		CHOICE,		//	�I����
		DECISION,	//	���艹
		MAX,		//SE�ő吔
	};
	enum class AUDIO_BGM_TITLE
	{
		TITLE,		//	�^�C�g��BGM
		MAX,		//	BGM�ő吔
	};
	static const int SE_MAX_	= 2;
	static const int BGM_MAX_	= 1;
	std::unique_ptr<Audio> bgm_[BGM_MAX_];
	std::unique_ptr<Audio> se_[SE_MAX_];
};

