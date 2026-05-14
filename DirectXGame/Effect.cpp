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

	// 裏側に回転する
	worldTransform_.rotation_.y = 3.141592654f;

	// スケールを大きくする
	worldTransform_.scale_ = {5.0f, 5.0f, 5.0f};

	// 乱数エンジン
	std::random_device seedGen;
	std::mt19937 engine(seedGen());

	// スケール用
	static std::uniform_real_distribution<float> scaleDist(1.0f, 5.0f);

	// 回転用
	static std::uniform_real_distribution<float> rotDist(0.0f, 3.141592654f);

	worldTransform_.scale_ = {scaleDist(engine), scaleDist(engine), scaleDist(engine)};
	worldTransform_.rotation_ = {rotDist(engine), rotDist(engine) + 2.5f, rotDist(engine)};
}

void Effect::Update() {

	// Rキーでリセット
	if (Input::GetInstance()->TriggerKey(DIK_R)) {

		// 乱数エンジン
		std::random_device seedGen;
		std::mt19937 engine(seedGen());

		// スケール用
		static std::uniform_real_distribution<float> scaleDist(1.0f, 5.0f);

		// 回転用
		static std::uniform_real_distribution<float> rotDist(0.0f, 3.141592654f);
		worldTransform_.scale_ = {scaleDist(engine), scaleDist(engine), scaleDist(engine)};

		worldTransform_.rotation_ = {rotDist(engine), rotDist(engine) + 2.5f, rotDist(engine)};
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