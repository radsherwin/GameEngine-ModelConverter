//----------------------------------------------------------------------------
// Copyright 2021, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#ifndef CAMERA_MANAGER_H
#define CAMERA_MANAGER_H 

#include "Camera.h"
#include "CameraMesh.h"
#include "CameraNode.h"

namespace Azul
{
    class CameraManager
    {

        //----------------------------------------------------------------------
        // Constructor
        //----------------------------------------------------------------------
    private:
        CameraManager();
        CameraManager(const CameraManager&) = delete;
        CameraManager& operator=(const CameraManager&) = delete;
        ~CameraManager() = default;

        //----------------------------------------------------------------------
        // Static Methods
        //----------------------------------------------------------------------
    public:
        static void Create();
        static void Destroy();

        static void Add(Camera::ID _cameraID, const float fovDeg, const float nearDist, const float farDist, const int width, const int height);
        static void AddMesh(CameraMesh* _mesh);
        static Camera* Find(Camera::ID _cameraID);
        static void SetCurrent(Camera::ID _cameraID);
        static Camera* CurrentCamera();

        static void MainCamera();
        static void TopCamera();
        static void ForwardCamera();
        static void SideCamera();

        static void Update();

        //----------------------------------------------------------------------
        // Private methods
        //----------------------------------------------------------------------
    private:
        static CameraManager* privGetInstance();
        void privAddToFront(CameraLink* node, CameraLink*& head);
        void privRemove(CameraLink* pNode, CameraLink*& poHead);


        //----------------------------------------------------------------------
        // Data: unique data for this manager 
        //----------------------------------------------------------------------
    private:
        CameraLink* poActive;
        Camera* pCurCamera;
        CameraMesh* pCameraMesh;
    };
}




#endif