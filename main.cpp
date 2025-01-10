#include <raylib.h>
#include <bits/stdc++.h>

using namespace std;

typedef struct Vec2 {
    int x;
    int y;
} Vec2;

const int SCREEN_WIDTH = 1024 + 128*3;
const int SCREEN_HEIGHT = 1024;
const int ROWS = 8;
const int COLS = 8;

bool in_range(int num, int num1, int low, int high) {
    if(num <= high && num >= low && num1 >= low && num1 <= high) {
        return true;
    }
    return false;
}

vector<pair<int, int>> showPossibleSquares(vector<vector<char>> &board, int x, int y, char piece){
    vector<pair<int, int>> possible_squares, piece_moves;

    if(piece == 'P'){
        if(in_range(x-1, y, 0, 7) && board[x-1][y] == ' ') {
            possible_squares.push_back({y,x-1});
        }
        if(x == 6 && board[x-2][y] == ' ') {
            possible_squares.push_back({y,x-2});
        }
        if(in_range(x-1, y+1, 0, 7) && islower(board[x-1][y+1])) {
            possible_squares.push_back({y+1, x-1});
        }
        if(in_range(x-1, y-1, 0, 7) && islower(board[x-1][y-1])) {
            possible_squares.push_back({y-1, x-1});
        }
    }
    else if(piece == 'p') {
        if(in_range(x+1, y, 0, 7) && board[x+1][y] == ' ') {
            possible_squares.push_back({y, x+1});
        }
        if(x== 1 && board[x+2][y] == ' ') {
            possible_squares.push_back({y, x+2});
        }
        if(in_range(x+1, y-1, 0, 7) && isupper(board[x+1][y-1])) {
            possible_squares.push_back({y-1, x+1});
        }
        if(in_range(x+1, y+1, 0, 7) && isupper(board[x+1][y+1])) {
            possible_squares.push_back({y+1, x+1});
        }
    }

    //Knight possible moves
    else if(piece == 'N' || piece == 'n') {
        piece_moves = {{y-1, x+2}, {y+1, x-2}, {y-2, x+1}, {y+2, x+1}, {y-2, x-1}, {y-1, x-2}, {y+2, x-1}, {y+1, x+2}};
        
        if(piece == 'N') {
            for(const pair<int, int> &moves: piece_moves) {
                //check for out of bounds and if the to pos is empty or enemy piece then move
                if(moves.first >=0 && moves.first <=7 && moves.second >=0 && moves.second <= 7 && (board[moves.second][moves.first] == ' ' || islower(board[moves.second][moves.first]))) {
                    printf("first = %d, second = %d\n", moves.first, moves.second);
                    possible_squares.push_back(moves);
                }
            }
        }
        else {
            for(const pair<int, int> &moves: piece_moves) {
                //check for out of bounds and if the to pos is empty or enemy piece then move
                if(in_range(moves.first, moves.second, 0, 7) && (board[moves.second][moves.first] == ' ' || isupper(board[moves.second][moves.first]))) {
                    possible_squares.push_back(moves);
                }
            }
        }
    } 

    return possible_squares;
}

bool move_piece_from_to(vector<vector<char>> &board, vector<pair<int, int>> move_piece_pos) {
    //initialize from pos and to pos
    Vec2 from, to;
    from.x = move_piece_pos[0].first, from.y = move_piece_pos[0].second;
    to.x = move_piece_pos[1].first, to.y = move_piece_pos[1].second;
    vector<pair<int, int>> possible_moves = showPossibleSquares(board, from.y, from.x, board[from.y][from.x]);  

    //move logic for all pieces
    for(pair<int, int> moves: possible_moves) {
        if(moves.first == to.x && moves.second == to.y) {
            board[to.y][to.x] = board[from.y][from.x];
            board[from.y][from.x] = ' ';
            return true;
        }
    }
    return false;
}

bool Checkmate = false;

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
    bool isMoved = false;

    // ToggleFullscreen();

    vector<pair<int, int>> move_piece_pos(2, {-1, -1});

    RenderTexture2D boardTexture = LoadRenderTexture(SCREEN_WIDTH, SCREEN_HEIGHT);

    // Pre-render board for efficiency
    BeginTextureMode(boardTexture);
    ClearBackground(WHITE);
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if ((i + j) % 2 == 0) {
                DrawRectangle(j * 128, i * 128, 128, 128, LIGHTGRAY); 
            } else {
                DrawRectangle(j * 128, i * 128, 128, 128, DARKGRAY);
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

        // // Drawing dark canvas on right
        // DrawTexture(dark_canvas, 128*8, 0, WHITE);

        // // Drawing light canvas on right
        // DrawTexture(light_canvas, 128*8, 128*4, WHITE);

        if(Checkmate) {
           //End Game 
        }

        if(selected_piece_x != -1){                       // this means a piece is selected
          vector<pair<int, int>> possible_squares = showPossibleSquares(board, selected_piece_y, selected_piece_x, board[selected_piece_y][selected_piece_x]);
          for(auto it: possible_squares){
            DrawCircle(it.first*128 + (128/2), it.second*128 + (128/2), 15, GREEN);
          }
        }

        if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            int mouse_x = GetMouseX()/128;
            int mouse_y = GetMouseY()/128;

            cout << mouse_x << " " << mouse_y << endl;

            if(light_turn && mouse_x <=7 && mouse_y <= 7){
                if(isupper(board[mouse_y][mouse_x])){
                    if(selected_piece_x == -1 && selected_piece_y == -1 || (mouse_x != selected_piece_x || mouse_y != selected_piece_y)) {
                        cout << "hello" << "\n";
                        move_piece_pos[0] = {mouse_x, mouse_y};
                    }
                    selected_piece_x = mouse_x;               //findng the x, y of selected piece
                    selected_piece_y = mouse_y;
                    // printf("from.x = %d, from.y = %d\n", move_piece_pos[0].first, move_piece_pos[0].second);
                    // printf("piece_x = %d, piece_y = %d\n", selected_piece_x, selected_piece_y);
                }
                else{
                    if(selected_piece_x == -1 && islower(board[mouse_y][mouse_x])) {
                        cout << "Invalid piece" << endl;
                    }
                    else {
                        cout << "move logic" << "\n";
                        move_piece_pos[1] = {mouse_x, mouse_y};
                        isMoved = move_piece_from_to(board, move_piece_pos);
                        if(isMoved) {
                            move_piece_pos = {{-1, -1}, {-1, -1}};
                            light_turn = false;
                            dark_turn = true;
                        }
                    }
                    selected_piece_x = -1;
                    selected_piece_y = -1;
                }  
            }
            else if(dark_turn && mouse_x <=7 && mouse_y <= 7) {
                if(islower(board[mouse_y][mouse_x])) {
                    if(selected_piece_x == -1 && selected_piece_y == -1 || (mouse_x != selected_piece_x || mouse_y != selected_piece_y)) {
                        cout << "hello" << "\n";
                        move_piece_pos[0] = {mouse_x, mouse_y};
                    }
                    selected_piece_x = mouse_x;
                    selected_piece_y = mouse_y;
                }
                else{
                    if(selected_piece_x == -1 && isupper(board[mouse_y][mouse_x])) {
                        cout << "Invalid Piece" << endl;
                    }
                    else {
                        // cout << "move logic" << "\n";
                        move_piece_pos[1] = {mouse_x, mouse_y};
                        isMoved = move_piece_from_to(board, move_piece_pos);
                        if(isMoved) {
                            move_piece_pos = {{-1, -1}, {-1, -1}};
                            light_turn = true;
                            dark_turn = false;
                        }
                    }
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



