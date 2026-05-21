#include "Particle.h"
#include "MyMath.h"
#include <cassert>

using namespace MathUtility;

void Particle::Initialize(Model* model,Vector3 pos) {

	// モデルのセット
	assert(model);
	model_ = model;

	// ワールドトランスフォームの初期化
	worldTransform_.Initialize();
	worldTransform_.translation_ = pos;

	// 色の設定
	objectColor_.Initialize();
	color_ = {1, 1, 0, 1};
}

void Particle::Update() {

	// 色を変更
	objectColor_.SetColor(color_);

	worldTransform_.translation_.y += 0.1f;

	// ワールドトランスフォームの更新
	WorldTransformUpdate(worldTransform_);
}

void Particle::Draw(const Camera& camera) {

	// 描画
	model_->Draw(worldTransform_, camera, &objectColor_);
}