//----------------------------------------------------------------------------
// Copyright 2021, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "sb7.h"
#include "GameManager.h"

#include "MathEngine.h"
#include "VectApp.h"
#include "QuatApp.h"

#include "GameObject.h"
#include "ShaderObject.h"
#include "CubeMesh.h"
#include "ProtoBuffMesh.h"

#include "TextureManager.h"
#include "InputManager.h"
#include "GameObjectManager.h"
#include "MeshNodeManager.h"
#include "ShaderManager.h"
#include "CameraManager.h"
#include "AnimationManager.h"

#include "Camera.h"
#include "CameraInput.h"
#include "ProtoMeshFactory.h"
#include "SphereMesh.h"
#include "GameObjectBoundingSphere.h"
#include "CameraMesh.h"

//Animation
#include "TimerController.h"
#include "AnimController.h"
#include "Clip.h"
#include "NullMesh.h"
#include "Skeleton.h"

using namespace Azul;

namespace Azul
{
	//AnimController* pAnimController;
	//Clip* pWalkClip = nullptr;
	//-----------------------------------------------------------------------------
//  Game::Game()
//		Game Engine Constructor
//-----------------------------------------------------------------------------
	Game::Game(const char* const pWindowName, const int Width, const int Height)
		:Engine(pWindowName, Width, Height)
	{
		assert(pWindowName);
		this->globalTimer.Tic();
		this->intervalTimer.Tic();
	}

	//-----------------------------------------------------------------------------
	//  Game::~Game()
	//		Game Engine destructor
	//-----------------------------------------------------------------------------
	Game::~Game()
	{
	}

	//-----------------------------------------------------------------------------
	// Game::Initialize()
	//		Allows the engine to perform any initialization it needs to before
	//      starting to run.  This is where it can query for any required services
	//      and load any non-graphic related content.
	//-----------------------------------------------------------------------------
	void Game::Initialize()
	{
	}

	//-----------------------------------------------------------------------------
	// Game::LoadContent()
	//		Allows you to load all content needed for your engine,
	//	    such as objects, graphics, etc.
	//-----------------------------------------------------------------------------
	void Game::LoadContent()
	{
		InputManager::Create();
		TextureManager::Create();
		MeshNodeManager::Create();
		ShaderManager::Create();
		CameraManager::Create();
		CameraInput::Create(this->window);
		AnimationManager::Create();

		//Camera setup
		CameraManager::Add(Camera::ID::MAIN, 50.0f, 0.10f, 1000.0f, this->info.windowWidth, this->info.windowHeight);
		CameraManager::Add(Camera::ID::TOP, 30.0f, 0.10f, 1000.0f, this->info.windowWidth, this->info.windowHeight);
		CameraManager::Add(Camera::ID::SIDE, 30.0f, 0.10f, 1000.0f, this->info.windowWidth, this->info.windowHeight);
		CameraManager::Add(Camera::ID::FORWARD, 30.0f, 0.10f, 1000.0f, this->info.windowWidth, this->info.windowHeight);
		CameraManager::SetCurrent(Camera::ID::MAIN);

		//-----------------------------------------------------------------------------
		//	    Load Camera and Sphere Mesh
		//-----------------------------------------------------------------------------

		//Sphere
		Mesh* pSphereMesh = new SphereMesh("sphereModel.azul");
		MeshNodeManager::Add(Mesh::Name::SPHERE, pSphereMesh);
		//Cube
		Mesh* pCubeMesh = new CubeMesh("./Models/cubeMEsh.azul");
		MeshNodeManager::Add(Mesh::Name::CUBE, pCubeMesh);

		Mesh* pNullMesh = new NullMesh(nullptr);
		MeshNodeManager::Add(Mesh::Name::NULL_MESH, pNullMesh);

		//Load Texture
		ProtoMeshFactory::LoadTexture("ChickenbotDiffuse.t.proto.azul", Texture::Name::CHICKEN_BOT);

		//Load mesh and set the correct Name for Skeleton.find
		Mesh* MeshArray[8];
		ProtoMeshFactory::GetMesh("walk_mesh.mt.proto.azul", MeshArray);
		MeshArray[0]->name = Mesh::Name::BONE;
		MeshArray[1]->name = Mesh::Name::BONE_R;
		MeshArray[2]->name = Mesh::Name::BONE_R_001;
		MeshArray[3]->name = Mesh::Name::BONE_R_002;
		MeshArray[4]->name = Mesh::Name::BONE_L;
		MeshArray[5]->name = Mesh::Name::BONE_L_001;
		MeshArray[6]->name = Mesh::Name::BONE_L_002;
		MeshArray[7]->name = Mesh::Name::BONE_01;

		Animation* Anim_Die_Left[8];
		ProtoMeshFactory::GetAnimation("die_left_mesh.a.proto.azul", Anim_Die_Left);

		Animation* Anim_Walk[8];
		ProtoMeshFactory::GetAnimation("walk_mesh.mt.proto.azul", Anim_Walk);

		Animation* Anim_Shot_Down[8];
		ProtoMeshFactory::GetAnimation("shot_down_mesh.a.proto.azul", Anim_Shot_Down);

		Animation* Anim_Hit_Right[8];
		ProtoMeshFactory::GetAnimation("hit_right_mesh.a.proto.azul", Anim_Hit_Right);

		Animation* Anim_Run[8];
		ProtoMeshFactory::GetAnimation("run_RM_mesh.a.proto.azul", Anim_Run);

		//-----------------------------------------------------------------------------
		//	    Create/Load Shaders
		//-----------------------------------------------------------------------------

		ShaderObject* pShaderObject_color = ShaderManager::Add(ShaderObject::Name::COLOR_POSITION, "../src/GLSL/colorRender");
		assert(pShaderObject_color);

		ShaderObject* pShaderObject_Null = ShaderManager::Add(ShaderObject::Name::NULL_SHADER, "../src/GLSL/nullRender");

		ShaderObject* pShaderObject_texture = ShaderManager::Add(ShaderObject::Name::TEXTURE_SIMPLE, "../src/GLSL/textureRender");
		assert(pShaderObject_texture);

		ShaderObject* pShaderObject_textureLight = ShaderManager::Add(ShaderObject::Name::TEXTURE_POINT_LIGHT, "../src/GLSL/texturePointLightDiff");
		assert(pShaderObject_textureLight);

		ShaderObject* pShaderObject_constColor = ShaderManager::Add(ShaderObject::Name::CONST_COLOR, "../src/GLSL/constcolorRender");
		assert(pShaderObject_constColor);

		ShaderObject* pShaderObject_specLighting = ShaderManager::Add(ShaderObject::Name::SPEC_LIGHTING, "../src/GLSL/specLighting");
		assert(pShaderObject_specLighting);

		ShaderObject* pShaderObject_colorSingle = ShaderManager::Add(ShaderObject::Name::COLOR_SINGLE, "../src/GLSL/colorSingleRender");
		assert(pShaderObject_colorSingle);

		// Textures
		TextureManager::Add("../src/Textures/Rocks.tga", Texture::Name::ROCKS);
		TextureManager::Add("../src/Textures/Stone.tga", Texture::Name::STONES);
		TextureManager::Add("../src/Textures/RedBrick.tga", Texture::Name::RED_BRICK);
		TextureManager::Add("../src/Textures/Duckweed.tga", Texture::Name::DUCKWEED);
		TextureManager::Add("../src/Textures/HotPink.tga", Texture::Name::PINK_ERROR);

		//-----------------------------------------------------------------------------
		//	    Create Animation
		//-----------------------------------------------------------------------------

		Skeleton* pSkel = new Skeleton(MeshArray, NUM_BONES);
		pSkel->SetPos(-1.3f, 0, 0);

		Skeleton* pSkel2 = new Skeleton(MeshArray, NUM_BONES);
		pSkel2->SetPos(0, 0, 0);

		Skeleton* pSkel3 = new Skeleton(MeshArray, NUM_BONES);
		pSkel3->SetPos(1.3f, 0, 0);

		Skeleton* pSkel4 = new Skeleton(MeshArray, NUM_BONES);
		pSkel4->SetPos(0, 1.4f, 0);

		AnimationManager::Add(Anim_Die_Left, Clip::Name::DIE_LEFT, NUM_BONES);
		AnimationManager::Add(Anim_Walk, Clip::Name::WALK, NUM_BONES);
		AnimationManager::Add(Anim_Shot_Down, Clip::Name::SHOT_DOWN, NUM_BONES);
		AnimationManager::Add(Anim_Hit_Right, Clip::Name::HIT_RIGHT, NUM_BONES);
		AnimationManager::Add(Anim_Run, Clip::Name::RUN, NUM_BONES);

		AnimationManager::AddController(AnimController::AnimName::MESH1, pSkel, Clip::Name::WALK);
		AnimationManager::AddController(AnimController::AnimName::MESH2, pSkel2, Clip::Name::DIE_LEFT);
		AnimationManager::AddController(AnimController::AnimName::MESH3, pSkel3, Clip::Name::SHOT_DOWN);
		AnimationManager::AddController(AnimController::AnimName::MESH4, pSkel4, Clip::Name::HIT_RIGHT);

		AnimationManager::Demo();

		//pSkel2->Hide();

		CameraManager::Update();

		Trace::out("Z - Reset ,  I,O - Zoom In/Out\n");
		Trace::out("ASDF - Switch Cameras\n");
		Trace::out("H: Hide B Spheres\n");

		Trace::out("-: Slow animation speed, =: Increase animation speed\n ");
		Trace::out("Q: Play animation reverse, W: Player animation forward\n ");
		Trace::out("E: Play Demo 2\n");
	}

	//-----------------------------------------------------------------------------
	// Game::Update()
	//      Called once per frame, update data, tranformations, etc
	//      Use this function to control process order
	//      Input, AI, Physics, Animation, and Graphics
	//-----------------------------------------------------------------------------
	void Game::Update(float currentTime)
	{
		this->intervalTimer.Toc();
		this->intervalTimer.Tic();

		// ------------------------------------
		// Camera update
		// ------------------------------------
		CameraManager::Update();
		CameraInput::Update();

		// ------------------------------------
		// Animate Me
		// ------------------------------------
		//pAnimController->Update();
		AnimationManager::Update();

		// ------------------------------------
		// GameObject update
		// ------------------------------------
		GameObjectManager::Update(this->globalTimer.Toc());
	}

	//-----------------------------------------------------------------------------
	// Game::Draw()
	//		This function is called once per frame
	//	    Use this for draw graphics to the screen.
	//      Only do rendering here
	//-----------------------------------------------------------------------------
	void Game::Draw()
	{
		GameObjectManager::Draw();
	}

	//------------------- ----------------------------------------------------------
	// Game::UnLoadContent()
	//       unload content (resources loaded above)
	//       unload all content that was loaded before the Engine Loop started
	//-----------------------------------------------------------------------------
	void Game::UnLoadContent()
	{
		TextureManager::Destroy();
		InputManager::Destroy();
		GameObjectManager::Destroy();
		MeshNodeManager::Destroy();
		ShaderManager::Destroy();
		CameraManager::Destroy();

		CameraInput::Destroy();
		AnimationManager::Destroy();
		//delete pAnimController;
		//delete pWalkClip;
	}

	//------------------------------------------------------------------
	// Game::ClearBufferFunc()
	// Allows user to change the way the clear buffer function works
	//------------------------------------------------------------------
	void Game::ClearBufferFunc()
	{
		const GLfloat grey[] = { 0.7f, 0.7f, 0.8f, 1.0f };
		const GLfloat one = 1.0f;

		glViewport(0, 0, info.windowWidth, info.windowHeight);
		glClearBufferfv(GL_COLOR, 0, grey);
		glClearBufferfv(GL_DEPTH, 0, &one);
	}
}

// --- End of File ---