#include "bsepch.h"
// BestSellerEngine.cpp : This file contains the 'main' function. Program execution begins and ends there.

// Game Globals
int P1Score = 0;
int P2Score = 0;
int ballVelocityX = -1; // Integer determining if the ball is moving in the positive/negative X direction.
int ballVelocityY = -1;
float ballAngleY = 0.5f; // (unsigned) float that determines the angle the ball is at.
float vertX1 = 0.0f; // Object coords
float vertY1 = 0.0f;
float vertX2 = 0.0f;
float vertY2 = 0.0f;
float vertX3 = 0.0f;
float vertY3 = 0.0f;
float ballSpeed = 0.5; // Units the ball travels per second.

// Declarations
int secondary();

// Collision callbacks
void test1(GameObject* go) {
    std::cout << "Collision event for go1 handled!" << std::endl;
}

void test2(GameObject* go) {
    std::cout << "Collision event for go2 handled!" << std::endl;
}


void ballCollisionCallback(GameObject* go) {
    std::string goName = go->GetName();
    std::cout << goName << std::endl;
    if (goName == "P1Paddle") {
        ballVelocityX = 1;
        ballSpeed += 0.05f;
        ballAngleY = std::rand() % 901 / 1000.0f; // Ball goes off in a random angle (rather than being determined by how far from the center of the paddle it was.
        if (std::rand() % 2 == 1) {
            ballVelocityY = 1;
        }
        else {
            ballVelocityY = -1;
        }
    }
    else if (goName == "P2Paddle") {
        ballVelocityX = -1;
        ballSpeed += 0.05f;
        ballAngleY = std::rand() % 901 / 1000.0f;
        if (std::rand() % 2 == 0) {
            ballVelocityY = -1;
        }
        else {
            ballVelocityY = 1;
        }
    }
    else {
        std::cout << "Unhandled ball collision event. goName == " << goName << std::endl;
    }
}

/*
void ballHitP1Paddle(GameObject* go) { // Don't want to simply invert and reuse this same callback for both paddles - potentially buggy.
    ballVelocityX = 1; 
    ballSpeed += 0.05f;
    ballAngleY = std::rand() % 801 / 1000.0f; // Ball goes off in a random angle (rather than being determined by how far from the center of the paddle it was.
    if (std::rand() % 2 == 1) {
        ballVelocityY = 1;
    }
    else {
        ballVelocityY = -1;
    }
}

void ballHitP2Paddle(GameObject* go) {
    ballVelocityX = -1;
    ballSpeed += 0.05f;
    ballAngleY = std::rand() % 801 / 1000.0f;
    if (std::rand() % 2 == 0) {
        ballVelocityY = -1;
    }
    else {
        ballVelocityY = 1;
    }
}

void ballHitTopBoundary(GameObject* go) {
    ballVelocityY = -1;
}

void ballHitBotBoundary(GameObject* go) {
    ballVelocityY = 1;
}

void ballHitP1Goal(GameObject* go) {
    ++P2Score;
    // Scorer serves.
    vertY3 = 0.0f;
    vertX3 = 0.75f;
    ballSpeed = 0.5f;
}

void ballHitP2Goal(GameObject* go) {
    ++P1Score;
    vertY3 = 0.0f;
    vertX3 = -0.75f;
    ballSpeed = 0.5f;
}
*/

int main() {
    secondary();
    //Game game = *Game::GetInstance();

    //game.Init();
    //game.Run();
    //game.Quit();
}


int secondary()
{
    // Window init.
    WindowHandler aWindow = WindowHandler::GetInstance();
    aWindow.Props.Title = "Test Window";
    aWindow.Props.Height = 768;
    aWindow.Props.Width = 1024;
    aWindow.Init();

    // Create GameObjects from JSON.
    GameObjectFactory::GetInstance()->CreateAllGameObjects("MainSceneGameObjects.json");
    GameObjectFactory::GetInstance()->InitializeGameObjects();
    //GameObjectFactory::GetInstance()->SetOneCollisionHandlerToAllPhysicsComponents(test1);

    GameObject* go1 = GameObjectFactory::GetInstance()->QuickFind("P1Paddle");
    GameObject* go2 = GameObjectFactory::GetInstance()->QuickFind("P2Paddle");
    GameObject* go3 = GameObjectFactory::GetInstance()->QuickFind("Ball");
    GameObject* go4 = GameObjectFactory::GetInstance()->QuickFind("Background");
    
    RenderComponent* rc1 = go1->FindComponent<RenderComponent>();
    RenderComponent* rc2 = go2->FindComponent<RenderComponent>();
    RenderComponent* rc3 = go3->FindComponent<RenderComponent>();
    RenderComponent* rc4 = go4->FindComponent<RenderComponent>();

    PhysicsComponent* pc1 = go1->FindComponent<PhysicsComponent>();
    PhysicsComponent* pc2 = go2->FindComponent<PhysicsComponent>();
    PhysicsComponent* pc3 = go3->FindComponent<PhysicsComponent>();
    PhysicsComponent* pc4 = go4->FindComponent<PhysicsComponent>();

    TransformComponent* tc1 = go1->FindComponent<TransformComponent>();
    TransformComponent* tc2 = go2->FindComponent<TransformComponent>();
    TransformComponent* tc3 = go3->FindComponent<TransformComponent>();
    TransformComponent* tc4 = go4->FindComponent<TransformComponent>();
    
    // User-defined variables.
    float vertx1 = tc1->GetPosition().x;
    float verty1 = tc1->GetPosition().y;
    float vertx2 = tc2->GetPosition().x;
    float verty2 = tc2->GetPosition().y;
    float vertx3 = tc3->GetPosition().x;
    float verty3 = tc3->GetPosition().y;
    float vertx4 = tc4->GetPosition().x;
    float verty4 = tc4->GetPosition().y;
    tc4->SetScale(2.0);
    pc4->physicsBody->Position = glm::vec3(10.0, 10.0, 0.0f);

    pc1->SetCollisionCallback(ballCollisionCallback);
    pc2->SetCollisionCallback(ballCollisionCallback);

    PhysicsManager::GetInstance()->Init();
    
    // ImGui init.
    ImGui::CreateContext();
    ImGui_ImplGlfwGL3_Init(aWindow.GetCurrentContext(), true);
    ImGui::StyleColorsDark();

    std::string gameover = "Not game over";

    // Main loop
    while (!aWindow.ShouldClose())
    {  
        aWindow.Update();
        ImGui_ImplGlfwGL3_NewFrame();
        float deltaTime = ImGui::GetIO().DeltaTime;

        if (P1Score >= 5 || P2Score >= 5) {
            ImGui::Text("Game Over! Press ENTER to play again.");
            vertx3 = verty3 = 0.0f;
            ballSpeed = 0.5f;
            ballVelocityX = ballVelocityY = -1;
        }

        if (glfwGetKey(aWindow.GetCurrentContext(), GLFW_KEY_ENTER) == GLFW_PRESS) {
            P1Score = P2Score = 0;
            vertx3 = verty3 = 0.0f;
            ballSpeed = 0.5f;
            ballVelocityX = ballVelocityY = -1;
        }

        // Background
        tc4->SetPosition(glm::vec3(vertx4, verty4, 0.0f));
        go4->Update();
        go4->Draw();

        // Paddle 1
        if (glfwGetKey(aWindow.GetCurrentContext(), GLFW_KEY_W) == GLFW_PRESS) verty1 += 0.03f * ballSpeed;
        if (glfwGetKey(aWindow.GetCurrentContext(), GLFW_KEY_S) == GLFW_PRESS) verty1 -= 0.03f * ballSpeed;
        if (glfwGetKey(aWindow.GetCurrentContext(), GLFW_KEY_A) == GLFW_PRESS) vertx1 -= 0.03f * ballSpeed;
        if (glfwGetKey(aWindow.GetCurrentContext(), GLFW_KEY_D) == GLFW_PRESS) vertx1 += 0.03f * ballSpeed;
        verty1 = std::min(0.9f, verty1);
        verty1 = std::max(-0.9f, verty1);
        vertx1 = std::max(-0.9f, vertx1);
        vertx1 = std::min(-0.3f, vertx1);
        tc1->SetPosition(glm::vec3(vertx1, verty1, 0.0f));
        pc1->physicsBody->Position = glm::vec3(vertx1, verty1, 0.0f);
        go1->Update();
        go1->Draw();

        // Paddle 2
        if (glfwGetKey(aWindow.GetCurrentContext(), GLFW_KEY_UP) == GLFW_PRESS) verty2 += 0.03f * ballSpeed;
        if (glfwGetKey(aWindow.GetCurrentContext(), GLFW_KEY_DOWN) == GLFW_PRESS) verty2 -= 0.03f * ballSpeed;
        if (glfwGetKey(aWindow.GetCurrentContext(), GLFW_KEY_LEFT) == GLFW_PRESS) vertx2 -= 0.03f * ballSpeed;
        if (glfwGetKey(aWindow.GetCurrentContext(), GLFW_KEY_RIGHT) == GLFW_PRESS) vertx2 += 0.03f * ballSpeed;
        verty2 = std::min(0.9f, verty2);
        verty2 = std::max(-0.9f, verty2);
        vertx2 = std::max(0.3f, vertx2);
        vertx2 = std::min(0.9f, vertx2);
        tc2->SetPosition(glm::vec3(vertx2, verty2, 0.0f));
        pc2->physicsBody->Position = glm::vec3(vertx2, verty2, 0.0f);
        go2->Update();
        go2->Draw();

        // Ball
        if (P1Score < 5 && P2Score < 5) { // If game isn't over
            vertx3 += ballVelocityX * deltaTime * (ballSpeed);
            verty3 += ballVelocityY * deltaTime * (ballSpeed)*ballAngleY;
        }
        if (verty3 > 1.0f) {
            ballVelocityY = -1;
        }
        if (verty3 < -1.0f) {
            ballVelocityY = 1;
        }
        if (vertx3 < -1.5f) {
            std::cout << "Player 2 scores!" << std::endl;
            ++P2Score;
            verty3 = 0.0f;
            vertx3 = 0.75f;
            ballSpeed = 0.5f;
        }
        if (vertx3 > 1.5f) {
            std::cout << "Player 1 scores!" << std::endl;
            ++P1Score;
            verty3 = 0.0f;
            vertx3 = -0.75f;
            ballSpeed = 0.5f;
        }

        tc3->SetPosition(glm::vec3(vertx3, verty3, 0));
        pc3->physicsBody->Position = tc3->GetPosition();
        go3->Update();
        go3->Draw();

        // Collisions
        PhysicsManager::GetInstance()->EvaluateCollisions();
        PhysicsManager::GetInstance()->RegisterCollisionEvents();
        for (Event* pEvent : EventManager::GetInstance()->events) {
            go1->HandleEvent(pEvent);
            go2->HandleEvent(pEvent);
            go3->HandleEvent(pEvent);
        }
        EventManager::GetInstance()->FlushEvents();
        PhysicsManager::GetInstance()->FlushCollisions();

        // ImGui
        /*
        ImGui::SliderFloat("Translate Obj1 X", &vertx1, -1.0f, 1.0f);
        ImGui::SliderFloat("Translate Obj1 Y", &verty1, -1.0f, 1.0f);
        ImGui::SliderFloat("Translate Obj2 X", &vertx2, -1.0f, 1.0f);
        ImGui::SliderFloat("Translate Obj2 Y", &verty2, -1.0f, 1.0f);
        ImGui::SliderFloat("Translate Obj4 X", &vertx4, -1.0f, 1.0f);
        ImGui::SliderFloat("Translate Obj4 Y", &verty4, -1.0f, 1.0f);
        */
        
        ImGui::Text("P1: %i/5, P2: %i/5", P1Score, P2Score);
        
        //ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
        //ImGui::Text("vertx3: %.3f, verty3: %.3f", vertx3, verty3);

        ImGui::Render();
        ImGui_ImplGlfwGL3_RenderDrawData(ImGui::GetDrawData());
        
        aWindow.SwapBuffers();
    }
    ImGui_ImplGlfwGL3_Shutdown();
    ImGui::DestroyContext();
    aWindow.ShutDown();
    exit(EXIT_SUCCESS);
}