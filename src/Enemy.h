//
// Created by m2-bukovics on 14/02/2023.
//

#ifndef SPACEINVADERSSFML_ENEMY_H
#define SPACEINVADERSSFML_ENEMY_H

#include "GameObject.h"

class Enemy: public  GameObject
{
 public:
  Enemy();
  ~Enemy();
  enum Colour {Blue, Green, Pink,Yellow};
  bool initialiseEnSprite(sf::Texture &texture, Colour col);
  bool isVisible() const;
  void setIsVisible(bool isVisible);
  Colour getColour() const;
  void setColour(Colour colour);
  bool move_right = true;
  float counter = 1;


  Vector2 velocity{0.f, 1.f};

 private:

  Colour colour;
  bool is_visible = true;
};

#endif // SPACEINVADERSSFML_ENEMY_H
