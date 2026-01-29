#pragma once
#include "KamataEngine.h"
#include <vector>
#include <random>
using namespace KamataEngine;
#include"Player.h"

class Stage {
public:
	void Initialize();
	void Update();
	void Draw();

	// ヘルパー
	void SpawnSquare();

private:
	WorldTransform worldTransform_;
	uint32_t textureHandle_ = 0;         // テクスチャハンドル
	Sprite* sprite_[2] = {nullptr,nullptr};
	float scrollSpeed_ = 2.0f;           // スクロール速度
	float posX_[2] = {0.0f,1280.0f};

	Player* player_ = nullptr;

	// --- 追加: 四角(障害物)生成関連 ---
	uint32_t squareTextureHandle_ = 0; // 四角用テクスチャ
	struct Square {
		Sprite* sprite = nullptr;
		float x = 0.0f;
		float y = 0.0f;
	};
	std::vector<Square> squares_;

	// タイマー・生成設定
	int spawnTimer_ = 0;         // 経過フレーム
	int nextSpawnFrames_ = 60;   // 次の出現までのフレーム（ランダムで更新）
	int spawnIntervalMin_ = 30;  // 最短間隔（フレーム）
	int spawnIntervalMax_ = 180; // 最長間隔（フレーム）
	int maxSquares_ = 50;        // 最大生成数
	float squareSpeed_ = 3.0f;   // 四角の移動速度（左方向）

	// 乱数
	std::mt19937 rng_{std::random_device{}()};
	std::uniform_real_distribution<float> distY_{0.0f, 720.0f}; // 生成Y範囲（画面高さに合わせて調整）
	std::uniform_int_distribution<int> distInterval_{spawnIntervalMin_, spawnIntervalMax_};

	

};