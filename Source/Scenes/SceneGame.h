#pragma once

#include "Scene.h"
#include "../Game/ShogiBoard.h"
#include "../Resources/Sprite.h"
#include "../Game/Stage.h"
#include "../Input/Input.h"
#include "../Game/Player.h"
#include "../Audio/Audio.h"

class SceneGame : public Scene
{
public:
	SceneGame(){}
	~SceneGame()override{}

	void Initialize()						override;
	void Finalize()							override;

	void Update(const float& elapsedTime, HWND hwnd)	override;
	void Render()							override;
	void DrawDebug()						override;


	//	ゲーム用変数
private:
	float gameIntervalTimer_;	//	ゲームがスタートするまでの時間
	int tutorialCount = 1;		//	チュートリアルのページ数カウント

private:	//	スプライト
	enum SPRITE_GAME	
	{
		//BACK,			//	背景画像
		TUTORIAL1,		//	チュートリアル画像1
		TUTORIAL2,		//	チュートリアル画像2
		MIKE,			//	マイク画像
		RESULT,			//	リザルト
		PIECE_COUNT,	//	テキスト落とした駒の数
		db,				//	テキストdb数
		MAX,			//	スプライトの上限数
	};

	std::unique_ptr<Sprite>		sprite_[static_cast<int>(SPRITE_GAME::MAX)];
	std::unique_ptr<Stage>		stage_;				//	茶室
	std::unique_ptr<ShogiBoard> shogiBoard_;		//	将棋盤
	Microsoft::WRL::ComPtr<ID3D11Buffer> sceneConstantBuffer_;

private:	//	オーディオ
	Audio audioInstance_ = Audio::Instance();
	enum class AUDIO_SE_GAME
	{
		CHOICE,		//	選択音
		DECISION,	//	決定音
		REC_START,	//	REC開始音
		REC_END,	//	REC終了音
		UP,			//	駒上昇音
		THRUST,		//	突撃音(突撃途中の風の音?)
		EXPLOSION,	//	爆発音
		MAX,		//	SE最大数
	};
	enum class AUDIO_BGM_GAME
	{
		NORMAL,		//	通常時BGM(チュートリアルとREC直前まで)
		REC,		//	REC中BGM
		THRUST,		//	突撃BGM
		RESULT,		//	リザルトBGM
		MAX,		//	BGM最大数
	};
	static const int SE_MAX_ = 2;
	static const int BGM_MAX_ = 1;
	std::unique_ptr<Audio> bgm_[BGM_MAX_];
	std::unique_ptr<Audio> se_[SE_MAX_];

};

