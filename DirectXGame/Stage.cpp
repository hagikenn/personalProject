#include "Stage.h"

void Stage::Initialize() {
	// ワールド変換の初期化
	worldTransform_.Initialize();
	// テクスチャの読み込み
	textureHandle_ = TextureManager::Load("background/starBG.png");
	// スプライトの生成
	sprite_[0] = Sprite::Create(textureHandle_, {posX_[0], 0});
	sprite_[1] = Sprite::Create(textureHandle_, {posX_[1], 0});
}

void Stage::Update() {
	// 2枚とも左に動かす
	for (int i = 0; i < 2; i++) {
		posX_[i] -= scrollSpeed_;
		// 画面外に出たら右端に移動
		if (posX_[i] <= -1280.0f) {
			posX_[i] = posX_[(i + 1) % 2] + 1275.0f;
		}
		sprite_[i]->SetPosition({posX_[i], 0});
	}
}

void Stage::Draw() {
	
	sprite_[0]->Draw();
	sprite_[1]->Draw();


}