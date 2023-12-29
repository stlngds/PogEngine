#include "bsepch.h"

void collisionCallbacks(GameObject* go) {
	
}

MainScene::MainScene() {
	this->callback = collisionCallbacks;
	this->gameObjectsFile = SceneConstants::MainSceneObjectsFile;
	this->scenegraphFile = SceneConstants::MainSceneScenegraphFile;
	ImGui::CreateContext();
	ImGui_ImplGlfwGL3_Init(WindowHandler::GetInstance().GetCurrentContext(), true);
	ImGui::StyleColorsDark();
}

MainScene::~MainScene() {
	ImGui_ImplGlfwGL3_Shutdown();
	ImGui::DestroyContext();
}

void MainScene::Update() {
	std::cerr << "MainScene::Update()" << std::endl;
	ImGui_ImplGlfwGL3_NewFrame();

	Scene::Update();
}

void MainScene::LateUpdate() {
	Scene::LateUpdate();

	// ImGui
	ImGui::SliderFloat("Translate Obj1 X", &vertx1, -1.0f, 1.0f);
	ImGui::SliderFloat("Translate Obj1 Y", &verty1, -1.0f, 1.0f);
	ImGui::SliderFloat("Translate Obj2 X", &vertx2, -1.0f, 1.0f);
	ImGui::SliderFloat("Translate Obj2 Y", &verty2, -1.0f, 1.0f);

	ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
	//ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate); // TODO: Display Collision Event info.

	ImGui::Render();
	ImGui_ImplGlfwGL3_RenderDrawData(ImGui::GetDrawData());
}