#pragma once
#include "KamataEngine.h"
#include "SceneBase.h"
#include "UI/DrawNumber.h"

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

	uint32_t UI_scoreTH;
	KamataEngine::Sprite* UI_score;

	// 数字描画
	DrawNumber* drawNumber_;
	uint32_t numberTH_ = 0;

	int score_;

	void UpdateUI();
};