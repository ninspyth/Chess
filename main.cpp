#include <raylib.h>
#include <bits/stdc++.h>

using namespace std;

const int SCREEN_WIDTH = 1024;
const int SCREEN_HEIGHT = 1024;
//test commit for developer branc "dev"
int main() {
    //chess board
    vector<vector<char>> board = {
        {'R', 'N', 'B', 'Q', 'K', 'B', 'N', 'R'},
        {'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P'},
        {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
        {'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P'},
        {'R', 'N', 'B', 'Q', 'K', 'B', 'N', 'R'}
    };

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Chess");

    //Dark Square
    Image dark_square = LoadImage(".\\assets\\pieces&board\\square brown dark_png_128px.png");
    Texture2D dark_square_texture = LoadTextureFromImage(dark_square);
    UnloadImage(dark_square);

    //LightSquare
    Image light_square = LoadImage(".\\assets\\pieces&board\\square brown light_png_128px.png");
    Texture2D light_square_texture = LoadTextureFromImage(light_square);
    UnloadImage(light_square);

    //black rook
    Image b_rook = LoadImage(".\\assets\\pieces&board\\b_rook_png_128px.png");
    ImageResize(&b_rook, 100, 100);
    Texture2D b_rook_texture = LoadTextureFromImage(b_rook);
    UnloadImage(b_rook);

    //black knight
    Image b_knight = LoadImage(".\\assets\\pieces&board\\b_knight_png_128px.png");
    ImageResize(&b_knight, 100, 100);
    Texture2D b_knight_texture = LoadTextureFromImage(b_knight);
    UnloadImage(b_knight);

    //black bishop
    Image b_bishop = LoadImage(".\\assets\\pieces&board\\b_bishop_png_128px.png");
    ImageResize(&b_bishop, 100, 100);
    Texture2D b_bishop_texture = LoadTextureFromImage(b_bishop);
    UnloadImage(b_bishop);

    //black Queen
    Image b_queen = LoadImage(".\\assets\\pieces&board\\b_queen_png_128px.png");
    ImageResize(&b_queen, 100, 100);
    Texture2D b_queen_texture = LoadTextureFromImage(b_queen);
    UnloadImage(b_queen);

    //black King
    Image b_king = LoadImage(".\\assets\\pieces&board\\b_king_png_128px.png");
    ImageResize(&b_king, 100, 100);
    Texture2D b_king_texture = LoadTextureFromImage(b_king);
    UnloadImage(b_king);

    //black pawn
    Image b_pawn = LoadImage(".\\assets\\pieces&board\\b_pawn_png_128px.png");
    ImageResize(&b_pawn, 100, 100);
    Texture2D b_pawn_texture = LoadTextureFromImage(b_pawn);
    UnloadImage(b_pawn);

    //white rook
    Image w_rook = LoadImage(".\\assets\\pieces&board\\w_rook_png_128px.png");
    ImageResize(&w_rook, 100, 100);
    Texture2D w_rook_texture = LoadTextureFromImage(w_rook);
    UnloadImage(w_rook);

    //white knight
    Image w_knight = LoadImage(".\\assets\\pieces&board\\w_knight_png_128px.png");
    ImageResize(&w_knight, 100, 100);
    Texture2D w_knight_texture = LoadTextureFromImage(w_knight);
    UnloadImage(w_knight);

    //white bishop
    Image w_bishop = LoadImage(".\\assets\\pieces&board\\w_bishop_png_128px.png");
    ImageResize(&w_bishop, 100, 100);
    Texture2D w_bishop_texture = LoadTextureFromImage(w_bishop);
    UnloadImage(w_bishop);

    //white Queen
    Image w_queen = LoadImage(".\\assets\\pieces&board\\w_queen_png_128px.png");
    ImageResize(&w_queen, 100, 100);
    Texture2D w_queen_texture = LoadTextureFromImage(w_queen);
    UnloadImage(w_queen);

    //white King
    Image w_king = LoadImage(".\\assets\\pieces&board\\w_king_png_128px.png");
    ImageResize(&w_king, 100, 100);
    Texture2D w_king_texture = LoadTextureFromImage(w_king);
    UnloadImage(w_king);

    //white pawn
    Image w_pawn= LoadImage(".\\assets\\pieces&board\\w_pawn_png_128px.png");
    ImageResize(&w_pawn, 100, 100);
    Texture2D w_pawn_texture = LoadTextureFromImage(w_pawn);
    UnloadImage(w_pawn);

    Vector2 square_pos = {(float)128, (float)128};
    int prev = 1;       //to switch between light and dark square.
    int piece_x;
    int piece_y;

    // ToggleFullscreen();

    while(!WindowShouldClose()) {
        ClearBackground(WHITE);
        
        BeginDrawing();
        
        //Generate the chess board
        for(int i = 0; i < 8; i++) {
            for(int j = 0; j < 8; j++) {
                if(prev == 1) {
                    DrawTexture(light_square_texture, (int)square_pos.x*j, (int)square_pos.y*i, WHITE);
                    prev = 0;
                }
                else {
                    DrawTexture(dark_square_texture, (int)square_pos.x*j, (int)square_pos.y*i, WHITE);
                    prev = 1;
                }
            }
            if(prev == 0) {
                prev = 1;
            }
            else {
                prev = 0;
            }
        }

        //placing the pieces on the board
        for(int i=0; i<8; i++) {
            for(int j=0; j<8; j++) {
                switch(board[i][j]) {
                    case 'R':
                        piece_x = i * 128 + 15;
                        piece_y = j * 128 + 15;
                        if(j < 2)
                            DrawTexture(b_rook_texture, piece_x, piece_y, WHITE);      
                        else
                            DrawTexture(w_rook_texture, piece_x, piece_y, WHITE); 
                        break;  
                    case 'N':
                        piece_x = i * 128 + 15;
                        piece_y = j * 128 + 15;
                        if(i < 2)
                            DrawTexture(b_knight_texture, piece_y, piece_x, WHITE);      
                        else
                            DrawTexture(w_knight_texture, piece_y, piece_x, WHITE); 
                        break;
                    case 'B':
                        piece_x = i * 128 + 15;
                        piece_y = j * 128 + 15;
                        if(i < 2)
                            DrawTexture(b_bishop_texture, piece_y, piece_x, WHITE);      
                        else
                            DrawTexture(w_bishop_texture, piece_y, piece_x, WHITE); 
                        break;
                    case 'Q':
                        piece_x = i * 128 + 15;
                        piece_y = j * 128 + 15;
                        if(i < 2)
                            DrawTexture(b_queen_texture, piece_y, piece_x, WHITE);      
                        else
                            DrawTexture(w_queen_texture, piece_y, piece_x, WHITE); 
                        break;
                    case 'K':
                        piece_x = i * 128 + 15;
                        piece_y = j * 128 + 15;
                        if(i < 2)
                            DrawTexture(b_king_texture, piece_y, piece_x, WHITE);      
                        else
                            DrawTexture(w_king_texture, piece_y, piece_x, WHITE); 
                        break;
                    case 'P':
                        piece_x = i * 129 + 15;
                        piece_y = j * 128 + 15;
                        if(i < 2)
                            DrawTexture(b_pawn_texture, piece_y, piece_x, WHITE);      
                        else
                            DrawTexture(w_pawn_texture, piece_y, piece_x, WHITE); 
                        break;
                };
            }
        }
        if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            int mouse_x = GetMouseX();
            int mouse_y = GetMouseY();
            cout << mouse_x / 128 << " " << mouse_y / 128 << "\n";
        }

        EndDrawing();
    } 
    UnloadTexture(w_rook_texture);
    UnloadTexture(w_bishop_texture);
    UnloadTexture(w_king_texture);
    UnloadTexture(w_queen_texture);
    UnloadTexture(w_knight_texture);
    UnloadTexture(w_pawn_texture);
    UnloadTexture(b_bishop_texture);
    UnloadTexture(b_king_texture);
    UnloadTexture(b_knight_texture);
    UnloadTexture(b_pawn_texture);
    UnloadTexture(b_queen_texture);
    UnloadTexture(b_rook_texture);
    CloseWindow(); 
    return 0;
}