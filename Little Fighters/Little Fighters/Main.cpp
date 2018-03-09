#include <SFML/Graphics.hpp>
#include <cmath>
#include <fstream>
#include <iostream>

#define CHANGE_TO_ASCII 97
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

using namespace std;

string getRandomLine(ifstream &file) {
	unsigned int num = 1+rand()%4905;
	file.seekg(ios::beg);
	for (int i = 0; i < num - 1; ++i) {
		file.ignore(numeric_limits<streamsize>::max(), '\n');
	}
	string line;
	file >> line;
	return line;
}


void shift_letters(char* tablica, int how_many)
{
	for (int i = how_many - 1; i >= 0; i--)
	{
		tablica[i + 1] = tablica[i];
	}
}

bool check_word(char* written_letters, string wanted_word)
{
	for (int i = 0; i < wanted_word.size(); i++)
	{
		if (written_letters[wanted_word.size()-1-i] != wanted_word[i]) return false;
	}
	return true;
}

void set_new_word(ifstream& slowa, sf::Text& cokolwiek, int window_width, int window_height) 
{
	cokolwiek.setString(getRandomLine(slowa));
	cokolwiek.setFillColor(sf::Color(0, 0, 0));
	int position_x = rand() % (window_width - (int)cokolwiek.getGlobalBounds().width);
	int position_y = rand() % (window_height - (int)cokolwiek.getGlobalBounds().height);
	cokolwiek.setPosition(position_x, position_y);
}

int main()
{
	sf::RenderWindow okno(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Creepy signs", sf::Style::Fullscreen);
	sf::Clock stoper;
	okno.setMouseCursorVisible(false);

	sf::Font font;
	if (!font.loadFromFile("youmurdererbb_reg.ttf")) {
		return EXIT_FAILURE;
	}

	ifstream slowa("words.txt");

	int window_width = WINDOW_WIDTH;
	int window_height = WINDOW_HEIGHT;
	srand(time(NULL));
	sf::Text cokolwiek("", font, 100);
	set_new_word(slowa, cokolwiek, window_width, window_height);
	char tablica[32];
	int points = 0;
	sf::Text punkty(to_string(points), font, 100);
	punkty.setFillColor(sf::Color(200, 0, 0));

	sf::CircleShape ksztalt(/*sin(stoper.getElapsedTime().asSeconds()) * okno.getSize().y / 8 + okno.getSize().y / 4*/okno.getSize().y / 4 );
	ksztalt.setOrigin(sf::Vector2f(ksztalt.getRadius(), ksztalt.getRadius()));
	ksztalt.setFillColor(sf::Color(200, 240, 140));

	while (okno.isOpen())
	{
		sf::Event event;
		while (okno.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				okno.close();
			else if (event.type == sf::Event::Resized)
			{
				okno.setView(sf::View(sf::FloatRect(0, 0, event.size.width, event.size.height)));
				window_width = okno.getSize().x;
				window_height = okno.getSize().y;
			}
			else if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::Space)
				{
					set_new_word(slowa, cokolwiek, window_width, window_height);
				}
				if (event.key.code == sf::Keyboard::Escape)
				{
					okno.close();
				}
				if (event.key.code <= sf::Keyboard::Z && event.key.code >= sf::Keyboard::A)
				{

					shift_letters(tablica, cokolwiek.getString().getSize());
					tablica[0] = event.key.code + CHANGE_TO_ASCII;

					if (check_word(tablica, cokolwiek.getString()))
					{
						if (points == 5)
						{
							cokolwiek.setString("jpgmd");
							cokolwiek.setFillColor(sf::Color(0, 0, 0));
							int position_x = rand() % (window_width - (int)cokolwiek.getGlobalBounds().width);
							int position_y = rand() % (window_height - (int)cokolwiek.getGlobalBounds().height);
							cokolwiek.setPosition(position_x, position_y);
							points++;
						}
						else
						{
							set_new_word(slowa, cokolwiek, window_width, window_height);
							points++;
						}
					}
				}
			}
		} //while
		okno.clear();

		punkty.setString(to_string(points));
		punkty.setPosition(window_width - (int)punkty.getGlobalBounds().width - 20, -20);
		ksztalt.setPosition(sf::Mouse::getPosition(okno).x, sf::Mouse::getPosition(okno).y);
		if (points <= 50)
		{
			ksztalt.setRadius(okno.getSize().y / 4 - floor((double)points/5) * 10);
		}
		okno.draw(ksztalt);
		okno.draw(cokolwiek);
		okno.draw(punkty);
		okno.display();
	} //while
	return 0;
}