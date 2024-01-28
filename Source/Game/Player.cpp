#include "Player.h"

#include "../Input/Mouse.h"
#include "../Game/ShogiBoard.h"
#include "Judge.h"

// RAYCAST
// Convert a position in screen space to a position on near plane in world space.
DirectX::XMFLOAT3 ConvertScreenToWorld(LONG x/*screen*/, LONG y/*screen*/, float z/*ndc*/, D3D11_VIEWPORT vp, const DirectX::XMFLOAT4X4& view_projection)
{
	DirectX::XMFLOAT3 p;
	DirectX::XMStoreFloat3(&p,
		DirectX::XMVector3TransformCoord(
			DirectX::XMVector3TransformCoord(
				DirectX::XMVectorSet(static_cast<float>(x), static_cast<float>(y), z, 1),
				DirectX::XMMatrixInverse(NULL,
					DirectX::XMMatrixSet(
						vp.Width * 0.5f, 0.0f, 0.0f, 0.0f,
						0.0f, -vp.Height * 0.5f, 0.0f, 0.0f,
						0.0f, 0.0f, vp.MaxDepth - vp.MinDepth, 0.0f,
						vp.TopLeftX + vp.Width * 0.5f, vp.Height * 0.5f + vp.TopLeftY, vp.MinDepth, 1.0f))
			), DirectX::XMMatrixInverse(NULL, XMLoadFloat4x4(&view_projection))
		)
	);
	return p;
}

//	�R���X�g���N�^
Player::Player(const char* fileName, bool triangulate, bool usedAsCollider)
	:Character(fileName, triangulate, usedAsCollider)
{

}

//	 �X�V����
void Player::Update(float elapsedTime,HWND hwnd) 
{
	ChoisePiece(hwnd);	//	���I��
	MovePiece();		//	��𓮂���
}

//	���I��
void Player::ChoisePiece(HWND hwnd)	//	����̋��I�ׂȂ��悤�ɂ���
{
	// RAYCAST
	if (GetAsyncKeyState(VK_LBUTTON) & 1)	//	�}�E�X���N���b�N
	{
		POINT p;
		GetCursorPos(&p);
		ScreenToClient(hwnd, &p);

		D3D11_VIEWPORT viewports[D3D11_VIEWPORT_AND_SCISSORRECT_OBJECT_COUNT_PER_PIPELINE];
		UINT viewportCount = { D3D11_VIEWPORT_AND_SCISSORRECT_OBJECT_COUNT_PER_PIPELINE };
		Graphics::Instance().GetDeviceContext()->RSGetViewports(&viewportCount, viewports);
		UINT num_viewports{ 1 };

		DirectX::XMFLOAT4X4 viewProjectionMatrix;
		DirectX::XMStoreFloat4x4(&viewProjectionMatrix, Camera::Instance().GetViewMatrix() * Camera::Instance().GetProjectionMatrix());
		DirectX::XMFLOAT3 positionOnNearPlane = ConvertScreenToWorld(p.x, p.y, 0.0f, viewports[0], viewProjectionMatrix);

		DirectX::XMFLOAT3 cameraPosition;
		cameraPosition = { Camera::Instance().GetEye() };
		DirectX::XMVECTOR L0 = DirectX::XMLoadFloat3(&cameraPosition);
		DirectX::XMFLOAT3 l0;
		DirectX::XMStoreFloat3(&l0, L0);
		DirectX::XMFLOAT3 l;
		DirectX::XMStoreFloat3(&l, DirectX::XMVectorSubtract(XMLoadFloat3(&positionOnNearPlane),  L0));

		std::string intersectedMesh;
		std::string intersectedMaterial;
		DirectX::XMFLOAT3 intersectedNormal = {};
		PieceManager& pieceManager = PieceManager::Instance();
		Piece* piece;
		for (int i = 0; i < Piece::PIECE_MAX; i++)
		{
			piece = pieceManager.GetPiece(i);
			DirectX::XMFLOAT4X4 pieceTransform = {};
			const DirectX::XMMATRIX S{ DirectX::XMMatrixScaling(piece->GetTransform()->GetScale().x, piece->GetTransform()->GetScale().y, piece->GetTransform()->GetScale().z)
				* DirectX::XMMatrixScaling(piece->GetTransform()->GetScaleFactor(), piece->GetTransform()->GetScaleFactor(), piece->GetTransform()->GetScaleFactor()) };
			const DirectX::XMMATRIX R{ DirectX::XMMatrixRotationRollPitchYaw(piece->GetTransform()->GetRotationX(), piece->GetTransform()->GetRotationY(), piece->GetTransform()->GetRotationZ()) };
			const DirectX::XMMATRIX T{ DirectX::XMMatrixTranslation(piece->GetTransform()->GetPositionX(), piece->GetTransform()->GetPositionY(), piece->GetTransform()->GetPositionZ()) };
			//DirectX::XMStoreFloat4x4(&pieceTransform, piece->GetTransform()->CalcWorld());
			DirectX::XMStoreFloat4x4(&pieceTransform, S * R * T);
			
			//	TOOD:���C�L���X�g ���C���������Ă�����
			if (piece->GetModel()->Raycast(l0, l, pieceTransform, intersectionPoint, intersectedNormal, intersectedMesh, intersectedMaterial))
			{
				//OutputDebugStringA("Intersected : ");
				//OutputDebugStringA(intersectedMesh.c_str());
				//OutputDebugStringA(" : ");
				//OutputDebugStringA(intersectedMaterial.c_str());
				//OutputDebugStringA("\n");
				if (!piece->GetPieceInfo(i).isEnemy_)			//	�I�񂾋�����̋�Ȃ�
				{
					pieceManager.SetChoicePiece(i);				//	�I��ł������Z�b�g
					Judge::Instance().SetDuringChoice(true);	//	�I�𒆃t���Otrue
				}

			}
			else
			{
				//OutputDebugStringA("Unintersected...\n");
			}
		}
	}

}

//	�I�񂾋�𓮂���
//	�I�񂾋��o�^�������ƂɌĂ�
void Player::MovePiece()
{
	PieceManager& pieceManager = PieceManager::Instance();
	if (pieceManager.GetChoicePiece() != nullptr)
	{
		Piece::DirectionInfo direction[8] = {};
		int choicePieceIndex = pieceManager.GetChoicePieceIndex();
		for (int i = 0; i < Piece::PIECE_DIRECTION_MAX; i++)	//	�I������Ă�������������擾(PIECE_DIRECTION_MAX�ɂȂ�܂ł�0������ꍇ������)
		{
			direction[i] = pieceManager.GetChoicePiece()->GetPieceInfo(choicePieceIndex).direction_[i];
		}
		ShogiBoard::Instance().EmptySquareInit(direction);		//	������}�X�A���A�󂢂Ă���}�X�ɃG�t�F�N�g�o������
		ShogiBoard::Instance().EmptySquareRender();

		Piece* choicePiece = pieceManager.GetChoicePiece();		//	�I�񂾋���擾

		// TODO:�u���ꏊ��I��ł��瓮���悤�ɂ���
		//if (Judge::Instance().GetDuringChoice()&& (GetAsyncKeyState(VK_LBUTTON) & 1))//	�I�𒆂��A���N���b�N������
		//{
			pieceManager.Move(choicePieceIndex, ChoiceSquare().x, ChoiceSquare().y);//	��𓮂���
			choicePiece->PieceInfoUpdate(pieceManager.GetChoicePieceIndex());		//	����X�V����
			pieceManager.RemoveChoicePiece();										//	�I������Ă����Z�b�g
		//}
	}
}

//	TODO:�u���}�X��I�� ���͑S��{1,1}�ɂȂ��Ă�
DirectX::XMFLOAT2 Player::ChoiceSquare()
{
	PieceManager& pieceManager = PieceManager::Instance();

	return { 1,1 };
}


