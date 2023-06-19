#pragma once
#include <d3d11.h>
#include <string>
#include <wrl.h>

using namespace Microsoft::WRL;
using std::string;

class Texture {
	ID3D11SamplerState* pSampler_;
	ID3D11ShaderResourceView* pSRV_;

	size_t width_;		//横幅
	size_t height_;		//縦幅
	size_t depth_;		//奥行
public:
	Texture();
	~Texture();
	//画像の読み込み
	HRESULT Load(string fileName);
	//解放
	void Release();
	//サンプラーのゲッター
	ID3D11SamplerState* GetSampler() { return pSampler_; };
	//シェーダーリソースビューのゲッター
	ID3D11ShaderResourceView* GetSRV() { return pSRV_; };

	//横幅のゲッター
	size_t GetWidth() { return width_; };
	//縦幅のゲッター
	size_t GetHeight() { return height_; };
	//奥行のゲッター
	size_t GetDepth() { return depth_; };
};