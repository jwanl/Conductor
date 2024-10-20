#pragma once

#include <vector>
#include <fstream>
#include <iostream>

namespace HighScore {

	const int amountOfLevels = 3; // TODO
	const char* fileName = "sc.dat";

	/* When this is ran for the first time, file is read */
	int getHighScore(int levelIndex);

	/* Returns true if score was set (bigger than previous score) and false otherwise */
	bool setHighScore(int levelIndex, int score);

	void readFile();

	void saveFile();

	std::vector<int> m_scores;

	bool m_read_already = false;

}