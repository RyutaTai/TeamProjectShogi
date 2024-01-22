#include "Piece.h"

#include "PieceManager.h"
#include "Stage.h"

int Piece::num = 0;	//	デバッグ用

//	コンストラクタ
Piece::Piece(const char* fileName, bool triangulate, bool usedAsCollider)
	:GameObject(fileName, triangulate, usedAsCollider)
{
	myNum_ = num++;	//	デバッグ用
}

Piece::~Piece()
{
}

//	初期化
void Piece::Initialize(int index)
{
	//	駒の座標 = (将棋盤(9x9マス)上での座標 + pieceOffset) * range_
	this->GetTransform()->SetPositionX((static_cast<float>(pieceInfo_[index].posX_) + pieceOffset_.x) * range_);
	this->GetTransform()->SetPositionY(Stage::Instance().GetTransform()->GetPosition().y);	//将棋盤と高さ合わせるため補正とかしない
	this->GetTransform()->SetPositionZ((static_cast<float>(pieceInfo_[index].posY_) + pieceOffset_.z) * range_);

	//	敵のときだけモデルの向きを反転させる
	if (pieceInfo_[index].isEnemy_)GetTransform()->SetRotationY(DirectX::XMConvertToRadians(180.0f));
}

//	駒の方向登録(pieceInfo_に登録)
void Piece::SetPieceDirection(int index)
{
	//	駒の種類ごとに処理を分ける(駒によって動けるマスが異なるため)
	switch (this->GetPieceInfo(index).pieceType_)
	{
	case Piece::PIECE_TYPE::HUHYO:		//	歩兵
		this->GetPieceInfo(index).direction_[0] = directionInfo_[static_cast<int>(DIRECTION_NAME::FRONT)];
		break;
	case Piece::PIECE_TYPE::TOKIN:		//	と金（成った歩兵）			
		this->GetPieceInfo(index).direction_[0] = directionInfo_[static_cast<int>(DIRECTION_NAME::FRONT)];
		this->GetPieceInfo(index).direction_[1] = directionInfo_[static_cast<int>(DIRECTION_NAME::FRONT_LEFT)];
		this->GetPieceInfo(index).direction_[2] = directionInfo_[static_cast<int>(DIRECTION_NAME::LEFT)];
		this->GetPieceInfo(index).direction_[3] = directionInfo_[static_cast<int>(DIRECTION_NAME::BACK)];
		this->GetPieceInfo(index).direction_[4] = directionInfo_[static_cast<int>(DIRECTION_NAME::FRONT_RIGHT)];
		this->GetPieceInfo(index).direction_[5] = directionInfo_[static_cast<int>(DIRECTION_NAME::RIGHT)];
		break;
	case Piece::PIECE_TYPE::KYOUSHA:	//	香車				
		this->GetPieceInfo(index).direction_[0] = directionInfo_[static_cast<int>(DIRECTION_NAME::FRONT)];
		break;
	case Piece::PIECE_TYPE::NARIKYO:	//	成香（成った香車）				
		this->GetPieceInfo(index).direction_[0] = directionInfo_[static_cast<int>(DIRECTION_NAME::FRONT)];
		this->GetPieceInfo(index).direction_[1] = directionInfo_[static_cast<int>(DIRECTION_NAME::FRONT_LEFT)];
		this->GetPieceInfo(index).direction_[2] = directionInfo_[static_cast<int>(DIRECTION_NAME::LEFT)];
		this->GetPieceInfo(index).direction_[3] = directionInfo_[static_cast<int>(DIRECTION_NAME::BACK)];
		this->GetPieceInfo(index).direction_[4] = directionInfo_[static_cast<int>(DIRECTION_NAME::FRONT_RIGHT)];
		this->GetPieceInfo(index).direction_[5] = directionInfo_[static_cast<int>(DIRECTION_NAME::RIGHT)];
		break;
	case Piece::PIECE_TYPE::KEIMA:		//	桂馬				
		this->GetPieceInfo(index).direction_[0] = directionInfo_[static_cast<int>(DIRECTION_NAME::KEIMA_RIGHT)];
		this->GetPieceInfo(index).direction_[1] = directionInfo_[static_cast<int>(DIRECTION_NAME::KEIMA_LEFT)];
		break;
	case Piece::PIECE_TYPE::NARIKEI:	//	成桂（成った桂馬）
		this->GetPieceInfo(index).direction_[0] = directionInfo_[static_cast<int>(DIRECTION_NAME::FRONT)];
		this->GetPieceInfo(index).direction_[1] = directionInfo_[static_cast<int>(DIRECTION_NAME::FRONT_LEFT)];
		this->GetPieceInfo(index).direction_[2] = directionInfo_[static_cast<int>(DIRECTION_NAME::LEFT)];
		this->GetPieceInfo(index).direction_[3] = directionInfo_[static_cast<int>(DIRECTION_NAME::BACK)];
		this->GetPieceInfo(index).direction_[4] = directionInfo_[static_cast<int>(DIRECTION_NAME::FRONT_RIGHT)];
		this->GetPieceInfo(index).direction_[5] = directionInfo_[static_cast<int>(DIRECTION_NAME::RIGHT)];
		break;
	case Piece::PIECE_TYPE::GINSHO:		//	銀将
		this->GetPieceInfo(index).direction_[0] = directionInfo_[static_cast<int>(DIRECTION_NAME::FRONT)];
		this->GetPieceInfo(index).direction_[1] = directionInfo_[static_cast<int>(DIRECTION_NAME::FRONT_LEFT)];
		this->GetPieceInfo(index).direction_[2] = directionInfo_[static_cast<int>(DIRECTION_NAME::FRONT_RIGHT)];
		this->GetPieceInfo(index).direction_[3] = directionInfo_[static_cast<int>(DIRECTION_NAME::BACK_LEFT)];
		this->GetPieceInfo(index).direction_[4] = directionInfo_[static_cast<int>(DIRECTION_NAME::BACK_RIGHT)];
		this->GetPieceInfo(index).direction_[5] = directionInfo_[static_cast<int>(DIRECTION_NAME::BACK)];
		break;
	case Piece::PIECE_TYPE::NARIGIN:	//	成銀（成った銀将）
		this->GetPieceInfo(index).direction_[0] = directionInfo_[static_cast<int>(DIRECTION_NAME::FRONT)];
		this->GetPieceInfo(index).direction_[1] = directionInfo_[static_cast<int>(DIRECTION_NAME::FRONT_LEFT)];
		this->GetPieceInfo(index).direction_[2] = directionInfo_[static_cast<int>(DIRECTION_NAME::LEFT)];
		this->GetPieceInfo(index).direction_[3] = directionInfo_[static_cast<int>(DIRECTION_NAME::BACK)];
		this->GetPieceInfo(index).direction_[4] = directionInfo_[static_cast<int>(DIRECTION_NAME::FRONT_RIGHT)];
		this->GetPieceInfo(index).direction_[5] = directionInfo_[static_cast<int>(DIRECTION_NAME::RIGHT)];
		break;
	case Piece::PIECE_TYPE::HISHA:		//	飛車
		this->GetPieceInfo(index).direction_[0] = directionInfo_[static_cast<int>(DIRECTION_NAME::FRONT)];
		this->GetPieceInfo(index).direction_[1] = directionInfo_[static_cast<int>(DIRECTION_NAME::LEFT)];
		this->GetPieceInfo(index).direction_[2] = directionInfo_[static_cast<int>(DIRECTION_NAME::RIGHT)];
		this->GetPieceInfo(index).direction_[3] = directionInfo_[static_cast<int>(DIRECTION_NAME::BACK)];
		break;
	case Piece::PIECE_TYPE::RYUO:		//	竜王（成った飛車）
		this->GetPieceInfo(index).direction_[0] = directionInfo_[static_cast<int>(DIRECTION_NAME::FRONT)];
		this->GetPieceInfo(index).direction_[1] = directionInfo_[static_cast<int>(DIRECTION_NAME::FRONT_LEFT)];
		this->GetPieceInfo(index).direction_[2] = directionInfo_[static_cast<int>(DIRECTION_NAME::LEFT)];
		this->GetPieceInfo(index).direction_[3] = directionInfo_[static_cast<int>(DIRECTION_NAME::BACK_LEFT)];
		this->GetPieceInfo(index).direction_[4] = directionInfo_[static_cast<int>(DIRECTION_NAME::BACK)];
		this->GetPieceInfo(index).direction_[5] = directionInfo_[static_cast<int>(DIRECTION_NAME::BACK_RIGHT)];
		this->GetPieceInfo(index).direction_[6] = directionInfo_[static_cast<int>(DIRECTION_NAME::RIGHT)];
		this->GetPieceInfo(index).direction_[7] = directionInfo_[static_cast<int>(DIRECTION_NAME::FRONT_RIGHT)];
		break;
	case Piece::PIECE_TYPE::KAKUGYO:	//	角行
		this->GetPieceInfo(index).direction_[0] = directionInfo_[static_cast<int>(DIRECTION_NAME::FRONT_LEFT)];
		this->GetPieceInfo(index).direction_[1] = directionInfo_[static_cast<int>(DIRECTION_NAME::BACK_LEFT)];
		this->GetPieceInfo(index).direction_[2] = directionInfo_[static_cast<int>(DIRECTION_NAME::BACK_RIGHT)];
		this->GetPieceInfo(index).direction_[3] = directionInfo_[static_cast<int>(DIRECTION_NAME::FRONT_RIGHT)];
		break;
	case Piece::PIECE_TYPE::RYUMA:		//	竜馬（成った角行）
		this->GetPieceInfo(index).direction_[0] = directionInfo_[static_cast<int>(DIRECTION_NAME::FRONT)];
		this->GetPieceInfo(index).direction_[1] = directionInfo_[static_cast<int>(DIRECTION_NAME::FRONT_LEFT)];
		this->GetPieceInfo(index).direction_[2] = directionInfo_[static_cast<int>(DIRECTION_NAME::LEFT)];
		this->GetPieceInfo(index).direction_[3] = directionInfo_[static_cast<int>(DIRECTION_NAME::BACK_LEFT)];
		this->GetPieceInfo(index).direction_[4] = directionInfo_[static_cast<int>(DIRECTION_NAME::BACK)];
		this->GetPieceInfo(index).direction_[5] = directionInfo_[static_cast<int>(DIRECTION_NAME::BACK_RIGHT)];
		this->GetPieceInfo(index).direction_[6] = directionInfo_[static_cast<int>(DIRECTION_NAME::RIGHT)];
		this->GetPieceInfo(index).direction_[7] = directionInfo_[static_cast<int>(DIRECTION_NAME::FRONT_RIGHT)];
		break;
	case Piece::PIECE_TYPE::KINSHO:		//	金将
		this->GetPieceInfo(index).direction_[0] = directionInfo_[static_cast<int>(DIRECTION_NAME::FRONT)];
		this->GetPieceInfo(index).direction_[1] = directionInfo_[static_cast<int>(DIRECTION_NAME::FRONT_LEFT)];
		this->GetPieceInfo(index).direction_[2] = directionInfo_[static_cast<int>(DIRECTION_NAME::LEFT)];
		this->GetPieceInfo(index).direction_[3] = directionInfo_[static_cast<int>(DIRECTION_NAME::BACK)];
		this->GetPieceInfo(index).direction_[4] = directionInfo_[static_cast<int>(DIRECTION_NAME::FRONT_RIGHT)];
		this->GetPieceInfo(index).direction_[5] = directionInfo_[static_cast<int>(DIRECTION_NAME::RIGHT)];
		break;
	case Piece::PIECE_TYPE::OUSHO:		//	王将
		this->GetPieceInfo(index).direction_[0] = directionInfo_[static_cast<int>(DIRECTION_NAME::FRONT)];
		this->GetPieceInfo(index).direction_[1] = directionInfo_[static_cast<int>(DIRECTION_NAME::FRONT_LEFT)];
		this->GetPieceInfo(index).direction_[2] = directionInfo_[static_cast<int>(DIRECTION_NAME::LEFT)];
		this->GetPieceInfo(index).direction_[3] = directionInfo_[static_cast<int>(DIRECTION_NAME::BACK_LEFT)];
		this->GetPieceInfo(index).direction_[4] = directionInfo_[static_cast<int>(DIRECTION_NAME::BACK)];
		this->GetPieceInfo(index).direction_[5] = directionInfo_[static_cast<int>(DIRECTION_NAME::BACK_RIGHT)];
		this->GetPieceInfo(index).direction_[6] = directionInfo_[static_cast<int>(DIRECTION_NAME::RIGHT)];
		this->GetPieceInfo(index).direction_[7] = directionInfo_[static_cast<int>(DIRECTION_NAME::FRONT_RIGHT)];
		break;
	case Piece::PIECE_TYPE::GYOKUSHO:	//	玉将	相手の王
		this->GetPieceInfo(index).direction_[0] = directionInfo_[static_cast<int>(DIRECTION_NAME::FRONT)];
		this->GetPieceInfo(index).direction_[1] = directionInfo_[static_cast<int>(DIRECTION_NAME::FRONT_LEFT)];
		this->GetPieceInfo(index).direction_[2] = directionInfo_[static_cast<int>(DIRECTION_NAME::LEFT)];
		this->GetPieceInfo(index).direction_[3] = directionInfo_[static_cast<int>(DIRECTION_NAME::BACK_LEFT)];
		this->GetPieceInfo(index).direction_[4] = directionInfo_[static_cast<int>(DIRECTION_NAME::BACK)];
		this->GetPieceInfo(index).direction_[5] = directionInfo_[static_cast<int>(DIRECTION_NAME::BACK_RIGHT)];
		this->GetPieceInfo(index).direction_[6] = directionInfo_[static_cast<int>(DIRECTION_NAME::RIGHT)];
		this->GetPieceInfo(index).direction_[7] = directionInfo_[static_cast<int>(DIRECTION_NAME::FRONT_RIGHT)];
		break;
	}
}

//	更新処理
void Piece::Update(float elapsedTime)
{

}

//	破棄
void Piece::Destroy()
{
	PieceManager::Instance().Remove(this);
}

//	選択フラグセット
void Piece::SetPieceChoise(bool choise)
{
	this->pieceInfo_->isChoise_ = choise;
}

//	描画処理
void Piece::Render()
{
	GameObject::Render(1.0f);
}

//	デバッグ用駒の種類文字列セット
void Piece::SetDebugStr()
{
	//	駒の種類
	switch (this->GetPieceInfo(this->myNum_).pieceType_) {
	case PIECE_TYPE::HUHYO:
		typeStr_ = u8"歩兵HUHYOU";
		break;
	case PIECE_TYPE::TOKIN:
		typeStr_ = u8"と金TOKIN";
		break;
	case PIECE_TYPE::KYOUSHA:
		typeStr_ = u8"香車KYOUSHA";
		break;
	case PIECE_TYPE::NARIKYO:
		typeStr_ = u8"成香NARIKYOU";
		break;
	case PIECE_TYPE::KEIMA:
		typeStr_ = u8"桂馬KEIMA";
		break;
	case PIECE_TYPE::NARIKEI:
		typeStr_ = u8"成桂NARIKEI";
		break;
	case PIECE_TYPE::GINSHO:
		typeStr_ = u8"銀将GINSHOU";
		break;
	case PIECE_TYPE::NARIGIN:
		typeStr_ = u8"成銀NARIGIN";
		break;
	case PIECE_TYPE::HISHA:
		typeStr_ = u8"飛車HISHA";
		break;
	case PIECE_TYPE::RYUO:
		typeStr_ = u8"竜王RYUOU";
		break;
	case PIECE_TYPE::KAKUGYO:
		typeStr_ = u8"角行KAKUGYOU";
		break;
	case PIECE_TYPE::RYUMA:
		typeStr_ = u8"竜馬RYUMA";
		break;
	case PIECE_TYPE::KINSHO:
		typeStr_ = u8"金将KINSHOU";
		break;
	case PIECE_TYPE::OUSHO:
		typeStr_ = u8"王将OUSHOU";
		break;
	case PIECE_TYPE::GYOKUSHO:
		typeStr_ = u8"玉将GYOKUSHO";
		break;
	}

	switch (this->GetPieceInfo(this->myNum_).isChoise_)
	{
	case true:
		choiseStr_ = u8"選択されている";
		break;
	case false:
		choiseStr_ = u8"選択されていない";
		break;
	}
}

//	デバッグ描画
void Piece::DrawDebug()
{
	//	駒の要素番号 何個目の駒か
	std::string n = "piace" + std::to_string(myNum_);
	SetDebugStr();

	if (ImGui::TreeNode(n.c_str()))	//	駒の要素番号
	{
		ImGui::Text(u8"State　%s", typeStr_.c_str());		//	駒の種類
		ImGui::Text(u8"IsChoise　%s", choiseStr_.c_str());	//	駒が選択されているか
		GetTransform()->DrawDebug();
		ImGui::TreePop();
	}
}