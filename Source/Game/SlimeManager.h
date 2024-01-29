//#pragma once
//
//#include "../Game/Slime.h"
//
//class SlimeManager
//{
//private:
//	SlimeManager() {}
//	~SlimeManager() {}
//public:
//	//	�B��̃C���X�^���X�擾
//	static SlimeManager& Instance()
//	{
//		static SlimeManager instance_;
//		return instance_;
//	}
//
//	void Initialize();				//	������
//	void Update(float elapsedTime);	//	�X�V����
//	void Render();					//	�`�揈��
//	void DrawDebug();				//	�f�o�b�O�`��
//
//	void Register(Slime* slime);	//	�X���C����o�^
//	void Clear();					//	�X���C����S�č폜
//	void Remove(Slime* slime);		//	�X���C�����폜
//
//	Slime*	GetSlime(int index) { return slimes_.at(index); }//	�X���C�����擾
//
//private:
//	std::vector<Slime*> slimes_;	//	�X���C���̔z��
//	std::set<Slime*>	removes_;		//	�j�����X�g
//
//};
//
