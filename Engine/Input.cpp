#include "Input.h"

namespace Input
{

	LPDIRECTINPUT8   pDInput = nullptr;
	LPDIRECTINPUTDEVICE8 pKeyDevice = nullptr; //デバイスオブジェクト
	BYTE keyState[256];                        //現在の各キーの状態
	BYTE prevkeyState[256];                    //前フレームでの各キーの状態

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
		if (keyState[keyCode] & 0x80)  //2進数:& 128  シフト演算:&(1<<7)
		{
			return true;
		}
		return false;
	}

	//押した瞬間
	bool IsKeyDown(int keyCode)
	{
		// 今は押してて、前回は押してない
		if ((keyState[keyCode] & 0x80) && !(prevkeyState[keyCode] & 0x80))
		{
			return true;
		}
		return false;
	}

	//離した瞬間
	bool IsKeyUp(int keyCode)
	{
		// さっきは押してて、今は押してない状態
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

