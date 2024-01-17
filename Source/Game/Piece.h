#pragma once

#include "GameObject.h"

//	�����̋�N���X
class Piece :public GameObject
{
private:	
	//	�\���̂Ƃ�
	enum class PIECE_TYPE		//	��̎�ނ�錾����
	{
		HUHYOU,					//	����
		TOKIN,					//	�Ƌ��i�����������j
		KYOUSHA,				//	����
		NARIKYOU,				//	�����i���������ԁj
		KEIMA,					//	�j�n
		NARIKEI,				//	���j�i�������j�n�j
		GINSHOU,				//	�⏫
		NARIGIN,				//	����i�������⏫�j
		HISHA,					//	���
		RYUOU,					//	�����i��������ԁj
		KAKUGYOU,				//	�p�s
		RYUMA,					//	���n�i�������p�s�j
		KINSHOU,				//	����
		OUSHOU,					//	���� �ʏ��͒�`���ĂȂ�
	};

	//	��̐i�s����
	enum class DIRECTION		
	{

	};

	//	��̏��
	struct PieceInfo			
	{
	public:
		int posX_;						//	���x���W ���W��9x9�}�X�̒��ŕ\�L����
		int posY_;						//	���y���W
		PIECE_TYPE pieceType_;			//	��̎��
		bool isEnemy_;					//	�G�̋�A�����̋ �G�Ȃ�true
	};

public:
	static const int PIECE_MAX = 40;	//	��̍ő吔
	//	��̏������W
	PieceInfo pieceInfo_[PIECE_MAX] =
	{
		//	�G
		{1,1,PIECE_TYPE::KYOUSHA,	true},
		{2,1,PIECE_TYPE::KEIMA,		true},
		{3,1,PIECE_TYPE::GINSHOU,	true},
		{4,1,PIECE_TYPE::KINSHOU,	true},
		{5,1,PIECE_TYPE::OUSHOU,	true},
		{6,1,PIECE_TYPE::KINSHOU,	true},
		{7,1,PIECE_TYPE::GINSHOU,	true},
		{8,1,PIECE_TYPE::KEIMA,		true},
		{9,1,PIECE_TYPE::KYOUSHA,	true},

		{2,2,PIECE_TYPE::HISHA,		true},	//	10
		{8,2,PIECE_TYPE::KAKUGYOU,	true},

		{1,3,PIECE_TYPE::HUHYOU,	true},
		{2,3,PIECE_TYPE::HUHYOU,	true},
		{3,3,PIECE_TYPE::HUHYOU,	true},
		{4,3,PIECE_TYPE::HUHYOU,	true},
		{5,3,PIECE_TYPE::HUHYOU,	true},
		{6,3,PIECE_TYPE::HUHYOU,	true},
		{7,3,PIECE_TYPE::HUHYOU,	true},
		{8,3,PIECE_TYPE::HUHYOU,	true},
		{9,3,PIECE_TYPE::HUHYOU,	true},	//	20

		//	����
		{1,7,PIECE_TYPE::KYOUSHA,	false},
		{2,7,PIECE_TYPE::KEIMA,		false},
		{3,7,PIECE_TYPE::GINSHOU,	false},
		{4,7,PIECE_TYPE::KINSHOU,	false},
		{5,7,PIECE_TYPE::OUSHOU,	false},
		{6,7,PIECE_TYPE::KINSHOU,	false},
		{7,7,PIECE_TYPE::GINSHOU,	false},
		{8,7,PIECE_TYPE::KEIMA,		false},
		{9,7,PIECE_TYPE::KYOUSHA,	false},

		{2,8,PIECE_TYPE::KAKUGYOU,	false},	//	30
		{8,8,PIECE_TYPE::HISHA,		false},

		{1,9,PIECE_TYPE::HUHYOU,	false},
		{2,9,PIECE_TYPE::HUHYOU,	false},
		{3,9,PIECE_TYPE::HUHYOU,	false},
		{4,9,PIECE_TYPE::HUHYOU,	false},
		{5,9,PIECE_TYPE::HUHYOU,	false},
		{6,9,PIECE_TYPE::HUHYOU,	false},
		{7,9,PIECE_TYPE::HUHYOU,	false},
		{8,9,PIECE_TYPE::HUHYOU,	false},
		{9,9,PIECE_TYPE::HUHYOU,	false},	//	40
	};

public:
	Piece(const char* filename, bool triangulate = false);
	~Piece() {}

	void Initialize(int index);							//	�������@�ʒu�ݒ�Ƃ�
	void Update(float elapsedTime);						//	�X�V����
	void Render();										//	�`�揈��
	void DrawDebug();									//	�f�o�b�O�`��

	void Destroy();										//	�j������
	PieceInfo GetPieceInfo(int index) { return this->pieceInfo_[index]; }	//	�����̋�f�[�^�擾	

private:
	static const int boradX_ = 9;								//	�}�X��x��
	static const int boardY_ = 9;								//	�}�X��y��
	static const int board_[boradX_][boardY_];					//	�����Ղ̃f�[�^ 9x9
	DirectX::XMFLOAT3 pieceOffset_ = { -5.0f, 0.0f, -5.0f };	//	����ŏ��ɕ`�悷��Ƃ��̃I�t�Z�b�g�l(�␳�l)
	float range_ = 2.5f;										//	��Ƌ�̊Ԋu���ǂꂭ�炢�󂯂邩

private:
	static int num;		//	ImGui�f�o�b�O�p
	int myNum_ = 0;		//	ImGui�f�o�b�O�p
};

