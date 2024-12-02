#include <bits/stdc++.h>
using namespace std;

const int MAXN = 500005;

struct Edge {
    int vertex; // docelowy wierzchołek krawędzi
    int order;  // kolejność dodania krawędzi
};

vector<Edge> wiersze[MAXN];
vector<Edge> kolumny[MAXN];
set<int> wypelnioneWiersze, wypelnioneKolumny;

bool checkCondition( vector <int> combination, int n) {
    
    bool czy_parzyste_wiersze = true;
    for (auto i : wypelnioneWiersze) {
        //cout << "Wiersz " << i << " ";

        int parzyste = 0;
        bool czy_parzyste = true;


        for (const Edge& e : wiersze[i]) {
            for (int i = 0; i < combination.size(); ++i) {
                if (combination[i] == e.order) ++parzyste;
            }

            if (parzyste%2 == 0){
                czy_parzyste = true;
            }else czy_parzyste = false;
            //cout << " " << e.vertex << "(K" << e.order << ")";
        }
        
        if (!czy_parzyste){
            czy_parzyste_wiersze = false;
            break;
        }
    }

    // Wyświetlanie grafu kolumnc
    //cout << endl;
    //cout << "Graf kolumn:" << endl;
    bool czy_parzyste_kolumny = true;
    for (auto i : wypelnioneKolumny) {
        //cout << "Kolumna " << i << " ->";

        int parzyste = 0;
        bool czy_parzyste = true;

        for (const Edge& e : kolumny[i]) {
             for (int i = 0; i < combination.size(); ++i) {
                if (combination[i] == e.order) ++parzyste;
            }

            if (parzyste%2 == 0){
                czy_parzyste = true;
            }else czy_parzyste = false; ;
            //cout << " " << e.vertex << "(W" << e.order << ")";
        }

        if (!czy_parzyste){
            czy_parzyste_kolumny = false;

            break;
        }
    }
    //cout << endl;
    //cout << "Graf wierszy:" << endl;
    bool czy_nieparzyste_wiersze = false;
    if (wypelnioneWiersze.size() == n){
    
    czy_nieparzyste_wiersze = true;
    for (auto i : wypelnioneWiersze) {
        //cout << i << " ->";


        int nieparzyste = 0;
        bool czy_nieparzyste = false;


        for (const Edge& e : wiersze[i]) {
            for (int i = 0; i < combination.size(); ++i) {
                if (combination[i] == e.order){
                    ++nieparzyste;

                 }
            }

            if (nieparzyste%2 == 1){
                czy_nieparzyste = true;
            }else czy_nieparzyste = false;
            //cout << " " << e.vertex << "(K" << e.order << ")";

        }

        if (!czy_nieparzyste){
            czy_nieparzyste_wiersze = false;

            break;
        }
    }
}

    // Wyświetlanie grafu kolumnc
    //cout << endl;
    //cout << "Graf kolumn:" << endl;
    
    
    bool czy_nieparzyste_kolumny = false;
    
    if (wypelnioneKolumny.size() == n){
    czy_nieparzyste_kolumny = true;
    
    for (auto i : wypelnioneKolumny) {
        //cout << "Kolumna " << i << " ->";


        int nieparzyste = 0;
        bool czy_nieparzyste = false;

        for (const Edge& e : kolumny[i]) {
             for (int i = 0; i < combination.size(); ++i) {
                if (combination[i] == e.order){
                ++nieparzyste;

                }
            }

            if (nieparzyste%2 == 1){
                czy_nieparzyste = true;
            }else czy_nieparzyste = false;


            //cout << " " << e.vertex << "(W" << e.order << ")";
        }

        if (!czy_nieparzyste){
            czy_nieparzyste_kolumny = false;
            break;
        }

    }
    }


    if ((czy_parzyste_wiersze == 1 && czy_parzyste_kolumny == 1) || (czy_nieparzyste_kolumny == 1 && czy_nieparzyste_wiersze == 1)){
        cout << "TAK" << '\n';
        int ile = 0;
        for (int i = 0; i < combination.size(); ++i) {
            ile++;
            }
        cout << ile << '\n';
        for (int i = 0; i < combination.size(); ++i) {
            cout << combination[i] << " ";
            }
        return true;
    }else{
        return 0;
    }
}

bool checkConditionParzyste (vector<int> combination, int n) {

    bool czy_parzyste_wiersze = true;
    for (auto i : wypelnioneWiersze) {
        //cout << "Wiersz " << i << " ->";

        int parzyste = 0;
        bool czy_parzyste = true;


        for (const Edge& e : wiersze[i]) {
            for (int i = 0; i < combination.size(); ++i) {
                if (combination[i] == e.order) ++parzyste;
            }

            if (parzyste%2 == 0){
                czy_parzyste = true;
            }else czy_parzyste = false;
            //cout << " " << e.vertex << "(K" << e.order << ")";
        }

        if (!czy_parzyste){
            czy_parzyste_wiersze = false;
            break;
        }
    }

    // Wyświetlanie grafu kolumnc
    //cout << endl;
    //cout << "Graf kolumn:" << endl;
    bool czy_parzyste_kolumny = true;
    for (auto i : wypelnioneKolumny) {
        //cout << "Kolumna " << i << " ->";

        int parzyste = 0;
        bool czy_parzyste = true;

        for (const Edge& e : kolumny[i]) {
             for (int i = 0; i < combination.size(); ++i) {
                if (combination[i] == e.order) ++parzyste;
            }

            if (parzyste%2 == 0){
                czy_parzyste = true;
            }else czy_parzyste = false; ;
            //cout << " " << e.vertex << "(W" << e.order << ")";
        }

        if (!czy_parzyste){
            czy_parzyste_kolumny = false;
            break;
        }
    }
    if (czy_parzyste_wiersze == 1 && czy_parzyste_kolumny == 1){
        cout << "TAK" << '\n';
        int ile = 0;
        for (int i = 0; i < combination.size(); ++i) {
            ile++;
            }
        cout << ile << '\n';
        for (int i = 0; i < combination.size(); ++i) {
            cout << combination[i] << " ";
            }
        return true;
    }else{
        return 0;
    }
}


// Rekurencyjna funkcja do generowania kombinacji
void generateCombinations(int m, int k, int start, vector<int>& current, vector<vector<int>>& result) {
    if (current.size() == k) {
        result.push_back(current);
        return;
    }
    for (int i = start; i <= m; ++i) {
        current.push_back(i);
        generateCombinations(m, k, i + 1, current, result);
        current.pop_back();
    }
}

int main() {
    cin.tie(0);
    ios_base::sync_with_stdio(0);
    cout.tie(0);
    int m,n;
    cin >> n >> m;

    // Zbieranie danych o krawędziach
    for(int i = 1; i <= m; ++i) {
        int a, b;
        cin >> a >> b;
        wiersze[a].push_back({b, i});
        kolumny[b].push_back({a, i});
        wypelnioneWiersze.insert(a); // niepuste wiersze
        wypelnioneKolumny.insert(b); // niepuste kolumny
    }

    if (m<=20){
        
    
    bool wieksze_rowne_20 = false;
    bool mniejsze_rowne_20 = false;
    if (m>=n){
    for (int k = 1; k <= m; ++k) {
        
        vector<int> current;
        vector<vector<int>> combinations;
        generateCombinations(m, k, 1, current, combinations);

        for (const auto& combo : combinations) {
            if (checkCondition(combo, n)) {
                mniejsze_rowne_20 = true;
                return 0;
            }
        }

        if (mniejsze_rowne_20){
            combinations.clear();
            break;
        }
        combinations.clear();
        }
    }else{
        
    for (int k = 1; k <= m; ++k) {
        vector<int> current;
        vector<vector<int>> combinations;
        generateCombinations(m, k, 1, current, combinations);

        for (const auto& combo : combinations) {
            if (checkConditionParzyste(combo, n)) {
                wieksze_rowne_20 = true;
                return 0;
            }
        }

        if (wieksze_rowne_20){
            combinations.clear();
            break;
        }
        combinations.clear();
        }
    }


    if (!wieksze_rowne_20 && !mniejsze_rowne_20){
        cout <<"NIE";
    }

    } else cout << "TAK";
    return 0;
}
