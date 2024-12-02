#include <bits/stdc++.h>
using namespace std;

const int MAX_SIZE = 2005;


const size_t p1 = 31;
const size_t p2 = 37;
const size_t m1 = 1e9 + 9;
const size_t m2 = 1e9 + 7;

pair<size_t, size_t> hash_string(const string& s) {
    size_t hash1 = 0;
    size_t hash2 = 0;
    size_t p_pow1 = 1;
    size_t p_pow2 = 1;
    for (char ch : s) {
        hash1 = (hash1 + (ch - 'A' + 1) * p_pow1) % m1;
        hash2 = (hash2 + (ch - 'A' + 1) * p_pow2) % m2;
        p_pow1 = (p_pow1 * p1) % m1;
        p_pow2 = (p_pow2 * p2) % m2;
    }
    return {hash1, hash2};
}

struct pair_hash {
    template <class T1, class T2>
    size_t operator () (const pair<T1, T2>& p) const {
        auto h1 = hash<T1>{}(p.first);
        auto h2 = hash<T2>{}(p.second);

        return h1 ^ h2;
    }
};

void generate_combinations(string current, int najdluzsza_doczepka, vector<string>& combinations, vector<int>& lengths) {
    // Sprawdzamy, czy osiągnięto już 1000 kombinacji
    if (combinations.size() >= 1000) {
        return;
    }

    // Jeśli osiągnięto żądaną długość, dodajemy 'C' na końcu i zapisujemy kombinację
    if (current.length() == najdluzsza_doczepka) {
        combinations.push_back(current + 'C');
        lengths.push_back(current.length() + 1);
        return;
    }

    // Generujemy kombinacje rekurencyjnie
    generate_combinations(current + 'x', najdluzsza_doczepka, combinations, lengths);
    generate_combinations(current + 'C', najdluzsza_doczepka, combinations, lengths);
}
int main() {
    cin.tie(0);
    ios_base::sync_with_stdio(0);
    cout.tie(0);

    vector<vector<char>> Pierwszy(MAX_SIZE, vector<char>(MAX_SIZE));
    vector<vector<char>> Drugi(MAX_SIZE, vector<char>(MAX_SIZE));

    vector<vector<char>> Przed_sklejanie_pierwszego(MAX_SIZE, vector<char>(MAX_SIZE));
    vector<vector<char>> Przed_sklejanie_drugiego(MAX_SIZE, vector<char>(MAX_SIZE));

    vector<vector<char>> sklejanie_pierwszego(MAX_SIZE, vector<char>(MAX_SIZE));
    vector<vector<char>> sklejanie_drugiego(MAX_SIZE, vector<char>(MAX_SIZE));
    vector<int> poczatkowe_ciagi[MAX_SIZE];

    int n, p, dlugosc_ciagu;
    cin >> n >> p >> dlugosc_ciagu;
    for (int i = 1; i <= p; i++) {
        int a, b;
        cin >> a >> b;

        poczatkowe_ciagi[b].push_back(a);
        poczatkowe_ciagi[a].push_back(b);
    }

    for (int i = 1; i <= n; i++) {
        if (poczatkowe_ciagi[i].size() > 0) {


            for (int j = 0; j < poczatkowe_ciagi[i].size(); j++) {
                int k = poczatkowe_ciagi[i][j];
                Pierwszy[k][i] = 'C';
            }
        }
    }

    for (int i = 1; i <= n; i++) {
        if (poczatkowe_ciagi[i+n].size() > 0) {


            for (int j = 0; j < poczatkowe_ciagi[i+n].size(); j++) {
                int k = poczatkowe_ciagi[i+n][j];
                Drugi[k][i] = 'C';
            }
        }
    }



    // Hashowanie kolumn
    unordered_map<pair<size_t, size_t>, vector<int>, pair_hash> hasz_Mapa_Pierwszego;
    for (int j = 1; j <= n; j++) {
        string column;
        for (int i = 1; i <= n*2; i++) {
            column += Pierwszy[i][j];
        }
        pair<size_t, size_t> hash_val = hash_string(column);
        hasz_Mapa_Pierwszego[hash_val].push_back(j);
    }

    // Przechowywanie indeksów kolumn, które nie są połączone z innymi
vector<int> niepolaczone_kolumny;

// Wypisywanie kolumn, które są takie same
for (const auto& i : hasz_Mapa_Pierwszego) {
    if (i.second.size() > 1) {
        //cout << "Kolumny takie same: ";
        for (int j : i.second) {
            //cout << j << " ";
            //cout << Pierwszy[j][niepolaczone_kolumny[i.second[0]]];
            Pierwszy[j][i.second[0]] = 'C';
        }
        //cout << endl;

        // Dodawanie pierwszej kolumny z grupy połączonych do listy niepołączonych
        niepolaczone_kolumny.push_back(i.second[0]);
    } else {
        // Dodawanie niepołączonych kolumn do listy
        niepolaczone_kolumny.push_back(i.second[0]);
    }
}


    // Hashowanie kolumn
    unordered_map<pair<size_t, size_t>, vector<int>, pair_hash> hasz_Mapa_Drugiego;
    for (int j = 1; j <= n; j++) {
        string column;
        for (int i = 1; i <= n*2; i++) {
            column += Drugi[i][j];
        }
        pair<size_t, size_t> hash_val = hash_string(column);
        hasz_Mapa_Drugiego[hash_val].push_back(j);
    }

// Przechowywanie indeksów kolumn, które nie są połączone z innymi (dla drugiej mapy)
vector<int> niepolaczone_kolumny_drugiego;

// Wypisywanie kolumn, które są takie same (dla drugiej mapy)
for (const auto& para : hasz_Mapa_Drugiego) {
    if (para.second.size() > 1) {
        //cout << "Kolumny takie same: ";
        for (int kolumna : para.second) {
            //cout << kolumna << " ";
            Drugi[kolumna+n][para.second[0]] = 'C';
            //Drugi[kolumna][niepolaczone_kolumny_drugiego[para.second[0]]];

        }
        //cout << endl;

        // Dodawanie pierwszej kolumny z grupy połączonych do listy niepołączonych (dla drugiej mapy)
        niepolaczone_kolumny_drugiego.push_back(para.second[0]);
    } else {
        // Dodawanie niepołączonych kolumn do listy (dla drugiej mapy)
        niepolaczone_kolumny_drugiego.push_back(para.second[0]);
    }
}



    for (int i = 1; i <= n; i++){
        Pierwszy[i][i] = 'C';
        Drugi[i+n][i] = 'C';
    }
    //usuwanie niepotrzbnych w drugim
    for (int j = 1; j <= n*2; j++){
        int temp = 0;
        for (int i = 1; i <= n; i++){
            if (Drugi[i][j] == 'C'){
                temp++;
            }
            if(i == n && temp == 0){
                for (int x = n+1; x<=2*n;x++){
                    Drugi[x][j] = 0;
                }
            }
        }
    }

    //usuwanie niepotrzbnych w pierwszym
    for (int j = 1; j <= n*2; j++){
        int temp = 0;
        for (int i = 2*n; i >= n+1; i--){
            if (Pierwszy[i][j] == 'C'){
                temp++;
            }
            if(i == n+1 && temp == 0){
                for (int x = n; x>=1;x--){
                    Pierwszy[x][j] = 0;
                }
            }
        }
    }

    //Przed_sklejanie_pierwszego
    for (int j = 1; j<=niepolaczone_kolumny.size(); j++){
        for (int i = 1; i<=2*n; i++){

            Przed_sklejanie_pierwszego[i][j] = Pierwszy[i][niepolaczone_kolumny[j-1]];

        }
    }

    //Przed_sklejanie_drugiego
    for (int j = 1; j<=niepolaczone_kolumny_drugiego.size(); j++){
        for (int i = 1; i<=n*2; i++){
            Przed_sklejanie_drugiego[i][j] = Drugi[i][niepolaczone_kolumny_drugiego[j-1]];

        }
    }


    //sklejanie drugiego
    int Akt_kolumna_drugiego = 1;

    for (int j = 1; j <= 2*n; j++) {
        bool foundC = false;
        for (int i = 1; i <= 2*n; i++) {
            if (Przed_sklejanie_drugiego[i][j] == 'C') {
                foundC = true;
                for (int x = i; x <= 2*n; x++) {
                sklejanie_drugiego[x][Akt_kolumna_drugiego] = Przed_sklejanie_drugiego[x][j];
                }
             break;
         }
     }
        if (foundC) {
            ++Akt_kolumna_drugiego;
         }
    }

    //sklejanie pierwszego
    int Akt_kolumna_pierwszego = 1;

    for (int j = 1; j <= 2*n; j++) {
        bool foundC = false;
        for (int i = 1; i <= 2*n; i++) {
            if (Przed_sklejanie_pierwszego[i][j] == 'C') {
                foundC = true;
                for (int x = i; x <= 2*n; x++) {
                sklejanie_pierwszego[x][Akt_kolumna_pierwszego] = Przed_sklejanie_pierwszego[x][j];
                }
             break;
         }
     }
        if (foundC) {
            ++Akt_kolumna_pierwszego;
         }
    }

unordered_map<pair<size_t, size_t>, vector<int>, pair_hash> hashmap_pierwszego;
unordered_map<pair<size_t, size_t>, vector<int>, pair_hash> hashmap_drugiego;



    //tworzenie kombinacji

    vector<string> combinations;
    vector<int> lengths;


    combinations.push_back("");  // pierwsza kombinacja - pusta
    lengths.push_back(0);
    combinations.push_back("C"); // druga kombinacja - tylko 'C'
    lengths.push_back(1);

    // Rozpoczynamy od najdluzsza_doczepka równego 1, ponieważ kombinacje dla 0 i 1 zostały już dodane
    int najdluzsza_doczepka = 1;
    while (combinations.size() < 1000) {
        generate_combinations("", najdluzsza_doczepka, combinations, lengths);
        najdluzsza_doczepka++;
    }


// Hashowanie dla sklejanie_pierwszego
// Hashowanie dla sklejanie_pierwszego
for (int i = 1; i <= n; i++) {
    string row(sklejanie_pierwszego[i].begin() + 1, sklejanie_pierwszego[i].begin() + 2*n + 1);
    pair<size_t, size_t> hash_val = hash_string(row);
    hashmap_pierwszego[hash_val].push_back(i);
}

// Hashowanie dla sklejanie_drugiego
for (int i = 1; i <= n; i++) {
    string row(sklejanie_drugiego[i].begin() + 1, sklejanie_drugiego[i].begin() + 2*n + 1);
    pair<size_t, size_t> hash_val = hash_string(row);
    hashmap_drugiego[hash_val].push_back(i);
}


//Akt_kolumna_drugiego
//od_ktorej_zaczac
// Wyświetlanie wyników dla sklejanie_drugiego

int temp = 0; // indeks dla kombinacji od 1 do n
int akt = 0; // indeks dla kombinacji od n+1 do 2n
int max_dlugosc_kombinacji = 0;
for (auto it = hashmap_drugiego.begin(); it != hashmap_drugiego.end(); ++it) {
    vector<int>& indeksy = it->second;  // Referencja do wektora indeksów
    if (indeksy.size() > 1) {
        //cout << "Rzędy o tych samych ciągach w sklejanie_drugiego: ";

         // Zmienna przechowująca maksymalną długość kombinacji w tym przejściu

        for (int i = 0; i < indeksy.size(); ++i) {

            if (indeksy[i] <= n && temp < combinations.size()) {
                for (int j = 0; j < lengths[temp]; j++) {
                    sklejanie_drugiego[indeksy[i]][Akt_kolumna_drugiego + j] = combinations[temp][j];
                }
                max_dlugosc_kombinacji = max(max_dlugosc_kombinacji, lengths[temp]); // Aktualizacja maksymalnej długości
                temp++;
            } else if (indeksy[i] > n && akt < combinations.size()) {
                for (int j = 0; j < lengths[akt]; j++) {
                    sklejanie_drugiego[indeksy[i]][Akt_kolumna_drugiego + j] = combinations[akt][j];
                }
                max_dlugosc_kombinacji = max(max_dlugosc_kombinacji, lengths[akt]); // Aktualizacja maksymalnej długości
                akt++;
                }
            }
        temp = 0;
        akt = 0;

    }
}
Akt_kolumna_drugiego += max_dlugosc_kombinacji;



//Wyswietlanie wynikow dla sklejonego pierwszego
int temp1 = 0; // indeks dla kombinacji od 1 do n
int akt1 = 0; // indeks dla kombinacji od n+1 do 2n
max_dlugosc_kombinacji = 0;
for (auto it = hashmap_pierwszego.begin(); it != hashmap_pierwszego.end(); ++it) {
    vector<int>& indeksy = it->second;  // Referencja do wektora indeksów
    if (indeksy.size() > 1) {
        //cout << "Rzędy o tych samych ciągach w sklejanie_pierwszego: ";

         // Zmienna przechowująca maksymalną długość kombinacji w tym przejściu

        for (int i = 0; i < indeksy.size(); ++i) {


            if (indeksy[i] <= n && temp1 < combinations.size()) {
                for (int j = 0; j < lengths[temp1]; j++) {
                    sklejanie_pierwszego[indeksy[i]][Akt_kolumna_pierwszego + j] = combinations[temp1][j];
                }
                max_dlugosc_kombinacji = max(max_dlugosc_kombinacji, lengths[temp1]); // Aktualizacja maksymalnej długości
                temp1++;
            } else if (indeksy[i] > n && akt1 < combinations.size()) {
                for (int j = 0; j < lengths[akt1]; j++) {
                    sklejanie_pierwszego[indeksy[i]][Akt_kolumna_pierwszego + j] = combinations[akt1][j];
                }
                max_dlugosc_kombinacji = max(max_dlugosc_kombinacji, lengths[akt1]); // Aktualizacja maksymalnej długości
                akt1++;
                }
            }

        temp1 = 0;
        akt1 = 0;
        // Aktualizacja Akt_kolumna_pierwszego poza pętlą


    }
}
 Akt_kolumna_pierwszego += max_dlugosc_kombinacji;
 hashmap_pierwszego.clear();
 hashmap_drugiego.clear();

 /////////////////////////////////////////
 // Hashowanie dla sklejanie_pierwszego

for (int i = n+1; i <= 2*n; i++) {
    string row(sklejanie_pierwszego[i].begin() + 1, sklejanie_pierwszego[i].begin() + 2*n + 1);
    pair<size_t, size_t> hash_val = hash_string(row);
    hashmap_pierwszego[hash_val].push_back(i);
}

// Hashowanie dla sklejanie_drugiego
for (int i = n+1; i <= 2*n; i++) {
    string row(sklejanie_drugiego[i].begin() + 1, sklejanie_drugiego[i].begin() + 2*n + 1);
    pair<size_t, size_t> hash_val = hash_string(row);
    hashmap_drugiego[hash_val].push_back(i);
}


//Akt_kolumna_drugiego
//od_ktorej_zaczac
// Wyświetlanie wyników dla sklejanie_drugiego

 temp = 0; // indeks dla kombinacji od 1 do n
 akt = 0; // indeks dla kombinacji od n+1 do 2n
 max_dlugosc_kombinacji = 0;
for (auto it = hashmap_drugiego.begin(); it != hashmap_drugiego.end(); ++it) {
    vector<int>& indeksy = it->second;  // Referencja do wektora indeksów
    if (indeksy.size() > 1) {
        //cout << "Rzędy o tych samych ciągach w sklejanie_drugiego: ";

         // Zmienna przechowująca maksymalną długość kombinacji w tym przejściu

        for (int i = 0; i < indeksy.size(); ++i) {

            if (indeksy[i] <= n && temp < combinations.size()) {
                for (int j = 0; j < lengths[temp]; j++) {
                    sklejanie_drugiego[indeksy[i]][Akt_kolumna_drugiego + j] = combinations[temp][j];
                }
                max_dlugosc_kombinacji = max(max_dlugosc_kombinacji, lengths[temp]); // Aktualizacja maksymalnej długości
                temp++;
            } else if (indeksy[i] > n && akt < combinations.size()) {
                for (int j = 0; j < lengths[akt]; j++) {
                    sklejanie_drugiego[indeksy[i]][Akt_kolumna_drugiego + j] = combinations[akt][j];
                }
                max_dlugosc_kombinacji = max(max_dlugosc_kombinacji, lengths[akt]); // Aktualizacja maksymalnej długości
                akt++;
                }
            }

        temp = 0;
        akt = 0;

    }
}
Akt_kolumna_drugiego += max_dlugosc_kombinacji;



//Wyswietlanie wynikow dla sklejonego pierwszego
 temp1 = 0; // indeks dla kombinacji od 1 do n
 akt1 = 0; // indeks dla kombinacji od n+1 do 2n
max_dlugosc_kombinacji = 0;
for (auto it = hashmap_pierwszego.begin(); it != hashmap_pierwszego.end(); ++it) {
    vector<int>& indeksy = it->second;  // Referencja do wektora indeksów
    if (indeksy.size() > 1) {
        //cout << "Rzędy o tych samych ciągach w sklejanie_pierwszego: ";

         // Zmienna przechowująca maksymalną długość kombinacji w tym przejściu

        for (int i = 0; i < indeksy.size(); ++i) {


            if (indeksy[i] <= n && temp1 < combinations.size()) {
                for (int j = 0; j < lengths[temp1]; j++) {
                    sklejanie_pierwszego[indeksy[i]][Akt_kolumna_pierwszego + j] = combinations[temp1][j];
                }
                max_dlugosc_kombinacji = max(max_dlugosc_kombinacji, lengths[temp1]); // Aktualizacja maksymalnej długości
                temp1++;
            } else if (indeksy[i] > n && akt1 < combinations.size()) {
                for (int j = 0; j < lengths[akt1]; j++) {
                    sklejanie_pierwszego[indeksy[i]][Akt_kolumna_pierwszego + j] = combinations[akt1][j];
                }
                max_dlugosc_kombinacji = max(max_dlugosc_kombinacji, lengths[akt1]); // Aktualizacja maksymalnej długości
                akt1++;
                }
            }

        temp1 = 0;
        akt1 = 0;
    }
}
   Akt_kolumna_pierwszego += max_dlugosc_kombinacji;








if (dlugosc_ciagu == n+1){
    dlugosc_ciagu = n+1;
}else dlugosc_ciagu = n+2;


cout << dlugosc_ciagu << '\n';

// Wypisywanie zawartości sklejanie_drugiego
if (Akt_kolumna_pierwszego > Akt_kolumna_drugiego){

for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= dlugosc_ciagu; j++) {
        if(sklejanie_drugiego[i][j] != 'C') sklejanie_drugiego[i][j] = 'A';
        cout << sklejanie_drugiego[i][j];
    }
    cout << '\n';
    }

for (int i = n+1; i <= 2*n; i++) {
    for (int j = 1; j <= dlugosc_ciagu; j++) {
        if(sklejanie_drugiego[i][j] != 'C') sklejanie_drugiego[i][j] = 'B';
        cout << sklejanie_drugiego[i][j];
    }
    cout << '\n';
    }
}
else{

for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= dlugosc_ciagu; j++) {
        if(sklejanie_pierwszego[i][j] != 'C') sklejanie_pierwszego[i][j] = 'A';
        cout << sklejanie_pierwszego[i][j];
    }
    cout << '\n';
    }

for (int i = n+1; i <= 2*n; i++) {
    for (int j = 1; j <= dlugosc_ciagu; j++) {
        if(sklejanie_pierwszego[i][j] != 'C') sklejanie_pierwszego[i][j] = 'B';
        cout << sklejanie_pierwszego[i][j];
    }
    cout << '\n';
    }
}

    return 0;
}
