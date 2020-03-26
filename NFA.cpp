#include <bits/stdc++.h>
#include <fstream>

using namespace std;

ifstream fin("nfa.in");
//ofstream fout("output.txt");

int tnz[101][101][101];
int OK;

// verifica daca litera se afla in lista de litere
bool checkChar(char c[], int m, int litera) {
	bool ok = false;
	for (int i = 0; i < m; ++i) {
		if (c[i] == litera || litera == '$') ok = true;
	}
	return ok;
}

// NFS RECURSIV
// current este starea curenta din care cautam noua stare
// noua stare va deveni ulterior starea curenta
// current este initial q[0] (starea initiala)
void NFS(char word[], int current, char c[], int m, int q[], int k) {
	int p1, p2, length = strlen(word);
	// parcurgem cuvantul litera cu litera
	for (int i = 0; i < length; ++i) {
		p1 = p2 = 0;
		// fiecare litera trebuie sa apartina alfabetului
		if (checkChar(c, m, word[i])) {
			// tnz[x][y][z] este o matrice tripla care pastreaza:
			// x - starea curenta
			// y - litera curenta din cuvant SAU $ care face transferul automat intr-o noua stare,
			//									   fara schimbarea literei curente
			// z - pot exista mai multe noi stari care au ca tranzitie aceeasi litera / $
			//	   pastram fiecare dintre aceste stari printr-o pozitie z
			while (tnz[current][word[i]][p1] != 0 || tnz[current]['$'][p2] != 0) {
				// exista stare noua de parcurs
				// verificam daca este de tip litera sau $
				if (tnz[current][word[i]][p1] != 0) {
					current = tnz[current][word[i]][p1];
					++p1;
				}
				// daca este de tip $, scadem i cu o valoare pentru a pastra acelasi numar de litere in cuvant
				// asta pentru ca transferul se face automat, fara a parcurge vreo litera din cuvant
				else {
					current = tnz[current]['$'][p2];
					++p2;
					--i;
				}
				// formam noul cuvant (prefixul cuvantului initial luat de la pozitia i + 1 pana la length
				char new_word[501] = "";
				for (int l = 0, j = i + 1; j < length; ++j, ++l) new_word[l] = word[j];
				// apelam recursiv NFS pentru noua stare
				NFS(new_word, current, c, m, q, k);
			}
			p1 = p2 = 0;
		}
		else {
			cout << "Literele din cuvant trebuie sa se afle in alfabet!";
			exit(EXIT_FAILURE);
		}
	}

	// acum in current se afla starea finala
	// avem de verificat daca aceasta corespunde uneia dintre starile finale din input
	for (int i = 1; i <= k; ++i) {
		if (current == q[i]) OK = 1;
	}
}

int main() {
	int n, m;
	char c[1001];
	fin >> n >> m;
	for (int i = 0; i < m; ++i) {
		fin >> c[i];
	}
	int q[1001], k;
	fin >> q[0] >> k;					// q0 - stare initiala
	for (int i = 1; i <= k; ++i) {		// q1..qk - stari finale
		fin >> q[i];
		if (0 > q[i] || n - 1 < q[i]) {
			exit(EXIT_FAILURE);
		}
	}
	int L, x, y, p;
	char alfa;
	fin >> L;
	for (int i = 0; i < L; ++i) {
		fin >> x >> alfa >> y;
		p = 0;
		if (checkChar(c, m, alfa)) {
			while (tnz[x][alfa][p] != 0) ++p;
			tnz[x][alfa][p] = y;
		}
		else {
			cout << "Literele din tranzitii trebuie sa se afle in alfabet!";
			exit(EXIT_FAILURE);
		}
	}
	char word[505];
	while (true) {
		cin.get(word, 505);
		cin.get();
		if (strcmp(word, "over") == 0) break;
		else {
			NFS(word, q[0], c, m, q, k);
			if (OK == 1) cout << "TRUE";
			else cout << "FALSE";
			cout << '\n';
			OK = 0;
		}
	}
	fin.close();
	return 0;
}
