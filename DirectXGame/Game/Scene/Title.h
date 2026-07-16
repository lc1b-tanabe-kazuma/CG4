#pragma once
#include "KamataEngine.h"
#include "SceneBase.h"
#include "UI/Aim.h"

class Title : public SceneBase {
public:
	Title(KamataEngine::Input* input) : SceneBase(input) {}

	// 初期化
	void Initialize() override;

	// 更新
	void Update() override;

	// 描画
	void Draw() override;

	~Title() override;

private:
	KamataEngine::Camera camera_;
	uint32_t UI_spaceTH;
	KamataEngine::Sprite* UI_space;
	uint32_t UI_titleTH;
	KamataEngine::Sprite* UI_title;

	Aim* aim_ = nullptr;
	KamataEngine::Model* model_ = nullptr;
	KamataEngine::WorldTransform worldTransform_;

	void UpdateUI();
};