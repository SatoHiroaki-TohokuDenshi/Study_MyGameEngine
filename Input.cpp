#include "Input.h"

namespace Input {
	//DirectInputの本体
	LPDIRECTINPUT8   pDInput = nullptr;

	//キーボードデバイスオブジェクト
	LPDIRECTINPUTDEVICE8 pKeyDevice = nullptr;
	//キーボードの監視用変数
	BYTE keyState[256] = { 0 };

	//初期化
	void Initialize(HWND hWnd) {
		//DirectInputの作成
		DirectInput8Create(GetModuleHandle(nullptr), DIRECTINPUT_VERSION, IID_IDirectInput8, (VOID**)&pDInput, nullptr);
		
		//キーボードデバイスオブジェクトの作成と設定
		pDInput->CreateDevice(GUID_SysKeyboard, &pKeyDevice, nullptr);
		pKeyDevice->SetDataFormat(&c_dfDIKeyboard);
		pKeyDevice->SetCooperativeLevel(hWnd, DISCL_NONEXCLUSIVE | DISCL_BACKGROUND);
	}

	//更新
	void Update() {
		pKeyDevice->Acquire();
		pKeyDevice->GetDeviceState(sizeof(keyState), &keyState);
	}

	//キーの検出
	bool IsKey(int keyCode) {
		if (keyState[keyCode] & 0x80) {
			return true;
		}
		return false;
	}

	//解放
	void Release() {
		SAFE_RELEASE(pKeyDevice);
		SAFE_RELEASE(pDInput);
	}
}