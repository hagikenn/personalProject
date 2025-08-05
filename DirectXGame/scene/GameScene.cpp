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
    player_->Initialize("cube");

	stage_ = new Stage();
	stage_->Initialize();

	camera_.Initialize();
}

void GameScene::Update() {
	// 自キャラの更新
	player_->Update();
	// ステージの更新
	stage_->Update();
	// カメラの更新
	camera_.Map();
}

void GameScene::Draw() {
	// DirectXCommonインスタンスの取得
	DirectXCommon* dxCommon = DirectXCommon::GetInstance();

	// 2D描画前処理
	Sprite::PreDraw(dxCommon->GetCommandList());
	//stage_->Draw();
	// 2D描画後処理
	Sprite::PostDraw();

	// 深度バッファクリア
	dxCommon->ClearDepthBuffer();

	// 3Dモデル描画前処理
	Model::PreDraw();
	player_->Draw(camera_);
	// 3Dモデル描画後処理
	Model::PostDraw();
}
