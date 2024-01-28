#include "../Input/Input.h"

#include <windows.h>

Input* Input::instance_ = nullptr;

// �R���X�g���N�^
Input::Input(HWND hWnd)
	: mouse_(hWnd)
{
	instance_ = this;
}

// �X�V����
void Input::Update()
{
	gamePad_.Update();
	mouse_.Update();
}
