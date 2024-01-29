#pragma once

#include <set>

#include "../Game/Piece.h"

//	�����̋�Ǘ��N���X
class PieceManager
{
private:
	PieceManager() {}
	~PieceManager() {}
public:
	//	�B��̃C���X�^���X�擾
	static PieceManager& Instance()
	{
		static PieceManager instance_;
		return instance_;
	}

	void Initialize();				//	������
	void Update(float elapsedTime,float gameIntervalTimer);	//	�X�V����
	void Render();					//	�`�揈��
	void DrawDebug();				//	�f�o�b�O�`��

	void Register(Piece* piece);	//	���o�^
	void Clear();					//	���S�č폜
	void Remove(Piece* piece);		//	����폜

	void Move(int index, int x, int y);	//	��ړ�

	void	SetChoicePiece(int index);	//	�I������Ă����Z�b�g	
	void	RemoveChoicePiece();		//	�I������Ă����Z�b�g	
	Piece*	GetChoicePiece()	{ return choicePiece_; }	//	�I������Ă����擾
	int		GetChoicePieceIndex() { return choiceIndex_; }	//	�I������Ă����̃C���f�b�N�X�擾
	int		GetPieceCount() const { return static_cast<int>(pieces_.size()); }	//	���݂̋�̐��擾
	Piece*	GetPiece(int index) { return pieces_.at(index); }					//	����擾

private:
	std::vector<Piece*> pieces_;	//	��̔z��
	std::set<Piece*> removes_;		//	�j�����X�g
	Piece* choicePiece_ = nullptr;	//	���ݑI������Ă����
	int choiceIndex_;				//	���ݑI������Ă����̃C���f�b�N�X �g�ݕ��̃~�X�ŕK�v�ɂȂ����B���Ԃ���ΏC������B

	static const int PUSH_MAX = 1;	//	�X�y�[�X�L�[���͎�t��
	int pushCount_ = 0;
	int pieceCount_ = 0;			//	���݂̋�̐�
	bool blowAway_ = false;			//	������΂��t���O?

};

