//
// Created by m2-bukovics on 14/02/2023.
//

#include "Enemy.h"
Enemy::Enemy()
{

}

Enemy::~Enemy() {};

bool Enemy::initialiseEnSprite( sf::Texture& texture, Enemy::Colour col)
{

  colour = col;
  sprite->setTexture(texture);
  return true;

}

bool Enemy::isVisible() const
{
  return is_visible;
}
void Enemy::setIsVisible(bool isVisible)
{
  is_visible = isVisible;
}
Enemy::Colour Enemy::getColour() const
{
  return colour;
}
void Enemy::setColour(Enemy::Colour colour)
{
  Enemy::colour = colour;
}