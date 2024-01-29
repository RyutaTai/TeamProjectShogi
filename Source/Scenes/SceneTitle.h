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

<<<<<<< HEAD
private:	//	スプライト
	enum class SPRITE_TITLE
=======
	Scene* nextScene_ = nullptr;
	std::thread* thread_ = nullptr;

private:

	enum SPRITE_TITLE
>>>>>>> TeamProjectShogi/Tomy
	{
		BACK,		       // 背景画像
		LoadingBar,        // ロードバー
		LoadingCompleteBar,// ロード完了バー
		Select,            // 選択

		MAX,		       // スプライトの上限数
	};
	std::unique_ptr<Sprite> sprite_[SPRITE_TITLE::MAX];

	enum class TITLE_SELECT
	{
		Play,
		Tutorial,
	}
	titleSelect_ = TITLE_SELECT::Play;
	
<<<<<<< HEAD
=======

	//	ローディングスレッド
	static void LoadingThread(SceneTitle* scene);


private:


>>>>>>> TeamProjectShogi/Tomy
private:	//	オーディオ
	Audio audioInstance_ = Audio::Instance();
	enum class AUDIO_SE_TITLE
	{
		CHOICE,		//	選択音
		DECISION,	//	決定音
		MAX,		//SE最大数
	};
	enum class AUDIO_BGM_TITLE
	{
		TITLE,		//	タイトルBGM
		MAX,		//	BGM最大数
	};
	static const int SE_MAX_	= 2;
	static const int BGM_MAX_	= 1;
	std::unique_ptr<Audio> bgm_[BGM_MAX_];
	std::unique_ptr<Audio> se_[SE_MAX_];

	bool now_loading;
	bool loading_complete;
	void LoadEasing();
};

