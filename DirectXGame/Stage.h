#pragma once
#include "KamataEngine.h"
#include <random>
#include <vector>
using namespace KamataEngine;
#include "Player.h"

class Stage {
public:
	void Initialize();
	void Update();
	void Draw();

	// ヘルパー
	void SpawnSquare();

private:
	uint32_t backGroundTextureHandle_ = 0; // テクスチャハンドル
	Sprite* backGroundSprite_[2] = {nullptr, nullptr};
	float scrollSpeed_ = 2.0f; // スクロール速度
	float posX_[2] = {0.0f, 1280.0f};

	uint32_t slimeTextureHandle_ = 0; // テクスチャハンドル
	std::vector<std::unique_ptr<Sprite>> slimeSprite_;

	int spawnCount;
	int spawnTime;
};