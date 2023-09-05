#include "Input.h"
#include <string>

namespace Input {
	//DirectInputの本体
	LPDIRECTINPUT8   pDInput_ = nullptr;

	//----------変数----------//

	//キーボード
	LPDIRECTINPUTDEVICE8 pKeyDevice_ = nullptr;	//キーボードデバイスオブジェクト
	BYTE keyState_[256] = { 0 };					//現在の状態
	BYTE prevKeyState_[256] = { 0 };				//1フレーム前の状態

	//マウス
	LPDIRECTINPUTDEVICE8	pMouseDevice_;	//デバイスオブジェクト
	DIMOUSESTATE mouseState_;				//マウスの状態
	DIMOUSESTATE prevMouseState_;			//前フレームのマウスの状態
	POINT mousePos_;						//マウスカーソルの位置

	//----------関数----------//

	//初期化
	void Initialize(HWND hWnd) {
		//DirectInputの作成
		DirectInput8Create(GetModuleHandle(nullptr), DIRECTINPUT_VERSION, IID_IDirectInput8, (VOID**)&pDInput_, nullptr);
		
		//キーボードデバイスオブジェクトの作成と設定
		pDInput_->CreateDevice(GUID_SysKeyboard, &pKeyDevice_, nullptr);
		pKeyDevice_->SetDataFormat(&c_dfDIKeyboard);
		pKeyDevice_->SetCooperativeLevel(hWnd, DISCL_NONEXCLUSIVE | DISCL_BACKGROUND);

		//マウス
		pDInput_->CreateDevice(GUID_SysMouse, &pMouseDevice_, nullptr);
		pMouseDevice_->SetDataFormat(&c_dfDIMouse);
		pMouseDevice_->SetCooperativeLevel(hWnd, DISCL_NONEXCLUSIVE | DISCL_FOREGROUND);
	}

	//更新
	void Update() {
		//1フレーム前の状態のコピー
		memcpy(prevKeyState_, keyState_, sizeof(BYTE) * 256);

		pKeyDevice_->Acquire();
		pKeyDevice_->GetDeviceState(sizeof(keyState_), &keyState_);

		//マウス
		pMouseDevice_->Acquire();
		memcpy(&prevMouseState_, &mouseState_, sizeof(mouseState_));
		pMouseDevice_->GetDeviceState(sizeof(mouseState_), &mouseState_);

	}

	//キーボード//
	
	//キーが押されているか
	bool IsKey(int keyCode) {
		if (keyState_[keyCode] & 0x80) {
			return true;
		}
		return false;
	}

	//キーが押されたか
	bool IsKeyDown(int keyCode) {
		//今は押してて、前回は押してない
		if (IsKey(keyCode) && !(prevKeyState_[keyCode] & 0x80)) {
			return true;
		}
		return false;
	}

	//キーが離されたか
	bool IsKeyUp(int keyCode) {
		//今は押してなくて、前回は押してた
		if (!IsKey(keyCode) && (prevKeyState_[keyCode] & 0x80)) {
			return true;
		}
		return false;
	}

	//マウス

	//マウスのボタンが押されているか調べる
	bool IsMouseButton(int buttonCode)
	{
		//押してる
		if (mouseState_.rgbButtons[buttonCode] & 0x80)
		{
			return true;
		}
		return false;
	}

	//マウスのボタンを今押したか調べる（押しっぱなしは無効）
	bool IsMouseButtonDown(int buttonCode)
	{
		//今は押してて、前回は押してない
		if (IsMouseButton(buttonCode) && !(prevMouseState_.rgbButtons[buttonCode] & 0x80))
		{
			return true;
		}
		return false;
	}

	//マウスのボタンを今放したか調べる
	bool IsMouseButtonUp(int buttonCode)
	{
		//今押してなくて、前回は押してる
		if (!IsMouseButton(buttonCode) && prevMouseState_.rgbButtons[buttonCode] & 0x80)
		{
			return true;
		}
		return false;
	}

	//マウスカーソルの位置を取得
	XMFLOAT3 GetMousePosition()
	{
		XMFLOAT3 result = XMFLOAT3((float)mousePos_.x, (float)mousePos_.y, 0);
		return result;
	}

	//マウスカーソルの位置をセット
	void SetMousePosition(int x, int y)
	{
		mousePos_.x = x;
		mousePos_.y = y;
		std::string result = "set mouse to " + std::to_string(x) + ", " + std::to_string(y) + "\n";
		OutputDebugString(result.c_str());
	}


	//そのフレームでのマウスの移動量を取得
	XMFLOAT3 GetMouseMove()
	{
		XMFLOAT3 result = XMFLOAT3((float)mouseState_.lX, (float)mouseState_.lY, (float)mouseState_.lZ);
		return result;
	}


	//解放
	void Release() {
		SAFE_RELEASE(pMouseDevice_);
		SAFE_RELEASE(pKeyDevice_);
		SAFE_RELEASE(pDInput_);
	}
}