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
	std::string n = "piace" + std::to_string(myNum_);
	if (ImGui::TreeNode(n.c_str()))
	{
		GetTransform()->DrawDebug();
		ImGui::TreePop();
	}
}
