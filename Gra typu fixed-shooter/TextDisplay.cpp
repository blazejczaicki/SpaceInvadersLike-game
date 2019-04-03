#include"TextDisplay.h"
#include"HumanStrategy.h"
TextDisplay::TextDisplay()
{
	initscr();
	resize_term(SCREEN_HEIGHT,SCREEN_WIDTH);
	nodelay(stdscr, TRUE);
	getmaxyx(stdscr, rows, columns);
}

TextDisplay::~TextDisplay()
{
	endwin();
}

void TextDisplay::printGrid()
{
	int columnsNum = TILE_WIDTH;
	int rowsNum = TILE_HEIGHT;
	for (int j = 0; j < rows; ++j)
		for (int i = 0; i < columns; ++i)
		{
			if (i % columnsNum == 0 && j % rowsNum == 0)
				mvprintw(j, i, "+");
			else if (i % columnsNum != 0 && j % rowsNum == 0)
				mvprintw(j, i, "-");
			else if (i % columnsNum == 0 && j % rowsNum != 0)
				mvprintw(j, i, "|");
			else mvprintw(j, i, " ");
		}
}

void TextDisplay::printObject(const size_t objectId, const Point<double>& pos, const std::set<Point<int>>& obj)
{
	if (objectId >= objects.size())
	{
		return;
	}
	std::stringstream ss(objects[objectId]);
	std::string line;
	int posY = static_cast<int>(pos.y);
	while (std::getline(ss, line, '\n'))
	{
		mvprintw(posY++, pos.x, line.c_str());
	}
}

size_t TextDisplay::loadObject(const std::string& object)
{
	std::lock_guard<std::mutex> lock(mts);
	objects.push_back(object);
	return objects.size() - 1;
}

std::set<Point<int>> TextDisplay::getObject(const size_t &objectId)
{
	std::lock_guard <std::mutex> lock(mts);
	std::set<Point<int>> object;
	if (objectId >= objects.size())
	{
		return object;
	}
	std::stringstream ss(objects[objectId]);
	std::string line;
	int col = 0;
	int row = 0;
	while (std::getline(ss, line, '\n'))
	{
		std::for_each(line.begin(), line.end(),
			[&object, &col, row](auto c) {
			++col;
			if (c != ' ') object.insert(Point<int>{ col, row });
		});
		++row;
		col = 0;
	}
	return object;
}

void TextDisplay::wait()
{
	std::this_thread::sleep_for(std::chrono::milliseconds(100));
	refresh();
}

void TextDisplay::printText(const std::string& text, const Point<double>& p) const
{
	std::stringstream ss(text);
	std::string line;
	double pY = p.y;
	while (std::getline(ss, line, '\n'))
	{
		mvprintw(pY++, p.x, line.c_str());
	}
}

void TextDisplay::displayUI(const int &hp, const size_t &lifes, const size_t &ammoID, const int &ammo) const
{
	std::string info = "Liczba odrodzen: " + std::to_string(lifes) + "           Punkty wytrzymalosci: " + std::to_string(hp) 
		+ "          ID amunicji: " + std::to_string(ammoID) + "           Ilosc: " + std::to_string(ammo);
	printText(info, { 6.0, SCREEN_HEIGHT - SCREEN_HEIGHT * 0.05 });
}

bool TextDisplay::menu(size_t &scenarioID, size_t &playerTypeShID)
{
	clear();
	char c;
	do
	{
		printText("Nowa Gra[Enter]", { SCREEN_WIDTH / 2 - 10, SCREEN_HEIGHT / 2 - 4 });
		printText("Wyjscie[Esc]", { SCREEN_WIDTH / 2 - 10, SCREEN_HEIGHT / 2 - 2 });
		refresh();
		noecho();
		c = getch();
		if (c==10)
		{
			clear();
			do
			{
				printText("Scenariusz 1", { SCREEN_WIDTH / 2 - 10, SCREEN_HEIGHT / 2 - 4 });
				printText("Scenariusz 2", { SCREEN_WIDTH / 2 - 10, SCREEN_HEIGHT / 2 - 2 });
				printText("Wstecz[Bspc]", { SCREEN_WIDTH / 2 - 10, SCREEN_HEIGHT / 2 });
				c = getch();
				switch (c)
				{
				case '1': scenarioID = 1; playerTypeShID = 1; return true; break;
				case '2': scenarioID = 2; playerTypeShID = 2; return true; break;
				}
			} while (c != 8);
			clear();
		}
	} while (c != 27);
		return false;
}

void TextDisplay::displayEnd(bool win)
{
	clear();
	std::string info;
	if (win)
	{
		info = R"ok(
#   #   # () \\	 []
 # # # #  || []\\[]
  #   #   || []  \\
)ok";
	}
	else
	{
		info = R"ok(
!    ||----||   ====   []````
!   ||      || ||___   []----
!___ || ___||   ____|| []____
)ok";
	}
	printText(info, { SCREEN_WIDTH*0.25, SCREEN_HEIGHT*0.5 });
	refresh();
}


void TextDisplay::playerMove(char &quit, HumanStrategy &scheme, GameObjects &gameObjects, GameObjects &playerGameObjects, std::mutex &mtx, TextDisplay &td)
{
	char c;
	while (quit != 27)
	{
		c = getch();
		if (c == 27)
			quit = 27;
		scheme.keyControler(c, gameObjects, playerGameObjects, td, mtx);
		std::this_thread::sleep_for(std::chrono::milliseconds(16));
	}
}