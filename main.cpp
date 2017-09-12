#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <stack>
#include <time.h>
#include <chrono>

using namespace std;

void hop3(stack<int> &st, stack<int> &p1, stack<int> &p2, stack<int> &des, int n, ofstream& file, int &movesCounter, int *pegs);
void hop2(stack<int> &st, stack<int> &p1, stack<int> &des, stack<int> &sh, int n, ofstream& file, int &movesCounter, int *pegs);
void hop1(stack<int> &st, stack<int>&des, ofstream& file, int &movesCounter, int *pegs);
string getName(stack<int> &peg, int* pegs);

int main() {
	int nm = 0; // number of moves for each case
	stack <int> start, aux1, aux2, aux3, aux4, dest;
	int pegs[6] = { (int)&start, (int)&aux1, (int)&aux2, (int)&aux3, (int)&aux4, (int)&dest };
	ofstream fout;
	fout.open("HanoiOutput.txt");
	for (int i = 1; i <= 10; i++) {
		fout << "Runing solution for " << i << " disks." << endl;
		for (int j = i; j > 0; j--)
			start.push(j);
		auto timeStart = std::chrono::system_clock::now();
// Step 1:
		for (int j = 0; j < i; j++) {
			hop1(start, aux1, fout, nm, pegs); //feed in 1 disk to the loop
			int n = j + 1; //real time number of disks inside the loop
			if (n == 1)
				hop3(aux1, aux2, aux3, aux4, n, fout, nm, pegs);
			else if (n > 1) {
				hop1(aux1, aux2, fout, nm, pegs);
				hop1(aux2, aux3, fout, nm, pegs);
				hop2(aux4, aux1, aux2, aux3, n - 1, fout, nm, pegs);
				hop1(aux3, aux4, fout, nm, pegs);
				hop2(aux2, aux3, aux4, aux1, n - 1, fout, nm, pegs);
			}
		}
// Step 2:
		int n = i;
		while (n > 0) {
			hop2(aux4, aux1, aux2, aux3, n - 1, fout, nm, pegs);
			hop1(aux4, dest, fout, nm, pegs);
			hop2(aux2, aux3, aux4, aux1, n - 1, fout, nm, pegs);
			n--;
		}
		fout << "Final destination disks: ";
		while (!dest.empty()) {
			fout << dest.top() << " ";
			dest.pop();
		}
		auto timeEnd = std::chrono::system_clock::now();
		auto elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(timeEnd - timeStart);

		fout << endl << "Number of moves: " << nm << endl;
		fout << "Time to solve: " << elapsed.count() << " nanoseconds.";
		fout << endl << "---------------------------------------" << endl;
		nm = 0;
	}
	fout.close();
	return 0;
}

void hop3(stack<int> &st, stack<int> &p1, stack<int> &p2, stack<int> &des, int n, ofstream& file, int &movesCounter, int *pegs) {
	if (n == 1) {
		hop1(st, p1, file, movesCounter, pegs);
		hop1(p1, p2, file, movesCounter, pegs);
		hop1(p2, des, file, movesCounter, pegs);
	}
	else if (n > 1) {
		hop3(st, p1, p2, des, n - 1, file, movesCounter, pegs);
		hop1(st, p1, file, movesCounter, pegs);
		hop1(p1, p2, file, movesCounter, pegs);
		hop2(des, st, p1, p2, n - 1, file, movesCounter, pegs);
		hop1(p2, des, file, movesCounter, pegs);
		hop2(p1, p2, des, st, n - 1, file, movesCounter, pegs);
	}
	else return;
}

void hop2(stack<int> &st, stack<int> &p1, stack <int> &des, stack<int> &sh, int n, ofstream& file, int &movesCounter, int *pegs) {
	if (n == 1) {
		hop1(st, p1, file, movesCounter, pegs);
		hop1(p1, des, file, movesCounter, pegs);
	}
	else if (n > 1) {
		hop3(st, p1, des, sh, n - 1, file, movesCounter, pegs);
		hop1(st, p1, file, movesCounter, pegs);
		hop1(p1, des, file, movesCounter, pegs);
		hop3(sh, st, p1, des, n - 1, file, movesCounter, pegs);
	}
	else return;
}

void hop1(stack<int> &st, stack<int> &des, ofstream& file, int &movesCounter, int *pegs) {
		file << "Move " << st.top() << " from " << getName(st, pegs) << " to " << getName(des, pegs) << endl;
		des.push(st.top());
		st.pop();
		movesCounter++;
}


string getName(stack<int> &peg, int* pegs) {
	if ((int)&peg == pegs[0])
		return "Start";
	else if ((int)&peg == pegs[1])
		return "Aux1";
	else if ((int)&peg == pegs[2])
		return "Aux2";
	else if ((int)&peg == pegs[3])
		return "Aux3";
	else if ((int)&peg == pegs[4])
		return "Aux4";
	else
		return "Destination";
}