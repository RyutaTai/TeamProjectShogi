#pragma once

#include "GameObject.h"
#include "../Game/Piece.h"
#include "../Game/PieceManager.h"

class ShogiBoard : public GameObject
{
public:
	ShogiBoard(const char* fileName, bool triangulate = false, bool usedAsCollider = false);
	ShogiBoard() {}
	~ShogiBoard();

	//	唯一のインスタンス取得
	static ShogiBoard& Instance()
	{
		static ShogiBoard instance_;
		return instance_;
	}

	void Initialize(int index);						//	初期化
	void Render();									//	描画処理
	void DrawDebug();								//	デバッグ描画

	void RegisterBoard(int index);					//	board_に駒を登録する
	void RemoveFromBoard(int index);				//	board_から駒を削除
	DirectX::XMFLOAT2 Serch(int index);				//	index番目の駒が動ける方向に空いているマスがあるかどうか調べる
	bool IsEmpty(int directionX, int directionY);	//	指定したマスが空いているか調べる

private:
	enum class SQUARE_STATE	//	マスの状態
	{
		EMPTY = 0,	//	空いている
		EXIST,		//	駒が存在している
	};

	//	空いているマスを検索するときに使う
	static const int boradX_ = 9;						//	マス目x軸
	static const int boardY_ = 9;						//	マス目y軸
	int board_[boradX_][boardY_] = {};					//	将棋盤のデータ 9x9

};