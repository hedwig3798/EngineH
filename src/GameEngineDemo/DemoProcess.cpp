#include "DemoProcess.h"
#include "DemoScene.h"
#include "DemoObject.h"
#include "Transform.h"
#include "MouseEvent.h"
#include "Bar.h"
#include "Button.h"
#include "SceneManager.h"

DemoProcess::DemoProcess()
	: hwnd(nullptr)
{
	this->graphicsEngine = new GraphicsEngine();
	this->manager = new ManagerSet();
}

DemoProcess::~DemoProcess()
{
	delete this->manager;
	delete this->graphicsEngine;
}

void DemoProcess::Initialize(HWND _hwnd)
{
	this->hwnd = _hwnd;
	this->graphicsEngine->Initialize(hwnd);
	manager->InitializeAllManager(this->hwnd, this->graphicsEngine);
	DemoScene* demoScene = new DemoScene(this->manager);
	manager->GetSceneManager()->AddScene("Demo", demoScene);

	DemoObject* demoObject2 = new DemoObject(this->manager);
	demoObject2->GetComponent<Transform>()->Translation({200, 50});
	demoObject2->movable = false;
	demoObject2->SetName("2");
	manager->GetSceneManager()->AddObject(demoObject2);

	DemoObject* demoObject3 = new DemoObject(this->manager);
	demoObject3->GetComponent<Transform>()->Translation({ 200, 200 });
	demoObject3->movable = false;
	demoObject3->SetName("3");
	manager->GetSceneManager()->AddObject(demoObject3);

	DemoObject* demoObject4 = new DemoObject(this->manager);
	demoObject4->GetComponent<Transform>()->Translation({ 200, 350 });
	demoObject4->movable = true;
	demoObject4->SetName("4");
	manager->GetSceneManager()->AddObject(demoObject4);
	demoObject4->CreateComponent<MouseEvent>();
}

void DemoProcess::Process()
{
	Update();
	FinalUpdate();
	Render();
}

void DemoProcess::Update()
{
	manager->Update();
}

void DemoProcess::Render()
{
	graphicsEngine->BDraw();
	graphicsEngine->ColorSet(D2D1::ColorF::Black);
	manager->Render(this->graphicsEngine);
#ifdef _DEBUG
	 //manager->DebugRender(this->graphicsEngine);
#endif // DEBUG

	graphicsEngine->EDraw();
}

void DemoProcess::FinalUpdate()
{
	manager->FinalUpdate();
}
