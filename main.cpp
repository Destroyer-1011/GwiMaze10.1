#pragma warning(disable : 4996) 
#include <iostream>
#include <vector>
#include <png.hpp>

struct Coords {
public:
    unsigned int x;
    unsigned int y;

    Coords() {
        x = 0;
        y = 0;
    }

    Coords(unsigned int xi, unsigned int yi) {
        x = xi;
        y = yi;
    }
};

const static char patterns[16][5][6] = {
    { //0 all
        "XXXXX",
        "X000X",
        "X000X",
        "X000X",
        "XXXXX"
    },
    { //1 b
        "XXXXX",
        "X000X",
        "X000X",
        "X000X",
        "X000X"
    },
    { //2 bl
        "XXXXX",
        "0000X",
        "0000X",
        "0000X",
        "X000X"
    },
    { //3 br
        "XXXXX",
        "X0000",
        "X0000",
        "X0000",
        "X000X"
    },
    { //4 l
        "XXXXX",
        "0000X",
        "0000X",
        "0000X",
        "XXXXX"
    },
    { //5 lbr
        "XXXXX",
        "00000",
        "00000",
        "00000",
        "X000X"
    },
    { //6 lr
        "XXXXX",
        "00000",
        "00000",
        "00000",
        "XXXXX"
    },
    { //7 ltb
        "X000X",
        "0000X",
        "0000X",
        "0000X",
        "X000X"
    },
    { //8 ltr
        "X000X",
        "00000",
        "00000",
        "00000",
        "XXXXX"
    },
    { //9 r
        "XXXXX",
        "X0000",
        "X0000",
        "X0000",
        "XXXXX"
    },
    { //10 t
        "X000X",
        "X000X",
        "X000X",
        "X000X",
        "XXXXX"
    },
    { //11 tb
        "X000X",
        "X000X",
        "X000X",
        "X000X",
        "X000X"
    },
    { //12 tl
        "X000X",
        "0000X",
        "0000X",
        "0000X",
        "XXXXX"
    },
    { //13 tr
        "X000X",
        "X0000",
        "X0000",
        "X0000",
        "XXXXX"
    },
    { //14 trb
        "X000X",
        "X0000",
        "X0000",
        "X0000",
        "X000X"
    },
    { //15 none
        "X000X",
        "00000",
        "00000",
        "00000",
        "X000X"
    }
};

static unsigned int w;
static unsigned int h;
static unsigned int xStart;
static Coords endCoords;
static std::vector<std::vector<int_fast8_t>> data;

int_fast8_t getAvailable(Coords cell) {
    int pathsAvailable = 0;

    if (cell.x != endCoords.x || cell.y != endCoords.y) {
        if (cell.x != 0 && data[cell.x - 1][cell.y] == 0)
        {
            pathsAvailable++;
        }
        //check right
        if (cell.x != w - 1 && data[cell.x + 1][cell.y] == 0)
        {
            pathsAvailable++;
        }
        //check top
        if (cell.y != 0 && data[cell.x][cell.y - 1] == 0)
        {
            pathsAvailable++;
        }
        //check bottom
        if (cell.y != h - 1 && data[cell.x][cell.y + 1] == 0)
        {
            pathsAvailable++;
        }
    }

    return pathsAvailable;
}
void update(Coords coords, Coords result) {
    int8_t currentConfig = data[coords.x][coords.y];
    bool* walls;
    switch (currentConfig)
    {
    case (int_fast8_t)0:
        walls = new bool[] { false, false, false, false };
        break;
    case (int_fast8_t)1:
        walls = new bool[] { false, false, false, true };
        break;
    case (int_fast8_t)2:
        walls = new bool[] { true, false, false, true };
        break;
    case (int_fast8_t)3:
        walls = new bool[] { false, false, true, true };
        break;
    case (int_fast8_t)4:
        walls = new bool[] { true, false, false, false };
        break;
    case (int_fast8_t)5:
        walls = new bool[] { true, false, true, true };
        break;
    case (int_fast8_t)6:
        walls = new bool[] { true, false, true, false };
        break;
    case (int_fast8_t)7:
        walls = new bool[] { true, true, false, true };
        break;
    case (int_fast8_t)8:
        walls = new bool[] { true, true, true, false };
        break;
    case (int_fast8_t)9:
        walls = new bool[] { false, false, true, false };
        break;
    case (int_fast8_t)10:
        walls = new bool[] { false, true, false, false };
        break;
    case (int_fast8_t)11:
        walls = new bool[] { false, true, false, true };
        break;
    case (int_fast8_t)12:
        walls = new bool[] { true, true, false, false };
        break;
    case (int_fast8_t)13:
        walls = new bool[] { false, true, true, false };
        break;
    case (int_fast8_t)14:
        walls = new bool[] { false, true, true, true };
        break;
    case (int_fast8_t)15:
        walls = new bool[] { true, true, true, true };
        break;
    default:
        throw "wtf?";
    }

    switch (result.x)
    {
    case 0:
        if (result.y == 1)
        {
            walls[3] = true;
        }
        else
        {
            walls[1] = true;
        }
        break;
    case 1:
        walls[2] = true;
        break;
    case -1:
        walls[0] = true;
        break;
    }

    if (walls[0] && walls[1] && walls[2] && walls[3])
    {
        data[coords.x][coords.y] = 15;
    }
    else if (walls[0] && !walls[1] && !walls[2] && !walls[3])
    {
        data[coords.x][coords.y] = 4;
    }
    else if (!walls[0] && walls[1] && !walls[2] && !walls[3])
    {
        data[coords.x][coords.y] = 10;
    }
    else if (!walls[0] && !walls[1] && walls[2] && !walls[3])
    {
        data[coords.x][coords.y] = 9;
    }
    else if (!walls[0] && !walls[1] && !walls[2] && walls[3])
    {
        data[coords.x][coords.y] = 1;
    }
    else if (walls[0] && !walls[1] && walls[2] && !walls[3])
    {
        data[coords.x][coords.y] = 6;
    }
    else if (!walls[0] && walls[1] && !walls[2] && walls[3])
    {
        data[coords.x][coords.y] = 11;
    }
    else if (walls[0] && !walls[1] && walls[2] && walls[3])
    {
        data[coords.x][coords.y] = 5;
    }
    else if (walls[0] && walls[1] && !walls[2] && walls[3])
    {
        data[coords.x][coords.y] = 7;
    }
    else if (walls[0] && walls[1] && walls[2] && !walls[3])
    {
        data[coords.x][coords.y] = 8;
    }
    else if (!walls[0] && walls[1] && walls[2] && walls[3])
    {
        data[coords.x][coords.y] = 14;
    }
    else if (!walls[0] && walls[1] && walls[2] && !walls[3])
    {
        data[coords.x][coords.y] = 13;
    }
    else if (walls[0] && walls[1] && !walls[2] && !walls[3])
    {
        data[coords.x][coords.y] = 12;
    }
    else if (walls[0] && !walls[1] && !walls[2] && walls[3])
    {
        data[coords.x][coords.y] = 2;
    }
    else if (!walls[0] && !walls[1] && walls[2] && walls[3])
    {
        data[coords.x][coords.y] = 3;
    }
    else
    {
        data[coords.x][coords.y] = 0;
    }

    delete[] walls;
}

int main(int argc, char** argv)
{
    const unsigned int maxLength = 0xFFFFFFFF / 5;
    std::cout << "Enter your desired width:\n";
    std::cin >> w;
    while (w < maxLength) {
        std::cout << "Please enter a width less than " << maxLength << ":";
        std::cin >> w;
    }
    std::cout << "Enter your desired height:\n";
    std::cin >> h;
    while (h < maxLength) {
        std::cout << "Please enter a height less than " << maxLength << ":";
        std::cin >> h;
    }
    
    data = std::vector<std::vector<int_fast8_t>>(w, std::vector<int_fast8_t>(h, 0));
    std::vector<Coords> cellBackTrack;
    srand(time(NULL));
    endCoords = Coords(rand() % w + 1, 0);
    xStart = rand() % w + 1;
    Coords cell = Coords(xStart, h - 1);
    cellBackTrack.push_back(cell);
    while (true) {
        //int pathsAvailable = getAvailable(cell);

        //checking for end condition
        if (getAvailable(cell) == 0) {
            while (true) {
                cellBackTrack.pop_back();
                if (cellBackTrack.size() == 0) goto Finish;

                if (getAvailable(cellBackTrack.back()) != 0) {
                    cell = cellBackTrack.back();
                    break;
                }
            }
        }

        //goes to new cell and removes wall
        Coords result = Coords(0, 0);
        Coords nextCoords = Coords(0, 0);
        while (true) {

            int8_t dir = rand() & 0b11; //bit operation hack for fast mod 4
            switch (dir){
                case 0:
                    result = Coords(-1, 0);
                    break;
                case 1:
                    result = Coords(0, 1);
                    break;
                case 2:
                    result = Coords(1, 0);
                    break;
                case 3:
                    result = Coords(0, -1);
                    break;
            }
            unsigned int x = cell.x + result.x;
            unsigned int y = cell.y + result.y;
            if (x < w && x > -1 && y < h && y > -1 && data[x][y] == 0) {
                if (x == endCoords.x && y == endCoords.y && getAvailable(endCoords)) continue;
                nextCoords = Coords(x, y);
                break;
            }
        }

        update(cell, result);
        update(nextCoords, Coords(-result.x, -result.y));

        if (nextCoords.x != endCoords.x || nextCoords.y != endCoords.y) {
            cellBackTrack.push_back(nextCoords);
            cell.x = nextCoords.x;
            cell.y = nextCoords.y;
        }
    }
Finish:
    
    png::image<png::rgb_pixel> maze(w * 5, h * 5);

    unsigned int columns = w * 5;
    unsigned int rows = h * 5;
    unsigned int X = 0;
    unsigned int Y = 0;
    png::rgb_pixel black(0, 0, 0);
    png::rgb_pixel white(255, 255, 255);

    for (int_fast32_t x = 0; x < w; x++)
    {
        Y = 0;
        for (int_fast32_t y = 0; y < h; y++)
        {
            for (int_fast8_t a = 0; a < 5; a++)
            {
                for (int_fast8_t b = 0; b < 5; b++)
                {
                    maze[Y + b][X + a] = patterns[data[x][y]][b][a] == 'X' ? black : white;
                }
            }
            Y += 5;
        }
        X += 5;
    }
    
    png::rgb_pixel green(0, 255, 0);
    png::rgb_pixel red(255, 0, 0);
    for (int_fast8_t a = 0; a < 5; a++)
    {
        for (int_fast8_t b = 0; b < 5; b++)
        {
            maze[(h - 1) * 5 + b][xStart * 5 + a] = red;
        }
    }

    
    for (int_fast8_t a = 0; a < 5; a++)
    {
        for (int_fast8_t b = 0; b < 5; b++)
        {
            maze[b][endCoords.x * 5 + a] = green;
        }
    }

    maze.write("maze.png");
    std::cout << "Done!\n";
}
