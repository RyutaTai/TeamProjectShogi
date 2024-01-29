#pragma once

#include "GameObject.h"

//	�����̋�N���X
class Piece :public GameObject
{
public:	//	���ʂ̏���	

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
		BACK_LEFT=0,			//	�����
		BACK,					//	���
		BACK_RIGHT,				//	�E���
		LEFT,					//	��
		RIGHT,					//	�E
		FRONT_LEFT,				//	���O
		FRONT,					//	�O
		FRONT_RIGHT,			//	�E�O
		KEIMA_RIGHT,			//	�����̌j�n�E����
		KEIMA_LEFT,				//	�����̌j�n�E����
		NONE,					//	�����Ȃ�
	};

	//	��̕����̏��
	struct DirectionInfo
	{
		DIRECTION_NAME name_;				//	�����̖��O
		float directionX_;					//	�����������x
		float directionY_;					//	�����������y
	};

	static const int PIECE_DIRECTION_MAX = 8;	//	�P�̋���Ă��̕����̍ő吔
	static const int DIRECTION_MAX = 11;		//	��̕����̍ő吔
	//	��̏��
	struct PieceInfo			
	{
		int posX_;						//	���x���W ���W��9x9�}�X�̒��ŕ\�L����
		int posY_;						//	���y���W
		PIECE_TYPE pieceType_;			//	��̎��
		bool isEnemy_;					//	�G�̋�A�����̋ �G�Ȃ�true
		bool isDead_;					//	��ɂ��邩�Ȃ���
		bool isChoice_;					//	�I������Ă��邩
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
		{DIRECTION_NAME::KEIMA_RIGHT,	+1.0f,	+2.0f},		//	�j�n�E����
		{DIRECTION_NAME::KEIMA_LEFT,	-1.0f,	+2.0f},		//	�j�n������
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

public:	//	������΂�����
	enum PIECE_STATE
	{
		IDLE = 0,		//	�ʏ�
		UP,				//	�㏸
		STOP,			//	����
		THRUST,			//	�˂�����
		BLOWN_AWAY,		//	������΂����
	};

public:
	Piece(const char* fileName, bool triangulate = false, bool usedAsCollider = false);	//	�R���X�g���N�^
	~Piece();													//	�f�X�g���N�^

	void Initialize(int index);									//	�������@�@�ʒu�ݒ�Ƃ�
	void Update(float elapsedTime,int index);					//	�X�V����
	void Render();												//	�`�揈��

	void Destroy();												//	�j������

	//	�f�o�b�O�p
	void DrawDebug();											//	�f�o�b�O�`��
	void SetDebugStr();											//	��̎�ނ�\���ł���悤typeStr_��pieceType_���Z�b�g
	void DrawDebugPrimitive();									//	�f�o�b�O�v���~�e�B�u�`��

public:	//	���ʂ̏���
	void Move(int index,int x, int y);										//	�ړ����� ���ʂ̏����ړ��p

	void SetChoicePiece(bool choice);										//	�I���t���O�Z�b�g
	void SetPieceDirection(int index);										//	��̕���direction_����̏��pieceInfo_�ɓo�^
	void PieceInfoUpdate(int index);										//	��f�[�^�X�V
	PieceInfo& GetPieceInfo(int index) { return this->pieceInfo_[index]; }	//	�����̋�f�[�^�擾	
	DirectX::XMFLOAT3 GetOffset() { return pieceOffset_; }					//	�����̋�I�t�Z�b�g�擾
	float GetRange() { return range_; }										//	�����̋�range�擾				
	DirectX::XMFLOAT3 GetImpulse() { return impulse_; }
	

public:	//	������΂�����
	void Move(int index);										//	�ړ�����(������΂�)
	void MoveToTarget();										//	�^�[�Q�b�g�Ɍ������Ĕ��
	void AddImpulse(const DirectX::XMFLOAT3& impulse);			//	�Ռ���^����
	void Up(float speed);										//	�㏸����
	void UpdateVelocity(float elapsedTime);						//	���͏����X�V
	void UpdateHorizontalVelocity(float elapsedFrame);			//	�������͍X�V����
	void UpdateHorizontalMove(float elapsedTime);				//	�����ړ��X�V����	
	void UpdateVerticalVelocity(float elapsedFrame);			//	�������͍X�V����
	void UpdateVerticalMove(float elapsedTime);					//	�����ړ��X�V����
	virtual void OnLanding() {}									//	���n�����Ƃ��ɌĂ΂��

	//	�X�e�[�g�֌W
	void SetState(PIECE_STATE state);							//	�X�e�[�g�Z�b�g
	PIECE_STATE GetState() { return pieceState_; }				//	�X�e�[�g�擾
	void TransitionIdleState();									//	�ҋ@�X�e�[�g�֑J��
	void UpdateIdleState(float elapsedTime);					//	�ҋ@�X�e�[�g�X�V����
	void TransitionUpState();									//	�㏸�X�e�[�g�֑J��
	void UpdateUpState(float elapsedTime, int index);			//	�㏸�X�e�[�g�X�V����
	void TransitionStopState();									//	�����X�e�[�g�֑J��
	void UpdateStopState(float elapsedTime);					//	�����X�e�[�g�X�V����
	void TransitionThrustState();								//	�ˌ��X�e�[�g�֑J��
	void UpdateThrustState(float elapsedTime, int index);		//	�ˌ��X�e�[�g�X�V����
	void TransitionBlownState();								//	�ˌ��X�e�[�g�֑J��
	void UpdateBlownState(float elapsedTime, int index);		//	�ˌ��X�e�[�g�X�V����

private:	//	���ʂ̏���
	DirectX::XMFLOAT3 pieceOffset_ = { -5.0f, 0.0f, -5.0f };	//	����ŏ��ɕ`�悷��Ƃ��̃I�t�Z�b�g�l(�␳�l)
	float range_ = 2.4f;										//	��Ƌ�̊Ԋu���ǂꂭ�炢�󂯂邩

private:	//	����΂��p
	float airPos_;				//	�󒆐����ʒu
	DirectX::XMFLOAT3 velocity_{ 0, 0, 0 };
	DirectX::XMFLOAT3 impulse_{0, 1, 1};
	float radius_ = 0.9f;		//	���a
	float height_ = 0.3f;		//	����
	float gravity_ = -1.0f;		//	�d��
	float upSpeed = 1.0f;		//	�㏸�X�s�[�h
	bool isGround_ = false;		//	�ڒn�t���O

	float friction = 0.5f;		//	���C��
	float acceleration = 1.0f;	//	�����x
	float maxMoveSpeed = 5.0f;	//	
	float moveVecX = 0.0f;		//	x�����̈ړ��x�N�g��
	float moveVecZ = 0.0f;		//	z�����̈ړ��x�N�g��
	float airControl = 0.3f;	//	��C��R?
	float stepOffset = 1.0f;	//
	float slopeRate = 1.0f;		//
	PIECE_STATE pieceState_;	//	��̃X�e�[�g

	float upTimer_ = 0.0f;		//	�㏸���鎞�Ԃ��J�E���g
	float upMax_ = 2.0f;		//	�㏸������܂ł̎���

	float thrustTimer_ = 0.0f;	//	�Փ˂���܂ł̎��Ԃ��J�E���g
	float thrustMax_ = 2.0f;	//	���b�ŏՓ˂�������

private:	//�f�o�b�O�p
	static int num;						//	�����̋�̗v�f�ԍ�
	int myNum_ = 0;						//	�����̋�̗v�f�ԍ�
	std::string typeStr_ = "";			//	��̎��
	std::string choiceStr_ = "";		//	�I������Ă��邩
	std::string pieceStateStr_ = "";	//	��̃X�e�[�g
	std::string isEnemyStr_ = "";		//	�����̋�G�̋

};

