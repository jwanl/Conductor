#pragma once

#include <vector>
#include <fstream>
#include <iostream>

/* When this is ran for the first time, file is read */
int getHighScore(int levelIndex);

/* Returns true if score was set (bigger than previous score) and false otherwise */
bool setHighScore(int levelIndex, int score);

void m_highscore_readFile();

void m_highscore_saveFile();