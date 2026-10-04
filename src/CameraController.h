#ifndef CAMERACONTROLLER_H
#define CAMERACONTROLLER_H

#include "raylib.h"
#include "rcamera.h"

class CameraController {

    private:
        Camera3D camera;
        Vector3 movement;

        bool lockView;
        bool rotateAroundTarget;
        bool rotateUp;
        bool moveInWorldPlane;

    public:
        CameraController();

        void update();

        Camera3D getCamera();
};


#endif