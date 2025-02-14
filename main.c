#include "raylib.h"

const int screenWidth = 1920; 
const int screenHeight = 1080;


typedef struct {
    Rectangle rect;
    Color col;
    bool isOn;
} Player;

typedef enum {
    STATE_GAME,
    STATE_MENU,
    STATE_QUIT_GAME
} GameState;

typedef struct {
    Rectangle rect;
    Color col;
}Button;

int main(){
    // SetConfigFlags(FLAG_WINDOW_RESIZABLE); si on veut pouvoire resize la fenetre 
    InitWindow(screenWidth, screenHeight, "Rogue - Sock");
    SetExitKey(KEY_NULL);
    SetTargetFPS(144);

    bool ExitWinReq = false;
    bool ExitWin = false;
    bool touchingBorder = false;

    GameState currentScene = STATE_GAME;

    Player player = { 
        .rect = { 350.0f, 250.0f, 100.0f, 100.0f },
        .col = BLUE,
        .isOn = true
    };
    

    Button btnPlay = {
        .rect = {300, 200, 200, 50},
        .col = DARKGRAY
    };
    Button btnQuit = {
        .rect = {300, 300, 200, 50},
        .col = DARKGRAY
    };

    int speed = 5;

    while(!WindowShouldClose()){
        Vector2 mousePos = GetMousePosition();

        if (IsKeyPressed(KEY_ESCAPE)) {
            if (currentScene == STATE_GAME) {
                currentScene = STATE_MENU;
            } else if (currentScene == STATE_MENU) {
                currentScene = STATE_GAME;
            }
        }

        if (currentScene == STATE_MENU) {
            // Changer la couleur si la souris est sur un bouton
            btnPlay.col = CheckCollisionPointRec(mousePos, btnPlay.rect) ? LIGHTGRAY : DARKGRAY;
            btnQuit.col = CheckCollisionPointRec(mousePos, btnQuit.rect) ? LIGHTGRAY : DARKGRAY;

            // Actions si on clique sur un bouton
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                if (CheckCollisionPointRec(mousePos, btnPlay.rect)) {
                    currentScene = STATE_GAME;  // Reprendre le jeu
                }
                if (CheckCollisionPointRec(mousePos, btnQuit.rect)) {
                    currentScene = STATE_QUIT_GAME;
                }
            }
        }
        if (currentScene == STATE_QUIT_GAME) {
            player.isOn = false;
            if (IsKeyPressed(KEY_Y)) {
                CloseWindow();
                return 0;
            }
            if (IsKeyPressed(KEY_N)) {
                player.isOn = true;
                currentScene = STATE_MENU;  // Retour au menu
            }
        }

        if(currentScene == STATE_GAME){
            touchingBorder = false;
            // deplacer le rectangle
            if(IsKeyDown(KEY_RIGHT)){
                player.rect.x += speed;
            }
            if(IsKeyDown(KEY_LEFT)){
                player.rect.x -= speed;
            }
            if(IsKeyDown(KEY_UP)){
                player.rect.y -= speed;
            }
            if(IsKeyDown(KEY_DOWN)){
                player.rect.y += speed;
            }
            // empecher le rectangle de sortir de la fenetre
            if(player.rect.x <= 0){
                player.rect.x = 0; // l'empecher de sortir par la gauche
                touchingBorder = true;
            }
            if(player.rect.y <= 0){
                player.rect.y = 0; // en haut
                touchingBorder = true;
            }
            if(player.rect.x + player.rect.width >= screenWidth){ // on regarde si le coté droit du joueur depasse la bordure
                player.rect.x = screenWidth - player.rect.width; // a droite
                touchingBorder = true;
            }
            if(player.rect.y + player.rect.height >= screenHeight){
                player.rect.y = screenHeight - player.rect.height; // en bas
                touchingBorder = true;
            }
            

            if(touchingBorder){
                player.col = RED;
            } else {
                player.col = BLUE;
            }
        }
        BeginDrawing();
        DrawFPS(10, 10);
        ClearBackground(WHITE);
        if(player.isOn){
            DrawRectangleRec(player.rect, player.col); 
        }
        if(IsKeyDown(KEY_M)){
                DrawRectangle(0, 0, 800, 600, Fade(BLACK, 0.5f)); // Fond semi-transparent
        }

        if (currentScene == STATE_GAME) {
            DrawRectangleRec(player.rect, player.col); 
        } else if (currentScene == STATE_MENU) {
            // Fond semi-transparent pour l'effet de menu
            DrawRectangle(0, 0, screenWidth, screenHeight, Fade(BLACK, 0.5f));

            DrawText("MENU", 350, 100, 40, RAYWHITE);

            // Dessin des boutons avec la couleur qui change au survol
            DrawRectangleRec(btnPlay.rect, btnPlay.col);
            DrawRectangleRec(btnQuit.rect, btnQuit.col);

            DrawText("Reprendre", btnPlay.rect.x + 50, btnPlay.rect.y + 15, 20, RAYWHITE);
            DrawText("Quitter", btnQuit.rect.x + 70, btnQuit.rect.y + 15, 20, RAYWHITE);
        }
        else if (currentScene == STATE_QUIT_GAME) {
            ClearBackground(RED);
            Vector2 textSize = MeasureTextEx(GetFontDefault(), "Tu es sûr de vouloir quitter ? [Y/N]", 30, 1);
            DrawText("Tu es sûr de vouloir quitter ? [Y/N]",
                     (screenWidth - textSize.x) / 2, (screenHeight - textSize.y) / 2, 30, WHITE);
        }
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
