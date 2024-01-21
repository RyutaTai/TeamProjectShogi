// RAYCAST
#include "raycast.h"

using namespace DirectX;

// The function returns the index of the triangle if it intersects, or -1 if it does not.
int IntersectRayTriangles
(
	const float* positions, // vertices
	const uint32_t offset, // bytes
	const uint32_t stride, // bytes
	const uint32_t* indices,
	const size_t indexCount,
	const XMFLOAT3& rayPosition,
	const XMFLOAT3& rayDirection,
	XMFLOAT4& intersection,
	float& distance,
	const bool RHS
)
{
	const bool CCW{ RHS }; // Counterclockwise 3D triangle ABC �����v����3�����O�p�`ABC
	const int C0{ 0 };
	const int C1{ CCW ? 1 : 2 };	//if(CCW) C1=1; else C1=2; �Ɠ���
	const int C2{ CCW ? 2 : 1 };

	// Ray-triangle intersection 
	// In this handout, we explore the steps needed to compute the intersection of a ray with a triangle, and then to
	// compute the barycentric coordinates of that intersection.First, we consider the geometry of such an intersection :
	//
	// where a ray with origin P and direction D intersects a triangle defined by its vertices, A, B, and C at intersection
	// point Q.The square region diagrammatically surrounding triangle ABC represents the supporting plane of the
	// triangle, i.e., the plane that the triangle lies on.
	//
	// To perform ray - triangle intersection, we must perform two steps :
	//
	//  1. Determine the point of intersection, Q.
	//  2. Determine if Q lies inside of triangle ABC.
	//
	// �����ƎO�p�`�̌�_ 
	//���̃n���h�A�E�g�ł́A�����ƎO�p�`�̌�_���v�Z��,���̌�_�̏d�S���W���v�Z���邽�߂ɕK�v�ȃX�e�b�v��T��܂��B
	// �܂��A���̂悤�Ȍ�_�̊􉽊w�I�`����l���܂��F
	//
	// ���_ P �ƕ��� D �����������A���̒��_ A, B, C �Œ�`�����O�p�`�ƌ�_ Q �Ō����B
	// �O�p�`ABC��}���I�Ɉ͂ސ����`�̗̈�́A�O�p�`�̎x�����ʂ�\���B
	// �O�p�`ABC��}���I�Ɉ͂ގl�p���̈�́A�O�p�`�̎x�����ʁA���Ȃ킿�O�p�`��������镽�ʂ�\���B
	//
	//�����ƎO�p�`�̌�_�����߂�ɂ́A2�̃X�e�b�v�����s����K�v������F
	//
	// 1. ��_Q�����肷��B
	// Q ���O�p�` ABC �̓����ɂ��邩�ǂ����𔻒f����B

	int intersectionCount{ 0 };				//	�������鐔
	int intersectedTriangleIndex{ -1 };		//	��������O�p�`�̃C���f�b�N�X

	const float rayLengthLimit{ distance };	//	���C�̒����̍ő�
	float closestDistance{ FLT_MAX };			//	�ł��߂��_

	XMVECTOR X{}; // closest cross point
	const XMVECTOR P{ XMVectorSet(rayPosition.x, rayPosition.y, rayPosition.z, 1) };							//		
	const XMVECTOR D{ XMVector3Normalize(XMVectorSet(rayDirection.x, rayDirection.y, rayDirection.z, 0)) };	//	

	using byte = uint8_t;
	const byte* p{ reinterpret_cast<const byte*>(positions) + offset };
	const size_t triangleCount{ indexCount / 3 };
	for (size_t triangleIndex = 0; triangleIndex < triangleCount; triangleIndex++)
	{
		const XMVECTOR A{ XMVectorSet(
			(reinterpret_cast<const float*>(p + indices[triangleIndex * 3 + C0] * stride))[0],
			(reinterpret_cast<const float*>(p + indices[triangleIndex * 3 + C0] * stride))[1],
			(reinterpret_cast<const float*>(p + indices[triangleIndex * 3 + C0] * stride))[2],
			1.0f
		) };
		const XMVECTOR B{ XMVectorSet(
			(reinterpret_cast<const float*>(p + indices[triangleIndex * 3 + C1] * stride))[0],
			(reinterpret_cast<const float*>(p + indices[triangleIndex * 3 + C1] * stride))[1],
			(reinterpret_cast<const float*>(p + indices[triangleIndex * 3 + C1] * stride))[2],
			1.0f
		) };
		const XMVECTOR C{ XMVectorSet(
			(reinterpret_cast<const float*>(p + indices[triangleIndex * 3 + C2] * stride))[0],
			(reinterpret_cast<const float*>(p + indices[triangleIndex * 3 + C2] * stride))[1],
			(reinterpret_cast<const float*>(p + indices[triangleIndex * 3 + C2] * stride))[2],
			1.0f
		) };

		// Determining Q
		// Determining the point of intersection Q in turn requires us to take two more steps :
		//  1. Determine the equation of the supporting plane for triangle ABC.
		//  2. Intersect the ray with the supporting plane.
		// We�E�fll handle these steps in reverse order.
		// Q�̌���
		// ��_Q�����߂�ɂ́A�����2�̃X�e�b�v�𓥂ޕK�v������F
		// 1. �O�p�` ABC �̎x�����ʂ̕����������߂�B
		// 2. �x�����ʂƌ���������������B
		// �����̃X�e�b�v���t�̏����ŏ�������B
		XMVECTOR Q;

		// 1. Determine the equation of the supporting plane for triangle ABC.
		// 1. �O�p�`ABC�̎x�����ʂ̕����������߂�B
		const XMVECTOR N{ XMVector3Normalize(XMVector3Cross(XMVectorSubtract(B, A), XMVectorSubtract(C, A))) };
		const float d{ XMVectorGetByIndex(XMVector3Dot(N, A), 0) };

		// 2. Intersect the ray with the supporting plane.
		// 2. �x�����ʂƌ���������������B
		const float denominator{ XMVectorGetByIndex(XMVector3Dot(N, D), 0) };
		if (denominator < 0) // Note that if N.D = 0 , then D is parallel to the plane and the ray does not intersect the plane.
							 //	N.D = 0 �̏ꍇ�AD �͕��ʂɕ��s�ł���A�����͕��ʂƌ������Ȃ��B
		{
			const float numerator{ d - XMVectorGetByIndex(XMVector3Dot(N, P), 0) };
			const float t{ numerator / denominator };

			if (t > 0 && t < rayLengthLimit) // Forward and Length limit of Ray
			{
				Q = XMVectorAdd(P, XMVectorScale(D, t));

				// Triangle inside - outside testing
				//	// �O�p�`�̓����ƊO���̃e�X�g

				// CHRISTER ERICSON. "REAL-TIME COLLISION DETECTION" pp.204
				// Test if point Q lies inside the counterclockwise 3D triangle ABC
				// �_Q�������v����3�����O�p�`ABC�̓����ɂ��邩�ǂ������e�X�g����B

				// Translate point and triangle so that point lies at origin
				//	�_�ƎO�p�`���ړ����āA���̓_�����_�ɂ���悤�ɂ���		

				const XMVECTOR QA{ XMVectorSubtract(A, Q) };
				const XMVECTOR QB{ XMVectorSubtract(B, Q) };
				const XMVECTOR QC{ XMVectorSubtract(C, Q) };

				XMVECTOR U{ XMVector3Cross(QB, QC) };
				XMVECTOR V{ XMVector3Cross(QC, QA) };
				if (XMVectorGetByIndex(XMVector3Dot(U, V), 0) < 0)
				{
					continue;
				}

				XMVECTOR W{ XMVector3Cross(QA, QB) };
				if (XMVectorGetByIndex(XMVector3Dot(U, W), 0) < 0)
				{
					continue;
				}
				if (XMVectorGetByIndex(XMVector3Dot(V, W), 0) < 0)
				{
					continue;
				}

				// Otherwise Q must be in (or on) the triangle
				if (t < closestDistance)
				{
					closestDistance = t;
					intersectedTriangleIndex = static_cast<int>(triangleIndex);
					X = Q;
				}
				intersectionCount++;
			}
		}
	}
	if (intersectionCount > 0)
	{
		XMStoreFloat4(&intersection, X);
		distance = closestDistance;
	}
	return intersectedTriangleIndex;
}
