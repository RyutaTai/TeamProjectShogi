//#include "SlimeManager.h"
//
////	������
//void SlimeManager::Initialize()
//{
//	for (Slime* slime : slimes_)
//	{
//		slime->Initialize();
//	}
//}
//
////	�X�V����
//void SlimeManager::Update(float elapsedTime)
//{
//	//	�X���C���̍X�V�����@���Ȃ�
//	
//	//	�j������
//	for (Slime* slime : removes_)
//	{
//		std::vector<Slime*>::iterator it =
//			std::find(slimes_.begin(), slimes_.end(), slime);
//		if (it != slimes_.end())
//		{
//			slimes_.erase(it);
//		}
//		delete slime;
//	}
//	//	�j�����X�g���N���A
//	removes_.clear();
//}
//
////	���o�^
//void SlimeManager::Register(Slime* slime)
//{
//	slimes_.emplace_back(slime);
//}
//
////	���S�č폜
//void SlimeManager::Clear()
//{
//	for (Slime* slime : slimes_)
//	{
//		delete slime;
//	}
//	slimes_.clear();
//}
//
////	����폜
//void SlimeManager::Remove(Slime* slime)
//{
//	removes_.insert(slime);	//	�j�����X�g�ɒǉ�
//}
//
////	�`�揈��
//void SlimeManager::Render()
//{
//	for (Slime* piece : slimes_)
//	{
//		piece->Render();
//	}
//}
//
////	�f�o�b�O�`��
//void SlimeManager::DrawDebug()
//{
//	for (Slime* slime : slimes_)
//	{
//		slime->DrawDebug();
//	}
//}
