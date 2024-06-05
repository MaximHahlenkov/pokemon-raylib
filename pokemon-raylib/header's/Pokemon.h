#pragma once

#include <string>
#include <raylib.h>
#include <vector>

using namespace std;

enum class PokemonElement {
    Water,
    Electric,
    Ice,
    Fire,
    Grass,
};

struct Pokemon
{
    string Name;
    PokemonElement Element;
    int Hp;
    int Attack;
    int Defense;
    int Special_attack;
    int Energy;
    PokemonElement Weakness;

    Pokemon();
};

void Pokemon_File_to_mas(std::vector<Pokemon>& Poke);

void LoadTextures(std::vector<Pokemon>& Poke, std::vector<Texture2D>& PokeTexture);

void LoadTexturesM(std::vector<Pokemon>& Poke, std::vector<Texture2D>& PokeTextureM);

void UnloadTextures(std::vector<Texture2D>& PokeTexture);

void UnloadTexturesM(std::vector<Texture2D>& PokeTextureM);
     