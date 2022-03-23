#include<SFML/Graphics.hpp>
#include<SFML/Audio.hpp>			
#include<iostream>
#include<sstream>
#include<string>
using namespace std;
using namespace sf;
int main() {
	RenderWindow window(VideoMode(800, 600), "Shazly");

	window.setFramerateLimit(60);
	window.setKeyRepeatEnabled(false);
	//varaible keeping game on
	bool play = true;
	//main event
	Event event;

	//FOnts
	Font font;
	if (font.loadFromFile("Data/arial.ttf") == false) cout << "no font";
	Text Score;
	Score.setFillColor(Color::Black);
	Score.setPosition(300, 20);
	Score.setFont(font);
	Score.setString("");
	Score.setCharacterSize(50);
	Score.setOutlineThickness(10);
	Score.setOutlineColor(Color::White);

	//Images
	Texture pads, bg, ball;
	if (pads.loadFromFile("Data/pad.png") == false || bg.loadFromFile("Data/background.png") == false || ball.loadFromFile("Data/ball.png") == false)  cout << "error png";

	//Sounds
	SoundBuffer hitt;
	if (hitt.loadFromFile("Data/hit.wav") == false)  cout << "sound not found";

	Sound hit;
	hit.setBuffer(hitt);
	hit.setVolume(50);
	hit.setPitch(2);
	//States 


   //variables

	bool up = false, down = false, left = false, right = false;

	int yVelocity = 0;
	int ballVelocityY = -3;
	int ballVelocityX = -3;
	int pad1Score = 0, pad2Score = 0;

	///////Shapes
	//Background
	RectangleShape background, pad1, pad2, balls;
	background.setSize(Vector2f(800, 600));
	background.setTexture(&bg);

	//Pads

	pad1.setSize(Vector2f(50, 100));
	pad1.setPosition(50, 200);
	pad1.setTexture(&pads);

	pad2.setSize(Vector2f(50, 100));
	pad2.setPosition(700, 200);
	pad2.setTexture(&pads);

	//ball
	balls.setSize(Vector2f(50, 50));
	balls.setPosition(350, 200);
	balls.setTexture(&ball);

	//Game loop
	while (play == true) {

		//events
		while (window.pollEvent(event)) {


			if (event.type == Event::Closed)
			{
				play = false;

			}

			if (event.type == Event::KeyPressed && event.key.code == Keyboard::Up)
			{
				up = true;
			}

			if (event.type == Event::KeyPressed && event.key.code == Keyboard::Down)
			{
				down = true;
			}

			if (event.type == Event::KeyReleased && event.key.code == Keyboard::Up)
			{
				up = false;
			}

			if (event.type == Event::KeyReleased && event.key.code == Keyboard::Down)
			{
				down = false;
			}


		}

		//Logic

		//Score
		//pad1
		if (up == true)
		{
			yVelocity = -5;
		}
		if (down == true)
		{
			yVelocity = 5;
		}
		if (up == false && down == false)
		{
			yVelocity = 0;
		}
		if (up == true && down == true)
		{
			yVelocity = 0;
		}
		//Out of bounds check
		if (pad1.getPosition().y <= 0)
		{
			pad1.setPosition(50, 0);
		}

		if (pad1.getPosition().y >= 500)
		{
			pad1.setPosition(50, 500);
		}
		pad1.move(0, yVelocity);
		////////////////////pad2
		int velocityPAD2 = 0;
		if (balls.getPosition().y < pad2.getPosition().y)
		{
			velocityPAD2 = -2;
		}
		if (balls.getPosition().y > pad2.getPosition().y)
		{
			velocityPAD2 = 3;
		}
		pad2.move(0, velocityPAD2);

		//Out of bounds check
		if (pad2.getPosition().y <= 0)
		{
			pad2.setPosition(50, 0);
		}

		if (pad2.getPosition().y >= 500)
		{
			pad2.setPosition(700, 500);
		}


		//////ball
		balls.move(ballVelocityX, ballVelocityY);

		//Out of bounds check

		if (balls.getPosition().y < 0)
		{
			ballVelocityY = -ballVelocityY;
		}

		if (balls.getPosition().y > 550)
		{
			ballVelocityY = -ballVelocityY;
		}
		if (balls.getPosition().x < -10)
		{
			pad2Score++;
			balls.setPosition(300, 200);

		}

		if (balls.getPosition().x > 810)
		{
			pad1Score++;
			balls.setPosition(300, 200);
		}
		//COLLISION
		if (pad1.getGlobalBounds().intersects(balls.getGlobalBounds()))
		{

			ballVelocityX = -ballVelocityX;
			hit.play();
		}

		if (pad2.getGlobalBounds().intersects(balls.getGlobalBounds()))
		{
			hit.play();
			ballVelocityX = -ballVelocityX;
		}

		//Rendering
		stringstream text;
		text << pad1Score << "    :    " << pad2Score;
		Score.setString(text.str());
		window.clear();
		window.draw(background);
		window.draw(pad1);
		window.draw(pad2);
		window.draw(balls);
		window.draw(Score);
		window.display();




	}


	return 0;
}