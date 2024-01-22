#pragma once

#include <set>

#include "../Game/Piece.h"

//	将棋の駒管理クラス
class PieceManager
{
private:
	PieceManager() {}
	~PieceManager() {}
public:
	//	唯一のインスタンス取得
	static PieceManager& Instance()
	{
		static PieceManager instance_;
		return instance_;
	}

	void Initialize();				//	初期化
	void Update(float elapsedTime);	//	更新処理
	void Render();					//	描画処理
	void DrawDebug();				//	デバッグ描画

	void Register(Piece* piece);	//	駒を登録
	void Clear();					//	駒を全て削除
	void Remove(Piece* piece);		//	駒を削除

	void	SetChoicePiece(int index);	//	選択されている駒セット	
	Piece*	GetChoicePiece() { return choicePiece_; }		//	選択されている駒取得
	int		GetChoicePieceIndex() { return choiceIndex_; }	//	選択されている駒のインデックス取得
	int		GetPieceCount() const { return static_cast<int>(pieces_.size()); }	//	現在の駒の数取得
	Piece*	GetPiece(int index) { return pieces_.at(index); }					//	駒を取得

private:
	std::vector<Piece*> pieces_;	//	駒の配列
	std::set<Piece*> removes_;		//	破棄リスト
	Piece* choicePiece_ = nullptr;	//	現在選択されている駒
	int choiceIndex_;				//	現在選択されている駒のインデックス 組み方のミスで必要になった。時間あれば修正する。

	int pieceCount_ = 0;			//	現在の駒の数

};

