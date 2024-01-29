#include "Piece.h"

#include "PieceManager.h"
#include "Stage.h"
#include "../Others/MathHelper.h"
#include "ShogiBoard.h"
#include "../Easing.h"
#include "../Core/HighResolutionTimer.h"

#include "../Core/Framework.h"

int Piece::num = 0;	//	デバッグ用

//	コンストラクタ
Piece::Piece(const char* fileName, bool triangulate, bool usedAsCollider)
	:GameObject(fileName, triangulate, usedAsCollider)
{
	myNum_ = num++;	//	デバッグ用
}

//	デストラクタ
Piece::~Piece()
{
}

//	初期化
void Piece::Initialize(int index)
{
	//	駒の方向セット
	SetPieceDirection(index);

	//	駒の座標 = (将棋盤(9x9マス)上での座標 + pieceOffset) * range_
	this->GetTransform()->SetPositionX((static_cast<float>(pieceInfo_[index].posX_) + pieceOffset_.x) * range_);
	this->GetTransform()->SetPositionY(ShogiBoard::Instance().GetTransform()->GetPosition().y);	//将棋盤と高さ合わせるため補正とかしない
	this->GetTransform()->SetPositionZ((static_cast<float>(pieceInfo_[index].posY_) + pieceOffset_.z) * range_);

	//	敵のときだけモデルの向きを反転させる
	if (pieceInfo_[index].isEnemy_)GetTransform()->SetRotationY(DirectX::XMConvertToRadians(180.0f));

	SetState(PIECE_STATE::NORMAL);	//	駒のステート初期化
	airPos_ = 20.0f;				//	空中制限位置初期化
}

//	駒データ更新
void Piece::PieceInfoUpdate(int index)
{
	//	駒の座標 = (将棋盤(9x9マス)上での座標 + pieceOffset) * range_
	this->GetTransform()->SetPositionX((static_cast<float>(pieceInfo_[index].posX_) + pieceOffset_.x) * range_);
	this->GetTransform()->SetPositionY(ShogiBoard::Instance().GetTransform()->GetPosition().y);	//将棋盤と高さ合わせるため補正とかしない
	this->GetTransform()->SetPositionZ((static_cast<float>(pieceInfo_[index].posY_) + pieceOffset_.z) * range_);

	//	敵のときだけモデルの向きを反転させる
	if (pieceInfo_[index].isEnemy_)GetTransform()->SetRotationY(DirectX::XMConvertToRadians(180.0f));
}

//	駒の方向登録(pieceInfo_に登録)
void Piece::SetPieceDirection(int index)	//　初期化以外に成った時も呼ぶ
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
void Piece::Update(float elapsedTime,int index)
{
	if (!this->pieceInfo_[index].isEnemy_)	//	TODO:自分の駒なら相手の駒に吹っ飛ぶようにする
	{
		//	上昇回数制限
		if (this->pieceState_ == PIECE_STATE::UP)	//	上昇ステートのときだけ処理する
		{
			this->Up(upSpeed);
		}
		//	突っ込む処理
		if (this->pieceState_ == PIECE_STATE::THRUST)
		{
			this->MoveToTarget();
		}
		//AddImpulse(impulse_);
		//Move(index);
	}
	else	//	敵の駒なら
	{
		SetState(PIECE_STATE::STOP);	//	制動ステートへ遷移
	}
	UpdateVelocity(elapsedTime);
}

//衝撃を与える
void Piece::AddImpulse(const DirectX::XMFLOAT3& impulse)
{
	//速力(velocity)に力を加える
	this->velocity_.x += impulse.x;
	this->velocity_.y += impulse.y;
	this->velocity_.z += impulse.z;
}

//	上昇処理
void Piece::Up(float speed)
{
	//TODO:上方向の力を設定
	//this->velocity_.y = speed;
	// イージング関数でpositionを直接いじって駒を上昇させる
	if (upTimer_ < upMax_)
	{
		float posY = Dante::Math::Easing::InSine(upTimer_, upMax_, 120.0f, 0.0f);
		this->GetTransform()->SetPositionY(posY);
		upTimer_ += Framework::tictoc_.GetDeltaTime();
	}
	else //	上昇が終わったら
	{
		this->SetState(PIECE_STATE::THRUST);
	}
}

//	移動処理　吹っ飛ばす用
void Piece::Move(int index)
{
	this->GetTransform()->SetPosition(this->GetTransform()->GetPosition() + velocity_);
}

//	ターゲットに向かって飛ぶ
void Piece::MoveToTarget()
{

}

////////////////////////////////////////////////////////////
//	移動処理

//	速力処理更新
void Piece::UpdateVelocity(float elapsedTime)
{
	//	経過フレーム
	float elapsedFrame = 60.0f * elapsedTime;

	//	垂直速力更新処理(重力)
	UpdateVerticalVelocity(elapsedFrame);

	//	水平速力更新処理
	UpdateHorizontalVelocity(elapsedFrame);

	//	垂直移動更新処理
	UpdateVerticalMove(elapsedTime);

	//	水平移動更新処理
	UpdateHorizontalMove(elapsedTime);

}

//	垂直速力更新処理
void Piece::UpdateVerticalVelocity(float elapsedFrame)
{
	//重力処理
	//this->velocity_.y += gravity_ * elapsedFrame;
	if (pieceState_ == PIECE_STATE::STOP)
	{
		this->velocity_ = { 0,0,0 };
	}
}

//	垂直移動更新処理
void Piece::UpdateVerticalMove(float elapsedTime)
{
	//	垂直方向の移動量
	float my = this->velocity_.y * elapsedTime;

	slopeRate = 0.0f;

	//	移動処理
	DirectX::XMFLOAT3 position = this->GetTransform()->GetPosition();
	this->GetTransform()->SetPositionY(position.y + this->velocity_.y);

	//	地面判定
	if (position.y < ShogiBoard::Instance().GetTransform()->GetPosition().y)
	{
		this->GetTransform()->SetPositionY(ShogiBoard::Instance().GetTransform()->GetPosition().y);
		velocity_.y = 0.0f;

		//	着地した
		if (!isGround_)
		{
			OnLanding();
		}
		isGround_ = true;
	}
	else
	{
		isGround_ = false;
	}

	//	上限判定(上に行ったら止まる)
	if (position.y > airPos_)
	{
		this->GetTransform()->SetPositionY(airPos_);
		SetState(PIECE_STATE::STOP);	//	制動ステートへ切り替え
	}
}

//	水平速力更新処理
void Piece::UpdateHorizontalVelocity(float elapsedFrame)
{
	//	XZ平面の速力を減速する
	float length = sqrtf(velocity_.x * velocity_.x + velocity_.z * velocity_.z);
	if (length > 0.0f)
	{
		//	摩擦力
		float friction = this->friction * elapsedFrame;

		//	空中にいるときは摩擦力を減らす
		if (!isGround_)friction *= airControl;

		//	摩擦による横方向の減速処理
		if (length > friction)
		{
			//単位ベクトル化
			float vx = velocity_.x / length;
			float vz = velocity_.z / length;

			velocity_.x -= vx * friction;
			velocity_.z -= vz * friction;
		}
		//	横方向の速力が摩擦力以下になったので速力を無効化
		else
		{
			velocity_.x = 0.0f;
			velocity_.z = 0.0f;
		}
	}

	//	XZ平面の速力を加速する
	if (length <= maxMoveSpeed)
	{
		//	移動ベクトルがゼロベクトルでないなら加速する
		float moveVecLength = sqrtf(moveVecX * moveVecX + moveVecZ * moveVecZ);//スティックの入力値を取ってくる
		if (moveVecLength > 0.0f)
		{
			//	加速力
			float acceleration = this->acceleration * elapsedFrame;

			//	空中にいるときは摩擦力を減らす
			if (!isGround_)acceleration *= airControl;

			//	移動ベクトルによる加速処理
			velocity_.x += moveVecX * acceleration;
			velocity_.z += moveVecZ * acceleration;

			//	最大速度制限
			float length = sqrtf(velocity_.x * velocity_.x + velocity_.z * velocity_.z);
			if (length > maxMoveSpeed)
			{
				//	単位ベクトル化
				float vx = velocity_.x / length;
				float vz = velocity_.z / length;

				velocity_.x = vx * maxMoveSpeed;
				velocity_.z = vz * maxMoveSpeed;
			}

			//	下り坂でガタガタしないようにする
			if (isGround_ && slopeRate > 0.0f)
			{
				velocity_.y -= length * slopeRate * elapsedFrame;
			}

		}
	}
	//	移動ベクトルをリセット
	moveVecX = 0.0f;
	moveVecZ = 0.0f;

	//	制動ステートならvelocityなし
	if (pieceState_ == PIECE_STATE::STOP)
	{
		velocity_ = { 0,0,0 };
	}
}

//	水平移動更新処理
void Piece::UpdateHorizontalMove(float elapsedTime)
{
	//	水平速力量計算
	float velocityLengthXZ = sqrtf(velocity_.x * velocity_.x + velocity_.z * velocity_.z);
	if (velocityLengthXZ > 0.0f)
	{
		//	水平移動値
		float mx = velocity_.x * elapsedTime;
		float mz = velocity_.z * elapsedTime;

		{
			//	移動
			DirectX::XMFLOAT3 position = this->GetTransform()->GetPosition();
			this->GetTransform()->SetPositionX(position.x + mx);
			this->GetTransform()->SetPositionZ(position.z + mz);
			
		}
	}
}

//	ステートセット
void Piece::SetState(PIECE_STATE pieceState)
{
	pieceState_ = pieceState;
}

///////////////////////////////////////////////////////////

//	移動処理 普通の将棋用
void Piece::Move(int index,int x,int y)
{
	if (!pieceInfo_[index].isEnemy_)	//	自分の駒
	{
		pieceInfo_[index].posX_ -= x;
		pieceInfo_[index].posY_ -= y;
	}
	else								//	敵の駒
	{
		pieceInfo_[index].posX_ += x;
		pieceInfo_[index].posY_ += y;
	}
}

//	破棄
void Piece::Destroy()
{
	PieceManager::Instance().Remove(this);
}

//	選択フラグセット
void Piece::SetChoicePiece(bool choice)
{
	this->pieceInfo_->isChoice_ = choice;
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

	//	駒が選択されているか
	switch (this->GetPieceInfo(this->myNum_).isChoice_)
	{
	case true:
		choiceStr_ = u8"選択されている";
		break;
	case false:
		choiceStr_ = u8"選択されていない";
		break;
	}

	//	敵の駒か味方の駒か
	switch (this->GetPieceInfo(this->myNum_).isEnemy_)
	{
	case true:
		isEnemyStr_ = u8"敵の駒";
		break;
	case false:
		isEnemyStr_ = u8"自分の駒";
		break;
	}

	//	駒のステート
	switch (this->pieceState_)
	{
	case PIECE_STATE::NORMAL:
		pieceStateStr_ = u8"NORMAL";
		break;
	case PIECE_STATE::UP:
		pieceStateStr_ = u8"UP";
		break;
	case PIECE_STATE::STOP:
		pieceStateStr_ = u8"STOP";
		break;
	case PIECE_STATE::THRUST:
		pieceStateStr_ = u8"THRUST";
		break;
	}
}

//	デバッグ描画
void Piece::DrawDebug()
{
	//	駒の要素番号 何個目の駒か
	std::string n = "piace" + std::to_string(myNum_);
	SetDebugStr();

	//	ImGui描画
	if (ImGui::TreeNode(n.c_str()))	//	駒の要素番号
	{
		ImGui::Text(u8"State　%s", typeStr_.c_str());				//	駒の種類
		ImGui::Text(u8"IsChoise　%s", choiceStr_.c_str());			//	駒が選択されているか
		ImGui::Text(u8"IsEnemy　 %s", isEnemyStr_.c_str());			//	自分の駒か敵の駒か
		ImGui::Text(u8"PieceState　 %s", pieceStateStr_.c_str());	//	自分の駒か敵の駒か
		ImGui::DragFloat3("Velocity", &velocity_.x, 1.0f, -FLT_MAX, FLT_MAX);
		GetTransform()->DrawDebug();
		ImGui::TreePop();
	}

	//	デバッグプリミティブ描画
	DrawDebugPrimitive();
}

//	デバッグプリミティブ描画
void Piece::DrawDebugPrimitive()
{
	DebugRenderer* debugRenderer = Graphics::Instance().GetDebugRenderer();

	//衝突判定用のデバッグ円柱を描画
	debugRenderer->DrawCylinder(this->GetTransform()->GetPosition(), radius_, height_, DirectX::XMFLOAT4(0, 0, 0, 1));

}