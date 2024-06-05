#pragma once
#include <iostream>
#include <raylib.h>
#include "../header's/Game.h"
#include "../header's/Pokemon.h"
#include <vector>

void StartMenu(GameState& Game);

void SelectionMenu(GameState& Game, std::vector<Texture2D> UITextures, std::vector<Texture2D>& Textures, std::vector<Pokemon>& Poke, Player& Player1, Player& Player2, Texture2D& texture, Texture2D& P1, Texture2D& P2);

void DrawStats(std::vector<Pokemon>& Poke, float x, float y, int itrt);

void LoadUITextures(std::vector<Texture2D>& UITextures);

void UnLoadUITextures(std::vector<Texture2D>& UITextures);

bool CheckPick(std::vector<int>& pick, int n);

void EndMenu(GameState& Game, Player& Player);

void Weak(PokemonElement Elem, int x, int y);

void DrawHpEnergy(std::vector<Texture2D>& TexturesUI, std::vector<Pokemon>& Poke, std::vector<Vector2>& Pos, int itrt);

vector<Color> PokElem(string Name);
