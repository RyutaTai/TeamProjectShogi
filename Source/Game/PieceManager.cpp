#include "PieceManager.h"

#include "../Input/GamePad.h"
#include "../Input/Input.h"
#include "../Game/ShogiBoard.h"

//	������
void PieceManager::Initialize()
{
	for (Piece* piece : pieces_)
	{
		piece->Initialize(pieceCount_);
		ShogiBoard::Instance().Initialize(pieceCount_);	//	������(board_)�ɋ��o�^
		pieceCount_ += 1;		//	��̐����J�E���g
	}
	blowAway_ = false;
	pushCount_ = 0;
}

//	�X�V����
void PieceManager::Update(float elapsedTime, float gameIntervalTimer)
{
	//	��̍X�V����

	
	//	�����̋�̐�����΂�����
	GamePad& gamePad = Input::Instance().GetGamePad();
	if ((gamePad.GetButtonDown() & GamePad::BTN_SPACE) && gameIntervalTimer == 0
		&& (pushCount_<PUSH_MAX))	//	�X�y�[�X�L�[
	{
		blowAway_ = true;
		int index = 0;
		for (Piece* piece : pieces_)
		{
			piece->SetState(Piece::PIECE_STATE::IDLE);	//	�㏸�X�e�[�g�֐؂�ւ�
			index += 1;
		}
		pushCount_++;
	}

	if (blowAway_)
	{
		int index = 0;
		for (Piece* piece : pieces_)
		{
			piece->Update(elapsedTime, index);
			index += 1;
		}
	}

	//	�j������
	for (Piece* piece : removes_)
	{
		std::vector<Piece*>::iterator it =
			std::find(pieces_.begin(), pieces_.end(), piece);
		if (it != pieces_.end())
		{
			pieces_.erase(it);
		}
		delete piece;
	}
	//	�j�����X�g���N���A
	removes_.clear();
}

//	���o�^
void PieceManager::Register(Piece* piece)
{
	pieces_.emplace_back(piece);
}

//	���S�č폜
void PieceManager::Clear()
{
	for (Piece* piece : pieces_)
	{
		delete piece;
	}
	pieces_.clear();
}

//	����폜
void PieceManager::Remove(Piece* piece)
{
	removes_.insert(piece);	//	�j�����X�g�ɒǉ�
}

//	��ړ�
void PieceManager::Move(int index, int x, int y)
{
	pieces_.at(index)->Move(index, x, y);				//	Piece�N���X��Move�Ă�
	pieces_.at(index)->pieceInfo_->isChoice_ = false;	//	�I���t���Ofalse
	RemoveChoicePiece();								//	�I������Ă�����nullptr�ɂ���
	Judge::Instance().SetDuringChoice(false);			//	�I�𒆃t���Ofalse
}

// �I������Ă����Z�b�g
void PieceManager::SetChoicePiece(int index)
{
	choicePiece_= pieces_.at(index);	//	�I������Ă������Z�b�g
	choiceIndex_ = index;				//	�I������Ă����̃C���f�b�N�X���Z�b�g
	pieces_.at(index)->pieceInfo_->isChoice_ = !pieces_.at(index)->pieceInfo_->isChoice_;	//	�I���t���O���]
}

//	�I������Ă����Z�b�g
void PieceManager::RemoveChoicePiece()
{
	choicePiece_ = nullptr;				//	�I������Ă����Z�b�g
}

//	�`�揈��
void PieceManager::Render()
{
	for (Piece* piece : pieces_)
	{
		piece->Render();
	}
}

//	�f�o�b�O�`��
void PieceManager::DrawDebug()
{
	for (Piece* piece : pieces_)
	{
		piece->DrawDebug();
	}
}


