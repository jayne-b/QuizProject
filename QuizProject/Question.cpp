#include "Question.h"

bool Question::play() {
	vector<string> t_answers(m_answers);
	int corrA = 0;
	cout << m_question << endl;
	do {
		t_answers = m_answers;
		int randA = rand() % 4;
		t_answers.erase(t_answers.begin() + randA);
	} while (find(t_answers.begin(), t_answers.end(), m_correct) == t_answers.end());
	shuffle(t_answers.begin(), t_answers.end(), random_device());
	for (int i = 1; i < 4; i++) {
		cout << i << ". " << t_answers[i - 1] << endl;
	}
	do {
		cout << "Choose an answer: ";
		cin >> corrA;
		if (corrA > 0 && corrA < 4) {
			if (t_answers[corrA - 1] == m_correct) { return true; }
			else { return false; }
		}
	} while (corrA < 1 || corrA >3);
	return false();
}
