#include <iostream>
#include <fstream>
#include <string>
#include <random>

using namespace std;

// Prototypes
bool isAlphaOnly(string);

class Wordle {
public:
	string targetWord;
	string userGuess;
	string response;
	int remainingGuesses = 6;
	bool gameOver = false;

	Wordle(string targetWord) {
		this->targetWord = targetWord;
	}

	void printGreeting() {
		cout << "Welcome to Worlde!" << endl;
		cout << "Try to guess the 5-letter word within 6 guesses" << endl;
		cout << "O - correct letter in correct spot" << endl;
		cout << "+ - correct letter in wrong spot" << endl;
		cout << "X - wrong letter" << endl;
		cout << "-----------------------------------------------" << endl;
	}

	// Prompt user to input their guess
	string getUserGuess() {
		string userGuess;
		bool invalidInput = true;
		int guessCount = 7 - this->remainingGuesses;
		do {
			cout << "Guess " << guessCount << "/6" << endl;
			cout << "-----" << endl;
			cin >> userGuess;
			if (userGuess.length() != 5 || !isAlphaOnly(userGuess)) {
				cout << "Please enter a 5-letter word" << endl;
				cout << "----------------------------" << endl;
			}
			else
				invalidInput = false;
		} while (invalidInput);

		// Convert input to lowercase
		for (int i = 0; i < userGuess.length(); i++) {
			userGuess[i] = tolower(userGuess[i]);
		}
		this->userGuess = userGuess;
		return userGuess;
	}

	// Compares the user's guess to the answer
	string checkGuess() {
		string userGuess = this->userGuess;
		string targetWord = this->targetWord;
		string response;

		for (int i = 0; i < userGuess.length(); i++) {
			for (int j = 0; j < targetWord.length(); j++) {
				// Checks for matching letters
				if (userGuess[i] == targetWord[j]) {
					if (i == j)
						response.append("O");
					else
						response.append("+");
					break;
				}
				// If no matches in whole word, append X
				if (j == targetWord.length() - 1)
					response.append("X");
			}
		}

		cout << response << endl;
		cout << "-----" << endl;
		this->response = response;
		return response;
	}

	bool isCorrectGuess() {
		if (this->userGuess == this->targetWord)
			return true;
		return false;
	}

	void endGame() {
		this->gameOver = true;
		cout << "Game Over" << endl;
		cout << "The answer is: " << this->targetWord << endl;
	}

	void checkWin() {
		if (isCorrectGuess()) {
			this->gameOver = true;
			cout << "Correct!" << endl;
		}
	}

	void decrementRemainingGuesses() {
		this->remainingGuesses--;
	}

	void setUserGuess(string userGuess) {
		this->userGuess = userGuess;
	}

	void setResponse(string response) {
		this->response = response;
	}
};

// Checks if a string only contains alphabetical letters
bool isAlphaOnly(string s) {
	for (char c : s) {
		if (!isalpha(c)) {
			return false;
		}
	}
	return true;
}

// Main game loop
void wordleGame() {
	ifstream wordFile("word-list.txt");
	if (!wordFile) {
		cout << "Error: Unable to open file" << endl;
		exit(1);
	}
	srand(time(NULL));
	const int FILE_LINES = 400; // Number of lines in the file
	const int LINE = rand() % FILE_LINES + 1;  // Choose a random line to get

	string targetWord;
	for (int i = 1; i <= LINE; i++)
		getline(wordFile, targetWord);
	wordFile.close();

	Wordle wordle(targetWord);
	wordle.printGreeting();
	while (!wordle.gameOver) {
		wordle.getUserGuess();
		wordle.checkGuess();
		wordle.checkWin();
		wordle.decrementRemainingGuesses();
		if (wordle.remainingGuesses <= 0)
			wordle.endGame();
	}
}

int main() {
	wordleGame();
	return 0;
}