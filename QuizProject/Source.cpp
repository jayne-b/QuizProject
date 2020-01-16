#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <iterator>
#include <algorithm>
#include "Question.h"
#include <time.h>
#include <random>

using namespace std;

void printMenu();

int main() {
	auto choice = 0, answer = 0, score = 0;
	string q, ans, corr, quit;
	vector<Question> questions;
	vector<string> answers;
	fstream file;
	bool saved = false;
	cout << "Welcome to the quiz program" << endl;
	do {
		printMenu();
		while (!(cin >> choice)) {
			cout << "Please enter a number." << endl;
			cin.clear();
			cin.ignore(123, '\n');
			printMenu();
		}
		switch (choice) {
		case 1:
			questions.clear();
			break;
		case 2:
			cin.ignore();
			answers.clear();
			do {
				cout << "Enter question: ";
				getline(cin, q);
			} while (q.length() < 1);
			for (int i = 1; i < 5; i++) {
				do {
					cout << "Enter answer " << i << ": ";
					getline(cin, ans);
				} while (ans.length() < 1);
				answers.push_back(ans);
			}
			do {
				cout << "\n" << q << endl;
				for (auto& a : answers) {
					cout << a << "\n";
				}
				cout << "Enter correct answer: ";
				cin >> answer;
				if (answer > 0 && answer < 5) { corr = answers[answer - 1]; }
				else { cout << "\nEnter a number between 1 and 4"; }
			} while (answer < 1 || answer >4);
			questions.emplace_back(Question(q, answers, corr));
			break;
		case 3:
			file.open("questions.txt", ios::in | ios::app);
			if (file.is_open()) {
				questions.erase(remove_if(questions.begin(), questions.end(), [](auto& q) {return q.getSaved();}), questions.end());
				Question q;
				while (file >> q) { q.setSaved(true); questions.push_back(q); }
			}
			else { cout << "File not opened" << endl; }
			file.close();
			break;
		case 4:
			file.open("questions.txt", ios::out | ios::app);
			if (file.is_open()) {
				for (auto& q : questions)
					if (q.getSaved() != true) {
						q.setSaved(true); file << q << endl;
					}
			}
			else { cout << "File not opened" << endl; }
			file.close();
			break;
		case 5:
			score = 0;
			if (questions.empty() || questions.size() < 5) { cout << "There are not enough questions to play" << endl; }
			else {
				shuffle(questions.begin(), questions.end(), random_device());
				for (int i = 0;i < 5;i++) {
					if (questions[i].play()) {
						cout << "Well done, that answer was correct!\n" << endl;
						score++;
					}
					else {
						cout << "Sorry, that was the wrong answer.\n" << endl;
					}
				}
				cout << "You scored " << score << " out of 5" << endl;
			}
			break;
		case 6:
			cout << "\nLIST OF QUESTIONS:" << endl;
			for (auto i = 0; i < questions.size(); i++) { cout << i + 1 << ". " << questions[i].getQ() << endl; }
			cout << endl;
			break;
		case 7:
			for (auto i = 0; i < questions.size(); i++) {
				if (questions[i].getSaved() == false) {
					cout << "You have unsaved questions. Would you still like to quit? ";
					cin >> quit;
					transform(quit.begin(), quit.end(), quit.begin(), [](unsigned char c) { return tolower(c); });
					if ((quit.compare("n") == 0) || (quit.compare("no") == 0)) { choice = 0; }

				}
			}
			break;
		}
	} while (choice != 7);
}

void printMenu() {
	cout << "\n1. Clear all questions" << endl;
	cout << "2. Add a new question" << endl;
	cout << "3. Load questions from file" << endl;
	cout << "4. Save questions to file" << endl;
	cout << "5. Take quiz" << endl;
	cout << "6. Print all questions" << endl;
	cout << "7. Quit" << endl;
	cout << "Make a choice: ";
}
