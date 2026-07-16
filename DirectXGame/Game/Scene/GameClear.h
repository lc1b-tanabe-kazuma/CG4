#pragma once
#include "KamataEngine.h"
#include "SceneBase.h"

class GameClear : public SceneBase {
public:
	GameClear(KamataEngine::Input* input) : SceneBase(input) {};

	// 初期化
	void Initialize() override;

	// 更新
	void Update() override;

	// 描画
	void Draw() override;

	~GameClear() override;

private:
	KamataEngine::Camera camera_;
	uint32_t UI_spaceTH;
	KamataEngine::Sprite* UI_space;

	void UpdateUI();
};