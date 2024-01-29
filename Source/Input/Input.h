#pragma once

#include "../Input/GamePad.h"
#include "../Input/Mouse.h"

// �C���v�b�g
class Input
{
public:
	Input(HWND hWnd);
	~Input() {}

public:
	// �C���X�^���X�擾
	static Input& Instance() { return *instance_; }

	// �X�V����
	void Update();

	// �Q�[���p�b�h�擾
	GamePad& GetGamePad() { return gamePad_; }

	// �}�E�X�擾
	Mouse& GetMouse() { return mouse_; }

private:
	static Input*		instance_;
	GamePad				gamePad_;
	Mouse				mouse_;
};
