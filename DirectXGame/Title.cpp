#include "Title.h"
#include "Math.h"
#include "SceneManager.h"
#include "imgui.h"

using namespace std;
using namespace KamataEngine;

void Title::Initialize() {
	// UI
	UI_spaceTH = TextureManager::Load("UI/UI_space.png");
	UI_space = Sprite::Create(UI_spaceTH, Vector2(600, 450));
	UI_space->SetSize({512.0f, 256.0f});
	UI_space->SetAnchorPoint({0.5f, 0.5f});
}

void Title::Update() {

	// Spaceキーが押されたらシーンを"Game"に変更
	if (input_->TriggerKey(DIK_SPACE)) {
		SceneManager::GetInstance()->ChangeScene("Game");
	}

	// UIの更新
	UpdateUI();

#ifdef DEBUG
	// ImGui
	ImGui::Begin("Title");
	ImGui::Text("Title Scene");
	ImGui::End();
#endif // DEBUG
}

void Title::Draw() {
	// コマンドリストの取得
	DirectXCommon* dxCommon_ = DirectXCommon::GetInstance();
	ID3D12GraphicsCommandList* commandList = dxCommon_->GetCommandList();

	// タイトルシーンの描画
	Model::PreDraw();

	// 3Dモデル描画後処理
	Model::PostDraw();

	// UI描画前処理
	Sprite::PreDraw(commandList);

	UI_space->Draw();

	// UI描画後処理
	Sprite::PostDraw();
}

Title::~Title() {}

void Title::UpdateUI() {
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