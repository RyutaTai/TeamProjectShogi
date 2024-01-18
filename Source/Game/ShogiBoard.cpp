#include "ShogiBoard.h"

#include "../Graphics/Graphics.h"

//	コンストラクタ
ShogiBoard::ShogiBoard(const char* filename, bool triangulate)
	: GameObject(filename, triangulate)
{
	GetTransform()->SetPosition(DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f));
	GetTransform()->SetScale(DirectX::XMFLOAT3(1.0f, 1.0f, 1.0f));
	GetTransform()->SetRotation(DirectX::XMFLOAT4(0.0f, DirectX::XMConvertToRadians(0), 0.0f, 0.0f));

}

//デストラクタ
ShogiBoard::~ShogiBoard()
{

}

//	描画処理
void ShogiBoard::Render()
{
	GameObject::Render(1.0f);
}

//	デバッグ描画
void ShogiBoard::DrawDebug()
{
	GetTransform()->DrawDebug();
}
