#include "GameScene.h"
#include <cassert>
#include <math.h>

GameScene::GameScene() {}

GameScene::~GameScene() {
	// 自キャラの開放
	delete player_;
	//ステージの開放
	delete stage_;
	delete model_;
}



void GameScene::Initialize() {  
    dxCommon_ = DirectXCommon::GetInstance();  
    input_ = Input::GetInstance();  
    audio_ = Audio::GetInstance();  

    // 自キャラの生成  
    player_ = new Player();  
    // 自キャラの初期化  
    player_->Initialize("player");

	stage_ = new Stage();
	stage_->Initialize();

	camera_.Initialize();

	mapChip_.Initialize();
	// マップの大きさ取得
	Vector2 mapSize = mapChip_.GetMaxMapSize();
	// 画面中央に置きたい場合（例：画面中心が(0,0)なら左下を -mapSize/2 する）
	mapChip_.SetOrigin(Vector2{-mapSize.x / 2.0f, -mapSize.y / 2.0f});
}

void GameScene::Update() {
	// 自キャラの更新
	player_->Update();
	// ステージの更新
	stage_->Update();
	// マップチップの更新
	mapChip_.Update();
	// カメラの更新
	camera_.Map();

	//Vector3 playerPos = player_->GetWorldTransform().translation_;
	//auto indexSet = mapChipField_.GetMapChipIndexSetByPosition(playerPos);
	//MapChipType type = mapChipField_.GetMapChipTypeByIndex(indexSet.xIndex, indexSet.yIndex);

	//if (type == MapChipType::kBlock) {
	//    // ブロック上にいる処理
	//}
}

void GameScene::Draw() {
	// DirectXCommonインスタンスの取得
	DirectXCommon* dxCommon = DirectXCommon::GetInstance();

	// 2D描画前処理
	Sprite::PreDraw(dxCommon->GetCommandList());
	stage_->Draw();
	// 2D描画後処理
	Sprite::PostDraw();

	// 深度バッファクリア
	dxCommon->ClearDepthBuffer();

	// 3Dモデル描画前処理
	Model::PreDraw();

	// マップチップの描画を追加
	mapChip_.Draw(&camera_);

	player_->Draw(camera_);
	// 3Dモデル描画後処理
	Model::PostDraw();
}

void GameScene::ChangePhase() {
	switch (phase_) {
	case Phase::kPlay:
		// プレイヤーが死亡したら死亡演出フェーズに遷移する
		if (player_->IsDead()) {
			// フェーズを死亡に切り替え
			phase_ = Phase::kDeath;
			// 自キャラの座標を取得して死亡演出の位置にする
			const Vector3& deathParticlesPosition = player_->GetWorldPosition();
			// 新しい死亡演出オブジェクトを生成して初期化する
			deathParticles_ = new DeathParticles;
			deathParticles_->Initialize(modelParticles_, &viewProjection_, deathParticlesPosition);
		}
		break;
	case Phase::kDeath:
		// 死亡演出が終了したらシーン終了フラグを立てる
		if (deathParticles_ && deathParticles_->IsFinished()) {
			finished_ = true;
		}
		break;
	}
}
