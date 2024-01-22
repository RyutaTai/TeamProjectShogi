#include "SceneGame.h"

#include "../Core/Framework.h"
#include "../Graphics/Graphics.h"
#include "../Graphics/Camera.h"
#include "../Input/GamePad.h"
#include "../Game/PieceManager.h"
#include "../Game/Piece.h"

//	������
void SceneGame::Initialize()
{
	//	�X�v���C�g������
	//sprite_[static_cast<int>(SPRITE_GAME::BACK)] = std::make_unique<Sprite>(Graphics::Instance().GetDevice(), L"./Resources/Image/Game.png");
	
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

	std::string filaname[maxIndex] =
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
			Piece* piece = new Piece(filaname[index].c_str(), true, true);	//	������C�L���X�gtrue
			pieceManager.Register(piece);
		}
	}
	pieceManager.Initialize();

}

//	�I����
void SceneGame::Finalize()
{
	//	�X�v���C�g�I����
	//for (int i = 0; i < static_cast<int>(SPRITE_GAME::MAX); i++)
	//{
	//	if (sprite_[i] != nullptr)
	//	{
	//		sprite_[i] = nullptr;
	//	}
	//}
	stage_=nullptr;
	shogiBoard_ = nullptr;	//	�X�e�[�W�I����
	//	�G�l�~�[�I����
	PieceManager::Instance().Clear();
}

//	�X�V����
void SceneGame::Update(const float& elapsedTime,HWND hwnd)
{
	GamePad gamePad;
	gamePad.Acquire();

	Camera::Instance().SetTarget(shogiBoard_.get()->GetTransform()->GetPosition());
	Camera::Instance().Update(elapsedTime);

#if 1 �����p
	if (gamePad.ButtonState(GamePad::Button::A))
		Camera::Instance().LaunchCameraMove(DirectX::XMFLOAT3(0.0f, 25.0f, 3.0f), DirectX::XMFLOAT3(-1.5f, 0.0f, 0.0f), 3.0f);

#endif


	PieceManager::Instance().Update(elapsedTime);
	player_.Update(elapsedTime,hwnd);
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

	//	Sprite
	{
		//sprite_[static_cast<int>(SPRITE_GAME::BACK)]->GetTransform()->SetSize(SCREEN_WIDTH, SCREEN_HEIGHT);
		//sprite_[static_cast<int>(SPRITE_GAME::BACK)]->Render();	//	�Q�[���X�v���C�g�`��
	}

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