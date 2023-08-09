//
// Created by m2-bukovics on 21/02/2023.
//

#ifndef SPACEINVADERSSFML_LASER_H
#define SPACEINVADERSSFML_LASER_H

#include "GameObject.h"

class Laser : public GameObject
{
 public:
  Laser();
  ~Laser();

  bool initialiseEnSprite(sf::Texture &texture);
  bool isVisible() const;
  void setIsVisible(bool isVisible);

 private:
  bool is_visible = true;
};

#endif // SPACEINVADERSSFML_LASER_H
