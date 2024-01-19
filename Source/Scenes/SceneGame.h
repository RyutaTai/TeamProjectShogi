#pragma once

#include "Scene.h"
#include "../Resources/Sprite.h"
#include "../Game/Stage.h"
#include "../Game/ShogiBoard.h"

class SceneGame : public Scene
{
public:
	SceneGame(){}
	~SceneGame()override{}

	void Initialize()						override;
	void Finalize()							override;

	void Update(const float& elapsedTime)	override;
	void Render()							override;
	void DrawDebug()						override;

private:
	enum class SPRITE_GAME	//	�X�v���C�g
	{
		BACK,		//	�w�i�摜
		MAX,		//	�X�v���C�g�̏����
	};

	std::unique_ptr<Sprite> sprite_[static_cast<int>(SPRITE_GAME::MAX)];
	std::unique_ptr<Stage>	stage_;
	std::unique_ptr<ShogiBoard>	shogiBoard_;	//	������
	Microsoft::WRL::ComPtr<ID3D11Buffer> sceneConstantBuffer_;

private:	//�Q�[���p�ϐ�
	bool isMyTurn_ = true;			//	�����̃^�[�����ǂ���
	float  allottedTime = 30.0f;	//	�e�v���C���[�̈�育�Ƃ̎�������


};

