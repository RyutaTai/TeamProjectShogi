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

private:
	enum class SPRITE_GAME	//	スプライト
	{
		BACK,		//	背景画像
		MIKE,		//	マイク画像
		MAX,		//	スプライトの上限数
	};

	std::unique_ptr<Sprite> sprite_[static_cast<int>(SPRITE_GAME::MAX)];
	std::unique_ptr<Stage>	stage_;				//	茶室
	std::unique_ptr<ShogiBoard>	shogiBoard_;	//	将棋盤
	Microsoft::WRL::ComPtr<ID3D11Buffer> sceneConstantBuffer_;
	Player player_;

private:	//	ゲーム用
	float gameIntervalTimer_;	//	ゲームがスタートするまでの時間

};

