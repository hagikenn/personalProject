#pragma once
#include "KamataEngine.h"
using namespace KamataEngine;

class Stage {
public:
	void Initialize();
	void Update();
	void Draw();

private:
	WorldTransform worldTransform_;
	uint32_t textureHandle_ = 0;         // テクスチャハンドル
	Sprite* sprite_[2] = {nullptr,nullptr};
	float scrollSpeed_ = 2.0f;           // スクロール速度
	float posX_[2] = {0.0f,1280.0f};

};