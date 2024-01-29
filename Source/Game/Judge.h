#pragma once

#include "../Game/Player.h"
#include "../Game/Enemy.h"
#include "../Game/Piece.h"
#include "../Game/PieceManager.h"
#include "../Game/ShogiBoard.h"
#include "../Graphics/Camera.h"

class Judge
{
public:
	Judge(){}
	~Judge(){}

	static Judge& Instance()
	{
		static Judge instance_;
		return instance_;
	}

	void FoulMoveCheck();		//	TODO:�ւ���`�F�b�N(�Q���Ƃ�) foul move : �ւ���
	void AreaCheck();			//	TODO:�G���A�`�F�b�N(�u����ꏊ��9x9�̒��ɂ��邩�A�G�w3�}�X�ȓ��ɓ�������)
	void ChangeTurn();			//	TODO:�^�[���؂�ւ� (Player,Enemy,�}�C�N���͂̂R�H)
	void PieceOverlapCheck();	//	TODO:��d�Ȃ��Ă��Ȃ����`�F�b�N

	void SetDuringChoice(bool choice) { duringChoice_ = choice; }	//	�I�𒆃t���O�Z�b�g
	bool GetDuringChoice()				{ return duringChoice_; }	//	�I�𒆂��ǂ���

private:
	//�Q�[���p�ϐ�
	bool	isMyTurn_ = true;		//	�����̃^�[�����ǂ���
	float	allottedTime = 30.0f;	//	�e�v���C���[�̈�育�Ƃ̎�������
	Player	player_;				//	�v���C���[
	Enemy	enemy_;					//	����
	bool	duringChoice_ = false;	//	��I�𒆂Ȃ�true

};

