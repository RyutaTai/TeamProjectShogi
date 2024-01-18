#pragma once

#include "GameObject.h"
#include "../Game/Piece.h"
#include "../Game/PieceManager.h"

class ShogiBoard : public GameObject
{
public:
	ShogiBoard(const char* filename, bool triangulate = false);
	ShogiBoard() {}
	~ShogiBoard();

	//	�B��̃C���X�^���X�擾
	static ShogiBoard& Instance()
	{
		static ShogiBoard instance_;
		return instance_;
	}

	void Initialize(int index);			//	������
	void Render();						//	�`�揈��
	void DrawDebug();					//	�f�o�b�O�`��

	void RegisterBoard(int index);		//	board_�ɋ��o�^����
	void Serch(int index);				//	index�Ԗڂ̋����������ɋ󂢂Ă���}�X�����邩�ǂ������ׂ�
	bool IsEmpty(float x, float y);		//	�w�肵���}�X���󂢂Ă��邩���ׂ�

private:
	enum class SQUARE_STATE	//	�}�X�̏��
	{
		EMPTY = 0,	//	�󂢂Ă���
		EXIST,		//	����݂��Ă���
	};

	//	�󂢂Ă���}�X����������Ƃ��Ɏg��
	static const int boradX_ = 9;						//	�}�X��x��
	static const int boardY_ = 9;						//	�}�X��y��
	int board_[boradX_][boardY_] = {};					//	�����Ղ̃f�[�^ 9x9

};