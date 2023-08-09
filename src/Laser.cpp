//
// Created by m2-bukovics on 21/02/2023.
//

#include "Laser.h"
Laser::Laser() {}
Laser::~Laser() {}

bool Laser::initialiseEnSprite( sf::Texture& texture)
{
  sprite->setTexture(texture);
  return true;
}

bool Laser::isVisible() const
{
  return is_visible;
}
void Laser::setIsVisible(bool isVisible)
{
  is_visible = isVisible;
}


