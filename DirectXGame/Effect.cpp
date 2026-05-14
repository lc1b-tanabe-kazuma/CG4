#define NOMINMAX

#include "Effect.h"
#include "MyMath.h"
#include <imgui.h>
#include <random>

using namespace KamataEngine;

void Effect::Initialize(Camera* camera) {

	camera_ = camera;

	// モデル生成
	model_ = Model2::CreateDiamond();

	// ワールド変換
	worldTransform_.Initialize();

	// 乱数エンジン
	std::random_device seedGenerator;
	std::mt19937_64 randomEngine;
	randomEngine.seed(seedGenerator());

	std::uniform_real_distribution<float> randomRot(-0.3f, 5.3f);

	worldTransform_.rotation_ = {0.0f, 3.14f, randomRot(randomEngine)};

	worldTransform_.scale_ = {1.0f, 4.0f, 1.0f};

	worldTransform_.Initialize();
}

void Effect::Update() {

	// 時間経過
	lifeTimer_ += 1.0f / 30.0f;

	// 0～1
	alpha_ = 1.0f - (lifeTimer_ / lifeTime_);

	// 0未満防止
	alpha_ = std::max(alpha_, 0.0f);

	model_->SetAlpha(alpha_);

	// Rキーでリセット
	if (Input::GetInstance()->TriggerKey(DIK_R)) {

		lifeTimer_ = 0.0f;

		// 乱数エンジン
		std::random_device seedGenerator;
		std::mt19937_64 randomEngine;
		randomEngine.seed(seedGenerator());

		std::uniform_real_distribution<float> randomRot(-0.3f, 5.3f);

		worldTransform_.rotation_ = {0.0f, 3.14f, randomRot(randomEngine)};

		worldTransform_.scale_ = {1.0f, 4.0f, 1.0f};
	}

	// 行列更新
	WorldTransformUpdate(worldTransform_);

	// Imguiの表示
#ifdef _DEBUG
	ImGui::Begin("effect");
	ImGui::DragFloat3("translation", &worldTransform_.translation_.x, 0.01f);
	ImGui::DragFloat3("rotation", &worldTransform_.rotation_.x, 0.01f);
	ImGui::End();
#endif
}

void Effect::Draw() { model_->Draw(worldTransform_, *camera_); }

void Effect::SetPosition(const Vector3& position) { worldTransform_.translation_ = position; }

void Effect::AddRotationZ(float angle) { worldTransform_.rotation_.z += angle; }