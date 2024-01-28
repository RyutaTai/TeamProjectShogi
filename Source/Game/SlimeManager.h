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
//	//	唯一のインスタンス取得
//	static SlimeManager& Instance()
//	{
//		static SlimeManager instance_;
//		return instance_;
//	}
//
//	void Initialize();				//	初期化
//	void Update(float elapsedTime);	//	更新処理
//	void Render();					//	描画処理
//	void DrawDebug();				//	デバッグ描画
//
//	void Register(Slime* slime);	//	スライムを登録
//	void Clear();					//	スライムを全て削除
//	void Remove(Slime* slime);		//	スライムを削除
//
//	Slime*	GetSlime(int index) { return slimes_.at(index); }//	スライムを取得
//
//private:
//	std::vector<Slime*> slimes_;	//	スライムの配列
//	std::set<Slime*>	removes_;		//	破棄リスト
//
//};
//
