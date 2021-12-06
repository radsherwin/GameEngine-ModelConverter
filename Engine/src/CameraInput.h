#ifndef CAMERA_INPUT_H
#define CAMERA_INPUT_H

#include "Camera.h"
#include "CameraManager.h"

class Keyboard;

namespace Azul
{
	class CameraInput : public Align16
	{
	public:
		CameraInput(GLFWwindow* _window);
		CameraInput() =delete;
		CameraInput(const CameraInput&) = delete;
		CameraInput& operator=(const CameraInput&) = delete;
		~CameraInput() = default;

		void SwitchCamera(Keyboard* pKey);
		void PlayDemo(Keyboard* pKey);
		void DemoChangeSpeed(Keyboard* pKey);

		static void Create(GLFWwindow* _window);
		static void Destroy();
		static void Update();

	private:
		static CameraInput* privGetInstance();

	private:
		Vect obj;
		GLFWwindow* pWindow; //Temporary, not sure if I want CameraInput to point to GLFWwindow currently, but it's easy to read for demo
		static CameraInput* posInstance;
		int mode = 1;
	};
}

#endif