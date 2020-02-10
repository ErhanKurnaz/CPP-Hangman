// HangmanConsoleGame.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <vector>
#include <array>
#include <stdlib.h>
#include <time.h>
#include <algorithm>
#include <fstream>
#include "models/User.h"

std::array<std::string, 370103> words = {};

void initWords() {
	std::cout << "initializing words" << std::endl;
	std::ifstream file;
	file.open(((std::string)SOURCE_DIR).append("/src/res/words_alpha.txt"));

	if (file.is_open()) {
		std::string word;

		int i = 0;
		while (std::getline(file, word)) {
			words[i] = word;
			i++;
		}
		file.close();
	}

	std::cout << "done initializing" << std::endl << std::endl;
}

int askPlayerSize() {
	int size = 0;

	std::cout << "Vul in hoeveel spelers deze game gaat hebben:" << std::endl;
	std::cin >> size;

	if (size < 2) {
		std::cin.clear();
		std::cin.ignore(10000, '\n');

		std::cout << "te weinig spelers" << std::endl << std::endl;
		return askPlayerSize();
	}

	return size;
}

std::vector<User> initUsers(int size) {
	std::vector<User> users = std::vector<User>();
	users.reserve(size);

	std::cin.clear();
	std::cin.ignore(10000, '\n');

	for (int i = 0; i < size; i++) {
		std::cout << "Wat is de naam van speler " << i + 1 << std::endl;

		std::string name;
		std::getline(std::cin, name);
		users.push_back(User(name));
	}

	return users;
}

void finishGame(std::vector<User>& users, std::string& word) {
	std::cout << "de word was: " << word << std::endl << std::endl;
	std::sort(users.begin(), users.end());

	for (int i = 0; i < (int) users.size(); i++) {
		std::cout
			<< i + 1
			<< ". "
			<< users[i].getName()
			<< " - "
			<< users[i].getPoints()
			<< (users[i].getPoints() == 1 ? " punt" :" punten")
			<< std::endl;
	}
}

std::string getPlayWord(std::string& word) {
	std::string playWord = "";

	for (int i = 0; i < (int) word.size(); i++) {
		playWord += "-";
	}

	return playWord;
}

bool find(std::string& word, std::string& playWord, char& letter) {
	std::vector<int> characterLocations;
	for (int i = 0; i < (int) word.size(); i++)
		if (word[i] == letter)
			characterLocations.push_back(i);

	if (characterLocations.empty()) {
		std::cout << "De letter \'" << letter << "\' bestaat niet in deze zin" << std::endl << std::endl;

		return true; // the player guessed wrong
	}

	std::cout << "De letter \'" << letter << "\' is " << characterLocations.size() << " keer gevonden" << std::endl << std::endl;
	for (int& position : characterLocations) {
		playWord[position] = word[position];
	}

	return false; // the player didn't guess wrong
}

void playGame(std::vector<User>& users, std::string& word) {
	bool gameFinished = false;
	std::string guessedChars;
	srand((unsigned int) time(NULL));
	word = words[rand() % words.size()];
	std::string playWord = getPlayWord(word);

	while (!gameFinished)
	{
		for (User& user : users)
		{
			bool guessedWrong = false;

			while (!guessedWrong && !gameFinished)
			{
				std::cout << std::endl << "Geraden letters: ";
				for (char& letter : guessedChars) {
					std::cout << letter << " ";
				}
				std::cout << std::endl;

				std::cout << "de word is: " << playWord;
				std::cout << std::endl
					<< "het is de beurt van: "
					<< user.getName()
					<< std::endl
					<< std::endl
					<< "wat is je gok: ";

				char guess[1];
				std::cin >> guess[0];
				std::cin.clear();
				std::cin.ignore(10000, '\n');

				if (guessedChars.find(guess[0]) != std::string::npos) {
					std::cout << "De letter \'" << guess[0] << "\' is al geraden" << std::endl;
					continue;
				}

				guessedChars += guess[0];
				guessedWrong = find(word, playWord, guess[0]);

				if (!guessedWrong) {
					user.addPoint();

					if (playWord.find('-') == std::string::npos) {
						gameFinished = true;
					}
				}
			}
		}
	}
}

int main()
{
	initWords();
	const int size = askPlayerSize();
	std::vector<User> users = initUsers(size);
	std::string word;
	playGame(users, word);
	finishGame(users, word);

	return 0;
}
