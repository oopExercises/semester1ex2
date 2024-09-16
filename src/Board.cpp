#include "Board.h"
#include <string>
#include <fstream>
#include <iostream> 

using std::cerr;
using std::endl;
using std::ifstream;
using std::cout;


int Board::getHeight()
{
    //to get the height of the map
    return (int)map.size();
}

Board::Board(int p, int lvl, int hp)
{
    m_pacman = Player();
    m_superSteps = 20;

    m_giftIsTaken = false;
    m_super = false;
    m_pacman.setHealth(3);
    m_allPoints = p;
    m_currentLevel = lvl;
    m_playerHealth = hp;

    //opens the file
    file.open("Levels.txt");
    if (!file.is_open()) {
        cerr << "input file not found" << endl;
        exit(EXIT_FAILURE);
    }

    //reading the level's name
    for (auto line = std::string(); std::getline(file, line);)
    {
        levels.push_back(line);
    }

    file.close();

    m_number_of_levels = (int)levels.size();
}

//function that builds the map into vector
void Board::buildMap(int index)
{
    std::string level = levels[index];
 
    //opens the file
    file.open(level);
    if (!file.is_open()) {
        cerr << level << " file not found" << endl;
        exit(EXIT_FAILURE);
    }

    //reads the map/level
    for (auto line = std::string(); std::getline(file, line);)
    {
        map.push_back(line);
    }

    std::system("cls"); // resets the screen

    char c;
    std::string theSuper;
    //prints the map for the first time and saves the characters & objects position
    for (int i = 0; i < map.size(); i++)
    {
        for (int j = 0; j < map[i].size(); j++)
        {
            Vertex position = Vertex(j, i);
            c = map[i][j];
            cout << c;

            switch (c)
            {
            case 'a':
                m_pacman.setPosition(position);
                m_initPlayerPos.setX(position.getX());
                m_initPlayerPos.setY(position.getY());
                break;
            case '&':
                demon.push_back(Enemy(position));
                initDemonPos.push_back(Vertex(position));
                break;
            case '%':
                key.push_back(Key(position));
                break;
            case '*':
                cake.push_back(Cake(position));
                break;
            case '$':
                gift.push_back(Gift(position));
                break;
            case 'D':
                door.push_back(Vertex(position));
                break;
            }
          
        }
        cout << endl;

        if (m_giftIsTaken)
        {
            m_super = true;
            theSuper = "true";
        }
        else
        {
            m_super = false;
            theSuper = "false";
        }
    }
     cout << "\nlevel: " << m_currentLevel + 1;
     cout << "\nHealth: " << getPlayerHealth();
     cout << "\nallPoints: " << m_allPoints;
}

Player Board::getPlayer()
{
    return m_pacman;
}

std::vector<std::string> Board::getMap()
{
    return map;
}

void Board::updatePlayerPos(Vertex position)
{
    m_pacman.setPosition(position);
}

void Board::updateMap(int x , int y , char c)
{
    map[y][x] = c;
}

//function that updates the tiles on the screen
void Board::updateScreen(char character)
{
   

    //if the character is pacman or superpacman
    if (character != enemyChar)
    {
        
        for (int i = 0; i < key.size(); i++)
        {
            //if the current tile that supposed to hold key is empty
            //it means the pacman took the key and its place is empty
            if (getMap()[key[i].getPosition().getY()][key[i].getPosition().getX()] == ' ')
            {
                //print space in the place that was a key
                Screen::setLocation(Location(key[i].getPosition().getY(), key[i].getPosition().getX()));
                cout << ' ';

                //updates the map vector and put space instead of the key that was taken
                updateMap(key[i].getPosition().getX(), key[i].getPosition().getY(), ' ');

                //removes the key from the key vector
                key.erase(key.begin() + i);

                //reset the cursor to the end of the map
                Screen::setLocation(Location(getHeight(), 0));
            }
        }
        for (int i = 0; i < cake.size(); i++)
        {
            //if the current tile that supposed to hold cake is empty
            //it means the pacman took the cake and its place is empty
            if (getMap()[cake[i].getPosition().getY()][cake[i].getPosition().getX()] == ' ')
            {
                //print space in the place that was a cake
                Screen::setLocation(Location(cake[i].getPosition().getY(), cake[i].getPosition().getX()));
                cout << ' ';

                //updates the map vector and put space instead of the cake that was taken
                updateMap(cake[i].getPosition().getX(), cake[i].getPosition().getY(), ' ');

                //reset the cursor to the end of the map
                Screen::setLocation(Location(getHeight(), 0));
            }
        }
        for (int i = 0; i < gift.size(); i++)
        {
            //if the current tile that supposed to hold gift is empty
             //it means the pacman took the gift and its place is empty
            if (getMap()[gift[i].getPosition().getY()][gift[i].getPosition().getX()] == ' ')
            {
                //print space in the place that was a gift
                Screen::setLocation(Location(gift[i].getPosition().getY(), gift[i].getPosition().getX()));
                cout << ' ';

                //updates the map vector and put space instead of the cake that was taken
                updateMap(gift[i].getPosition().getX(), gift[i].getPosition().getY(), ' ');

                //reset the cursor to the end of the map
                Screen::setLocation(Location(getHeight(), 0));
            }
        }

        for (int i = 0; i < demon.size(); i++)
        {
           //if the pacman touches a demon and the demon place became a space, then print & which is the demon
            if (getMap()[demon[i].getPosition().getY()][demon[i].getPosition().getX()] == ' ')
            {
                //print demon in its place
                Screen::setLocation(Location(demon[i].getPosition().getY(), demon[i].getPosition().getX()));
                cout << '&';

                //updates the map vector and put demon in its place
                updateMap(demon[i].getPosition().getX(), demon[i].getPosition().getY(), '&');

                //reset the cursor to the end of the map
                Screen::setLocation(Location(getHeight(), 0));
            }
        }
    }
    
    //if the character is demon
    else
    {
        for (int i = 0; i < key.size(); i++)
        {
            //if the place of a key is space because the demon touched the key
            if (getMap()[key[i].getPosition().getY()][key[i].getPosition().getX()] == ' ')
            {
                //print key in its place
                Screen::setLocation(Location(key[i].getPosition().getY(), key[i].getPosition().getX()));
                cout << '%';

                //updates the map vector and put key in its place
                updateMap(key[i].getPosition().getX(), key[i].getPosition().getY(), '%');

                //reset the cursor to the end of the map
                Screen::setLocation(Location(getHeight(), 0));
            }
        }
        for (int i = 0; i < cake.size(); i++)
        {
            //if the place of a cake is space because the demon touched the cake
            if (getMap()[cake[i].getPosition().getY()][cake[i].getPosition().getX()] == ' ')
            {
                //print cake in its place
                Screen::setLocation(Location(cake[i].getPosition().getY(), cake[i].getPosition().getX()));
                cout << '*';

                //updates the map vector and put cake in its place
                updateMap(cake[i].getPosition().getX(), cake[i].getPosition().getY(), '*');

                //reset the cursor to the end of the map
                Screen::setLocation(Location(getHeight(), 0));
            }
        }
        for (int i = 0; i < gift.size(); i++)
        {
            //if the place of a gift is space because the demon touched the gift
            if (getMap()[gift[i].getPosition().getY()][gift[i].getPosition().getX()] == ' ') 
            {
                //print gift in its place
                Screen::setLocation(Location(gift[i].getPosition().getY(), gift[i].getPosition().getX()));
                cout << '$';

                //updates the map vector and put gift in its place
                updateMap(gift[i].getPosition().getX(), gift[i].getPosition().getY(), '$');

                //reset the cursor to the end of the map
                Screen::setLocation(Location(getHeight(), 0));
            }
        }

        for (int i = 0; i < demon.size(); i++)
        {
           //if a demon touched another demon 
            if (getMap()[demon[i].getPosition().getY()][demon[i].getPosition().getX()] == ' ')
            {
                //print demon in its place
                Screen::setLocation(Location(demon[i].getPosition().getY(), demon[i].getPosition().getX()));
                cout << '&';

                //updates the map vector and puts demon in its place
                updateMap(demon[i].getPosition().getX(), demon[i].getPosition().getY(), '&');

                //reset the cursor to the end of the map
                Screen::setLocation(Location(getHeight(), 0));
            }
        }
    } 
}

//function that print the map on the screen
void Board::printScreen()
{
    std::system("cls"); // resets the screen
    int playerPoints = m_pacman.getPoints();

    //print the map
    for (int i = 0; i < map.size(); i++)
    {
        cout << map[i] << endl;
    }

    if (m_giftIsTaken)
        m_super = true;
    else
        m_super = false;

    cout << "\nlevel: " << m_currentLevel + 1;
    cout << "\nHealth: " << getPlayerHealth();
    cout << "\nallPoints: " << m_allPoints + playerPoints;
}

void Board::updateSuperSteps(int x)
{
    m_superSteps = m_superSteps + x;
}

void Board::updateSuperStatus(bool s)
{
    m_pacman.setSuperStatus(s);
}

void Board::updateDemonPos(Vertex position, int index)
{
    demon[index].setPosition(position);
}

Enemy Board::getDemon(int i)
{
    return demon[i];
}

Vertex Board::getInitPlayerPos()
{
    return m_initPlayerPos;
}


void Board::resetPlayerPos()
{
    updateMap(m_pacman.getPosition().getX(), m_pacman.getPosition().getY(), ' ');
    updateMap(m_initPlayerPos.getX(), m_initPlayerPos.getY(), 'a');
    m_pacman.setPosition(m_initPlayerPos);
}

void Board::resetDemonPos()
{
    for (int i = 0; i < demon.size(); i++)
    {
        updateMap(demon[i].getPosition().getX(), demon[i].getPosition().getY(), ' ');
        updateMap(initDemonPos[i].getX(), initDemonPos[i].getY(), '&');
        demon[i].setPosition(initDemonPos[i]);
    }
}



void Board::updatePlayerPoints(int p)
{
    m_pacman.setPoints(p);
}

int Board::getPlayerPoints()
{
    return m_pacman.getPoints();
}

void Board::updatePlayerHealth()
{
    m_playerHealth--;
}

int Board::getPlayerHealth()
{
    return m_playerHealth;
}

char Board::getTile(int x, int y)
{
    return map[y][x];
}

int Board::getNumberOfLevels()
{
    return m_number_of_levels;
}

bool Board::getSuperStatus()
{
    return m_pacman.getSuperStatus();
}

bool Board::getSuperSteps()
{
   return m_superSteps;
}

void Board::printMessage(int _case)
{
        std::system("cls"); // resets the screen
        Screen::setLocation(Location(5, 5));

        //if the player lost
        if (_case == 0)
            cout << "THE DEMON ATE YOU THREE TIMES, YOU LOST!!\n\n\n\n\n\n";
        //if the player finished all the levels
        else
        cout << "CONGRATULATIONS YOU HAVE COMPLETED THE GAME SUCCESSFULLY\n\n\n\n\n\n";

        exit(EXIT_SUCCESS);
        
}

void Board::removeKey(int x, int y)
{
    Vertex pos;
    pos.setX(x);
    pos.setY(y);

    for (int i = 0; i < key.size(); i++) 
    {
        if (key[i].getPosition().sameVertex(pos))
        {
            key.erase(key.begin() + i);
        }
    }
}

void Board::removeCake(int x, int y)
{
    Vertex pos;
    pos.setX(x);
    pos.setY(y);

    for (int i = 0; i < cake.size(); i++) 
    {
        if (cake[i].getPosition().sameVertex(pos))
        {
            cake.erase(cake.begin() + i);
        }
    }
}

void Board::removeGift(int x, int y)
{
    Vertex pos;
    pos.setX(x);
    pos.setY(y);

    for (int i = 0; i < gift.size(); i++)
    {

        if (gift[i].getPosition().sameVertex(pos))
        {
            gift.erase(gift.begin() + i);
        }
    }
}

void Board::removeDemon(int x, int y)
{
    Vertex pos;
    pos.setX(x);
    pos.setY(y);

    for (int i = 0; i < demon.size(); i++) 
    {
        if (demon[i].getPosition().sameVertex(pos))
        {
            demon.erase(demon.begin() + i);
        }
    }
}

void Board::removeDoor(int x, int y)
{
    Vertex pos;
    pos.setX(x);
    pos.setY(y);

    for (int i = 0; i < door.size(); i++) 
    {
        if (door[i].sameVertex(pos))
        {
            door.erase(door.begin() + i);
        }
    }
}

int Board::getCakeSize()
{
    return cake.size();
}

int Board::getDemonSize()
{
    return demon.size();
}

Vertex Board::getDoor(int i)
{
    return door[i];
}

void Board::updateKeys(Vertex position)
{
    key.push_back(position);
}


