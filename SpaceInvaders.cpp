#include <iostream>
#include <windows.h>
#include <string>
#include <ctime>

using namespace std;


/* Global Variables */
int boardy = 15;
int boardx = 20;
char playerSymbol = '^';
char bulletSymbol = '*';
char alienSymbol = '@';
char wallSymbol = '#';
char emptySymbol = ' ';
int GameSpeed = 100;
bool isBullet = false;


class Player{
    public:

    int x, y, startx, starty, lives, score;

    Player()
    {
        x = 0;
        y = 0;
        startx = 9;
        starty = 13;
        lives = 3;
        score = 0;
    }
};

struct Aliens{
    int xfirst, xlast, yfirst, ylast;
    bool isGoLeft;
    Aliens()
    {
        xfirst = 4;
        xlast = 13;
        yfirst = 2;
        ylast = 6;
        isGoLeft = false;
    }
};
struct Bullet{
    int x, y;

    Bullet(Player &player)
    {
        x = player.x;
        y = player.y;
    }
};

/* Game Board*/
char board[15][20] =
{
    "###################",
    "#                 #",
    "#   @@@@@@@@@@    #",
    "#    @@@@@@@@     #",
    "#      @@@@@      #",
    "#       @@@       #",
    "#        @        #",
    "#                 #",
    "#                 #",
    "#                 #",
    "#                 #",
    "#                 #",
    "#                 #",
    "#                 #",
    "###################"
};

bool isValidPosition(int x, int y)
{
    return x < 20 && x >= 0 && y < 15 && y >= 0;
}

bool moveBullet(Bullet &bullet, Player &player)
{
    if(isValidPosition(bullet.x, bullet.y - 1) )
    {
        char block = board[bullet.y-1][bullet.x];
        if(block == emptySymbol)
        {
            (board[bullet.y][bullet.x] == playerSymbol ? : board[bullet.y][bullet.x] = emptySymbol);
            board[bullet.y-1][bullet.x] = bulletSymbol;
            bullet.y--;
            return true;
        }
        else if(block == alienSymbol)
        {
            player.score++;
            board[bullet.y][bullet.x] = emptySymbol;
            board[bullet.y-1][bullet.x] = emptySymbol;
            return false;
        }
        else if(block == wallSymbol)
        {
            board[bullet.y][bullet.x] = emptySymbol;
            return false;
        }
    }
    else
    {
        board[bullet.y][bullet.x] = emptySymbol;
        return false;
    }
}

bool moveBullet(int x, int y, Player &player)
{
    if(isValidPosition(x, y - 1) )
    {
        char block = board[y-1][x];
        if(block == emptySymbol)
        {
            (board[y][x] == playerSymbol ? : board[y][x] = emptySymbol);
            board[y-1][x] = bulletSymbol;
            return true;
        }
        else if(block == alienSymbol)
        {
            player.score++;
            board[y][x] = emptySymbol;
            board[y-1][x] = emptySymbol;
            return false;
        }
        else if(block == wallSymbol)
        {
            board[y][x] = emptySymbol;
            return false;
        }
    }
    else
    {
        board[y][x] = emptySymbol;
        return false;
    }
}

void movePlayer(Player &player, int x, int y)
{
    if(isValidPosition(x, y))
    {
        if(board[y][x] != emptySymbol)
            return;

        board[player.y][player.x] = emptySymbol;

        board[y][x] = playerSymbol;
        player.x = x;
        player.y = y;
    }
}

void moveAliens(Aliens &aliens)
{
    int alieny;
    bool isGoDown = false;

    if(board[aliens.yfirst][aliens.xfirst - 1] == emptySymbol && board[aliens.ylast][aliens.xlast + 1] == wallSymbol && !aliens.isGoLeft)
    {
        aliens.isGoLeft = true;
        isGoDown = true;
    }
    else if(board[aliens.yfirst][aliens.xfirst - 1] == wallSymbol && board[aliens.ylast][aliens.xlast + 1] == emptySymbol && aliens.isGoLeft)
    {
        aliens.isGoLeft = false;
    }

    if(!aliens.isGoLeft)
    {
        for(int i = aliens.yfirst; i <= aliens.ylast; i++)
            for(int j = aliens.xlast + 1; j >= aliens.xfirst; j--)
            {
                board[i][j] = board[i][j-1];
            }
        aliens.xfirst++;
        aliens.xlast++;
    }
    else if(aliens.isGoLeft)
    {
        for(int i = aliens.yfirst; i <= aliens.ylast; i++)
        {
            for(int j = aliens.xfirst; j <= aliens.xlast; j++)
            {
                if(board[i][j+1] == wallSymbol)
                    board[i][j] = emptySymbol;
                else board[i][j] = board[i][j+1];
            }
        }

        aliens.xfirst--;
        aliens.xlast--;
    }
}
void alienAttack(Aliens aliens)
{
    int random = rand() % (aliens.ylast - aliens.yfirst);

    if(board[aliens.ylast - 1][random] == alienSymbol && board[aliens.ylast][random] == emptySymbol)
        board[aliens.ylast][random]  = bulletSymbol;

}

void displayboard()
{
    for(int i = 0; i < boardy; i++)
    {
        cout << board[i] << endl;
    }
}

void displayPlayerInfo(Player &player)
{
    cout << "     Score = " << player.score << endl;
    cout << "     Lives = " << player.lives << endl;
}

void displayIntro()
{
    system("cls");
    int xFirst = 4, xlast = 15,
        xSFirst = 3, xSlast = 16;
    int Speed = 500;
    char Map[15][20] =
    {
        "                   ",
        "                   ",
        "                   ",
        "                   ",
        "                   ",
        "                   ",
        "                   ",
        "                   ",
        "                   ",
        "                   ",
        "                   ",
        "                   ",
        "                   ",
        "                   ",
        "                   "
    };
    char word1[13] = "Command Line";
    //char word2[15] = "Space Invaders";


    //for(int i = 21; i >= 0; i--)
    //{
       // if(i == 21)
       //     Sleep(Speed);
       int counter = 0;
        for(int j = xFirst; j <= xlast; j++)
        {
            Map[13][j] = word1[counter++];
        }
        for(int i = 0; i < 20; i++)
            cout << Map[i] << endl;

        Sleep(Speed);
    //}
}
void gameLoop()
{
    Player player;
    Bullet *bullet;
    Aliens aliens;
    bool isFinished = false;
    int counter = 0;

    movePlayer(player, player.startx, player.starty);
    displayIntro();

    while(!isFinished)
    {
        system("cls");
        displayboard();
        displayPlayerInfo(player);



        if(GetAsyncKeyState(VK_SPACE) )
        {
            if(!isBullet)
            {
                bullet = new Bullet(player);
                isBullet = true;
            }
        }
        else if(GetAsyncKeyState(VK_LEFT) )
        {
            movePlayer(player, player.x - 1, player.y);
        }
        else if(GetAsyncKeyState(VK_RIGHT) )
        {
            movePlayer(player, player.x + 1, player.y);
        }
        else if(GetAsyncKeyState(VK_LCONTROL) )
        {
            break;
        }

        if(isBullet)
            if(!moveBullet(*bullet, player) )
            {
                isBullet = false;
                delete bullet;
            }

        //if(++counter % 10 == 0 ) moveAliens(aliens) ;
        alienAttack(aliens);

        Sleep(GameSpeed);
    }
}
int main()
{
    cout << "This a barebone Space Invaders command line game!" << endl << endl;
    gameLoop();

    cin.get();
    return 0;
}


