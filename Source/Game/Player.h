#pragma once

#include "Character.h"
#include "../Core/HighResolutionTimer.h"
#include "../Graphics/Graphics.h"
#include "../Graphics/Camera.h"
#include "../Game/PieceManager.h"
#include "../Game/Piece.h"

class Player :public Character
{
public:
	Player(const char* fileName, bool triangulate = false, bool usedAsCollider = false);
	Player() {}
	void Update(float elapsedTime, HWND hwnd);


protected:
	void ChoisePiece(HWND hwnd)	;	//	駒を選択
	void MovePiece()	override;	//	選んだ駒を動かす

private:
	DirectX::XMFLOAT2 ChoiceSquare();	//	置くマスを選択 → 選択したマスのx,y座標を返す

public:
	// RAYCAST
	DirectX::XMFLOAT4 intersectionPoint{};
	DirectX::XMFLOAT4X4 islandTransform{ -0.01f, 0, 0, 0, 0, 0.01f, 0, 0, 0, 0, 0.01f, 0, 0, 0, 0, 1 };
	Graphics::SceneConstants sceneData_{};

};