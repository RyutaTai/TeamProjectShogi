#pragma once

#include "Scene.h"
#include "../Resources/Sprite.h"
#include "../Game/Stage.h"
#include "../Game/ShogiBoard.h"
#include "../Input/Input.h"
#include "../Game/Player.h"

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

	//	ターン切り替え (Player,Enemy,マイク入力の３つ？)
	void ChangeTurn();

private:
	enum class SPRITE_GAME	//	スプライト
	{
		BACK,		//	背景画像
		MAX,		//	スプライトの上限数
	};

	std::unique_ptr<Sprite> sprite_[static_cast<int>(SPRITE_GAME::MAX)];
	std::unique_ptr<Stage>	stage_;
	std::unique_ptr<ShogiBoard>	shogiBoard_;	//	将棋盤
	Microsoft::WRL::ComPtr<ID3D11Buffer> sceneConstantBuffer_;

private:	//ゲーム用変数
	bool	isMyTurn_ = true;			//	自分のターンかどうか
	float	allottedTime = 30.0f;	//	各プレイヤーの一手ごとの持ち時間
	Player player_;

};

