#include "Stage.h"
#include <algorithm>
#include <iostream>

void Stage::Initialize() {
	// テクスチャの読み込み
	backGroundTextureHandle_ = TextureManager::Load("background/starBG.png");
	// スプライトの生成
	backGroundSprite_[0] = Sprite::Create(backGroundTextureHandle_, {posX_[0], 0});
	backGroundSprite_[1] = Sprite::Create(backGroundTextureHandle_, {posX_[1], 0});

	//backGroundTextureHandle_ = TextureManager::Load("player_resource.png");
	std::unique_ptr<Sprite> newSlime = std::unique_ptr<Sprite>(Sprite::Create(slimeTextureHandle_, {0.0f, 0.0f}));
	slimeSprite_.push_back(std::move(newSlime));

	SpawnSquare();
}

void Stage::SpawnSquare() {}

void Stage::Update() {
	SpawnSquare();

	for (int i = 0; i < 2; i++) {
		posX_[i] -= scrollSpeed_;
		// 画面外に出たら右端に移動
		if (posX_[i] <= -1280.0f) {
			posX_[i] = posX_[(i + 1) % 2] + 1275.0f;
		}
		backGroundSprite_[i]->SetPosition({posX_[i], 0});
	}
}

void Stage::Draw() {

	backGroundSprite_[0]->Draw();
	backGroundSprite_[1]->Draw();
}