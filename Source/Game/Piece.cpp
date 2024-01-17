#include "Piece.h"

#include "PieceManager.h"
#include "Stage.h"

int Piece::num = 0;	//	デバッグ用

//	コンストラクタ
Piece::Piece(const char* filename, bool triangulate)
	:GameObject(filename, triangulate)
{
	myNum_ = num++;	//	デバッグ用
}

//	初期化
void Piece::Initialize(int index)
{
	//	駒の座標 = (将棋盤(9x9マス)上での座標 + pieceOffset) * range_

	GetTransform()->SetPositionX((pieceInfo_[index].posX_ + pieceOffset_.x) * range_);
	GetTransform()->SetPositionY(Stage::Instance().GetTransform()->GetPosition().y);	//将棋盤と高さ合わせるため補正とかしない
	GetTransform()->SetPositionZ((pieceInfo_[index].posY_ + pieceOffset_.z) * range_);

	//	敵のときだけモデルの向きを反転させる
	if (pieceInfo_[index].isEnemy_)GetTransform()->SetRotationY(DirectX::XMConvertToRadians(180));
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

//	描画処理
void Piece::Render()
{
	GameObject::Render(1.0f);
}

//	デバッグ描画
void Piece::DrawDebug()
{
	//	駒の要素番号 何個目の駒か
	std::string n = "piace" + std::to_string(myNum_);	
	SetDebugStr();

	if (ImGui::TreeNode(n.c_str()))	//	駒の要素番号
	{
		ImGui::Text(u8"State　%s", typeStr_.c_str());	//	駒の種類
		GetTransform()->DrawDebug();
		ImGui::TreePop();
	}
}

void Piece::SetDebugStr()
{
	//	駒の種類
	switch (this->GetPieceInfo(this->myNum_).pieceType_) {
	case PIECE_TYPE::HUHYOU:
		typeStr_ = u8"歩兵HUHYOU";
		break;
	case PIECE_TYPE::TOKIN:
		typeStr_ = u8"と金TOKIN";
		break;
	case PIECE_TYPE::KYOUSHA:
		typeStr_ = u8"香車KYOUSHA";
		break;
	case PIECE_TYPE::NARIKYOU:
		typeStr_ = u8"成香NARIKYOU";
		break;
	case PIECE_TYPE::KEIMA:
		typeStr_ = u8"桂馬KEIMA";
		break;
	case PIECE_TYPE::NARIKEI:
		typeStr_ = u8"成桂NARIKEI";
		break;
	case PIECE_TYPE::GINSHOU:
		typeStr_ = u8"銀将GINSHOU";
		break;
	case PIECE_TYPE::NARIGIN:
		typeStr_ = u8"成銀NARIGIN";
		break;
	case PIECE_TYPE::HISHA:
		typeStr_ = u8"飛車HISHA";
		break;
	case PIECE_TYPE::RYUOU:
		typeStr_ = u8"竜王RYUOU";
		break;
	case PIECE_TYPE::KAKUGYOU:
		typeStr_ = u8"角行KAKUGYOU";
		break;
	case PIECE_TYPE::RYUMA:
		typeStr_ = u8"竜馬RYUMA";
		break;
	case PIECE_TYPE::KINSHOU:
		typeStr_ = u8"金将KINSHOU";
		break;
	case PIECE_TYPE::OUSHOU:
		typeStr_ = u8"王将OUSHOU";
		break;
	}
}
