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

	//	駒の進行方向
	enum class DIRECTION		
	{

	};

	//	駒の情報
	struct PieceInfo			
	{
	public:
		int posX_;						//	駒のx座標 座標を9x9マスの中で表記する
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
		{1,1,PIECE_TYPE::KYOUSHA,	true},
		{2,1,PIECE_TYPE::KEIMA,		true},
		{3,1,PIECE_TYPE::GINSHO,	true},
		{4,1,PIECE_TYPE::KINSHO,	true},
		{5,1,PIECE_TYPE::GYOKUSHO,	true},
		{6,1,PIECE_TYPE::KINSHO,	true},
		{7,1,PIECE_TYPE::GINSHO,	true},
		{8,1,PIECE_TYPE::KEIMA,		true},
		{9,1,PIECE_TYPE::KYOUSHA,	true},

		{2,2,PIECE_TYPE::HISHA,		true},	//	10
		{8,2,PIECE_TYPE::KAKUGYO,	true},

		{1,3,PIECE_TYPE::HUHYO,	true},
		{2,3,PIECE_TYPE::HUHYO,	true},
		{3,3,PIECE_TYPE::HUHYO,	true},
		{4,3,PIECE_TYPE::HUHYO,	true},
		{5,3,PIECE_TYPE::HUHYO,	true},
		{6,3,PIECE_TYPE::HUHYO,	true},
		{7,3,PIECE_TYPE::HUHYO,	true},
		{8,3,PIECE_TYPE::HUHYO,	true},
		{9,3,PIECE_TYPE::HUHYO,	true},	//	20

		//	味方
		{1,7,PIECE_TYPE::KYOUSHA,	false},
		{2,7,PIECE_TYPE::KEIMA,		false},
		{3,7,PIECE_TYPE::GINSHO,	false},
		{4,7,PIECE_TYPE::KINSHO,	false},
		{5,7,PIECE_TYPE::OUSHO,	false},
		{6,7,PIECE_TYPE::KINSHO,	false},
		{7,7,PIECE_TYPE::GINSHO,	false},
		{8,7,PIECE_TYPE::KEIMA,		false},
		{9,7,PIECE_TYPE::KYOUSHA,	false},

		{2,8,PIECE_TYPE::KAKUGYO,	false},	//	30
		{8,8,PIECE_TYPE::HISHA,		false},

		{1,9,PIECE_TYPE::HUHYO,	false},
		{2,9,PIECE_TYPE::HUHYO,	false},
		{3,9,PIECE_TYPE::HUHYO,	false},
		{4,9,PIECE_TYPE::HUHYO,	false},
		{5,9,PIECE_TYPE::HUHYO,	false},
		{6,9,PIECE_TYPE::HUHYO,	false},
		{7,9,PIECE_TYPE::HUHYO,	false},
		{8,9,PIECE_TYPE::HUHYO,	false},
		{9,9,PIECE_TYPE::HUHYO,	false},	//	40
	};

public:
	Piece(const char* filename, bool triangulate = false);
	Piece();
	~Piece() {}

	void Initialize(int index);							//	初期化　位置設定とか
	void Update(float elapsedTime);						//	更新処理
	void Render();										//	描画処理

	void Destroy();										//	破棄処理
	const char& GetFilePath(int index);					//	要素番号のモデルのファイルパスを取得	

	void DrawDebug();									//	デバッグ描画
	void SetDebugStr();									//	駒の種類を表示できるようtypeStr_にpieceType_をセット

	PieceInfo GetPieceInfo(int index) { return this->pieceInfo_[index]; }	//	将棋の駒データ取得	

private:
	static const int boradX_ = 9;								//	マス目x軸
	static const int boardY_ = 9;								//	マス目y軸
	static const int board_[boradX_][boardY_];					//	将棋盤のデータ 9x9
	DirectX::XMFLOAT3 pieceOffset_ = { -5.0f, 0.0f, -5.0f };	//	駒を最初に描画するときのオフセット値(補正値)
	float range_ = 2.5f;										//	駒と駒の間隔をどれくらい空けるか

private:	//デバッグ用
	static int num;				//	将棋の駒の要素番号
	int myNum_ = 0;				//	将棋の駒の要素番号
	std::string typeStr_ = "";	//	駒の種類

};

