#pragma once

#include "GameObject.h"

//	将棋の駒クラス
class Piece :public GameObject
{
public:	
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
		BACK_LEFT,			//	左後ろ
		BACK,				//	後ろ
		BACK_RIGHT,			//	右後ろ
		LEFT,				//	左
		RIGHT,				//	右
		FRONT_LEFT,			//	左前
		FRONT,				//	前
		FRONT_RIGHT,		//	右前
		KEIMA_RIGHT,		//	自分の桂馬右方向
		KEIMA_LEFT,			//	自分の桂馬右方向
		NONE,				//	方向なし
	};

	//	駒の方向の情報
	struct DirectionInfo
	{
		DIRECTION_NAME name_;				//	方向の名前
		float directionX_;					//	動ける方向のx
		float directionY_;					//	動ける方向のy
	};

	static const int PIECE_DIRECTION_MAX = 8;	//	１つの駒が持てる駒の方向の最大数
	static const int DIRECTION_MAX = 12;		//	駒の方向の最大数
	//	駒の情報
	struct PieceInfo			
	{
		int posX_;						//	駒のx座標 座標を9x9マスの中で表記する
		int posY_;						//	駒のy座標
		PIECE_TYPE pieceType_;			//	駒の種類
		bool isEnemy_;					//	敵の駒か、自分の駒か 敵ならtrue
		bool isDead_;					//	場にあるかないか
		bool isChoise_;					//	選択されているか
		DirectionInfo direction_[PIECE_DIRECTION_MAX];		//	駒の方向情報を持つ(方向の名前、動けるマスを持ってる) まだ関連付けしてない
	};

	static const int PIECE_MAX = 40;		//	駒の最大数
	static const int PIECE_TYPE_MAX = 16;	//	駒の種類の最大数(玉将も含んでる)
	//	駒が動ける方向
	DirectionInfo	directionInfo_[DIRECTION_MAX] =
	{
		{DIRECTION_NAME::BACK_LEFT,		-1.0f,	-1.0f},		//	左後ろ
		{DIRECTION_NAME::BACK,			 0.0f,	-1.0f},		//	後ろ
		{DIRECTION_NAME::BACK_RIGHT,	+1.0f,	-1.0f},		//	右後ろ
		{DIRECTION_NAME::LEFT,			-1.0f,	 0.0f},		//	左
		{DIRECTION_NAME::RIGHT,			+1.0f,	 0.0f},		//	右
		{DIRECTION_NAME::FRONT_LEFT,	-1.0f,	+1.0f},		//	左前
		{DIRECTION_NAME::FRONT,			 0.0f,	+1.0f},		//	前
		{DIRECTION_NAME::FRONT_RIGHT,	+1.0f,	+1.0f},		//	右前
		{DIRECTION_NAME::KEIMA_RIGHT,	+2.0f,	+1.0f},		//	桂馬右方向
		{DIRECTION_NAME::KEIMA_LEFT,	+2.0f,	+1.0f},		//	桂馬左方向
		{DIRECTION_NAME::NONE,			 0.0f,   0.0f},		//	方向なし
	};
	
	//	駒の初期座標
	PieceInfo pieceInfo_[PIECE_MAX] =
	{
		{1,3,PIECE_TYPE::HUHYO,		true,	true,	false},		//	敵歩兵
		{2,3,PIECE_TYPE::HUHYO,		true,	true,	false},
		{3,3,PIECE_TYPE::HUHYO,		true,	true,	false},
		{4,3,PIECE_TYPE::HUHYO,		true,	true,	false},
		{5,3,PIECE_TYPE::HUHYO,		true,	true,	false},
		{6,3,PIECE_TYPE::HUHYO,		true,	true,	false},
		{7,3,PIECE_TYPE::HUHYO,		true,	true,	false},
		{8,3,PIECE_TYPE::HUHYO,		true,	true,	false},
		{9,3,PIECE_TYPE::HUHYO,		true,	true,	false},	
		{1,7,PIECE_TYPE::HUHYO,		false,	true,	false},		//	味方歩兵
		{2,7,PIECE_TYPE::HUHYO,		false,	true,	false},
		{3,7,PIECE_TYPE::HUHYO,		false,	true,	false},
		{4,7,PIECE_TYPE::HUHYO,		false,	true,	false},
		{5,7,PIECE_TYPE::HUHYO,		false,	true,	false},
		{6,7,PIECE_TYPE::HUHYO,		false,	true,	false},
		{7,7,PIECE_TYPE::HUHYO,		false,	true,	false},
		{8,7,PIECE_TYPE::HUHYO,		false,	true,	false},
		{9,7,PIECE_TYPE::HUHYO,		false,	true,	false},
		{8,2,PIECE_TYPE::KAKUGYO,	true,	true,	false},		//	敵角行
		{8,8,PIECE_TYPE::KAKUGYO,	false,	true,	false},		//	味方角行
		{2,2,PIECE_TYPE::HISHA,		true,	true,	false},		//	敵飛車
		{2,8,PIECE_TYPE::HISHA,		false,	true,	false},		//	味方飛車
		{1,1,PIECE_TYPE::KYOUSHA,	true,	true,	false},		//	敵香車
		{9,1,PIECE_TYPE::KYOUSHA,	true,	true,	false},
		{1,9,PIECE_TYPE::KYOUSHA,	false,	true,	false},		//	味方香車
		{9,9,PIECE_TYPE::KYOUSHA,	false,	true,	false},
		{2,1,PIECE_TYPE::KEIMA,		true,	true,	false},		//	敵桂馬
		{8,1,PIECE_TYPE::KEIMA,		true,	true,	false},
		{2,9,PIECE_TYPE::KEIMA,		false,	true,	false},		//	味方桂馬
		{8,9,PIECE_TYPE::KEIMA,		false,	true,	false},
		{3,1,PIECE_TYPE::GINSHO,	true,	true,	false},		//	敵銀将
		{7,1,PIECE_TYPE::GINSHO,	true,	true,	false},
		{3,9,PIECE_TYPE::GINSHO,	false,	true,	false},		//	味方銀将
		{7,9,PIECE_TYPE::GINSHO,	false,	true,	false},
		{4,1,PIECE_TYPE::KINSHO,	true,	true,	false},		//	敵金将
		{6,1,PIECE_TYPE::KINSHO,	true,	true,	false},
		{4,9,PIECE_TYPE::KINSHO,	false,	true,	false},		//	味方金将
		{6,9,PIECE_TYPE::KINSHO,	false,	true,	false},
		{5,1,PIECE_TYPE::GYOKUSHO,	true,	true,	false},		//	玉将
		{5,9,PIECE_TYPE::OUSHO,		false,	true,	false},		//	王将

	};

public:
	Piece(const char* fileName, bool triangulate = false, bool usedAsCollider = false);	//	コンストラクタ
	~Piece();													//	デストラクタ

	void Initialize(int index);									//	初期化　　位置設定とか
	void Update(float elapsedTime);								//	更新処理
	void Render();												//	描画処理

	void Destroy();												//	破棄処理

	void SetPieceChoise(bool choise);										//	選択フラグセット
	void SetPieceDirection(int index);										//	駒の方向direction_を駒の情報pieceInfo_に登録
	PieceInfo GetPieceInfo(int index) { return this->pieceInfo_[index]; }	//	将棋の駒データ取得	

	//	デバッグ用
	void DrawDebug();											//	デバッグ描画
	void SetDebugStr();											//	駒の種類を表示できるようtypeStr_にpieceType_をセット

private:
	DirectX::XMFLOAT3 pieceOffset_ = { -5.0f, 0.0f, -5.0f };	//	駒を最初に描画するときのオフセット値(補正値)
	float range_ = 2.4f;										//	駒と駒の間隔をどれくらい空けるか

private:	//デバッグ用
	static int num;					//	将棋の駒の要素番号
	int myNum_ = 0;					//	将棋の駒の要素番号
	std::string typeStr_ = "";		//	駒の種類
	std::string choiseStr_ = "";	//	選択されているか

};

