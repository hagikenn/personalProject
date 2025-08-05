//#include"MathUtilityForText.h"
//#include"WorldTransform.h"
#include <KamataEngine.h>

using namespace KamataEngine;
using namespace MathUtility;

void WorldTransform::UpdateMatrix() {
	////スケール、回転、平行移動を合成して行列を計算する
	//matWorld_ = MakeAffineMatrix(scale_, rotation_, translation_);

	//　スケーリング行列の作成
	Matrix4x4 matScale = MakeScaleMatrix(scale_);

	// 　回転行列の作成
	Matrix4x4 matRotX = MakeRotateXMatrix(rotation_.x);
	Matrix4x4 matRotY = MakeRotateYMatrix(rotation_.y);
	Matrix4x4 matRotZ = MakeRotateZMatrix(rotation_.z);
	Matrix4x4 matRot = matRotZ * matRotY * matRotX;

	// 　平行移動行列の作成
	Matrix4x4 matTrans = MakeTranslateMatrix(translation_);

	// スケーリング、回転、平行移動を合成して行列を計算する
	matWorld_ = matScale * matRot * matTrans;

	//定数バッファに転送する
	TransferMatrix();
}