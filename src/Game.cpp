
#include "Game.h"
#include <iostream>
#include <cmath>

bool Game::outOffScreen(GameObject& sprite)
{
  if (
    (sprite.getSprite()->getPosition().x +
       sprite.getSprite()->getGlobalBounds().width <=
     0) ||
    (sprite.getSprite()->getPosition().y +
       sprite.getSprite()->getGlobalBounds().height <=
     0) ||
    (sprite.getSprite()->getPosition().y >= window.getSize().y) ||
    (sprite.getSprite()->getPosition().x >= window.getSize().x))
  {
    return true;
  }
  else
    return  false;
}

void Game::setSpaceship()
{
  space_ship.initialiseSprite(space_ship_texture,"Data/Images/SpaceShooterRedux/PNG/playerShip3_blue.png");
  space_ship.getSprite()->setPosition(window.getSize().x / 2 - space_ship.getSprite()->getGlobalBounds().width / 2, window.getSize().y * 0.85);
  space_ship.getSprite()->setScale(0.7, 0.7);
  space_ship.setSpeed(200);
}

void Game::loadTexturesAliens()
{
  if ((!blue_alien_texture.loadFromFile("Data/Images/Alien UFO pack/PNG/shipBlue_manned.png")) ||
        (!green_alien_texture.loadFromFile("Data/Images/Alien UFO pack/PNG/shipGreen_manned.png")) ||
          (!pink_alien_texture.loadFromFile("Data/Images/Alien UFO pack/PNG/shipPink_manned.png")) ||
            (!yellow_alien_texture.loadFromFile("Data/Images/Alien UFO pack/PNG/shipYellow_manned.png")))
  {
    std::cout << "Error\n";
  }
}

void Game::setAliens()
{
  for (int i = 0; i < column_size; i++)
  {
    for (int j = 0; j < grid_size; j++)
    {
     if (j == 1)
      {
        aliens[i * grid_size + j].initialiseEnSprite(
          blue_alien_texture, Enemy::Blue);
      }
      else if (j == 2)
      {
        aliens[i * grid_size + j].initialiseEnSprite(
          yellow_alien_texture, Enemy::Yellow);
      }
      else if (j == 3)
      {
        aliens[i * grid_size + j].initialiseEnSprite(
          pink_alien_texture, Enemy::Pink);
      }
      else
      {
        aliens[i * grid_size + j].initialiseEnSprite(
          green_alien_texture, Enemy::Green);
      }
      aliens[i * grid_size + j].getSprite()->setPosition(
        20 + 70 * i, 70 + 70 * j);
      aliens[i * grid_size + j].getSprite()->setScale(0.5, 0.5);
      aliens[i * grid_size + j].direction.x = 1;
      aliens[i * grid_size + j].direction.y = 0;
      aliens[i * grid_size + j].direction.normalise();
      aliens[i * grid_size + j].setSpeed(100);
      aliens[i * grid_size + j].setIsVisible(true);
      aliens[i * grid_size + j].velocity.y = 1.f;
      number_of_aliens = column_size * grid_size;
      aliens[i * grid_size + j].move_right = true;
      aliens[i * grid_size + j].counter = 1;

    }
  }
}

void Game::setLaser()
{
  if (!laser_texture.loadFromFile("Data/Images/SpaceShooterRedux/PNG/Lasers/laserRed16.png"))
  {
    std::cout << "Error\n";
  }
  for (int i = 0; i < no_of_lasers; i++)
  {
    lasers[i].initialiseEnSprite(laser_texture);
    lasers[i].setIsVisible(false);
    lasers[i].direction.x = 0;
    lasers[i].direction.y = -10;
    lasers[i].setSpeed(0);
  }
}

void Game::shootLaser(const float& dt)
{
  static bool laserShot = false;
  static float now = 0.0f;
  now += dt;
  for (int i = 0; i < no_of_lasers; i++)
    if (outOffScreen(lasers[i]))
    {
      lasers[i].setIsVisible(false);
    }
  if (now >= shot_delay)
  {
    for (int i = 0; i < no_of_lasers; i++)
    {
      if (!laserShot)
      {
        if (shooting && !lasers[i].isVisible())
        {
          lasers[i].setIsVisible(true);
          lasers[i].setSpeed(200);
          lasers[i].getSprite()->setPosition(
            space_ship.getMidPointX() - lasers[i].getSprite()->getGlobalBounds().width / 2, space_ship.getSprite()->getPosition().y);
          laserShot = true;
          now       = 0;
          if (i == no_of_lasers)
          {
            i = 0;
          }
          break;
        }
      }
      else
      {
        laserShot = false;
      }
    }
  }
}

void Game::loadFonts()
{
  if (!tittle_font.loadFromFile("Data/Fonts/open-sans/OpenSans-ExtraBold.ttf") ||
      (!font.loadFromFile("Data/Fonts/OpenSans-Bold.ttf")))
  {
    std::cout << "font did not load";
  }
}

void Game::menuSetText()
{
  menu_text.setFont(tittle_font);
  menu_text.setCharacterSize(100);
  menu_text.setFillColor(sf::Color(48, 108, 203));

  start_text.setFont(font);
  start_text.setCharacterSize(60);
  start_text.setFillColor(sf::Color(240, 102, 84));

  normal_mode_t.setString("Normal Mode");
  normal_mode_t.setFont(tittle_font);
  normal_mode_t.setCharacterSize(40);
  normal_mode_t.setFillColor(sf::Color::Red);
  normal_mode_t.setPosition(
    window.getSize().x / 2 - normal_mode_t.getGlobalBounds().width / 2.,
    window.getSize().y * 0.55 - normal_mode_t.getGlobalBounds().height / 2);

  gravity_mode_t.setString("Gravity Mode");
  gravity_mode_t.setFont(tittle_font);
  gravity_mode_t.setCharacterSize(40);
  gravity_mode_t.setFillColor(sf::Color::White);
  gravity_mode_t.setPosition(
    window.getSize().x / 2 - gravity_mode_t.getGlobalBounds().width / 2.,
    window.getSize().y * 0.65 - gravity_mode_t.getGlobalBounds().height / 2);

  quadratic_mode_t.setString("Quadratic Mode");
  quadratic_mode_t.setFont(tittle_font);
  quadratic_mode_t.setCharacterSize(40);
  quadratic_mode_t.setFillColor(sf::Color::White);
  quadratic_mode_t.setPosition(
    window.getSize().x / 2 - quadratic_mode_t.getGlobalBounds().width / 2.,
    window.getSize().y * 0.75 - quadratic_mode_t.getGlobalBounds().height / 2);

  curve_mode_t.setString("Curve Mode");
  curve_mode_t.setFont(tittle_font);
  curve_mode_t.setCharacterSize(40);
  curve_mode_t.setFillColor(sf::Color::White);
  curve_mode_t.setPosition(
    window.getSize().x / 2 - curve_mode_t.getGlobalBounds().width / 2.,
    window.getSize().y * 0.85 - curve_mode_t.getGlobalBounds().height / 2);

  menu_position = 1;
}

void Game::sateTexts()
{
  if (game_state == GameStates::MENU)
  {
    menu_text.setString("SPACE INVADERS");
    start_text.setString("Press enter to start");
  }
  if (game_state == GameStates::GAME_OVER)
  {
    start_text.setString("Press Enter to go back to Menu");
    menu_text.setString("GAME OVER");
  }
  if (game_state == GameStates::WIN_GAME)
  {
    start_text.setString("Press Enter to go back to Menu");
    menu_text.setString("YOU WON");
  }
  if (game_state == GameStates::PAUSE_GAME)
  {
    start_text.setString("Press Enter to continue");
    menu_text.setString("PAUSE");
  }
  start_text.setPosition(
    window.getSize().x / 2 - start_text.getGlobalBounds().width / 2.,
    window.getSize().y * 0.4 - start_text.getGlobalBounds().height / 2);

  menu_text.setPosition(
    window.getSize().x / 2 - menu_text.getGlobalBounds().width / 2.,
    window.getSize().y / 4 - menu_text.getGlobalBounds().height / 2);

};

void Game::scoreSetText()
{
  score_text.setString("0");
  score_text.setFont(font);
  score_text.setCharacterSize(45);score_text.setPosition( window.getSize().x - score_text.getGlobalBounds().width - 30, 10);
  score_text.setFillColor(sf::Color::White);
  score = 0;
}

void Game::resetPosition()
  {
    setSpaceship();
    setAliens();
    setLaser();
    scoreSetText();
    menuSetText();
  };

  void Game:: alienMovement(const float& dt)
  {
    static float now = 0.0f;

    for (int i = 0; i < number_of_aliens; i++)
    {
      aliens[i].move_object(dt);
    }
    if(!go_down)
    {
      for (int j = 0; j < number_of_aliens; j++)
      {
        if (aliens[j].isVisible() &&(aliens[j].getSprite()->getPosition().x <= 0 ||
             aliens[j].getSprite()->getPosition().x +
                 aliens[j].getSprite()->getGlobalBounds().width >=
               window.getSize().x))
        {
          go_down = true;
          for (int i = 0; i < number_of_aliens; i++)
          {
            if (aliens[j].getSprite()->getPosition().x <= 0)
            {
              aliens[i].direction.x = 1;
            }
            else
            {
              aliens[i].direction.x = -1;
            }
            aliens[i].direction.y = 1;
          }
        }
      }
    }
    if(go_down){
      now += dt;
    }
    if( now > 0.5f){
      for (int i = 0; i < number_of_aliens; i++)
      {
        aliens[i].direction.y = 0;
        now                   = 0;
        go_down = false;
      }
    }
  };
  void Game::alienGravityMovement(const float& dt)
  {
    time_elapsed = dt;
    for (int i = 0; i < number_of_aliens; i++)
    {
      aliens[i].getSprite()->move(
        aliens[i].getSpeed() * aliens[i].direction.x * time_elapsed,
        (aliens[i].velocity.y * time_elapsed));
    }
    for (int j = 0; j < number_of_aliens; j++)
    {
      if ((aliens[j].isVisible() &&
           (aliens[j].getSprite()->getPosition().x <= 0 ||
            aliens[j].getSprite()->getPosition().x +
                aliens[j].getSprite()->getGlobalBounds().width >=
              window.getSize().x)))
      {
        for (int i = 0; i < number_of_aliens; i++)
        {
          if (aliens[j].getSprite()->getPosition().x <= 0)
          {
            aliens[i].direction.x = 2;
          }
          else
          {
            aliens[i].direction.x = -2;
          }
        }
      }
      aliens[j].velocity.y += gravity * time_elapsed;
    }
  }
  void Game::alienQaudMovement(const float& dt)
  {
    for (int i = 0; i < column_size; i++)
    {
      for (int j = 0; j < grid_size; j++)
      {
        float x;
        float y;
        if (aliens[i * grid_size + j].move_right)
        {
          x = aliens[i * grid_size + j].getSprite()->getPosition().x + 1;
        }

        else
        {
          x = aliens[i * grid_size + j].getSprite()->getPosition().x - 1;
        }
        y =
          -pow(
            (x -
             (window.getSize().x -
              aliens[i * grid_size + j].getSprite()->getGlobalBounds().width) /
               2),
            2) /
            window.getSize().x / 2 +
          100 + 70 * j + aliens[i * grid_size + j].counter * 50;
        aliens[i * grid_size + j].getSprite()->setPosition(x, y);
        if (
          (x +
           aliens[i * grid_size + j].getSprite()->getGlobalBounds().width) >=
          window.getSize().x)
        {
          aliens[i * grid_size + j].counter++;
          aliens[i * grid_size + j].move_right = false;
        }
        if (x <= 0)
        {
          aliens[i * grid_size + j].counter++;
          aliens[i * grid_size + j].move_right = true;
        }
      }
    }
  }

  void Game::alienCurveMovement(const float& dt)
  {
    for (int i = 0; i < column_size; i++)
    {
      for (int j = 0; j < grid_size; j++)
      {
        float x;
        float y;
        if (aliens[i * grid_size + j].move_right)
        {
          x = aliens[i * grid_size + j].getSprite()->getPosition().x + 1;
        }

        else
        {
          x = aliens[i * grid_size + j].getSprite()->getPosition().x - 1;
        }
        y = 40 * sin(0.015 * x)+
             70 * j + aliens[i * grid_size + j].counter * 70;
        aliens[i * grid_size + j].getSprite()->setPosition(x, y);

        if (x >=window.getSize().x)
        {
          aliens[i * grid_size + j].counter++;
          aliens[i * grid_size + j].move_right = false;
        }
        if (x + aliens[i * grid_size + j].getSprite()->getGlobalBounds().width <= 0)
        {
          aliens[i * grid_size + j].counter++;
          aliens[i * grid_size + j].move_right = true;
        }
      }
    }
  }

Game::Game(sf::RenderWindow& game_window)
  : window(game_window)
{
  srand(time(NULL));
}

Game::~Game()
{

}

bool Game::init()
{
  loadFonts();
  loadTexturesAliens();
  resetPosition();
  background.initialiseSprite(background_texture,"Data/Images/star-sky.png");
  game_state = GameStates::MENU;
  return true;
}

void Game::update(float dt)
{
  if (game_state == GameStates::PLAY_GAME)
  {
    space_ship.move_object(dt);
    shootLaser(dt);
    for (int i = 0; i < no_of_lasers; i++)
    {
      if (lasers[i].isVisible())
      {
        lasers[i].move_object(dt);
      }
    }
    if (normal_mode)
    {
      alienMovement(dt);
    }
    else if (gravity_mode)
    {
      alienGravityMovement(dt);
    }
    else if (quadratic_mode)
    {
      alienQaudMovement(dt);
    }
    else
    {
      alienCurveMovement(dt);
    }
    for (int i = 0; i < number_of_aliens; i++)
    {
      for (int j = 0; j < no_of_lasers; j++)
      {
        if (
          aliens[i].is_collide(lasers[j]) && aliens[i].isVisible() &&
          lasers[j].isVisible())
        {
          aliens[i].setIsVisible(false);
          lasers[j].setIsVisible(false);
          score++;
        }
      if (aliens[i].is_collide(space_ship) && aliens[i].isVisible())
      {
        game_state = GameStates::GAME_OVER;
      }
      else if (aliens[i].isVisible() && (aliens[i].getSprite()->getPosition().y >= window.getSize().y))
      {
        aliens_escaped++;
        aliens[i].setIsVisible(false);
        std::cout << aliens_escaped + score << "\n";
        std::cout << number_of_aliens << "\n";
      }
      else if (
          (aliens_escaped + score >= number_of_aliens) ||
          (score == number_of_aliens))
        {
          game_state = GameStates::WIN_GAME;
        }
      }
    }
  }
}

void Game::render()
{
  sateTexts();
  background.drawObject(window);
  if (game_state == GameStates::MENU)
  {
    window.draw(menu_text);
    window.draw(start_text);
    window.draw(normal_mode_t);
    window.draw(gravity_mode_t);
    window.draw(quadratic_mode_t);
    window.draw(curve_mode_t);

  }
  if (game_state == GameStates::PLAY_GAME)
  {
    score_text.setPosition(
      window.getSize().x - score_text.getGlobalBounds().width - 30, 10);
    score_text.setString(std::to_string(score));
    window.draw(score_text);
    space_ship.drawObject(window);
    for (int i = 0; i < number_of_aliens; i++)
    {
      if (aliens[i].isVisible())
      {
        aliens[i].drawObject(window);
      }
    }
    for (int i = 0; i < no_of_lasers; i++)
    {
      if (lasers[i].isVisible())
      {
        lasers[i].drawObject(window);
      }
    }
  }
    if (game_state == GameStates::GAME_OVER || game_state == GameStates::WIN_GAME || game_state == GameStates::PAUSE_GAME)
    {
      window.draw(menu_text);
      window.draw(start_text);
      window.draw(score_text);
    }
  }


void Game::mouseClicked(sf::Event event)
{
  //get the click position
  sf::Vector2i click = sf::Mouse::getPosition(window);
}


void Game::keyPressed(sf::Event event)
{
  if (game_state == GameStates::MENU)
  {
    if ((event.key.code == sf::Keyboard::Down || event.key.code == sf::Keyboard::S) && event.type == sf::Event::KeyPressed)
    {
      if(menu_position < 4)
      {
        ++menu_position;
      }
    }
    else if (
      (event.key.code == sf::Keyboard::Up || event.key.code == sf::Keyboard::W) &&
      event.type == sf::Event::KeyPressed)
    {
      if (menu_position > 1)
        --menu_position;
    }
    if (menu_position == 1)
    {
      normal_mode_t.setFillColor(sf::Color::Red);
      gravity_mode_t.setFillColor(sf::Color::White);
      quadratic_mode_t.setFillColor(sf::Color::White);
      curve_mode_t.setFillColor(sf::Color::White);
    }
    else if (menu_position == 2)
    {
      normal_mode_t.setFillColor(sf::Color::White);
      gravity_mode_t.setFillColor(sf::Color::Red);
      quadratic_mode_t.setFillColor(sf::Color::White);
      curve_mode_t.setFillColor(sf::Color::White);
    }
    else if (menu_position == 3)
    {
      normal_mode_t.setFillColor(sf::Color::White);
      gravity_mode_t.setFillColor(sf::Color::White);
      quadratic_mode_t.setFillColor(sf::Color::Red);
      curve_mode_t.setFillColor(sf::Color::White);
    }
    else
    {
      normal_mode_t.setFillColor(sf::Color::White);
      gravity_mode_t.setFillColor(sf::Color::White);
      quadratic_mode_t.setFillColor(sf::Color::White);
      curve_mode_t.setFillColor(sf::Color::Red);
    }

      if (
        (event.key.code == sf::Keyboard::Enter &&
         event.type == sf::Event::KeyPressed))
      {
        if(menu_position == 1)
        {
          normal_mode = true;
          gravity_mode = false;
          quadratic_mode = false;
        }
        else if(menu_position == 2)
        {
          normal_mode = false;
          gravity_mode = true;
          quadratic_mode = false;
        }
        else if(menu_position == 3)
        {
          normal_mode = false;
          gravity_mode = false;
          quadratic_mode = true;
        }
        else
        {
          normal_mode = false;
          gravity_mode = false;
          quadratic_mode = false;
        }
        game_state = GameStates::PLAY_GAME;
      }
      else if (
        event.key.code == sf::Keyboard::Escape)
      {
        window.close();
      }
  }
  if (game_state == GameStates::PAUSE_GAME)
  {
    if (event.key.code == sf::Keyboard::Enter)
    {
      game_state = GameStates::PLAY_GAME;

    }
    else if (
      event.key.code == sf::Keyboard::Escape)
    {
      resetPosition();
      game_state = GameStates::MENU;
    }
    }
    if (game_state == GameStates::GAME_OVER || game_state == GameStates::WIN_GAME)
    {
      if (event.key.code == sf::Keyboard::Enter)
      {
        resetPosition();
        game_state = GameStates::MENU;
      }
      else if (
        event.key.code == sf::Keyboard::Escape)
      {
        window.close();
      }
    }
  if (game_state == GameStates::PLAY_GAME)
  {
    if (event.key.code == sf::Keyboard::A)
    {
      if ( space_ship.getSprite()->getPosition().x > 0 )
      {
        space_ship.direction.x = -1;
      }
      else
      {
        space_ship.direction.x = 0;
      }
    }
    else if (event.key.code == sf::Keyboard::D)
    {
      if ( space_ship.getSprite()->getPosition().x + space_ship.getSprite()->getGlobalBounds().width < window.getSize().x )
      {
        space_ship.direction.x = 1;
      }
      else
      {
        space_ship.direction.x = 0;
      }
    }
    else if (event.key.code == sf::Keyboard::Space &&
             event.type == sf::Event::KeyPressed)
    {
      shooting = true;
    }

    if (event.key.code == sf::Keyboard::Escape &&
        event.type == sf::Event::KeyPressed)
    {
      game_state = GameStates::PAUSE_GAME;
    }
  }
}
void  Game::keyReleased(sf::Event event)
{
  if ((event.key.code == sf::Keyboard::D || event.key.code == sf::Keyboard::A) && event.type == sf::Event::KeyReleased)
  {
    space_ship.direction.x = 0;
  }
  else if (event.key.code == sf::Keyboard::Space && event.type == sf::Event::KeyReleased)

  {
    shooting = false;
  }
}


