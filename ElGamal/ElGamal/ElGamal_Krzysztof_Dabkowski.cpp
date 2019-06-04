#include <cstdlib>
#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>
using namespace std;

void dec_to_bin(unsigned long long int liczba, unsigned long long int tab[31])
{
	long long int i = 0;

	while (liczba)
	{
		tab[i++] = liczba % 2;
		liczba /= 2;
	}
}
unsigned long long int ASPM(unsigned long long int a, unsigned long  long int b, unsigned long long int c) {
	unsigned long long int sum = 1;
	unsigned long long int TAB[31];
	unsigned long long int tab[31];
	for (int i = 0; i < 31; i++) tab[i] = 3;
	dec_to_bin(b, tab);
	TAB[0] = a % c;
	if (tab[0] == 1) sum *= TAB[0];
	for (int i = 1; tab[i] <2; i++) {
		TAB[i] = pow(TAB[i - 1], 2);
		TAB[i] %= c;
		if (tab[i] == 1) sum *= (TAB[i]);
		sum %= c;
	}
	return sum;

}
void faktoryzacja(unsigned int k,vector<int> &TAB)
{
	    unsigned long x, y, r, u, n;
		x = (unsigned long)(sqrt(k));
		do
		
		{
		
				r = x * x - k;y = (unsigned long)floor(sqrt(r));
				if (r == y * y){
					u = x + y;
					n = x - y;
					if (n == 1)
							
					break;
					faktoryzacja(u,TAB);
					faktoryzacja(n,TAB);
					return;
					
				}
			
				x++;
			
		} while (x + y < k);
			
		TAB.push_back(k);
			
}
void LUCAS(int p, int q) {
	vector <int> TAB;
	bool pierwsza = false;
	faktoryzacja(p - 1, TAB);
	if (ASPM(q, p - 1, p) == 1) {
		cout << endl << q << "^(" << p - 1 << ") =" << ASPM(q, p - 1, p) << " (mod " << p << ")" << endl;
		pierwsza = true;
		for (int i = 0; i < TAB.size(); i++) {

			if (ASPM(q, (p - 1) / TAB[i], p) == 1) {
				pierwsza = false;
				if (i == 0) cout << q << "^(" << p - 1 << "/" << TAB[i] << ") =/=" << ASPM(q, (p - 1) / TAB[i], p) << " (mod " << p << ")" << endl;
				else if (i != 0 and TAB[i] != TAB[i - 1])
					cout << q << "^(" << p - 1 << "/" << TAB[i] << ") ==" << ASPM(q, (p - 1) / TAB[i], p) << " (mod " << p << ")" << endl;
			}

			else {
				if (i == 0) cout << q << "^(" << p - 1 << "/" << TAB[i] << ") =/=" << ASPM(q, (p - 1) / TAB[i], p) << " (mod " << p << ")" << endl;
				else if (i != 0 and TAB[i] != TAB[i - 1]) cout << q << "^(" << p - 1 << "/" << TAB[i] << ") =/=" << ASPM(q, (p - 1) / TAB[i], p) << " (mod " << p << ")" << endl;
			}
		}
	}
	if (pierwsza == true) cout << endl << p << " jest pierwsza" << endl;
	else cout << endl << "nie rozstrzyga czy " << p << " jest pierwsza" << endl;


}
void p_pierwotne(int n,int r) {
	bool on = true;
	vector <int> TAB;
	int f = n-1;
	while (f % 2 == 0)
	{
		f /= 2;
		TAB.push_back(2);
	}
	faktoryzacja(f,TAB);
	long long int help;
	for (int i = 0; i < TAB.size()-1 ; i++) {
		help = ASPM(r, (n - 1) / TAB[i], n); 
		if (help == 1) { cout << "Error !  r nie jest dzielnikiem pierwszym! "; on = false; break; }
	}
	if (on) {
		int k;
		cout << "Podaj 'tajna' liczbe k: ";
		cin >> k;
		if (k > (n - 1) || k <= 1) cout << "Error ! k>=(n-1) lub k<=1 !" << endl;
		else
		{
			long long unsigned int a = ASPM(r, k, n);
			cout << "Klucz publiczny: (" << n << "," << r << "," << a << ")" << endl;
			cout << "Klucz prywatny: (" << n << "," << r << "," << a << "," << k << ")" << endl;
			int t;
			cout << endl << "Podaj tekst t(<n): " ;
			cin >> t;
			if (t > (n - 1) || t <= 1) cout << "Error ! t>=(n-1) lub t<=1 !" << endl;
			else
			{
				int j;
				cout << "Wylosuj liczbe j (<n-1): " ;
				cin >> j;
				if (j > (n - 1) || j <= 1) cout << "Error ! j>=(n-1) lub j<=1 !" << endl;
				else
				{
					long long unsigned int c1, c2;
					c1 = ASPM(r, j, n);
					c2 = (t*ASPM(a, j, n)) % n;
					long long unsigned int sz = (c2*(c1 ^ (n - 1 - k)));
					sz = (c2*ASPM(c1, n - 1 - k, n)) % n;
					cout << endl << "Szyfrogram to: (" << c1 << "," << c2 << ")" << endl;
					cout << "t odszyfrowane to: " << sz << endl;
				}
			}
		}
	}
}
bool pierwsza(int n) {

	for (int i = 2; i < n; i++) {
		if (n%i == 0) { return false; break; }
	}
	return true;
}
int main() {


	int n, r;
	cout << "Podaj n (liczba pierwsza) : " ;
	cin >> n;
	if (pierwsza(n)) {
		cout << "Podaj r (<n-1): ";
		cin >> r;
		if (r >= (n - 1) || n <= 1) cout << "Error ! r<=1 lub  r>=n-1" << endl;
		else p_pierwotne(n, r);
	}
	else cout << "Error ! n nie jest pierwsza! " << endl;
	
	
	system("pause");
	return 0;
}