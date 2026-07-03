#include "GameScene.h"
#include "SceneManager.h"
#include <imgui.h>
#include <random>

using namespace KamataEngine;
using namespace MathUtility;

std::random_device rd;
std::mt19937 randomEngine(rd());
std::uniform_real_distribution<float> distribution(-1.0f, 1.0f);

void GameScene::Initialize() {
	// テクスチャーインスタンスの作成
	textureHandle_ = TextureManager::Load("uvChecker.png");

	// カメラの初期化
	camera_.Initialize();

	modelParticle_->StaticInitialize();
	modelParticle_ = Model::CreateSphere(4, 4);

	//
	worldTransform_.Initialize();

	// プレイヤーの初期化
	player_ = new Player();
	modelPlayer_ = Model::CreateFromOBJ("player", true);
	modelBullet_ = Model::CreateFromOBJ("playerBullet", true);
	player_->Initialize(modelPlayer_, &camera_, modelBullet_);

	// エイムの初期化
	aim_ = new Aim();
	aim_->Initialize(&camera_);

	// 乱数の初期化
	srand((unsigned int)time(nullptr));

	// ステージの初期化
	stage_ = new Stage();
	stage_->Initialize();

	// UIの初期化
	HPTH_ = TextureManager::Load("white1x1.png");
	spriteHP_ = Sprite::Create(HPTH_, posHP_);
	spriteHP2_ = Sprite::Create(HPTH_, posHP_);
	spriteHP_->SetSize(sizeHP_);
	spriteHP2_->SetSize(sizeHP_);
	spriteHP_->SetColor({1.0f, 0.0f, 0.0f, 0.5f});  // 赤色で半透明
	spriteHP2_->SetColor({0.0f, 1.0f, 0.0f, 0.5f}); // 緑色で半透明

	// 数字描画の初期化
	drawNumber_ = new DrawNumber();
	drawNumber_->Initialize(TextureManager::Load("number.png"));
}

void GameScene::Update() {

	// タイマーの更新
	timer_ += 1.0f / 60.0f;

	// ステージの更新
	stage_->Update();

	// エイムの更新
	aim_->Updeta();

	if (aim_->IsAttac()) {
		Vector3 worldPos = GetMouseWorldPosition();

		player_->Attack({worldPos.x, worldPos.y});
	}
	
	// プレイヤーの更新
	player_->Update();

	// UIの更新
	UpdateUI();

	// 数字描画の更新
	drawNumber_->Update(static_cast<int>(timer_));
}

void GameScene::Draw() {

	// DirectXCommonインスタンスの取得
	DirectXCommon* dxCommon = DirectXCommon::GetInstance();

	// スプライト描画前処理
	Sprite::PreDraw(dxCommon->GetCommandList());

	// ステージの描画
	stage_->Draw();

	// UIの描画
	spriteHP_->Draw();
	spriteHP2_->Draw();

	// 数字描画
	drawNumber_->Draw();

	aim_->Draw();

	// 画像描画後処理
	Sprite::PostDraw();

	// 深度バッファクリア
	dxCommon->ClearDepthBuffer();

	// 3Dオブジェクト描画前処理
	Model::PreDraw();

	// プレイヤーの描画
	player_->Draw();

	// 3Dオブジェクト後処理
	Model::PostDraw();
}

void GameScene::UpdateUI() {

	// 徐々にHPが減るように
	static float hp = 1.0f;                                  // HPの割合（0.0f～1.0f）
	hp -= 0.001f;                                            // HPを減らす
	spriteHP2_->SetSize(Vector2(sizeHP_.x * hp, sizeHP_.y)); // HPバーのサイズを更新
	if (hp <= 0.0f) {
		hp = 1.0f; // HPが0になったらリセット
	}
}

KamataEngine::Vector3 GameScene::GetMouseWorldPosition() {
	Ray ray = aim_->GetRayFromMouse();

	// z = 0 の平面との交点
	float t = -ray.origin.z / ray.direction.z;

	return {ray.origin.x + ray.direction.x * t, ray.origin.y + ray.direction.y * t, 0.0f};
}

GameScene::~GameScene() {

	// ステージの解放
	if (stage_) {
		delete stage_;
	}

	delete player_;

	delete modelPlayer_;

	delete aim_;

	delete drawNumber_;
}