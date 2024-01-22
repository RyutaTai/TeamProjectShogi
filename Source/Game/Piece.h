#pragma once

#include "GameObject.h"

//	�����̋�N���X
class Piece :public GameObject
{
public:	
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
		BACK_LEFT,			//	�����
		BACK,				//	���
		BACK_RIGHT,			//	�E���
		LEFT,				//	��
		RIGHT,				//	�E
		FRONT_LEFT,			//	���O
		FRONT,				//	�O
		FRONT_RIGHT,		//	�E�O
		KEIMA_RIGHT,		//	�����̌j�n�E����
		KEIMA_LEFT,			//	�����̌j�n�E����
		NONE,				//	�����Ȃ�
	};

	//	��̕����̏��
	struct DirectionInfo
	{
		DIRECTION_NAME name_;				//	�����̖��O
		float directionX_;					//	�����������x
		float directionY_;					//	�����������y
	};

	static const int PIECE_DIRECTION_MAX = 8;	//	�P�̋���Ă��̕����̍ő吔
	static const int DIRECTION_MAX = 12;		//	��̕����̍ő吔
	//	��̏��
	struct PieceInfo			
	{
		int posX_;						//	���x���W ���W��9x9�}�X�̒��ŕ\�L����
		int posY_;						//	���y���W
		PIECE_TYPE pieceType_;			//	��̎��
		bool isEnemy_;					//	�G�̋�A�����̋ �G�Ȃ�true
		bool isDead_;					//	��ɂ��邩�Ȃ���
		bool isChoise_;					//	�I������Ă��邩
		DirectionInfo direction_[PIECE_DIRECTION_MAX];		//	��̕�����������(�����̖��O�A������}�X�������Ă�) �܂��֘A�t�����ĂȂ�
	};

	static const int PIECE_MAX = 40;		//	��̍ő吔
	static const int PIECE_TYPE_MAX = 16;	//	��̎�ނ̍ő吔(�ʏ����܂�ł�)
	//	����������
	DirectionInfo	directionInfo_[DIRECTION_MAX] =
	{
		{DIRECTION_NAME::BACK_LEFT,		-1.0f,	-1.0f},		//	�����
		{DIRECTION_NAME::BACK,			 0.0f,	-1.0f},		//	���
		{DIRECTION_NAME::BACK_RIGHT,	+1.0f,	-1.0f},		//	�E���
		{DIRECTION_NAME::LEFT,			-1.0f,	 0.0f},		//	��
		{DIRECTION_NAME::RIGHT,			+1.0f,	 0.0f},		//	�E
		{DIRECTION_NAME::FRONT_LEFT,	-1.0f,	+1.0f},		//	���O
		{DIRECTION_NAME::FRONT,			 0.0f,	+1.0f},		//	�O
		{DIRECTION_NAME::FRONT_RIGHT,	+1.0f,	+1.0f},		//	�E�O
		{DIRECTION_NAME::KEIMA_RIGHT,	+2.0f,	+1.0f},		//	�j�n�E����
		{DIRECTION_NAME::KEIMA_LEFT,	+2.0f,	+1.0f},		//	�j�n������
		{DIRECTION_NAME::NONE,			 0.0f,   0.0f},		//	�����Ȃ�
	};
	
	//	��̏������W
	PieceInfo pieceInfo_[PIECE_MAX] =
	{
		{1,3,PIECE_TYPE::HUHYO,		true,	true,	false},		//	�G����
		{2,3,PIECE_TYPE::HUHYO,		true,	true,	false},
		{3,3,PIECE_TYPE::HUHYO,		true,	true,	false},
		{4,3,PIECE_TYPE::HUHYO,		true,	true,	false},
		{5,3,PIECE_TYPE::HUHYO,		true,	true,	false},
		{6,3,PIECE_TYPE::HUHYO,		true,	true,	false},
		{7,3,PIECE_TYPE::HUHYO,		true,	true,	false},
		{8,3,PIECE_TYPE::HUHYO,		true,	true,	false},
		{9,3,PIECE_TYPE::HUHYO,		true,	true,	false},	
		{1,7,PIECE_TYPE::HUHYO,		false,	true,	false},		//	��������
		{2,7,PIECE_TYPE::HUHYO,		false,	true,	false},
		{3,7,PIECE_TYPE::HUHYO,		false,	true,	false},
		{4,7,PIECE_TYPE::HUHYO,		false,	true,	false},
		{5,7,PIECE_TYPE::HUHYO,		false,	true,	false},
		{6,7,PIECE_TYPE::HUHYO,		false,	true,	false},
		{7,7,PIECE_TYPE::HUHYO,		false,	true,	false},
		{8,7,PIECE_TYPE::HUHYO,		false,	true,	false},
		{9,7,PIECE_TYPE::HUHYO,		false,	true,	false},
		{8,2,PIECE_TYPE::KAKUGYO,	true,	true,	false},		//	�G�p�s
		{8,8,PIECE_TYPE::KAKUGYO,	false,	true,	false},		//	�����p�s
		{2,2,PIECE_TYPE::HISHA,		true,	true,	false},		//	�G���
		{2,8,PIECE_TYPE::HISHA,		false,	true,	false},		//	�������
		{1,1,PIECE_TYPE::KYOUSHA,	true,	true,	false},		//	�G����
		{9,1,PIECE_TYPE::KYOUSHA,	true,	true,	false},
		{1,9,PIECE_TYPE::KYOUSHA,	false,	true,	false},		//	��������
		{9,9,PIECE_TYPE::KYOUSHA,	false,	true,	false},
		{2,1,PIECE_TYPE::KEIMA,		true,	true,	false},		//	�G�j�n
		{8,1,PIECE_TYPE::KEIMA,		true,	true,	false},
		{2,9,PIECE_TYPE::KEIMA,		false,	true,	false},		//	�����j�n
		{8,9,PIECE_TYPE::KEIMA,		false,	true,	false},
		{3,1,PIECE_TYPE::GINSHO,	true,	true,	false},		//	�G�⏫
		{7,1,PIECE_TYPE::GINSHO,	true,	true,	false},
		{3,9,PIECE_TYPE::GINSHO,	false,	true,	false},		//	�����⏫
		{7,9,PIECE_TYPE::GINSHO,	false,	true,	false},
		{4,1,PIECE_TYPE::KINSHO,	true,	true,	false},		//	�G����
		{6,1,PIECE_TYPE::KINSHO,	true,	true,	false},
		{4,9,PIECE_TYPE::KINSHO,	false,	true,	false},		//	��������
		{6,9,PIECE_TYPE::KINSHO,	false,	true,	false},
		{5,1,PIECE_TYPE::GYOKUSHO,	true,	true,	false},		//	�ʏ�
		{5,9,PIECE_TYPE::OUSHO,		false,	true,	false},		//	����

	};

public:
	Piece(const char* fileName, bool triangulate = false, bool usedAsCollider = false);	//	�R���X�g���N�^
	~Piece();													//	�f�X�g���N�^

	void Initialize(int index);									//	�������@�@�ʒu�ݒ�Ƃ�
	void Update(float elapsedTime);								//	�X�V����
	void Render();												//	�`�揈��

	void Destroy();												//	�j������

	void SetPieceChoise(bool choise);										//	�I���t���O�Z�b�g
	void SetPieceDirection(int index);										//	��̕���direction_����̏��pieceInfo_�ɓo�^
	PieceInfo GetPieceInfo(int index) { return this->pieceInfo_[index]; }	//	�����̋�f�[�^�擾	

	//	�f�o�b�O�p
	void DrawDebug();											//	�f�o�b�O�`��
	void SetDebugStr();											//	��̎�ނ�\���ł���悤typeStr_��pieceType_���Z�b�g

private:
	DirectX::XMFLOAT3 pieceOffset_ = { -5.0f, 0.0f, -5.0f };	//	����ŏ��ɕ`�悷��Ƃ��̃I�t�Z�b�g�l(�␳�l)
	float range_ = 2.4f;										//	��Ƌ�̊Ԋu���ǂꂭ�炢�󂯂邩

private:	//�f�o�b�O�p
	static int num;					//	�����̋�̗v�f�ԍ�
	int myNum_ = 0;					//	�����̋�̗v�f�ԍ�
	std::string typeStr_ = "";		//	��̎��
	std::string choiseStr_ = "";	//	�I������Ă��邩

};

