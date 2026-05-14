#pragma once
#include "KamataEngine.h"
#include "Model2/Model2.h"

class Effect {
public:
	// 初期化
	void Initialize(KamataEngine::Camera* camera);

	// 更新
	void Update();

	// 描画
	void Draw();

	// 座標設定
	void SetPosition(const KamataEngine::Vector3& position);

	void AddRotationZ(float angle);

private:
	// ワールド変換
	KamataEngine::WorldTransform worldTransform_;

	// モデル
	KamataEngine::Model2* model_ = nullptr;

	// 色
	KamataEngine::Vector4 color_ = {1, 1, 1, 1};

	// カメラ
	KamataEngine::Camera* camera_ = nullptr;
};