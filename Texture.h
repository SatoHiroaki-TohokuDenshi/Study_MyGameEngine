#pragma once
#include <d3d11.h>
#include <string>
#include <wrl.h>

using namespace Microsoft::WRL;
using std::string;

class Texture
{
	ID3D11SamplerState* pSampler_;
	ID3D11ShaderResourceView* pSRV_;
public:
	Texture();
	~Texture();
	//ファイルの読み込み
	HRESULT Load(string filename);
	//開放
	void Release();
	ID3D11SamplerState* GetSampler() { return pSampler_; }
	ID3D11ShaderResourceView* GetSRV() { return pSRV_; }
};