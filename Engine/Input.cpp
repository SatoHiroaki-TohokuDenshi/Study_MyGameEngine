#include "Input.h"

namespace Input {
	//DirectInputの本体
	LPDIRECTINPUT8   pDInput = nullptr;

	//キーボードデバイスオブジェクト
	LPDIRECTINPUTDEVICE8 pKeyDevice = nullptr;
	//キーボードの監視用変数
	BYTE keyState[256] = { 0 };		//現在の状態
	BYTE prevKeyState[256] = { 0 };	//1フレーム前の状態

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
		//1フレーム前の状態のコピー
		memcpy(prevKeyState, keyState, sizeof(BYTE) * 256);

		pKeyDevice->Acquire();
		pKeyDevice->GetDeviceState(sizeof(keyState), &keyState);
	}

	//キーが押されているか
	bool IsKey(int keyCode) {
		if (keyState[keyCode] & 0x80) {
			return true;
		}
		return false;
	}

	//キーが押されたか
	bool IsKeyDown(int keyCode) {
		//今は押してて、前回は押してない
		if (IsKey(keyCode) && !(prevKeyState[keyCode] & 0x80)) {
			return true;
		}
		return false;
	}

	//キーが離されたか
	bool IsKeyUp(int keyCode) {
		//今は押してなくて、前回は押してた
		if (!IsKey(keyCode) && (prevKeyState[keyCode] & 0x80)) {
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