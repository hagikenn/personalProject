#include "TitleScene.h"
#include <cmath>
#include <numbers>

// TitleScene.cpp
// タイトルシーンの実装。
// モデル読み込み・初期配置・更新（アニメーション、入力、フェード）・描画を行う。

TitleScene::~TitleScene() { 
	// 動的確保したリソースの解放
	delete modelPlayer_;
	delete modelTitle_;
	delete fade_;
}

void TitleScene::Initialize() {

	// スプライト用テクスチャをロード（ファイル名はプロジェクトに合わせて変更）
	titleTextureHandle_ = TextureManager::Load("../Resources/title.png");
	// 画面中心に生成（画面サイズに合わせて調整）
	titleSprite_ = Sprite::Create(titleTextureHandle_, {0.0f, 0.0f});

	

	// ビュー射影行列の初期化（カメラ行列等）
	camera_.Initialize();

	// タイトルのスケールを設定（そのままの大きさ）
	const float kPlayerTitle = 1.0f;
	worldTransformTitle_.Initialize();
	worldTransformTitle_.scale_ = {kPlayerTitle, kPlayerTitle, kPlayerTitle};

	// プレイヤー表示用ワールド（タイトル画面上のオブジェクト）
	const float kPlayerScale = 10.0f;
	worldTransformPlayer_.Initialize();
	worldTransformPlayer_.scale_ = {kPlayerScale, kPlayerScale, kPlayerScale};

	// プレイヤーはY軸回転で向きを設定（初期角度）
	worldTransformPlayer_.rotation_.y = 0.95f * std::numbers::pi_v<float>;

	// プレイヤーの表示位置（タイトル画面上の配置）
	worldTransformPlayer_.translation_.x = -2.0f;
	worldTransformPlayer_.translation_.y = -10.0f;

	// フェード（画面遷移用）を生成・初期化
	fade_ = new Fade();
	fade_->Initialize();
	// タイトル開始時にフェードインさせる（1秒）
	fade_->Start(Fade::Status::FadeIn, 1);
}

void TitleScene::Update() {

	// SPACEキーが押されたらフェードアウトを開始（ゲームシーンへ遷移する合図）
	if (Input::GetInstance()->PushKey(DIK_SPACE)) {
		fade_->Start(Fade::Status::FadeOut, 1);
	}

	// フェードアウトが終了したらシーン終了フラグを立てる（呼び出し元でシーン切替）
	if (fade_->IsFadeOutFinished() == true) {
		finished_ = true;
	}

	
		
	titleSprite_->SetPosition({0.0f, 0.0f});
	

	// フェード更新（内部で時間経過処理を行う）
	fade_->Update();
}

void TitleScene::Draw() {

	// DirectX 共通インスタンス（コマンドリスト取得のため）
	DirectXCommon* dxCommon_ = DirectXCommon::GetInstance();

	// 描画コマンドリストを取得
	ID3D12GraphicsCommandList* commandList = dxCommon_->GetCommandList();

	// スプライト描画（タイトルスプライト・フェードなど）
	Sprite::PreDraw(commandList);
	if (titleSprite_)
		titleSprite_->Draw();
	fade_->Draw(commandList);
	Sprite::PostDraw();

	// フェードはスプライト等で描画されるため、コマンドリストを渡して描画
	fade_->Draw(commandList);
}
