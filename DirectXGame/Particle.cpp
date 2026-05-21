#include "Particle.h"
#include <algorithm>
#include <cassert>

#define _USE_MATH_DEFINES

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

	// 終了なら何もしない
	if (isDead_) {
		return;
	}

	// 経過時間を更新
	counter_ += 1.0f / 60.0f;

	// 持続時間を超えたら終了
	if (counter_ >= lifeTime_) {
		counter_ = lifeTime_;
		isDead_ = true;
	}

	// フェードアウト
	color_.w = std::clamp(1.0f - counter_ / lifeTime_, 0.0f, 1.0f);

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