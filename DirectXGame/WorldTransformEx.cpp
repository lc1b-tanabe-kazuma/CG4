#include <KamataEngine.h>

using namespace KamataEngine;
using namespace MathUtility;

void WorldTransform::UpdateMatrix() {
	// スケーリング行列
	Matrix4x4 matScale = MakeScaleMatrix(scale_);

	// X,Y,Z軸回りの回転行列
	Matrix4x4 matRotX = MakeRotateXMatrix(rotation_.x);
	Matrix4x4 matRotY = MakeRotateYMatrix(rotation_.y);
	Matrix4x4 matRotZ = MakeRotateZMatrix(rotation_.z);

	// 回転行列を合成
	Matrix4x4 matRot = matRotZ * matRotY * matRotX;

	// 平行移動行列
	Matrix4x4 matTrans = MakeTranslateMatrix(translation_);

	// ワールド行列の合成
	matWorld_ = matScale * matRot * matTrans;

	TransferMatrix();
}