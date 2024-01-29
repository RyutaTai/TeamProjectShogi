#include "Piece.h"

#include "PieceManager.h"
#include "Stage.h"
#include "../Others/MathHelper.h"
#include "ShogiBoard.h"
#include "../Easing.h"
#include "../Core/HighResolutionTimer.h"

#include "../Core/Framework.h"

int Piece::num = 0;	//	�f�o�b�O�p

//	�R���X�g���N�^
Piece::Piece(const char* fileName, bool triangulate, bool usedAsCollider)
	:GameObject(fileName, triangulate, usedAsCollider)
{
	myNum_ = num++;	//	�f�o�b�O�p
}

//	�f�X�g���N�^
Piece::~Piece()
{
}

//	������
void Piece::Initialize(int index)
{
	//	��̕����Z�b�g
	SetPieceDirection(index);

	//	��̍��W = (������(9x9�}�X)��ł̍��W + pieceOffset) * range_
	this->GetTransform()->SetPositionX((static_cast<float>(pieceInfo_[index].posX_) + pieceOffset_.x) * range_);
	this->GetTransform()->SetPositionY(ShogiBoard::Instance().GetTransform()->GetPosition().y);	//�����Ղƍ������킹�邽�ߕ␳�Ƃ����Ȃ�
	this->GetTransform()->SetPositionZ((static_cast<float>(pieceInfo_[index].posY_) + pieceOffset_.z) * range_);

	//	�G�̂Ƃ��������f���̌����𔽓]������
	if (pieceInfo_[index].isEnemy_)GetTransform()->SetRotationY(DirectX::XMConvertToRadians(180.0f));

	SetState(PIECE_STATE::NORMAL);	//	��̃X�e�[�g������
	airPos_ = 20.0f;				//	�󒆐����ʒu������
}

//	��f�[�^�X�V
void Piece::PieceInfoUpdate(int index)
{
	//	��̍��W = (������(9x9�}�X)��ł̍��W + pieceOffset) * range_
	this->GetTransform()->SetPositionX((static_cast<float>(pieceInfo_[index].posX_) + pieceOffset_.x) * range_);
	this->GetTransform()->SetPositionY(ShogiBoard::Instance().GetTransform()->GetPosition().y);	//�����Ղƍ������킹�邽�ߕ␳�Ƃ����Ȃ�
	this->GetTransform()->SetPositionZ((static_cast<float>(pieceInfo_[index].posY_) + pieceOffset_.z) * range_);

	//	�G�̂Ƃ��������f���̌����𔽓]������
	if (pieceInfo_[index].isEnemy_)GetTransform()->SetRotationY(DirectX::XMConvertToRadians(180.0f));
}

//	��̕����o�^(pieceInfo_�ɓo�^)
void Piece::SetPieceDirection(int index)	//�@�������ȊO�ɐ����������Ă�
{
	//	��̎�ނ��Ƃɏ����𕪂���(��ɂ���ē�����}�X���قȂ邽��)
	switch (this->GetPieceInfo(index).pieceType_)
	{
	case Piece::PIECE_TYPE::HUHYO:		//	����
		this->GetPieceInfo(index).direction_[0] = directionInfo_[static_cast<int>(DIRECTION_NAME::FRONT)];
		break;
	case Piece::PIECE_TYPE::TOKIN:		//	�Ƌ��i�����������j			
		this->GetPieceInfo(index).direction_[0] = directionInfo_[static_cast<int>(DIRECTION_NAME::FRONT)];
		this->GetPieceInfo(index).direction_[1] = directionInfo_[static_cast<int>(DIRECTION_NAME::FRONT_LEFT)];
		this->GetPieceInfo(index).direction_[2] = directionInfo_[static_cast<int>(DIRECTION_NAME::LEFT)];
		this->GetPieceInfo(index).direction_[3] = directionInfo_[static_cast<int>(DIRECTION_NAME::BACK)];
		this->GetPieceInfo(index).direction_[4] = directionInfo_[static_cast<int>(DIRECTION_NAME::FRONT_RIGHT)];
		this->GetPieceInfo(index).direction_[5] = directionInfo_[static_cast<int>(DIRECTION_NAME::RIGHT)];
		break;
	case Piece::PIECE_TYPE::KYOUSHA:	//	����				
		this->GetPieceInfo(index).direction_[0] = directionInfo_[static_cast<int>(DIRECTION_NAME::FRONT)];
		break;
	case Piece::PIECE_TYPE::NARIKYO:	//	�����i���������ԁj				
		this->GetPieceInfo(index).direction_[0] = directionInfo_[static_cast<int>(DIRECTION_NAME::FRONT)];
		this->GetPieceInfo(index).direction_[1] = directionInfo_[static_cast<int>(DIRECTION_NAME::FRONT_LEFT)];
		this->GetPieceInfo(index).direction_[2] = directionInfo_[static_cast<int>(DIRECTION_NAME::LEFT)];
		this->GetPieceInfo(index).direction_[3] = directionInfo_[static_cast<int>(DIRECTION_NAME::BACK)];
		this->GetPieceInfo(index).direction_[4] = directionInfo_[static_cast<int>(DIRECTION_NAME::FRONT_RIGHT)];
		this->GetPieceInfo(index).direction_[5] = directionInfo_[static_cast<int>(DIRECTION_NAME::RIGHT)];
		break;
	case Piece::PIECE_TYPE::KEIMA:		//	�j�n				
		this->GetPieceInfo(index).direction_[0] = directionInfo_[static_cast<int>(DIRECTION_NAME::KEIMA_RIGHT)];
		this->GetPieceInfo(index).direction_[1] = directionInfo_[static_cast<int>(DIRECTION_NAME::KEIMA_LEFT)];
		break;
	case Piece::PIECE_TYPE::NARIKEI:	//	���j�i�������j�n�j
		this->GetPieceInfo(index).direction_[0] = directionInfo_[static_cast<int>(DIRECTION_NAME::FRONT)];
		this->GetPieceInfo(index).direction_[1] = directionInfo_[static_cast<int>(DIRECTION_NAME::FRONT_LEFT)];
		this->GetPieceInfo(index).direction_[2] = directionInfo_[static_cast<int>(DIRECTION_NAME::LEFT)];
		this->GetPieceInfo(index).direction_[3] = directionInfo_[static_cast<int>(DIRECTION_NAME::BACK)];
		this->GetPieceInfo(index).direction_[4] = directionInfo_[static_cast<int>(DIRECTION_NAME::FRONT_RIGHT)];
		this->GetPieceInfo(index).direction_[5] = directionInfo_[static_cast<int>(DIRECTION_NAME::RIGHT)];
		break;
	case Piece::PIECE_TYPE::GINSHO:		//	�⏫
		this->GetPieceInfo(index).direction_[0] = directionInfo_[static_cast<int>(DIRECTION_NAME::FRONT)];
		this->GetPieceInfo(index).direction_[1] = directionInfo_[static_cast<int>(DIRECTION_NAME::FRONT_LEFT)];
		this->GetPieceInfo(index).direction_[2] = directionInfo_[static_cast<int>(DIRECTION_NAME::FRONT_RIGHT)];
		this->GetPieceInfo(index).direction_[3] = directionInfo_[static_cast<int>(DIRECTION_NAME::BACK_LEFT)];
		this->GetPieceInfo(index).direction_[4] = directionInfo_[static_cast<int>(DIRECTION_NAME::BACK_RIGHT)];
		this->GetPieceInfo(index).direction_[5] = directionInfo_[static_cast<int>(DIRECTION_NAME::BACK)];
		break;
	case Piece::PIECE_TYPE::NARIGIN:	//	����i�������⏫�j
		this->GetPieceInfo(index).direction_[0] = directionInfo_[static_cast<int>(DIRECTION_NAME::FRONT)];
		this->GetPieceInfo(index).direction_[1] = directionInfo_[static_cast<int>(DIRECTION_NAME::FRONT_LEFT)];
		this->GetPieceInfo(index).direction_[2] = directionInfo_[static_cast<int>(DIRECTION_NAME::LEFT)];
		this->GetPieceInfo(index).direction_[3] = directionInfo_[static_cast<int>(DIRECTION_NAME::BACK)];
		this->GetPieceInfo(index).direction_[4] = directionInfo_[static_cast<int>(DIRECTION_NAME::FRONT_RIGHT)];
		this->GetPieceInfo(index).direction_[5] = directionInfo_[static_cast<int>(DIRECTION_NAME::RIGHT)];
		break;
	case Piece::PIECE_TYPE::HISHA:		//	���
		this->GetPieceInfo(index).direction_[0] = directionInfo_[static_cast<int>(DIRECTION_NAME::FRONT)];
		this->GetPieceInfo(index).direction_[1] = directionInfo_[static_cast<int>(DIRECTION_NAME::LEFT)];
		this->GetPieceInfo(index).direction_[2] = directionInfo_[static_cast<int>(DIRECTION_NAME::RIGHT)];
		this->GetPieceInfo(index).direction_[3] = directionInfo_[static_cast<int>(DIRECTION_NAME::BACK)];
		break;
	case Piece::PIECE_TYPE::RYUO:		//	�����i��������ԁj
		this->GetPieceInfo(index).direction_[0] = directionInfo_[static_cast<int>(DIRECTION_NAME::FRONT)];
		this->GetPieceInfo(index).direction_[1] = directionInfo_[static_cast<int>(DIRECTION_NAME::FRONT_LEFT)];
		this->GetPieceInfo(index).direction_[2] = directionInfo_[static_cast<int>(DIRECTION_NAME::LEFT)];
		this->GetPieceInfo(index).direction_[3] = directionInfo_[static_cast<int>(DIRECTION_NAME::BACK_LEFT)];
		this->GetPieceInfo(index).direction_[4] = directionInfo_[static_cast<int>(DIRECTION_NAME::BACK)];
		this->GetPieceInfo(index).direction_[5] = directionInfo_[static_cast<int>(DIRECTION_NAME::BACK_RIGHT)];
		this->GetPieceInfo(index).direction_[6] = directionInfo_[static_cast<int>(DIRECTION_NAME::RIGHT)];
		this->GetPieceInfo(index).direction_[7] = directionInfo_[static_cast<int>(DIRECTION_NAME::FRONT_RIGHT)];
		break;
	case Piece::PIECE_TYPE::KAKUGYO:	//	�p�s
		this->GetPieceInfo(index).direction_[0] = directionInfo_[static_cast<int>(DIRECTION_NAME::FRONT_LEFT)];
		this->GetPieceInfo(index).direction_[1] = directionInfo_[static_cast<int>(DIRECTION_NAME::BACK_LEFT)];
		this->GetPieceInfo(index).direction_[2] = directionInfo_[static_cast<int>(DIRECTION_NAME::BACK_RIGHT)];
		this->GetPieceInfo(index).direction_[3] = directionInfo_[static_cast<int>(DIRECTION_NAME::FRONT_RIGHT)];
		break;
	case Piece::PIECE_TYPE::RYUMA:		//	���n�i�������p�s�j
		this->GetPieceInfo(index).direction_[0] = directionInfo_[static_cast<int>(DIRECTION_NAME::FRONT)];
		this->GetPieceInfo(index).direction_[1] = directionInfo_[static_cast<int>(DIRECTION_NAME::FRONT_LEFT)];
		this->GetPieceInfo(index).direction_[2] = directionInfo_[static_cast<int>(DIRECTION_NAME::LEFT)];
		this->GetPieceInfo(index).direction_[3] = directionInfo_[static_cast<int>(DIRECTION_NAME::BACK_LEFT)];
		this->GetPieceInfo(index).direction_[4] = directionInfo_[static_cast<int>(DIRECTION_NAME::BACK)];
		this->GetPieceInfo(index).direction_[5] = directionInfo_[static_cast<int>(DIRECTION_NAME::BACK_RIGHT)];
		this->GetPieceInfo(index).direction_[6] = directionInfo_[static_cast<int>(DIRECTION_NAME::RIGHT)];
		this->GetPieceInfo(index).direction_[7] = directionInfo_[static_cast<int>(DIRECTION_NAME::FRONT_RIGHT)];
		break;
	case Piece::PIECE_TYPE::KINSHO:		//	����
		this->GetPieceInfo(index).direction_[0] = directionInfo_[static_cast<int>(DIRECTION_NAME::FRONT)];
		this->GetPieceInfo(index).direction_[1] = directionInfo_[static_cast<int>(DIRECTION_NAME::FRONT_LEFT)];
		this->GetPieceInfo(index).direction_[2] = directionInfo_[static_cast<int>(DIRECTION_NAME::LEFT)];
		this->GetPieceInfo(index).direction_[3] = directionInfo_[static_cast<int>(DIRECTION_NAME::BACK)];
		this->GetPieceInfo(index).direction_[4] = directionInfo_[static_cast<int>(DIRECTION_NAME::FRONT_RIGHT)];
		this->GetPieceInfo(index).direction_[5] = directionInfo_[static_cast<int>(DIRECTION_NAME::RIGHT)];
		break;
	case Piece::PIECE_TYPE::OUSHO:		//	����
		this->GetPieceInfo(index).direction_[0] = directionInfo_[static_cast<int>(DIRECTION_NAME::FRONT)];
		this->GetPieceInfo(index).direction_[1] = directionInfo_[static_cast<int>(DIRECTION_NAME::FRONT_LEFT)];
		this->GetPieceInfo(index).direction_[2] = directionInfo_[static_cast<int>(DIRECTION_NAME::LEFT)];
		this->GetPieceInfo(index).direction_[3] = directionInfo_[static_cast<int>(DIRECTION_NAME::BACK_LEFT)];
		this->GetPieceInfo(index).direction_[4] = directionInfo_[static_cast<int>(DIRECTION_NAME::BACK)];
		this->GetPieceInfo(index).direction_[5] = directionInfo_[static_cast<int>(DIRECTION_NAME::BACK_RIGHT)];
		this->GetPieceInfo(index).direction_[6] = directionInfo_[static_cast<int>(DIRECTION_NAME::RIGHT)];
		this->GetPieceInfo(index).direction_[7] = directionInfo_[static_cast<int>(DIRECTION_NAME::FRONT_RIGHT)];
		break;
	case Piece::PIECE_TYPE::GYOKUSHO:	//	�ʏ�	����̉�
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

//	�X�V����
void Piece::Update(float elapsedTime,int index)
{
	if (!this->pieceInfo_[index].isEnemy_)	//	TODO:�����̋�Ȃ瑊��̋�ɐ�����Ԃ悤�ɂ���
	{
		//	�㏸�񐔐���
		if (this->pieceState_ == PIECE_STATE::UP)	//	�㏸�X�e�[�g�̂Ƃ�������������
		{
			this->Up(upSpeed);
		}
		//	�˂����ޏ���
		if (this->pieceState_ == PIECE_STATE::THRUST)
		{
			this->MoveToTarget();
		}
		//AddImpulse(impulse_);
		//Move(index);
	}
	else	//	�G�̋�Ȃ�
	{
		SetState(PIECE_STATE::STOP);	//	�����X�e�[�g�֑J��
	}
	UpdateVelocity(elapsedTime);
}

//�Ռ���^����
void Piece::AddImpulse(const DirectX::XMFLOAT3& impulse)
{
	//����(velocity)�ɗ͂�������
	this->velocity_.x += impulse.x;
	this->velocity_.y += impulse.y;
	this->velocity_.z += impulse.z;
}

//	�㏸����
void Piece::Up(float speed)
{
	//TODO:������̗͂�ݒ�
	//this->velocity_.y = speed;
	// �C�[�W���O�֐���position�𒼐ڂ������ċ���㏸������
	if (upTimer_ < upMax_)
	{
		float posY = Dante::Math::Easing::InSine(upTimer_, upMax_, 120.0f, 0.0f);
		this->GetTransform()->SetPositionY(posY);
		upTimer_ += Framework::tictoc_.GetDeltaTime();
	}
	else //	�㏸���I�������
	{
		this->SetState(PIECE_STATE::THRUST);
	}
}

//	�ړ������@������΂��p
void Piece::Move(int index)
{
	this->GetTransform()->SetPosition(this->GetTransform()->GetPosition() + velocity_);
}

//	�^�[�Q�b�g�Ɍ������Ĕ��
void Piece::MoveToTarget()
{

}

////////////////////////////////////////////////////////////
//	�ړ�����

//	���͏����X�V
void Piece::UpdateVelocity(float elapsedTime)
{
	//	�o�߃t���[��
	float elapsedFrame = 60.0f * elapsedTime;

	//	�������͍X�V����(�d��)
	UpdateVerticalVelocity(elapsedFrame);

	//	�������͍X�V����
	UpdateHorizontalVelocity(elapsedFrame);

	//	�����ړ��X�V����
	UpdateVerticalMove(elapsedTime);

	//	�����ړ��X�V����
	UpdateHorizontalMove(elapsedTime);

}

//	�������͍X�V����
void Piece::UpdateVerticalVelocity(float elapsedFrame)
{
	//�d�͏���
	//this->velocity_.y += gravity_ * elapsedFrame;
	if (pieceState_ == PIECE_STATE::STOP)
	{
		this->velocity_ = { 0,0,0 };
	}
}

//	�����ړ��X�V����
void Piece::UpdateVerticalMove(float elapsedTime)
{
	//	���������̈ړ���
	float my = this->velocity_.y * elapsedTime;

	slopeRate = 0.0f;

	//	�ړ�����
	DirectX::XMFLOAT3 position = this->GetTransform()->GetPosition();
	this->GetTransform()->SetPositionY(position.y + this->velocity_.y);

	//	�n�ʔ���
	if (position.y < ShogiBoard::Instance().GetTransform()->GetPosition().y)
	{
		this->GetTransform()->SetPositionY(ShogiBoard::Instance().GetTransform()->GetPosition().y);
		velocity_.y = 0.0f;

		//	���n����
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

	//	�������(��ɍs������~�܂�)
	if (position.y > airPos_)
	{
		this->GetTransform()->SetPositionY(airPos_);
		SetState(PIECE_STATE::STOP);	//	�����X�e�[�g�֐؂�ւ�
	}
}

//	�������͍X�V����
void Piece::UpdateHorizontalVelocity(float elapsedFrame)
{
	//	XZ���ʂ̑��͂���������
	float length = sqrtf(velocity_.x * velocity_.x + velocity_.z * velocity_.z);
	if (length > 0.0f)
	{
		//	���C��
		float friction = this->friction * elapsedFrame;

		//	�󒆂ɂ���Ƃ��͖��C�͂����炷
		if (!isGround_)friction *= airControl;

		//	���C�ɂ�鉡�����̌�������
		if (length > friction)
		{
			//�P�ʃx�N�g����
			float vx = velocity_.x / length;
			float vz = velocity_.z / length;

			velocity_.x -= vx * friction;
			velocity_.z -= vz * friction;
		}
		//	�������̑��͂����C�͈ȉ��ɂȂ����̂ő��͂𖳌���
		else
		{
			velocity_.x = 0.0f;
			velocity_.z = 0.0f;
		}
	}

	//	XZ���ʂ̑��͂���������
	if (length <= maxMoveSpeed)
	{
		//	�ړ��x�N�g�����[���x�N�g���łȂ��Ȃ��������
		float moveVecLength = sqrtf(moveVecX * moveVecX + moveVecZ * moveVecZ);//�X�e�B�b�N�̓��͒l������Ă���
		if (moveVecLength > 0.0f)
		{
			//	������
			float acceleration = this->acceleration * elapsedFrame;

			//	�󒆂ɂ���Ƃ��͖��C�͂����炷
			if (!isGround_)acceleration *= airControl;

			//	�ړ��x�N�g���ɂ���������
			velocity_.x += moveVecX * acceleration;
			velocity_.z += moveVecZ * acceleration;

			//	�ő呬�x����
			float length = sqrtf(velocity_.x * velocity_.x + velocity_.z * velocity_.z);
			if (length > maxMoveSpeed)
			{
				//	�P�ʃx�N�g����
				float vx = velocity_.x / length;
				float vz = velocity_.z / length;

				velocity_.x = vx * maxMoveSpeed;
				velocity_.z = vz * maxMoveSpeed;
			}

			//	�����ŃK�^�K�^���Ȃ��悤�ɂ���
			if (isGround_ && slopeRate > 0.0f)
			{
				velocity_.y -= length * slopeRate * elapsedFrame;
			}

		}
	}
	//	�ړ��x�N�g�������Z�b�g
	moveVecX = 0.0f;
	moveVecZ = 0.0f;

	//	�����X�e�[�g�Ȃ�velocity�Ȃ�
	if (pieceState_ == PIECE_STATE::STOP)
	{
		velocity_ = { 0,0,0 };
	}
}

//	�����ړ��X�V����
void Piece::UpdateHorizontalMove(float elapsedTime)
{
	//	�������͗ʌv�Z
	float velocityLengthXZ = sqrtf(velocity_.x * velocity_.x + velocity_.z * velocity_.z);
	if (velocityLengthXZ > 0.0f)
	{
		//	�����ړ��l
		float mx = velocity_.x * elapsedTime;
		float mz = velocity_.z * elapsedTime;

		{
			//	�ړ�
			DirectX::XMFLOAT3 position = this->GetTransform()->GetPosition();
			this->GetTransform()->SetPositionX(position.x + mx);
			this->GetTransform()->SetPositionZ(position.z + mz);
			
		}
	}
}

//	�X�e�[�g�Z�b�g
void Piece::SetState(PIECE_STATE pieceState)
{
	pieceState_ = pieceState;
}

///////////////////////////////////////////////////////////

//	�ړ����� ���ʂ̏����p
void Piece::Move(int index,int x,int y)
{
	if (!pieceInfo_[index].isEnemy_)	//	�����̋�
	{
		pieceInfo_[index].posX_ -= x;
		pieceInfo_[index].posY_ -= y;
	}
	else								//	�G�̋�
	{
		pieceInfo_[index].posX_ += x;
		pieceInfo_[index].posY_ += y;
	}
}

//	�j��
void Piece::Destroy()
{
	PieceManager::Instance().Remove(this);
}

//	�I���t���O�Z�b�g
void Piece::SetChoicePiece(bool choice)
{
	this->pieceInfo_->isChoice_ = choice;
}

//	�`�揈��
void Piece::Render()
{
	GameObject::Render(1.0f);
}

//	�f�o�b�O�p��̎�ޕ�����Z�b�g
void Piece::SetDebugStr()
{
	//	��̎��
	switch (this->GetPieceInfo(this->myNum_).pieceType_) {
	case PIECE_TYPE::HUHYO:
		typeStr_ = u8"����HUHYOU";
		break;
	case PIECE_TYPE::TOKIN:
		typeStr_ = u8"�Ƌ�TOKIN";
		break;
	case PIECE_TYPE::KYOUSHA:
		typeStr_ = u8"����KYOUSHA";
		break;
	case PIECE_TYPE::NARIKYO:
		typeStr_ = u8"����NARIKYOU";
		break;
	case PIECE_TYPE::KEIMA:
		typeStr_ = u8"�j�nKEIMA";
		break;
	case PIECE_TYPE::NARIKEI:
		typeStr_ = u8"���jNARIKEI";
		break;
	case PIECE_TYPE::GINSHO:
		typeStr_ = u8"�⏫GINSHOU";
		break;
	case PIECE_TYPE::NARIGIN:
		typeStr_ = u8"����NARIGIN";
		break;
	case PIECE_TYPE::HISHA:
		typeStr_ = u8"���HISHA";
		break;
	case PIECE_TYPE::RYUO:
		typeStr_ = u8"����RYUOU";
		break;
	case PIECE_TYPE::KAKUGYO:
		typeStr_ = u8"�p�sKAKUGYOU";
		break;
	case PIECE_TYPE::RYUMA:
		typeStr_ = u8"���nRYUMA";
		break;
	case PIECE_TYPE::KINSHO:
		typeStr_ = u8"����KINSHOU";
		break;
	case PIECE_TYPE::OUSHO:
		typeStr_ = u8"����OUSHOU";
		break;
	case PIECE_TYPE::GYOKUSHO:
		typeStr_ = u8"�ʏ�GYOKUSHO";
		break;
	}

	//	��I������Ă��邩
	switch (this->GetPieceInfo(this->myNum_).isChoice_)
	{
	case true:
		choiceStr_ = u8"�I������Ă���";
		break;
	case false:
		choiceStr_ = u8"�I������Ă��Ȃ�";
		break;
	}

	//	�G�̋�����̋
	switch (this->GetPieceInfo(this->myNum_).isEnemy_)
	{
	case true:
		isEnemyStr_ = u8"�G�̋�";
		break;
	case false:
		isEnemyStr_ = u8"�����̋�";
		break;
	}

	//	��̃X�e�[�g
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

//	�f�o�b�O�`��
void Piece::DrawDebug()
{
	//	��̗v�f�ԍ� ���ڂ̋
	std::string n = "piace" + std::to_string(myNum_);
	SetDebugStr();

	//	ImGui�`��
	if (ImGui::TreeNode(n.c_str()))	//	��̗v�f�ԍ�
	{
		ImGui::Text(u8"State�@%s", typeStr_.c_str());				//	��̎��
		ImGui::Text(u8"IsChoise�@%s", choiceStr_.c_str());			//	��I������Ă��邩
		ImGui::Text(u8"IsEnemy�@ %s", isEnemyStr_.c_str());			//	�����̋�G�̋
		ImGui::Text(u8"PieceState�@ %s", pieceStateStr_.c_str());	//	�����̋�G�̋
		ImGui::DragFloat3("Velocity", &velocity_.x, 1.0f, -FLT_MAX, FLT_MAX);
		GetTransform()->DrawDebug();
		ImGui::TreePop();
	}

	//	�f�o�b�O�v���~�e�B�u�`��
	DrawDebugPrimitive();
}

//	�f�o�b�O�v���~�e�B�u�`��
void Piece::DrawDebugPrimitive()
{
	DebugRenderer* debugRenderer = Graphics::Instance().GetDebugRenderer();

	//�Փ˔���p�̃f�o�b�O�~����`��
	debugRenderer->DrawCylinder(this->GetTransform()->GetPosition(), radius_, height_, DirectX::XMFLOAT4(0, 0, 0, 1));

}