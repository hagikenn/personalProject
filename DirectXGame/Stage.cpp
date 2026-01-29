#include "Stage.h"
#include <algorithm>
#include <iostream>

void Stage::Initialize() {
	// ワールド変換の初期化
	worldTransform_.Initialize();
	// テクスチャの読み込み
	textureHandle_ = TextureManager::Load("background/starBG.png");
	// スプライトの生成
	sprite_[0] = Sprite::Create(textureHandle_, {posX_[0], 0});
	sprite_[1] = Sprite::Create(textureHandle_, {posX_[1], 0});

	// 四角用テクスチャ読み込み（例: 白い四角）
	squareTextureHandle_ = TextureManager::Load("white1x1.png");

	// 乱数分布初期化（interval分布はメンバで宣言済みだが初期next値を作る）
	nextSpawnFrames_ = distInterval_(rng_);

}

void Stage::SpawnSquare() {
	if (static_cast<int>(squares_.size()) >= maxSquares_)
		return;

	if (squareTextureHandle_ == 0) {
		std::cout << "squareTextureHandle_ is 0. texture load failed?" << std::endl;
		return;
	}

	// 生成Xは画面右端外側に固定（画面幅に合わせて調整）
	const float spawnX = 1280.0f + 50.0f;
	// Yはランダム
	const float spawnY = distY_(rng_);

	Sprite* s = Sprite::Create(squareTextureHandle_, {spawnX, spawnY});
	if (!s) {
		std::cout << "Sprite::Create returned nullptr" << std::endl;
		return;
	}

	Square sq;
	sq.sprite = s;
	sq.x = spawnX;
	sq.y = spawnY;

	squares_.push_back(sq);
	std::cout << "Spawned square at (" << sq.x << ", " << sq.y << "), total: " << squares_.size() << std::endl;
}

void Stage::Update() {

	/*for (player_->Update();) {*/
		// 2枚とも左に動かす
		for (int i = 0; i < 2; i++) {
			posX_[i] -= scrollSpeed_;
			// 画面外に出たら右端に移動
			if (posX_[i] <= -1280.0f) {
				posX_[i] = posX_[(i + 1) % 2] + 1275.0f;
			}
			sprite_[i]->SetPosition({posX_[i], 0});
		}
	/*}*/

		// --- 四角の移動と削除 ---
	    for (auto it = squares_.begin(); it != squares_.end();) {
		    it->x -= squareSpeed_;
		    // スプライトの位置更新
		    if (it->sprite) {
			    it->sprite->SetPosition({it->x, it->y});
		    }

		    // 画面左に出たら削除（閾値はテクスチャ幅に合わせて調整）
		    if (it->x < -200.0f) {
			    if (it->sprite) {
				    delete it->sprite;
				    it->sprite = nullptr;
			    }
			    it = squares_.erase(it);
		    } else {
			    ++it;
		    }
	    }

		// --- 出現タイマー（ランダム間隔） ---
		spawnTimer_++;
		if (spawnTimer_ >= nextSpawnFrames_) {
			SpawnSquare();
			spawnTimer_ = 0;
			// 次の出現間隔をランダムに決定
			nextSpawnFrames_ = distInterval_(rng_);
		}

		//（デバッグ）現在の生成数を出力（多すぎるとログがうるさくなるので適宜コメントアウト）
		std::cout << "Squares count: " << squares_.size() << std::endl;
}

void Stage::Draw() {
	
	/*sprite_[0]->Draw();
	sprite_[1]->Draw();*/

	// 四角描画
	for (const auto& sq : squares_) {
		
		if (sq.sprite)
			sq.sprite->Draw();
	}

}

