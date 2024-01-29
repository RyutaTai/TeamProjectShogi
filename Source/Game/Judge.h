#pragma once

#include "../Game/Player.h"
#include "../Game/Enemy.h"
#include "../Game/Piece.h"
#include "../Game/PieceManager.h"
#include "../Game/ShogiBoard.h"
#include "../Graphics/Camera.h"

class Judge
{
public:
	Judge(){}
	~Judge(){}

	static Judge& Instance()
	{
		static Judge instance_;
		return instance_;
	}

	void FoulMoveCheck();		//	TODO:禁じ手チェック(２歩とか) foul move : 禁じ手
	void AreaCheck();			//	TODO:エリアチェック(置ける場所が9x9の中にあるか、敵陣3マス以内に入ったか)
	void ChangeTurn();			//	TODO:ターン切り替え (Player,Enemy,マイク入力の３つ？)
	void PieceOverlapCheck();	//	TODO:駒が重なっていないかチェック

	void SetDuringChoice(bool choice) { duringChoice_ = choice; }	//	選択中フラグセット
	bool GetDuringChoice()				{ return duringChoice_; }	//	選択中かどうか

private:
	//ゲーム用変数
	bool	isMyTurn_ = true;		//	自分のターンかどうか
	float	allottedTime = 30.0f;	//	各プレイヤーの一手ごとの持ち時間
	Player	player_;				//	プレイヤー
	Enemy	enemy_;					//	相手
	bool	duringChoice_ = false;	//	駒選択中ならtrue

};

