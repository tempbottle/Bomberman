//
// Player.cpp for Bomberman in /home/tran_0/rendu/cpp_bomberman/include
// 
// Made by David Tran
// Login   <tran_0@epitech.net>
// 
// Started on  Sun May  3 01:33:50 2015 David Tran
// Last update Sun May  3 11:46:09 2015 David Tran
//

#include "Player.hh"

Player::Player(char Speed, bool alive, char Range) : speed(Speed), isAlive(alive), range(Range)
{
  Bomb	*newone = new Bomb;

  bombs.push_back(newone);
}

Player::~Player()
{}

//
// Alive Functions
//
bool	Player::is_Alive() const
{
  return (isAlive);
}

void	Player::triggerAlive()
{
  (isAlive) ? isAlive = false : isAlive = true;
}

//
// Bomb Functions
//
void		Player::addBomb()
{
  Bomb		*newone = new Bomb;

  bombs.push_back(newone);
}

std::vector<Bomb *>		Player::getBombs() const
{
  return (bombs);
}

std::vector<Bomb*>::const_iterator	Player::getBombIt() const
{
  return (bombs.begin());
}

bool	Player::triggerOneBomb()
{
  std::vector<Bomb *>::const_iterator	it = bombs.begin();

  while (it != bomb.end())
    {
      if ((*it).isLaunched() == false)
	{
	  (*it).triggerLaunch();
	  return (true);
	}
      it++;
    }
  return (false);
}

//
// PowerUp Functions
//
char	Player::getRange() const
{
  return (range);
}

void	Player::setRange(char const &Range)
{
  range = Range;
}

char	Player::getSpeed() const
{
  return (speed);
}

void	Player::setSpeed(char const &Speed)
{
  speed = Speed;
}
