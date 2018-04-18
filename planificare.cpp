// Copyright 2018 Cretu Diana

#include <fstream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <iostream>
#include <climits>
using namespace std;

class Planificare {
 public:
	void solve() {
		read_input();
		print_output(get_result());
	}

 private:
	int nr_P, B, D;
	vector<int> P;

	void read_input() {
		ifstream fin("planificare.in");
		int proba;
		fin >> nr_P >> D >> B;
		for (int i = 0; i < nr_P; i ++) {
			fin >> proba;
			P.push_back(proba);
		}
		fin.close();
	}

	pair<long long, int> get_result() {
		long long dp[nr_P][nr_P];
		// Caz de baza, pe prima linie vom trata cazul in care
		// fiecare proba este in cate un concurs
		for (int i = 0; i < nr_P - 1; i ++) {
			dp[0][i] = (D - P[i])*(D - P[i])*(D - P[i]);
		}
		dp[0][nr_P - 1] = 0;
		// Construiesc matricea
		int nr_linii = 0;
		for (int i = 1; i < nr_P; i ++) {
			// Numar cate maximuri am pe o linie cu variabila invalid
			long long invalid = 0;
			for (int j = 0; j < nr_P; j ++) {
				long long suma = 0;
				if (j < i) {
					// Nu exista suficiente probe pentru a le pune in concurs
					// inainte de proba[j]
					dp[i][j] = LONG_MAX;
					invalid++;
				} else {
					// Suma celor i probe de dinaintea probei[j] inclusiv
					// pentru a le pune pe toate intr-un concurs
					for (int k = j; k >= j - i; k --) {
						suma += P[k];
					}
					dp[i][j] = (D - suma - B * i)
						*(D - suma - B * i)
							*(D - suma - B * i);
					// Cazul in care pierderile sunt negative, inseamna ca nu
					// au incaput toate in acelasi concurs
					if (dp[i][j] < 0) {
						dp[i][j] = LONG_MAX;
						invalid ++;
					} else {
						// Daca ne aflam la ultimul concurs, nu exista pierderi
						if (j == nr_P - 1) {
							dp[i][j] = 0;
						}
					}
				}
			}
			// Cand exista o linie doar cu numere prea mari, nu mai are rost sa
			// parcurg mai departe matricea, deoarece liniile care vor urma,
			// vor fi automat la fel
			if (invalid == nr_P) {
				nr_linii = i;
				break;
			}
		}
		vector<int> concurs(nr_P);
		concurs[0] = 1;
		for (int j = 1; j < nr_P; j ++) {
			// Minimul va fi initializat cu suma dintre minimul de la pasul
			// precedent si pierderea daca proba de la acest pas ar fi intr-un
			// concurs
			long long min = dp[0][j] + dp[0][j - 1];
			// Asadar, la numarul de concursuri pe care il aveam inainte se
			// adauga un singur concurs, iar noul rezultat se salveaza pe
			// pozitia curenta din vectorul concurs
			concurs[j] = concurs[j - 1] + 1;
			// Verificam daca exista alta solutie mai optima
			for (int i = 1; i < nr_linii; i ++) {
				if (j - (i + 1) >= 0) {
					if (dp[i][j] != LONG_MAX &&
							min > dp[i][j] + dp[0][j - (i + 1)]) {
						min = dp[i][j] + dp[0][j - (i + 1)];
						concurs[j] = concurs[j - (i + 1)] + 1;
					}
				} else {
					if (dp[i][j] != LONG_MAX && min > dp[i][j]) {
						min = dp[i][j];
						concurs[j] = 1;
					}
				}
			}
			// Schimbam in prima linie din matrice minimul calculat, astfel pas
			// cu pas obtinem pe ultima coloana de pe prima linie solutia
			// optima
			dp[0][j] = min;
		}
		return make_pair(dp[0][nr_P - 1], concurs[nr_P - 1]);
	}

	void print_output(pair<long long, int> result) {
		ofstream fout("planificare.out");
		fout << result.first << " " << result.second;
		fout.close();
	}
};

int main() {
	Planificare f;
	f.solve();
	return 0;
}
