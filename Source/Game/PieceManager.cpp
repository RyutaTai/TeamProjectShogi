#include "PieceManager.h"

#include "../Input/GamePad.h"
#include "../Input/Input.h"
#include "../Game/ShogiBoard.h"

//	初期化
void PieceManager::Initialize()
{
	for (Piece* piece : pieces_)
	{
		piece->Initialize(pieceCount_);
		ShogiBoard::Instance().Initialize(pieceCount_);	//	将棋盤(board_)に駒を登録
		pieceCount_ += 1;		//	駒の数をカウント
	}
	blowAway_ = false;
	pushCount_ = 0;
}

//	更新処理
void PieceManager::Update(float elapsedTime, float gameIntervalTimer)
{
	//	駒の更新処理

	
	//	自分の駒の吹っ飛ばし処理
	GamePad& gamePad = Input::Instance().GetGamePad();
	if ((gamePad.GetButtonDown() & GamePad::BTN_SPACE) && gameIntervalTimer == 0
		&& (pushCount_<PUSH_MAX))	//	スペースキー
	{
		blowAway_ = true;
		int index = 0;
		for (Piece* piece : pieces_)
		{
			piece->SetState(Piece::PIECE_STATE::IDLE);	//	上昇ステートへ切り替え
			index += 1;
		}
		pushCount_++;
	}

	if (blowAway_)
	{
		int index = 0;
		for (Piece* piece : pieces_)
		{
			piece->Update(elapsedTime, index);
			index += 1;
		}
	}

	//	破棄処理
	for (Piece* piece : removes_)
	{
		std::vector<Piece*>::iterator it =
			std::find(pieces_.begin(), pieces_.end(), piece);
		if (it != pieces_.end())
		{
			pieces_.erase(it);
		}
		delete piece;
	}
	//	破棄リストをクリア
	removes_.clear();
}

//	駒を登録
void PieceManager::Register(Piece* piece)
{
	pieces_.emplace_back(piece);
}

//	駒を全て削除
void PieceManager::Clear()
{
	for (Piece* piece : pieces_)
	{
		delete piece;
	}
	pieces_.clear();
}

//	駒を削除
void PieceManager::Remove(Piece* piece)
{
	removes_.insert(piece);	//	破棄リストに追加
}

//	駒移動
void PieceManager::Move(int index, int x, int y)
{
	pieces_.at(index)->Move(index, x, y);				//	PieceクラスのMove呼ぶ
	pieces_.at(index)->pieceInfo_->isChoice_ = false;	//	選択フラグfalse
	RemoveChoicePiece();								//	選択されている駒をnullptrにする
	Judge::Instance().SetDuringChoice(false);			//	選択中フラグfalse
}

// 選択されている駒セット
void PieceManager::SetChoicePiece(int index)
{
	choicePiece_= pieces_.at(index);	//	選択されている駒をセット
	choiceIndex_ = index;				//	選択されている駒のインデックスをセット
	pieces_.at(index)->pieceInfo_->isChoice_ = !pieces_.at(index)->pieceInfo_->isChoice_;	//	選択フラグ反転
}

//	選択されている駒リセット
void PieceManager::RemoveChoicePiece()
{
	choicePiece_ = nullptr;				//	選択されている駒リセット
}

//	描画処理
void PieceManager::Render()
{
	for (Piece* piece : pieces_)
	{
		piece->Render();
	}
}

//	デバッグ描画
void PieceManager::DrawDebug()
{
	for (Piece* piece : pieces_)
	{
		piece->DrawDebug();
	}
}


