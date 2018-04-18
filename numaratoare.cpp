// Copyright 2018 Cretu Diana

#include <fstream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <iostream>
#include <climits>
using namespace std;

class Numaratoare {
 public:
	void solve() {
		read_input();
		print_output(get_result());
	}

 private:
	int s, nr_elemente, indx;
	vector<vector<int> > posibilitati;
	vector<int> v;

	void read_input() {
		ifstream fin("numaratoare.in");
		fin >> s;
		fin >> nr_elemente;
		fin >> indx;
		fin.close();
	}

	int nr_sol = 0;
	bool exit_back = false;

	// Genereaza solutiile
	void back(int k, int elem_anterior, int sum, int n) {
		if ( sum < n )
			return;
		for (int i = min(sum - n + k + 1, elem_anterior); i > 0; i --) {
			v.push_back(i);
			if ( k == nr_elemente - 1 ) {
				if ( sum - i == 0 ) {
					nr_sol ++;
					if ( nr_sol - 1 == indx ) {
						exit_back = true;
					}
				}
			} else {
				back(k + 1, i, sum - i, n - 1);
			}
			if ( exit_back )
				return;
			v.pop_back();
		}
	}

	bool get_result() {
		back(0, s, s, nr_elemente);
		return exit_back;
	}

	void print_output(int result) {
		ofstream fout("numaratoare.out");
		if (result) {
			fout << s << "=" << v[0];
			for ( int i = 1; i < nr_elemente; i++ ) {
				fout << "+" << v[i];
			}
		} else {
			fout << "-";
		}
		fout.close();
	}
};

int main() {
	Numaratoare f;
	f.solve();
	return 0;
}
