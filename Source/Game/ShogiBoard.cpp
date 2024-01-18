#include "ShogiBoard.h"

#include "../Graphics/Graphics.h"

//	�R���X�g���N�^
ShogiBoard::ShogiBoard(const char* filename, bool triangulate)
	: GameObject(filename, triangulate)
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
void ShogiBoard::Serch(int index)
{
	Piece* piece = PieceManager::Instance().GetPiece(index);
	

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

//	�w�肵���}�X���󂢂Ă��邩���ׂ�
bool ShogiBoard::IsEmpty(float x, float y)
{
	for (int x = 0; x < boradX_; x++)
	{
		for (int y = 0; y < boardY_; y++)
		{
			
		}
	}
	return false;
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
