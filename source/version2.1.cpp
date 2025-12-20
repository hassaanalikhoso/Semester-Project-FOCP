#include<raylib.h>
#include<cmath>

struct Car {
    
    float carX = 0;
    float carY = 290;
    float angle = 0;
    float speed = 0.5;
    float revspeed = speed / 4;
    float scale = 0.5f;
};
int score = 0;
int level = 0;
bool gameover = false;


Texture2D background;
Texture2D instructions;
Texture2D GOscreen;
Texture2D LCscreen;
bool LevelComplete = true;
bool showinst;
bool showWin;
bool Crash = false;

Rectangle offRec1 = { 0,0,0,0 };
Rectangle offRec2 = { 0,0,0,0 };
Rectangle offRec3 = { 0,0,0,0 };

Rectangle offRec4 = { 0,0,0,0 };
Rectangle offRec5 = { 0,0,0,0 };
Rectangle offRec6 = { 0,0,0,0 };

Rectangle offRec7 = { 0,0,0,0 };
Rectangle offRec8 = { 0,0,0,0 };
Rectangle offRec9 = { 0,0,0,0 };

Rectangle Finish;

void Drive(Car& Car);
void LoadLevel(int& level, Car& Car);
void Collisions( Car& Car, float carH, float radius, Sound& crash);
void Render(Car& Car, Texture2D& car, int displayspeed);
void Audio(Car& Car, Music& drive, Music& coast, bool& engine, bool& coasting);
void GOCheck(Car& Car, float carH, float radius);

Color green = { 20,160,133,255 };

int main()
{
    InitWindow(1920, 1080, "First Raylib Game");
    InitAudioDevice();
    SetTargetFPS(60);
    Car Car;
    Texture2D car = LoadTexture("Car.png");
    GOscreen = LoadTexture("GOscreen.png");
    LCscreen = LoadTexture("LCscreen.png");
    Sound crash = LoadSound("CrashSound.mp3");
    Music drive = LoadMusicStream("DriveSound.mp3");
    Music coast = LoadMusicStream("CoastSound.mp3");
    bool engine = false;
    bool coasting = false;

    float carW = car.width / 20;
    float carH = car.height / 20;
    float radius = carW * 0.25f;

  
    int displayspeed;

    while (WindowShouldClose() == false)
    {
       

        if (Car.speed == 0.5)
        {
            displayspeed = 0;
        }
        else
        {
            displayspeed = Car.speed * 25;
        }

        if (!gameover && !showinst)
        {
            LoadLevel(level, Car);
        }
        if (!gameover && !showinst && !showWin)
        {
            Collisions(Car, carH, radius, crash);
        }
        if (!gameover && !showinst && !showWin)
        {
            Audio(Car, drive, coast, engine, coasting);
        }
        if (!gameover && !showinst)
        {
            GOCheck(Car, carH, radius);
        }
        Render(Car, car, displayspeed);
    }

    UnloadTexture(car);
    UnloadTexture(background);
    UnloadTexture(instructions);
    UnloadTexture(GOscreen);
    UnloadTexture(LCscreen);
    CloseAudioDevice();
    CloseWindow();
    return 0;
}

void Drive(Car& Car)
{
    if (showinst)
    {
        return;
    }


    if (Car.speed > 0.6)
    {
        if (IsKeyDown(KEY_RIGHT)) Car.angle += 0.6;
        if (IsKeyDown(KEY_LEFT))  Car.angle -= 0.6;
    }
    if (Car.revspeed > 0.15)
    {
        if (IsKeyDown(KEY_RIGHT)) Car.angle -= 0.3;
        if (IsKeyDown(KEY_LEFT))  Car.angle += 0.3;
    }
    // coast
    Car.carX += Car.speed * cosf(Car.angle * DEG2RAD);
    Car.carY += Car.speed * sinf(Car.angle * DEG2RAD);

    Car.carX -= 0.5 * cosf(Car.angle * DEG2RAD);
    Car.carY -= 0.5 * sinf(Car.angle * DEG2RAD);

    Car.carX -= Car.revspeed * cosf(Car.angle * DEG2RAD);
    Car.carY -= Car.revspeed * sinf(Car.angle * DEG2RAD);

    Car.carX += 0.125 * cosf(Car.angle * DEG2RAD);
    Car.carY += 0.125 * sinf(Car.angle * DEG2RAD);

    // friction
    if (Car.speed > 0.5 && IsKeyUp(KEY_UP))
    {
        Car.speed = Car.speed * 0.985;
    }
    if (Car.revspeed > 0.125 && IsKeyUp(KEY_DOWN))
    {
        Car.revspeed = Car.revspeed * 0.985;
    }
    if (IsKeyDown(KEY_UP))
    {
        Car.carX += Car.speed * cosf(Car.angle * DEG2RAD);
        Car.carY += Car.speed * sinf(Car.angle * DEG2RAD);

        if (Car.speed < 3)
            Car.speed = Car.speed * 1.01;


    }
    if (IsKeyDown(KEY_DOWN))
    {
        Car.carX -= Car.revspeed * cosf(Car.angle * DEG2RAD);
        Car.carY -= Car.revspeed * sinf(Car.angle * DEG2RAD);

        if (Car.revspeed < 1.0)
            Car.revspeed = Car.revspeed * 1.01;

    }

}

void LoadLevel(int& level, Car& Car)
{
    if (LevelComplete)
    {
        level++;
        
        showinst = true;
        
        
        // change background depending on level
        if (level == 1)
        {

            background = LoadTexture("Level1.png");
            instructions = LoadTexture("Intro1.png");

            offRec1 = { -500,-205,3000,450 };
            offRec2 = { 0,0,0,0 };
            offRec3 = { 0,0,0,0 };

            offRec4 = { -500,415,1955,450 };
            offRec5 = { 0,0,0,0 };
            offRec6 = { 1665,70,875,800 };

            offRec7 = { -500,1040,875,450 };
            offRec8 = { 580,1040,875,450 };
            offRec9 = { 1665,1040,875,450 };
            Finish = { 0,880,10,150 };
        }

        if (level == 2)
        {
            background = LoadTexture("Map.png");
            offRec1 = { -500,-205,875,450 };
            offRec2 = { 580,-205,875,450 };
            offRec3 = { 1665,-205,875,450 };

            offRec4 = { -500,415,875,450 };
            offRec5 = { 580,415,875,450 };
            offRec6 = { 1665,415,875,450 };

            offRec7 = { -500,1040,875,450 };
            offRec8 = { 580,1040,875,450 };
            offRec9 = { 1665,1040,875,450 };
            Car.angle = 0;
        }

        Car.carX = 0;
        Car.carY = 290;
        Car.angle = 0;
        Car.speed = 0.5;
        LevelComplete = false;
    }
}

void Collisions(Car& Car, float carH, float radius, Sound& crash)
{
    Vector2 forward;
    forward.x = cosf(Car.angle * DEG2RAD);
    forward.y = sinf(Car.angle * DEG2RAD);

    Vector2 frontCircle = {
        Car.carX + forward.x * (carH * 0.55f),
        Car.carY + forward.y * (carH * 0.55f)
    };

    Vector2 rearCircle = {
        Car.carX - forward.x * (carH * 0.55f),
        Car.carY - forward.y * (carH * 0.55f)
    };

    bool frontcoll = CheckCollisionCircleRec(frontCircle, radius, offRec1) ||
        CheckCollisionCircleRec(frontCircle, radius, offRec2) ||
        CheckCollisionCircleRec(frontCircle, radius, offRec3) ||
        CheckCollisionCircleRec(frontCircle, radius, offRec4) ||
        CheckCollisionCircleRec(frontCircle, radius, offRec5) ||
        CheckCollisionCircleRec(frontCircle, radius, offRec6) ||
        CheckCollisionCircleRec(frontCircle, radius, offRec7) ||
        CheckCollisionCircleRec(frontCircle, radius, offRec8) ||
        CheckCollisionCircleRec(frontCircle, radius, offRec9);

    bool rearcoll =
        CheckCollisionCircleRec(rearCircle, radius, offRec1) ||
        CheckCollisionCircleRec(rearCircle, radius, offRec2) ||
        CheckCollisionCircleRec(rearCircle, radius, offRec3) ||
        CheckCollisionCircleRec(rearCircle, radius, offRec4) ||
        CheckCollisionCircleRec(rearCircle, radius, offRec5) ||
        CheckCollisionCircleRec(rearCircle, radius, offRec6) ||
        CheckCollisionCircleRec(rearCircle, radius, offRec7) ||
        CheckCollisionCircleRec(rearCircle, radius, offRec8) ||
        CheckCollisionCircleRec(rearCircle, radius, offRec9);



    showWin = CheckCollisionCircleRec(frontCircle, radius, Finish) || CheckCollisionCircleRec(rearCircle, radius, Finish);

    if (!frontcoll && !rearcoll)
    {
        Drive(Car);
    }
    else if (frontcoll)
    {
        Car.carX = Car.carX - forward.x * (carH * 0.02f);
        Car.carY = Car.carY - forward.y * (carH * 0.02f);

        Car.speed = 0.5;
        Car.revspeed = 0.125;
        PlaySound(crash);

    }
    else if (rearcoll)
    {
        Car.carX = Car.carX + forward.x * (carH * 0.02f);
        Car.carY = Car.carY + forward.y * (carH * 0.02f);

        Car.speed = 0.5;
        Car.revspeed = 0.125;
        PlaySound(crash);

    }
    if (frontcoll || rearcoll)
    {
        Crash = true;
    }
}
void Render(Car& Car, Texture2D& car, int displayspeed)
{
    BeginDrawing();

    ClearBackground(green);
    DrawTextureEx(background, { 0.0f, 0.0f }, 0, 1.3f, WHITE);



    Vector2 carPos = { Car.carX, Car.carY };
    Rectangle src = { 0,0,(float)car.width,(float)car.height };
    Rectangle dst = { Car.carX, Car.carY,car.width / 20,car.height / 20 };
    Vector2 origin = { car.width / 20, car.height / 20 };
    origin.x = (car.width / 20) * Car.scale;
    origin.y = (car.height / 20) * Car.scale;

    // INVISIBLE SHAPES

   /*DrawRectangleRec(offRec1, BLUE);
    DrawRectangleRec(offRec2, BLUE);
    DrawRectangleRec(offRec3, BLUE);

    DrawRectangleRec(offRec4, BLUE);
    DrawRectangleRec(offRec5, BLUE);
    DrawRectangleRec(offRec6, BLUE);

    DrawRectangleRec(offRec7, BLUE);
    DrawRectangleRec(offRec8, BLUE);
    DrawRectangleRec(offRec9, BLUE);*/

    /*DrawCircleLines(frontCircle.x, frontCircle.y, radius, RED);
     DrawCircleLines(rearCircle.x, rearCircle.y, radius, RED);*/

     /*DrawRectangleRec(Finish, RED);*/

    DrawTexturePro(car, src, dst, origin, Car.angle, WHITE);
    DrawText(TextFormat("SCORE: %i", score), 1750, 40, 30, WHITE);
    DrawText(TextFormat("SPEED: %i", displayspeed), 1750, 70, 30, WHITE);

    if (showWin)
    {
        DrawTextureEx(LCscreen, { 680, 370 }, 0, .8f, WHITE);

        if (IsKeyPressed(KEY_ENTER))
        {
            LevelComplete = true;
            showWin = false;
        }
    }
    if (showinst)
    {
        DrawTextureEx(instructions, { 680, 370 }, 0, .8f, WHITE);

        if (IsKeyPressed(KEY_ENTER))
        {
            showinst = false;
        }
    }
    if (gameover)
    {
        DrawTextureEx(GOscreen, { 680, 370 }, 0, .8f, WHITE);

        if (IsKeyPressed(KEY_ENTER))
        {
            gameover = false;
            Crash = false;

            Car.carX = 0;
            Car.carY = 290;
            Car.angle = 0;
        }
    }
    
    EndDrawing();
}
void Audio(Car& Car,Music& drive, Music& coast, bool& engine, bool& coasting)
{
    UpdateMusicStream(drive);
    UpdateMusicStream(coast);

    if (IsKeyDown(KEY_UP))
    {
        if (!engine)
        {
            PlayMusicStream(drive);
            engine = true;
        }
    }
    else
    {
        if (engine)
        {
            StopMusicStream(drive);
            engine = false;
        }
    }

    if (Car.speed > 0.5 && !IsKeyDown(KEY_UP) && !IsKeyDown(KEY_DOWN))
    {
        if (!coasting)
        {
            PlayMusicStream(coast);
            coasting = true;
        }
    }
    else
    {
        if (coasting)
        {
            StopMusicStream(coast);
            coasting = false;
        }
    }

}
void GOCheck(Car& Car, float carH, float radius)
{

    switch (level)
    {
        case 1:
            if (Crash)
            {
                gameover = true;
               
            }
            break;
        case 2:
            break;
        default:
            break;
    }


}