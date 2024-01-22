#include "Player.h"

#include "../Input/Mouse.h"

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
	ChoisePiece(hwnd);
}

//	駒を選択
void Player::ChoisePiece(HWND hwnd)
{
	// RAYCAST
	if (GetAsyncKeyState(VK_LBUTTON) & 1)
	{
		POINT p;
		GetCursorPos(&p);
		ScreenToClient(hwnd, &p);

		D3D11_VIEWPORT viewports[D3D11_VIEWPORT_AND_SCISSORRECT_OBJECT_COUNT_PER_PIPELINE];
		UINT viewportCount = { D3D11_VIEWPORT_AND_SCISSORRECT_OBJECT_COUNT_PER_PIPELINE };
		Graphics::Instance().GetDeviceContext()->RSGetViewports(&viewportCount, viewports);
		UINT num_viewports{ 1 };

		DirectX::XMFLOAT4X4 viewFloat4x4;
		DirectX::XMStoreFloat4x4(&viewFloat4x4, Camera::Instance().GetViewMatrix());
		DirectX::XMFLOAT3 positionOnNearPlane = ConvertScreenToWorld(p.x, p.y, 0.0f, viewports[0], viewFloat4x4);

		DirectX::XMFLOAT3 cameraPosition;
		cameraPosition = { Camera::Instance().GetEye() };
		DirectX::XMVECTOR L0 = DirectX::XMLoadFloat3(&cameraPosition);
		DirectX::XMFLOAT3 l0;
		DirectX::XMStoreFloat3(&l0, L0);
		DirectX::XMFLOAT3 l;
		DirectX::XMStoreFloat3(&l, DirectX::XMVectorSubtract(L0, XMLoadFloat3(&positionOnNearPlane)));

		std::string intersectedMesh;
		std::string intersectedMaterial;
		DirectX::XMFLOAT3 intersectedNormal = {};

		for (int i = 0; i < Piece::PIECE_MAX; i++)
		{
			Piece* piece = PieceManager::Instance().GetPiece(i);
			DirectX::XMFLOAT4X4 pieceTransform;
			DirectX::XMStoreFloat4x4(&pieceTransform, piece->GetTransform()->CalcWorldMatrix(1.0f));
			//	レイが当たっていたら
			if (piece->GetModel()->Raycast(l0, l, pieceTransform, intersectionPoint, intersectedNormal, intersectedMesh, intersectedMaterial))
			{
				OutputDebugStringA("Intersected : ");
				OutputDebugStringA(intersectedMesh.c_str());
				OutputDebugStringA(" : ");
				OutputDebugStringA(intersectedMaterial.c_str());
				OutputDebugStringA("\n");
				piece->SetPieceChoise(true);
			}
			else
			{
				OutputDebugStringA("Unintersected...\n");
			}
		}
	}

}

//	選んだ駒を動かす
void Player::MovePiece()
{

}

