//
// Created by Neemaxon on 01.03.2026.
//

#include <filament/FilamentAPI.h>
#include <filament/Box.h>
#include <filament/Engine.h>
#include <QMainWindow>
#include <filament/View.h>

using namespace filament;

void start3dobfuscation(QMainWindow* window) {
    Engine* engine = Engine::create();
    SwapChain* swapChain = engine->createSwapChain(window);
    Renderer* renderer = engine->createRenderer();
}