/*
** EPITECH PROJECT, 2019
** OOP_arcade_2019
** File description:
** Core.cpp
*/

#include "Core.hpp"

Core::Core(int &ac, const char *av1)
    : playerName(DEFAULT_NAME), path(ArgsError::checkArgs(ac, av1)), lloader(path), lib(lloader.getInstance())
{
    if (!lib.get()) {
        err.flag = GameError::ERRCREATE;
        throw err;
    }
    while (libs.dlname[libs.index].compare(lloader.getPath()) && libs.index < libs.dlname.size())
        ++libs.index;
}

int Core::sendErr(GameError &error) noexcept
{
    cout << error.what();
    if (err.sym.empty() == false)
        cout << err.sym + "' symbol.";
    cout << endl;
    return error.flag;
}

int Core::launchMenu()
{
    vector<display_t> elems;
    bool changeNameState(false);

    push_menu_elems(elems);
    while (true) {
        const char event = lib->getEvent();
        if (quit(event))
            return arcade::Commands::QUIT;
        display(elems);
        if (handleNameEvents(event, elems, changeNameState))
            continue;
        const size_t game = select(event) - 1;
        if (isAvailable(game)) {
            games.index = game;
            return game + 1;
        }
        changeLib(event);
    }
}

void Core::push_menu_elems(vector<display_t> &elems) noexcept
{
    float y(0.30);

    elems.push_back({ "", "", "", "./assets/menu.jpg", 0.0, 0.0, true });
    elems.push_back({ "MENU", "red", "", "", 0.50, 0.20, true });
    elems.push_back({ "GAMES", "red", "", "", 0.35, y, true });
    elems.push_back({ "LIBS", "red", "", "", 0.65, y, true });
    for (const auto game : games.getNames())
        elems.push_back({ game, "red", "", "", 0.35, (y += 0.10), true });
    y = 0.30;
    for (const auto lib : libs.getNames())
        elems.push_back({ lib, "pink", "", "", 0.65, (y += 0.10), true });
    elems.push_back({ "hight score - ", "blue", "", "", 0.40, (y += 0.10), true });
    elems.push_back({ getHighScore(), "blue", "", "", 0.65, y, true });
    elems.push_back({ "name - ", "green", "", "", 0.40, (y += 0.10), true });
    elems.push_back({ playerName, "green", "", "", 0.60, y, true });
}

bool Core::quit(const char &event) const
{
    if (event == arcade::Commands::QUIT || event == arcade::Commands::ESCAPE) {
        lib->destructor();
        return true;
    }
    return false;
}

const string &Core::getPlayerName() const noexcept
{
    return playerName;
}

bool Core::handleNameEvents(const char &event, vector<display_t> &elems, bool &changeNameState) noexcept
{
    if (changeNameState == true)
        changeName(event, elems, changeNameState);
    if (event == arcade::Commands::NEW_NAME && changeNameState == false) {
        playerName = "                             ";
        elems[elems.size() - 1].ascii = playerName;
        changeNameState = true;
    }
    return changeNameState;
}

void Core::changeName(const char &event, vector<display_t> &elems, bool &changeNameState) noexcept
{
    static size_t index = 0;

    if (index < MAX_NAME_LENGTH && IS_VALID_CHARAC(event)) {
        playerName[index++] = event;
        elems[elems.size() - 1].ascii = playerName;
    }
    if (event == arcade::Commands::ENTER) {
        index = 0;
        changeNameState = false;
    }
}

int Core::select(const char &event) const noexcept
{
    return (event >= '0' && event <= '9') ? event - 48 : -1;
}

bool Core::isAvailable(const size_t &index) const noexcept
{
    return (index < games.dlname.size()) ? true : false;
}

void Core::display(vector<display_t> &elems)
{
    if (lib->clockDisplay() == false)
        return ;
    for (auto display : elems) {
        display.x = display.x * lib->getWindowWidth();
        display.y = display.y * lib->getWindowHeight();
        lib->print(display);
    }
    lib->refresh();
}

void Core::changeLib(const char &event)
{
    if (event == arcade::NEXT_LIB || event == arcade::PREV_LIB) {
        lib->destructor();
        lib.release();
        lib.reset((event == arcade::NEXT_LIB) ? lloader.next(libs) : lloader.prev(libs));
    }
}

int Core::launchGame()
{
    char direction(4);

    gloader.setPath(games.dlname[games.index].c_str());
    gloader.load();
    game.reset(gloader.getInstance());

    while (true) {
        const char event = lib->getEvent();
        if (quit(event))
            return game->getScore();
        changeLib(event);
        changeGame(event);
        game->getInitState();
        if (event == arcade ::Commands::MENU)
            launchMenu();
        if (event == arcade ::Commands::RESTART)
            game->restart();
        direction = getDirection(direction, event);
        if (game->speedGame())
            game->move(direction);
        if (game->getStatus() == arcade::statusGame::LOSE || game->getStatus() == arcade::statusGame::WIN) {
            displayEndScreen();
            break;
        }
        display(game->getState());
    }
    return game->getScore();
}

char Core::getDirection(char &dir, const char &event) noexcept
{
    if (event == arcade::Commands::UP
        || event == arcade::Commands::DOWN
        || event == arcade::Commands::LEFT
        || event == arcade::Commands::RIGHT
        || event == arcade::Commands::ENTER)
        return event;
    return dir;
}

void Core::displayEndScreen()
{
    stringstream buff;
    string score;
    vector<display_t> end;

    buff << game->getScore();
    buff >> score;
    if (game->getStatus() == arcade::statusGame::LOSE)
        end = {
            { "", "", "", "./assets/go.jpg", 0., -0.25, true },
            { "YOU LOOSE", "red", "", "", 0.45, 0.35, true },
            { "hight score - ", "blue", "", "", 0.35, 0.50, true },
            { score, "blue", "", "", 0.60, 0.50, true },
            { "name - ", "green", "", "", 0.35, 0.60, true },
            { playerName, "green", "", "", 0.55, 0.60, true },
        };
    else
        end = {
            { "", "", "", "./assets/go.jpg", 0., -0.25, true },
            { "YOU WIN", "red", "", "", 0.45, 0.35, true },
            { "hight score - ", "blue", "", "", 0.35, 0.50, true },
            { score, "blue", "", "", 0.60, 0.50, true },
            { "name - ", "green", "", "", 0.35, 0.60, true },
            { playerName, "green", "", "", 0.55, 0.60, true },
        };
    while (true) {
        const char event = lib->getEvent();
        if (quit(event))
            break;
        changeLib(event);
        display(end);
    }
}

void Core::changeGame(const char &event)
{
    if (event == arcade::NEXT_GAME || event == arcade::PREV_GAME) {
        game.release();
        game.reset((event == arcade::NEXT_GAME) ? gloader.next(games) : gloader.prev(games));
    }
}

GameStorage &Core::getGames() noexcept
{
    return games;
}

LibStorage &Core::getLibs() noexcept
{
    return libs;
}

void Core::saveScore(const int &score) const noexcept
{
    ofstream file(SCORE_CONF, ios::app);

    if (file.is_open()) {
        file << score << " - " << playerName << endl;
        file.close();
    }
}

const string Core::getHighScore() const noexcept
{
    ifstream file(SCORE_CONF, ios::in);
    string buff;
    int score(0);

    if (file.is_open()) {
        while (!getline(file, buff).eof()) {
            stringstream ss(buff);
            int tmp;
            ss >> tmp;
            if (score < tmp)
                score = tmp;
        }
        file.close();
    }
    stringstream ss;
    ss << score;
    ss >> buff;
    return buff;
}