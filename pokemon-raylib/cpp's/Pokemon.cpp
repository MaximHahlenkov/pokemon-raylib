#include <fstream>
#include <string>
#include <raylib.h>
#include <vector>
#include "..\header's\Pokemon.h"

using namespace std;

Pokemon::Pokemon() {
	Name = " - ";
	Element = (PokemonElement)0;
	Weakness = (PokemonElement)0;
	Hp = 0;
	Attack = 0;
	Defense = 0;
	Special_attack = 0;
	Energy = 0;
}

void Pokemon_File_to_mas(std::vector<Pokemon>& Poke)
{
	ifstream File;
	File.open("Pokemon.txt");
	string line;
	Pokemon pokemon;
	int Element;
	int Weakness;
	if (File.is_open()) 
	{
		while (File >> pokemon.Name >> Element >> pokemon.Hp >> pokemon.Attack >> pokemon.Defense >> pokemon.Special_attack >> pokemon.Energy >> Weakness) {
			pokemon.Element = (PokemonElement)Element;
			pokemon.Weakness = (PokemonElement)Weakness;
			Poke.push_back(pokemon);
		}
	}	
	File.close();
}



void LoadTextures(std::vector<Pokemon>& Poke, std::vector<Texture2D>& PokeTexture) 
{
	for (auto Pk : Poke) 
	{
		string FileName = "texturesPokemon/" + Pk.Name + ".png";
		PokeTexture.push_back(LoadTexture(FileName.c_str()));	
	}

}

void UnloadTextures(std::vector<Texture2D>& PokeTexture) 
{
	for (auto tx : PokeTexture) 
	{
		UnloadTexture(tx);
	}

}

void LoadTexturesM(std::vector<Pokemon>& Poke, std::vector<Texture2D>& PokeTextureM)
{
	for (auto Pk : Poke)
	{
		string FileName = "texturesPokemon/" + Pk.Name + "M.png";
		PokeTextureM.push_back(LoadTexture(FileName.c_str()));
	}

}

void UnloadTexturesM(std::vector<Texture2D>& PokeTextureM)
{
	for (auto tx : PokeTextureM)
	{
		UnloadTexture(tx);
	}

}