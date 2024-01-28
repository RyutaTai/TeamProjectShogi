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

private:	//	スプライト
	enum class SPRITE_TITLE
	{
		BACK,		//	背景画像
		TEXT_KEY,	//	Push to ○○Key の表示
		MAX,		//	スプライトの上限数
	};
	std::unique_ptr<Sprite> sprite_[static_cast<int>(SPRITE_TITLE::MAX)];
	
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
};

