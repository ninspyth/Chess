#include <raylib.h>
#include <bits/stdc++.h>

using namespace std;

const int SCREEN_WIDTH = 1024 + 128*3;
const int SCREEN_HEIGHT = 1024;
const int ROWS = 8;
const int COLS = 8;

vector<pair<int, int>> showPossibleSquares(vector<vector<char>> &board, int x, int y){
   vector<pair<int, int>> possible_squares;
   if(board[x][y] == 'P'){
      possible_squares.push_back(make_pair(y,x-1));
      possible_squares.push_back(make_pair(y,x-2));
   }
   return possible_squares;
}


int main() {
    //chess board
    vector<vector<char>> board = {
        {'r', 'n', 'b', 'q', 'k', 'b', 'n', 'r'},           //small case indicates dark coins
        {'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p'},
        {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
        {'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P'},           //capital case indicates light coins
        {'R', 'N', 'B', 'Q', 'K', 'B', 'N', 'R'}
    };

    int selected_piece_x = -1;
    int selected_piece_y = -1;


    bool light_turn = true;
    bool dark_turn = false;

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Chess");

    //Dark Square
    Image dark_square = LoadImage(".\\assets\\pieces&board\\square brown dark_png_128px.png");
    Texture2D dark_square_texture = LoadTextureFromImage(dark_square);


    // Dark canvas for right margin
    ImageResize(&dark_square, 128*3, 128*4);
    Texture2D dark_canvas = LoadTextureFromImage(dark_square);
    UnloadImage(dark_square);


    //LightSquare
    Image light_square = LoadImage(".\\assets\\pieces&board\\square brown light_png_128px.png");
    Texture2D light_square_texture = LoadTextureFromImage(light_square);

    //Light canvas for right margin
    ImageResize(&light_square, 128*3, 128*4);
    Texture2D light_canvas = LoadTextureFromImage(light_square);
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
    int prev = 1;       //if prev is 1, we print light square, else dark
    int piece_x;
    int piece_y;

    // ToggleFullscreen();


    RenderTexture2D boardTexture = LoadRenderTexture(SCREEN_WIDTH, SCREEN_HEIGHT);

    // Pre-render board for efficiency
    BeginTextureMode(boardTexture);
    ClearBackground(WHITE);
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if ((i + j) % 2 == 0) {
                DrawTexture(light_square_texture, j * 128, i * 128, WHITE);
            } else {
                DrawTexture(dark_square_texture, j * 128, i * 128, WHITE);
            }
        }
    }
    EndTextureMode();

    SetTargetFPS(10);
    while(!WindowShouldClose()) {
        ClearBackground(WHITE);
        
        BeginDrawing();
        
        //Generate the chess board
        DrawTexture(boardTexture.texture, 0, 0, WHITE);

        //placing the pieces on the board
        for(int i=0; i<8; i++) {
            for(int j=0; j<8; j++) {
                piece_x = j*128 + 15;       //computing the coordinates of x for a coin
                piece_y = i*128 + 15;       //computing the coordinates of y for a coin
                switch(board[i][j]) { 
                    case 'r':
                        DrawTexture(b_rook_texture, piece_x, piece_y, WHITE);      
                        break;  
                    case 'R':
                        DrawTexture(w_rook_texture, piece_x, piece_y, WHITE);      
                        break;
                    case 'n':
                        DrawTexture(b_knight_texture, piece_x, piece_y, WHITE);      
                        break;
                    case 'N':
                        DrawTexture(w_knight_texture, piece_x, piece_y, WHITE);      
                        break;
                    case 'b':
                        DrawTexture(b_bishop_texture, piece_x, piece_y, WHITE);      
                        break;
                    case 'B':
                        DrawTexture(w_bishop_texture, piece_x, piece_y, WHITE);      
                        break;
                    case 'q':
                        DrawTexture(b_queen_texture, piece_x, piece_y, WHITE);      
                        break;
                    case 'Q':
                        DrawTexture(w_queen_texture, piece_x, piece_y, WHITE);      
                        break;
                    case 'k':
                        DrawTexture(b_king_texture, piece_x, piece_y, WHITE);      
                        break;
                    case 'K':
                        DrawTexture(w_king_texture, piece_x, piece_y, WHITE);      
                        break;
                    case 'p':
                        DrawTexture(b_pawn_texture, piece_x, piece_y, WHITE);      
                        break;
                    case 'P':
                        DrawTexture(w_pawn_texture, piece_x, piece_y, WHITE);      
                        break;
                };
            }
        }

        // Drawing dark canvas on right
        DrawTexture(dark_canvas, 128*8, 0, WHITE);

        // Drawing light canvas on right
        DrawTexture(light_canvas, 128*8, 128*4, WHITE);

        if(selected_piece_x != -1){
          vector<pair<int, int>> possible_squares = showPossibleSquares(board, selected_piece_y, selected_piece_x);
          for(auto it: possible_squares){
            DrawCircle(it.first*128 + (128/2), it.second*128 + (128/2), 15, GREEN);
          }
        }

        if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
         
            int mouse_x = GetMouseX()/128;
            int mouse_y = GetMouseY()/128;

            if(light_turn){
               
               if((int)board[mouse_y][mouse_x] > 65 && (int)board[mouse_y][mouse_x] < 90){
                  
                  selected_piece_x = mouse_x;
                  selected_piece_y = mouse_y;
               }else{
                  selected_piece_x = -1;
                  selected_piece_y = -1;
               }
               
            }else{
               if(board[mouse_y][mouse_x] > 97 && board[mouse_y][mouse_x] < 122){
                  selected_piece_x = mouse_x;
                  selected_piece_y = mouse_y;
               }else{
                  selected_piece_x = -1;
                  selected_piece_y = -1;
               }
            }
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



