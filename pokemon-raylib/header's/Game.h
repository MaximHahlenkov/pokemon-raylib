#pragma once
#include <string>
#include "../header's/Pokemon.h" 
#include <vector>
#include <raylib.h>

struct GameState 
{
	bool Player1Move;
	bool Player2Move;
	bool WaitingForInput;
	bool SelectionOfPokemons;
	bool Fight;
	bool EndMenu;
	bool Game;
	GameState();
};

struct Player 
{
	string Name;
	std::vector<Pokemon> PlayerPokemons;
};

void FightSystem(Player& Player1, Player& Player2, GameState& Game, std::vector<Pokemon>& Poke, std::vector<Texture2D> Textures, std::vector<Texture2D> TexturesM, std::vector<Texture2D>& UITextures, Texture2D& Arrow);

bool CheckPokemons(std::vector<Pokemon>& Poke);

void AttackFunc(int itrtPs, int itrtPok1, int itrtPok2, Player& Player1, Player& Player2);

void EnergyBalance(Player& Player, std::vector<Pokemon>& Poke);

bool PokeEnergyCheck(string name, int energy, int mod);
	