#define NOMINMAX

#include "Efect/Effect.h"
#include "MyMath.h"
#include <imgui.h>
#include <numbers>
#include <random>

using namespace KamataEngine;

void Effect::Initialize(Camera* camera, const Vector4& color) {

	camera_ = camera;

	// モデル生成
	model_ = Model2::CreateDiamond();

	// ワールド変換
	worldTransform_.Initialize();

	// 色
	color_.Initialize();
	color_.SetColor(color);

	// 乱数エンジン
	static std::mt19937 engine(std::random_device{}());

	// 回転
	std::uniform_real_distribution<float> randomRot(-std::numbers::pi_v<float>, std::numbers::pi_v<float>);

	// 長さ
	std::uniform_real_distribution<float> scaleY(2.0f, 12.0f);

	// 太さ
	std::uniform_real_distribution<float> scaleX(0.05f, 0.7f);

	// 寿命
	std::uniform_real_distribution<float> lifeDist(0.3f, 2.0f);

	// 初期タイマー
	std::uniform_real_distribution<float> timerDist(0.0f, 1.0f);

	// 回転ランダム
	worldTransform_.rotation_ = {0.0f, 3.14f, randomRot(engine)};

	// サイズランダム
	worldTransform_.scale_ = {scaleX(engine), scaleY(engine), 1.0f};

	// 寿命ランダム
	lifeTime_ = lifeDist(engine);

	// 時間をズラす
	lifeTimer_ = timerDist(engine) * lifeTime_;

	// 初期アルファ
	alpha_ = 1.0f;

	// 死亡フラグ
	isDead_ = false;
}

void Effect::Update() {

	// 時間更新
	lifeTimer_ += 1.0f / 30.0f;

	// 進行率
	float t = lifeTimer_ / lifeTime_;

	// フェード
	alpha_ = 1.0f - t / 3.0f;

	// 0未満防止
	alpha_ = std::max(alpha_, 0.0f);

	// 色反映
	Vector4 color = color_.GetColor();
	color.w = alpha_;
	color_.SetColor(color);

	// 少し縮小
	worldTransform_.scale_.y *= 0.95f;

	// 寿命
	if (lifeTimer_ >= lifeTime_) {
		isDead_ = true;
	}

	// 行列更新
	WorldTransformUpdate(worldTransform_);
}

void Effect::Draw() { model_->Draw(worldTransform_, *camera_, &color_); }

void Effect::SetPosition(const Vector3& position) {

	worldTransform_.translation_ = position;

	// 行列更新
	WorldTransformUpdate(worldTransform_);
}

void Effect::AddRotationZ(float angle) {

	worldTransform_.rotation_.z += angle;

	// 行列更新
	WorldTransformUpdate(worldTransform_);
}

Effect::~Effect() {

	delete model_;
	model_ = nullptr;
}