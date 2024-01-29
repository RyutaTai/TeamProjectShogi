#include "Piece.h"

#include "Stage.h"
#include "ShogiBoard.h"
#include "../Easing.h"
#include "../Others/MathHelper.h"
#include "../Core/HighResolutionTimer.h"
#include "../Core/Framework.h"
#include "../Collision/Collision.h"
#include "../Input/Microphone.h"
#include <random>

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

	SetState(PIECE_STATE::IDLE);	//	��̃X�e�[�g������
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
///////////////////////////////
//	�X�V����
////////////////////////////////
void Piece::Update(float elapsedTime,int index)
{
	switch (Piece::GetState())	//	��̏�Ԃŏ����𕪂���
	{
	case PIECE_STATE::IDLE:		//	�ʏ�
		UpdateIdleState(elapsedTime);
		break;
	case PIECE_STATE::UP:		//	�㏸
		UpdateUpState(elapsedTime, index);
		break;
	case PIECE_STATE::STOP:		//	����
		UpdateStopState(elapsedTime);
		break;
	case PIECE_STATE::THRUST:	//	�ˌ�
		UpdateThrustState(elapsedTime, index);
		break;
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
	//	TODO:������̗͂�ݒ�
	//	this->velocity_.y = speed;
	// �C�[�W���O�֐���position�𒼐ڂ������ċ���㏸������
	if (upTimer_ < upMax_)
	{
		float posY = Dante::Math::Easing::InSine(upTimer_, upMax_, 20.0f, 0.0f);
		this->GetTransform()->SetPositionY(posY);
		upTimer_ += Framework::tictoc_.GetDeltaTime();
	}
	else //	�㏸���I�������
	{
		// TODO::�������
		if(!Microphone::Instance().GetOnRecording())
		this->SetState(PIECE_STATE::THRUST);
	}
}

//	�ړ������@������΂��p
void Piece::Move(int index)
{
	this->GetTransform()->SetPosition(this->GetTransform()->GetPosition() + velocity_);
}

//	TODO:�^�[�Q�b�g�Ɍ������Ĕ��
void Piece::MoveToTarget()
{
	DirectX::XMFLOAT3 myPos = this->GetTransform()->GetPosition();
	DirectX::XMFLOAT3 targetPos = {};

	std::vector<int>index;
	for (int i = 0; i < PIECE_MAX; i++)//	�G�̋�̃C���f�b�N�X���擾
	{
		if (pieceInfo_[i].isEnemy_ == true)
		{
			index.emplace_back(i);
		}
	}
	int selectNo = 0;
	std::random_device rnd;     // �񌈒�I�ȗ���������𐶐�
	std::mt19937 mt(rnd());     //  �����Z���k�E�c�C�X�^��32�r�b�g�ŁA�����͏����V�[�h�l
	std::uniform_int_distribution<> randIndex(0, (index.size()-1)); // [0, index.size()] �܂ł͈̔͂̈�l����
	selectNo = randIndex(mt);
	targetPos.x = ((float)pieceInfo_[index.at(selectNo)].posX_ + pieceOffset_.x) * range_;
	targetPos.y = 0.0f;
	targetPos.z = ((float)pieceInfo_[index.at(selectNo)].posY_ + pieceOffset_.z) * range_;

	// �C�[�W���O�֐���position�𒼐ڂ������ďՓ˂�����
	if (thrustTimer_ < thrustMax_)
	{
		float posX = Dante::Math::Easing::InSine(thrustTimer_, thrustMax_, targetPos.x, myPos.x);
		float posY = Dante::Math::Easing::InSine(thrustTimer_, thrustMax_, targetPos.y, myPos.y);
		float posZ = Dante::Math::Easing::InSine(thrustTimer_, thrustMax_, targetPos.z, myPos.z);
		this->GetTransform()->SetPositionX(posX);
		this->GetTransform()->SetPositionY(posY);
		this->GetTransform()->SetPositionZ(posZ);
		thrustTimer_ += Framework::tictoc_.GetDeltaTime();
	}

	//	TODO:��̏Փˏ���(�~���Ɖ~��)
	//	�S�Ă̓G�Ƃ̑�������ŏՓˏ���
	PieceManager& pieceManager = PieceManager::Instance();
	for (int i = 0; i < PIECE_MAX; i++)
	{
		Piece* piece = pieceManager.GetPiece(i);

		//�Փˏ���
		DirectX::XMFLOAT3 outPosition;
		if (Collision::InterSectCylinderVsCyliner(
			myPos,
			radius_,
			height_,
			piece->GetTransform()->GetPosition(),
			radius_,
			height_,
			outPosition))
		{
			DirectX::XMVECTOR PositionA = DirectX::XMLoadFloat3(&myPos);
			DirectX::XMVECTOR PositionB = DirectX::XMLoadFloat3(&piece->GetTransform()->GetPosition());
			DirectX::XMVECTOR Vec = DirectX::XMVectorSubtract(PositionB, PositionA);
			float VecY = DirectX::XMVectorGetY(Vec);
			if (VecY < 0.1f)	//	��̏�ɓ������Ă�����
			{
				velocity_.y = 0;
			}

			DirectX::XMFLOAT3 impulse;//������΂���
			const float power = 1.0f;
			DirectX::XMFLOAT3 e = piece->GetTransform()->GetPosition();

			float vx = e.x - myPos.x;
			float vz = e.z - myPos.z;
			float lengthXZ = sqrtf(vx * vx + vz * vz);
			vx /= lengthXZ;
			vz /= lengthXZ;

			impulse.x = vx * power;
			impulse.y = 0;
			//impulse.y = power * 0.2f;
			impulse.z = vz * power;
			// TODO:db�l��implse�ɔ��f�����Ă���������(y���ɂ���΂�����)
			float db = Microphone::Instance().Sort();
			DirectX::XMStoreFloat3(&impulse, DirectX::XMVectorScale(DirectX::XMLoadFloat3(&impulse), db));

			piece->AddImpulse(impulse);

			//�����o����̈ʒu�ݒ�
			piece->GetTransform()->SetPosition(outPosition);
		}
	}

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
	if(!isGround_)this->velocity_.y += gravity_ * elapsedFrame;
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
	DirectX::XMFLOAT2 wall = { 12.0f,12.0f };	//	�����Ղ̓������ǂ����̔���
	float tyasituY = -18.5f;	//	�����̏���Y���W(����)

	//	�����Ղ̏ォ�ǂ���
	if ((-wall.x < position.x && position.x < wall.x) && (-wall.y < position.z && position.z < wall.y))
	{
		if (position.y <= ShogiBoard::Instance().GetTransform()->GetPosition().y)
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
	}
	else if (position.y <= tyasituY)	//	�����̏��ɂ�����
	{
		this->GetTransform()->SetPositionY(tyasituY);
		velocity_.y = 0.0f;

		//	���n����
		if (!isGround_)
		{
			OnLanding();
			PieceManager::Instance().SetRemainCount();	//	�����Ă����擾	
		}
		isGround_ = true;
	}
	else
	{
		isGround_ = false;
	}

	////	�������(��ɍs������~�܂�)
	//if (position.y > airPos_)
	//{
	//	this->GetTransform()->SetPositionY(airPos_);
	//	SetState(PIECE_STATE::STOP);	//	�����X�e�[�g�֐؂�ւ�
	//}
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

//////////////////////////////
//�X�e�[�g�֌W
/////////////////////////////

//	�X�e�[�g�Z�b�g
void Piece::SetState(PIECE_STATE pieceState)
{
	pieceState_ = pieceState;
}

//	�ҋ@�X�e�[�g�֑J��
void Piece::TransitionIdleState()
{
	pieceState_ = PIECE_STATE::IDLE;
}

//	�ҋ@�X�e�[�g�X�V����
void Piece:: UpdateIdleState(float elapsedTime)
{
	this->velocity_ = { 0,0,0 };

	SetState(PIECE_STATE::UP);
}

//	�㏸�X�e�[�g�֑J��
void Piece::TransitionUpState()
{
	pieceState_ = PIECE_STATE::UP;
}

//	�㏸�X�e�[�g�X�V����
void Piece::UpdateUpState(float elapsedTime,int index)
{
	if (!this->pieceInfo_[index].isEnemy_)	//	TODO:�����̋�Ȃ瑊��̋�ɐ�����Ԃ悤�ɂ���
	{
		this->Up(upSpeed);	//Up�֐��̒���Thrust�ւ̑J�ڂ����Ă�
	}

}

//	�����X�e�[�g�֑J��
void Piece::TransitionStopState() 
{
	pieceState_ = PIECE_STATE::STOP;
}

//	�����X�e�[�g�X�V����
void Piece::UpdateStopState(float elapsedTime) 
{
	this->velocity_ = { 0,0,0 };
	SetState(PIECE_STATE::THRUST);
}

//	�ˌ��X�e�[�g�֑J��
void Piece::TransitionThrustState()
{
	pieceState_ = PIECE_STATE::THRUST;
}

//	�ˌ��X�e�[�g�X�V����
void Piece::UpdateThrustState(float elapsedTime,int index)
{
	if (!this->pieceInfo_[index].isEnemy_)	//	TODO:�����̋�Ȃ瑊��̋�ɐ�����Ԃ悤�ɂ���
	{
		if (Microphone::Instance().ThreadStoped()) // �^���I��������
		{
			this->MoveToTarget();
		}
	}

}

//	������΂����X�e�[�g�J��
void Piece::TransitionBlownState()
{
	pieceState_ = PIECE_STATE::BLOWN_AWAY;
}

//	������΂����X�e�[�g�X�V
void Piece::UpdateBlownState(float elapsedTime, int index)
{

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
	case PIECE_STATE::IDLE:
		pieceStateStr_ = u8"IDLE";
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