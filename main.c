#include "raylib.h"

const int screenWidth = 1920; 
const int screenHeight = 1080;

typedef struct {
    Rectangle rect;
    Color col;
    bool isOn;
} Player;

int main(){
    // SetConfigFlags(FLAG_WINDOW_RESIZABLE); si on veut pouvoire resize la fenetre 
    InitWindow(screenWidth, screenHeight, "test");
    SetExitKey(KEY_NULL);
    SetTargetFPS(144);

    bool ExitWinReq = false;
    bool ExitWin = false;
    bool touchingBorder = false;


    Player player = { 
        .rect = { 350.0f, 250.0f, 100.0f, 100.0f },
        .col = BLUE,
        .isOn = true
    };
    
    int speed = 5;

    while(!ExitWin){
        touchingBorder = false;
        if(WindowShouldClose() || IsKeyDown(KEY_ESCAPE)) ExitWinReq = true;
        if(ExitWinReq){
            if(IsKeyDown(KEY_Y)) ExitWin = true;
            else if (IsKeyDown(KEY_N)){
                    ExitWinReq = false;
                    player.isOn = true ;
                }
        }
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

        BeginDrawing();
        DrawFPS(10, 10);
        ClearBackground(WHITE);
        if(player.isOn){
            DrawRectangleRec(player.rect, player.col); 
        }

        if(ExitWinReq){
            player.isOn = false;
            ClearBackground(RED);
            Vector2 closeTextSize = MeasureTextEx(GetFontDefault(), "Tu es sur de vouloir quitter ? [Y/N]", 30, 1);
            DrawText("Tu es sur de vouloir quitter ? [Y/N]", (screenWidth-closeTextSize.x)/2, (screenHeight-closeTextSize.y)/2, 30, WHITE);           
        }
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
