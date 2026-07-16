#include "Enemy/Enemy.h"
#include "MyMath.h"
using namespace KamataEngine;

void Enemy::Initialize(Model* model, Vector3 position) {
	model_ = model;
	worldTransform_.Initialize();
	worldTransform_.translation_ = position;
	worldTransform_.rotation_.y = 3.14159265f / -2.0f; // 180度回転させる
	worldTransform_.scale_ = {0.75f, 0.75f, 0.75f};   // スケールを半分にする
}

void Enemy::Update() {
	if (isDead_) {
		return;
	}
	worldTransform_.translation_.x -= 0.05f;

	WorldTransformUpdate(worldTransform_);

	if (worldTransform_.translation_.x <= -30.0f) {
		isDead_ = true;
	}
}

void Enemy::Draw(const KamataEngine::Camera& camera) {
	if (isDead_) {
		return;
	}
	model_->Draw(worldTransform_, camera);
}

Vector3 Enemy::GetPosition() const { // ワールド座標を入れる変数
	Vector3 worldPos;
	// ワールド行列の平行移動成分を取得（ワールド座標）
	worldPos.x = worldTransform_.matWorld_.m[3][0];
	worldPos.y = worldTransform_.matWorld_.m[3][1];
	worldPos.z = worldTransform_.matWorld_.m[3][2];
	return worldPos;
}

void Enemy::OnCollision() { isDead_ = true; }