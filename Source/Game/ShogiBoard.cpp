#include "ShogiBoard.h"

#include "../Graphics/Graphics.h"

//	コンストラクタ
ShogiBoard::ShogiBoard(const char* fileName, bool triangulate, bool usedAsCollider)
	: GameObject(fileName, triangulate, usedAsCollider)
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
DirectX::XMFLOAT2 ShogiBoard::Serch(int index)
{
	Piece* piece = PieceManager::Instance().GetPiece(index);				//	駒取得
	Piece::PIECE_TYPE pieceType = piece->GetPieceInfo(index).pieceType_;	//	駒の種類
	DirectX::XMFLOAT2 movablePos[Piece::PIECE_DIRECTION_MAX + 1] = {};		//	動けるマスをストック 動けない場合{0,0}を入れる
	for (int i = 0; i < Piece::PIECE_DIRECTION_MAX; i++)
	{
		//	動くマスを指定してIsEmpty()を呼ぶ
		//	動けるマスを全部チェックしたい。
		float directionX = piece->GetPieceInfo(index).direction_[i].directionX_;	//	駒が動けるx方向 配列になるかも
		float directionY = piece->GetPieceInfo(index).direction_[i].directionY_;	//	駒が動けるy方向
		//	動ける方向がもし空いていたら
		if (IsEmpty(directionX, directionY))
		{
			return movablePos[i] = { directionX,directionY };
		}
	}
	
	return movablePos[8];
}

//	指定したマスが空いているか調べる
bool ShogiBoard::IsEmpty(int directionX, int directionY)
{
	if (board_[directionX][directionY] == static_cast<int>(SQUARE_STATE::EMPTY))	//	EMPTYならtrueを返す　条件式どうしよう
	{
		return true;
	}
	return false;
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

//	 Boardの配列から駒を削除
void ShogiBoard::RemoveFromBoard(int index)
{
	Piece* piece = PieceManager::Instance().GetPiece(index);
	int posX, posY;
	posX = piece->GetPieceInfo(index).posX_;
	posY = piece->GetPieceInfo(index).posY_;
	board_[posX][posY] = static_cast<int>(SQUARE_STATE::EMPTY);	//	マスを空いている状態にする

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
