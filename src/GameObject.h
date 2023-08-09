
#ifndef SPACEINVADERS_GAMEOBJECT_H
#define SPACEINVADERS_GAMEOBJECT_H
#include <SFML/Graphics.hpp>
#include <string>
#include "Vector2.h"

class GameObject{
 public:
  GameObject();
  ~GameObject();

  bool initialiseSprite(sf::Texture &texture, std::string filename);
  sf::Sprite* getSprite();

  void drawObject(sf::RenderWindow & window);
  Vector2 direction = {0,0};

  float mid_point_x;
  float getMidPointX();
  float getMidPointY();
  float mid_point_y;

  int getSpeed() const;
  void setSpeed(int speed);

  void move_object(const float& dt);
  bool is_collide(const GameObject& sprite1);



 private:

  bool top_collide(const GameObject& sprite1);
  bool left_collide(const GameObject& sprite1);
  bool right_collide(const GameObject& sprite1);
  bool bottom_collide(const GameObject& sprite1);
  int speed = 0;

 protected:
  sf::Sprite* sprite;
};


#endif // SPACEINVADERS_GAMEOBJECT_H
