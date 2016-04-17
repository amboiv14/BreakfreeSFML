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
	//window.setVerticalSyncEnabled(true);

	//Vi kan låse maks frame rate med denne
	//window.setFramerateLimit(60);

	//, sf::Style::Close|sf::Style::Titlebar);

	if (!font.loadFromFile("Fonts/visitor.ttf"))
	{
		isInitSuccessfull = false;
		std::cout << "Could not load score font" << std::endl;
	}

	if (!buf_hit0.loadFromFile("Audio/sfxHit0.wav"),
		!buf_hit1.loadFromFile("Audio/sfxHit1.wav"),
		!buf_hit2.loadFromFile("Audio/sfxHit2.wav"),
		!buf_paddle.loadFromFile("Audio/sfxPaddle.wav"))
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
		std::cout << "You won the game!" << std::endl;
		isPlaying = false;
		gameState = 3;
		return;
	}
	paddle->ResetPaddle();
}

void GameManager::sortScores()
{
	for (int i = 0; i < SCORE_SLOTS; i++)
	{
		for (int j = 0; j < i; j++)
		{
			if (playerScores[i] > playerScores[j])
			{
				int temp = playerScores[i];
				string temp2 = playerNames[i];

				playerScores[i] = playerScores[j];
				playerNames[i] = playerNames[j];

				playerScores[j] = temp;
				playerNames[j] = temp2;
			}	
		}
	}
}

void GameManager::saveScores()
{
	// add player result
	for (int i = 0; i < SCORE_SLOTS; i++)
	{
		if (playerScores[i] == 0)
		{
			playerScores[i] = score;
			playerNames[i] = name;
			break;
		}
	}
	// save to file
	ofstream file("highscores.txt");
	if (file.is_open())
	{
		for (int i = 0; i < SCORE_SLOTS; i++)
		{
			file << playerScores[i];
			file << " " << playerNames[i] << " ";
		}
		file.close();
	}
	else cout << "Unable to open file.\n";
}

void GameManager::loadScores()
{
	// load from file
	string line;
	ifstream file("highscores.txt");
	if (file.is_open())
	{
		int counter = 0;
		while (getline(file, line))
		{
			cout << line << '\n';
		}
		file.close();
	}
	else cout << "Unable to open file.\n";

	// add to local variables
	int i = 0;
	stringstream ssin(line);
	while (ssin.good() && i < 10) {
		ssin >> playerScores[i];
		ssin >> playerNames[i];
		++i;
	}
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

			loadScores();
			sortScores();

			sf::Text scores[10];
			int lineSpacing = 0;
			for (int i = 0; i < SCORE_SLOTS; i++)
			{
				if (playerScores[i] != 0)
				{
					scores[i].setString(std::to_string(playerScores[i]) + "  " + playerNames[i]);
					scores[i].setPosition(460, 336 + lineSpacing);
					scores[i].setFont(font);
					scores[i].setCharacterSize(20);
					lineSpacing += 22;
				}
			}

			while (gameState == 0)
			{
				// events
				sf::Event event;
				while (window.pollEvent(event))
				{
					if (event.type == sf::Event::Closed)
						window.close();
				}

				// mouse hover on buttons
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
					exit.setScale(0.6, 0.6);
					start.setScale(1, 1);
					exit.setPosition(80, 361);
					start.setPosition(112, 304);
					if (mouse.isButtonPressed(mouse.Left))
					{
						gameState = 1;
					}
				}

				inputManager.ExecuteEvents(window);

				// -- draw --
				window.clear();

				window.draw(bg);
				window.draw(start);
				window.draw(exit);

				for (int i = 0; i < SCORE_SLOTS; i++)
				{
					window.draw(scores[i]);
				}

				window.display();
			}
		}
		break;
		case 1: // ingame
		{
			levelManager = new LevelManager;
			paddle = new Paddle(300, 550, 128, 16);

			sf::Music theme;
			if (!theme.openFromFile("Audio/theme.ogg"))
				abort();
			theme.setVolume(80);
			theme.setLoop(true);
			theme.play();

			sf::Sprite bg;
			sf::Texture tex_bg;
			if (!tex_bg.loadFromFile("Textures/bg.png"))
				abort();
			bg.setTexture(tex_bg);

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

					window.draw(bg);
					DrawGUI();
					
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
			// no more time to make game over screen (23:45)
			gameover = true;
			gameState = 3;
			break;
		case 3: // won the game

			sf::Text text("You broke free!", font, 60);
			text.setPosition(120, 60);
			if (gameover)
			{
				text.setString("Game over!");
			}

			sf::Text text2("Enter your name: ", font, 20);
			text2.setPosition(90, 280);

			sf::Text text3("Press space to submit and continue.", font, 10);
			text3.setPosition(90, 305);

			sf::Text text4("Final score: " + std::to_string(score), font, 30);
			text4.setPosition(120, 120);

			string playerName;

			sf::Sprite winbg;
			sf::Texture tex_winbg;
			if (!tex_winbg.loadFromFile("Textures/winbg.png"))
				abort();
			winbg.setTexture(tex_winbg);

			while (gameState == 3)
			{
				// events
				sf::Event event;
				while (window.pollEvent(event))
				{
					if (event.type == sf::Event::KeyPressed)
					{
						if (event.key.code == sf::Keyboard::Space)
						{
							name = playerName;
							saveScores();
							sortScores();
							gameState = 0;
						}
					}
					if (event.type == sf::Event::Closed)
						window.close();
					if (event.type == sf::Event::TextEntered)
					{
						if (event.text.unicode == 8)
						{
							playerName.pop_back();
							text2.setString("Enter your name: " + playerName);
						}
						else
						{
							// ASCII characters only
							if (event.text.unicode < 128)
							{
								playerName += static_cast<char>(event.text.unicode);
								text2.setString("Enter your name: " + playerName);
							}
						}
					}
				}

				// draw
				window.clear();

				window.draw(winbg);

				window.draw(text);
				window.draw(text2);
				window.draw(text3);
				window.draw(text4);

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

void GameManager::GameOver()
{
	gameState = 2;
	std::cout << "Game Over" << std::endl;
}

void GameManager::loseLife()
{
	lives--;
	if (lives <= 0)
	{
		GameOver();
	}
	paddle->ResetPaddle();
}

void GameManager::CheckPaddleCollisions() // TODO: måtte fjerne const for å spille av lyd??
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
		loseLife();
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

					//sideWallPerimeter should be at least as high as the ball's movement speed, but not too high.
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

void GameManager::DrawGUI()
{
	int GUIHeight = 576;
	sf::Text GUILives("Lives x " + std::to_string(lives), font, 20);
	sf::Text GUIScore("Score: " + std::to_string(score), font, 20);
	GUILives.setPosition(655, GUIHeight);
	GUIScore.setPosition(20, GUIHeight);
	window.draw(GUILives);
	window.draw(GUIScore);
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
