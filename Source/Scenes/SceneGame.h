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


	//	�Q�[���p�ϐ�
private:
	float gameIntervalTimer_;	//	�Q�[�����X�^�[�g����܂ł̎���
	int tutorialCount = 1;		//	�`���[�g���A���̃y�[�W���J�E���g

private:	//	�X�v���C�g
	enum SPRITE_GAME	
	{
		//BACK,			//	�w�i�摜
		TUTORIAL1,		//	�`���[�g���A���摜1
		TUTORIAL2,		//	�`���[�g���A���摜2
		MIKE,			//	�}�C�N�摜
		RESULT,			//	���U���g
		PIECE_COUNT,	//	�e�L�X�g���Ƃ�����̐�
		db,				//	�e�L�X�gdb��
		MAX,			//	�X�v���C�g�̏����
	};

	std::unique_ptr<Sprite>		sprite_[static_cast<int>(SPRITE_GAME::MAX)];
	std::unique_ptr<Stage>		stage_;				//	����
	std::unique_ptr<ShogiBoard> shogiBoard_;		//	������
	Microsoft::WRL::ComPtr<ID3D11Buffer> sceneConstantBuffer_;

private:	//	�I�[�f�B�I
	Audio audioInstance_ = Audio::Instance();
	enum class AUDIO_SE_GAME
	{
		CHOICE,		//	�I����
		DECISION,	//	���艹
		REC_START,	//	REC�J�n��
		REC_END,	//	REC�I����
		UP,			//	��㏸��
		THRUST,		//	�ˌ���(�ˌ��r���̕��̉�?)
		EXPLOSION,	//	������
		MAX,		//	SE�ő吔
	};
	enum class AUDIO_BGM_GAME
	{
		NORMAL,		//	�ʏ펞BGM(�`���[�g���A����REC���O�܂�)
		REC,		//	REC��BGM
		THRUST,		//	�ˌ�BGM
		RESULT,		//	���U���gBGM
		MAX,		//	BGM�ő吔
	};
	static const int SE_MAX_ = 2;
	static const int BGM_MAX_ = 1;
	std::unique_ptr<Audio> bgm_[BGM_MAX_];
	std::unique_ptr<Audio> se_[SE_MAX_];

};

