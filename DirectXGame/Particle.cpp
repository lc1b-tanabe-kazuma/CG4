#include "Particle.h"
#include <cassert>

using namespace MathUtility;

void Particle::Initialize(Model* model, Vector3 pos, Vector3 velocity) {

	// モデルのセット
	assert(model);
	model_ = model;

	// ワールドトランスフォームの初期化
	worldTransform_.Initialize();
	worldTransform_.translation_ = pos;
	worldTransform_.scale_ = {0.2f, 0.2f, 0.2f};

	// 色の設定
	objectColor_.Initialize();
	color_ = {1, 1, 0, 1};

	// 速度の設定
	velocity_ = velocity;
}

void Particle::Update() {

	// 色を変更
	objectColor_.SetColor(color_);

	worldTransform_.translation_ += velocity_;

	// ワールドトランスフォームの更新
	worldTransform_.UpdateMatrix();
}

void Particle::Draw(const Camera& camera) {

	// 描画
	model_->Draw(worldTransform_, camera, &objectColor_);
}

bool Particle::IsDead() const { return isDead_; }