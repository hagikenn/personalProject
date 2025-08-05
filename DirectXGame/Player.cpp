#include "Player.h"


void Player::Initialize(const std::string& modelName) {
    model_ = Model::CreateFromOBJ(modelName, false); 
    worldtransform.Initialize();

	// Y=0までジャンプできる初速を計算
	jumpPower = std::sqrt(-2.0f * gravity * (0.0f - ground[1]));

	 // プレイヤーの初期位置を X = groundX(-30.0f),y = groundY(-13.0f)に設定
	worldtransform.translation_.x = ground[0];
	worldtransform.translation_.y = ground[1]; 
}

void Player::Update() {
  
    // worldtransformの座標を右に移動
    worldtransform.translation_.x += moveSpeed;
	// worldtransformの座標がX=30を超えたら、X=0に戻す
	if (worldtransform.translation_.x > 0.0f) {
		moveSpeed = 0.0f; // 移動速度を0にする
	}

    // スペースキーでジャンプ（地面にいる時のみ）
	if (!isJumping && Input::GetInstance()->TriggerKey(DIK_SPACE)) {
		isJumping = true;
		velocityY = jumpPower;
	}

	// ジャンプ中の処理
	if (isJumping) {
		worldtransform.translation_.y += velocityY;
		velocityY += gravity;

		// 地面に着地したらジャンプ終了
		if (worldtransform.translation_.y <= ground[1]) {
			worldtransform.translation_.y = ground[1];
			isJumping = false;
			velocityY = 0.0f;
		}
	}

    // 行列更新
    worldtransform.UpdateMatrix();
}

void Player::Draw(Camera& camera) {
    
     model_->Draw(worldtransform, camera);
    
}

