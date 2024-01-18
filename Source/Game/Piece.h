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
		{1,3,PIECE_TYPE::HUHYO,		true},		//	�G����
		{2,3,PIECE_TYPE::HUHYO,		true},
		{3,3,PIECE_TYPE::HUHYO,		true},
		{4,3,PIECE_TYPE::HUHYO,		true},
		{5,3,PIECE_TYPE::HUHYO,		true},
		{6,3,PIECE_TYPE::HUHYO,		true},
		{7,3,PIECE_TYPE::HUHYO,		true},
		{8,3,PIECE_TYPE::HUHYO,		true},
		{9,3,PIECE_TYPE::HUHYO,		true},	
		{1,7,PIECE_TYPE::HUHYO,		false},		//	��������
		{2,7,PIECE_TYPE::HUHYO,		false},
		{3,7,PIECE_TYPE::HUHYO,		false},
		{4,7,PIECE_TYPE::HUHYO,		false},
		{5,7,PIECE_TYPE::HUHYO,		false},
		{6,7,PIECE_TYPE::HUHYO,		false},
		{7,7,PIECE_TYPE::HUHYO,		false},
		{8,7,PIECE_TYPE::HUHYO,		false},
		{9,7,PIECE_TYPE::HUHYO,		false},
		{8,2,PIECE_TYPE::KAKUGYO,	true},		//	�G�p�s
		{8,8,PIECE_TYPE::KAKUGYO,	false},		//	�����p�s
		{2,2,PIECE_TYPE::HISHA,		true},		//	�G���
		{2,8,PIECE_TYPE::HISHA,		false},		//	�������
		{1,1,PIECE_TYPE::KYOUSHA,	true},		//	�G����
		{9,1,PIECE_TYPE::KYOUSHA,	true},
		{1,9,PIECE_TYPE::KYOUSHA,	false},		//	��������
		{9,9,PIECE_TYPE::KYOUSHA,	false},
		{2,1,PIECE_TYPE::KEIMA,		true},		//	�G�j�n
		{8,1,PIECE_TYPE::KEIMA,		true},
		{2,9,PIECE_TYPE::KEIMA,		false},		//	�����j�n
		{8,9,PIECE_TYPE::KEIMA,		false},
		{3,1,PIECE_TYPE::GINSHO,	true},		//	�G�⏫
		{7,1,PIECE_TYPE::GINSHO,	true},
		{3,9,PIECE_TYPE::GINSHO,	false},		//	�����⏫
		{7,9,PIECE_TYPE::GINSHO,	false},
		{4,1,PIECE_TYPE::KINSHO,	true},		//	�G����
		{6,1,PIECE_TYPE::KINSHO,	true},
		{4,9,PIECE_TYPE::KINSHO,	false},		//	��������
		{6,9,PIECE_TYPE::KINSHO,	false},
		{5,1,PIECE_TYPE::GYOKUSHO,	true},		//	�ʏ�
		{5,9,PIECE_TYPE::OUSHO,		false},		//	����

	};

public:
	Piece(const char* filename, bool triangulate = false);
	~Piece();

	void Initialize(int index);									//	�������@�ʒu�ݒ�Ƃ�
	void Update(float elapsedTime);								//	�X�V����
	void Render();												//	�`�揈��

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

