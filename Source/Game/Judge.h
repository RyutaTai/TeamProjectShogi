#pragma once

//#include "../Game/Player.h"
//#include "../Game/Enemy.h"
#include "../Game/Piece.h"
#include "../Game/PieceManager.h"
//#include "../Game/ShogiBoard.h"
#include "../Graphics/Camera.h"

class Judge
{
public:
	enum GAME_STATE	//	�Q�[���̏��
	{
		TUTORIAL = 0, 	//	�`���[�g���A��
		START,			//	�`���[�g���A���I����Ă����̃Q�[�����
		REC,			//	�^����
		END,			//	�Q�[���I��
		MAX,			//	�X�e�[�g�ő吔
	};
	
public:
	Judge(){}
	~Judge(){}

	static Judge& Instance()
	{
		static Judge instance_;
		return instance_;
	}

	//void FoulMoveCheck();		//	TODO:�ւ���`�F�b�N(�Q���Ƃ�) foul move : �ւ���
	//void AreaCheck();			//	TODO:�G���A�`�F�b�N(�u����ꏊ��9x9�̒��ɂ��邩�A�G�w3�}�X�ȓ��ɓ�������)
	//void ChangeTurn();			//	TODO:�^�[���؂�ւ� (Player,Enemy,�}�C�N���͂̂R�H)
	//void PieceOverlapCheck();	//	TODO:��d�Ȃ��Ă��Ȃ����`�F�b�N

	void SetDuringChoice(bool choice) { duringChoice_ = choice; }	//	�I�𒆃t���O�Z�b�g
	bool GetDuringChoice()				{ return duringChoice_; }	//	�I�𒆂��ǂ���
	void SetGameState(GAME_STATE gameState);						//	�Q�[���X�e�[�g�ݒ�
	void ResetGameState() { gameState_ = {}; }						//	�Q�[���X�e�[�g���Z�b�g

	GAME_STATE GetGameState() { return gameState_; }

	//�Q�[���p�ϐ�
private:
	GAME_STATE gameState_ = {};

private:
	//	���ʂ̏���
	//bool	isMyTurn_ = true;		//	�����̃^�[�����ǂ���
	//float	allottedTime = 30.0f;	//	�e�v���C���[�̈�育�Ƃ̎�������
	//Player	player_;				//	�v���C���[
	//Enemy	enemy_;					//	����
	bool	duringChoice_ = false;	//	��I�𒆂Ȃ�true

};

