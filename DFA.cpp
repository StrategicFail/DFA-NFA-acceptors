#include <bits/stdc++.h>
#include <fstream>


using namespace std;

ifstream fin("dfa.in");

int tnz[1001][1001];

// verifica daca litera se afla in lista de litere
bool checkChar(char c[], int m, int litera) {
	bool ok = false;
	for (int i = 0; i < m; ++i) {
		if (c[i] == litera) ok = true;
	}
	return ok;
}

int DFA(char cuvant[], int q[], int k, char c[], int m) {
	int current, length = strlen(cuvant);
	current = q[0];
	for (int i = 0; i < length; ++i) {
		if (checkChar(c, m, cuvant[i])) {
			current = tnz[current][cuvant[i]];
		}
		else {
			cout << "Literele din cuvant trebuie sa se afle in alfabet!";
			exit(EXIT_FAILURE);
		}
	}

	// current retine starea in care am ajuns dupa tranzitii
	// urmeaza sa verificam daca aceasta corespunde uneia din starile finale ale DFA

	for (int i = 1; i <= k; ++i) {
		if (current == q[i]) return 0;
	}
	return 1;
}

int main() {
	int n, m;
	char c[1001];
	fin >> n >> m;
	for (int i = 0; i < m; ++i) {
		fin >> c[i]; // alfabet
	}
	int q[1001], k;
	fin >> q[0] >> k;					// q0 - stare initiala
	for (int i = 1; i <= k; ++i) {		// q1..qk - stari finale
		fin >> q[i];
		if (0 > q[i] || n - 1 < q[i]) {
			exit(EXIT_FAILURE);
		}
	}
	int L, x, y;
	char alfa;
	fin >> L;
	for (int i = 0; i < L; ++i) {
		fin >> x >> alfa >> y; // tranzitii
		if (checkChar(c, m, alfa)) {
			tnz[x][alfa] = y;
		}
		else {
			cout << "Literele din tranzitii trebuie sa se afle in alfabet!";
			exit(EXIT_FAILURE);
		}
	}
	char cuvant[505];
	while (true) {
		cin.get(cuvant, 505);
		cin.get();
		if (strcmp(cuvant, "over") == 0) break; // programul se termina la input-ul "over"
		else {
			if (DFA(cuvant, q, k, c, m) == 0) cout << "TRUE";
			else cout << "FALSE";
			cout << '\n';
		}
	}
	fin.close();
	return 0;
}
