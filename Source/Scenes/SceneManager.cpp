#include "SceneManager.h"

//	�f�X�g���N�^
SceneManager::~SceneManager()
{
	if (currentScene_) //	���݂̃V�[���I����
	{
		delete currentScene_;
		currentScene_ = nullptr;
	}
	if (nextScene_)	//���̃V�[���I����
	{
		delete nextScene_;
		nextScene_ = nullptr;
	}
}

//	�X�V����
void SceneManager::Update(const float& elapsedTime, HWND hwnd)
{
	if (nextScene_ != nullptr)//	���̃V�[�����ݒ肳��Ă�����N���A
	{
		Clear();
		currentScene_ = nextScene_;
		nextScene_ = nullptr;

		if (!currentScene_->IsReady())
		{
			currentScene_->Initialize();
		}
	}

	if (currentScene_ != nullptr)
	{
		currentScene_->Update(elapsedTime,hwnd);
#ifdef USE_IMGUI
		currentScene_->DrawDebug();
#endif// USE_IMGUI
	}
}

//	�`�揈��
void SceneManager::Render()
{
	if (currentScene_ != nullptr)
	{
		currentScene_->Render();
	}
}

//	�V�[���N���A
void SceneManager::Clear()
{
	if (currentScene_ != nullptr)
	{
		currentScene_->Finalize();
		delete currentScene_;
		currentScene_ = nullptr;
	}
}

//	�V�[���؂�ւ�
void SceneManager::ChangeScene(Scene* scene)
{
	nextScene_ = scene;
}