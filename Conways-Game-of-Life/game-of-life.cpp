#include <iostream>
#include <Windows.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>


struct cell
{
    bool live = false;
    int y;
    int x;
};

const int maxX = 20;
const int maxY = 10;
cell cells[maxY][maxX] = { {} };
cell getCellAt(int y, int x) // starts at 0
{
    if(cells[y][x].y == y + 1 && cells[y][x].x == x + 1)
        return cells[y][x];
}

int tick() // play a round
{
    cell new_cells[maxY][maxX];
    memcpy(new_cells, cells, sizeof(new_cells));
    for (int y = 0; y < maxY; y++)
    {
        for (int x = 0; x < maxX; x++)
        {
            cell adj[8] = {};
            if (x > 0)
                adj[0] = cells[y][x - 1]; // left
            if (y > 0)
                adj[1] = cells[y - 1][x - 1]; // top left
            if (x < maxX)
                adj[2] = cells[y][x + 1]; // right
            if (y < maxY)
                adj[3] = cells[y - 1][x + 1]; // top right
            if (y > 0)
                adj[4] = cells[y - 1][x]; // top
            if (x < maxX)
                adj[5] = cells[y + 1][x + 1]; // bottom right
            if (y < maxY)
                adj[6] = cells[y + 1][x]; // bottom
            if (x > 0)
                adj[7] = cells[y + 1][x - 1]; // bottom left
            int liveCount = 0;
            int deadCount = 0;
            for (int i = 0; i < 8; i++)
            {
                if (adj[i].y > 0)
                {
                    if (adj[i].live)
                        liveCount += 1;
                    else
                        deadCount += 1;
                }
            }/*
            if (y == 0 && x == 2)
            {
                std::cout << "is live " << cells[y][x].live << " [" << cells[y][x].y << ", " << cells[y][x].x  << "]" << std::endl;
                std::cout << "live count " << liveCount << std::endl;
                std::cout << "dead count " << deadCount << std::endl;
                for (int i = 0; i < 8; i++)
                {
                    std::cout << i << " .. cell at " << adj[i].y << ", " << adj[i].x << " is live: " << adj[i].live << std::endl;
                }
            }*/
            if (cells[y][x].live && (liveCount == 3 || liveCount == 2))
                new_cells[y][x].live = true;
                //cells[y][x].live = true;
            else if(!cells[y][x].live && liveCount == 3)
                new_cells[y][x].live = true;
                //cells[y][x].live = true;
            else if(cells[y][x].live)
                new_cells[y][x].live = false;
                //cells[y][x].live = false;
        }
        std::cout << std::endl;
    }
    memcpy(cells, new_cells, sizeof(cells));
    return 1;
}

int main() // setup
{
    srand(time(0));
    for (int y = 0; y < maxY; y++)
    {
        for (int x = 0; x < maxX; x++)
        {
            cells[y][x] = { (bool)(rand() % 2), y + 1, x + 1 };
        }
    }
    std::string A = "";
    int alive;
    int dead;
    for(int i = 0; i < 0x7FFFFFFF; i++)
    {
        A = "";
        alive = 0;
        dead = 0;
        for (int y = 0; y < maxY; y++)
        {
            for (int x = 0; x < maxX; x++)
            {
                if (cells[y][x].live)
                {
                    alive++;
                    A += "x";
                }
                else
                {
                    dead++;
                    A += "-";
                }
            }
            A += "\n";
        }
        std::cout << A << std::endl;
        std::cout << maxY << ", " << maxX << " tick [" << i << "]" << std::endl;
        std::cout << alive << " alive" << std::endl;
        std::cout << dead << " dead" << std::endl;
        tick();
        Sleep(800);
        //std::cin.get();
        system("cls");
    }
}