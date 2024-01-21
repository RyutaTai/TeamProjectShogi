#include "GameObject.h"

#include "../Graphics/Graphics.h"

//	�R���X�g���N�^
GameObject::GameObject(const char* fbxFileName,bool triangulate, bool usedAsCollider)
{
	model_ = std::make_unique<SkinnedMesh>(Graphics::Instance().GetDevice(), fbxFileName, triangulate, usedAsCollider);
}

//	�`�揈��
void GameObject::Render(const float& scale)
{
	model_->Render(GetTransform()->CalcWorldMatrix(scale), {1,1,1,1},nullptr);
}