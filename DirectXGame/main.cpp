#include "KamataEngine.h"
#include <Windows.h>
using namespace KamataEngine;
#include "scene/GameScene.h"
#include "scene/TitleScene.h"
#include <imgui.h>

GameScene* gameScene = nullptr;
TitleScene* titleScene = nullptr;


enum class Scene {
	kUnknown = 0,
	kTitle,
	kGame,

};

void ChangeScene(Scene scene) {

	switch (scene) {
	case Scene::kTitle:
		if (titleScene->IsFinished()) {
			scene = Scene::kGame;
			delete titleScene;
			titleScene = nullptr;
			gameScene = new GameScene;
			gameScene->Initialize();
		}
		break;
		/*case Scene::kGame:
		    if (gameScene->IsFinished()) {

		        scene = Scene::kTitle;
		        delete gameScene;
		        gameScene = nullptr;
		        titleScene = new TitleScene;
		        titleScene->Initialize();
		    }
		    break;*/
	}
}

void UpdateScene(Scene scene) {

	switch (scene) {
	case Scene::kTitle:
		titleScene->Update();

		break;

		/*case Scene::kGame:
		    gameScene->Update();
		    break;*/
	}
}

void DrawScene(Scene scene) {

	switch (scene) {
	case Scene::kTitle:
		titleScene->Draw();

		break;

		/*case Scene::kGame:
		    gameScene->Draw();
		    break;*/
	}
}


// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(_In_ HINSTANCE, _In_opt_ HINSTANCE, _In_ LPSTR, _In_ int) {
	// エンジンの初期化
	KamataEngine::Initialize(L"LE3D_11_ハギワラ_ケンタ");

	// DirectXCommonインスタンスの取得
	DirectXCommon* dxCommon = DirectXCommon::GetInstance();

	// ゲームシーンのインスタンス生成
	//GameScene* gameScene = new GameScene();
	// ゲームシーンの初期化
	Scene scene = Scene::kTitle;
	titleScene = new TitleScene;
	titleScene->Initialize();

	// メインループ
	while (true) {

		// エンジンの更新
		if (KamataEngine::Update()) {
			break;
		}
		// ゲームシーンの毎フレーム処理
		ChangeScene(scene);
		UpdateScene(scene);

		// ゲームシーンの更新
		//gameScene->Update();

		// 描画開始
		dxCommon->PreDraw();

		//// --- ImGui: 現在のシーンを表示 ---
		//// ImGui が有効ならウィンドウを表示、無ければデバッグ出力のみ
		//if (ImGui::GetCurrentContext()) {
		//	ImGui::Begin("Debug: Scene");
		//	const char* sceneName = "Unknown";
		//	switch (scene) {
		//	case Scene::kTitle:
		//		sceneName = "Title";
		//		break;
		//	case Scene::kGame:
		//		sceneName = "Game";
		//		break;
		//	default:
		//		sceneName = "Unknown";
		//		break;
		//	}
		//	ImGui::Text("Current Scene: %s", sceneName);
		//	ImGui::End();
		//} else {
		//	// GUIコンテキストが無ければ Visual Studio 出力に情報を送る
		//	char buf[64];
		//	sprintf_s(buf, "ImGui context not found. Scene=%d\n", static_cast<int>(scene));
		//	OutputDebugStringA(buf);
		//}

		// ゲームシーンの描画
		DrawScene(scene);
		// 描画終了
		dxCommon->PostDraw();
	}

	// エンジンの終了処理
	KamataEngine::Finalize();

	// ゲームシーンの解放
	delete gameScene;
	// nullptrの代入
	gameScene = nullptr;

	return 0;
}

