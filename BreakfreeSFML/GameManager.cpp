#include "GameManager.h"


GameManager::GameManager()
{
}


GameManager::~GameManager()
{
}

bool GameManager::init()
{
	auto isInitSuccessfull = true;

	window.create(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Breakfree");
	window.setVerticalSyncEnabled(true);

	//Vi kan l�se maks frame rate med denne
	//window.setFramerateLimit(60);

	//, sf::Style::Close|sf::Style::Titlebar);

	if (!font.loadFromFile("Fonts/Nirmala.ttf"))
	{
		isInitSuccessfull = false;
		std::cout << "Could not load score font" << std::endl;
	}

	if (!buf_hit0.loadFromFile("Sounds/sfxHit0.wav"),
		!buf_hit1.loadFromFile("Sounds/sfxHit1.wav"),
		!buf_hit2.loadFromFile("Sounds/sfxHit2.wav"),
		!buf_paddle.loadFromFile("Sounds/sfxPaddle.wav"))
		abort();
	sfxHit0.setBuffer(buf_hit0);
	sfxHit1.setBuffer(buf_hit1);
	sfxHit2.setBuffer(buf_hit2);
	sfxPaddle.setBuffer(buf_paddle);

	return isInitSuccessfull;
}

void GameManager::CheckPaddleOutOfBounds()
{
	if (paddle->x >= SCREEN_WIDTH - paddle->width)
	{
		paddle->x = SCREEN_WIDTH - paddle->width;
	}
	else if (paddle->x <= 0)
	{
		paddle->x = 0;
	}
}

void GameManager::addScore(int bonus)
{
	score += bonus;
}

void GameManager::winLevel()
{
	std::cout << "Cleared level!" << std::endl;
	if (!levelManager->loadNextLevel())
	{
		std::cout << "You won The game!" << std::endl;
		isPlaying = false;
		gameState = 3;
		return;
	}
	paddle->ResetPaddle();
}

void GameManager::runGame()
{
	InputManager inputManager;
	//now = sf::Time::Zero;
	//nextUpdates = sf::seconds(1.f / 60.f);
	//Ball ball;

	while (window.isOpen())
	{
		/*switch (level)
		{
		case 0:
		break;
		}*/

		switch (gameState)
		{
		case 0: // menu
		{
			std::string title = "Breakfree!";
			window.setTitle(title);

			sf::Sprite bg, start, exit;
			sf::Texture tex_bg, tex_start, tex_exit;

			if (!tex_bg.loadFromFile("Textures/screenStart.png"),
				!tex_start.loadFromFile("Textures/start.png"),
				!tex_exit.loadFromFile("Textures/exit.png"))
				abort();

			bg.setTexture(tex_bg);
			start.setTexture(tex_start);
			exit.setTexture(tex_exit);

			start.setPosition(112, 304);
			exit.setPosition(80, 361);
			exit.setScale(0.6, 0.6);

			sf::Mouse mouse;

			//sf::Text text("" + std::to_string(score), font, 10);
			//text.setPosition(660, 220);
			while (gameState == 0)
			{
				// events
				sf::Event event;
				while (window.pollEvent(event))
				{
					if (event.type == sf::Event::Closed)
						window.close();
				}

				//if (now > nextUpdates) // 60 fps updates
				//{
					//now -= nextUpdates;

					if (exit.getGlobalBounds().contains(mouse.getPosition(window).x, mouse.getPosition(window).y))
					{
						exit.setScale(1, 1);
						start.setScale(0.4, 0.4);
						exit.setPosition(80, 341);
						start.setPosition(80, 311);
						if (mouse.isButtonPressed(mouse.Left))
						{
							window.close();
						}
						
					}
					else if (start.getGlobalBounds().contains(mouse.getPosition(window).x, mouse.getPosition(window).y))
					{
						/*if (exit.getScale().x > 0.6)
						{
							exit.scale(-0.05, -0.05);
						}
						if (start.getScale().x < 1)
						{
						start.scale(0.05, 0.05);
						}
						if (exit.getPosition().x > 80)
						{
						exit.move(-0.05, 0);
						}
						if (exit.getPosition().y > 361)
						{
						exit.move(0, -0.05);
						}
						if (start.getPosition().x < 112)
						{
						start.move(0.05, 0);
						}
						if (start.getPosition().y < 304)
						{
						start.move(0, 0.05);
						}*/
						exit.setScale(0.6, 0.6);
						start.setScale(1, 1);
						exit.setPosition(80, 361);
						start.setPosition(112, 304);
						if (mouse.isButtonPressed(mouse.Left))
						{
							gameState = 1;
						}
					}
				//}
				//now += timer.restart();


				inputManager.ExecuteEvents(window);

				// -- draw --
				window.clear();

				window.draw(bg);
				window.draw(start);
				window.draw(exit);

				window.display();
			}
		}
		break;
		case 1: // ingame
		{
			levelManager = new LevelManager;
			paddle = new Paddle(300, 550, 128, 16);

			/*switch (level)
			{
			case 0:
			break;
			}*/

			while (gameState == 1)
			{
				// events
				sf::Event event;
				while (window.pollEvent(event))
				{
					if (event.type == sf::Event::Closed)
						window.close();
				}

				if (!levelManager->LoadLevel(level))
				{
					winLevel();
				}
				while (isPlaying)
				{
					if (levelManager->brickCount <= 0)
					{
						winLevel();
					}
					deltaTime = timer.restart();
					inputManager.ExecuteEvents(window);

					paddle->Update(&deltaTime);
					paddle->ball->Update(&deltaTime);

					// collision checking
					CheckBoardCollisions();
					CheckPaddleCollisions();
					CheckPaddleOutOfBounds();
					CheckBrickCollisions();


					// -- draw --
					window.clear();

					sf::Text text("Score: " + std::to_string(score), font, 20);
					text.setPosition(660, 220);
					window.draw(text);

					levelManager->Draw(window);
					window.draw(paddle->sprite);
					window.draw(paddle->ball->sprite);

					std::string title = "Breakfree!      FPS: " + std::to_string(1.f / deltaTime.asSeconds());
					window.setTitle(title);

					window.display();
				}
			}
		}
		break;
		case 2: // game over
			break;
		case 3: // won the game
			while (gameState == 3)
			{
				// draw
				window.clear();

				sf::Text text("YOU WON THE GAME", font, 40);
				text.setPosition(260, 220);
				window.draw(text);

				window.display();
			}
			break;
		}
	}

	window.close();
}

float GameManager::GetReflection(float hitx) const
{
	// Make sure the hitx variable is within the width of the paddle
	if (hitx < 0) {
		hitx = 0;
	}
	else if (hitx > paddle->width) 
	{
		hitx = paddle->width;
	}

	// Everything to the left of the center of the paddle is reflected to the left
	// while everything right of the center is reflected to the right
	hitx -= paddle->width / 2.0f;

	// Scale the reflection, making it fall in the range -2.0f to 2.0f
	return 2.0f * (hitx / (paddle->width / 2.0f));
}

void GameManager::CheckPaddleCollisions() // TODO: m�tte fjerne const for � spille av lyd??
{
	// Get the center x-coordinate of the ball
	float ballcenterx = paddle->ball->x + paddle->ball->width / 2.0f;

	// Check paddle collision
	if (paddle->ball->Collides(paddle)) 
	{
		paddle->ball->y = paddle->y - paddle->ball->height;
		paddle->ball->SetDirection(GetReflection(ballcenterx - paddle->x), -1);
		sfxPaddle.play();
		//ball->SetDirection(0, -1);
	}
}

void GameManager::CheckBoardCollisions()
{
	// Top and bottom collisions
	if (paddle->ball->y < 0.f) {
		// Top
		// Keep the ball within the board and reflect the y-direction
		paddle->ball->y = 0.f;
		paddle->ball->direction.y = 1;
		sfxHit0.play();
	}
	else if (paddle->ball->y + paddle->ball->height > SCREEN_HEIGHT) {
		// Bottom

		// Ball lost
		paddle->ResetPaddle();
		// TODO: deep sound nedtur sfx
	}

	// Left and right collisions
	if (paddle->ball->x <= 0.f) {
		// Left
		// Keep the ball within the board and reflect the x-direction
		paddle->ball->x = 0.f;
		paddle->ball->direction.x = 1;
		sfxHit0.play();
	}
	else if (paddle->ball->x + paddle->ball->width >= SCREEN_WIDTH) {
		// Right
		// Keep the ball within the board and reflect the x-direction
		paddle->ball->x = SCREEN_WIDTH - paddle->ball->width;
		paddle->ball->direction.x = -1;
		sfxHit0.play();
	}
}

void GameManager::CheckBrickCollisions() 
{
	int currentLevel = levelManager->currentLevel;
	for (int i = 0; i < levelManager->getNum(); i++)
	{
		//std::cout << i;
		if (levelManager->getLevelData(currentLevel, i) != 0 && levelManager->Bricks[i].isActive) 
		{
			float vicinityX = (levelManager->Bricks[i].width / 2) + (paddle->ball->width / 2);
			float vicinityY = (levelManager->Bricks[i].height / 2) + (paddle->ball->height / 2);
			// Find position of center of brick
			float brickCenterX = levelManager->Bricks[i].x + (levelManager->Bricks[i].width / 2);
			float brickCenterY = levelManager->Bricks[i].y + (levelManager->Bricks[i].height / 2);

			// find position of center of ball
			float ballCenterX = paddle->ball->x + (paddle->ball->width / 2);
			float ballCenterY = paddle->ball->y + (paddle->ball->height / 2);

			//TODO:
			if (ballCenterY <= brickCenterY + vicinityY && ballCenterY >= brickCenterY - vicinityY)
			{
				if (ballCenterX <= brickCenterX + vicinityX && ballCenterX >= brickCenterX - vicinityX)
				{
					//Destroy and add brickScore to total score
					if (levelManager->destroyBrick(i))
					{
						addScore(levelManager->Bricks[i].getScore());
						std::cout << "newScore: " << score << std::endl;
						sfxHit1.play();
					}
					else
					{
						sfxHit2.play();
					}

					//Tror denne burde v�re minst like stor som ballens movement speed, men ikke FOR stor
					float sideWallPerimeter = 5.f;
					if (ballCenterX + vicinityX <= brickCenterX + sideWallPerimeter)
					{
						std::cout << "hit left side!" << std::endl;
						paddle->ball->x = levelManager->Bricks[i].x - paddle->ball->width - 1;
						paddle->ball->direction.x = -1;
					}
					else if (ballCenterX - vicinityX >= brickCenterX - sideWallPerimeter)
					{
						std::cout << "hit right side!" << std::endl;
						paddle->ball->x = levelManager->Bricks[i].x + levelManager->Bricks[i].width + 1;
						paddle->ball->direction.x = 1;
					}
					else
					{
						if (ballCenterY >= brickCenterY)
						{
							std::cout << "hit bottom side!" << std::endl;
							paddle->ball->y += 1;
							paddle->ball->direction.y = 1;
						}
						else
						{
							std::cout << "hit top side!" << std::endl;
							paddle->ball->y -= 1;
							paddle->ball->direction.y = -1;
						}
					}
				}
			}	
		}
	}
}

int main()
{
	GameManager* gameManager = new GameManager;

	if (gameManager->init())
	{
		gameManager->runGame();
	}


	delete gameManager;

	return 0;
}