#include "ShogiBoard.h"

#include "../Graphics/Graphics.h"
#include "Stage.h"
#include "Judge.h"

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

//	空いているマス描画用の初期化関数
void ShogiBoard::EmptySquareInit(Piece::DirectionInfo direction[])
{
	//	駒が動ける方向取得、動けるマスの数カウント
	Piece::DirectionInfo copyDirection[8] = {};
	directionCount_ = 0;
	for (int i = 0; i < Piece::PIECE_DIRECTION_MAX; i++)	//	駒の方向取得
	{
		copyDirection[i] = direction[i];
		if (!(copyDirection->directionX_ == 0 && copyDirection->directionY_ == 0))	//	駒が動ける方向の数取得
		{
			directionCount_ += 1;	//	動けるマスの数カウント
		}
	}

	//	選ばれている駒取得
	PieceManager& pieceManager = PieceManager::Instance();
	Piece* choicePiece = pieceManager.GetChoicePiece();
	int choiceIndex = pieceManager.GetChoicePieceIndex();
	for (int i = 0; i < directionCount_; i++)	//	動けるマスに描画するモデルセット
	{
		//	駒の座標 = (将棋盤(9x9マス)上での座標 + pieceOffset) * range_
		
	}
}

//	自分が動けるマスに描画
void ShogiBoard::EmptySquareRender()
{	
	Graphics::Instance().GetShader()->SetRasterizerState(Shader::RASTERIZER_STATE::SOLID);
	Graphics::Instance().GetShader()->SetDepthStencilState(Shader::DEPTH_STENCIL_STATE::ZT_ON_ZW_ON);
	Graphics::Instance().GetShader()->SetBlendState(Shader::BLEND_STATE::ALPHA);
}

//	描画処理
void ShogiBoard::Render()
{
	GameObject::Render(1.0f);
	if (Judge::Instance().GetDuringChoice())EmptySquareRender();
	EmptySquareRender();
}

//	デバッグ描画
void ShogiBoard::DrawDebug()
{
		ImGui::TreePop();
}
