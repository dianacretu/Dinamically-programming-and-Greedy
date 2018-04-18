// Copyright 2018 Cretu Diana

#include <fstream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;

struct Concurs {
	int jocuri;
	int benzi;
	int suma;
	Concurs(int _jocuri, int _benzi, int _suma)
	: jocuri(_jocuri), benzi(_benzi), suma(_suma) {}
};

struct Final {
	int john;
	int sam;
};

struct comp {
	inline bool operator() (const Concurs c1, const Concurs c2) {
        return ((c1.jocuri + c1.benzi) > (c2.jocuri + c2.benzi));
    }
};

struct compJohn {
	inline bool operator() (const Concurs c1, const Concurs c2) {
        if ((c1.suma) == (c2.suma)) {
        	return (c1.jocuri > c2.jocuri);
       	}
       	return (c1.suma > c2.suma);
    }
};

class Frati {
 public:
	void solve() {
		read_input();
		print_output(get_result());
	}

 private:
	int nr_concursuri;
	vector<Concurs> objs;
	std::vector<int> v;

	void read_input() {
		ifstream fin("frati.in");
		fin >> nr_concursuri;
		int jocuri, benzi, suma;
		bool participat = false;
		for (int i = 0; i < nr_concursuri; i++) {
			fin >> jocuri >> benzi;
			suma = jocuri + benzi;
			objs.push_back(Concurs(jocuri, benzi, suma));
		}
		fin.close();
	}

	struct Final get_result() {
		Final f;
		sort(objs.begin(), objs.end(), compJohn());
		f.john = f.sam = 0;
		vector<vector<Concurs> > a;
		vector<Concurs> v;
		v.push_back(objs[0]);
		for (int i = 1; i < nr_concursuri; i ++) {
			if (objs[i - 1].suma == objs[i].suma) {
				v.push_back(objs[i]);
			} else {
				a.push_back(v);
				v.clear();
				v.push_back(objs[i]);
			}
		}
		a.push_back(v);
		int rand = 0;
		for(int i = 0; i < a.size(); i ++) {
			int j = 0, k = a[i].size() - 1;
			while (j <= k) {
				if (rand % 2 == 0) {
					f.john += a[i][j].jocuri;
					j ++;
					rand ++;
				} else {
					f.sam += a[i][k].benzi;
					k --;
					rand ++;
				}
			}
		}
		return f;
	}

	void print_output(struct Final result) {
		ofstream fout("frati.out");
		fout << result.john << " " << result.sam << endl;
		fout.close();
	}
};

int main() {
	Frati f;
	f.solve();
	return 0;
}
