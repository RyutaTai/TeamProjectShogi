#pragma once

#include <memory>
#include <thread>

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

	Scene* nextScene_ = nullptr;
	std::thread* thread_ = nullptr;

private:

	enum SPRITE_TITLE
	{
		BACK,		       // �w�i�摜
		LoadingBar,        // ���[�h�o�[
		LoadingCompleteBar,// ���[�h�����o�[
		Select,            // �I��

		MAX,		       // �X�v���C�g�̏����
	};
	std::unique_ptr<Sprite> sprite_[SPRITE_TITLE::MAX];

	enum class TITLE_SELECT
	{
		Play,
		Tutorial,
	}
	titleSelect_ = TITLE_SELECT::Play;
	

	//	���[�f�B���O�X���b�h
	static void LoadingThread(SceneTitle* scene);


private:


private:	//	�I�[�f�B�I
	Audio audioInstance_ = Audio::Instance();
	static const int SE_MAX_	= 8;
	static const int BGM_MAX_	= 4;
	std::unique_ptr<Audio> bgm_[BGM_MAX_];
	std::unique_ptr<Audio> se_[SE_MAX_];

	bool now_loading;
	bool loading_complete;
	void LoadEasing();
};

