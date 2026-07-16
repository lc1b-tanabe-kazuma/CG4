#include "KamataEngine.h"
#include "Scene/GameScene.h"
#include "SceneManager.h"
#include <Windows.h>
#include <imgui.h>

using namespace KamataEngine;

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(_In_ HINSTANCE, _In_opt_ HINSTANCE, _In_ LPSTR, _In_ int) {

	// エンジンの初期化
	KamataEngine::Initialize(L"CG4_LE3D_16タナベ_カズマ");

	// DirectXCommonインスタンスの取得
	DirectXCommon* dxCommon = DirectXCommon::GetInstance();

	// scnenマネージャーの作成
	SceneManager* sceneManager = SceneManager::GetInstance();
	sceneManager->Initialize();

#ifdef _DEBUG
	// ImguiManagerのインスタンスを取得
	ImGuiManager* imguiManager_ = ImGuiManager::GetInstance();
#endif

	// カーソルを隠す
	ShowCursor(FALSE);

	// メインループ
	while (true) {
		// エンジンの更新
		if (KamataEngine::Update()) {
			break;
		}

#ifdef _DEBUG
		// Imgui受付開始
		imguiManager_->Begin();
#endif

		// シーンマネージャーの更新
		sceneManager->Update();

#ifdef _DEBUG
		// Imgui受付終了
		imguiManager_->End();
#endif

		// 描画開始
		dxCommon->PreDraw();

		// シーンマネージャーの描画
		sceneManager->Draw();

#ifdef _DEBUG
		// Imguiの描画
		imguiManager_->Draw();
#endif

		// 描画終了
		dxCommon->PostDraw();
	}

	// エンジンの終了処理
	KamataEngine::Finalize();

	// シーンマネージャーの終了処理
	sceneManager->Finalize();

	return 0;
}
