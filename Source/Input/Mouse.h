#pragma once

#include <Windows.h>

using MouseButton = unsigned int;

// �}�E�X
class Mouse
{
public:
	static const MouseButton BTN_LEFT = (1 << 0);
	static const MouseButton BTN_MIDDLE = (1 << 1);
	static const MouseButton BTN_RIGHT = (1 << 2);

public:
	Mouse(HWND hWnd_);
	~Mouse() {}

	// �X�V
	void Update();

	// �{�^�����͏�Ԃ̎擾
	MouseButton GetButton() const { return buttonState_[0]; }

	// �{�^��������Ԃ̎擾
	MouseButton GetButtonDown() const { return buttonDown_; }

	// �{�^�������Ԃ̎擾
	MouseButton GetButtonUp() const { return buttonUp_; }

	// �z�C�[���l�̐ݒ�
	void SetWheel(int wheel_) { this->wheel_[0] += wheel_; }

	// �z�C�[���l�̎擾
	int GetWheel() const { return wheel_[1]; }

	// �}�E�X�J�[�\��X���W�擾
	int GetPositionX() const { return positionX_[0]; }

	// �}�E�X�J�[�\��Y���W�擾
	int GetPositionY() const { return positionY_[0]; }

	// �O��̃}�E�X�J�[�\��X���W�擾
	int GetOldPositionX() const { return positionX_[1]; }

	// �O��̃}�E�X�J�[�\��Y���W�擾
	int GetOldPositionY() const { return positionY_[1]; }

	// �X�N���[�����ݒ�
	void SetScreenWidth(int width) { screenWidth_ = width; }

	// �X�N���[�������ݒ�
	void SetScreenHeight(int height) { screenHeight_ = height; }

	// �X�N���[�����擾
	int GetScreenWidth() const { return screenWidth_; }

	// �X�N���[�������擾
	int GetScreenHeight() const { return screenHeight_; }

private:
	MouseButton		buttonState_[2] = { 0 };
	MouseButton		buttonDown_ = 0;
	MouseButton		buttonUp_ = 0;
	int				positionX_[2];
	int				positionY_[2];
	int				wheel_[2];
	int				screenWidth_ = 0;
	int				screenHeight_ = 0;
	HWND			hWnd_ = nullptr;
};
