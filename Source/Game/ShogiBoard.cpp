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

//	初期化	PieceManagerのInitialize()の中で呼ぶ
void ShogiBoard::Initialize(int index)
{
	RegisterBoard(index);
}

//	DirectionInfoの方向に空いているマスがあるか調べる
void ShogiBoard::Serch(int index)
{
	Piece* piece = PieceManager::Instance().GetPiece(index);
	

}

//	 Boardの配列に駒を登録
void ShogiBoard::RegisterBoard(int index)
{
	Piece * piece = PieceManager::Instance().GetPiece(index);
	int posX, posY;
	posX = piece->GetPieceInfo(index).posX_;
	posY = piece->GetPieceInfo(index).posY_;
	board_[posX][posY] = static_cast<int>(SQUARE_STATE::EXIST);	//	存在していることを登録

}

//	指定したマスが空いているか調べる
bool ShogiBoard::IsEmpty(float x, float y)
{
	for (int x = 0; x < boradX_; x++)
	{
		for (int y = 0; y < boardY_; y++)
		{
			
		}
	}
	return false;
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
