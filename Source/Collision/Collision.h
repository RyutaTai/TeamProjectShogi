#pragma once

#include <DirectXMath.h>

//�q�b�g����
struct HitResult
{
	DirectX::XMFLOAT3 position = { 0,0,0 };		//���C�ƃ|���S���̌�_
	DirectX::XMFLOAT3 normal = { 0,0,0 };		//�Փ˂����|���S���̖@���x�N�g��
	float distance = 0.0f;						//���C�̎n�_�����_�܂ł̋���
	int materialIndex;							//�Փ˂����|���S���̃}�e���A���ԍ�
	DirectX::XMFLOAT3 rotation = { 0,0,0 };		//��]��
};


//�R���W����
class Collision
{
public:
	//���Ƌ��̌�������
	static bool IntersectSphereVsSphere(
		const DirectX::XMFLOAT3& positionA,
		float radiusA,
		const DirectX::XMFLOAT3& positionB,
		float radiusB,
		DirectX::XMFLOAT3& outPositionB
	);

	//�~���Ɖ~���̌�������
	static bool InterSectCylinderVsCyliner(
		const DirectX::XMFLOAT3& positionA,
		float radiusA,
		float heightA,
		const DirectX::XMFLOAT3& positionB,
		float radiusB,
		float heightB,
		DirectX::XMFLOAT3& outPositionB
	);

	//���Ɖ~���̌�������
	static bool IntersectSphereVsCylinder(
		const DirectX::XMFLOAT3& spherePosition,
		float sphereRadius,
		const DirectX::XMFLOAT3& cylinderPosition,
		float cylinderRadius,
		float cylinderHeight,
		DirectX::XMFLOAT3& outCylinderPosition
	);

	////Unit12
	////���C�ƃ��f���̌�������
	//static bool IntersectRayVsModel(
	//	const DirectX::XMFLOAT3& start,
	//	const DirectX::XMFLOAT3& end,
	//	const Model* model,
	//	HitResult& result
	//);
};