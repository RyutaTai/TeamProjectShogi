#include "ShogiBoard.h"

#include "../Graphics/Graphics.h"

//	�R���X�g���N�^
ShogiBoard::ShogiBoard(const char* fileName, bool triangulate, bool usedAsCollider)
	: GameObject(fileName, triangulate, usedAsCollider)
{
	GetTransform()->SetPosition(DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f));
	GetTransform()->SetScale(DirectX::XMFLOAT3(1.0f, 1.0f, 1.0f));
	GetTransform()->SetRotation(DirectX::XMFLOAT4(0.0f, DirectX::XMConvertToRadians(0), 0.0f, 0.0f));

}

//	������	PieceManager��Initialize()�̒��ŌĂ�
void ShogiBoard::Initialize(int index)
{
	RegisterBoard(index);
}

//	DirectionInfo�̕����ɋ󂢂Ă���}�X�����邩���ׂ�
DirectX::XMFLOAT2 ShogiBoard::Serch(int index)
{
	Piece* piece = PieceManager::Instance().GetPiece(index);				//	��擾
	Piece::PIECE_TYPE pieceType = piece->GetPieceInfo(index).pieceType_;	//	��̎��
	DirectX::XMFLOAT2 movablePos[Piece::PIECE_DIRECTION_MAX + 1] = {};		//	������}�X���X�g�b�N �����Ȃ��ꍇ{0,0}������
	for (int i = 0; i < Piece::PIECE_DIRECTION_MAX; i++)
	{
		//	�����}�X���w�肵��IsEmpty()���Ă�
		//	������}�X��S���`�F�b�N�������B
		float directionX = piece->GetPieceInfo(index).direction_[i].directionX_;	//	�������x���� �z��ɂȂ邩��
		float directionY = piece->GetPieceInfo(index).direction_[i].directionY_;	//	�������y����
		//	����������������󂢂Ă�����
		if (IsEmpty(directionX, directionY))
		{
			return movablePos[i] = { directionX,directionY };
		}
	}
	
	return movablePos[8];
}

//	�w�肵���}�X���󂢂Ă��邩���ׂ�
bool ShogiBoard::IsEmpty(int directionX, int directionY)
{
	if (board_[directionX][directionY] == static_cast<int>(SQUARE_STATE::EMPTY))	//	EMPTY�Ȃ�true��Ԃ��@�������ǂ����悤
	{
		return true;
	}
	return false;
}

//	 Board�̔z��ɋ��o�^
void ShogiBoard::RegisterBoard(int index)
{
	Piece * piece = PieceManager::Instance().GetPiece(index);
	int posX, posY;
	posX = piece->GetPieceInfo(index).posX_;
	posY = piece->GetPieceInfo(index).posY_;
	board_[posX][posY] = static_cast<int>(SQUARE_STATE::EXIST);	//	���݂��Ă��邱�Ƃ�o�^

}

//	 Board�̔z�񂩂����폜
void ShogiBoard::RemoveFromBoard(int index)
{
	Piece* piece = PieceManager::Instance().GetPiece(index);
	int posX, posY;
	posX = piece->GetPieceInfo(index).posX_;
	posY = piece->GetPieceInfo(index).posY_;
	board_[posX][posY] = static_cast<int>(SQUARE_STATE::EMPTY);	//	�}�X���󂢂Ă����Ԃɂ���

}

//�f�X�g���N�^
ShogiBoard::~ShogiBoard()
{

}

//	�`�揈��
void ShogiBoard::Render()
{
	GameObject::Render(1.0f);
}

//	�f�o�b�O�`��
void ShogiBoard::DrawDebug()
{
	GetTransform()->DrawDebug();
}
