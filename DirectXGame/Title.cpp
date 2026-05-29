#include "Title.h"
#include "Math.h"
#include "SceneManager.h"
#include "imgui.h"

using namespace std;
using namespace KamataEngine;

void Title::Initialize() {}

void Title::Update() {

	// Spaceキーが押されたらシーンを"Game"に変更
	if (input_->TriggerKey(DIK_SPACE)) {
		SceneManager::GetInstance()->ChangeScene("Game");
	}

#ifdef DEBUG
	// ImGui
	ImGui::Begin("Title");
	ImGui::Text("Title Scene");
	ImGui::End();
#endif // DEBUG
}

void Title::Finalize() {}

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

	// UI描画後処理
	Sprite::PostDraw();
}

Title::~Title() {}