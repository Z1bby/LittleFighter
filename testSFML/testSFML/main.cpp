#include <SFML/Graphics.hpp>
#include <iostream>

#define WINDOW_WIDTH 600
#define WINDOW_HEIGHT 450
#define PLAYER_RESOLUTION 64

#define IDLE_ANIMATION_LENGHT 4

enum eDirections { Left, Right };
enum eAnimationTypes { Idle, Walk };

class Player {
	int record_idle_animation;
	int speed_idle_animation;
	int animation_frame;
public:
	eAnimationTypes actual_animation;
	
	sf::Texture texture;
	sf::Sprite sprite;

	eDirections direction;
	sf::Keyboard::Key key_up;
	sf::Keyboard::Key key_right;
	sf::Keyboard::Key key_down;
	sf::Keyboard::Key key_left;
	Player() {
		texture.loadFromFile("bitmaps/player1/player1_sheet.png");
		sprite.setTexture(texture);
		sprite.setPosition(sf::Vector2f(0, 0));

		direction = Left;
		key_up = sf::Keyboard::Up;
		key_right = sf::Keyboard::Right;
		key_down = sf::Keyboard::Down;
		key_left = sf::Keyboard::Left;

		record_idle_animation = 0;
		speed_idle_animation = 200;
		animation_frame = 0;
		actual_animation = Idle;
	}
	void update_animation() {
		if (actual_animation == Idle && clock() - record_idle_animation > speed_idle_animation) {
			animation_frame = (++animation_frame) % IDLE_ANIMATION_LENGHT;
			sprite.setTextureRect(sf::IntRect(animation_frame*PLAYER_RESOLUTION, 0, PLAYER_RESOLUTION, PLAYER_RESOLUTION));
			record_idle_animation = clock();
		}
	}
	void update() {
		update_animation();
	}
	~Player() {}
};

int main()
{
	sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Litte Fighter");
	window.setFramerateLimit(30);
	Player player1;
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			else if (event.type == sf::Event::KeyPressed) {
				if (event.key.code == player1.key_left)
					std::cout << "L\n";
				else if (event.key.code == player1.key_right)
					std::cout << "R\n";
			}
		} //while

		player1.update();

		window.clear();
		window.draw(player1.sprite);
		window.display();
	} //while
	return 0;
}