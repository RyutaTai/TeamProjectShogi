#include "GameObject.h"

#include "../Graphics/Graphics.h"

//	コンストラクタ
GameObject::GameObject(const char* fbxFileName,bool triangulate, bool usedAsCollider)
{
	model_ = std::make_unique<SkinnedMesh>(Graphics::Instance().GetDevice(), fbxFileName, triangulate, usedAsCollider);
}

//	描画処理
void GameObject::Render(const float& scale)
{
	model_->Render(GetTransform()->CalcWorldMatrix(scale), {1,1,1,1},nullptr);
}