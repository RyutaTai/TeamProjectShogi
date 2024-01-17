#pragma once

#include "GameObject.h"

//	将棋の駒クラス
class Piece :public GameObject
{
private:	
	//	構造体とか
	enum class PIECE_TYPE		//	駒の種類を宣言する
	{
		HUHYOU,					//	歩兵
		TOKIN,					//	と金（成った歩兵）
		KYOUSHA,				//	香車
		NARIKYOU,				//	成香（成った香車）
		KEIMA,					//	桂馬
		NARIKEI,				//	成桂（成った桂馬）
		GINSHOU,				//	銀将
		NARIGIN,				//	成銀（成った銀将）
		HISHA,					//	飛車
		RYUOU,					//	竜王（成った飛車）
		KAKUGYOU,				//	角行
		RYUMA,					//	竜馬（成った角行）
		KINSHOU,				//	金将
		OUSHOU,					//	王将 玉将は定義してない
	};

	//	駒の進行方向
	enum class DIRECTION		
	{

	};

	//	駒の情報
	struct PieceInfo			
	{
	public:
		int posX_;						//	駒のx座標
		int posY_;						//	駒のy座標
		PIECE_TYPE pieceType_;			//	駒の種類
		bool isEnemy_;					//	敵の駒か、味方の駒か 敵ならtrue
	};

public:
	static const int PIECE_MAX = 40;	//	駒の最大数
	//	駒の初期座標
	PieceInfo pieceInfo_[PIECE_MAX] =
	{
		//	敵
		{1,1,PIECE_TYPE::KYOUSHA,	false},
		{2,1,PIECE_TYPE::KEIMA,		false},
		{3,1,PIECE_TYPE::GINSHOU,	false},
		{4,1,PIECE_TYPE::KINSHOU,	false},
		{5,1,PIECE_TYPE::OUSHOU,	false},
		{6,1,PIECE_TYPE::KINSHOU,	false},
		{7,1,PIECE_TYPE::GINSHOU,	false},
		{8,1,PIECE_TYPE::KEIMA,		false},
		{9,1,PIECE_TYPE::KYOUSHA,	false},

		{2,2,PIECE_TYPE::HISHA,		false},	//	10
		{8,2,PIECE_TYPE::KAKUGYOU,	false},

		{1,1,PIECE_TYPE::HUHYOU,	false},
		{2,1,PIECE_TYPE::HUHYOU,	false},
		{3,1,PIECE_TYPE::HUHYOU,	false},
		{4,1,PIECE_TYPE::HUHYOU,	false},
		{5,1,PIECE_TYPE::HUHYOU,	false},
		{6,1,PIECE_TYPE::HUHYOU,	false},
		{7,1,PIECE_TYPE::HUHYOU,	false},
		{8,1,PIECE_TYPE::HUHYOU,	false},
		{9,1,PIECE_TYPE::HUHYOU,	false},	//	20

		//	味方
		{1,7,PIECE_TYPE::KYOUSHA,	false},
		{2,7,PIECE_TYPE::KEIMA,		false},
		{3,7,PIECE_TYPE::GINSHOU,	false},
		{4,7,PIECE_TYPE::KINSHOU,	false},
		{5,7,PIECE_TYPE::OUSHOU,	false},
		{6,7,PIECE_TYPE::KINSHOU,	false},
		{7,7,PIECE_TYPE::GINSHOU,	false},
		{8,7,PIECE_TYPE::KEIMA,		false},
		{9,7,PIECE_TYPE::KYOUSHA,	false},

		{2,8,PIECE_TYPE::KAKUGYOU,	false},	//	30
		{8,8,PIECE_TYPE::HISHA,		false},

		{1,9,PIECE_TYPE::HUHYOU,	false},
		{2,9,PIECE_TYPE::HUHYOU,	false},
		{3,9,PIECE_TYPE::HUHYOU,	false},
		{4,9,PIECE_TYPE::HUHYOU,	false},
		{5,9,PIECE_TYPE::HUHYOU,	false},
		{6,9,PIECE_TYPE::HUHYOU,	false},
		{7,9,PIECE_TYPE::HUHYOU,	false},
		{8,9,PIECE_TYPE::HUHYOU,	false},
		{9,9,PIECE_TYPE::HUHYOU,	false},	//	40
	};

public:
	Piece(const char* filename, bool triangulate = false);
	~Piece() {}

	void Initialize(int index);							//	初期化　位置設定とか
	void Update(float elapsedTime);						//	更新処理
	void Render();										//	描画処理
	void DrawDebug();									//	デバッグ描画

	void Destroy();										//	破棄処理
	PieceInfo GetPieceInfo(int index) { return this->pieceInfo_[index]; }	//	将棋の駒データ取得	

private:
	static const int boradX_ = 9;						//	マス目x軸
	static const int boardY_ = 9;						//	マス目y軸
	static const int board_[boradX_][boardY_];			//	将棋盤のデータ 9x9
	DirectX::XMFLOAT3 pieceOffset_ = { 10,10,10 };		//	駒を最初に描画するときのオフセット値

private:
	static int num;	//	ImGuiデバッグ用
	int myNum_;		//	ImGuiデバッグ用
};

