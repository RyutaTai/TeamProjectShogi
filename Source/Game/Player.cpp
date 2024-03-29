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

//	コンストラクタ
Player::Player(const char* fileName, bool triangulate, bool usedAsCollider)
	:Character(fileName, triangulate, usedAsCollider)
{

}

//	 更新処理
void Player::Update(float elapsedTime,HWND hwnd) 
{
	ChoisePiece(hwnd);	//	駒を選択
	MovePiece();		//	駒を動かす
}

//	駒を選択
void Player::ChoisePiece(HWND hwnd)	//	相手の駒を選べないようにする
{
	// RAYCAST
	if (GetAsyncKeyState(VK_LBUTTON) & 1)	//	マウス左クリック
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
			
			//	TOOD:レイキャスト レイが当たっていたら
			if (piece->GetModel()->Raycast(l0, l, pieceTransform, intersectionPoint, intersectedNormal, intersectedMesh, intersectedMaterial))
			{
				//OutputDebugStringA("Intersected : ");
				//OutputDebugStringA(intersectedMesh.c_str());
				//OutputDebugStringA(" : ");
				//OutputDebugStringA(intersectedMaterial.c_str());
				//OutputDebugStringA("\n");
				if (!piece->GetPieceInfo(i).isEnemy_)			//	選んだ駒が自分の駒なら
				{
					pieceManager.SetChoicePiece(i);				//	選んでいる駒をセット
					Judge::Instance().SetDuringChoice(true);	//	選択中フラグtrue
				}

			}
			else
			{
				//OutputDebugStringA("Unintersected...\n");
			}
		}
	}

}

//	選んだ駒を動かす
//	選んだ駒を登録したあとに呼ぶ
void Player::MovePiece()
{
	PieceManager& pieceManager = PieceManager::Instance();
	if (pieceManager.GetChoicePiece() != nullptr)
	{
		Piece::DirectionInfo direction[8] = {};
		int choicePieceIndex = pieceManager.GetChoicePieceIndex();
		for (int i = 0; i < Piece::PIECE_DIRECTION_MAX; i++)	//	選択されている駒が動ける方向取得(PIECE_DIRECTION_MAXになるまでに0が入る場合もある)
		{
			direction[i] = pieceManager.GetChoicePiece()->GetPieceInfo(choicePieceIndex).direction_[i];
		}
		ShogiBoard::Instance().EmptySquareInit(direction);		//	動けるマス、かつ、空いているマスにエフェクト出したい
		ShogiBoard::Instance().EmptySquareRender();

		Piece* choicePiece = pieceManager.GetChoicePiece();		//	選んだ駒を取得

		// TODO:置く場所を選んでから動くようにする
		//if (Judge::Instance().GetDuringChoice()&& (GetAsyncKeyState(VK_LBUTTON) & 1))//	選択中かつ、左クリックしたら
		//{
			pieceManager.Move(choicePieceIndex, ChoiceSquare().x, ChoiceSquare().y);//	駒を動かす
			choicePiece->PieceInfoUpdate(pieceManager.GetChoicePieceIndex());		//	駒を更新する
			pieceManager.RemoveChoicePiece();										//	選択されている駒リセット
		//}
	}
}

//	TODO:置くマスを選択 今は全部{1,1}になってる
DirectX::XMFLOAT2 Player::ChoiceSquare()
{
	PieceManager& pieceManager = PieceManager::Instance();

	return { 1,1 };
}


