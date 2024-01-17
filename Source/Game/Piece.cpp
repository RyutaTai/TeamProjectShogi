#include "Piece.h"

#include "PieceManager.h"
#include "Stage.h"

int Piece::num = 0;	//	�f�o�b�O�p

//	�R���X�g���N�^
Piece::Piece(const char* filename, bool triangulate)
	:GameObject(filename, triangulate)
{
	myNum_ = num++;	//	�f�o�b�O�p
}

//	������
void Piece::Initialize(int index)
{
	//	��̍��W = (������(9x9�}�X)��ł̍��W + pieceOffset) * range_

	GetTransform()->SetPositionX((pieceInfo_[index].posX_ + pieceOffset_.x) * range_);
	GetTransform()->SetPositionY(Stage::Instance().GetTransform()->GetPosition().y);	//�����Ղƍ������킹�邽�ߕ␳�Ƃ����Ȃ�
	GetTransform()->SetPositionZ((pieceInfo_[index].posY_ + pieceOffset_.z) * range_);

	//	�G�̂Ƃ��������f���̌����𔽓]������
	if (pieceInfo_[index].isEnemy_)GetTransform()->SetRotationY(DirectX::XMConvertToRadians(180));
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

//	�`�揈��
void Piece::Render()
{
	GameObject::Render(1.0f);
}

//	�f�o�b�O�`��
void Piece::DrawDebug()
{
	//	��̗v�f�ԍ� ���ڂ̋
	std::string n = "piace" + std::to_string(myNum_);	
	SetDebugStr();

	if (ImGui::TreeNode(n.c_str()))	//	��̗v�f�ԍ�
	{
		ImGui::Text(u8"State�@%s", typeStr_.c_str());	//	��̎��
		GetTransform()->DrawDebug();
		ImGui::TreePop();
	}
}

void Piece::SetDebugStr()
{
	//	��̎��
	switch (this->GetPieceInfo(this->myNum_).pieceType_) {
	case PIECE_TYPE::HUHYOU:
		typeStr_ = u8"����HUHYOU";
		break;
	case PIECE_TYPE::TOKIN:
		typeStr_ = u8"�Ƌ�TOKIN";
		break;
	case PIECE_TYPE::KYOUSHA:
		typeStr_ = u8"����KYOUSHA";
		break;
	case PIECE_TYPE::NARIKYOU:
		typeStr_ = u8"����NARIKYOU";
		break;
	case PIECE_TYPE::KEIMA:
		typeStr_ = u8"�j�nKEIMA";
		break;
	case PIECE_TYPE::NARIKEI:
		typeStr_ = u8"���jNARIKEI";
		break;
	case PIECE_TYPE::GINSHOU:
		typeStr_ = u8"�⏫GINSHOU";
		break;
	case PIECE_TYPE::NARIGIN:
		typeStr_ = u8"����NARIGIN";
		break;
	case PIECE_TYPE::HISHA:
		typeStr_ = u8"���HISHA";
		break;
	case PIECE_TYPE::RYUOU:
		typeStr_ = u8"����RYUOU";
		break;
	case PIECE_TYPE::KAKUGYOU:
		typeStr_ = u8"�p�sKAKUGYOU";
		break;
	case PIECE_TYPE::RYUMA:
		typeStr_ = u8"���nRYUMA";
		break;
	case PIECE_TYPE::KINSHOU:
		typeStr_ = u8"����KINSHOU";
		break;
	case PIECE_TYPE::OUSHOU:
		typeStr_ = u8"����OUSHOU";
		break;
	}
}
