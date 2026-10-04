// Copyright 2026 Renan Surian

#include "CameraController.h"
#include <iostream>

CameraController::CameraController() {

    this->camera = Camera3D { 0 };
    // Camera position
    this->camera.position = (Vector3){ 0.0f, 10.0f, 10.0f };
    // Camera looking at point
    this->camera.target = (Vector3){ 0.0f, 0.0f, 0.0f };  
    // Camera up vector (rotation towards target)
    this->camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };
    // Camera field-of-view Y
    this->camera.fovy = 60.0f;
    this->camera.projection = CAMERA_PERSPECTIVE;

    this->lockView = false;
    this->rotateAroundTarget = true;
    this->rotateUp = false;
    this->moveInWorldPlane = true;
}

void CameraController::update() {

    Vector3 currentPosition = this->camera.position;

    // Get movement input
    this->movement = (Vector3){
        // Move forward-backward
        (IsKeyDown(KEY_W) || IsKeyDown(KEY_UP))*0.1f -
        (IsKeyDown(KEY_S) || IsKeyDown(KEY_DOWN))*0.1f,
        // Move right-left
        (IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT))*0.1f -
        (IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT))*0.1f,
        // Move up-down
        0.0f
    };

    Vector3 rotation = (Vector3){
        // Rotation: yaw
        IsMouseButtonDown(MOUSE_BUTTON_MIDDLE) ? (GetMouseDelta().x * 0.05f) : 0.0f,
        // Rotation: pitch
        IsMouseButtonDown(MOUSE_BUTTON_MIDDLE) ? (GetMouseDelta().y * 0.05f) : 0.0f,
        // Rotation: roll
        0.0f
    };

    // Camera movement
    CameraMoveForward(&this->camera, this->movement.x, this->moveInWorldPlane);
    CameraMoveRight(&this->camera, this->movement.y, this->moveInWorldPlane);
    CameraMoveUp(&this->camera, this->movement.z);

    // Camera rotation
    CameraPitch(&this->camera, -rotation.y*DEG2RAD, this->lockView, this->rotateAroundTarget, this->rotateUp);
    CameraYaw(&this->camera, -rotation.x*DEG2RAD, this->rotateAroundTarget);
    CameraRoll(&this->camera, rotation.z*DEG2RAD);

    // Zoom target distance
    CameraMoveToTarget(&this->camera, GetMouseWheelMove()*2.0f * -1.0f);

    // enforce camera position constraints
    if (this->camera.position.y < 2.0f) {
        this->camera.position = currentPosition;
    }
}

Camera3D CameraController::getCamera() {
    return this->camera;
}
