#include "../Input/Mouse.h"

static const int KeyMap[] =
{
	VK_LBUTTON,		// ���{�^��
	VK_MBUTTON,		// ���{�^��
	VK_RBUTTON,		// �E�{�^��
};

// �R���X�g���N�^
Mouse::Mouse(HWND hWnd_)
	: hWnd_(hWnd_)
{
	RECT rc;
	GetClientRect(hWnd_, &rc);
	screenWidth_ = rc.right - rc.left;
	screenHeight_ = rc.bottom - rc.top;
}

// �X�V
void Mouse::Update()
{
	// �X�C�b�`���
	MouseButton newButtonState = 0;

	for (int i = 0; i < ARRAYSIZE(KeyMap); ++i)
	{
		if (::GetAsyncKeyState(KeyMap[i]) & 0x8000)
		{
			newButtonState |= (1 << i);
		}
	}

	// �z�C�[��
	wheel_[1] = wheel_[0];
	wheel_[0] = 0;

	// �{�^�����X�V
	buttonState_[1] = buttonState_[0];	// �X�C�b�`����
	buttonState_[0] = newButtonState;

	buttonDown_ = ~buttonState_[1] & newButtonState;	// �������u��
	buttonUp_ = ~newButtonState & buttonState_[1];	// �������u��

	// �J�[�\���ʒu�̎擾
	POINT cursor;
	::GetCursorPos(&cursor);
	::ScreenToClient(hWnd_, &cursor);

	// ��ʂ̃T�C�Y���擾����B
	RECT rc;
	GetClientRect(hWnd_, &rc);
	UINT screenW = rc.right - rc.left;
	UINT screenH = rc.bottom - rc.top;
	UINT viewportW = screenWidth_;
	UINT viewportH = screenHeight_;

	// ��ʕ␳
	positionX_[1] = positionX_[0];
	positionY_[1] = positionY_[0];
	positionX_[0] = (LONG)(cursor.x / static_cast<float>(viewportW) * static_cast<float>(screenW));
	positionY_[0] = (LONG)(cursor.y / static_cast<float>(viewportH) * static_cast<float>(screenH));
}
