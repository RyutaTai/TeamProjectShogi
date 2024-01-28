//#include "SlimeManager.h"
//
////	初期化
//void SlimeManager::Initialize()
//{
//	for (Slime* slime : slimes_)
//	{
//		slime->Initialize();
//	}
//}
//
////	更新処理
//void SlimeManager::Update(float elapsedTime)
//{
//	//	スライムの更新処理　今なし
//	
//	//	破棄処理
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
//	//	破棄リストをクリア
//	removes_.clear();
//}
//
////	駒を登録
//void SlimeManager::Register(Slime* slime)
//{
//	slimes_.emplace_back(slime);
//}
//
////	駒を全て削除
//void SlimeManager::Clear()
//{
//	for (Slime* slime : slimes_)
//	{
//		delete slime;
//	}
//	slimes_.clear();
//}
//
////	駒を削除
//void SlimeManager::Remove(Slime* slime)
//{
//	removes_.insert(slime);	//	破棄リストに追加
//}
//
////	描画処理
//void SlimeManager::Render()
//{
//	for (Slime* piece : slimes_)
//	{
//		piece->Render();
//	}
//}
//
////	デバッグ描画
//void SlimeManager::DrawDebug()
//{
//	for (Slime* slime : slimes_)
//	{
//		slime->DrawDebug();
//	}
//}
