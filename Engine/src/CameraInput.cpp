#include "CameraInput.h"
#include "InputManager.h"
#include "GameObjectManager.h"
#include "AnimationManager.h" //For demo

using namespace Azul;

CameraInput* CameraInput::posInstance = nullptr;

CameraInput::CameraInput(GLFWwindow* _window)
	:pWindow(_window)
{
	this->obj.set(0.0f, 0.0f, 0.0f);
}

void CameraInput::SwitchCamera(Keyboard* pKey)
{
	//Main camera
	static bool keyState1 = false;
	if (pKey->GetKeyState(Keyboard::KEY_A) && !keyState1)
	{
		keyState1 = true;
	}

	if (pKey->GetKeyReleaseState(Keyboard::KEY_A) && keyState1)
	{
		CameraManager::MainCamera();
		glfwSetWindowTitle(this->pWindow, "Press A: Main, S: Side, D: Top, F: Forward ---- CURRENTLY: Main");
		keyState1 = false;
	}
	//Side
	static bool keyState2 = false;
	if (pKey->GetKeyState(Keyboard::KEY_S) && !keyState2)
	{
		keyState2 = true;
	}

	if (pKey->GetKeyReleaseState(Keyboard::KEY_S) && keyState2)
	{
		CameraManager::SideCamera();
		glfwSetWindowTitle(this->pWindow, "Press A: Main, S: Side, D: Top, F: Forward ---- CURRENTLY: Side");
		keyState2 = false;
	}

	//Top
	static bool keyState3 = false;
	if (pKey->GetKeyState(Keyboard::KEY_D) && !keyState3)
	{
		keyState3 = true;
	}

	if (pKey->GetKeyReleaseState(Keyboard::KEY_D) && keyState3)
	{
		CameraManager::TopCamera();
		glfwSetWindowTitle(this->pWindow, "Press A: Main, S: Side, D: Top, F: Forward ---- CURRENTLY: Top");
		keyState3 = false;
	}

	//Forward
	static bool keyState4 = false;
	if (pKey->GetKeyState(Keyboard::KEY_F) && !keyState4)
	{
		keyState4 = true;
	}

	if (pKey->GetKeyReleaseState(Keyboard::KEY_F) && keyState4)
	{
		CameraManager::ForwardCamera();
		glfwSetWindowTitle(this->pWindow, "Press A: Main, S: Side, D: Top, F: Forward ---- CURRENTLY: Forward");
		keyState4 = false;
	}
}

void CameraInput::PlayDemo(Keyboard* pKey)
{
	//------------
	//	Walk
	//------------
	static bool keyState1 = false;
	if (pKey->GetKeyState(Keyboard::KEY_1) && !keyState1)
	{
		keyState1 = true;
	}

	if (pKey->GetKeyReleaseState(Keyboard::KEY_1) && keyState1)
	{
		AnimationManager::SetClip(Clip::Name::WALK, AnimController::AnimName::MESH1);
		keyState1 = false;
	}

	//------------
	//	Die_Left
	//------------
	static bool keyState2 = false;
	if (pKey->GetKeyState(Keyboard::KEY_2) && !keyState2)
	{
		keyState2 = true;
	}

	if (pKey->GetKeyReleaseState(Keyboard::KEY_2) && keyState2)
	{
		AnimationManager::SetClip(Clip::Name::DIE_LEFT, AnimController::AnimName::MESH1);
		keyState2 = false;
	}

	//------------
	//	Shot_Down
	//------------
	static bool keyState3 = false;
	if (pKey->GetKeyState(Keyboard::KEY_3) && !keyState3)
	{
		keyState3 = true;
	}

	if (pKey->GetKeyReleaseState(Keyboard::KEY_3) && keyState3)
	{
		AnimationManager::SetClip(Clip::Name::SHOT_DOWN, AnimController::AnimName::MESH1);
		keyState3 = false;
	}

	//------------
	//	Hit_Right
	//------------
	static bool keyState4 = false;
	if (pKey->GetKeyState(Keyboard::KEY_4) && !keyState4)
	{
		keyState4 = true;
	}

	if (pKey->GetKeyReleaseState(Keyboard::KEY_4) && keyState4)
	{
		AnimationManager::SetClip(Clip::Name::HIT_RIGHT, AnimController::AnimName::MESH1);
		keyState4 = false;
	}

	//------------
	//	Run
	//------------
	static bool keyState5 = false;
	if (pKey->GetKeyState(Keyboard::KEY_5) && !keyState5)
	{
		keyState5 = true;
	}

	if (pKey->GetKeyReleaseState(Keyboard::KEY_5) && keyState5)
	{
		AnimationManager::SetClip(Clip::Name::RUN, AnimController::AnimName::MESH1);
		keyState5 = false;
	}

}

void CameraInput::DemoChangeSpeed(Keyboard* pKey)
{
	static bool keyState1 = false;
	if (pKey->GetKeyState(Keyboard::KEY_EQUAL) && !keyState1)
	{
		keyState1 = true;
	}

	if (pKey->GetKeyReleaseState(Keyboard::KEY_EQUAL) && keyState1)
	{
		AnimationManager::IncreaseSpeed(1.25f);
		keyState1 = false;
	}

	static bool keyState2 = false;
	if (pKey->GetKeyState(Keyboard::KEY_MINUS) && !keyState2)
	{
		keyState2 = true;
	}

	if (pKey->GetKeyReleaseState(Keyboard::KEY_MINUS) && keyState2)
	{
		AnimationManager::DecreaseSpeed(1.25f);
		keyState2 = false;
	}

	static bool keyState3 = false;
	if (pKey->GetKeyState(Keyboard::KEY_Q) && !keyState3)
	{
		keyState3 = true;
	}

	if (pKey->GetKeyReleaseState(Keyboard::KEY_Q) && keyState3)
	{
		AnimationManager::Reverse();
		keyState3 = false;
	}

	static bool keyState4 = false;
	if (pKey->GetKeyState(Keyboard::KEY_W) && !keyState4)
	{
		keyState4 = true;
	}

	if (pKey->GetKeyReleaseState(Keyboard::KEY_W) && keyState4)
	{
		AnimationManager::Forward();
		keyState4 = false;
	}

	static bool keyState5 = false;
	if (pKey->GetKeyState(Keyboard::KEY_SPACE) && !keyState5)
	{
		keyState5 = true;
	}

	if (pKey->GetKeyReleaseState(Keyboard::KEY_SPACE) && keyState5)
	{
		AnimationManager::PlayPause();
		keyState5 = false;
	}

	//Demo 2
	static bool keyState6 = false;
	if (pKey->GetKeyState(Keyboard::KEY_E) && !keyState6)
	{
		keyState6 = true;
	}

	if (pKey->GetKeyReleaseState(Keyboard::KEY_E) && keyState6)
	{
		AnimationManager::Demo2();
		keyState6 = false;
	}
	
}

void CameraInput::Create(GLFWwindow* _window)
{
    if (posInstance == nullptr)
    {
        posInstance = new CameraInput(_window);
    }
}

void CameraInput::Destroy()
{
    CameraInput* pMan = CameraInput::privGetInstance();
    assert(pMan != nullptr);
	AZUL_UNUSED_VAR(pMan);

    delete CameraInput::posInstance;
    CameraInput::posInstance = nullptr;
}

CameraInput* CameraInput::privGetInstance()
{
    // Safety - this forces users to call Create() first before using class
    assert(posInstance != nullptr);

    return posInstance;
}

void CameraInput::Update()
{
	CameraInput* pMan = CameraInput::privGetInstance();
    Camera* pCam = CameraManager::CurrentCamera();
	Keyboard* pKey = InputManager::GetKeyboard();

	pMan->PlayDemo(pKey);
	pMan->DemoChangeSpeed(pKey);

	static bool keyState1 = false;
	if (pKey->GetKeyState(Keyboard::KEY_H) && !keyState1)
	{
		keyState1 = true;
	}

	if (pKey->GetKeyReleaseState(Keyboard::KEY_H) && keyState1)
	{
		GameObjectManager::FlipBSphere();
		keyState1 = false;
	}

	pMan->SwitchCamera(pKey);

	//Reset
	if (pKey->GetKeyState(Keyboard::KEY_Z))
	{
		// Reset	
		pMan->obj.set(0, 0, 0);
		pCam->GetOriginal();
	}
	//Zoom in
	if (pKey->GetKeyState(Keyboard::KEY_I) && !pCam->bStatic)
	{

		Vect pos;
		Vect tar;
		Vect up;
		Vect upNorm;
		Vect forwardNorm;
		Vect rightNorm;

		pCam->GetHelper(up, tar, pos, upNorm, forwardNorm, rightNorm);

		// OK, now 3 points... pos, tar, up
		//     now 3 normals... upNorm, forwardNorm, rightNorm
		//	tar = obj;

		pos = pos + 0.03f * forwardNorm;
		//tar = tar + 0.03f * forwardNorm;
		up = up + 0.03f * forwardNorm;
		if((pos - tar).mag() > 0.5f)
		{
			pCam->SetHelper(up, tar, pos);
		}
		
	}
	//Zoom out
	if (pKey->GetKeyState(Keyboard::KEY_O) && !pCam->bStatic)
	{

		Vect pos;
		Vect tar;
		Vect up;
		Vect upNorm;
		Vect forwardNorm;
		Vect rightNorm;

		pCam->GetHelper(up, tar, pos, upNorm, forwardNorm, rightNorm);

		// OK, now 3 points... pos, tar, up
		//     now 3 normals... upNorm, forwardNorm, rightNorm
		tar = pMan->obj;

		pos = pos - 0.03f * forwardNorm;
		up = up - 0.03f * forwardNorm;

		pCam->SetHelper(up, tar, pos);
	}


	//TURN RIGHT
	if (pKey->GetKeyState(Keyboard::KEY_ARROW_RIGHT) && !pCam->bStatic)
	{
		Vect pos;
		Vect tar;
		Vect up;
		Vect upNorm;
		Vect forwardNorm;
		Vect rightNorm;

		pCam->GetHelper(up, tar, pos, upNorm, forwardNorm, rightNorm);

		// OK, now 3 points... pos, tar, up
		//     now 3 normals... upNorm, forwardNorm, rightNorm
		tar = pMan->obj;
		Matrix Trans(Matrix::Trans::XYZ, tar);
		Matrix NegTrans(Matrix::Trans::XYZ, -tar);

		Matrix Rot;
		Rot.set(Matrix::Rot::AxisAngle, upNorm, +0.03f);

		Matrix M = NegTrans * Rot * Trans;

		//M = Rot;

		up = up * M;
		pos = pos * M;
		tar = tar * M;

		pCam->SetHelper(up, tar, pos);
	}

	if (pKey->GetKeyState(Keyboard::KEY_ARROW_LEFT) && !pCam->bStatic)
	{

		Vect pos;
		Vect tar;
		Vect up;
		Vect upNorm;
		Vect forwardNorm;
		Vect rightNorm;

		pCam->GetHelper(up, tar, pos, upNorm, forwardNorm, rightNorm);

		// OK, now 3 points... pos, tar, up
		//     now 3 normals... upNorm, forwardNorm, rightNorm

		tar = pMan->obj;
		Matrix Trans(Matrix::Trans::XYZ, tar);
		Matrix NegTrans(Matrix::Trans::XYZ, -tar);

		Matrix Rot;
		Rot.set(Matrix::Rot::AxisAngle, upNorm, -0.03f);

		Matrix M = NegTrans * Rot * Trans;

		up = up * M;
		pos = pos * M;
		tar = tar * M;

		pCam->SetHelper(up, tar, pos);
	}

	if (pKey->GetKeyState(Keyboard::KEY_ARROW_DOWN) && !pCam->bStatic)
	{
		Vect pos;
		Vect tar;
		Vect up;
		Vect upNorm;
		Vect forwardNorm;
		Vect rightNorm;

		pCam->GetHelper(up, tar, pos, upNorm, forwardNorm, rightNorm);

		tar = pMan->obj;

		// OK, now 3 points... pos, tar, up
		//     now 3 normals... upNorm, forwardNorm, rightNorm

		Matrix Trans(Matrix::Trans::XYZ, tar);
		Matrix NegTrans(Matrix::Trans::XYZ, -tar);
		Matrix Rot;
		Rot.set(Matrix::Rot::AxisAngle, rightNorm, 0.03f);

		Matrix M = NegTrans * Rot * Trans;

		up = up * M;
		pos = pos * M;
		tar = tar * M;

		pCam->SetHelper(up, tar, pos);
	}

	if (pKey->GetKeyState(Keyboard::KEY_ARROW_UP) && !pCam->bStatic)
	{
		Vect pos;
		Vect tar;
		Vect up;
		Vect upNorm;
		Vect forwardNorm;
		Vect rightNorm;

		pCam->GetHelper(up, tar, pos, upNorm, forwardNorm, rightNorm);

		// OK, now 3 points... pos, tar, up
		//     now 3 normals... upNorm, forwardNorm, rightNorm
		tar = pMan->obj;

		Matrix Trans(Matrix::Trans::XYZ, tar);
		Matrix NegTrans(Matrix::Trans::XYZ, -tar);
		Matrix Rot;
		Rot.set(Matrix::Rot::AxisAngle, rightNorm, -0.03f);

		Matrix M = NegTrans * Rot * Trans;

		up = up * M;
		pos = pos * M;
		tar = tar * M;

		pCam->SetHelper(up, tar, pos);
	}
}
