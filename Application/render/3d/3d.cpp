//
// Created by Neemaxon on 01.03.2026.
//
// system libraries
#include <string>

// filament libraries
#include <filament/FilamentAPI.h>
#include <filament/Box.h>
#include <filament/View.h>
#include <filament/Skybox.h>
#include <filament/Color.h>
#include <filament/Engine.h>

// Qt6 libraries
#include <QMainWindow>

using namespace std;

void Start3DObfuscation(QMainWindow* window) {
    using namespace filament;

    Engine* engine = Engine::create();
    SwapChain* swapChain = engine->createSwapChain(window);
    Renderer* renderer = engine->createRenderer();
}

void AddMesh(string MeshProperties) {

}

void AddLight(string LightProperties) {

}