#include "SceneTitle.h"

#include "../Graphics/Graphics.h"
#include "../Resources/Texture.h"
#include "../Input/GamePad.h"
#include "../Scenes/SceneManager.h"
#include "../Scenes/SceneLoading.h"
#include "../Scenes/SceneGame.h"

extern LONG SCREEN_WIDTH{ 1920 };

//	������
void SceneTitle::Initialize()
{
    sprite_[SPRITE_TITLE::BACK] = std::make_unique<Sprite>(Graphics::Instance().GetDevice(), L"./Resources/Image/Title/TitleBuck.png");
    sprite_[SPRITE_TITLE::Select] = std::make_unique<Sprite>(Graphics::Instance().GetDevice(), L"./Resources/Image/Title/Select.png");
    sprite_[SPRITE_TITLE::LoadingBar] = std::make_unique<Sprite>(Graphics::Instance().GetDevice(), L"./Resources/Image/Title/LoadingBar.png");
    sprite_[SPRITE_TITLE::LoadingCompleteBar] = std::make_unique<Sprite>(Graphics::Instance().GetDevice(), L"./Resources/Image/Title/LoadingComplete.png");
    sprite_[SPRITE_TITLE::Select]->GetTransform()->SetPosition(DirectX::XMFLOAT2(522, 722));
    sprite_[SPRITE_TITLE::LoadingBar]->GetTransform()->SetPosition(DirectX::XMFLOAT2(0, 535));
    sprite_[SPRITE_TITLE::LoadingCompleteBar]->GetTransform()->SetPosition(DirectX::XMFLOAT2(-1920, 535));


    // �I�[�f�B�I������
    audioInstance_.Initialize();
    bgm_[0] = std::make_unique<Audio>(audioInstance_.GetXAudio2(), L"./Resources/Audio/BGM/009.wav");

    nextScene_ = new SceneGame();

    thread_ = new std::thread(LoadingThread, this);


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


    if (gamePad.GetButtonDown() & GamePad::BTN_LEFT)
        titleSelect_ = TITLE_SELECT::Play;

    else if (gamePad.GetButtonDown() & GamePad::BTN_RIGHT)
        titleSelect_ = TITLE_SELECT::Tutorial;


    //	Enter�L�[����������Q�[���V�[���֐؂�ւ�
    if (titleSelect_ == TITLE_SELECT::Play && gamePad.GetButtonDown() & GamePad::BTN_START)
    {
        now_loading = true;
    }


    LoadEasing();

    if (nextScene_->IsReady())
    {
        if (loading_complete)
            SceneManager::Instance().ChangeScene(nextScene_);
    }

    //	BGM�Đ�
    bgm_[0]->Play();

}

//	�`�揈��
void SceneTitle::Render()
{
    // �^�C�g���X�v���C�g�`��
    if (titleSelect_ == TITLE_SELECT::Play)
        sprite_[SPRITE_TITLE::Select]->GetTransform()->SetPosition(DirectX::XMFLOAT2(522, 722));
    else if (titleSelect_ == TITLE_SELECT::Tutorial)
        sprite_[SPRITE_TITLE::Select]->GetTransform()->SetPosition(DirectX::XMFLOAT2(1015, 722));

    for (int sprite_i = 0; sprite_i < SPRITE_TITLE::MAX; sprite_i++)
    {
        sprite_[sprite_i]->Render();
    }

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
        if (ImGui::TreeNode("bar"))	//	�L�[�e�L�X�g
        {
            sprite_[static_cast<int>(SPRITE_TITLE::LoadingCompleteBar)]->DrawDebug();
            ImGui::TreePop();
        }
        ImGui::TreePop();
    }
}

void SceneTitle::LoadingThread(SceneTitle* scene)
{
    //	COM�֘A�̏������ŃX���b�h���ɌĂԕK�v������
    CoInitialize(nullptr);

    //	���̃V�[���̏��������s��
    scene->nextScene_->Initialize();

    //	�X���b�h���I���O��COM�֘A�̏I����
    CoUninitialize();

    //	���̃V�[���̏��������ݒ�
    scene->nextScene_->SetReady();

}

void SceneTitle::LoadEasing()
{
    if (!now_loading)return;
    if (loading_complete)return;

    DirectX::XMFLOAT2 pos = sprite_[LoadingCompleteBar]->GetTransform()->GetPosition();

    if (!nextScene_->IsReady() && pos.x > -800.0f)
    {
        pos.x += 0.1f;
     
    }
    else if (nextScene_->IsReady())
        pos.x += 5.0f;
    else
        pos.x += 1.0f;

    sprite_[LoadingCompleteBar]->GetTransform()->SetPosition(pos);

    if (sprite_[SPRITE_TITLE::LoadingCompleteBar]->GetTransform()->GetPositionX() > 0)
    {
        loading_complete = true;
    }
}
