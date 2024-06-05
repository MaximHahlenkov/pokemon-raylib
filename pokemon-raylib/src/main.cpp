#include <iostream>
#include <raylib.h>
#include <raymath.h>
#include <rlgl.h>
#include "../header's/Pokemon.h"
#include "../header's/Game.h"
#include "../header's/UI.h"

using namespace std;

//1p: wasd - navigation
//    e - use
//    r - yes
//    f - no
//2p: ijkl - navigation
//    u - use
//    y - yes
//    h - no


int main() {

    int screenWidth = 1920;
    int screenHeight = 1080;

    SetConfigFlags(FLAG_WINDOW_RESIZABLE | FLAG_VSYNC_HINT);
    InitWindow(screenWidth, screenHeight, "POKEKEKI by Pro100Max0n ver 1.0");

    SetTargetFPS(60);               

    if (IsWindowResized() && !IsWindowFullscreen())
    {
        screenWidth = GetScreenWidth();
        screenHeight = GetScreenHeight();
    }

    if (IsKeyPressed(KEY_ENTER) && (IsKeyDown(KEY_LEFT_ALT) || IsKeyDown(KEY_RIGHT_ALT)))
    {
        int display = GetCurrentMonitor();

        if (IsWindowFullscreen())
        {
            SetWindowSize(screenWidth, screenHeight);
        }
        else
        {
            SetWindowSize(GetMonitorWidth(display), GetMonitorHeight(display));
        }
        ToggleFullscreen();
    }

    Texture2D ArrowUI = LoadTexture("texturesPokemon/Arrow.png");
    Texture2D P1 = LoadTexture("texturesPokemon/1P.png");
    Texture2D P2 = LoadTexture("texturesPokemon/2P.png");

    vector<Pokemon> Poke;
    Pokemon_File_to_mas(Poke);
    
    vector<Texture2D> Textures;
    LoadTextures(Poke, Textures);

    vector<Texture2D> TexturesM;
    LoadTexturesM(Poke, TexturesM);

    vector<Texture2D> UITextures;
    LoadUITextures(UITextures);
    
    GameState Game;
    
    Player Player1;
    Player Player2;

    Player1.Name = "1P";
    Player2.Name = "2P";

    while (!WindowShouldClose()) {
        BeginDrawing();
        
        rlDrawRenderBatchActive();
        Matrix proj = MatrixOrtho(0, screenWidth, screenHeight, 0, -1, 1);
        rlSetMatrixProjection(proj);
        
        ClearBackground(WHITE);
        DrawFPS(1890, 1050);

        if (Game.Game) 
        {
            StartMenu(Game);

            SelectionMenu(Game, UITextures, Textures, Poke, Player1, Player2, ArrowUI, P1, P2);

            FightSystem(Player1, Player2, Game, Poke, Textures, TexturesM, UITextures, ArrowUI);

            EndMenu(Game, Player1);
        }

        EndDrawing();
    }
    UnloadTexture(ArrowUI);
    UnloadTexture(P1);
    UnloadTexture(P2);
    UnloadTextures(Textures);
    UnloadTexturesM(TexturesM);
    UnLoadUITextures(UITextures);
    CloseWindow();
    return 0;
}