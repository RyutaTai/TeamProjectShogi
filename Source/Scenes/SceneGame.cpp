#include "SceneGame.h"

#include "../Core/Framework.h"
#include "../Graphics/Graphics.h"
#include "../Graphics/Camera.h"
#include "../Input/GamePad.h"
#include "../Game/Piece.h"
#include "../Game/PieceManager.h"

//	初期化
void SceneGame::Initialize()
{
	//	スプライト初期化
	//sprite_[static_cast<int>(SPRITE_GAME::BACK)] = std::make_unique<Sprite>(Graphics::Instance().GetDevice(), L"./Resources/Image/Game.png");
	sprite_[static_cast<int>(SPRITE_GAME::TUTORIAL1)] = std::make_unique<Sprite>(Graphics::Instance().GetDevice(), L"./Resources/Image/Tutorial1.png");
	sprite_[static_cast<int>(SPRITE_GAME::TUTORIAL2)] = std::make_unique<Sprite>(Graphics::Instance().GetDevice(), L"./Resources/Image/Tutorial2.png");
	sprite_[static_cast<int>(SPRITE_GAME::MIKE)] = std::make_unique<Sprite>(Graphics::Instance().GetDevice(), L"./Resources/Image/Mike.png");
	sprite_[static_cast<int>(SPRITE_GAME::RESULT)] = std::make_unique<Sprite>(Graphics::Instance().GetDevice(), L"./Resources/Image/Result.png");
	sprite_[static_cast<int>(SPRITE_GAME::PIECE_COUNT)] = std::make_unique<Sprite>(Graphics::Instance().GetDevice(), L"./Resources/Fonts/font6.png");
	sprite_[static_cast<int>(SPRITE_GAME::db)] = std::make_unique<Sprite>(Graphics::Instance().GetDevice(), L"./Resources/Fonts/font6.png");

	//	ステージ初期化
	//stage_ = std::make_unique<Stage>("./Resources/Model/cybercity-2099-v2/source/Cyber_City_2099_ANIM.fbx", true);//	シティモデル
	stage_ = std::make_unique<Stage>("./Resources/Model/tyasitu.fbx", true);//	茶室		
	shogiBoard_ = std::make_unique<ShogiBoard>("./Resources/Model/Shogi/shogiban.fbx",true);//	将棋盤
	
	D3D11_BUFFER_DESC desc;
	desc.ByteWidth = (sizeof(Graphics::SceneConstants));
	desc.Usage = D3D11_USAGE_DEFAULT;
	desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	desc.CPUAccessFlags = 0;
	desc.MiscFlags = 0;
	desc.StructureByteStride = 0;
	Graphics::Instance().GetDevice()->CreateBuffer(&desc, nullptr, sceneConstantBuffer_.GetAddressOf());

	//	カメラ初期設定
	Camera::Instance().Initialize();

	//	将棋の駒生成
	const int maxIndex = 9;	//駒の種類(モデルの数)

	//	駒の種類ごとの駒の数
	int pieceNum[maxIndex] =
	{
		18, // 歩
		2,  // 角
		2,  // 飛
		4,  // 香
		4,  // 桂
		4,  // 銀
		4,  // 金
		1,  // 王
		1,  // 玉
	};

	//	モデルのファイルパス設定
	//	駒の種類ごとのファイルパス
	std::string pieceFilaname[maxIndex] =
	{
		"./Resources/Model/Shogi/hohei.fbx",	// 歩
		"./Resources/Model/Shogi/kakugyo.fbx",	// 角
		"./Resources/Model/Shogi/hisha.fbx",	// 飛
		"./Resources/Model/Shogi/kyousha.fbx",	// 香
		"./Resources/Model/Shogi/keima.fbx",	// 桂
		"./Resources/Model/Shogi/ginsho.fbx",	// 銀
		"./Resources/Model/Shogi/kinsho.fbx",	// 金
		"./Resources/Model/Shogi/ohsho.fbx",	// 王
		"./Resources/Model/Shogi/gyokusho.fbx",	// 玉
	};

	PieceManager& pieceManager = PieceManager::Instance();
	for (int index = 0; index < maxIndex; index++)
	{
		for (int num = 0; num < pieceNum[index]; num++)
		{
			Piece* piece = new Piece(pieceFilaname[index].c_str(), true, true);	//	駒だけレイキャストtrue
			pieceManager.Register(piece);
		}
	}
	pieceManager.Initialize();

	//	ゲームインターバルタイマー初期化
	gameIntervalTimer_ = 2.0f;

<<<<<<< HEAD
	//	ゲームステート初期化
	Judge::Instance().SetGameState(Judge::GAME_STATE::TUTORIAL);	//	チュートリアル開始 
	tutorialCount = 1;
=======
	
}
>>>>>>> TeamProjectShogi/Tomy

	//TODO:処理分けたい
	//if (gameState_==nullptr)	//	ローディングシーンからゲームシーンに来た場合
	//{
		//SetGameState(GAME_STATE::TUTORIAL);	//	チュートリアル開始
	//}
	//else	//	ゲームを再スタートした場合
	//{
	//	SetGameState(GAME_STATE::START);	//	ゲーム開始
	//}
}

//	更新処理
void SceneGame::Update(const float& elapsedTime,HWND hwnd)
{
	GamePad& gamePad = Input::Instance().GetGamePad();

	Camera::Instance().SetTarget(shogiBoard_.get()->GetTransform()->GetPosition());
	Camera::Instance().Update(elapsedTime);

#if 1 //実験用
	if (gamePad.GetButtonDown() & GamePad::BTN_A)//Zキー
		Camera::Instance().LaunchCameraMove(DirectX::XMFLOAT3(0.0f, 25.0f, 3.0f), DirectX::XMFLOAT3(-1.5f, 0.0f, 0.0f), 3.0f);

#endif
	switch (Judge::Instance().GetGameState())	//	ゲームの状態で更新処理を分ける
	{
	case Judge::GAME_STATE::TUTORIAL:

		break;
	case Judge::GAME_STATE::START:

		break;
	case Judge::GAME_STATE::REC:

		break;
	case Judge::GAME_STATE::END:

		break;
	}

	gameIntervalTimer_ -= elapsedTime;									//	ゲーム開始タイマーカウントダウン
	if (gameIntervalTimer_ < 0)gameIntervalTimer_ = 0.0f;				//	
	PieceManager::Instance().Update(elapsedTime,gameIntervalTimer_);	//	駒の更新処理
	//player_.Update(elapsedTime,hwnd);									//	将棋ゲーム用	
}

//	描画処理
void SceneGame::Render()
{
	Graphics::SceneConstants sceneConstants;

	Camera::Instance().SetPerspectiveFov();

	DirectX::XMStoreFloat4x4(&sceneConstants.viewProjection_, Camera::Instance().GetViewMatrix() * Camera::Instance().GetProjectionMatrix());
	sceneConstants.lightDirection_ = { 0, -1,  0,  0 };
	sceneConstants.cameraPosition_ = { 0,  0,  1,  0 };
	Graphics::Instance().GetDeviceContext()->UpdateSubresource(sceneConstantBuffer_.Get(), 0, 0, &sceneConstants, 0, 0);
	Graphics::Instance().GetDeviceContext()->VSSetConstantBuffers(1, 1, sceneConstantBuffer_.GetAddressOf());
	Graphics::Instance().GetDeviceContext()->PSSetConstantBuffers(1, 1, sceneConstantBuffer_.GetAddressOf());

	//	Sprite
	{
		//sprite_[static_cast<int>(SPRITE_GAME::BACK)]->GetTransform()->SetSize(SCREEN_WIDTH, SCREEN_HEIGHT);
		//sprite_[static_cast<int>(SPRITE_GAME::BACK)]->Render();	//	ゲームスプライト描画

		sprite_[static_cast<int>(SPRITE_GAME::TUTORIAL1)]->GetTransform()->SetSize(SCREEN_WIDTH, SCREEN_HEIGHT);
		Graphics::Instance().GetShader()->SetRasterizerState(Shader::RASTERIZER_STATE::CULL_NONE);
		Graphics::Instance().GetShader()->SetDepthStencilState(Shader::DEPTH_STENCIL_STATE::ZT_OFF_ZW_OFF);

		switch (Judge::Instance().GetGameState())	//	ゲームの状態で処理を分ける
		{
		case Judge::GAME_STATE::TUTORIAL:
			if (tutorialCount == 1)
			{
				sprite_[SPRITE_GAME::TUTORIAL1]->Render();
			}
			else
			{
				sprite_[SPRITE_GAME::TUTORIAL2]->Render();
			}
			break;
		case Judge::GAME_STATE::START:
			sprite_[SPRITE_GAME::MIKE]->Render();
			break;
		case Judge::GAME_STATE::REC:
			sprite_[SPRITE_GAME::MIKE]->Render();
			break;
		case Judge::GAME_STATE::END:
			sprite_[SPRITE_GAME::RESULT]->Render();
			sprite_[static_cast<int>(SPRITE_GAME::PIECE_COUNT)]->Textout("12345.", 350, 600, 30, 25);
			sprite_[static_cast<int>(SPRITE_GAME::db)]->Textout("12345.", 350, 600, 30, 25);
			break;
		}
	}

	// Model
	{
		//	ステージ
		//	ステート設定
#if 0	//	シティモデル用
		Graphics::Instance().GetShader()->SetRasterizerState(Shader::RASTERIZER_STATE::CULL_NONE);	//	両面描画するため
		Graphics::Instance().GetShader()->SetDepthStencilState(Shader::DEPTH_STENCIL_STATE::ZT_ON_ZW_ON);
		Graphics::Instance().GetShader()->SetBlendState(Shader::BLEND_STATE::ALPHA);
#else	//	茶室用
		Graphics::Instance().GetShader()->SetRasterizerState(Shader::RASTERIZER_STATE::CULL_NONE);
		Graphics::Instance().GetShader()->SetDepthStencilState(Shader::DEPTH_STENCIL_STATE::ZT_ON_ZW_ON);
		Graphics::Instance().GetShader()->SetBlendState(Shader::BLEND_STATE::ALPHA);
#endif
		stage_->Render();
		//	将棋盤描画
		Graphics::Instance().GetShader()->SetRasterizerState(Shader::RASTERIZER_STATE::SOLID);
		Graphics::Instance().GetShader()->SetDepthStencilState(Shader::DEPTH_STENCIL_STATE::ZT_ON_ZW_ON);
		Graphics::Instance().GetShader()->SetBlendState(Shader::BLEND_STATE::ALPHA);
		shogiBoard_->Render();	//	将棋盤描画

		//	将棋の駒描画
		Graphics::Instance().GetShader()->SetRasterizerState(Shader::RASTERIZER_STATE::SOLID);
		Graphics::Instance().GetShader()->SetDepthStencilState(Shader::DEPTH_STENCIL_STATE::ZT_ON_ZW_ON);
		Graphics::Instance().GetShader()->SetBlendState(Shader::BLEND_STATE::ALPHA);
		PieceManager::Instance().Render();

	}

	//	TODO:デバッグプリミティブ
	{
		// デバッグレンダラ描画実行
		Graphics::Instance().GetDebugRenderer()->Render();
	}

}

//	終了化
void SceneGame::Finalize()
{
	//	スプライト終了化
	for (int i = 0; i < static_cast<int>(SPRITE_GAME::MAX); i++)
	{
		if (sprite_[i] != nullptr)
		{
			sprite_[i] = nullptr;
		}
	}
	stage_ = nullptr;
	shogiBoard_ = nullptr;	//	ステージ終了化
	//	エネミー終了化
	PieceManager::Instance().Clear();
	//	ステート終了化
	//gameState_ = {};
}

//	デバッグ描画
void SceneGame::DrawDebug()
{
	if (ImGui::TreeNode(u8"Cameraカメラ"))	//	カメラ
	{
		Camera::Instance().DrawDebug();
		ImGui::TreePop();
	}
	if (ImGui::TreeNode(u8"Tyasitu茶室"))	//	茶室
	{
		stage_->DrawDebug();
		ImGui::TreePop();
	}
	if (ImGui::TreeNode(u8"ShogiBoard将棋盤"))	//	将棋盤
	{
		shogiBoard_->DrawDebug();
		ImGui::TreePop();
	}
	PieceManager::Instance().DrawDebug();
}