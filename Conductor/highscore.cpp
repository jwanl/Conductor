#include "highscore.h"

int HighScore::getHighScore(int levelIndex)
{
	if (!m_read_already) 
		readFile();

	return m_scores.at(levelIndex);
}

bool HighScore::setHighScore(int levelIndex, int score)
{
	if (m_scores.size() > levelIndex)
	{
		if (m_scores.at(levelIndex) < score)
		{
			m_scores[levelIndex] = score;
			saveFile();
			return true;
		}
	} // else
	return false;
}

void HighScore::readFile()
{
	std::ifstream scoreFile(fileName);

	if (scoreFile.is_open())
	{
		while (scoreFile) {
			int score = 0;
			scoreFile >> std::hex >> score;
		}
	}
	else
	{
		// if read fails, create vector of zeroes
		for (int i = 0; i < amountOfLevels; i++)
			m_scores.push_back(0);

		std::cout << "Unable to read high score or file not found!" << "\n";
	}

	scoreFile.close();
}

void HighScore::saveFile()
{
	// overwrite previous save file
	std::ofstream scoreFile(fileName, std::ios::trunc);

	if (scoreFile.is_open())
	{
		while (scoreFile) {
			for (int score : m_scores)
			{
				scoreFile << std::hex << score;
			}
		}
	}
	else
	{
		std::cout << "Unable to save file!" << "\n";
	}
}