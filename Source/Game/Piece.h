#pragma once

#include "GameObject.h"

//	�����̋�N���X
class Piece :public GameObject
{
private:	
	//	�\���̂Ƃ�
	enum class PIECE_TYPE		//	��̎�ނ�錾����
	{
		HUHYO,					//	����
		TOKIN,					//	�Ƌ��i�����������j
		KYOUSHA,				//	����
		NARIKYO,				//	�����i���������ԁj
		KEIMA,					//	�j�n
		NARIKEI,				//	���j�i�������j�n�j
		GINSHO,					//	�⏫
		NARIGIN,				//	����i�������⏫�j
		HISHA,					//	���
		RYUO,					//	�����i��������ԁj
		KAKUGYO,				//	�p�s
		RYUMA,					//	���n�i�������p�s�j
		KINSHO,					//	����
		OUSHO,					//	����
		GYOKUSHO,				//	�ʏ�	����̉�
	};

	//	��̐i�s������
	enum class DIRECTION_NAME		
	{
		BACK_LEFT,			//	����
		BAXK,				//	��
		BACK_RIGHT,			//	�E��
		LEFT,				//	��
		RIGHT,				//	�E
		UP_LEFT,			//	����
		UP,					//	��
		UP_RIGHT,			//	�E��
		MY_KEIMA_RIGHT,		//	�����̌j�n�E����
		MY_KEIMA_LEFT,		//	�����̌j�n�E����
		ENEMY_KEIMA_RIGHT,	//	�G�̌j�n�E����
		ENEMY_KEIMA_LEFT,	//	�G�̌j�n�E����
	};

	//	��̕����̏��
	struct DirectionInfo
	{
		DIRECTION_NAME name_;				//	�����̖��O
		float directionX_;					//	�����������x
		float directionY_;					//	�����������y
	};

	//	��̏��
	struct PieceInfo			
	{
		int posX_;						//	���x���W ���W��9x9�}�X�̒��ŕ\�L����
		int posY_;						//	���y���W
		PIECE_TYPE pieceType_;			//	��̎��
		bool isEnemy_;					//	�G�̋�A�����̋ �G�Ȃ�true
		bool isDead_;					//	��ɂ��邩�Ȃ���
		DirectionInfo direction_;		//	��̕�����������(�����̖��O�A������}�X�������Ă�)
	};

public:
	//	�\���̂Ƃ�
	static const int PIECE_MAX = 40;		//	��̍ő吔
	static const int DIRECTION_MAX = 12;	//	��̕����̍ő吔
	static const int PIECE_TYPE_MAX = 15;	//	��̎�ނ̍ő吔(�ʏ����܂�ł�)
	//	����������
	DirectionInfo	directionInfo_[DIRECTION_MAX] =
	{
		{DIRECTION_NAME::BACK_LEFT,		-1.0f,	-1.0f},		//	����
		{DIRECTION_NAME::BAXK,			 0.0f,	-1.0f},		//	��
		{DIRECTION_NAME::BACK_RIGHT,	+1.0f,	-1.0f},		//	�E��
		{DIRECTION_NAME::LEFT,			-1.0f,	 0.0f},		//	��
		{DIRECTION_NAME::RIGHT,			+1.0f,	 0.0f},		//	�E
		{DIRECTION_NAME::BACK_LEFT,		-1.0f,	+1.0f},		//	����
		{DIRECTION_NAME::BACK_LEFT,		 0.0f,	+1.0f},		//	��
		{DIRECTION_NAME::BACK_LEFT,		+1.0f,	+1.0f},		//	�E��
		{DIRECTION_NAME::BACK_LEFT,		+2.0f,	+1.0f},		//	�����̌j�n�E����
		{DIRECTION_NAME::BACK_LEFT,		+2.0f,	+1.0f},		//	�����̌j�n�E����
		{DIRECTION_NAME::BACK_LEFT,		+2.0f,	-1.0f},		//	�G�̌j�n�E����
		{DIRECTION_NAME::BACK_LEFT,		-2.0f,	-1.0f},		//	�G�̌j�n�E����
	}
	;
	//	��̏������W
	PieceInfo pieceInfo_[PIECE_MAX] =
	{
		{1,3,PIECE_TYPE::HUHYO,		true,	true},		//	�G����
		{2,3,PIECE_TYPE::HUHYO,		true,	true},
		{3,3,PIECE_TYPE::HUHYO,		true,	true},
		{4,3,PIECE_TYPE::HUHYO,		true,	true},
		{5,3,PIECE_TYPE::HUHYO,		true,	true},
		{6,3,PIECE_TYPE::HUHYO,		true,	true},
		{7,3,PIECE_TYPE::HUHYO,		true,	true},
		{8,3,PIECE_TYPE::HUHYO,		true,	true},
		{9,3,PIECE_TYPE::HUHYO,		true,	true},	
		{1,7,PIECE_TYPE::HUHYO,		false,	true},		//	��������
		{2,7,PIECE_TYPE::HUHYO,		false,	true},
		{3,7,PIECE_TYPE::HUHYO,		false,	true},
		{4,7,PIECE_TYPE::HUHYO,		false,	true},
		{5,7,PIECE_TYPE::HUHYO,		false,	true},
		{6,7,PIECE_TYPE::HUHYO,		false,	true},
		{7,7,PIECE_TYPE::HUHYO,		false,	true},
		{8,7,PIECE_TYPE::HUHYO,		false,	true},
		{9,7,PIECE_TYPE::HUHYO,		false,	true},
		{8,2,PIECE_TYPE::KAKUGYO,	true,	true},		//	�G�p�s
		{8,8,PIECE_TYPE::KAKUGYO,	false,	true},		//	�����p�s
		{2,2,PIECE_TYPE::HISHA,		true,	true},		//	�G���
		{2,8,PIECE_TYPE::HISHA,		false,	true},		//	�������
		{1,1,PIECE_TYPE::KYOUSHA,	true,	true},		//	�G����
		{9,1,PIECE_TYPE::KYOUSHA,	true,	true},
		{1,9,PIECE_TYPE::KYOUSHA,	false,	true},		//	��������
		{9,9,PIECE_TYPE::KYOUSHA,	false,	true},
		{2,1,PIECE_TYPE::KEIMA,		true,	true},		//	�G�j�n
		{8,1,PIECE_TYPE::KEIMA,		true,	true},
		{2,9,PIECE_TYPE::KEIMA,		false,	true},		//	�����j�n
		{8,9,PIECE_TYPE::KEIMA,		false,	true},
		{3,1,PIECE_TYPE::GINSHO,	true,	true},		//	�G�⏫
		{7,1,PIECE_TYPE::GINSHO,	true,	true},
		{3,9,PIECE_TYPE::GINSHO,	false,	true},		//	�����⏫
		{7,9,PIECE_TYPE::GINSHO,	false,	true},
		{4,1,PIECE_TYPE::KINSHO,	true,	true},		//	�G����
		{6,1,PIECE_TYPE::KINSHO,	true,	true},
		{4,9,PIECE_TYPE::KINSHO,	false,	true},		//	��������
		{6,9,PIECE_TYPE::KINSHO,	false,	true},
		{5,1,PIECE_TYPE::GYOKUSHO,	true,	true},		//	�ʏ�
		{5,9,PIECE_TYPE::OUSHO,		false,	true},		//	����

	};

public:
	Piece(const char* filename, bool triangulate = false);		//	�R���X�g���N�^
	~Piece();													//	�f�X�g���N�^

	void Initialize(int index);									//	�������@�ʒu�ݒ�Ƃ�
	void Update(float elapsedTime);								//	�X�V����
	void Render();												//	�`�揈��

	void Serch(int index);										//	�󂢂Ă���}�X�����邩�ǂ������ׂ�
	void Destroy();												//	�j������

	void DrawDebug();											//	�f�o�b�O�`��
	void SetDebugStr();											//	��̎�ނ�\���ł���悤typeStr_��pieceType_���Z�b�g

	PieceInfo GetPieceInfo(int index) { return this->pieceInfo_[index]; }	//	�����̋�f�[�^�擾	

private:
	static const int boradX_ = 9;								//	�}�X��x��
	static const int boardY_ = 9;								//	�}�X��y��
	static const int board_[boradX_][boardY_];					//	�����Ղ̃f�[�^ 9x9
	DirectX::XMFLOAT3 pieceOffset_ = { -5.0f, 0.0f, -5.0f };	//	����ŏ��ɕ`�悷��Ƃ��̃I�t�Z�b�g�l(�␳�l)
	float range_ = 2.4f;										//	��Ƌ�̊Ԋu���ǂꂭ�炢�󂯂邩

private:	//�f�o�b�O�p
	static int num;				//	�����̋�̗v�f�ԍ�
	int myNum_ = 0;				//	�����̋�̗v�f�ԍ�
	std::string typeStr_ = "";	//	��̎��

};

