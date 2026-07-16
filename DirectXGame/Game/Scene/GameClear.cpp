#include "Scene/GameClear.h"
#include "MyMath.h"
#include "SceneManager.h"
#include "imgui.h"

using namespace std;
using namespace KamataEngine;

void GameClear::Initialize() {
	// UI
	UI_spaceTH = TextureManager::Load("UI/UI_space.png");
	UI_space = Sprite::Create(UI_spaceTH, Vector2(600, 550));
	UI_space->SetSize({512.0f, 256.0f});
	UI_space->SetAnchorPoint({0.5f, 0.5f});

	UI_scoreTH = TextureManager::Load("UI/UI_score.png");
	UI_score = Sprite::Create(UI_scoreTH, Vector2(600, 150));
	UI_score->SetSize({512.0f, 256.0f});
	UI_score->SetAnchorPoint({0.5f, 0.5f});

	// 数字描画の初期化
	drawNumber_ = new DrawNumber();
	drawNumber_->Initialize(TextureManager::Load("number.png"), Vector2(600, 350));

	score_ = SceneManager::GetInstance()->GetScore();
}

void GameClear::Update() {

	// Spaceキーが押されたらシーンを"Title"に変更
	if (input_->TriggerKey(DIK_SPACE)) {
		SceneManager::GetInstance()->ChangeScene("Title");
	}

	// UIの更新
	UpdateUI();

	// 数字描画の更新
	drawNumber_->Update(static_cast<int>(score_));

#ifdef DEBUG
	// ImGui
	ImGui::Begin("Title");
	ImGui::Text("Title Scene");
	ImGui::End();
#endif // DEBUG
}

void GameClear::UpdateUI() {
	// UIを点滅させる
	static float alpha = 1.0f;    // アルファ値
	static bool fadingOut = true; // フェードアウト中かどうか
	if (fadingOut) {
		alpha -= 0.01f; // アルファ値を減少
		if (alpha <= 0.0f) {
			alpha = 0.0f;
			fadingOut = false; // フェードインに切り替え
		}
	} else {
		alpha += 0.01f; // アルファ値を増加
		if (alpha >= 1.0f) {
			alpha = 1.0f;
			fadingOut = true; // フェードアウトに切り替え
		}
	}
	UI_space->SetColor({1.0f, 1.0f, 1.0f, alpha});
}

void GameClear::Draw() {

	// コマンドリストの取得
	DirectXCommon* dxCommon_ = DirectXCommon::GetInstance();
	ID3D12GraphicsCommandList* commandList = dxCommon_->GetCommandList();

	// UI描画前処理
	Sprite::PreDraw(commandList);

	UI_space->Draw();

	UI_score->Draw();

	// 数字描画
	drawNumber_->Draw();

	// UI描画後処理
	Sprite::PostDraw();
}

GameClear::~GameClear() {
	delete UI_space;
	delete drawNumber_;
}