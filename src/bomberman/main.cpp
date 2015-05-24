//
// main.cpp for CPP_BOMBERMAN in /home/paasch_j/cpp_bomberman/src/bomberman_src
//
// Made by Johan Paasche
// Login   <paasch_j@epitech.net>
//
// Started on  Mon Apr 27 11:27:27 2015 Johan Paasche
// Last update Sun May 24 05:39:37 2015 Emmanuel Chambon
//

#include	"basics.hh"
#include	"Bomberman.hh"
#include	"UIManager/UIManager.hh"

int	main()
{
  try {
    //UIManager();
    Bomberman();
  } catch (std::exception &e) {
    std::cerr << e.what() << std::endl;
  }
}
