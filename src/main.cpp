/*
Raylib example file.
This is an example main file for a simple raylib project.
Use this as a starting point or replace it with your code.

by Jeffery Myers is marked with CC0 1.0. To view a copy of this license, visit https://creativecommons.org/publicdomain/zero/1.0/

*/
#include <iostream>

#include "raylib.h"

#include "rcamera.h"

#include "CameraController.h"
# include "Cell.h"

#include "resource_dir.h"	// utility header for SearchAndSetResourceDir


static Mesh GenMeshCustom(void);

int main ()
{
	// Tell the window to use vsync and work on high DPI displays
	SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI);

	// Create the window and OpenGL context
	InitWindow(800, 600, "Hello Raylib");

	// Utility function from resource_dir.h to find the resources folder and set it as the current working directory so we can load from it
	SearchAndSetResourceDir("resources");

	// Load a texture from the resources directory
	Texture wabbit = LoadTexture("wabbit_alpha.png");

	// Define the camera to look into our 3d world
	CameraController cameraController;

    Vector3 cubePosition = { 0.0f, 0.0f, 0.0f };

	//Model terrain = LoadModelFromMesh(GenMeshCustom());

    Cell cell(0, 0, 0);
    Model terrain = LoadModelFromMesh(cell.mesh);
	
	// game loop
	while (!WindowShouldClose())		// run the loop until the user presses ESCAPE or presses the Close button on the window
	{

		cameraController.update();

		// drawing
		BeginDrawing();

			ClearBackground(BLACK);

			BeginMode3D(cameraController.getCamera());

				//DrawCube(cubePosition, 2.0f, 2.0f, 2.0f, RED);
				//DrawCubeWires(cubePosition, 2.0f, 2.0f, 2.0f, MAROON);
				 DrawModel(terrain, cubePosition, 1.0f, WHITE);

				DrawGrid(10, 1.0f);

			EndMode3D();

			DrawFPS(10, 10);
		
		// end the frame and get ready for the next one  (display frame, poll input, etc...)
		EndDrawing();
	}

	// cleanup
	// unload our texture so it can be cleaned up
	UnloadTexture(wabbit);

	// destroy the window and cleanup the OpenGL context
	CloseWindow();
	return 0;
}


static Mesh GenMeshCustom(void)
{
    Mesh mesh = { 0 };
    mesh.triangleCount = 1;
    mesh.vertexCount = mesh.triangleCount*3;
    mesh.vertices = (float *)MemAlloc(mesh.vertexCount*3*sizeof(float));    // 3 vertices, 3 coordinates each (x, y, z)
    mesh.texcoords = (float *)MemAlloc(mesh.vertexCount*2*sizeof(float));   // 3 vertices, 2 coordinates each (x, y)
    mesh.normals = (float *)MemAlloc(mesh.vertexCount*3*sizeof(float));     // 3 vertices, 3 coordinates each (x, y, z)

    //       +Y (Up)
    //          |
    //          |   -Z (Forward / Depth into screen)
    //          |  /
    //          | /
    //          |/____________ +X (Right / Horizontal)
    //         /
    //        /
    //       /
    //    +Z (Backward / Out of screen toward you)

    // Vertex at (0, 0, 0)
    mesh.vertices[0] = 0;
    mesh.vertices[1] = 0;
    mesh.vertices[2] = -1;
    mesh.normals[0] = 0;
    mesh.normals[1] = 0;
    mesh.normals[2] = 0;
    mesh.texcoords[0] = 0;
    mesh.texcoords[1] = 0;

    // Vertex at (1, 0, 2)
    mesh.vertices[3] = 1;
    mesh.vertices[4] = 0;
    mesh.vertices[5] = 2;
    mesh.normals[3] = 0;
    mesh.normals[4] = 0;
    mesh.normals[5] = 0;
    mesh.texcoords[2] = 0.5f;
    mesh.texcoords[3] = 1.0f;

    // Vertex at (2, 0, 0)
    mesh.vertices[6] = 2;
    mesh.vertices[7] = 0;
    mesh.vertices[8] = 0;
    mesh.normals[6] = 0;
    mesh.normals[7] = 0;
    mesh.normals[8] = 0;
    mesh.texcoords[4] = 1;
    mesh.texcoords[5] =0;

    // Upload mesh data from CPU (RAM) to GPU (VRAM) memory
    UploadMesh(&mesh, false);

    return mesh;
}