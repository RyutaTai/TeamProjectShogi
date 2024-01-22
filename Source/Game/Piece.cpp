#include "Piece.h"

#include "PieceManager.h"
#include "Stage.h"

int Piece::num = 0;	//	�f�o�b�O�p

//	�R���X�g���N�^
Piece::Piece(const char* fileName, bool triangulate, bool usedAsCollider)
	:GameObject(fileName, triangulate, usedAsCollider)
{
	myNum_ = num++;	//	�f�o�b�O�p
}

Piece::~Piece()
{
}

//	������
void Piece::Initialize(int index)
{
	//	��̍��W = (������(9x9�}�X)��ł̍��W + pieceOffset) * range_
	this->GetTransform()->SetPositionX((static_cast<float>(pieceInfo_[index].posX_) + pieceOffset_.x) * range_);
	this->GetTransform()->SetPositionY(Stage::Instance().GetTransform()->GetPosition().y);	//�����Ղƍ������킹�邽�ߕ␳�Ƃ����Ȃ�
	this->GetTransform()->SetPositionZ((static_cast<float>(pieceInfo_[index].posY_) + pieceOffset_.z) * range_);

	//	�G�̂Ƃ��������f���̌����𔽓]������
	if (pieceInfo_[index].isEnemy_)GetTransform()->SetRotationY(DirectX::XMConvertToRadians(180.0f));
}

//	��̕����o�^(pieceInfo_�ɓo�^)
void Piece::SetPieceDirection(int index)
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
void Piece::Update(float elapsedTime)
{

}

//	�j��
void Piece::Destroy()
{
	PieceManager::Instance().Remove(this);
}

//	�I���t���O�Z�b�g
void Piece::SetPieceChoise(bool choise)
{
	this->pieceInfo_->isChoise_ = choise;
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

	switch (this->GetPieceInfo(this->myNum_).isChoise_)
	{
	case true:
		choiseStr_ = u8"�I������Ă���";
		break;
	case false:
		choiseStr_ = u8"�I������Ă��Ȃ�";
		break;
	}
}

//	�f�o�b�O�`��
void Piece::DrawDebug()
{
	//	��̗v�f�ԍ� ���ڂ̋
	std::string n = "piace" + std::to_string(myNum_);
	SetDebugStr();

	if (ImGui::TreeNode(n.c_str()))	//	��̗v�f�ԍ�
	{
		ImGui::Text(u8"State�@%s", typeStr_.c_str());		//	��̎��
		ImGui::Text(u8"IsChoise�@%s", choiseStr_.c_str());	//	��I������Ă��邩
		GetTransform()->DrawDebug();
		ImGui::TreePop();
	}
}