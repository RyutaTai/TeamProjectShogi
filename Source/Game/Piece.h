#pragma once

#include "GameObject.h"

//	将棋の駒クラス
class Piece :public GameObject
{
private:	
	//	構造体とか
	enum class PIECE_TYPE		//	駒の種類を宣言する
	{
		HUHYO,					//	歩兵
		TOKIN,					//	と金（成った歩兵）
		KYOUSHA,				//	香車
		NARIKYO,				//	成香（成った香車）
		KEIMA,					//	桂馬
		NARIKEI,				//	成桂（成った桂馬）
		GINSHO,					//	銀将
		NARIGIN,				//	成銀（成った銀将）
		HISHA,					//	飛車
		RYUO,					//	竜王（成った飛車）
		KAKUGYO,				//	角行
		RYUMA,					//	竜馬（成った角行）
		KINSHO,					//	金将
		OUSHO,					//	王将
		GYOKUSHO,				//	玉将	相手の王
	};

	//	駒の進行方向名
	enum class DIRECTION_NAME		
	{
		BACK_LEFT,			//	左下
		BAXK,				//	下
		BACK_RIGHT,			//	右下
		LEFT,				//	左
		RIGHT,				//	右
		UP_LEFT,			//	左上
		UP,					//	上
		UP_RIGHT,			//	右上
		MY_KEIMA_RIGHT,		//	自分の桂馬右方向
		MY_KEIMA_LEFT,		//	自分の桂馬右方向
		ENEMY_KEIMA_RIGHT,	//	敵の桂馬右方向
		ENEMY_KEIMA_LEFT,	//	敵の桂馬右方向
	};

	//	駒の方向の情報
	struct DirectionInfo
	{
		DIRECTION_NAME name_;				//	方向の名前
		float directionX_;					//	動ける方向のx
		float directionY_;					//	動ける方向のy
	};

	//	駒の情報
	struct PieceInfo			
	{
		int posX_;						//	駒のx座標 座標を9x9マスの中で表記する
		int posY_;						//	駒のy座標
		PIECE_TYPE pieceType_;			//	駒の種類
		bool isEnemy_;					//	敵の駒か、自分の駒か 敵ならtrue
		bool isDead_;					//	場にあるかないか
		DirectionInfo direction_;		//	駒の方向情報を持つ(方向の名前、動けるマスを持ってる)
	};

public:
	//	構造体とか
	static const int PIECE_MAX = 40;		//	駒の最大数
	static const int DIRECTION_MAX = 12;	//	駒の方向の最大数
	static const int PIECE_TYPE_MAX = 15;	//	駒の種類の最大数(玉将も含んでる)
	//	駒が動ける方向
	DirectionInfo	directionInfo_[DIRECTION_MAX] =
	{
		{DIRECTION_NAME::BACK_LEFT,		-1.0f,	-1.0f},		//	左下
		{DIRECTION_NAME::BAXK,			 0.0f,	-1.0f},		//	下
		{DIRECTION_NAME::BACK_RIGHT,	+1.0f,	-1.0f},		//	右下
		{DIRECTION_NAME::LEFT,			-1.0f,	 0.0f},		//	左
		{DIRECTION_NAME::RIGHT,			+1.0f,	 0.0f},		//	右
		{DIRECTION_NAME::BACK_LEFT,		-1.0f,	+1.0f},		//	左上
		{DIRECTION_NAME::BACK_LEFT,		 0.0f,	+1.0f},		//	上
		{DIRECTION_NAME::BACK_LEFT,		+1.0f,	+1.0f},		//	右上
		{DIRECTION_NAME::BACK_LEFT,		+2.0f,	+1.0f},		//	自分の桂馬右方向
		{DIRECTION_NAME::BACK_LEFT,		+2.0f,	+1.0f},		//	自分の桂馬右方向
		{DIRECTION_NAME::BACK_LEFT,		+2.0f,	-1.0f},		//	敵の桂馬右方向
		{DIRECTION_NAME::BACK_LEFT,		-2.0f,	-1.0f},		//	敵の桂馬右方向
	}
	;
	//	駒の初期座標
	PieceInfo pieceInfo_[PIECE_MAX] =
	{
		{1,3,PIECE_TYPE::HUHYO,		true,	true},		//	敵歩兵
		{2,3,PIECE_TYPE::HUHYO,		true,	true},
		{3,3,PIECE_TYPE::HUHYO,		true,	true},
		{4,3,PIECE_TYPE::HUHYO,		true,	true},
		{5,3,PIECE_TYPE::HUHYO,		true,	true},
		{6,3,PIECE_TYPE::HUHYO,		true,	true},
		{7,3,PIECE_TYPE::HUHYO,		true,	true},
		{8,3,PIECE_TYPE::HUHYO,		true,	true},
		{9,3,PIECE_TYPE::HUHYO,		true,	true},	
		{1,7,PIECE_TYPE::HUHYO,		false,	true},		//	味方歩兵
		{2,7,PIECE_TYPE::HUHYO,		false,	true},
		{3,7,PIECE_TYPE::HUHYO,		false,	true},
		{4,7,PIECE_TYPE::HUHYO,		false,	true},
		{5,7,PIECE_TYPE::HUHYO,		false,	true},
		{6,7,PIECE_TYPE::HUHYO,		false,	true},
		{7,7,PIECE_TYPE::HUHYO,		false,	true},
		{8,7,PIECE_TYPE::HUHYO,		false,	true},
		{9,7,PIECE_TYPE::HUHYO,		false,	true},
		{8,2,PIECE_TYPE::KAKUGYO,	true,	true},		//	敵角行
		{8,8,PIECE_TYPE::KAKUGYO,	false,	true},		//	味方角行
		{2,2,PIECE_TYPE::HISHA,		true,	true},		//	敵飛車
		{2,8,PIECE_TYPE::HISHA,		false,	true},		//	味方飛車
		{1,1,PIECE_TYPE::KYOUSHA,	true,	true},		//	敵香車
		{9,1,PIECE_TYPE::KYOUSHA,	true,	true},
		{1,9,PIECE_TYPE::KYOUSHA,	false,	true},		//	味方香車
		{9,9,PIECE_TYPE::KYOUSHA,	false,	true},
		{2,1,PIECE_TYPE::KEIMA,		true,	true},		//	敵桂馬
		{8,1,PIECE_TYPE::KEIMA,		true,	true},
		{2,9,PIECE_TYPE::KEIMA,		false,	true},		//	味方桂馬
		{8,9,PIECE_TYPE::KEIMA,		false,	true},
		{3,1,PIECE_TYPE::GINSHO,	true,	true},		//	敵銀将
		{7,1,PIECE_TYPE::GINSHO,	true,	true},
		{3,9,PIECE_TYPE::GINSHO,	false,	true},		//	味方銀将
		{7,9,PIECE_TYPE::GINSHO,	false,	true},
		{4,1,PIECE_TYPE::KINSHO,	true,	true},		//	敵金将
		{6,1,PIECE_TYPE::KINSHO,	true,	true},
		{4,9,PIECE_TYPE::KINSHO,	false,	true},		//	味方金将
		{6,9,PIECE_TYPE::KINSHO,	false,	true},
		{5,1,PIECE_TYPE::GYOKUSHO,	true,	true},		//	玉将
		{5,9,PIECE_TYPE::OUSHO,		false,	true},		//	王将

	};

public:
	Piece(const char* filename, bool triangulate = false);		//	コンストラクタ
	~Piece();													//	デストラクタ

	void Initialize(int index);									//	初期化　位置設定とか
	void Update(float elapsedTime);								//	更新処理
	void Render();												//	描画処理

	void Serch(int index);										//	空いているマスがあるかどうか調べる
	void Destroy();												//	破棄処理

	void DrawDebug();											//	デバッグ描画
	void SetDebugStr();											//	駒の種類を表示できるようtypeStr_にpieceType_をセット

	PieceInfo GetPieceInfo(int index) { return this->pieceInfo_[index]; }	//	将棋の駒データ取得	

private:
	static const int boradX_ = 9;								//	マス目x軸
	static const int boardY_ = 9;								//	マス目y軸
	static const int board_[boradX_][boardY_];					//	将棋盤のデータ 9x9
	DirectX::XMFLOAT3 pieceOffset_ = { -5.0f, 0.0f, -5.0f };	//	駒を最初に描画するときのオフセット値(補正値)
	float range_ = 2.4f;										//	駒と駒の間隔をどれくらい空けるか

private:	//デバッグ用
	static int num;				//	将棋の駒の要素番号
	int myNum_ = 0;				//	将棋の駒の要素番号
	std::string typeStr_ = "";	//	駒の種類

};

