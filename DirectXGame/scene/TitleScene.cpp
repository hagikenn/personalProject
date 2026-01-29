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

	// タイトル用のモデルをOBJから読み込む（テクスチャ有無などはModel側に依存）
	modelTitle_ = Model::CreateFromOBJ("title", true);
	// プレイヤーモデルを読み込む（表示用）
	modelPlayer_ = Model::CreateFromOBJ("player");

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

	// タイトル上の時間管理（カウンタ更新）
	counter_ += 1.0f / 60.0f;
	// カウンタを周期で折り返す（オーバーフロー防止）
	counter_ = std::fmod(counter_, kTimeTitleMove);

	// タイトルの上下移動アニメーション（正弦波）
	float angle = counter_ / kTimeTitleMove * 2.0f * std::numbers::pi_v<float>;
	worldTransformTitle_.translation_.y = std::sin(angle) + 10.0f;

	// タイトル画面上のプレイヤーをゆっくり回転させる
	worldTransformPlayer_.rotation_.y += 0.05f;

	// ビュー射影行列をGPU用に転送（Model描画に必要）
	camera_.TransferMatrix();

	// ワールド行列を更新（描画で使う最終行列を生成）
	worldTransformTitle_.UpdateMatrix();
	worldTransformPlayer_.UpdateMatrix();

	// フェード更新（内部で時間経過処理を行う）
	fade_->Update();
}

void TitleScene::Draw() {

	// DirectX 共通インスタンス（コマンドリスト取得のため）
	DirectXCommon* dxCommon_ = DirectXCommon::GetInstance();

	// 描画コマンドリストを取得
	ID3D12GraphicsCommandList* commandList = dxCommon_->GetCommandList();

	// モデル描画の前処理（シェーダ・定数バッファ設定など）
	Model::PreDraw();

	// タイトルモデルを描画（ワールド行列とビュー射影を渡す）
	//modelTitle_->Draw(worldTransformTitle_, camera_);
	//// プレイヤーモデルを描画（タイトル画面内の飾りとして）
	//modelPlayer_->Draw(worldTransformPlayer_, camera_);

	// モデル描画の後処理（状態リセットなど）
	Model::PostDraw();

	// フェードはスプライト等で描画されるため、コマンドリストを渡して描画
	fade_->Draw(commandList);
}
