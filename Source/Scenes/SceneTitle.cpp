#include "SceneTitle.h"

#include "../Graphics/Graphics.h"
#include "../Resources/Texture.h"
#include "../Input/GamePad.h"
#include "../Scenes/SceneManager.h"
#include "../Scenes/SceneLoading.h"
#include "../Scenes/SceneGame.h"

//	������
void SceneTitle::Initialize()
{
	sprite_[static_cast<int>(SPRITE_TITLE::BACK)]		= std::make_unique<Sprite>(Graphics::Instance().GetDevice(), L"./Resources/Image/Title.png");
	sprite_[static_cast<int>(SPRITE_TITLE::TEXT_KEY)]	= std::make_unique<Sprite>(Graphics::Instance().GetDevice(), L"./Resources/Fonts/font6.png");

	// �I�[�f�B�I������
	audioInstance_.Initialize();
	bgm_[0] = std::make_unique<Audio>(audioInstance_.GetXAudio2(), L"./Resources/Audio/BGM/009.wav");
	/*se_[0] = std::make_unique<Audio>(audioInstance_.GetXAudio2(), L"./Resources/Audio/SE/0footsteps-of-a-runner-on-gravel.wav");
	se_[1] = std::make_unique<Audio>(audioInstance_.GetXAudio2(), L"./Resources/Audio/SE/0footsteps-dry-leaves-g.wav");
	se_[2] = std::make_unique<Audio>(audioInstance_.GetXAudio2(), L"./Resources/Audio/SE/0explosion-8-bit.wav");*/

}

//	�I����
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
	
//	�X�V����
void SceneTitle::Update(const float& elapsedTime, HWND hwnd)
{
	GamePad& gamePad = Input::Instance().GetGamePad();

	const GamePadButton anyButton =
		GamePad::BTN_A  //Z
		| GamePad::BTN_B  //X
		| GamePad::BTN_X  //C
		| GamePad::BTN_Y; //V

	//	TODO:�Ȃɂ��{�^������������Q�[���V�[���֐؂�ւ�
	if (gamePad.GetButtonDown() & anyButton) {
		SceneManager::Instance().ChangeScene(new SceneLoading(new SceneGame));
	}

	//	Enter�L�[����������Q�[���V�[���֐؂�ւ�
	if (GetAsyncKeyState(VK_RETURN))
	{
		SceneManager::Instance().ChangeScene(new SceneLoading(new SceneGame));
	}

	//	BGM�Đ�
	//bgm_[0]->Play();
}

//	�`�揈��
void SceneTitle::Render()
{	
	// �^�C�g���X�v���C�g�`��
	sprite_[static_cast<int>(SPRITE_TITLE::BACK)]->Render();
	sprite_[static_cast<int>(SPRITE_TITLE::TEXT_KEY)]->Textout("12345.", 350, 600, 30, 25);
}

//	�f�o�b�O�`��
void SceneTitle::DrawDebug()
{
	if (ImGui::TreeNode("Sprite"))	//	�^�C�g�����
	{
		if (ImGui::TreeNode("Back"))	//	�^�C�g�����
		{
			sprite_[static_cast<int>(SPRITE_TITLE::BACK)]->DrawDebug();
			ImGui::TreePop();
		}
		if (ImGui::TreeNode("TextKey"))	//	�L�[�e�L�X�g
		{
			sprite_[static_cast<int>(SPRITE_TITLE::TEXT_KEY)]->DrawDebug();
			ImGui::TreePop();
		}
	}
}
