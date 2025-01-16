#include <raylib.h>
#include <bits/stdc++.h>

// ---------- TODO -------------
// 1. Utilize OOP for the pieces ( Done )
// 2. Add Castling
// 3. Add en-passant
// 4. Add logic for check and checkmate


// ---------- Issues -----------
// 1. Check logic and Checkmate logic are not working

using namespace std;

const int SCREEN_WIDTH = 1024 + 128*3;
const int SCREEN_HEIGHT = 1024;
const int ROWS = 8;
const int COLS = 8;
bool no_moves_for_king = false;
bool Check = false;

typedef struct Vec2 {
    int x;
    int y;
} Vec2;

bool in_range(int num, int num1, int low, int high) {
    if(num <= high && num >= low && num1 >= low && num1 <= high) {
        return true;
    }
    return false;
}

bool same_case(char a, char b) {
     if((isupper(a) && isupper(b)) || (islower(a) && islower(b))) {
        return true;
     }
     return false;
}

bool is_opponent_king_check(vector<vector<char>> &board, vector<pair<int, int>> &possible_squares, char piece) {
    for(pair<int, int> p: possible_squares) {
        //for light pieces
        if(isupper(piece)) {
            if(board[p.second][p.first] == 'k') {
                return true;
            }
        }

        //for dark pieces
        else {
            if(board[p.second][p.first] == 'K') {
                return true;
            }
        }
    }
    return false;
}

class Piece {
    public:
        //piece moves
        vector<pair<int, int>> piece_moves;

        // to show diagonal possible moves
        int show_diagonal_moves(vector<vector<char>> &board, int x, int y, vector<pair<int, int>> &possible_squares, char piece, int max_level);

        // to show horizontal possible moves
        int show_moves_along_axes(vector<vector<char>> &board, int x, int y, vector<pair<int, int>> &possible_squares, char piece, int max_level);

        //to show rest possible moves
        virtual int show_rest_possible_moves(vector<vector<char>> &board, int x, int y, vector<pair<int, int>> &possible_squares, char piece)= 0; 

        //destructor
        virtual ~Piece() = default;
};

class Knight: public Piece {
    public:
        int show_rest_possible_moves(vector<vector<char>> &board, int x, int y, vector<pair<int, int>> &possible_squares, char piece) override {
           //eligible moves for knight
            piece_moves = {{y-1, x+2}, {y+1, x-2}, {y-2, x+1}, {y+2, x+1}, {y-2, x-1}, {y-1, x-2}, {y+2, x-1}, {y+1, x+2}};
            
            //White Knight
            if(piece == 'N') {
                for(const pair<int, int> &moves: piece_moves) {
                    //check for out of bounds and if the to pos is empty or enemy piece then move
                    if(moves.first >=0 && moves.first <=7 && moves.second >=0 && moves.second <= 7 && (board[moves.second][moves.first] == ' ' || islower(board[moves.second][moves.first]))) {
                        printf("first = %d, second = %d\n", moves.first, moves.second);
                        possible_squares.push_back(moves);
                    }
                }
            }

            //Black Knight
            else {
                for(const pair<int, int> &moves: piece_moves) {
                    //check for out of bounds and if the to pos is empty or enemy piece then move
                    if(in_range(moves.first, moves.second, 0, 7) && (board[moves.second][moves.first] == ' ' || isupper(board[moves.second][moves.first]))) {
                        possible_squares.push_back(moves);
                    }
                }
            }

            return possible_squares.size();
        }
};

class Pawn: public Piece {
    public:
        int show_rest_possible_moves(vector<vector<char>> &board, int x, int y, vector<pair<int, int>> &possible_squares, char piece) override {
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

            //eligible moves for black pawn
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

            return possible_squares.size();
        }
};

int Piece::show_diagonal_moves(vector<vector<char>> &board, int x, int y, vector<pair<int, int>> &possible_squares, char piece, int max_level) {
    int level = 1, piece_x = x, piece_y = y;
    bool q1 = true, q2 = true, q3 = true, q4 = true;
    while(level <= max_level) {
        // - -
        if(q1 && in_range(piece_x - level, piece_y - level, 0, 7)) {
            if(board[piece_x - level][piece_y - level] == ' ') {
                possible_squares.push_back({piece_y - level, piece_x - level});
            }
            else if(!same_case(board[piece_x - level][piece_y - level], piece)) {
                possible_squares.push_back({piece_y - level, piece_x - level});
                q1 = false;
            }
            else {
                q1 = false;
            }
        }
        // - +
        if(q2 && in_range(piece_x - level, piece_y + level, 0, 7)) {
            if(board[piece_x - level][piece_y + level] == ' ') {
                possible_squares.push_back({piece_y + level, piece_x - level});
            }
            else if(!same_case(board[piece_x - level][piece_y + level], piece)) {
                possible_squares.push_back({piece_y + level, piece_x - level});
                q2 = false;
            }
            else {
                q2 = false;
            }
        }
        // + +
        if(q3 && in_range(piece_x + level, piece_y + level, 0, 7)) {
            if(board[piece_x + level][piece_y + level] == ' ') {
                possible_squares.push_back({piece_y + level, piece_x + level});
            }
            else if(!same_case(board[piece_x + level][piece_y + level], piece)) {
                possible_squares.push_back({piece_y + level, piece_x + level});
                q3 = false;
            }
            else {
                q3 = false;
            }
        }
        // + -
        if(q4 && in_range(piece_x + level, piece_y - level, 0, 7)) {
            if(board[piece_x + level][piece_y - level] == ' ') {
                possible_squares.push_back({piece_y - level, piece_x + level});
            }
            else if(!same_case(board[piece_x + level][piece_y - level], piece)) {
                possible_squares.push_back({piece_y - level, piece_x + level});
                q4 = false;
            }
            else {
                q4 = false;
            }
        }
        level++;
    }
    return possible_squares.size();
}

int Piece::show_moves_along_axes(vector<vector<char>> &board, int x, int y, vector<pair<int, int>> &possible_squares, char piece, int max_level) {
    int level = 1;
    bool q1 = true, q2 = true, q3 = true, q4 = true;
    while(level <= max_level) {
        if(q1 && in_range(x - level, y, 0, 7)) {
            if(board[x - level][y] == ' ') {
                possible_squares.push_back({y, x - level});
            }
            else if(!same_case(board[x - level][y], piece)) {
                possible_squares.push_back({y, x - level});
                q1 = false;
            }
            else {
                q1 = false;
            }
        }
        if(q2 && in_range(x + level, y, 0, 7)) {
            if(board[x + level][y] == ' ') {
                possible_squares.push_back({y, x + level});
            }
            else if(!same_case(board[x + level][y], piece)) {
                possible_squares.push_back({y, x + level});
                q2 = false;
            }
            else {
                q2 = false;
            }
        }
        if(q3 && in_range(x, y - level, 0, 7)) {
           if(board[x][y - level] == ' ') {
                possible_squares.push_back({y - level, x});
            }
            else if(!same_case(board[x][y - level], piece)) {
                possible_squares.push_back({y - level, x});
                q3 = false;
            } 
            else {
                q3 = false;
            }
        }
        if(q4 && in_range(x, y + level, 0, 7)) {
           if(board[x][y + level] == ' ') {
                possible_squares.push_back({y + level, x});
            }
            else if(!same_case(board[x][y + level], piece)) {
                possible_squares.push_back({y + level, x});
                q4 = false;
            } 
            else {
                q4 = false;
            }
        }
        level++;
    }   
    return possible_squares.size();
}


vector<pair<int, int>> showPossibleSquares(vector<vector<char>> &board, int x, int y, char piece) {

    Knight k;
    Pawn p;

    vector<pair<int, int>> possible_squares;

    int no_of_moves = 0;

    //pawn moves
    if(piece == 'P' || piece == 'p') {
        no_of_moves = p.show_rest_possible_moves(board, x, y, possible_squares, piece);
    }

    //Knight moves
    else if(piece == 'N' || piece == 'n') {
        no_of_moves = k.show_rest_possible_moves(board, x, y, possible_squares, piece);
    }

    //bishop moves
    else if(piece == 'B' || piece == 'b') {
        no_of_moves = k.show_diagonal_moves(board, x, y, possible_squares, piece, 7);
    }

    //king moves
    else if(piece == 'K' || piece == 'k') {
        no_of_moves += k.show_moves_along_axes(board, x, y, possible_squares, piece, 1);
        no_of_moves += k.show_diagonal_moves(board, x, y, possible_squares, piece, 1);

        //Checking for checkmate
        if(no_of_moves == 0) {
            no_moves_for_king = true;
        }
        else {
            no_moves_for_king = false;
        }
    }

    //queen moves
    else if(piece == 'Q' || piece == 'q') {
        no_of_moves += k.show_diagonal_moves(board, x, y, possible_squares, piece, 7);
        no_of_moves += k.show_moves_along_axes(board, x, y, possible_squares, piece, 7);
    }

    //rook moves
    else if(piece == 'R' || piece == 'r') {
        no_of_moves = k.show_moves_along_axes(board, x, y, possible_squares, piece, 7);
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
    vector<pair<int, int>> possible_moves;

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


        if(selected_piece_x != -1){                       // this means a piece is selected
          vector<pair<int, int>> possible_squares = showPossibleSquares(board, selected_piece_y, selected_piece_x, board[selected_piece_y][selected_piece_x]);
          for(auto it: possible_squares){
            DrawCircle(it.first*128 + (128/2), it.second*128 + (128/2), 15, BLACK);
          }
        }

        if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            int mouse_x = GetMouseX()/128;
            int mouse_y = GetMouseY()/128;

            cout << mouse_x << " " << mouse_y << endl;

            //Check if the selected square is in bounds
            //moves for light pieces
            if(light_turn && mouse_x <=7 && mouse_y <= 7){

                //We want to move the selected piece
                if(isupper(board[mouse_y][mouse_x])){
                    if(selected_piece_x == -1 && selected_piece_y == -1 || (mouse_x != selected_piece_x || mouse_y != selected_piece_y)) {
                        move_piece_pos[0] = {mouse_x, mouse_y};
                    }
                    selected_piece_x = mouse_x;               //findng the x, y of selected piece
                    selected_piece_y = mouse_y;
                }

                //We want to move the selected piece to the selected square  
                else{
                    if(selected_piece_x == -1 && islower(board[mouse_y][mouse_x])) {
                        cout << "Invalid piece" << endl;
                    }
                    else if(selected_piece_x == -1 && board[mouse_y][mouse_x] == ' ') {
                        cout << "select a piece" << endl;
                    }
                    else {
                        cout << "move logic" << "\n";
                        move_piece_pos[1] = {mouse_x, mouse_y};
                        isMoved = move_piece_from_to(board, move_piece_pos);
                        if(isMoved) {
                            
                            //Checking if the opponent king is in check
                            possible_moves = showPossibleSquares(board, mouse_y, mouse_x, board[mouse_y][mouse_x]);
                            Check = is_opponent_king_check(board, possible_moves, board[mouse_y][mouse_x]);

                            if(Check && no_moves_for_king) {
                                cout << "White Won!!" << endl;
                            }

                            move_piece_pos = {{-1, -1}, {-1, -1}};
                            light_turn = false;
                            dark_turn = true;
                        }
                    }
                    selected_piece_x = -1;
                    selected_piece_y = -1;
                }  
            }
            
            //check if selected square is in bounds
            //moves for dark piece
            else if(dark_turn && mouse_x <=7 && mouse_y <= 7) {
                
                //We want to move the selected piece 
                if(islower(board[mouse_y][mouse_x])) {
                    if(selected_piece_x == -1 && selected_piece_y == -1 || (mouse_x != selected_piece_x || mouse_y != selected_piece_y)) {
                        move_piece_pos[0] = {mouse_x, mouse_y};
                    }
                    selected_piece_x = mouse_x;
                    selected_piece_y = mouse_y;
                }

                //We want to move the selected piece to the selected square
                else{
                    if(selected_piece_x == -1 && isupper(board[mouse_y][mouse_x])) {
                        cout << "Invalid Piece" << endl;
                    }
                    else {
                        move_piece_pos[1] = {mouse_x, mouse_y};
                        isMoved = move_piece_from_to(board, move_piece_pos);
                        if(isMoved) {

                            //Checking if the opponent king is in check
                            possible_moves = showPossibleSquares(board, mouse_x, mouse_y, board[mouse_y][mouse_x]);
                            Check = is_opponent_king_check(board, possible_moves, board[mouse_y][mouse_x]);

                            if(Check && no_moves_for_king) {
                                cout << "White Won!!" << endl;
                            }

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



