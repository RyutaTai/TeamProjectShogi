#pragma once

#include "Character.h"
#include "../Graphics/Graphics.h"
#include "../Graphics/Camera.h"
#include "../Game/PieceManager.h"
#include "../Game/Piece.h"

class Player :public Character
{
public:
	// RAYCAST
	DirectX::XMFLOAT4 intersectionPoint{};
	DirectX::XMFLOAT4X4 islandTransform{ -0.01f, 0, 0, 0, 0, 0.01f, 0, 0, 0, 0, 0.01f, 0, 0, 0, 0, 1 };
	Graphics::SceneConstants sceneData_{};

public:
	Player(const char* fileName, bool triangulate = false, bool usedAsCollider = false);
	Player() {}
	void Update(float elapsedTime, HWND hwnd);

protected:
	void ChoisePiece(HWND hwnd)	;	//	‹î‚ð‘I‘ð
	void MovePiece()	override;	//	‘I‚ñ‚¾‹î‚ð“®‚©‚·

};