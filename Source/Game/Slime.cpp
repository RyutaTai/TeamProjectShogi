//#include "Slime.h"
//
//Slime::Slime(const char* fileName, bool triangulate, bool usedAsCollider)
//	:GameObject(fileName, triangulate, usedAsCollider)
//{
//	GetTransform()->SetPosition(DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f));
//	GetTransform()->SetScale(DirectX::XMFLOAT3(1.0f, 1.0f, 1.0f));
//	GetTransform()->SetRotation(DirectX::XMFLOAT4(0.0f, DirectX::XMConvertToRadians(0), 0.0f, 0.0f));
//}
//
//// 初期化
//void Slime::Initialize()
//{
//
//}
//
////	描画処理
//void Slime::Render()
//{
//	GameObject::Render(100.0f);
//}
//
////	デバッグ描画
//void Slime::DrawDebug()
//{
//	GetTransform()->DrawDebug();
//}