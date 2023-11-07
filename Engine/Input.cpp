#include "Input.h"

namespace Input
{

	LPDIRECTINPUT8   pDInput = nullptr;
	LPDIRECTINPUTDEVICE8 pKeyDevice = nullptr; //�f�o�C�X�I�u�W�F�N�g
	BYTE keyState[256];                        //���݂̊e�L�[�̏��
	BYTE prevkeyState[256];                    //�O�t���[���ł̊e�L�[�̏��

	void Initialize(HWND hWnd)
	{
		DirectInput8Create(GetModuleHandle(nullptr), DIRECTINPUT_VERSION, IID_IDirectInput8, (VOID**)&pDInput, nullptr);
		pDInput->CreateDevice(GUID_SysKeyboard, &pKeyDevice, nullptr);
		pKeyDevice->SetDataFormat(&c_dfDIKeyboard);
		pKeyDevice->SetCooperativeLevel(hWnd, DISCL_NONEXCLUSIVE | DISCL_BACKGROUND);
	}

	void Update()
	{
		memcpy(prevkeyState, keyState, sizeof(keyState));

		pKeyDevice->Acquire();
		pKeyDevice->GetDeviceState(sizeof(keyState), &keyState);
	}

	bool IsKey(int keyCode)
	{
		if (keyState[keyCode] & 0x80)  //2�i��:& 128  �V�t�g���Z:&(1<<7)
		{
			return true;
		}
		return false;
	}

	//�������u��
	bool IsKeyDown(int keyCode)
	{
		// ���͉����ĂāA�O��͉����ĂȂ�
		if ((keyState[keyCode] & 0x80) && !(prevkeyState[keyCode] & 0x80))
		{
			return true;
		}
		return false;
	}

	//�������u��
	bool IsKeyUp(int keyCode)
	{
		// �������͉����ĂāA���͉����ĂȂ����
		if (!(keyState[keyCode] & 0x80) && (prevkeyState[keyCode] & 0x80))
		{
			return true;
		}
		return false;
	}

	void Release()
	{
		SAFE_RELEASE(pDInput);
	}
}

