#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <ctime>
#include <algorithm>
#include <cstdlib>

using namespace std;

//Function Prototypes
int scanWord(string correctWord, char userLetter);
string findEasy(int randNum);
string findInter(int randNum);
string findHard(int randNum);
string makeUser();
int saveUser();
int retrieveUser();
void savePoints(int point, string user);

//IO Streams
ifstream inStreamEasy, inStreamHard, inStreamInter, inStreamUser, inStreamUpdated;
ofstream outStreamUser, outStreamUpdated;

//Variables
string guessingWord, word, userGuess, username, user, name, pointString, mode;
int lineNum, guess1, guess2, guess3, guess4, guess5, randomNumber, accountDecision, score, points, point;
bool correctCharactersUsername, correctStartUsername;
char playAgain;

int startingScore = 0;
char won = 0;
int loopedAlready = 0;

//Vectors
vector <string> dataVector;
vector<char> alpha{ 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z' };
vector<char> alphaSecond{ 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z' };

int main()
{
	cout << "Welcome to Wordle!!" << endl;
	cout << "Guess the five-letter word correctly within 6 tries." << endl;
	cout << "Enter your words in ALL LOWERCASE." << endl;
	cout << endl;
	cout << "KEYS:" << endl;
	cout << "GREEN - letter is in correct spot." << endl;
	cout << "YELLOW - letter exists in the word, but in a different spot." << endl;
	cout << "RED - letter doesn't exist in the word." << endl;
	cout << endl;
	cout << "Type '1' to resume where you left off. Type '2' to make a new account/start over." << endl;
	cin >> accountDecision;
	cout << endl;

	if (accountDecision == 2)
	{
		score = saveUser();
	}
	if (accountDecision == 1)
	{
		score = retrieveUser();
		if (score == 1000)
		{
			cout << "Username not found! Wordle is closing..." << endl;
			return 1;
		}
	}

	do
	{
		inStreamEasy.open("wordsLibraryEasy.txt");
		inStreamInter.open("wordsLibraryIntermediate.txt");
		inStreamHard.open("wordsLibraryHard.txt");

		if (loopedAlready > 0)
		{
			cout << username << " has " << score << " points." << endl;
			alpha = alphaSecond;
		}

		if (score >= 0 && score <= 2)
			mode = "easy";
		if (score >= 3 && score <= 5)
			mode = "inter";
		if (score >= 6 && score <= 8)
			mode = "hard";
		if (score >= 9)
			mode = "beat";

		if (mode == "easy")
		{
			srand(time(0));
			randomNumber = (rand() % 480) + 1;
		}
		if (mode == "inter" || mode == "hard")
		{
			srand(time(0));
			randomNumber = (rand() % 250) + 1;
		}

		if (mode == "easy")
		{
			guessingWord = findEasy(randomNumber);
			cout << "Level: Easy" << endl;
		}
		if (mode == "inter")
		{
			guessingWord = findInter(randomNumber);
			cout << "Level: Intermediate" << endl;
		}
		if (mode == "hard")
		{
			guessingWord = findHard(randomNumber);
			cout << "Level: Hard" << endl;
		}
		if (mode == "beat")
		{
			cout << "You beat the game!" << endl;
			inStreamHard.close();
			inStreamEasy.close();
			inStreamInter.close();
			break;
		}
		for (int i = 0; i < 6; i++)
		{
			cout << "Enter your Guess Word #" << (i + 1) << ": ";
			cin >> userGuess;
			for (int z = 0; z < 5; z++)
			{
				for (int k = 0; k < alpha.size(); k++)
				{
					if (alpha[k] == userGuess[z])
						alpha.erase(alpha.begin() + k);
				}
			}

			for (int j = 0; j < 5; j++)
			{
				if (userGuess[j] == guessingWord[j])
				{
					if (j == 0)
						guess1 = 1;
					if (j == 1)
						guess2 = 1;
					if (j == 2)
						guess3 = 1;
					if (j == 3)
						guess4 = 1;
					if (j == 4)
						guess5 = 1;
				}
				if (userGuess[j] != guessingWord[j])
				{
					if (j == 0)
						guess1 = scanWord(guessingWord, userGuess[j]);
					if (j == 1)
						guess2 = scanWord(guessingWord, userGuess[j]);
					if (j == 2)
						guess3 = scanWord(guessingWord, userGuess[j]);
					if (j == 3)
						guess4 = scanWord(guessingWord, userGuess[j]);
					if (j == 4)
						guess5 = scanWord(guessingWord, userGuess[j]);
				}
			}
			char c1 = userGuess[0];
			char c2 = userGuess[1];
			char c3 = userGuess[2];
			char c4 = userGuess[3];
			char c5 = userGuess[4];

			//Letter 1
			if (guess1 == 1)
				std::cout << "\033[42m" << c1 << "\033[0m" << " ";
			else if (guess1 == 2)
				std::cout << "\033[43m" << c1 << "\033[0m" << " ";
			else
				std::cout << "\033[41m" << c1 << "\033[0m" << " ";

			//Letter 2
			if (guess2 == 1)
				std::cout << "\033[42m" << c2 << "\033[0m" << " ";
			else if (guess2 == 2)
				std::cout << "\033[43m" << c2 << "\033[0m" << " ";
			else
				std::cout << "\033[41m" << c2 << "\033[0m" << " ";

			//Letter 3
			if (guess3 == 1)
				std::cout << "\033[42m" << c3 << "\033[0m" << " ";
			else if (guess3 == 2)
				std::cout << "\033[43m" << c3 << "\033[0m" << " ";
			else
				std::cout << "\033[41m" << c3 << "\033[0m" << " ";

			//Letter 4
			if (guess4 == 1)
				std::cout << "\033[42m" << c4 << "\033[0m" << " ";
			else if (guess4 == 2)
				std::cout << "\033[43m" << c4 << "\033[0m" << " ";
			else
				std::cout << "\033[41m" << c4 << "\033[0m" << " ";

			//Letter 5
			if (guess5 == 1)
				std::cout << "\033[42m" << c5 << "\033[0m";
			else if (guess5 == 2)
				std::cout << "\033[43m" << c5 << "\033[0m";
			else
				std::cout << "\033[41m" << c5 << "\033[0m";

			cout << endl;
			cout << endl;
			cout << "LETTER BOARD:" << endl;
			for (int z = 0; z < alpha.size(); z++)
				cout << alpha[z] << " ";
			cout << endl;
			cout << endl;

			if (guess1 == 1 && guess2 == 1 && guess3 == 1 && guess4 == 1 && guess5 == 1)
			{
				cout << "Congratulations! You guessed the word!" << endl;
				score++;
				won = 1;
				break;
			}
			won = 0;
		}
		if (won == 0)
		{
			cout << "You're out of guesses!" << endl;
			cout << "The correct word was '" << guessingWord << "'" << endl;
			if (score > 0)
				score--;
		}
		savePoints(score, username);

		cout << "Would you like to play again? (type 'y' for yes or 'n' for no): ";
		cin >> playAgain;
		cout << endl;

		inStreamEasy.close();
		inStreamInter.close();
		inStreamHard.close();
		alpha.clear();
		loopedAlready++;

	} while (playAgain == 'y');

	cout << "Wordle is closing..." << endl;
	return 0;
}

//Scans correctWord to see if userletter is used or not. Returns 2 if letter is used and 0 if not used
int scanWord(string correctWord, char userLetter)
{
	for (int i = 0; i < 5; i++)
	{
		if (correctWord[i] == userLetter)
			return 2;
	}
	return 0;
}

//Accesses "wordLibraryEasy.txt" and searches for the line corresponding to randNum. Returns the word on that line
string findEasy(int randNum)
{
	while (!inStreamEasy.eof())
	{
		inStreamEasy >> lineNum >> word;
		if (lineNum == randNum)
			return word;
	}
}
//Accesses "wordLibraryHard.txt" and searches for the line corresponding to randNum. Returns the word on that line
string findHard(int randNum)
{
	while (!inStreamHard.eof())
	{
		inStreamHard >> lineNum >> word;
		if (lineNum == randNum)
			return word;
	}
}

//Accesses "wordLibraryIntermediate.txt" and searches for the line corresponding to randNum. Returns the word on that line
string findInter(int randNum)
{
	while (!inStreamInter.eof())
	{
		inStreamInter >> lineNum >> word;
		if (lineNum == randNum)
			return word;
	}
}

//Asks user for a username and checks if it's valid. Loops until it is valid. Returns username if it's valid.
string makeUser()
{
	do
	{
		correctCharactersUsername = true;
		correctStartUsername = true;

		cout << "Enter a username: ";
		cin >> username;
		for (int i = 0; i < username.length(); i++)
		{
			if (isalnum(username[i]) == false)
				correctCharactersUsername = false;
		}
		if (isalpha(username[0]) == false)
			correctStartUsername = false;

		if (!correctCharactersUsername || !correctStartUsername)
			cout << "INVALID USERNAME! Username contains characters other than letters or numbers or starts with a number." << endl;

	} while (!correctCharactersUsername || !correctStartUsername);

	return username;
}

//Calls on makeUser and saves the username in "usernames.txt". Returns the score of the new account which is 0.
int saveUser()
{
	outStreamUser.open("usernames.txt");
	username = makeUser();
	outStreamUser << username << " " << startingScore << endl;
	score = startingScore;
	cout << username << " has " << score << " points." << endl;
	outStreamUser.close();
	return score;
}

//Asks user for their existing username and returns the score associated with it. If the username can't be found, it informs the user and exits the program.
int retrieveUser()
{
	inStreamUpdated.open("fileout.txt");
	cout << "Enter your username: ";
	cin >> username;
	while (inStreamUpdated >> user)
	{
		inStreamUpdated >> points;
		if (user == username)
		{
			score = points;
			cout << username << " has " << score << " points." << endl;
			inStreamUpdated.close();
			return score;
		}
	}
	inStreamUpdated.close();
	return 1000;
}

//Creates a vector of the user's username (user) and updated score (point), and saves it in "fileout.txt".
void savePoints(int point, string user)
{
	inStreamUser.open("usernames.txt");
	outStreamUpdated.open("fileout.txt");
	string nameReplace = user;
	int pointsNew = point;
	while (inStreamUser >> name)
	{
		inStreamUser >> point;
		if (name == nameReplace)
			point = pointsNew;
		pointString = to_string(point);
		dataVector.push_back(name + " " + pointString);
	}
	inStreamUser.close();
	for (int i = 0; i < dataVector.size(); i++)
		outStreamUpdated << dataVector[i] << endl;
	dataVector.clear();
	outStreamUpdated.close();
}