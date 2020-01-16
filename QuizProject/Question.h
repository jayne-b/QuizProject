#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <iterator>
#include <algorithm>
#include <random>

using namespace std;

class Question {
	friend std::ostream& operator <<(std::ostream& os, const Question& q)
	{
		os << q.m_question << "\n";
		copy(q.m_answers.begin(), q.m_answers.end(), ostream_iterator<string>(os, "\n"));
		os << q.m_correct;
		return os;
	}
	friend std::istream& operator >>(std::istream& is, Question& q)
	{
		getline(is, q.m_question);
		for (auto& a : q.m_answers) { getline(is, a); }
		getline(is, q.m_correct);
		return is;
	}
public:
	Question(string q = "", vector<string> a = { 4, "" }, string corr = "", bool saved = false) : m_question{ q }, m_answers{ a }, m_correct{ corr }, m_saved{ saved }{};
	~Question() { };
	bool play();
	string getQ() { return m_question; }
	bool getSaved() { return m_saved; }
	void setSaved(const bool saved) { m_saved = saved; }
private:
	string m_question, m_correct;
	vector<string> m_answers;
	bool m_saved;

};
