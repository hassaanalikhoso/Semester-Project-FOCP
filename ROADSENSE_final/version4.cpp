#include<raylib.h>
#include <fstream>
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
float timer = 0;
int displayspeed;
int DriverScore;
int HighScore = 0;

bool gameover = false;
bool LevelComplete = false;
bool showinst;
bool showinstructions = false;
bool showcontrols = true;
bool showWin = true;
bool showcongrats = false;
bool showdriverscore = false;
bool zebracrossed = false;
bool playwinmusic;
bool playtitlemusic;
bool Crash = false;
bool hasstopped = false;
bool didntstop = false;
bool showcredits = false;
bool restart = false;
bool showTitle = true;

Texture2D background;
Texture2D controls;
Texture2D instructions;
Texture2D GOscreen;
Texture2D LCscreen;
Texture2D TitleScreen;
Texture2D Congrats;
Texture2D Scorescreen;
Texture2D Credits;

Texture2D Redlight;
Texture2D Yellowlight;
Texture2D Greenlight;
Texture2D pole;

Texture2D Redlight2;
Texture2D Yellowlight2;
Texture2D Greenlight2;
Texture2D pole2;


Rectangle offRec1 = { 0,0,0,0 };
Rectangle offRec2 = { 0,0,0,0 };
Rectangle offRec3 = { 0,0,0,0 };

Rectangle offRec4 = { 0,0,0,0 };
Rectangle offRec5 = { 0,0,0,0 };
Rectangle offRec6 = { 0,0,0,0 };

Rectangle offRec7 = { 0,0,0,0 };
Rectangle offRec8 = { 0,0,0,0 };
Rectangle offRec9 = { 0,0,0,0 };
Rectangle Barricade = { 0,0,0,0 };
Rectangle Zebra1 = { 0,0,0,0 };
Rectangle Zebra2 = { 0,0,0,0 };

Rectangle Finish;

void Drive(Car& Car);
void LoadLevel(int& level, Car& Car, Music& gamemusic);
void Collisions(Car& Car, float carH, float radius, Sound& crash);
void Render(Car& Car, Texture2D& car, int displayspeed, Music& gamemusic, Music& winmusic, Music& titlemusic);
void Audio(Car& Car, Music& drive, Music& coast, bool& engine, bool& coasting);
void GOCheck(Car& Car, float carH, float radius);
void TrafficLights();

Color green = { 20,160,133,255 };

int main()
{
    InitWindow(1920, 1080, "First Raylib Game");
    InitAudioDevice();
    SetTargetFPS(60);

    std::ifstream in("highscore.txt");
    if (in) in >> HighScore;
    in.close();

    Car Car;
    Texture2D car = LoadTexture("Car.png");
    GOscreen = LoadTexture("GOscreen.png");
    LCscreen = LoadTexture("LCscreen.png");
    TitleScreen = LoadTexture("TitleScreen.png");

    Sound crash = LoadSound("CrashSound.mp3");
    Music drive = LoadMusicStream("DriveSound.mp3");
    Music coast = LoadMusicStream("CoastSound.mp3");
    Texture2D Redlight = LoadTexture("Redlight.png");
    Texture2D Yellowlight = LoadTexture("Yellowlight.png");
    Texture2D Greenlight = LoadTexture("Greenlight.png");

    Music titlemusic = LoadMusicStream("TitleMusic.mp3");
    Music gamemusic = LoadMusicStream("Shift.mp3");
    Music winmusic = LoadMusicStream("ShiftBoosted.mp3");
    bool engine = false;
    bool coasting = false;

    float carW = car.width / 20;
    float carH = car.height / 20;
    float radius = carW * 0.25f;

    while (WindowShouldClose() == false)
    {
        if (Car.speed < 1)
        {
            displayspeed = 0;
        }
        else
        {
            displayspeed = Car.speed * 25;
        }


        if (!gameover && !showinst)
        {
            LoadLevel(level, Car, gamemusic);
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
        if (!gameover && !showinst && !showWin)
        {
            TrafficLights();
        }
        Render(Car, car, displayspeed, gamemusic, winmusic, titlemusic);
        UpdateMusicStream(gamemusic);

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

        if (Car.speed < 5)
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

void LoadLevel(int& level, Car& Car, Music& gamemusic)
{
    if (LevelComplete)
    {
        PlayMusicStream(gamemusic);
        level++;

        showinst = true;

        if (level == 1)
        {
            DriverScore = 1000;

            controls = background = LoadTexture("Controls.png");
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
            Finish = { -30,880,10,150 };

            showcontrols = true;
            showinstructions = false;
            showinst = true;
        }

        if (level == 2)
        {
            showcontrols = false;
            showinstructions = true;
            showinst = true;

            background = LoadTexture("Level2.png");
            instructions = LoadTexture("Intro2.png");
            offRec1 = { -500,-205,875,450 };
            offRec2 = { 580,-205,875,450 };
            offRec3 = { 1665,-205,875,450 };

            offRec4 = { -500,415,875,450 };
            offRec5 = { 580,415,875,450 };
            offRec6 = { 1665,415,875,450 };

            offRec7 = { -500,1040,875,450 };
            offRec8 = { 580,1040,875,450 };
            offRec9 = { 1665,1040,875,450 };
            Finish = { 1920,880,10,150 };
        }
        if (level == 3)
        {
            showcontrols = false;
            showinstructions = true;
            showinst = true;
            background = LoadTexture("Level3.png");
            instructions = LoadTexture("Intro3.png");

            Zebra1 = { 1395, 250, 40,150 };
            Zebra2 = { 1310, 250, 80,150 };
            offRec1 = { -500,-205,1200,450 };
            offRec2 = { 580,-205,875,450 };
            offRec3 = { 1665,-205,875,450 };

            offRec4 = { -500,415,1200,1000 };
            offRec5 = { 580,415,875,1000 };
            offRec6 = { 1665,415,875,1000 };

            offRec7 = { -500,1040,875,450 };
            offRec8 = { 580,1040,875,450 };
            offRec9 = { 1665,1040,875,450 };
            Finish = { 1920,250,10,150 };
        }
        if (level == 4)
        {
            showcontrols = false;
            showinstructions = true;
            showinst = true;

            background = LoadTexture("Level4.png");
            instructions = LoadTexture("Intro4.png");

            Redlight = LoadTexture("Redlight.png");
            Yellowlight = LoadTexture("Yellowlight.png");
            Greenlight = LoadTexture("Greenlight.png");
            pole = LoadTexture("Pole.png");

            Redlight2 = LoadTexture("Redlight.png");
            Yellowlight2 = LoadTexture("Yellowlight.png");
            Greenlight2 = LoadTexture("Greenlight.png");
            pole2 = LoadTexture("Pole.png");

            Barricade = { 395, 610, 160,20 };
            Zebra1 = { 1395, 250, 40,150 };
            Zebra2 = { 600, 880, 40,150 };

            offRec1 = { -500,-205,875,450 };
            offRec2 = { 580,-205,875,450 };
            offRec3 = { 1665,-205,875,450 };

            offRec4 = { -500,415,875,450 };
            offRec5 = { 580,415,875,450 };
            offRec6 = { 1665,415,875,450 };

            offRec7 = { -500,1040,875,450 };
            offRec8 = { 580,1040,875,450 };
            offRec9 = { 1665,1040,875,450 };
            Finish = { -30,880,10,150 };
            Congrats = LoadTexture("Congrats.png");
            Scorescreen = LoadTexture("Scorescreen.png");
            Credits = LoadTexture("Credits.png");

        }
        if (level == 5)
        {
            showcongrats = true;
            showdriverscore = false;
            showcredits = false;
            showWin = false;
            showinst = false;
        }

        if (level != 5)
        {
            Car.carX = 0;
            Car.carY = 290;
            Car.angle = 0;
            Car.speed = 0.5;
        }
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
        CheckCollisionCircleRec(frontCircle, radius, offRec9) ||
        CheckCollisionCircleRec(frontCircle, radius, Barricade);

    bool rearcoll =
        CheckCollisionCircleRec(rearCircle, radius, offRec1) ||
        CheckCollisionCircleRec(rearCircle, radius, offRec2) ||
        CheckCollisionCircleRec(rearCircle, radius, offRec3) ||
        CheckCollisionCircleRec(rearCircle, radius, offRec4) ||
        CheckCollisionCircleRec(rearCircle, radius, offRec5) ||
        CheckCollisionCircleRec(rearCircle, radius, offRec6) ||
        CheckCollisionCircleRec(rearCircle, radius, offRec7) ||
        CheckCollisionCircleRec(rearCircle, radius, offRec8) ||
        CheckCollisionCircleRec(rearCircle, radius, offRec9) ||
        CheckCollisionCircleRec(rearCircle, radius, Barricade);

    if (level < 5)
    {
        showWin = CheckCollisionCircleRec(frontCircle, radius, Finish) || CheckCollisionCircleRec(rearCircle, radius, Finish);
    }
    else
    {
        showWin = false;
    }

    bool zebrafront = CheckCollisionCircleRec(frontCircle, radius, Zebra1) || CheckCollisionCircleRec(frontCircle, radius, Zebra2);
    bool zebrarear = CheckCollisionCircleRec(rearCircle, radius, Zebra1) || CheckCollisionCircleRec(rearCircle, radius, Zebra2);

    zebracrossed = zebrafront || zebrarear;

    if (level == 3)
    {
        hasstopped = CheckCollisionCircleRec(frontCircle, radius, Zebra2) || CheckCollisionCircleRec(rearCircle, radius, Zebra2);
        didntstop = CheckCollisionCircleRec(frontCircle, radius, Zebra1) || CheckCollisionCircleRec(rearCircle, radius, Zebra1);
    }

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
        DriverScore -= 10;
    }
}
void Render(Car& Car, Texture2D& car, int displayspeed, Music& gamemusic, Music& winmusic, Music& titlemusic)
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

    // BOUNDARY SHAPES

  /* DrawRectangleRec(offRec1, BLUE);
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

     /* DrawRectangleRec(Finish, RED);
      DrawRectangleRec(Barricade, RED);*/

      /* DrawRectangleRec(Zebra1, GREEN);
       DrawRectangleRec(Zebra2, RED);*/

    DrawTexturePro(car, src, dst, origin, Car.angle, WHITE);

    // SPEED DISPLAY

    DrawText(TextFormat("SPEED: %i", displayspeed), 1750, 40, 30, WHITE);
    /* DrawText(TextFormat("TIME: %d", (int)timer), 1750, 100, 30, WHITE);*/


     //TRAFFIC LIGHT RENDERS

    if (level == 4)
    {
        DrawTextureEx(pole, { 1390, 200 }, 0, 0.1f, WHITE);
        DrawTextureEx(pole2, { 645, 1100 }, 180, 0.1f, WHITE);
        if (timer < 12)
        {
            DrawTextureEx(Redlight, { 1420, 240 }, 0, 0.1f, WHITE);
            DrawTextureEx(Redlight2, { 620, 1045 }, 180, 0.1f, WHITE);

        }
        else if (timer < 15)
        {
            DrawTextureEx(Yellowlight, { 1420, 240 }, 0, 0.1f, WHITE);
            DrawTextureEx(Yellowlight2, { 620, 1045 }, 180, 0.1f, WHITE);
        }
        else if (timer < 20)
        {
            DrawTextureEx(Greenlight, { 1420, 240 }, 0, 0.1f, WHITE);
            DrawTextureEx(Greenlight2, { 620, 1045 }, 180, 0.1f, WHITE);
        }
    }

    //LEVEL COMPLETE SEQUENCE

    if (showWin)
    {
        if (level == 0 && !restart)
        {
            if (!playtitlemusic)
            {
                PlayMusicStream(titlemusic);
            }
            playtitlemusic = true;
            UpdateMusicStream(titlemusic);

        }
        else
        {
            PauseMusicStream(gamemusic);
            if (!playwinmusic)
            {
                PlayMusicStream(winmusic);
            }
            playwinmusic = true;
            UpdateMusicStream(winmusic);
            DrawTextureEx(LCscreen, { 680, 370 }, 0, .8f, WHITE);
        }

        if (IsKeyPressed(KEY_ENTER))
        {
            playwinmusic = false;
            if (level != 5)
            {
                StopMusicStream(winmusic);
            }
            LevelComplete = true;
            showWin = false;
        }
    }

    // INSTRUCTIONS DISPLAY

    if (showinst)
    {
        if (showcontrols)
        {
            DrawTextureEx(controls, { 680, 370 }, 0, 0.8f, WHITE);

            if (IsKeyPressed(KEY_ENTER))
            {
                showcontrols = false;
                showinstructions = true;
            }
        }
        else if (showinstructions)
        {
            DrawTextureEx(instructions, { 680, 370 }, 0, 0.8f, WHITE);

            if (IsKeyPressed(KEY_ENTER))
            {
                showinstructions = false;
                showinst = false;
            }
        }
    }

    // GAMEOVER SEQUENCE

    if (gameover)
    {
        DrawTextureEx(GOscreen, { 680, 370 }, 0, .8f, WHITE);

        if (IsKeyPressed(KEY_ENTER))
        {
            gameover = false;
            Crash = false;
            showinst = true;
            showcontrols = false;
            showinstructions = true;
            showWin = false;

            Car.carX = 0;
            Car.carY = 290;
            Car.angle = 0;
            Car.speed = 0.5;
            showinst = true;
        }
    }

    // GAME ENDING SEQUENCE

    if (level == 5)
    {
        if (!playwinmusic)
        {
            PlayMusicStream(winmusic);
            playwinmusic = true;
        }
        UpdateMusicStream(winmusic);

        if (showcongrats)
        {
           
            DrawTextureEx(Congrats, { 680, 370 }, 0, 0.8f, WHITE);

            if (DriverScore > HighScore)
            {
                HighScore = DriverScore;
                std::ofstream out("highscore.txt");
                out << HighScore;
                out.close();
            }

            if (IsKeyPressed(KEY_ENTER))
            {
                showcongrats = false;
                showdriverscore = true;
            }
        }
        else if (showdriverscore)
        {
            DrawTextureEx(Scorescreen, { 680, 370 }, 0, 0.8f, WHITE);

            DrawText(TextFormat(" %d", DriverScore), 880, 450, 80, BLACK);
            DrawText(TextFormat(" %d", HighScore), 880, 600, 80, BLACK);

            if (IsKeyPressed(KEY_ENTER))
            {
                showdriverscore = false;
                showcredits = true;


            }
        }
        else if (showcredits)
        {
            DrawTextureEx(Credits, { 680, 370 }, 0, 0.8f, WHITE);
            if (IsKeyPressed(KEY_ENTER))
            {
           
                showcredits = false;
                showcongrats = false;
                showdriverscore = false;
                showinst = false;
                showinstructions = false;
                showcontrols = true;
                showWin = false;
                LevelComplete = false;
                gameover = false;
                Crash = false;
                hasstopped = false;
                didntstop = false;
                zebracrossed = false;
                playwinmusic = false;
                playtitlemusic = false;
                restart = true;

                
                level = 0;
                timer = 0;
                DriverScore = 1000;

               
                Car.carX = 0;
                Car.carY = 290;
                Car.angle = 0;
                Car.speed = 0.5;
                Car.revspeed = Car.speed / 4;

             
                StopMusicStream(winmusic);
                StopMusicStream(gamemusic);
                StopMusicStream(titlemusic);

                offRec1 = { 0,0,0,0 };
                offRec2 = { 0,0,0,0 };
                offRec3 = { 0,0,0,0 };
                offRec4 = { 0,0,0,0 };
                offRec5 = { 0,0,0,0 };
                offRec6 = { 0,0,0,0 };
                offRec7 = { 0,0,0,0 };
                offRec8 = { 0,0,0,0 };
                offRec9 = { 0,0,0,0 };
                Barricade = { 0,0,0,0 };
                Zebra1 = { 0,0,0,0 };
                Zebra2 = { 0,0,0,0 };
            }
        }
    }

    // TITLE SCREEN

    if (level == 0)
    {
        DrawTextureEx(TitleScreen, { 0.0f, 0.0f }, 0, 1.0f, WHITE);
        if (IsKeyPressed(KEY_ENTER))
        {
            LevelComplete = true;
            restart = false; 
            StopMusicStream(titlemusic); 
            playtitlemusic = false;
        }
    }

    EndDrawing();
}
void Audio(Car& Car, Music& drive, Music& coast, bool& engine, bool& coasting)
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
        if (displayspeed > 99)
        {
            gameover = true;
        }
        break;
    case 3:
        if (hasstopped && Car.speed < 0.55)
        {
            Zebra1 = { 0,0,0,0 };
            hasstopped = false;
            zebracrossed = false;
        }
        if (didntstop)
        {
            gameover = true;
            didntstop = false;
        }
        break;
    case 4:
        if (timer < 15 && zebracrossed)
        {
            gameover = true;
            zebracrossed = false;
        }
    default:
        break;
    }
    if (gameover)
    {
        DriverScore -= 100;
    }
}

void TrafficLights()
{
    timer += GetFrameTime();

    if (timer > 20)
    {
        DriverScore -= timer;
        timer = 0;
    }
}