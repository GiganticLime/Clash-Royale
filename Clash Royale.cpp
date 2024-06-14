#include "SFML/Graphics.hpp"
#include <iostream>
#include <vector>

using namespace std;
using namespace sf;

enum troopType { rock, paper, scissor };

class Troop {
public:
	troopType type;
	Sprite sprite;
	Texture texture;

	Troop(Vector2f position) {
		sprite.setPosition(position);
	}
	virtual void drawTroop(RenderWindow& window) = 0;
	void updatePosition(Vector2f velocity) {
		sprite.move(velocity);
	}
	Vector2f getPosition() {
		return sprite.getPosition();
	}
	FloatRect getGlobalBounds() {
		return sprite.getGlobalBounds();
	}
};

class Rock : public Troop {
public:
	Rock(Vector2f position, Texture &color) : Troop(position) {
		type = troopType::rock;
		/*texture.loadFromFile("rock.png");*/
		sprite.setTexture(color);
		sprite.setScale(0.3f, 0.3f);
	}
	void drawTroop(RenderWindow& window) {
		window.draw(sprite);
	}
};

class Paper : public Troop {
public:
	Paper(Vector2f position, Texture &color) : Troop(position) {
		type = troopType::paper;
		/*texture.loadFromFile("paper.png");*/
		sprite.setScale(0.3f, 0.3f);
		sprite.setTexture(color);
	}
	void drawTroop(RenderWindow& window) {
		window.draw(sprite);
	}
};

class Scissor : public Troop {
public:
	Scissor(Vector2f position, Texture &color) : Troop(position) {
		type = troopType::scissor;
		/*texture.loadFromFile("scissor.png");*/
		sprite.setScale(0.3f, 0.3f);
		sprite.setTexture(color);
	}
	void drawTroop(RenderWindow& window) {
		window.draw(sprite);
	}
};


class Tower {
public:
	Vector2f towerPosition[2];
};


class Player {
public:
	Tower tower;
	vector<Troop*> troops;

	Texture redRock;
	Texture redPaper;
	Texture redScissor;

	void createTroop(RenderWindow& window) {
		for (int i = 0; i < troops.size(); i++)
		{
			troops[i]->drawTroop(window);
		}
	}
	virtual void updateTroopPositions() = 0;
	virtual void handleInput() = 0;
	virtual bool checkCollision() = 0;
	virtual Vector2f getSpawnPosition() = 0;

	void deleteTroop(int i) {
		troops.erase(i + troops.begin());
	}
};

class Blue : public Player {
private:

	bool zPressed = false;
	bool xPressed = false;
	bool cPressed = false;
	
	Texture blueRock;
	Texture bluePaper;
	Texture blueScissor;
public:
	Blue() {
		tower.towerPosition[0] = Vector2f(777, 764);
		tower.towerPosition[1] = Vector2f(385, 764);
		blueRock.loadFromFile("bluerock.png");
		bluePaper.loadFromFile("bluepaper.png");
		blueScissor.loadFromFile("bluescissor.png");
	}
	Vector2f getSpawnPosition() {
		int random = rand() % 2;
		cout << random;
		if (random == 0) {
			return tower.towerPosition[0];
		}
		else if (random == 1)
		{
			return tower.towerPosition[1];
		}
	}

	void handleInput() {
		if (Keyboard::isKeyPressed(Keyboard::Z)) {
			if (!zPressed) {
				troops.push_back(new Rock(getSpawnPosition(), blueRock));
				zPressed = true;
			}
		}
		else {
			zPressed = false;
		}

		if (Keyboard::isKeyPressed(Keyboard::X)) {
			if (!xPressed) {
				troops.push_back(new Paper(getSpawnPosition(), bluePaper));
				xPressed = true;
			}
		}
		else {
			xPressed = false;
		}

		if (Keyboard::isKeyPressed(Keyboard::C)) {
			if (!cPressed) {
				troops.push_back(new Scissor(getSpawnPosition(), blueScissor));
				cPressed = true;
			}
		}
		else {
			cPressed = false;
		}
	}
	void updateTroopPositions() {
		for (int i = 0; i < troops.size(); i++)
		{
			troops[i]->updatePosition(Vector2f(0, -2));
		}
	}

	bool checkCollision() {
		for (int i = 0; i < troops.size();)
		{
			if (troops[i]->getPosition().y < 326 && troops[i]->getPosition().x == 777) {
				deleteTroop(i);
				cout << "Collided with Red Right Tower" << endl;
				return true;
			}
			else if (troops[i]->getPosition().y < 326 && troops[i]->getPosition().x == 385) {
				cout << "Collided with Red Left Tower" << endl;
				deleteTroop(i);
				return true;
			}
			else {
				++i;
				return false;
			}
		}
	}
};
class Red : public Player {
private:
	bool qPressed = false;
	bool wPressed = false;
	bool ePressed = false;
	
public:
	Red() {
		tower.towerPosition[0] = Vector2f(777, 326);
		tower.towerPosition[1] = Vector2f(385, 326);

		redRock.loadFromFile("redrock.png");
		redPaper.loadFromFile("redpaper.png");
		redScissor.loadFromFile("redscissor.png");
	}
	Vector2f getSpawnPosition() {
		int random;
		random = rand() % 2;
		cout << random;
		if (random == 0) {
			return tower.towerPosition[0];
		}
		else if (random == 1)
		{ 
			return tower.towerPosition[1]; 
		}
	}

	void handleInput() {
		if (Keyboard::isKeyPressed(Keyboard::Q)) {
			if (!qPressed) {
				troops.push_back(new Rock(getSpawnPosition(), redRock));
				qPressed = true;
			}
		}
		else {
			qPressed = false;
		}

		if (Keyboard::isKeyPressed(Keyboard::W)) {
			if (!wPressed) {
				troops.push_back(new Paper(getSpawnPosition(), redPaper));
				wPressed = true;
			}
		}
		else {
			wPressed = false;
		}

		if (Keyboard::isKeyPressed(Keyboard::E)) {
			if (!ePressed) {
				troops.push_back(new Scissor(getSpawnPosition(), redScissor));
				ePressed = true;
			}
		}
		else {
			ePressed = false;
		}
	}

	void updateTroopPositions() {
		for (int i = 0; i < troops.size(); i++)
		{
			troops[i]->updatePosition(Vector2f(0, 2));
		}
	}
	bool checkCollision() {
		for (int i = 0; i < troops.size();)
		{
			if (troops[i]->getPosition().y > 764 && troops[i]->getPosition().x == 385) {
				cout << "Collided with Blue Left Tower" << endl;
				deleteTroop(i);
				return true;
			}
			else if (troops[i]->getPosition().y > 764 && troops[i]->getPosition().x == 777) {
				cout << "Collided with Blue Right Tower" << endl;
				deleteTroop(i);
				return true;
			}
			else {
				++i;
				return false;
			}
		}
	}
};
void troopInteraction(Blue &blue, Red &red) {
	for (int i = 0; i < blue.troops.size();)
	{
		 {bool collision = false;
		for (int j = 0; j < red.troops.size();) {
			if (blue.troops[i]->getGlobalBounds().intersects(red.troops[j]->getGlobalBounds())) {
				collision = true;
				troopType type1 = blue.troops[i]->type;
				troopType type2 = red.troops[j]->type;

				if (type1 == rock && type2 == scissor ||
					type1 == scissor && type2 == paper ||
					type1 == paper && type2 == rock)
				{
					cout << "red dies";
					red.deleteTroop(j);
				}
				else if (type2 == rock && type1 == scissor ||
					type2 == scissor && type1 == paper ||
					type2 == paper && type1 == rock)
				{
					blue.deleteTroop(i);
					cout << "blue dies";
					break;
				}
				else {
					blue.deleteTroop(i);
					red.deleteTroop(j);
					cout << "no one dies";
					break;
				}
			}
			else {
				++j; // If both are the same type or no valid game rule match, skip collision
			}
		}
		if (!collision)
			++i;
		}
	}
}
class MainLoop {
public:
	RenderWindow window;
	Texture background;
	Sprite backgroundSprite;

	Texture menuT;
	Sprite menu;

	Text winText;
	Font font;

	bool gameMenu = true;
	bool gameOver = false;

	Blue blue;
	Red red;

	MainLoop() : window(VideoMode(1193, 1058), "Clash Royale") {
		window.setFramerateLimit(60);
		//Game Background
		background.loadFromFile("gameBackground.png");
		backgroundSprite.setTexture(background);

		//Menu Background
		menuT.loadFromFile("menu.png");
		menu.setTexture(menuT);
		menu.setPosition(200, 0);

		//Win Text
		font.loadFromFile("neon.otf");
		winText.setFont(font);
		winText.setCharacterSize(120);
		winText.setPosition(440, 400);


		while (window.isOpen()) {
			Event event;
			while (window.pollEvent(event)) 
			{
				if (event.type == Event::Closed) window.close();
			}
			if (gameMenu) {
				renderMenu();
			}
			else if (!gameMenu)
			{
				renderGame();
			}
			if (!gameOver) {
				updateGame();
			}
		}
	}

	void renderMenu() {
		window.clear();
		window.draw(menu);
		window.display();

		FloatRect buttonArea(350, 244, 480, 120);
		FloatRect buttonAreaExit(350, 450, 480, 120);

		// Check for mouse click event
		Event event;
		while (window.pollEvent(event)) {
			if (event.type == Event::MouseButtonPressed) {
				if (event.mouseButton.button == Mouse::Left) {
					Vector2i mousePosition = Mouse::getPosition(window);
					if (buttonArea.contains(mousePosition.x, mousePosition.y)) {
						gameMenu = false;
					}
					else  if (buttonAreaExit.contains(mousePosition.x, mousePosition.y))
					{
						window.close();
					}
					else
					{
						gameMenu = true;
					}
				}
			}
		}
	}

	void renderGame() {
		window.clear();
		window.draw(backgroundSprite);
		
		blue.createTroop(window); // draw
		red.createTroop(window);

		window.draw(winText);
		window.display();

	}

	void updateGame() {

		red.handleInput(); // create
		blue.handleInput();

		blue.updateTroopPositions();
		red.updateTroopPositions();

		troopInteraction(blue, red);

		if (blue.checkCollision()) {
			winText.setFillColor(Color::Blue);
			winText.setString("Blue Wins!");
			gameOver = true;
		}
		else if (red.checkCollision()) {
			winText.setFillColor(Color::Red);
			winText.setString("Red Wins!");
			gameOver = true;
		}
	}
};


int main()
{
	MainLoop game;
}