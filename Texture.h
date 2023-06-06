#pragma once
#include <d3d11.h>
#include <string>
#include <wrl.h>

using namespace Microsoft::WRL;
using std::string;

class Texture {
	ID3D11SamplerState* pSampler_;
	ID3D11ShaderResourceView* pSRV_;
public:
	Texture();
	~Texture();
	//‰æ‘œ‚Ì“Ç‚İ‚İ
	HRESULT Load(string fileName);
	//‰ğ•ú
	void Release();
};