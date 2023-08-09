
#ifndef SPACEINVADERS_GAME_H
#define SPACEINVADERS_GAME_H

#include <SFML/Graphics.hpp>
#include "Vector2.h"
#include "GameObject.h"
#include "Enemy.h"
#include "Laser.h"
class Game
{
 public:
  Game(sf::RenderWindow& window);
  ~Game();
  bool init();
  void update(float dt);
  void render();
  void mouseClicked(sf::Event event);
  void keyPressed(sf::Event event);
  void keyReleased(sf::Event event);

  enum GameStates
  {
    MENU = 1,
    PLAY_GAME = 2,
    GAME_OVER = 3,
    WIN_GAME = 4,
    PAUSE_GAME = 5
  };
  GameStates game_state;

 private:
  sf::RenderWindow& window;

  void setSpaceship();
  GameObject space_ship;
  sf::Texture space_ship_texture;

  GameObject background;
  sf::Texture background_texture;

  void menuSetText();
  sf::Font tittle_font;
  sf::Font font;
  void sateTexts();
  sf::Text normal_mode_t;
  sf::Text gravity_mode_t;
  sf::Text quadratic_mode_t;
  sf::Text curve_mode_t;
  bool normal_mode;
  bool gravity_mode;
  bool quadratic_mode;
  bool curve_mode;
  int menu_position = 1;

  sf::Text menu_text;
  sf::Text start_text;

  sf::Text score_text;
  void scoreSetText();
  int score;

  void resetPosition();

  void setAliens();
  int column_size = 13;
  int grid_size = 4;
  Enemy aliens[70];
  int number_of_aliens;
  int aliens_escaped = 0;
  void alienMovement(const float& dt);
  bool go_down =false;
  float gravity = 30.f;
  float  time_elapsed;

  void loadTexturesAliens();
  sf::Texture beige_alien_texture;
  sf::Texture blue_alien_texture;
  sf::Texture green_alien_texture;
  sf::Texture pink_alien_texture;
  sf::Texture yellow_alien_texture;

  void setLaser();
  sf::Texture laser_texture;
  Laser lasers[20];
  int no_of_lasers = 20;
  void shootLaser(const float& dt);
  sf::Clock clock;
  const float shots_per_second = 8.0f;
  const float shot_delay = 1.0f / shots_per_second;
  bool  shooting = false;

  bool outOffScreen(GameObject& sprite);

  void loadFonts();
  void alienGravityMovement(const float& dt);
  void alienQaudMovement(const float& dt);
  void alienCurveMovement(const float& dt);
};

#endif // SPACEINVADERS_GAME_H
