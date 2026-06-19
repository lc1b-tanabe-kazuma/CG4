#include "Player.h"
#include "MyMath.h"
using namespace KamataEngine;

void Player::Initialize(Model* model, Camera* camera) {
	model_ = model;
	camera_ = camera;

	// ワールドトランスフォームの初期化
	worldTransform_.Initialize();
	worldTransform_.translation_ = {0, 0, 0};
	worldTransform_.scale_ = {2.5f, 2.5f, 2.5f};
	worldTransform_.rotation_.y = -3.14f;

	input_ = Input::GetInstance();
}

void Player::Update() { Move(); }

void Player::Draw() { model_->Draw(worldTransform_, *camera_); }

// 移動処理
void Player::Move() {
	if (input_->PushKey(DIK_W)) {
		worldTransform_.translation_.y += moveSpeed_;
	}

	if (input_->PushKey(DIK_S)) {
		worldTransform_.translation_.y -= moveSpeed_;
	}

	if (input_->PushKey(DIK_A)) {
		worldTransform_.translation_.x -= moveSpeed_;
	}

	if (input_->PushKey(DIK_D)) {
		worldTransform_.translation_.x += moveSpeed_;
	}

	if (input_->PushKey(DIK_A)) {
		worldTransform_.translation_.x -= moveSpeed_;
	}

	// ワールド変換行列の更新
	WorldTransformUpdate(worldTransform_);
}

Vector3 Player::GetWorldPosition() const { return worldTransform_.translation_; }