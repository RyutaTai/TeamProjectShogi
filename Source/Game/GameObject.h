#pragma once

#include <memory>

#include "../Resources/SkinnedMesh.h"
#include "../Others/Transform.h"

class GameObject
{
public:
	GameObject(const char* fbxFileName, bool triangulate = false, bool usedAsCollider = false);
	GameObject() {}
	virtual ~GameObject() {}

	void Render(const float& scale);

	Transform* GetTransform() { return &transform_; }
	SkinnedMesh* GetModel() { return model_.get(); }

private:
	std::unique_ptr<SkinnedMesh>	model_;
	Transform						transform_;
	Animation::Keyframe				keyframe_ = {};

};

