#include "SceneGame.h"

#include "../Core/Framework.h"
#include "../Graphics/Graphics.h"
#include "../Graphics/Camera.h"
#include "../Input/GamePad.h"
#include "../Input/Microphone.h"
#include "../Game/Piece.h"
#include "../Game/PieceManager.h"
#include "../Others/Converter.h"
#include "SceneManager.h"
#include "../Scenes/SceneTitle.h"
#include "../Scenes/SceneLoading.h"

//	初期化
void SceneGame::Initialize()
{
	//	スプライト初期化
	//sprite_[static_cast<int>(SPRITE_GAME::BACK)] = std::make_unique<Sprite>(Graphics::Instance().GetDevice(), L"./Resources/Image/Game.png");
	sprite_[static_cast<int>(SPRITE_GAME::TUTORIAL1)] = std::make_unique<Sprite>(Graphics::Instance().GetDevice(), L"./Resources/Image/Tutorial1.png");
	sprite_[static_cast<int>(SPRITE_GAME::TUTORIAL2)] = std::make_unique<Sprite>(Graphics::Instance().GetDevice(), L"./Resources/Image/Tutorial2.png");
	sprite_[static_cast<int>(SPRITE_GAME::MIKE)] = std::make_unique<Sprite>(Graphics::Instance().GetDevice(), L"./Resources/Image/Mike.png");
	sprite_[static_cast<int>(SPRITE_GAME::RESULT)] = std::make_unique<Sprite>(Graphics::Instance().GetDevice(), L"./Resources/Image/Result2.png");
	sprite_[static_cast<int>(SPRITE_GAME::PIECE_COUNT)] = std::make_unique<Sprite>(Graphics::Instance().GetDevice(), L"./Resources/Fonts/font7.png");
	sprite_[static_cast<int>(SPRITE_GAME::db)] = std::make_unique<Sprite>(Graphics::Instance().GetDevice(), L"./Resources/Fonts/font7.png");
	sprite_[static_cast<int>(SPRITE_GAME::SELECT)] = std::make_unique<Sprite>(Graphics::Instance().GetDevice(), L"./Resources/Image/Title/Select.png");

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
	gameIntervalTimer_ = 5.0f;
	
	//	ゲームステート初期化
	Judge::Instance().SetGameState(Judge::GAME_STATE::START);	//	チュートリアル開始 
	tutorialCount = 1;			//	チュートリアルのページを1ページ目
	isResultRender_ = false;	//	リザルト描画フラグをfalse

	
}

//	リセット
void SceneGame::Reset()
{
	//	カメラ初期設定
	Camera::Instance().Initialize();

	//PieceManager& pieceManager = PieceManager::Instance();
	//pieceManager.Initialize();

	//	ゲームインターバルタイマー初期化
	gameIntervalTimer_ = 5.0f;

	//	ゲームステート初期化
	Judge::Instance().SetGameState(Judge::GAME_STATE::START);	//	チュートリアル開始 
	tutorialCount = 1;			//	チュートリアルのページを1ページ目
	isResultRender_ = false;	//	リザルト描画フラグをfalse

}

//	更新処理
void SceneGame::Update(const float& elapsedTime,HWND hwnd)
{
	GamePad& gamePad = Input::Instance().GetGamePad();

	Camera::Instance().SetTarget(shogiBoard_.get()->GetTransform()->GetPosition());
	Camera::Instance().Update(elapsedTime);

#if 0 //実験用
	if (gamePad.GetButtonDown() & GamePad::BTN_A)//Zキー
		Camera::Instance().LaunchCameraMove(DirectX::XMFLOAT3(0.0f, 25.0f, 3.0f), DirectX::XMFLOAT3(-1.5f, 0.0f, 0.0f), 3.0f);

#endif
	//	ゲームのステート毎の更新処理
	switch (Judge::Instance().GetGameState())	//	ゲームの状態で更新処理を分ける
	{
	case Judge::GAME_STATE::TUTORIAL:
		TutorialUpdate();
		break;
	case Judge::GAME_STATE::START:
		StartUpdate();
		break;
	case Judge::GAME_STATE::RECREADY:
		RecReadyUpdate();
		break;
	case Judge::GAME_STATE::REC:
		RecUpdate();
		break;
	case Judge::GAME_STATE::RESULT:
		ResultUpdate();
		break;
	}

	//gameIntervalTimer_ -= elapsedTime;					//	ゲーム開始タイマーカウントダウン
	//if (gameIntervalTimer_ < 0)gameIntervalTimer_ = 0.0f;	//	

	PieceManager::Instance().Update(elapsedTime);			//	駒の更新処理

	//player_.Update(elapsedTime,hwnd);						//	将棋ゲーム用	
}

//	ステートごとの更新処理
//	TUTORIALステート更新処理
void SceneGame::TutorialUpdate()
{
	GamePad& gamePad = Input::Instance().GetGamePad();

	if (gamePad.GetButtonDown() & GamePad::BTN_RIGHT)
	{
		tutorialCount += 1;
	}

	if (tutorialCount >= TUTORIAL_MAX && (gamePad.GetButtonDown() & GamePad::BTN_START))	//	Enterキー
	{
		Judge::Instance().SetGameState(Judge::GAME_STATE::START);	//	ゲーム開始ステートへ遷移
	}
}

//	STARTステート更新処理
void SceneGame::StartUpdate()
{
	GamePad& gamePad = Input::Instance().GetGamePad();

	if ((gamePad.GetButtonDown() & GamePad::BTN_SPACE))	//	スペースキー
	{
		Judge::Instance().SetGameState(Judge::GAME_STATE::RECREADY);	//	RECステートへ遷移
	}
}

//	RECREADYステート更新処理
void SceneGame::RecReadyUpdate()
{
	GamePad& gamePad = Input::Instance().GetGamePad();

	if(!Microphone::Instance().IsStart())
	{
		Microphone::Instance().StartRecording(timer_);//	録音開始
	}
	if (Microphone::Instance().GetOnRecording()) //	録音中
		Judge::Instance().SetGameState(Judge::GAME_STATE::REC);	//	Resultステートへ遷移
}

//	RECステート更新処理
void SceneGame::RecUpdate()
{
	
	if (Microphone::Instance().ThreadStoped()) // 録音終了したら
	{
		Microphone::Instance().StopRecording();	//
		//	最大db数取得
		decibel = Microphone::Instance().Sort();
		gameIntervalTimer_ -= Framework::tictoc_.GetDeltaTime();	//	ゲーム開始タイマーカウントダウン
		if (gameIntervalTimer_ <= 0)
		{
			gameIntervalTimer_ = 0.0f;
			Judge::Instance().SetGameState(Judge::GAME_STATE::RESULT);
		}
	}
}

//	RESULTステート更新処理
void SceneGame::ResultUpdate()
{
	//TODO:カメラ演出
	//Camera::Instance().LaunchCameraMove(DirectX::XMFLOAT3(0.0f, 25.0f, 3.0f), DirectX::XMFLOAT3(-1.5f, 0.0f, 0.0f), 3.0f);
	if (!Camera::Instance().IsCameraMove())isResultRender_ = true;
	
	GamePad& gamePad = Input::Instance().GetGamePad();
	if (gamePad.GetButtonDown() & GamePad::BTN_UP)
	{
		resultSelect_ = RESULT_SELECT::ReStart;
	}

	else if (gamePad.GetButtonDown() & GamePad::BTN_DOWN)
	{
		resultSelect_ = RESULT_SELECT::Title;
	}

	//	Enterキーを押したら切り替え
	if (gamePad.GetButtonDown() & GamePad::BTN_START)
	{
		if (resultSelect_ == RESULT_SELECT::ReStart)Reset();	//	ゲーム開始
		if (resultSelect_ == RESULT_SELECT::Title)SceneManager::Instance().ChangeScene(new SceneTitle);	//	チュートリアル開始

	}

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

	//	Sprite
	{
		//sprite_[static_cast<int>(SPRITE_GAME::BACK)]->GetTransform()->SetSize(SCREEN_WIDTH, SCREEN_HEIGHT);
		//sprite_[static_cast<int>(SPRITE_GAME::BACK)]->Render();	//	ゲームスプライト描画

		Graphics::Instance().GetShader()->SetDepthStencilState(Shader::DEPTH_STENCIL_STATE::ZT_ON_ZW_ON);
		Graphics::Instance().GetShader()->SetBlendState(Shader::BLEND_STATE::ALPHA);
		Graphics::Instance().GetShader()->SetRasterizerState(Shader::RASTERIZER_STATE::CULL_NONE);//	各ステート毎のスプライト描画
		
		switch (Judge::Instance().GetGameState())	//	ゲームの状態で処理を分ける
		{
		case Judge::GAME_STATE::TUTORIAL:
			if (tutorialCount == 1)
			{
				sprite_[SPRITE_GAME::TUTORIAL1]->GetTransform()->SetSize(SCREEN_WIDTH, SCREEN_HEIGHT);
				sprite_[SPRITE_GAME::TUTORIAL1]->Render();
			}
			else
			{
				sprite_[SPRITE_GAME::TUTORIAL2]->GetTransform()->SetSize(SCREEN_WIDTH, SCREEN_HEIGHT);
				sprite_[SPRITE_GAME::TUTORIAL2]->Render();
			}
			break;
		case Judge::GAME_STATE::START:
			Graphics::Instance().GetShader()->SetBlendState(Shader::BLEND_STATE::ALPHA);
			sprite_[SPRITE_GAME::MIKE]->GetTransform()->SetSize(460, 460);
			sprite_[SPRITE_GAME::MIKE]->GetTransform()->SetTexSize(460, 460);
			sprite_[SPRITE_GAME::MIKE]->Render();
			break;
		case Judge::GAME_STATE::REC:
			sprite_[SPRITE_GAME::MIKE]->GetTransform()->SetTexPosX(460);
			if (!Microphone::Instance().ThreadStoped()) // 録音終了してなかったら
			{
				sprite_[SPRITE_GAME::MIKE]->Render();
			}
			break;
		case Judge::GAME_STATE::RESULT:
			if (isResultRender_)	//	リザルト描画フラグ(カメラ演出終わったら描画したい)
			{
				//	落とした駒の数取得
				int dropPiece = Piece::PIECE_MAX - PieceManager::Instance().GetRemainCount();

				sprite_[SPRITE_GAME::RESULT]->Render();
				sprite_[static_cast<int>(SPRITE_GAME::PIECE_COUNT)]->Textout(IntegerToString(dropPiece), 400, 500, 75, 150, 0.5f, 0.5f, 0.5f, 1.0f);
				sprite_[static_cast<int>(SPRITE_GAME::db)]->Textout(IntegerToString(static_cast<int>(decibel)), 925, 500, 75, 150, 1.0f,0.0f,0.0f);
			
				if (resultSelect_ == RESULT_SELECT::ReStart)
					sprite_[SPRITE_GAME::SELECT]->GetTransform()->SetPosition(DirectX::XMFLOAT2(1240, 410));
				else if (resultSelect_ == RESULT_SELECT::Title)
					sprite_[SPRITE_GAME::SELECT]->GetTransform()->SetPosition(DirectX::XMFLOAT2(1240, 564));
				sprite_[SPRITE_GAME::SELECT]->Render();
			}
			break;
		}
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