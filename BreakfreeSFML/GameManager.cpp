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

	//Vi kan låse maks frame rate med denne
	//window.setFramerateLimit(60);

	//, sf::Style::Close|sf::Style::Titlebar);

	if (!font.loadFromFile("Fonts/Nirmala.ttf"))
	{
		isInitSuccessfull = false;
		std::cout << "Could not load score font" << std::endl;
	}
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

void GameManager::runGame()
{
	levelManager = new LevelManager;
	InputManager inputManager;
	paddle = new Paddle(300, 550, 128, 16);
	//Ball ball;

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		switch (level)
		{
		case 0:
			break;
		}
		levelManager->LoadLevel(level);

		while (isPlaying)
		{
			deltaTime = timer.restart();
			inputManager.ExecuteEvents(window);

			paddle->Update(&deltaTime);
			paddle->ball->Update(&deltaTime);

			//Collision Checking
			CheckBoardCollisions();
			CheckPaddleCollisions();
			CheckPaddleOutOfBounds();
			CheckBrickCollisions();


			window.clear(); // ------draw graphics here-------

			sf::Text text("Score: " + std::to_string(score), font, 20);
			text.setPosition(660, 220);
			window.draw(text);

			levelManager->Draw(window);
			window.draw(paddle->sprite);
			window.draw(paddle->ball->sprite);

			std::string title = "Breakfree!      FPS: " + std::to_string(1.f / deltaTime.asSeconds());
			window.setTitle(title);

			window.display(); // -----------------------
		}
	}
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

void GameManager::CheckPaddleCollisions() const
{
	// Get the center x-coordinate of the ball
	float ballcenterx = paddle->ball->x + paddle->ball->width / 2.0f;

	// Check paddle collision
	if (paddle->ball->Collides(paddle)) 
	{
		paddle->ball->y = paddle->y - paddle->ball->height;
		paddle->ball->SetDirection(GetReflection(ballcenterx - paddle->x), -1);
		
		//ball->SetDirection(0, -1);
	}
}

void GameManager::CheckBoardCollisions() const
{
	// Top and bottom collisions
	if (paddle->ball->y < 0.f) {
		// Top
		// Keep the ball within the board and reflect the y-direction
		paddle->ball->y = 0.f;
		paddle->ball->direction.y = 1;
	}
	else if (paddle->ball->y + paddle->ball->height > SCREEN_HEIGHT) {
		// Bottom

		// Ball lost
		paddle->ResetPaddle();
	}

	// Left and right collisions
	if (paddle->ball->x <= 0.f) {
		// Left
		// Keep the ball within the board and reflect the x-direction
		paddle->ball->x = 0.f;
		paddle->ball->direction.x = 1;
	}
	else if (paddle->ball->x + paddle->ball->width >= SCREEN_WIDTH) {
		// Right
		// Keep the ball within the board and reflect the x-direction
		paddle->ball->x = SCREEN_WIDTH - paddle->ball->width;
		paddle->ball->direction.x = -1;
	}
}

void GameManager::CheckBrickCollisions() 
{
	int currentLevel = levelManager->currentLevel;
	for (int i = 0; i < levelManager->getNum(); i++)
	{
		//std::cout << i;
		if (levelManager->getLevelData(currentLevel, i) != 0) 
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
					//Tror denne burde være minst like stor som ballens movement speed, men ikke FOR stor
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

/*void Game::BallBrickResponse(int dirindex) {
	// dirindex 0: Left, 1: Top, 2: Right, 3: Bottom

	// Direction factors
	int mulx = 1;
	int muly = 1;

	if (ball->dirx > 0) {
		// Ball is moving in the positive x direction
		if (ball->diry > 0) {
			// Ball is moving in the positive y direction
			// +1 +1
			if (dirindex == 0 || dirindex == 3) {
				mulx = -1;
			}
			else {
				muly = -1;
			}
		}
		else if (ball->diry < 0) {
			// Ball is moving in the negative y direction
			// +1 -1
			if (dirindex == 0 || dirindex == 1) {
				mulx = -1;
			}
			else {
				muly = -1;
			}
		}
	}
	else if (ball->dirx < 0) {
		// Ball is moving in the negative x direction
		if (ball->diry > 0) {
			// Ball is moving in the positive y direction
			// -1 +1
			if (dirindex == 2 || dirindex == 3) {
				mulx = -1;
			}
			else {
				muly = -1;
			}
		}
		else if (ball->diry < 0) {
			// Ball is moving in the negative y direction
			// -1 -1
			if (dirindex == 1 || dirindex == 2) {
				mulx = -1;
			}
			else {
				muly = -1;
			}
		}
	}

	// Set the new direction of the ball, by multiplying the old direction
	// with the determined direction factors
	ball->SetDirection(mulx*ball->dirx, muly*ball->diry);
}

int Game::GetBrickCount() {
	int brickcount = 0;
	for (int i = 0; i<BOARD_WIDTH; i++) {
		for (int j = 0; j<BOARD_HEIGHT; j++) {
			Brick brick = board->bricks[i][j];
			if (brick.state) {
				brickcount++;
			}
		}
	}

	return brickcount;
}*/



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