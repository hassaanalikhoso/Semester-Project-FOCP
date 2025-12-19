//#include<raylib.h>
//#include<cmath>
//
//struct Car {
//    ;
//    float carX = 0;
//    float carY = 290;
//    float angle = 0;
//    float speed = 0.5;
//    float revspeed = speed / 4;
//    float scale = 0.5f;
//};
//
//
//void Drive(Car& Car);
//void CollCheck();
//
//Color green = { 20,160,133,255 };
//
//int main()
//{
//    Car Car;
//
//    // car rectangle
//    InitWindow(1920, 1080, "First Raylib Game");
//    InitAudioDevice();
//    SetTargetFPS(60);
//    Texture2D background = LoadTexture("Map.png");
//    Texture2D car = LoadTexture("Car.png");
//    Sound crash = LoadSound("CrashSound.mp3");
//    Music drive = LoadMusicStream("DriveSound.mp3");
//    bool engine = false;
//
//    float carW = car.width / 20;
//    float carH = car.height / 20;
//    float radius = carW * 0.25f;
//
//
//
//
//
//    Rectangle offRec1 = { -500,-205,875,450 };
//    Rectangle offRec2 = { 580,-205,875,450 };
//    Rectangle offRec3 = { 1665,-205,875,450 };
//
//    Rectangle offRec4 = { -500,415,875,450 };
//    Rectangle offRec5 = { 580,415,875,450 };
//    Rectangle offRec6 = { 1665,415,875,450 };
//
//    Rectangle offRec7 = { -500,1040,875,450 };
//    Rectangle offRec8 = { 580,1040,875,450 };
//    Rectangle offRec9 = { 1665,1040,875,450 };
//
//    // Game Loop
//    while (WindowShouldClose() == false)
//    {
//        // Event Handling
//        UpdateMusicStream(drive);
//
//        if (IsKeyDown(KEY_UP))
//        {
//            if (!engine)
//            {
//                PlayMusicStream(drive);
//                engine = true;
//            }
//        }
//        else
//        {
//            if (engine)
//            {
//                StopMusicStream(drive);
//                engine = false;
//            }
//        }
//         
//        Vector2 forward;
//        forward.x = cosf(Car.angle * DEG2RAD);
//        forward.y = sinf(Car.angle * DEG2RAD);
//
//        Vector2 frontCircle = {
//            Car.carX + forward.x * (carH * 0.55f),
//            Car.carY + forward.y * (carH * 0.55f)
//        };
//
//        Vector2 rearCircle = {
//            Car.carX - forward.x * (carH * 0.55f),
//            Car.carY - forward.y * (carH * 0.55f)
//        };
//
//        bool frontcoll = CheckCollisionCircleRec(frontCircle, radius, offRec1) ||
//            CheckCollisionCircleRec(frontCircle, radius, offRec2) ||
//            CheckCollisionCircleRec(frontCircle, radius, offRec3) ||
//            CheckCollisionCircleRec(frontCircle, radius, offRec4) ||
//            CheckCollisionCircleRec(frontCircle, radius, offRec5) ||
//            CheckCollisionCircleRec(frontCircle, radius, offRec6) ||
//            CheckCollisionCircleRec(frontCircle, radius, offRec7) ||
//            CheckCollisionCircleRec(frontCircle, radius, offRec8) ||
//            CheckCollisionCircleRec(frontCircle, radius, offRec9);
//
//        bool rearcoll =
//            CheckCollisionCircleRec(rearCircle, radius, offRec1) ||
//            CheckCollisionCircleRec(rearCircle, radius, offRec2) ||
//            CheckCollisionCircleRec(rearCircle, radius, offRec3) ||
//            CheckCollisionCircleRec(rearCircle, radius, offRec4) ||
//            CheckCollisionCircleRec(rearCircle, radius, offRec5) ||
//            CheckCollisionCircleRec(rearCircle, radius, offRec6) ||
//            CheckCollisionCircleRec(rearCircle, radius, offRec7) ||
//            CheckCollisionCircleRec(rearCircle, radius, offRec8) ||
//            CheckCollisionCircleRec(rearCircle, radius, offRec9);
//
//        if (!frontcoll && !rearcoll)
//        {
//            Drive(Car);
//        }
//        else if (frontcoll)
//        {
//            Car.carX = Car.carX - forward.x * (carH * 0.02f);
//            Car.carY = Car.carY - forward.y * (carH * 0.02f);
//
//            Car.speed = 0.5;
//            Car.revspeed = 0.125;
//            PlaySound(crash);
//
//        }
//        else if (rearcoll)
//        {
//            Car.carX = Car.carX + forward.x * (carH * 0.02f);
//            Car.carY = Car.carY + forward.y * (carH * 0.02f);
//
//            Car.speed = 0.5;
//            Car.revspeed = 0.125;
//            PlaySound(crash);
//        }
//
//        // Updating Positions
//
//        // Drawing
//        BeginDrawing();
//
//        ClearBackground(green);
//        DrawTextureEx(background, { 0.0f, 0.0f }, 0, 1.3f, WHITE);
//
//
//
//        Vector2 carPos = { Car.carX, Car.carY };
//        Rectangle src = { 0,0,(float)car.width,(float)car.height };
//        Rectangle dst = { Car.carX, Car.carY,car.width / 20,car.height / 20 };
//        Vector2 origin = { car.width / 20, car.height / 20 };
//        origin.x = (car.width / 20) * Car.scale;
//        origin.y = (car.height / 20) * Car.scale;
//
//       // INVISIBLE SHAPES
//
//      /*DrawRectangleRec(offRec1, BLUE);
//       DrawRectangleRec(offRec2, BLUE);
//       DrawRectangleRec(offRec3, BLUE);
//
//       DrawRectangleRec(offRec4, BLUE);
//       DrawRectangleRec(offRec5, BLUE);
//       DrawRectangleRec(offRec6, BLUE);
//
//       DrawRectangleRec(offRec7, BLUE);
//       DrawRectangleRec(offRec8, BLUE);
//       DrawRectangleRec(offRec9, BLUE);
//
//       DrawCircleLines(frontCircle.x, frontCircle.y, radius, RED);
//       DrawCircleLines(rearCircle.x, rearCircle.y, radius, RED);*/
//
//
//        DrawTexturePro(car, src, dst, origin, Car.angle, WHITE);
//        EndDrawing();
//    }
//
//    UnloadTexture(car);
//    UnloadTexture(background);
//    CloseAudioDevice;
//    CloseWindow();
//    return 0;
//}
//
//void Drive(Car& Car)
//{
//
//    if (Car.speed > 0.6)
//    {
//        if (IsKeyDown(KEY_RIGHT)) Car.angle += 0.6;
//        if (IsKeyDown(KEY_LEFT))  Car.angle -= 0.6;
//    }
//    if (Car.revspeed > 0.15)
//    {
//        if (IsKeyDown(KEY_RIGHT)) Car.angle -= 0.3;
//        if (IsKeyDown(KEY_LEFT))  Car.angle += 0.3;
//    }
//    // coast
//    Car.carX += Car.speed * cosf(Car.angle * DEG2RAD);
//    Car.carY += Car.speed * sinf(Car.angle * DEG2RAD);
//
//    Car.carX -= 0.5 * cosf(Car.angle * DEG2RAD);
//    Car.carY -= 0.5 * sinf(Car.angle * DEG2RAD);
//
//    Car.carX -= Car.revspeed * cosf(Car.angle * DEG2RAD);
//    Car.carY -= Car.revspeed * sinf(Car.angle * DEG2RAD);
//
//    Car.carX += 0.125 * cosf(Car.angle * DEG2RAD);
//    Car.carY += 0.125 * sinf(Car.angle * DEG2RAD);
//
//    // friction
//    if (Car.speed > 0.5 && IsKeyUp(KEY_UP))
//    {
//        Car.speed = Car.speed * 0.985;
//    }
//    if (Car.revspeed > 0.125 && IsKeyUp(KEY_DOWN))
//    {
//        Car.revspeed = Car.revspeed * 0.985;
//    }
//    if (IsKeyDown(KEY_UP))
//    {
//        Car.carX += Car.speed * cosf(Car.angle * DEG2RAD);
//        Car.carY += Car.speed * sinf(Car.angle * DEG2RAD);
//
//        if (Car.speed < 3)
//            Car.speed = Car.speed * 1.01;
//
//
//    }
//    if (IsKeyDown(KEY_DOWN))
//    {
//        Car.carX -= Car.revspeed * cosf(Car.angle * DEG2RAD);
//        Car.carY -= Car.revspeed * sinf(Car.angle * DEG2RAD);
//
//        if (Car.revspeed < 1.0)
//            Car.revspeed = Car.revspeed * 1.01;
//
//    }
//
//
//
//}
