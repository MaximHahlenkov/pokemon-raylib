#include <iostream>
#include <raylib.h>
#include "../header's/UI.h";
#include "../header's/Game.h"
#include "../header's/Pokemon.h"
#include <vector>
#include <string>
#include <raymath.h>
#include <rlgl.h>

const char* PokemonElementNames[] = {
	"Water",
	"Electric",
	"Ice",
	"Fire",
	"Grass",
};

void StartMenu(GameState& Game)
{
	bool flag = true; 
	int res = 0;
	while (Game.WaitingForInput)
	{
		BeginDrawing();
		
		rlDrawRenderBatchActive();
		Matrix proj = MatrixOrtho(0, 1920, 1080, 0, -1, 1);
		rlSetMatrixProjection(proj);

		ClearBackground(WHITE);
		if (IsKeyPressed(GetKeyPressed()))
			Game.WaitingForInput = false;

		DrawText("Pro100Max0n present's:", 480, 360, 80, BLACK);
		DrawText("Pokekeki!",  690, 490, res, BLACK);
		DrawText("Press any key to continue",  615, 780, 50, BLACK);
		
		if (res < 120 && flag)
			res++;
		if (res > 100 && !flag)
			res--;
		if (res == 120)
			flag = false;
		if (res == 100)
			flag = true;
		EndDrawing();
	}

}

void DrawHpEnergy(std::vector<Texture2D>& TexturesUI, std::vector<Pokemon>& Poke, std::vector<Vector2>& Pos, int itrt)
{
	DrawText(TextFormat("%i", Poke[itrt].Hp), Pos[itrt].x + 360, Pos[itrt].y + 10, 30, RED);
	DrawText(TextFormat("%i", Poke[itrt].Energy), Pos[itrt].x + 360, Pos[itrt].y + 70, 30, GOLD);
	DrawTexture(TexturesUI[0], Pos[itrt].x + 290, Pos[itrt].y, WHITE);
	DrawTexture(TexturesUI[2], Pos[itrt].x + 290, Pos[itrt].y + 60, WHITE);
}

void Weak(PokemonElement Elem, int x, int y)
{
	if (Elem == PokemonElement::Electric)
		DrawText("Ice", x, y, 40, SKYBLUE);

	if (Elem == PokemonElement::Ice)
		DrawText("Electric", x - 45, y, 40, GOLD);

	if (Elem == PokemonElement::Fire)
	{
		DrawText("Water", x - 140, y, 40, BLUE);
		DrawText(" and ", x - 20, y, 40, GRAY);
		DrawText("Electric", x + 80, y, 40, GOLD);
	}

	if (Elem == PokemonElement::Water)
		DrawText("Grass", x - 20, y, 40, GREEN);

	if (Elem == PokemonElement::Grass)
		DrawText("Fire", x - 5, y, 40, ORANGE);
}

bool CheckPick(std::vector<int>& pick, int n)
{
	for (auto p : pick)
	{
		if (n == p)
			return false;
	}
	return true;
}

vector<Color> PokElem(string Name) 
{
	if (Name == "Pikachu")
		return {GOLD,SKYBLUE};
	
	if (Name == "Charmander")
		return { ORANGE,BLUE };
	
	if (Name == "Vulpix")
		return { ORANGE,GOLD };
	
	if (Name == "Squirtle")
		return { BLUE,GREEN};
	
	if (Name == "Bulbasaur")
		return { GREEN,ORANGE };
	
	if (Name == "Lapras")
		return { SKYBLUE,GOLD };
	
}

void DrawStats(std::vector<Pokemon>& Poke, float x, float y, int itrt) 
{
	DrawText(TextFormat("%i",Poke[itrt].Hp), x, y, 30,RED);
	DrawText(TextFormat("%i", Poke[itrt].Attack), x, y+30, 30, BLACK);
	DrawText(TextFormat("%i", Poke[itrt].Energy), x, y+60, 30, GOLD);
	DrawText(TextFormat("%i", Poke[itrt].Defense), x, y+90, 30,GRAY);
}

void SelectionMenu(GameState& Game, std::vector<Texture2D> UITextures, std::vector<Texture2D>& Textures, std::vector<Pokemon>& Poke, Player& Player1, Player& Player2, Texture2D& texture, Texture2D& P1, Texture2D& P2)
{
	int CountChoPok = 0;
	string P_1 = Player1.Name + " 's choice";
	string P_2 = Player2.Name + " 's choice";
	Color color[2] = { GRAY, GOLD};
	int Arr_x = 30;
	bool Flag1 = false;
	bool Flag2 = false;
	bool CancelFlag = false;
	vector<int> PickedPokemons;

	while (Game.SelectionOfPokemons) 
	{
		BeginDrawing();
		
		rlDrawRenderBatchActive();
		Matrix proj = MatrixOrtho(0, 1920, 1080, 0, -1, 1);
		rlSetMatrixProjection(proj);

		ClearBackground(WHITE);
		
		if (CountChoPok == 6)
			Game.SelectionOfPokemons = false;

		DrawText("Selection Menu: ", 25, 50, 50, BLACK);
		DrawText(P_1.c_str(), 25, 100, 30, color[Game.Player1Move]);
		DrawText(P_2.c_str(), 1730 - Player2.Name.size()*16, 100, 30, color[Game.Player2Move]);
		
		float y = 640.f;
		float x = 10.f;
		int itrt = 0;
		
		for (auto Texture : Textures)
	    {
			DrawTextureEx(Texture, Vector2{ x, 230.f }, 0.f, .3f, WHITE);
			DrawText(Poke[itrt].Name.c_str(), x, 550, 40, BLACK);
			DrawStats(Poke, x + 40, y, itrt);
			DrawText(PokemonElementNames[(int)Poke[itrt].Element], x + 10, y - 45, 30, PokElem(Poke[itrt].Name)[0]);
			for (auto TextureUI : UITextures)
			{
				DrawTextureEx(TextureUI, Vector2{ x, y }, 0.f, .5f, WHITE);
				y += 30.f;

			}
			y = 640.f;
			x += 325.f;
			itrt++;
		}
		
		if (!PickedPokemons.empty()) 
		{
			for (int i = 0; i < PickedPokemons.size(); ++i) 
			{
				if (i % 2 == 0) 
					DrawTexture(P1,PickedPokemons[i]*325+90,180,WHITE);
				
				else 
					DrawTexture(P2, PickedPokemons[i] * 325 + 90, 180, WHITE);
			}	
		}


		if (Flag1)
			DrawText("Are you sure you want pick this Pokemon? (Press R / Yes) | (Press F / No)", 240, 980, 40, BLACK);
		if (Flag2)
			DrawText("Are you sure you want pick this Pokemon? (Press Y / Yes) | (Press H / No)", 240, 980, 40, BLACK);

		
		if(CancelFlag)
			DrawText("This Pokemon alredy was picked", 240, 980, 40, BLACK);


		if(Game.Player1Move)
		{
			DrawTexture(texture, Arr_x, 800, BLACK);			
			if (IsKeyPressed(KEY_E)) 
			{
				Flag1 = true;
				CancelFlag = false;
			}
			
			if (IsKeyPressed(KEY_F))
				Flag1 = false;

			if (!Flag1) 
			{
				if (IsKeyPressed(KEY_D) && Arr_x < 1500)
					Arr_x += 325;

				if (IsKeyPressed(KEY_A) && Arr_x > 40)
					Arr_x -= 325;
			}
			
			if (Flag1 && IsKeyPressed(KEY_R)) 
			{
				if (CheckPick(PickedPokemons, (int)(Arr_x / 325))) 
				{
					Player1.PlayerPokemons.push_back(Poke[(int)(Arr_x / 325)]);
					PickedPokemons.push_back((int)(Arr_x / 325));
					CountChoPok++;
					Flag1 = false;
					Game.Player1Move = false;
					Game.Player2Move = true;

				}
				else 
				{
					Flag1 = false;
					CancelFlag = true;
				}
			}
		}
		
		if (Game.Player2Move)
		{

			DrawTexture(texture, Arr_x, 800, BLACK);
			if (IsKeyPressed(KEY_U))
			{
				Flag2 = true;
				CancelFlag = false;
			}

			if (IsKeyPressed(KEY_H))
				Flag2 = false;

			if (!Flag2)
			{
				if (IsKeyPressed(KEY_L) && Arr_x < 1500)
					Arr_x += 325;

				if (IsKeyPressed(KEY_J) && Arr_x > 40)
					Arr_x -= 325;
			}

			if (Flag2 && IsKeyPressed(KEY_Y))
			{
				if (CheckPick(PickedPokemons, (int)(Arr_x / 325)))
				{
					Player2.PlayerPokemons.push_back(Poke[(int)(Arr_x / 325)]);
					PickedPokemons.push_back((int)(Arr_x / 325));
					CountChoPok++;
					Flag2 = false;
					Game.Player2Move = false;
					Game.Player1Move = true;

				}
				else
				{
					Flag2 = false;
					CancelFlag = true;
				}
			}
		}

		EndDrawing();
	}
	Game.Fight = true;
}

void EndMenu(GameState& Game, Player& Player) 
{
	while (Game.EndMenu)
	{
		BeginDrawing();
		
		rlDrawRenderBatchActive();
		Matrix proj = MatrixOrtho(0, 1920, 1080, 0, -1, 1);
		rlSetMatrixProjection(proj);

		ClearBackground(WHITE);

		if (IsKeyPressed(KEY_V))
		{
			Game.Game = false;
			Game.EndMenu = false;
		}

		int temp = 0;
		for (Pokemon pk : Player.PlayerPokemons) 
		{
			if (pk.Hp == 0)
				temp++;
		}
			
		DrawText("Thanks for playing POKEKEKI by Pro100Max0n ver 1.0", 400, 200, 40, BLACK);
		DrawText("If you want support me ( Sber | Tinkoff | Gazprombank ) : ", 400, 300, 40, BLACK);
		DrawText("+7 904-084 26 43", 400, 400, 40, BLACK);
		DrawText("Press V to exit", 800, 950, 30, BLACK);
		if(temp != 3)
			DrawText("1P Wins!!!", 800, 650, 60, BLACK);
		else
			DrawText("2P Wins!!!", 800, 650, 60, BLACK);

		EndDrawing();
	}	
}

void LoadUITextures(std::vector<Texture2D>& UITextures) 
{
	string texts[] = {"Heart", "Fist", "Energy", "Shield"};
	for (auto tx : texts) 
	{
		string filename = "texturesPokemon/" + tx + ".png";
		UITextures.push_back(LoadTexture(filename.c_str()));
	}
}

void UnLoadUITextures(std::vector<Texture2D>& UITextures) 
{
	for (auto tx : UITextures) 
	{
		UnloadTexture(tx);
	}
}