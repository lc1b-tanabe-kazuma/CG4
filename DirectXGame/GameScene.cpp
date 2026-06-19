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
	player_->Initialize(modelPlayer_, &camera_);

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
}

void GameScene::Update() {

	// Spaceキーが押されたらシーンを"Game"に変更
	if (input_->TriggerKey(DIK_SPACE)) {
		SceneManager::GetInstance()->ChangeScene("Title");
	}

	// ステージの更新
	stage_->Update();

	// プレイヤーの更新
	player_->Update();

	// UIの更新
	UpdateUI();

	//// パーティクルの削除
	//particles_.remove_if([](Particle* particle) {
	//	if (particle->IsDead()) {
	//		delete particle;
	//		return true;
	//	}
	//	return false;
	//});

	//// 確率でパーティクル発生
	//if (rand() % 20 == 0) {

	//	// 発生位置は乱数で
	//	Vector3 pos = {distribution(randomEngine) * 30.0f, distribution(randomEngine) * 20.0f, 0.0f};

	//	// パーティクルの発生
	//	SpawnParticle(pos);
	//}

	//// パーティクルの更新
	//for (Particle* particle : particles_) {
	//	particle->Update();
	//}
}

void GameScene::Draw() {

	// 画像描画前処理
	Sprite::PreDraw();

	// ステージの描画
	stage_->Draw();

	// UIの描画
	spriteHP_->Draw();
	spriteHP2_->Draw();

	// 画像描画後処理
	Sprite::PostDraw();

	// 3Dオブジェクト描画前処理
	Model::PreDraw();

	player_->Draw();

	// パーティクルの描画
	/*for (Particle* particle : particles_) {
		particle->Draw(camera_);
	}*/

	// 3Dオブジェクト後処理
	Model::PostDraw();
}

void GameScene::SpawnParticle(Vector3 pos) {

	// パーティクルの初期化
	for (int i = 0; i < 150; i++) {

		// 生成
		Particle* particle = new Particle();

		// 速度
		float angle = i * 0.3f;
		float speed = i * 0.005f;

		// 渦巻き状に広がるように
		Vector3 velocity = {cosf(angle) * speed, sinf(angle) * speed, 0.0f};

		// 色をランダムに
		Vector4 color = {distribution(randomEngine) * 0.5f + 0.5f, distribution(randomEngine) * 0.5f + 0.5f, distribution(randomEngine) * 0.5f + 0.5f, 1.0f};

		// 初期化
		particle->Initialize(modelParticle_, pos, velocity, color);

		// リストに追加
		particles_.push_back(particle);
	}
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

GameScene::~GameScene() {
	if (modelParticle_) {
		delete modelParticle_;
		modelParticle_ = nullptr;
	}

	// パーティクルの解放
	for (Particle* particle : particles_) {
		delete particle;
	}
	particles_.clear();

	// ステージの解放
	if (stage_) {
		delete stage_;
	}
}