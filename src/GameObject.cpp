

#include "GameObject.h"
#include <iostream>

GameObject::GameObject()
  : sprite(nullptr)
    {
      sprite = new sf::Sprite();
    };


GameObject::~GameObject()
{
  delete sprite;
};


bool GameObject::initialiseSprite(sf::Texture &texture, std::string filename)
{
  if (!texture.loadFromFile(filename))
  {
    std::cout << "Error\n";
    return false;
  }
  sprite->setTexture(texture);
  return true;
}


void GameObject::drawObject(sf::RenderWindow& window)
{
  window.draw(*sprite);
}

sf::Sprite* GameObject::getSprite()
{
  return sprite;
}


void GameObject::move_object(const float& dt)
{
  sprite->move(speed * direction.x * dt, speed * direction.y * dt);
}


bool GameObject::is_collide(const GameObject& sprite1)
{
  if (top_collide(sprite1) && bottom_collide(sprite1) && right_collide(sprite1) && left_collide(sprite1))
  {
    return true;
  }
  else
    return false;
}


bool GameObject::top_collide(const GameObject& sprite1)
{
  if (sprite->getPosition().y <= sprite1.sprite->getPosition().y + sprite1.sprite->getGlobalBounds().height)
  {
    return true;
  }
  else
    return false;
}


bool GameObject::bottom_collide(const GameObject& sprite1)
{
  if (sprite->getPosition().y + sprite->getGlobalBounds().height >= sprite1.sprite->getPosition().y)
  {
    return true;
  }
  else
    return false;
}


bool GameObject::left_collide(const GameObject& sprite1)
{
  if (sprite->getPosition().x <= sprite1.sprite->getPosition().x + sprite1.sprite->getGlobalBounds().width)

  {
    return true;
  }
  else
    return false;
}


bool GameObject::right_collide(const GameObject& sprite1)
{
  if (sprite->getPosition().x + sprite->getGlobalBounds().width >= sprite1.sprite->getPosition().x)
  {
    return true;
  }
  else
    return false;
}


float GameObject::getMidPointX()
{
  mid_point_x = sprite->getPosition().x + sprite->getGlobalBounds().width / 2;
  return mid_point_x;
}


float GameObject::getMidPointY()
{
  mid_point_y = sprite->getPosition().y + sprite->getGlobalBounds().height / 2;
  return mid_point_y;
}


int GameObject::getSpeed() const
{
  return speed;
}


void GameObject::setSpeed(int speed)
{
  GameObject::speed = speed;
}
