#include "api.h"
#include "raylib.h"
#include "map.h"
#include "palette.h"
#include <stdio.h>

#define FLOPPY_RADIUS 24
#define TUBES_WIDTH 80

#define max(a, b) ((a) > (b) ? (a) : (b))
#define min(a, b) ((a) < (b) ? (a) : (b))

float clamp(float value, float min, float max)
{
    return value < min ? min : value > max ? max : value;
}

void open(void)
{
    InitWindow(800, 600, "florpheus");
    SetTargetFPS(60);
}

void close(void)
{
    CloseWindow();
}

void init(game_state *gs)
{
    Vector2 screen = {800, 600};

    Settings settings = {
        .api_version = 0,
        .max_api_version = 0,
        .gameOver = false,
        .pause = false,
    };

   Floppy floppy = {
        .radius = FLOPPY_RADIUS,
        .velocity = (Vector2){ 300.0f, 0.0f },
        .position = (Vector2){ 0, screen.y / 2.0f },
        .color = (Color){0, 0, 0, 255},
    };

    printf("initialized floppy to pos %f %f\n", floppy.position.x, floppy.position.y);

    Camera2D camera = {0};
    camera.target = (Vector2){ floppy.position.x - 200.f, 0.0 };
    camera.offset = (Vector2){ 200.0, 0.0 };
    camera.rotation = 0.0f;
    camera.zoom = 1.0f;

    Map map;

    // only initialize the map once
    if (gs->map.nTubes == 0)
        init_map(&map);
    else
        map = gs->map;

    *gs = (game_state){
        .screen = screen,
        .settings = settings,
        .floppy = floppy,
        .camera = camera,
        .superfx = false,
        .score = 0,
        .map = map,
        .hiScore = 0,
        .delta = 0.0,
        .elapsed = gs->elapsed,
    };
}

void UpdateGame(game_state *gs)
{
    gs->delta = GetFrameTime();
    gs->elapsed = GetTime();

    Settings *settings = &gs->settings;
    if (settings->gameOver)
    {
        if (IsKeyPressed(KEY_ENTER))
        {
            printf("RESTARTING\n");
            init(gs);
            return;
        }
        return;
    }

    if (IsKeyPressed('P')) settings->pause = !settings->pause;
    if (settings->pause)
        return;

    float gravity = 7.0;
    gs->floppy.velocity.y += gravity;

    gs->floppy.position = (Vector2){
        gs->floppy.position.x + gs->floppy.velocity.x * gs->delta,
        gs->floppy.position.y + gs->floppy.velocity.y * gs->delta
    };

    if (IsKeyPressed(KEY_SPACE)) {
        // TODO: CONFIGURE NICE JUMP KINEMATICS
        gs->floppy.velocity.y = max(gs->floppy.velocity.y - 400., -300);
    }

    gs->camera.target.x = gs->floppy.position.x;

    // Check Collisions
    for (int i = 0; i < gs->map.nTubes; i++)
    {
        Tubes *tube = &gs->map.tubes[i];
        bool collided = CheckCollisionCircleRec(
            gs->floppy.position, gs->floppy.radius, tube->rec);
        if (collided) {
            settings->gameOver = true;
            settings->pause = false;
            break;
        }
    }
}

void DrawGame(game_state *gs)
{
    ClearBackground(get_color(COLOR_BACKGROUND));

    if (gs->settings.gameOver)
    {
        DrawText("PRESS [ENTER] TO PLAY AGAIN",
            gs->screen.x / 2.0 - (float)MeasureText("PRESS [ENTER] TO PLAY AGAIN", 40)/2,
            gs->screen.y / 2.0 - 40, 40, RED);
        return;
    }

    if (gs->settings.pause) {
        DrawText("GAME PAUSED",
                gs->screen.x / 2.0 - (float)MeasureText("GAME PAUSED", 40)/2,
                gs->screen.y / 2.0 - 40, 40, RED);
        return;
    }

    BeginMode2D(gs->camera);

    draw_map(&gs->map);
    DrawCircle(gs->floppy.position.x+4, gs->floppy.position.y+4, gs->floppy.radius*1.3, get_color(COLOR_TUBE_SHADOW));
    DrawCircle(gs->floppy.position.x, gs->floppy.position.y, gs->floppy.radius*1.3, get_color(COLOR_AVATAR_BORDER2));
    DrawCircle(gs->floppy.position.x, gs->floppy.position.y, gs->floppy.radius*1.2, get_color(COLOR_AVATAR_BORDER1));
    DrawCircle(gs->floppy.position.x, gs->floppy.position.y, gs->floppy.radius, get_color(COLOR_AVATAR));

    EndMode2D();
}

bool step(game_state *state) {
    BeginDrawing();
    if (IsKeyPressed(KEY_ESCAPE))
        return false;

    UpdateGame(state);
    DrawGame(state);

    EndDrawing();
    return true;
}

int requested_api_version_id(const game_state *state)
{
    return state->settings.api_version;
}

void set_api_version_id(game_state *state, int version_id) {
    state->settings.api_version = version_id;
    state->settings.max_api_version = max(version_id, state->settings.max_api_version);
}

const game_api shared_obj_api = {
    .open = open,
    .close = close,
    .init = init,
    .step = step,
    .requested_api_version_id = requested_api_version_id,
    .set_api_version_id_callback = set_api_version_id,
    .game_state_size = sizeof(game_state)
};
