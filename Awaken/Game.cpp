#include "Main.h"
#include "GameObjects.h"
#include "HandleInput.h"
#include "Game.h"

void Game::Run()
{
	Init();
	MainLoop();
}

void Game::MainLoop()
{
	//main game loop
	while (window.isOpen())
	{
		sf::Event event;
		//event listening
		while (window.pollEvent(event))
		{
			dt = clock.restart().asSeconds();
			if (event.type == sf::Event::Closed)
				window.close();
		}
		khandle(player); //handle keypress
		
		Update();

		viewpos = sf::Vector2f(player->getPosition().x + 10 - (800 / 2), player->getPosition().y + 10 - (600 / 2));

		if (viewpos.x < 0)
			viewpos.x = 0;
		if (viewpos.y < 0)
			viewpos.y = 0;

		view.reset(sf::FloatRect(viewpos.x, viewpos.y, 800, 600));

		window.clear(sf::Color::White); //clear the window
		window.setView(view);
		window.draw(bg);
		window.draw(Text);
		for each (Tile* tile in tiles)
		{
			window.draw(tile->getSprite());
		}
		window.draw(player->getCurrentSprite()); //draw to the back buffer
		window.display(); //display the back buffer
	}
}

void Game::Init()
{
	window.create(sf::VideoMode(800, 600), "Awaken", sf::Style::Titlebar | sf::Style::Close);
	SCREEN_HEIGHT = window.getSize().y;
	SCREEN_WIDTH = window.getSize().x;
	//set fps limit to 60
	window.setFramerateLimit(60);
	//enable vsync
	window.setVerticalSyncEnabled(true);

	//make a view
	view.reset(sf::FloatRect(0, 0, (float)SCREEN_WIDTH, (float)SCREEN_HEIGHT));
	view.setViewport(sf::FloatRect(0, 0, 1.0f, 1.0f));

	float lastTime = 0;

	player = new Player(sf::Vector2f((float)((SCREEN_WIDTH / 2) - 32), (float)((SCREEN_HEIGHT / 2) - 32)));

	if (!font.loadFromFile("assets/fonts/consola.ttf"))
		MessageBox(0, L"Error: failed to load asset", L"Error", MB_ABORTRETRYIGNORE);

	if (!player->texture.loadFromFile("assets/images/player.png"))
		MessageBox(0, L"Error: failed to load asset", L"Error", MB_ABORTRETRYIGNORE);
	else
		player->setTexture(player->texture);
	if (!bgtexture.loadFromFile("assets/images/bg.png"))
		MessageBox(0, L"Error: failed to load asset", L"Error", MB_ABORTRETRYIGNORE);
	else
		bg.setTexture(bgtexture);

	tiles.push_back(new Tile(sf::Vector2f((SCREEN_WIDTH / 2) - 32, (SCREEN_HEIGHT / 2) + 32)));
	tiles.push_back(new Tile(sf::Vector2f((SCREEN_WIDTH / 2), (SCREEN_HEIGHT / 2) + 32)));
	tiles.push_back(new Tile(sf::Vector2f((SCREEN_WIDTH / 2) + 32, SCREEN_HEIGHT / 2)));
	tiles.push_back(new Tile(sf::Vector2f((SCREEN_WIDTH / 2) - 64, SCREEN_HEIGHT / 2)));
	tiles.push_back(new Tile(sf::Vector2f((SCREEN_WIDTH / 2) - 64, (SCREEN_HEIGHT / 2) - 128)));
	int count = 0;
	Text.setColor(sf::Color::Black);
	Text.setFont(font);
}

void Game::Update()
{
	player->setPosition(player->getPosition().x + player->vel.x * dt, player->getPosition().y + player->vel.y * dt);
	if (player->vel.y > 100)
		player->vel.y = 100;
	player->isTouchingGround = false;
	Text.setPosition(viewpos.x, viewpos.y);
	std::string string1 = std::to_string(player->getPosition().x);
	std::string string2 = std::to_string(player->getPosition().y);
	Text.setString(string1 + "," + string2);
	for each (Tile* tile in tiles)
	{
		if (tile->getSprite().getGlobalBounds().intersects(player->getSprite().getGlobalBounds()))
		{
			player->isTouchingGround = true;
			//top
			if (player->getSprite().getPosition().y < tile->getSprite().getPosition().y)
				player->getSprite().setPosition(player->getSprite().getPosition().x, tile->getSprite().getPosition().y - tile->getSprite().getGlobalBounds().height);
			//left
			else if (player->getSprite().getPosition().x + player->getSprite().getGlobalBounds().width - 8 > tile->getSprite().getPosition().x)
				player->getSprite().setPosition(tile->getSprite().getPosition().x - (tile->getSprite().getGlobalBounds().width - 8), player->getSprite().getPosition().y);
		}
	}
}