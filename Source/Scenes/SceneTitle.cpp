#include "SceneTitle.h"

#include "../Graphics/Graphics.h"
#include "../Resources/Texture.h"
#include "../Input/GamePad.h"
#include "../Scenes/SceneManager.h"
#include "../Scenes/SceneLoading.h"
#include "../Scenes/SceneGame.h"

extern LONG SCREEN_WIDTH{ 1920 };

//	初期化
void SceneTitle::Initialize()
{
	sprite_[SPRITE_TITLE::BACK]		= std::make_unique<Sprite>(Graphics::Instance().GetDevice(), L"./Resources/Image/Title/TitleBuck.png");
	sprite_[SPRITE_TITLE::Select]	= std::make_unique<Sprite>(Graphics::Instance().GetDevice(), L"./Resources/Image/Title/Select.png");
	sprite_[SPRITE_TITLE::LoadingBar]	= std::make_unique<Sprite>(Graphics::Instance().GetDevice(), L"./Resources/Image/Title/LoadingBar.png");
	sprite_[SPRITE_TITLE::LoadingCompleteBar]	= std::make_unique<Sprite>(Graphics::Instance().GetDevice(), L"./Resources/Image/Title/LoadingComplete.png");
	sprite_[SPRITE_TITLE::Select]->GetTransform()->SetPosition(DirectX::XMFLOAT2(522, 722));
	sprite_[SPRITE_TITLE::LoadingBar]->GetTransform()->SetPosition(DirectX::XMFLOAT2(0, 535));
	sprite_[SPRITE_TITLE::LoadingCompleteBar]->GetTransform()->SetPosition(DirectX::XMFLOAT2(-1920, 535));

	// オーディオ初期化
	audioInstance_.Initialize();
	bgm_[0] = std::make_unique<Audio>(audioInstance_.GetXAudio2(), L"./Resources/Audio/BGM/009.wav");

	nextScene_ = new SceneGame();
	
	thread_ = new std::thread(LoadingThread, this);


	/*se_[0] = std::make_unique<Audio>(audioInstance_.GetXAudio2(), L"./Resources/Audio/SE/0footsteps-of-a-runner-on-gravel.wav");
	se_[1] = std::make_unique<Audio>(audioInstance_.GetXAudio2(), L"./Resources/Audio/SE/0footsteps-dry-leaves-g.wav");
	se_[2] = std::make_unique<Audio>(audioInstance_.GetXAudio2(), L"./Resources/Audio/SE/0explosion-8-bit.wav");*/

}

//	終了化
void SceneTitle::Finalize()
{
	for (int i = 0; i < static_cast<int>(SPRITE_TITLE::MAX); i++)
	{
		if (sprite_[i] != nullptr)
		{
			sprite_[i] = nullptr;
		}
	}
}
	
//	更新処理
void SceneTitle::Update(const float& elapsedTime, HWND hwnd)
{
	GamePad gamePad;
	gamePad.Acquire();
	static const int BUTTON_MAX = 4;

	GamePad::Button anyButton[BUTTON_MAX] =
	{ 
		GamePad::Button::A,		//	Z
		GamePad::Button::B,		//	X
		GamePad::Button::X,		//	C
		GamePad::Button::Y,		//	V
	};

	if(gamePad.ButtonState(GamePad::Button::LEFT))
	{
		sprite_[SPRITE_TITLE::Select]->GetTransform()->SetPosition(DirectX::XMFLOAT2(522, 722));

	    //	Enterキーを押したらゲームシーンへ切り替え
		if (gamePad.ButtonState(GamePad::Button::ENTER, TriggerMode::NONE))
		{
			now_loading = true;
		}
	}
	if (gamePad.ButtonState(GamePad::Button::RIGHT))
	{
		sprite_[SPRITE_TITLE::Select]->GetTransform()->SetPosition(DirectX::XMFLOAT2(1015, 722));
	}

	////	なにかボタンを押したらゲームシーンへ切り替え
	//for (int i = 0; i < BUTTON_MAX; i++)
	//{
	//	if (gamePad.ButtonState(anyButton[i], TriggerMode::NONE))
	//	{
	//		SceneManager::Instance().ChangeScene(new SceneLoading(new SceneGame));
	//		break;
	//	}
	//}

	////	Enterキーを押したらゲームシーンへ切り替え
	//if (gamePad.ButtonState(GamePad::Button::ENTER, TriggerMode::NONE))
	//{
	//	SceneManager::Instance().ChangeScene(new SceneLoading(new SceneGame));
	//}

	LoadEasing();

	if (nextScene_->IsReady())
	{
		if (loading_complete)
			SceneManager::Instance().ChangeScene(new SceneGame);
	}

    //	BGM再生
	bgm_[0]->Play();
}

//	描画処理
void SceneTitle::Render()
{	
	// タイトルスプライト描画
	for (int sprite_i = 0; sprite_i < SPRITE_TITLE::MAX; sprite_i++)
	{
	    sprite_[sprite_i]->Render();
	}
}

//	デバッグ描画
void SceneTitle::DrawDebug()
{
	if (ImGui::TreeNode("Sprite"))	//	タイトル画面
	{
		if (ImGui::TreeNode("Back"))	//	タイトル画面
		{
			sprite_[static_cast<int>(SPRITE_TITLE::BACK)]->DrawDebug();
			ImGui::TreePop();
		}
		if (ImGui::TreeNode("bar"))	//	キーテキスト
		{
			sprite_[static_cast<int>(SPRITE_TITLE::LoadingCompleteBar)]->DrawDebug();
			ImGui::TreePop();
		}
		ImGui::TreePop();
	}
}

void SceneTitle::LoadingThread(SceneTitle* scene)
{
	//	COM関連の初期化でスレッド毎に呼ぶ必要がある
	CoInitialize(nullptr);

	//	次のシーンの初期化を行う
	scene->nextScene_->Initialize();

	//	スレッドが終わる前にCOM関連の終了化
	CoUninitialize();

	//	次のシーンの準備完了設定
	scene->nextScene_->SetReady();

}

void SceneTitle::LoadEasing()
{
	if (!now_loading)return;
    
	DirectX::XMFLOAT2 pos = sprite_[LoadingCompleteBar]->GetTransform()->GetPosition();
	pos.x += 10.0f;
	sprite_[LoadingCompleteBar]->GetTransform()->SetPosition(pos);

	if (sprite_[SPRITE_TITLE::LoadingCompleteBar]->GetTransform()->GetPositionX() > SCREEN_WIDTH)
	{
		loading_complete = true;
	}
}
