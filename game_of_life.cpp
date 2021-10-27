#include <iostream>
#include <vector>

using namespace std;

#define BOX 25

class Cell
{
    int x;
    int y;
    bool alive;

public:
    void setX(int x)
    {
        this->x = x;
    };

    void setY(int y)
    {
        this->y = y;
    };

    void setBoth(int x, int y)
    {
        this->x = x;
        this->y = y;
    };

    void setAlive(bool alive)
    {
        this->alive = alive;
    }

    int getX()
    {
        return this->x;
    };

    int getY()
    {
        return this->y;
    };

    bool getAlive()
    {
        return this->alive;
    }

    vector<int> getBoth()
    {
        vector<int> coords = {this->x, this->y};
        return coords;
    };
};

void initMap(Cell **map);
void printMap(Cell **map, bool neighBors);
void mapRound(Cell **map);
int countNeighbors(Cell cell, Cell **map);

int main()
{
    /* Defining the map */
    Cell **map;
    map = new Cell *[BOX];
    for (int i = 0; i < BOX; i++)
    {

        map[i] = new Cell[BOX];
    }

    /*initializing coordinates*/
    initMap(map);

    int rounds = 0;
    //change to any positive integer to adapt rounds
    int totalrounds = 100;

    while(rounds<totalrounds){
        cout << "-------ROUND "<<rounds+1<< "------" <<endl;
        mapRound(map);

        //the boolean parameter can be turned to true to show the number
        //of alive neighbors of each cell instead of the cells
        printMap(map, false);
        rounds++;
    }

    //cleanup
    for (int i = 0; i < BOX; i++)
    {
        delete[] map[i];
    }

    return 0;
}

void initMap(Cell **map)
{

    int i = 0;
    int j = 0;

    for (i = 0; i < BOX; i++)
    {
        for (j = 0; j < BOX; j++)
        {
            map[i][j].setX(j);
            map[i][j].setY(i);
            map[i][j].setAlive(false);
        }
    }

    map[11][11].setAlive(true);
    map[11][12].setAlive(true);
    map[12][10].setAlive(true);
    map[12][11].setAlive(true);
    map[12][13].setAlive(true);
    map[13][10].setAlive(true);
    map[13][13].setAlive(true);
    map[14][11].setAlive(true);
    map[14][12].setAlive(true);

    return;
}

void printMap(Cell **map, bool neighBors)
{

    for (int i = 0; i < BOX; i++)
    {
        cout << "##### ";
        for (int j = 0; j < BOX; j++)
        {
            if (map[i][j].getAlive() == false)
            {
               if(neighBors){
                   cout << countNeighbors(map[i][j],map);
               }
               else{
                   cout << " ";
               }
            }
            else
            {
               if(neighBors){
                   cout << countNeighbors(map[i][j],map);
               }
               else{
                   cout << "0";
               }
            }
        }
        cout << " #####" << endl;
    }
}

void mapRound(Cell **map)
{
    vector<Cell> toLive;
    vector<Cell> toDie;
    
    for (int i = 0; i < BOX; i++)
    {
        for (int j = 0; j < BOX; j++)
        {
            int count = countNeighbors(map[i][j], map);
            bool alive = map[i][j].getAlive();

            if (alive)
            {
                if ((count == 0) || (count == 1))
                {
                    cout << j << "," << i << " has died" << endl;
                    Cell cell;
                    cell.setX(map[i][j].getX());
                    cell.setY(map[i][j].getY());
                    toDie.push_back(cell);
                }
                else if(count>3){
                    cout << j << "," << i << " has died" << endl;
                    Cell cell;
                    cell.setX(map[i][j].getX());
                    cell.setY(map[i][j].getY());
                    toDie.push_back(cell);
                }
                else
                {
                    continue;
                }
            }
            else
            {
                if (count == 3)
                {
                    cout << j << "," << i << " has come to life" << endl;
                    Cell cell;
                    cell.setX(map[i][j].getX());
                    cell.setY(map[i][j].getY());
                    toLive.push_back(cell);
                }
            }
        }
    }

    for(Cell cell: toLive){
        map[cell.getY()][cell.getX()].setAlive(true);
    }

    for(Cell cell: toDie){
        map[cell.getY()][cell.getX()].setAlive(false);
    }
}

int countNeighbors(Cell cell, Cell **map)
{

    int x = cell.getX();
    int y = cell.getY();
    int count = 0;

    //check up 1
    if ((y - 1) >= 0)
    {
        if (map[y - 1][x].getAlive() == true)
        {
            count++;
        }
    }

    //check upleft 2
    if (((y - 1) >= 0) && ((x - 1) >= 0))
    {
        if (map[y - 1][x - 1].getAlive() == true)
        {
            count++;
        }
    }

    //check left 3
    if ((x - 1) >= 0)
    {
        if (map[y][x - 1].getAlive() == true)
        {
            count++;
        }
    }
    //check bottomleft 4
    if (((y + 1) != BOX) && ((x - 1) >= 0))
    {
        if (map[y + 1][x - 1].getAlive() == true)
        {
            count++;
        }
    }

    //check bottom 5
    if ((y + 1) != BOX)
    {
        if (map[y + 1][x].getAlive() == true)
        {
            count++;
        }
    }

    //check bottom right 6
    if (((y + 1) != BOX) && ((x + 1) != BOX))
    {
        if (map[y + 1][x + 1].getAlive() == true)
        {
            count++;
        }
    }

    //check right 7
    if ((x + 1) != BOX)
    {
        if (map[y][x + 1].getAlive() == true)
        {
            count++;
        }
    }

    //check top right 8
    if (((y - 1) >= 0) && ((x + 1) != BOX))
    {
        if (map[y - 1][x + 1].getAlive() == true)
        {
            count++;
        }
    }

    return count;
}

