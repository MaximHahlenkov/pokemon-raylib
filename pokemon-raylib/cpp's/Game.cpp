#include <string>
#include "../header's/Game.h" 
#include "../header's/Pokemon.h"
#include <vector>
#include <raylib.h>
#include <raymath.h>
#include <rlgl.h>
#include "../header's/UI.h"

GameState::GameState() 
{
	WaitingForInput = true;
	Player1Move = true;
	Player2Move = false;
	SelectionOfPokemons = true;
	Fight = false;
	EndMenu = false;
	Game = true;
}

bool PokeEnergyCheck(string name, int energy, int mod)
{
	if (name == "Pikachu")
	{
		if (mod == 0) 
		{
			if (energy >= 20)
				return true;
			else
				return false;
		}
		else          
		{
			if (energy >= 60)
				return true;
			else
				return false;
		}
	}
	if (name == "Charmander")
	{
		if (mod == 0) 
		{
			if (energy >= 25)
				return true;
			else
				return false;
		}
		else          
		{
			if (energy >= 55)
				return true;
			else
				return false;
		}
	}
	if (name == "Vulpix")
	{
		if (mod == 0) 
		{
			if (energy >= 15)
				return true;
			else
				return false;
		}
		else          
		{
			if (energy >= 45)
				return true;
			else
				return false;
		}
	}
	if (name == "Squirtle")
	{
		if (mod == 0) 
		{
			if (energy >= 20)
				return true;
			else
				return false;
		}
		else          
		{
			if (energy >= 60)
				return true;
			else
				return false;
		}
	}
	if (name == "Bulbasaur")
	{
		if (mod == 0) 
		{
			if (energy >= 25)
				return true;
			else
				return false;
		}
		else          
		{
			if (energy >= 55)
				return true;
			else
				return false;
		}
	}
	if (name == "Lapras")
	{
		if (mod == 0)  
		{
			if (energy >= 25)
				return true;
			else
				return false;
		}
		else          
		{
			if (energy >= 55)
				return true;
			else
				return false;
		}
	}
}

void EnergyBalance(Player& Player, std::vector<Pokemon>& Poke)
{
	for (int i = 0; i < 3; i++) {
		int temp = 0;
		for (auto pk : Poke)
		{
			if (pk.Name == Player.PlayerPokemons[i].Name)
				temp = pk.Energy;

		}
		if (Player.PlayerPokemons[i].Energy < temp)
			Player.PlayerPokemons[i].Energy += 5;
	}
}

bool CheckPokemons(std::vector<Pokemon>& Poke)
{
	if (Poke[0].Hp <= 0 && Poke[1].Hp <= 0 && Poke[2].Hp <= 0)
		return false;
	return true;
}

void AttackFunc(int itrtPs, int itrtPok1, int itrtPok2, Player& Player1, Player& Player2) 
{
	if (itrtPs == 0)
	{
		if (Player1.PlayerPokemons[itrtPok1].Attack  - Player2.PlayerPokemons[itrtPok2].Defense * 0.5 >= Player2.PlayerPokemons[itrtPok2].Hp)
			Player2.PlayerPokemons[itrtPok2].Hp = 0;
		else
			Player2.PlayerPokemons[itrtPok2].Hp -= (Player1.PlayerPokemons[itrtPok1].Attack - Player2.PlayerPokemons[itrtPok2].Defense * 0.5);
		
		Player1.PlayerPokemons[itrtPok1].Energy -= 5;
	}
	else 
	{
		if (Player1.PlayerPokemons[itrtPok1].Element == Player2.PlayerPokemons[itrtPok2].Weakness)
		{
			if (Player1.PlayerPokemons[itrtPok1].Special_attack * 1.5 - Player2.PlayerPokemons[itrtPok2].Defense * 0.7 >= Player2.PlayerPokemons[itrtPok2].Hp)
				Player2.PlayerPokemons[itrtPok2].Hp = 0;
			else 
				Player2.PlayerPokemons[itrtPok2].Hp -= (Player1.PlayerPokemons[itrtPok1].Special_attack * 1.5 - Player2.PlayerPokemons[itrtPok2].Defense * 0.7);

			Player1.PlayerPokemons[itrtPok1].Energy -= 30;
		}
		else
		{
			if (Player1.PlayerPokemons[itrtPok1].Special_attack - Player2.PlayerPokemons[itrtPok2].Defense * 0.7 >= Player2.PlayerPokemons[itrtPok2].Hp)
				Player2.PlayerPokemons[itrtPok2].Hp = 0;
			else
				Player2.PlayerPokemons[itrtPok2].Hp -= (Player1.PlayerPokemons[itrtPok1].Special_attack - Player2.PlayerPokemons[itrtPok2].Defense * 0.7);

			Player1.PlayerPokemons[itrtPok1].Energy -= 30;
		}
	}
}



void FightSystem(Player& Player1, Player& Player2, GameState& Game, std::vector<Pokemon>& Poke, std::vector<Texture2D> Textures, std::vector<Texture2D> TexturesM, std::vector<Texture2D>& UITextures, Texture2D& Arrow)
{
	string P_1 = Player1.Name + " 's move";
	string P_2 = Player2.Name + " 's move";
	Color color[2] = { GRAY, GOLD };
	Color colorAtk[2] = { GRAY, BLACK };
	Color colorFight[2] = { GRAY,WHITE };

	std::vector<Vector2> Pok1 = { {500,270}, {470, 605}, {610,930} };
	std::vector<Vector2> Pok2 = { {1320,210}, {1350, 545}, {1210,870} };
	std::vector<Vector2> Pos1 = { {90,120},{30, 455},{200, 780} };
	std::vector<Vector2> Pos2 = { {1410,120},{1470, 455},{1300, 780} };
	std::vector<Vector2> Ps = { {1090,450},{1090,510}, {1035,570} };


	int itrt = 0;
	int itrtPs = 0;
	int itrtPok1 = 0;
	int itrtPok2 = 0;
	int itrtAtk1 = 0;
	int itrtAtk2 = 0;
	
	bool FlagPok1 = false;
	bool FlagPok2 = false;
	bool Atk1 = false;
	bool Atk2 = false;
	bool SkipMove = false;
	
	while (Game.Fight) 
	{
		BeginDrawing();
		ClearBackground(WHITE);

		rlDrawRenderBatchActive();
		Matrix proj = MatrixOrtho(0, 1920, 1080, 0, -1, 1);
		rlSetMatrixProjection(proj);
		
		DrawText("Fight!", 25, 30, 50, BLACK);
		DrawText(P_1.c_str(), 25, 80, 30, color[Game.Player1Move]);
		DrawText(P_2.c_str(), 1730 - Player2.Name.size() * 16, 80, 30, color[Game.Player2Move]);
		
		if (!CheckPokemons(Player1.PlayerPokemons) || !CheckPokemons(Player2.PlayerPokemons))
		{
			Game.Player1Move = false;
			Game.Player2Move = false;
			Game.EndMenu = true;
			Game.Fight = false;
		}

		for (auto pk1 : Player1.PlayerPokemons)
		{
			if (pk1.Name == "Pikachu")
			{
				DrawTextureEx(TexturesM[0], Pos1[itrt], 0, 0.3f, colorFight[pk1.Hp > 0]);
				if (pk1.Hp > 0) 
				{
					DrawHpEnergy(UITextures, Player1.PlayerPokemons, Pos1, itrt);
					DrawText("Electric", Pos1[itrt].x + 300, Pos1[itrt].y + 130, 30, GOLD);
				}
			}
			if (pk1.Name == "Charmander")
			{
				DrawTextureEx(TexturesM[1], Pos1[itrt], 0, 0.3f, colorFight[pk1.Hp > 0]);
				if (pk1.Hp > 0)
				{
					DrawHpEnergy(UITextures, Player1.PlayerPokemons, Pos1, itrt);
					DrawText("Fire", Pos1[itrt].x + 300, Pos1[itrt].y + 130, 30, ORANGE);
				}
			}
			if (pk1.Name == "Vulpix")
			{
				DrawTextureEx(TexturesM[2], Pos1[itrt], 0, 0.3f, colorFight[pk1.Hp > 0]);
				if (pk1.Hp > 0)
				{
					DrawHpEnergy(UITextures, Player1.PlayerPokemons, Pos1, itrt);
					DrawText("Fire", Pos1[itrt].x + 300, Pos1[itrt].y + 130, 30, ORANGE);

				}
			}
			if (pk1.Name == "Squirtle")
			{
				DrawTextureEx(TexturesM[3], Pos1[itrt], 0, 0.3f, colorFight[pk1.Hp > 0]);
				if (pk1.Hp > 0)
				{
					DrawHpEnergy(UITextures, Player1.PlayerPokemons, Pos1, itrt);
					DrawText("Water", Pos1[itrt].x + 300, Pos1[itrt].y + 130, 30, BLUE);
				}
			}
			if (pk1.Name == "Bulbasaur")
			{
				DrawTextureEx(TexturesM[4], Pos1[itrt], 0, 0.3f, colorFight[pk1.Hp > 0]);
				if (pk1.Hp > 0)
				{
					DrawHpEnergy(UITextures, Player1.PlayerPokemons, Pos1, itrt);
					DrawText("Grass", Pos1[itrt].x + 300, Pos1[itrt].y + 130, 30, GREEN);
				}
			}
			if (pk1.Name == "Lapras")
			{
				DrawTextureEx(TexturesM[5], Pos1[itrt], 0, 0.3f, colorFight[pk1.Hp > 0]);
				if (pk1.Hp > 0)
				{
					DrawHpEnergy(UITextures, Player1.PlayerPokemons, Pos1, itrt);
					DrawText("Ice", Pos1[itrt].x + 300, Pos1[itrt].y + 130, 30, SKYBLUE);

				}
			}
			itrt++;
		}
		itrt = 0;
		
		for (auto pk2 : Player2.PlayerPokemons)
		{
			if (pk2.Name == "Pikachu")
			{
				DrawTextureEx(Textures[0], Pos2[itrt], 0, 0.3f, colorFight[pk2.Hp > 0]);
				if (pk2.Hp > 0)
				{
					DrawHpEnergy(UITextures, Player2.PlayerPokemons, Pos2, itrt);
					DrawText("Electric", Pos2[itrt].x + 300, Pos2[itrt].y + 130, 30, GOLD);
				}
			}
			if (pk2.Name == "Charmander")
			{
				DrawTextureEx(Textures[1], Pos2[itrt], 0, 0.3f, colorFight[pk2.Hp > 0]);
				if (pk2.Hp > 0)
				{
					DrawHpEnergy(UITextures, Player2.PlayerPokemons, Pos2, itrt);
					DrawText("Fire", Pos2[itrt].x + 300, Pos2[itrt].y + 130, 30, ORANGE);

				}
			}
			if (pk2.Name == "Vulpix")
			{
				DrawTextureEx(Textures[2], Pos2[itrt], 0, 0.3f, colorFight[pk2.Hp > 0]);
				if (pk2.Hp > 0)
				{
					DrawHpEnergy(UITextures, Player2.PlayerPokemons, Pos2, itrt);
					DrawText("Fire", Pos2[itrt].x + 300, Pos2[itrt].y + 130, 30, ORANGE);
				}
			}
			if (pk2.Name == "Squirtle")
			{
				DrawTextureEx(Textures[3], Pos2[itrt], 0, 0.3f, colorFight[pk2.Hp > 0]);
				if (pk2.Hp > 0)
				{
					DrawHpEnergy(UITextures, Player2.PlayerPokemons, Pos2, itrt);
					DrawText("Water", Pos2[itrt].x + 300, Pos2[itrt].y + 130, 30, BLUE);

				}
			}
			if (pk2.Name == "Bulbasaur")
			{
				DrawTextureEx(Textures[4], Pos2[itrt], 0, 0.3f, colorFight[pk2.Hp > 0]);
				if (pk2.Hp > 0)
				{
					DrawHpEnergy(UITextures, Player2.PlayerPokemons, Pos2, itrt);
					DrawText("Grass", Pos2[itrt].x + 300, Pos2[itrt].y + 130, 30, GREEN);

				}
			}
			if (pk2.Name == "Lapras")
			{
				DrawTextureEx(Textures[5], Pos2[itrt], 0, 0.3f, colorFight[pk2.Hp > 0]);
				if (pk2.Hp > 0)
				{
					DrawHpEnergy(UITextures, Player2.PlayerPokemons, Pos2, itrt);
					DrawText("Ice", Pos2[itrt].x + 300, Pos2[itrt].y + 130, 30, SKYBLUE);

				}
			}
			itrt++;
		}
		itrt = 0;

		if (Game.Player1Move)
		{
			DrawTextureEx(Arrow, Pok1[itrtPok1], 270.f, 1, WHITE);

			if (!FlagPok1) 
			{
				if (itrtPok1 > 0 && IsKeyPressed(KEY_W))
					itrtPok1--;

				if (itrtPok1 < 2 && IsKeyPressed(KEY_S))
					itrtPok1++;			
			}
			
			if (IsKeyPressed(KEY_E) && Player1.PlayerPokemons[itrtPok1].Hp > 0) 
				FlagPok1 = true;

			if (IsKeyPressed(KEY_F) && !Atk1 && !SkipMove)
				FlagPok1 = false;
			
			if (FlagPok1)
			{
				DrawText("Normal attack", 800, 400, 40, colorAtk[PokeEnergyCheck(Player1.PlayerPokemons[itrtPok1].Name, Player1.PlayerPokemons[itrtPok1].Energy, 0)]);
				DrawText("Special attack", 800, 460, 40, colorAtk[PokeEnergyCheck(Player1.PlayerPokemons[itrtPok1].Name, Player1.PlayerPokemons[itrtPok1].Energy, 1)]);
				DrawText("Skip move", 838, 520, 40, BLACK);

				DrawTextureEx(Arrow, Ps[itrtPs], 270.f, .7f, WHITE);
				if (!Atk1 && !SkipMove)
				{
					if (itrtPs > 0 && IsKeyPressed(KEY_W))
						itrtPs--;

					if (itrtPs < 2 && IsKeyPressed(KEY_S))
						itrtPs++;
				}

				if (itrtPs == 0) 
				{
					DrawText("Deals", 780, 600, 40, BLACK);
					DrawText(TextFormat("%i", Player1.PlayerPokemons[itrtPok1].Attack), 910, 600, 40, GRAY);
					DrawText(" damage", 950, 600, 40, BLACK);
				}
				if (itrtPs == 1)
				{
					DrawText("Deals", 780, 600, 40, BLACK);
					DrawText(TextFormat("%i", Player1.PlayerPokemons[itrtPok1].Special_attack),910, 600, 40, GRAY);
					DrawText(" damage", 950, 600, 40, BLACK);
					DrawText("+ 1.5 multiplier against: ", 710, 640, 40, GRAY);
					Weak(Player1.PlayerPokemons[itrtPok1].Element, 900, 680);
				}
				if (!Atk1 && IsKeyPressed(KEY_R) && PokeEnergyCheck(Player1.PlayerPokemons[itrtPok1].Name, Player1.PlayerPokemons[itrtPok1].Energy, itrtPs) && itrtPs != 2)
				{
					Atk1 = true;
				}
				else if (!Atk1 && IsKeyPressed(KEY_R) && itrtPs == 2)
				{
					SkipMove = true;
				}
				if (SkipMove) 
				{
					DrawText("Do you want to skip move? (E if yes | F if no)", 500, 600, 40, GRAY);
					if (IsKeyPressed(KEY_E))
					{
						SkipMove = false;
						EnergyBalance(Player2, Poke);
						Atk1 = false;
						itrtPok1 = 0;
						FlagPok1 = false;
						itrtPs = 0;
						Game.Player1Move = false;
						Game.Player2Move = true;
					}
					if (IsKeyPressed(KEY_F))
					{
						SkipMove = false;
					}
				}

				if (Atk1)
				{
					DrawTextureEx(Arrow, Pok2[itrtAtk1], 90.f, 1, WHITE);

					if (itrtAtk1 > 0 && IsKeyPressed(KEY_W))
						itrtAtk1--;

					if (itrtAtk1 < 2 && IsKeyPressed(KEY_S))
						itrtAtk1++;

					if (IsKeyPressed(KEY_F))
					{
						Atk1 = false;
					}

					if (IsKeyPressed(KEY_E) && Player2.PlayerPokemons[itrtAtk1].Hp > 0)
					{
						AttackFunc(itrtPs, itrtPok1, itrtAtk1, Player1, Player2);
						DrawText("Attack", 100, 100, 20, RED);
						EnergyBalance(Player2, Poke);
						Atk1 = false;
						itrtPok1 = 0;
						FlagPok1 = false;
						itrtPs = 0;
						Game.Player1Move = false;
						Game.Player2Move = true;
					}
				}
			}
			//DEV FUNC
			if (IsKeyPressed(KEY_C))
			{
				Game.Player1Move = false;
				Game.Player2Move = true;
				EnergyBalance(Player2, Poke);
			}

		}
		if (Game.Player2Move)
		{
			DrawTextureEx(Arrow, Pok2[itrtPok2], 90.f, 1, WHITE);
			if(!FlagPok2)
			{
				if (itrtPok2 > 0 && IsKeyPressed(KEY_I))
					itrtPok2--;

				if (itrtPok2 < 2 && IsKeyPressed(KEY_K))
					itrtPok2++;
			}

			if (IsKeyPressed(KEY_U) && Player2.PlayerPokemons[itrtPok2].Hp > 0)
				FlagPok2 = true;

			if (IsKeyPressed(KEY_H) && !Atk2 && !SkipMove)
				FlagPok2 = false;

			if (FlagPok2)
			{
				DrawText("Normal attack", 800, 400, 40, colorAtk[PokeEnergyCheck(Player2.PlayerPokemons[itrtPok2].Name, Player2.PlayerPokemons[itrtPok2].Energy, 0)]);
				DrawText("Special attack", 800, 460, 40, colorAtk[PokeEnergyCheck(Player2.PlayerPokemons[itrtPok2].Name, Player2.PlayerPokemons[itrtPok2].Energy, 1)]);
				DrawText("Skip move", 838, 520, 40, BLACK);
				
				DrawTextureEx(Arrow, Ps[itrtPs], 270.f, .7f, WHITE);
				if (!Atk2 && !SkipMove)
				{
					if (itrtPs > 0 && IsKeyPressed(KEY_I))
						itrtPs--;

					if (itrtPs < 2 && IsKeyPressed(KEY_K))
						itrtPs++;
				}

				if (itrtPs == 0)
				{
					DrawText("Deals", 780, 600, 40, BLACK);
					DrawText(TextFormat("%i", Player2.PlayerPokemons[itrtPok2].Attack), 910, 600, 40, GRAY);
					DrawText(" damage", 950, 600, 40, BLACK);
				}
				else if (itrtPs == 1)
				{
					DrawText("Deals", 780, 600, 40, BLACK);
					DrawText(TextFormat("%i", Player2.PlayerPokemons[itrtPok2].Special_attack), 910, 600, 40, GRAY);
					DrawText(" damage", 950, 600, 40, BLACK);
					DrawText("+ 1.5 multiplier against: ", 710, 640, 40, GRAY);
					Weak(Player2.PlayerPokemons[itrtPok2].Element, 900, 680);
				}


				if (!Atk2 && IsKeyPressed(KEY_Y) && PokeEnergyCheck(Player2.PlayerPokemons[itrtPok2].Name, Player2.PlayerPokemons[itrtPok2].Energy, itrtPs) && itrtPs != 2)
				{
					Atk2 = true;
				}	
				else if (!Atk2 && IsKeyPressed(KEY_Y) && itrtPs == 2)
				{
					SkipMove = true;
				}
				if (SkipMove)
				{
					DrawText("Do you want to skip move? (U if yes | H if no)", 500, 600, 40, GRAY);
					if (IsKeyPressed(KEY_U))
					{
						SkipMove = false;
						EnergyBalance(Player1, Poke);
						itrtPok2 = 0;
						Atk2 = false;
						FlagPok2 = false;
						itrtPs = 0;
						Game.Player1Move = true;
						Game.Player2Move = false;
					}
					if (IsKeyPressed(KEY_H))
					{
						SkipMove = false;
					}
				}

				if (Atk2)
				{
					DrawTextureEx(Arrow, Pok1[itrtAtk2], 270.f, 1, WHITE);

					if (itrtAtk2 > 0 && IsKeyPressed(KEY_I))
						itrtAtk2--;

					if (itrtAtk2 < 2 && IsKeyPressed(KEY_K))
						itrtAtk2++;

					if (IsKeyPressed(KEY_H))
					{
						Atk2 = false;
					}

					if (IsKeyPressed(KEY_U) && Player1.PlayerPokemons[itrtAtk2].Hp > 0)
					{
						DrawText("Attack", 100, 100, 20, RED);
						AttackFunc(itrtPs, itrtPok2, itrtAtk2, Player2, Player1);
						EnergyBalance(Player1, Poke);
						itrtPok2 = 0;
						Atk2 = false;
						FlagPok2 = false;
						itrtPs = 0;
						Game.Player2Move = false;
						Game.Player1Move = true;
					}
				}
			}
			//DEV FUNC
			if (IsKeyPressed(KEY_V))
			{

				EnergyBalance(Player1, Poke);
				Game.Player1Move = true;
				Game.Player2Move = false;
			}
		}

		EndDrawing();
	} 
}
