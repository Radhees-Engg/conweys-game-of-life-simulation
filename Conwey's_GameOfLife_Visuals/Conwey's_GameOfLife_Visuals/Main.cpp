#include <iostream>
#include <raylib.h>
#include <vector>

int gridSize = 100, cell = 1, empty = 0, cellSize = 10;
int dx[8] = { -1, 0, 1, 0, -1, 1, 1, -1 }, nx = 0;
int dy[8] = { 0, 1, 0, -1, 1, 1, -1, -1 }, ny = 0;
int generation = 0;

float currentTime = 0.0f, lastTime = 0.0f, TimerCooldown = 0.3;

class World
{
private:
    std::vector<std::vector<int>>& grid;
    std::vector<std::vector<int>> TempGrid;

    void WrapPos(int& nx, int& ny)
    {
        if (nx < 0) { nx = gridSize - 1; }
        if (ny < 0) { ny = gridSize - 1; }
        if (nx >= gridSize) { nx = 0; }
        if (ny >= gridSize) { ny = 0; }
    }

    void CheckNeighbour(int x, int y, int& neighbour)
    {
        for (int d = 0; d < 8; d++)
        {
            nx = x + dx[d];
            ny = y + dy[d];
            WrapPos(nx, ny);
            if (nx < grid.size() && ny < grid.size() && nx >= 0 && ny >= 0 && grid[nx][ny] == cell)
            {
                neighbour++;
            }
        }
    }

public:
    World(std::vector<std::vector<int>>& Grid) : grid(Grid), TempGrid(0)  {}

    void UpdateGrid()
    {
        TempGrid = grid;
        for (int x = 0; x < grid.size(); x++)
        {
            int neighbour = 0;
            for (int y = 0; y < grid.size(); y++)
            {
                neighbour = 0;
                if (grid[x][y] == cell)
                {
                    CheckNeighbour(x, y, neighbour);
                    if (neighbour > 3 || neighbour < 2)
                    {
                        TempGrid[x][y] = empty;
                    }
                }
                else if (grid[x][y] == empty)
                {
                    CheckNeighbour(x, y, neighbour);
                    if (neighbour == 3)
                    {
                        TempGrid[x][y] = cell;
                    }
                }
                else std::cout << " This is Not Possible " << std::endl;
            }
        }
        grid = TempGrid;
        generation += 1;
    }

    void PrintGrid()
    {
        for (auto row = grid.begin(); row != grid.end(); row++)
        {
            for (auto cols = row->begin(); cols != row->end(); cols++)
            {
                std::cout << *cols;
            }
            std::cout << std::endl;
        }
    }
};

class Render
{
private:
    std::vector<std::vector<int>>& grid;
    Camera2D& cam;
    int MouseWheel;
public:

    Render(std::vector<std::vector<int>>& Grid, Camera2D& camera) : grid(Grid), cam(camera), MouseWheel(0) {}

    void UpdateCam_Mouse(Camera2D& camera)
    {
        MouseWheel = GetMouseWheelMove();
        cam = camera;
    }

    void DrawGrid()
    {
        for (int i = 0; i < grid.size(); i++)
        {
            for (int j = 0; j < grid.size(); j++)
            {
                if (grid[i][j] == cell)
                {
                    DrawRectangle(i * cellSize, j * cellSize, cellSize, cellSize, GREEN);
                }
                DrawRectangleLines(i * cellSize, j * cellSize, cellSize, cellSize, GRAY);
            }
        }
    }
    void MoveGridCam()
    {
        if (IsKeyDown(KEY_RIGHT)) { cam.target.x += 2; }
        if (IsKeyDown(KEY_DOWN)) { cam.target.y += 2; }
        if (IsKeyDown(KEY_LEFT) && cam.target.x >= 0) { cam.target.x -= 2; }
        if (IsKeyDown(KEY_UP) && cam.target.y >= 0) { cam.target.y -= 2; }
        if (IsKeyPressed(KEY_R)) 
        {
            cam.target = { 0,0 };
            cam.zoom = 1.0f;
        }
        if (MouseWheel > 0) { cam.zoom += 0.08; }
        if (MouseWheel < 0) { cam.zoom -= 0.08; }
    }
};

int main()
{
    const int ScreenHeight = 900, ScreenWidth = 1000;
    InitWindow(ScreenWidth, ScreenHeight, "VisualizeGameOfLife");
    SetTargetFPS(GetMonitorRefreshRate(0));

    Camera2D cam;
    cam.offset = { 0.0f,0.0f };
    cam.rotation = 0;
    cam.target = { 0.0f,0.0f };
    cam.zoom = 1.0f;

    std::vector<std::vector<int>> grid(gridSize, std::vector<int>(gridSize));

    // this is oscillator
    //grid[4][4] = cell;
    //grid[4][3] = cell;
    //grid[4][5] = cell;

    /* This is space ship
    grid[21][10] = cell;
    grid[24][10] = cell;
    grid[20][11] = cell;
    grid[20][12] = cell;
    grid[24][12] = cell;    
    grid[20][13] = cell;
    grid[21][13] = cell;
    grid[22][13] = cell;
    grid[23][13] = cell;
    */

     // this is ACRON
    grid[48][50] = cell;
    grid[49][50] = cell;
    grid[49][48] = cell;
    grid[51][49] = cell;
    grid[52][50] = cell;
    grid[53][50] = cell;
    grid[54][50] = cell;
    

    World world(grid);
    Render render(grid, cam);

    while (!WindowShouldClose())
    {
        currentTime = GetTime();
        render.UpdateCam_Mouse(cam);
        if (currentTime - lastTime >= TimerCooldown)
        {
            world.UpdateGrid();
            lastTime = currentTime;
        }
        BeginDrawing();
        BeginMode2D(cam);
        ClearBackground(BLACK);
        render.DrawGrid();
        render.MoveGridCam();
        std::cout << '\r' << "Gen: " << generation;

        EndMode2D();
        EndDrawing();
    }
    CloseWindow();
}