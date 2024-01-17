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
	std::string n = "piace" + std::to_string(myNum_);
	if (ImGui::TreeNode(n.c_str()))
	{
		GetTransform()->DrawDebug();
		ImGui::TreePop();
	}
}
