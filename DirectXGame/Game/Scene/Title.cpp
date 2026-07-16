#include "Title.h"
#include "MyMath.h"
#include "SceneManager.h"
#include "imgui.h"

using namespace std;
using namespace KamataEngine;

void Title::Initialize() {
	// UI
	UI_spaceTH = TextureManager::Load("UI/UI_space.png");
	UI_space = Sprite::Create(UI_spaceTH, Vector2(600, 550));
	UI_space->SetSize({512.0f, 256.0f});
	UI_space->SetAnchorPoint({0.5f, 0.5f});

	// UI
	UI_titleTH = TextureManager::Load("UI/UI_title.png");
	UI_title = Sprite::Create(UI_titleTH, Vector2(600, 0.0f));
	UI_title->SetSize({512.0f, 256.0f});
	UI_title->SetAnchorPoint({0.5f, 0.5f});

	// エイムの初期化
	aim_ = new Aim();
	aim_->Initialize(&camera_);

	// モデルの初期化
	model_ = Model::CreateFromOBJ("enemy", true);

	worldTransform_.Initialize();
	worldTransform_.translation_ = {0.0f, -1.0f, 0.0f};
	worldTransform_.scale_ = {1.5f, 1.5f, 1.5f};
	worldTransform_.rotation_.y = 3.14f / 2.0f;

	camera_.Initialize();
}

void Title::Update() {

	// Spaceキーが押されたらシーンを"Game"に変更
	if (input_->TriggerKey(DIK_SPACE)) {
		SceneManager::GetInstance()->ChangeScene("Game");
	}

	aim_->Updeta();

	// UIの更新
	UpdateUI();

	//
	worldTransform_.rotation_.y += 0.01f;

	WorldTransformUpdate(worldTransform_);
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

	model_->Draw(worldTransform_, camera_);

	// 3Dモデル描画後処理
	Model::PostDraw();

	// UI描画前処理
	Sprite::PreDraw(commandList);

	UI_space->Draw();
	UI_title->Draw();

	aim_->Draw();

	// UI描画後処理
	Sprite::PostDraw();
}

Title::~Title() {
	delete aim_;
	delete model_;
}

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

	if (UI_title->GetPosition().y < 150.0f) {
		UI_title->SetPosition({600.0f, UI_title->GetPosition().y + 0.5f});
	}
}