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

//	������
void SceneGame::Initialize()
{
	//	�X�v���C�g������
	//sprite_[static_cast<int>(SPRITE_GAME::BACK)] = std::make_unique<Sprite>(Graphics::Instance().GetDevice(), L"./Resources/Image/Game.png");
	sprite_[static_cast<int>(SPRITE_GAME::TUTORIAL1)] = std::make_unique<Sprite>(Graphics::Instance().GetDevice(), L"./Resources/Image/Tutorial1.png");
	sprite_[static_cast<int>(SPRITE_GAME::TUTORIAL2)] = std::make_unique<Sprite>(Graphics::Instance().GetDevice(), L"./Resources/Image/Tutorial2.png");
	sprite_[static_cast<int>(SPRITE_GAME::MIKE)] = std::make_unique<Sprite>(Graphics::Instance().GetDevice(), L"./Resources/Image/Mike.png");
	sprite_[static_cast<int>(SPRITE_GAME::RESULT)] = std::make_unique<Sprite>(Graphics::Instance().GetDevice(), L"./Resources/Image/Result2.png");
	sprite_[static_cast<int>(SPRITE_GAME::PIECE_COUNT)] = std::make_unique<Sprite>(Graphics::Instance().GetDevice(), L"./Resources/Fonts/font7.png");
	sprite_[static_cast<int>(SPRITE_GAME::db)] = std::make_unique<Sprite>(Graphics::Instance().GetDevice(), L"./Resources/Fonts/font7.png");
	sprite_[static_cast<int>(SPRITE_GAME::SELECT)] = std::make_unique<Sprite>(Graphics::Instance().GetDevice(), L"./Resources/Image/Title/Select.png");

	//	�X�e�[�W������
	//stage_ = std::make_unique<Stage>("./Resources/Model/cybercity-2099-v2/source/Cyber_City_2099_ANIM.fbx", true);//	�V�e�B���f��
	stage_ = std::make_unique<Stage>("./Resources/Model/tyasitu.fbx", true);//	����		
	shogiBoard_ = std::make_unique<ShogiBoard>("./Resources/Model/Shogi/shogiban.fbx",true);//	������
	
	D3D11_BUFFER_DESC desc;
	desc.ByteWidth = (sizeof(Graphics::SceneConstants));
	desc.Usage = D3D11_USAGE_DEFAULT;
	desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	desc.CPUAccessFlags = 0;
	desc.MiscFlags = 0;
	desc.StructureByteStride = 0;
	Graphics::Instance().GetDevice()->CreateBuffer(&desc, nullptr, sceneConstantBuffer_.GetAddressOf());

	//	�J���������ݒ�
	Camera::Instance().Initialize();

	//	�����̋��
	const int maxIndex = 9;	//��̎��(���f���̐�)

	//	��̎�ނ��Ƃ̋�̐�
	int pieceNum[maxIndex] =
	{
		18, // ��
		2,  // �p
		2,  // ��
		4,  // ��
		4,  // �j
		4,  // ��
		4,  // ��
		1,  // ��
		1,  // ��
	};

	//	���f���̃t�@�C���p�X�ݒ�
	//	��̎�ނ��Ƃ̃t�@�C���p�X
	std::string pieceFilaname[maxIndex] =
	{
		"./Resources/Model/Shogi/hohei.fbx",	// ��
		"./Resources/Model/Shogi/kakugyo.fbx",	// �p
		"./Resources/Model/Shogi/hisha.fbx",	// ��
		"./Resources/Model/Shogi/kyousha.fbx",	// ��
		"./Resources/Model/Shogi/keima.fbx",	// �j
		"./Resources/Model/Shogi/ginsho.fbx",	// ��
		"./Resources/Model/Shogi/kinsho.fbx",	// ��
		"./Resources/Model/Shogi/ohsho.fbx",	// ��
		"./Resources/Model/Shogi/gyokusho.fbx",	// ��
	};

	PieceManager& pieceManager = PieceManager::Instance();
	for (int index = 0; index < maxIndex; index++)
	{
		for (int num = 0; num < pieceNum[index]; num++)
		{
			Piece* piece = new Piece(pieceFilaname[index].c_str(), true, true);	//	������C�L���X�gtrue
			pieceManager.Register(piece);
		}
	}
	pieceManager.Initialize();

	//	�Q�[���C���^�[�o���^�C�}�[������
	gameIntervalTimer_ = 5.0f;
	
	//	�Q�[���X�e�[�g������
	Judge::Instance().SetGameState(Judge::GAME_STATE::START);	//	�`���[�g���A���J�n 
	tutorialCount = 1;			//	�`���[�g���A���̃y�[�W��1�y�[�W��
	isResultRender_ = false;	//	���U���g�`��t���O��false

	
}

//	���Z�b�g
void SceneGame::Reset()
{
	//	�J���������ݒ�
	Camera::Instance().Initialize();

	//PieceManager& pieceManager = PieceManager::Instance();
	//pieceManager.Initialize();

	//	�Q�[���C���^�[�o���^�C�}�[������
	gameIntervalTimer_ = 5.0f;

	//	�Q�[���X�e�[�g������
	Judge::Instance().SetGameState(Judge::GAME_STATE::START);	//	�`���[�g���A���J�n 
	tutorialCount = 1;			//	�`���[�g���A���̃y�[�W��1�y�[�W��
	isResultRender_ = false;	//	���U���g�`��t���O��false

}

//	�X�V����
void SceneGame::Update(const float& elapsedTime,HWND hwnd)
{
	GamePad& gamePad = Input::Instance().GetGamePad();

	Camera::Instance().SetTarget(shogiBoard_.get()->GetTransform()->GetPosition());
	Camera::Instance().Update(elapsedTime);

#if 0 //�����p
	if (gamePad.GetButtonDown() & GamePad::BTN_A)//Z�L�[
		Camera::Instance().LaunchCameraMove(DirectX::XMFLOAT3(0.0f, 25.0f, 3.0f), DirectX::XMFLOAT3(-1.5f, 0.0f, 0.0f), 3.0f);

#endif
	//	�Q�[���̃X�e�[�g���̍X�V����
	switch (Judge::Instance().GetGameState())	//	�Q�[���̏�ԂōX�V�����𕪂���
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

	//gameIntervalTimer_ -= elapsedTime;					//	�Q�[���J�n�^�C�}�[�J�E���g�_�E��
	//if (gameIntervalTimer_ < 0)gameIntervalTimer_ = 0.0f;	//	

	PieceManager::Instance().Update(elapsedTime);			//	��̍X�V����

	//player_.Update(elapsedTime,hwnd);						//	�����Q�[���p	
}

//	�X�e�[�g���Ƃ̍X�V����
//	TUTORIAL�X�e�[�g�X�V����
void SceneGame::TutorialUpdate()
{
	GamePad& gamePad = Input::Instance().GetGamePad();

	if (gamePad.GetButtonDown() & GamePad::BTN_RIGHT)
	{
		tutorialCount += 1;
	}

	if (tutorialCount >= TUTORIAL_MAX && (gamePad.GetButtonDown() & GamePad::BTN_START))	//	Enter�L�[
	{
		Judge::Instance().SetGameState(Judge::GAME_STATE::START);	//	�Q�[���J�n�X�e�[�g�֑J��
	}
}

//	START�X�e�[�g�X�V����
void SceneGame::StartUpdate()
{
	GamePad& gamePad = Input::Instance().GetGamePad();

	if ((gamePad.GetButtonDown() & GamePad::BTN_SPACE))	//	�X�y�[�X�L�[
	{
		Judge::Instance().SetGameState(Judge::GAME_STATE::RECREADY);	//	REC�X�e�[�g�֑J��
	}
}

//	RECREADY�X�e�[�g�X�V����
void SceneGame::RecReadyUpdate()
{
	GamePad& gamePad = Input::Instance().GetGamePad();

	if(!Microphone::Instance().IsStart())
	{
		Microphone::Instance().StartRecording(timer_);//	�^���J�n
	}
	if (Microphone::Instance().GetOnRecording()) //	�^����
		Judge::Instance().SetGameState(Judge::GAME_STATE::REC);	//	Result�X�e�[�g�֑J��
}

//	REC�X�e�[�g�X�V����
void SceneGame::RecUpdate()
{
	
	if (Microphone::Instance().ThreadStoped()) // �^���I��������
	{
		Microphone::Instance().StopRecording();	//
		//	�ő�db���擾
		decibel = Microphone::Instance().Sort();
		gameIntervalTimer_ -= Framework::tictoc_.GetDeltaTime();	//	�Q�[���J�n�^�C�}�[�J�E���g�_�E��
		if (gameIntervalTimer_ <= 0)
		{
			gameIntervalTimer_ = 0.0f;
			Judge::Instance().SetGameState(Judge::GAME_STATE::RESULT);
		}
	}
}

//	RESULT�X�e�[�g�X�V����
void SceneGame::ResultUpdate()
{
	//TODO:�J�������o
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

	//	Enter�L�[����������؂�ւ�
	if (gamePad.GetButtonDown() & GamePad::BTN_START)
	{
		if (resultSelect_ == RESULT_SELECT::ReStart)Reset();	//	�Q�[���J�n
		if (resultSelect_ == RESULT_SELECT::Title)SceneManager::Instance().ChangeScene(new SceneTitle);	//	�`���[�g���A���J�n

	}

}

//	�`�揈��
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
		//	�X�e�[�W
		//	�X�e�[�g�ݒ�
#if 0	//	�V�e�B���f���p
		Graphics::Instance().GetShader()->SetRasterizerState(Shader::RASTERIZER_STATE::CULL_NONE);	//	���ʕ`�悷�邽��
		Graphics::Instance().GetShader()->SetDepthStencilState(Shader::DEPTH_STENCIL_STATE::ZT_ON_ZW_ON);
		Graphics::Instance().GetShader()->SetBlendState(Shader::BLEND_STATE::ALPHA);
#else	//	�����p
		Graphics::Instance().GetShader()->SetRasterizerState(Shader::RASTERIZER_STATE::CULL_NONE);
		Graphics::Instance().GetShader()->SetDepthStencilState(Shader::DEPTH_STENCIL_STATE::ZT_ON_ZW_ON);
		Graphics::Instance().GetShader()->SetBlendState(Shader::BLEND_STATE::ALPHA);
#endif
		stage_->Render();
		//	�����Օ`��
		Graphics::Instance().GetShader()->SetRasterizerState(Shader::RASTERIZER_STATE::SOLID);
		Graphics::Instance().GetShader()->SetDepthStencilState(Shader::DEPTH_STENCIL_STATE::ZT_ON_ZW_ON);
		Graphics::Instance().GetShader()->SetBlendState(Shader::BLEND_STATE::ALPHA);
		shogiBoard_->Render();	//	�����Օ`��

		//	�����̋�`��
		Graphics::Instance().GetShader()->SetRasterizerState(Shader::RASTERIZER_STATE::SOLID);
		Graphics::Instance().GetShader()->SetDepthStencilState(Shader::DEPTH_STENCIL_STATE::ZT_ON_ZW_ON);
		Graphics::Instance().GetShader()->SetBlendState(Shader::BLEND_STATE::ALPHA);
		PieceManager::Instance().Render();

	}

	//	Sprite
	{
		//sprite_[static_cast<int>(SPRITE_GAME::BACK)]->GetTransform()->SetSize(SCREEN_WIDTH, SCREEN_HEIGHT);
		//sprite_[static_cast<int>(SPRITE_GAME::BACK)]->Render();	//	�Q�[���X�v���C�g�`��

		Graphics::Instance().GetShader()->SetDepthStencilState(Shader::DEPTH_STENCIL_STATE::ZT_ON_ZW_ON);
		Graphics::Instance().GetShader()->SetBlendState(Shader::BLEND_STATE::ALPHA);
		Graphics::Instance().GetShader()->SetRasterizerState(Shader::RASTERIZER_STATE::CULL_NONE);//	�e�X�e�[�g���̃X�v���C�g�`��
		
		switch (Judge::Instance().GetGameState())	//	�Q�[���̏�Ԃŏ����𕪂���
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
			if (!Microphone::Instance().ThreadStoped()) // �^���I�����ĂȂ�������
			{
				sprite_[SPRITE_GAME::MIKE]->Render();
			}
			break;
		case Judge::GAME_STATE::RESULT:
			if (isResultRender_)	//	���U���g�`��t���O(�J�������o�I�������`�悵����)
			{
				//	���Ƃ�����̐��擾
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

	//	TODO:�f�o�b�O�v���~�e�B�u
	{
		// �f�o�b�O�����_���`����s
		Graphics::Instance().GetDebugRenderer()->Render();
	}

}

//	�I����
void SceneGame::Finalize()
{
	//	�X�v���C�g�I����
	for (int i = 0; i < static_cast<int>(SPRITE_GAME::MAX); i++)
	{
		if (sprite_[i] != nullptr)
		{
			sprite_[i] = nullptr;
		}
	}
	stage_ = nullptr;
	shogiBoard_ = nullptr;	//	�X�e�[�W�I����
	//	�G�l�~�[�I����
	PieceManager::Instance().Clear();
	//	�X�e�[�g�I����
	//gameState_ = {};
}

//	�f�o�b�O�`��
void SceneGame::DrawDebug()
{
	if (ImGui::TreeNode(u8"Camera�J����"))	//	�J����
	{
		Camera::Instance().DrawDebug();
		ImGui::TreePop();
	}
	if (ImGui::TreeNode(u8"Tyasitu����"))	//	����
	{
		stage_->DrawDebug();
		ImGui::TreePop();
	}
	if (ImGui::TreeNode(u8"ShogiBoard������"))	//	������
	{
		shogiBoard_->DrawDebug();
		ImGui::TreePop();
	}
	PieceManager::Instance().DrawDebug();
}