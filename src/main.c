
#include <raylib.h>
#include <math.h>
#include "files.h"
#include "level.h"
#include "draw.h"
#include "state.h"

int main(int argc, char const *argv[]){

    // Initialization
    bool pause = false;
    const int screen_width = 800;
    const int screen_height = 600;
    int playerScore = 0; // The Counter "playerScore" starts
    int highscore = current_highscore();
    InitAudioDevice(); // Initialize audio device
    int vez_repetida = 0;

    Music music = LoadMusicStream("resources/music.ogg");
    Sound death = LoadSound("resources/death.ogg");
    music.looping = true;
    PlayMusicStream(music);

    InitWindow(screen_width,screen_height,"Presente - the game");
    SetTargetFPS(60);

    // Initialize level and fill randomly
    level *lvl = level_new(50,40);
    level_fill_random(lvl,6);

    // Initialize state (and add enemies)
    state *sta = state_new();
    state_populate_random(lvl,sta,40);

    // Main loop
    while(!WindowShouldClose()){
        UpdateMusicStream(music);
        if (IsKeyPressed(KEY_P))
        {
            pause = !pause;

            if (pause) PauseMusicStream(music);
            else ResumeMusicStream(music);
        }

        // Update input depending if keys are pressed or not
        sta->button_state[0] = IsKeyDown(KEY_D);
        sta->button_state[1] = IsKeyDown(KEY_W);
        sta->button_state[2] = IsKeyDown(KEY_A);
        sta->button_state[3] = IsKeyDown(KEY_S);
        sta->button_state[4] = IsMouseButtonDown(MOUSE_LEFT_BUTTON);

        // Compute the angle the player is looking at from the mouse's position relative to the screen's center
        float mouse_y = GetMouseY()-GetScreenHeight()/2;
        float mouse_x = GetMouseX()-GetScreenWidth()/2;
        sta->aim_angle = atan2(-mouse_y,mouse_x);

        // Update the state
        state_update(lvl,sta,&playerScore);

        // Drawing
        BeginDrawing();

            ClearBackground(RAYWHITE);

            draw_state(lvl, sta);

            DrawText("Presente profe!",190,200,20,LIGHTGRAY);

            DrawText(FormatText("Score: %08i", playerScore), 280, 80, 30, BLACK);

            DrawText(FormatText("Highscore: %08i", highscore), 240, 40, 30, RED);

        EndDrawing();

        if(sta->pla.ent.dead==1){
          if (vez_repetida<1){
            highscore_update(&playerScore);
            StopMusicStream(music);
            PlaySound(death);
            vez_repetida++;
          }
          DrawText("Perdiste:C",240,250,20,BLUE);

        }

    }

    // Closer window
    highscore_update(&playerScore);

    UnloadSound(death);

    UnloadMusicStream(music);

    CloseAudioDevice();

    CloseWindow();

    // Free memory
    state_free(sta);
    level_free(lvl);

    return 0;
}
