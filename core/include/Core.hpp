/*
** EPITECH PROJECT, 2019
** OOP_arcade_2019
** File description:
** Core.hpp
*/

#ifndef CORE_HPP
# define CORE_HPP

/** 
 * \file Core.hpp
 * \date March 2020
 * \version 0.1
*/
#include "DLLoader.hpp"
#include "IGraphics.hpp"
#include "arcade_ptr.hpp"

#include <fstream>
#include <sstream>

static const string &SCORE_CONF      = "./.conf/score_list";
static const string &DEFAULT_NAME    = "anonymous";
static const size_t &MAX_NAME_LENGTH = 30;

/**
 * \def IS_VALID_CHARAC(c)
 * \brief check if a character is alphanumeric
 * \param c compared character
 * \return true is c is alphanumeric, false otherwise
*/
#define IS_VALID_CHARAC(c) ((c >= '0' && c <= '9') || (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))

/**
 * \class Core
 * \brief main project class. Contains all necessary functions from libs/games interfaces to articulate the whole
*/
class Core
{
    public:
        /**
        * \fn explicit Core (int &, const char *)
        * \brief constructor of Core class
        * \param ac number of command line args
        * \param av1 first command line arg
        */
        explicit Core(int &ac, const char *av1);
        /**
        * \fn ~Core ()
        * \brief destructor of Core class
        */
        ~Core() = default;
    public:
        /**
        * \fn int sendErr (GameError &) noexcept
        * \brief print the error on the standard output
        * \param error error thrown by the Core functions
        * \return the error flag
        */
        static int sendErr(GameError &error) noexcept;
    public:
        /**
        * \fn int launchMenu ()
        * \brief launch main menu of arcade
        */
        int  launchMenu();
        /**
        * \fn void push_menu_elems (vector<display_t> &) noexcept
        * \brief fill elems with all elements to display in the menu
        * \param elems vector of elements displayed in the menu
        */
        void push_menu_elems(vector<display_t> &elems) noexcept;
        /**
        * \fn bool quit (const char &) const
        * \brief check if the QUIT input has been pressed by the player
        * \param event key code of user input
        * \return true if QUIT was pressed, false otherwise
        */
        bool quit(const char &event) const;
        /**
        * \fn bool handleNameEvents (const char &, vector<display_t> &, bool &) noexcept
        * \brief check if the NEW_NAME input has been pressed by the player and change state according to input
        * \param event key code of user input
        * \param elems vector of elements to display
        * \param state state to check if inputs have to be treated as events or characters
        * \return state
        */
        bool handleNameEvents(const char &event, vector<display_t> &elems, bool &state) noexcept;
        /**
        * \fn void changeName (const char &, vector<display_t> &, bool &) noexcept
        * \brief change player name according to the received inputs
        * \param event key code of user input
        * \param elems vector of elements to display
        * \param state state to check if inputs have to be treated as events or characters
        */
        void changeName(const char &event, vector<display_t> &elems, bool &state) noexcept;
        /**
        * \fn int select(const char &) const noexcept
        * \brief check if a game input has been pressed
        * \param event key code of user input
        * \return index of the game
        */
        int  select(const char &event) const noexcept;
        /**
        * \fn bool isAvailable (const size_t &) const noexcept
        * \brief check if the index game is valid
        * \param index index to check
        * \return true if index is valid, false otherwise
        */
        bool isAvailable(const size_t &index) const noexcept;
        /**
        * \fn void display (vector<display_t> &)
        * \brief call all lib functions which print items on screen
        * \param elems elements to display
        */
        void display(vector<display_t> &elems);
        /**
        * \fn int launchGame ()
        * \brief launch game from dynamic library
        * \return player score
        */
        int  launchGame();
        /**
        * \fn char getDirection (char &, const char &) noexcept
        * \brief check if a movement event occured, and change direction according to the user input
        * \param dir direction of player
        * \param event key code of user input
        * \return current direction
        */
        char getDirection(char &dir, const char &event) noexcept;
        /**
        * \fn void changeLib (const char &)
        * \brief check if a *_LIB input was pressed, and swap libs according to the input
        * \param event key code of user input
        */
        void changeLib(const char &event);
        /**
        * \fn void changeGame (const char &)
        * \brief check if a *_GAME input was pressed, and swap games according to the input
        * \param event key code of user input
        */
        void changeGame(const char &event);
        /**
        * \fn void saveScore (const int &) const noexcept
        * \brief write player name and score into a config file
        * \param score player score
        */
        void saveScore(const int &score) const noexcept;
        /**
        * \fn void displayEndScreen ()
        * \brief display whether the player win or lose his pseudo and score
        */
        void displayEndScreen();
        /**
        * \fn const string getHightScore () const noexcept
        * \brief read all scores stacked in config files and search for the highest
        * \return highest score
        */
        const string getHighScore() const noexcept;
        /**
        * \fn const string &getPlayerName () const noexcept
        * \brief getter for player name
        * \return player name
        */
        const string &getPlayerName() const noexcept;
    private:
        string       playerName; /*!< pseudo of the player */
        const string path; /*!< first command line argument */
        DLLoader<arcade::IGraphics>   lloader; /*!< dynamic library loader */
        DLLoader<arcade::IGame>       gloader; /*!< dynamic game loader */
        arcade_ptr<arcade::IGraphics> lib; /*!< smart pointer on dynamic library for lib */
        arcade_ptr<arcade::IGame>     game; /*!< smart pointer on dynamic library for game */
    public:
        /**
        * \fn GameStorage &getGames () noexcept
        * \brief getter for available games
        * \return games paths
        */
        GameStorage &getGames() noexcept;
        /**
        * \fn LibStorage &getLibs () noexcept
        * \brief getter for available libs
        * \return libs paths
        */
        LibStorage  &getLibs() noexcept;
    private:
        LibStorage  libs; /*!< storage for libs path and name */
        GameStorage games; /*!< storage for games path and name */
};

#endif