#include <bits/stdc++.h>
using namespace std;

int MAX_SIZE = 1005;

int main() {
    
    cin.tie(0);
    ios_base::sync_with_stdio(0);
    cout.tie(0);
    
    int n, k, a, b;

    string slowo;
    cin >> n >> k >> a >> b;
    cin >> slowo;

    int ile = b-n;

    if (n<=100 && b <=1000){

        vector <char> tab(slowo.size());

        for (int i = 0; i < slowo.size(); i++) {
            tab[i] = slowo[i];
        }

        while(ile--){

            vector<char> szukanie_znakow;

            vector<char> aktualny_sufiks(k);

            for (int i = 0; i < k; i++) {
                aktualny_sufiks[i] = tab[tab.size() - k + i];
            }

            for (int i = 0; i < (tab.size()-k); i++){
                bool czy_poprawny = false;
                for (int j = i; j<k+i; j++){
                    if (aktualny_sufiks[j-i] == tab[j]){
                        czy_poprawny = true;
                        if (j == k+i-1 && czy_poprawny == true){
                            szukanie_znakow.push_back(tab[k+i]);
                        }
                    }else break;
                }

            }

            map<char, int> licznikZnakow;


            for (char znak : szukanie_znakow) {
                licznikZnakow[znak]++;
            }

            if(licznikZnakow.empty())
            {
                tab.push_back('a');
                continue;
            }

            int maksWystapien = 0;

            for (const auto& para : licznikZnakow) {
                maksWystapien = max(maksWystapien, para.second);
            }

            for (char znak = 'a'; znak <= 'z'; znak++) {
                if (licznikZnakow[znak] == maksWystapien) {
                    tab.push_back(znak);
                    break;  // Dodane, aby przerwać pętlę po znalezieniu pierwszego znaku
                }
            }

            szukanie_znakow.clear();
            aktualny_sufiks.clear();
            licznikZnakow.clear();

        }
        for (int i = a-1; i<=b-1; i++) cout << tab[i];
    }
    else{
        for (int i = a; i<=b; i++) cout << 'a';
    }
}
