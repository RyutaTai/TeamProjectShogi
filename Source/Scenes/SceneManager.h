#pragma once

#include "Scene.h"

class SceneManager
{
private:
	SceneManager() {}
	~SceneManager() 
	{ 
		if (currentScene_) {
			delete currentScene_;
			currentScene_ = nullptr;
		}
		if (nextScene_) {
			delete nextScene_;
			nextScene_ = nullptr;
		}
	}

public: 
	static SceneManager& Instance()
	{
		static SceneManager instance;
		return instance;
	}
	void Update(const float& elapsedTime);
	void Render();
	void Clear();
	void ChangeScene(Scene* scene);

private:
	Scene* currentScene_ = nullptr;		//	現在のシーン
	Scene* nextScene_ = nullptr;		//	次のシーン

};

