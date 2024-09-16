#include "Controller.h"
#include <conio.h>

Controller::Controller()
{
	m_gameOver = false;
	m_levelFinished = false;
	m_levelNum = 0;
    m_allPoints = 0;
    m_health = 3;
}

void Controller::runGame()
{
    bool exitTheGame = false;
    int button;
  
    while (!m_gameOver) //main loop of the game
    {
        Board theBoard(m_allPoints, m_levelNum, m_health);
        
        theBoard.buildMap(m_levelNum);

        while (exitTheGame == false && m_levelFinished == false) // inside level loop
        {
            button = _getch();
            switch (button)
            {
            case KB_Up:
                move(KB_Up, theBoard);
                break;
            case KB_Down:
                move(KB_Down, theBoard);
                break;
            case KB_Left:
                move(KB_Left, theBoard);
                break;
            case KB_Right:
                move(KB_Right, theBoard);
                break;
            case KB_Space:
                move(KB_Space, theBoard);
                break;
            case KB_Escape:
                exitTheGame = true;
                m_gameOver = true;
                break;
            }
        }

        
        m_levelNum++;
        m_allPoints += theBoard.getDemonSize() * m_points.getEnemyPoints() + m_points.getEndLevelPoints();
        m_levelFinished = false;

        //checks if the levels are over
        if (theBoard.getNumberOfLevels() == m_levelNum)
        {
            theBoard.printMessage(1);
            m_gameOver = true;
        }
    }
    
}

void Controller::move(int direction, Board& theBoard)
{
    int currentX = 0, currentY = 0, newX = 0, newY = 0;
    int doorNum = 0;//for deleting doors starting with the first one which its index is 0
    char nextTile;
    char characterName = ' ';
    bool pacmanMoved = true; //if the pacman moved legaly
    bool pacmanDead = false; //if the pacman touched the demon
    currentX = theBoard.getPlayer().getPosition().getX();
    currentY = theBoard.getPlayer().getPosition().getY();

    newX = currentX;
    newY = currentY;

    switch (direction)
    {
    case KB_Up:
        newY--;
        break;
    case KB_Down:
        newY++;
        break;
    case KB_Left:
        newX--;
        break;
    case KB_Right:
        newX++;
        break;
    case KB_Space:
        pacmanMoved = true;
        break;
    }
    //if the pacman tries to get out of the map limits, then stay in the same place
    if (newX < 0 || newX >= theBoard.getMap()[0].size() || newY < 0 || newY >= theBoard.getMap().size())
    {
        newX = currentX;
        newY = currentY;
        pacmanMoved = false;
    }
    
        nextTile = theBoard.getTile(newX, newY);

        theBoard.updateMap(currentX, currentY, ' ');

        Vertex position = Vertex(newX, newY);

        //if the pacman is superpacman, it eats cakes,gifts, walk through the doors,and not hurt by the demons
        if (theBoard.getSuperStatus())
        {
            characterName = superPacmanChar;

            if (nextTile == wallChar)
            {
                position = Vertex(currentX, currentY);
                pacmanMoved = false;
            }

            else if (nextTile == doorChar)
            {
                theBoard.updateMap(newX, newY, characterName);
            }

            else if (nextTile == cakeChar)
            {
                theBoard.updatePlayerPoints(m_points.getCakePoints());
                m_allPoints += m_points.getCakePoints();
                theBoard.updateMap(newX, newY, characterName);
                theBoard.removeCake(newX, newY);
            }
            else if (nextTile == giftChar)
            {
                theBoard.updatePlayerPoints(m_points.getGiftPoints());
                m_allPoints += m_points.getGiftPoints();
                theBoard.updateMap(newX, newY, characterName);
                theBoard.updateSuperStatus(true);
                theBoard.removeGift(newX, newY);
            }
            else if (nextTile == keyChar)
            {
                theBoard.updatePlayerPoints(m_points.getkeyPoints());
                m_allPoints += m_points.getkeyPoints();
                theBoard.updateMap(newX, newY, characterName);
                theBoard.updateMap(theBoard.getDoor(doorNum).getX(), theBoard.getDoor(doorNum).getY(), ' ');
                theBoard.removeDoor(theBoard.getDoor(doorNum).getX(), theBoard.getDoor(doorNum).getY());
                theBoard.removeKey(position.getX(), position.getY());
                doorNum++;
            }
            else if (nextTile == enemyChar)
            {
                theBoard.updateMap(newX, newY, characterName);
            }

            theBoard.updateSuperSteps(-1);

            if (theBoard.getSuperSteps() <= 0)
            {
                theBoard.updateSuperSteps(20);
                theBoard.updateSuperStatus(false);
            }
            theBoard.updateMap(position.getX(), position.getY(), characterName);
            theBoard.updatePlayerPos(position);
            theBoard.updateScreen(superPacmanChar);
        }
        //if the pacman is not superpacman, it eats cakes,gifts, cant walk through the doors,and hurt by the demons
        else
        {
            characterName = pacmanChar;

            if (nextTile == wallChar || nextTile == doorChar)
            {
                position = Vertex(currentX, currentY);
                pacmanMoved = false;
            }

            else if (nextTile == cakeChar)
            {
                theBoard.updatePlayerPoints(m_points.getCakePoints());
                m_allPoints += m_points.getCakePoints();
                theBoard.updateMap(newX, newY, characterName);
                theBoard.removeCake(newX, newY);
            }
            else if (nextTile == giftChar)
            {
                theBoard.updatePlayerPoints(m_points.getGiftPoints());
                m_allPoints += m_points.getGiftPoints();
                characterName = superPacmanChar;
                theBoard.updateMap(newX, newY, characterName);
                theBoard.updateSuperStatus(true);
                theBoard.removeGift(newX, newY);
            }
            else if (nextTile == keyChar)
            {
                theBoard.updatePlayerPoints(m_points.getkeyPoints());
                m_allPoints += m_points.getkeyPoints();
                theBoard.updateMap(newX, newY, characterName);
                theBoard.updateMap(theBoard.getDoor(doorNum).getX(), theBoard.getDoor(doorNum).getY(), ' ');
                theBoard.removeDoor(theBoard.getDoor(doorNum).getX(), theBoard.getDoor(doorNum).getY());
                theBoard.removeKey(position.getX(), position.getY());
                doorNum++;
            }
            else if (nextTile == enemyChar)
            {
                pacmanDead = true;
            }
            theBoard.updateMap(position.getX(), position.getY(), characterName);
            theBoard.updatePlayerPos(position);
            theBoard.updateScreen(pacmanChar);
        }
        

        if (pacmanMoved)
        {
            //to move the demons
            int currentDemonX = 0, currentDemonY = 0, newDemonX = 0, newDemonY = 0;
            Vertex demonPosition;
            for (int i = 0; i < theBoard.getDemonSize(); i++)
            {
                currentDemonX = theBoard.getDemon(i).getPosition().getX();
                currentDemonY = theBoard.getDemon(i).getPosition().getY();

                newDemonX = currentDemonX;
                newDemonY = currentDemonY;

                int d = rand() % 4;

                switch (d)
                {
                case 0:
                    newDemonY--;
                    break;
                case 1:
                    newDemonY++;
                    break;
                case 2:
                    newDemonX--;
                    break;
                case 3:
                    newDemonX++;
                    break;
                }
                //if the demon tries to go out of the map limits then stay at the same position
                if (newDemonX < 0 || newDemonX >= theBoard.getMap()[0].size() || newDemonY < 0 || newDemonY >= theBoard.getMap().size())
                {
                    newDemonX = currentDemonX;
                    newDemonY = currentDemonY;
                }
                characterName = enemyChar;

                nextTile = theBoard.getTile(newDemonX, newDemonY);

                theBoard.updateMap(currentDemonX, currentDemonY, ' ');

                 demonPosition = Vertex(newDemonX, newDemonY);

                if (nextTile == wallChar || nextTile == doorChar)
                {
                    demonPosition = Vertex(currentDemonX, currentDemonY);
                }

                else if (nextTile == pacmanChar)
                {
                    theBoard.updateMap(newDemonX, newDemonY, enemyChar);
                }
                else if (nextTile == cakeChar)
                {
                    theBoard.updateMap(newDemonX, newDemonY, enemyChar);
                }
                else if (nextTile == giftChar)
                {
                    theBoard.updateMap(newDemonX, newDemonY, enemyChar);
           
                }
                else if (nextTile == keyChar)
                {
                    theBoard.updateMap(newDemonX, newDemonY, enemyChar);
                }
                else if (nextTile == enemyChar)
                {
                    theBoard.updateMap(newDemonX, newDemonY, enemyChar);
                }
                if (newDemonX == newX && newDemonY == newY)
                {
                    pacmanDead = true;
                }

                theBoard.updateDemonPos(demonPosition, i);
                theBoard.updateScreen(enemyChar);
            }
            //if the pacman died, reset the position of the player and demons, decrease the health
            if (pacmanDead)
            {
                
                theBoard.resetPlayerPos();
                theBoard.resetDemonPos();
                theBoard.updatePlayerHealth();
                m_health--;
            }
        }

        theBoard.printScreen();

        //if the pacman ate all the cakes, move to the next level
        if (theBoard.getCakeSize() == 0)
        {
            m_levelFinished = true;
            return;
        }

        //if the players health is 0, then he loses
        if (theBoard.getPlayerHealth() <= 0)
        {
            m_gameOver = true;
            theBoard.printMessage(0);
        }
    
    
}


