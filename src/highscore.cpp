#include "highscore.h"

std::vector<int> m_highscore_scores = {0, 0, 0};
bool m_highscore_read_already = false;
const int amountOfLevels = 3; // TODO
const char* fileName = "sc.dat";

int getHighScore(int levelIndex)
{
	if (!m_highscore_read_already)
		m_highscore_readFile();

	return m_highscore_scores.at(levelIndex);
}

bool setHighScore(int levelIndex, int score)
{
	if (m_highscore_scores.size() > levelIndex)
	{
		if (m_highscore_scores.at(levelIndex) < score)
		{
			m_highscore_scores[levelIndex] = score;
			m_highscore_saveFile();
			return true;
		}
	} // else
	return false;
}

void m_highscore_readFile()
{
	std::ifstream scoreFile(fileName);

	if (scoreFile.is_open())
	{
		int i = 0;
		while (scoreFile && i < amountOfLevels) {
			int score = 0;
			scoreFile.read(reinterpret_cast<char*>(&score), 4);
			m_highscore_scores[i] = score;
			i++;
		}
	}
	else
	{
		std::cout << "Unable to read high score or file not found!" << "\n";
	}

	scoreFile.close();
	m_highscore_read_already = true;
}

void m_highscore_saveFile()
{
	// overwrite previous save file
	std::ofstream scoreFile(fileName, std::ios::trunc);

	if (scoreFile.is_open())
	{
		if (scoreFile) {
			for (int score : m_highscore_scores)
			{
				scoreFile.write(reinterpret_cast<char*>(&score), 4);
			}
		}
	}
	else
	{
		std::cout << "Unable to save file!" << "\n";
	}
	scoreFile.close();
}