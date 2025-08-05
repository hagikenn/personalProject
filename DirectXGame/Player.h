#pragma once
#include <KamataEngine.h>
using namespace KamataEngine;


class Player {
public:
    // モデル名を指定して初期化
    void Initialize(const std::string& modelName);

    void Update();
    void Draw(Camera& camera);

private:
    Model* model_ = nullptr;
    WorldTransform worldtransform;
	Input* input_ = nullptr;

    // 右方向（+X軸）に進む速度
	float moveSpeed = 0.05f;

    // ジャンプ中かどうかを判定するフラグ（true:ジャンプ中, false:地面にいる状態）
    bool isJumping = false;
    // ジャンプ中のY軸方向の速度（毎フレーム加算される値、重力やジャンプ初速に利用）
    float velocityY = 0.0f;
	// ジャンプ初速
	float jumpPower = 2.0f; 
	// 重力加速度
	float gravity = -0.1f; 
	// 地面の高さ
	float ground[2] = {-30.0f,-13.0f,};
};