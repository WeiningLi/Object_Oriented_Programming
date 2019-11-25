#include <iostream>
#include <sstream>
#include <string>
#include <utility>
#include "mastermind.h"
using namespace std;

Mastermind::Mastermind(int seed, int codeLength, int guessLimit) : seed{ seed }, codeLength{ codeLength }, guessLimit{ guessLimit } {}

Mastermind::~Mastermind() {}

int whitePegs(string password, string guess, int len) {
	int count = 0;
	string wrongPass = "";
	string wrongGuess = "";
	for (int index = 0; index < len; ++index) {
		if (password[index] != guess[index]) {
			wrongPass += password[index];
			wrongGuess += guess[index];
		}
	}
	int newLen = wrongPass.length();
	int guessLen = wrongGuess.length();
	for (int i = 0; i < newLen; ++i) {
		for (int j = 0; j < guessLen; ++j) {
			if (wrongPass[i] == wrongGuess[j]) {
				++count;
				wrongGuess.erase(j, 1);
				guessLen = wrongGuess.length();
				break;
			}
		}
	}
	return count;
}

int blackPegs(string password, string guess, int len) {
	int count = 0;
	for (int index = 0; index < len; ++index) {
		if (password[index] == guess[index]) {
			++count;
		}
	}
	return count;
}

void Mastermind::playGame() {
	string  password = "";
	for (int len = 0; len < codeLength; ++len) {
		password += genCodeChar();
	}
	cout << "Welcome to Mastermind! Please enter your first guess:" << endl;
	int round = 0;
	while (round < guessLimit) {
		++round;
		string myGuess = "";
		int acceptedCode = 0;
		char curr;
		while (acceptedCode < codeLength) {
			cin >> curr;
			if (curr == 'a' || curr == 'A') {
				myGuess += "A";
				++acceptedCode;
			}
			else if (curr == 'b' || curr == 'B') {
				myGuess += "B";
				++acceptedCode;
			}
			else if (curr == 'c' || curr == 'C') {
				myGuess += "C";
				++acceptedCode;
			}
			else if (curr == 'd' || curr == 'D') {
				myGuess += "D";
				++acceptedCode;
			}
			else if (curr == 'e' || curr == 'E') {
				myGuess += "E";
				++acceptedCode;
			}
			else if (curr == 'f' || curr == 'F') {
				myGuess += "F";
				++acceptedCode;
			}
		}
		int white = whitePegs(password, myGuess, codeLength);
		int black = blackPegs(password, myGuess, codeLength);
		cout << black << "b," << white << "w" << endl;
		if (password == myGuess) {
			cout << "You won in " << round << " guesses!" << endl;
			cout << "Would you like to play again? (Y/N):" << endl;
			while (cin >> curr) {
				if (curr == 'N' || curr == 'n') return;
				else if (curr == 'Y' || curr == 'y') {
					playGame();
				}
			}
		}
		else if ((guessLimit - round) > 0) {
			int left = guessLimit - round;
			cout << left << " guesses left. Enter guess:" << endl;
		}
		else if ((guessLimit - round) == 0) {
			cout << "You lost! The password was: " << password << endl;
			cout << "Would you like to play again? (Y/N):" << endl;
			while (cin >> curr) {
				if (curr == 'N' || curr == 'n') return;
				else if (curr == 'Y' || curr == 'y') {
					playGame();
				}
			}
		}
	}
}

