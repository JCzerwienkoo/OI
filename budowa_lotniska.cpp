#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1505;

char a[MAXN][MAXN];

int prawo[MAXN][MAXN];
int lewo[MAXN][MAXN];
int dol[MAXN][MAXN];
int gora[MAXN][MAXN];

int Pozioma_gora_MAX[MAXN][MAXN];

int Pozioma_dol_MAX[MAXN][MAXN];

int Po_lewej_max_poziomy[MAXN][MAXN];

int Po_prawej_max_poziomy[MAXN][MAXN];

int Pionowa_gora_MAX[MAXN][MAXN];

int Pionowa_dol_MAX[MAXN][MAXN];

int Pionowa_po_lewej_MAX[MAXN][MAXN];

int Pionowa_po_prawejMAX[MAXN][MAXN];

int main()
{
    cin.tie(0);
    ios_base::sync_with_stdio(0);
    cout.tie(0);

    int n,m,Najwieksza = 0;
    cin >> n >> m;

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            cin >> a[i][j];
            //cout << Pionowa_gora_MAX[i][j];
        }
        //cout << endl;
    }

    // right
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (a[i][j] == '.' && prawo[i][j-1] == 0) {
                prawo[i][j] = 1;
            }
            if (a[i][j-1] == '.' && a[i][j] == '.'){
                prawo[i][j]+=prawo[i][j-1]+1;
            }
        }
    }

    // down
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (a[i][j] == '.' && dol[i-1][j] == 0) {
                dol[i][j] = 1;
            }
            if (a[i-1][j] == '.' && a[i][j] == '.'){
                dol[i][j]+=dol[i-1][j]+1;
            }
        }
    }

    // left
    for (int i = 1; i <= n; i++) {
        for (int j = n; j >= 1; j--) {
            if (a[i][j] == '.' && lewo[i][j+1] == 0) {
                lewo[i][j] = 1;
            }
            if (a[i][j+1] == '.' && a[i][j] == '.'){
                lewo[i][j]+=lewo[i][j+1]+1;
            }
        }
    }

    // up
    for (int j = 1; j <= n; j++) {
        for (int i = n; i >= 1; i--) {
            if (a[i][j] == '.' && (i == n || gora[i+1][j] == 0)) {
                gora[i][j] = 1;
            }
            if (i < n && a[i+1][j] == '.' && a[i][j] == '.') {
                gora[i][j] += gora[i+1][j] + 1;
            }
        }
    }


    // sprawdza jaki najdluzszy ciag moze byc powyzej ktory idzie w bok Pozioma_gora_MAX[i-1][n]

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (j!=1){
            Pozioma_gora_MAX[i][j] = max(Pozioma_gora_MAX[i][j-1],prawo[i][j]);
            }
            else Pozioma_gora_MAX[i][j] = max(Pozioma_gora_MAX[i-1][n], prawo[i][j]);
        }
    }


    // sprawdza jaki najdluzszy ciag moze byc ponizej ktory idzie w bok Pozioma_dol_MAX[i+1][n])

    for (int i = n; i >= 1; i--) {
        for (int j = 1; j <= n; j++) {
            if(j!=1){
                Pozioma_dol_MAX[i][j] = max(Pozioma_dol_MAX[i][j-1], prawo[i][j]);
            }
            else Pozioma_dol_MAX[i][j] = max(prawo[i][j], Pozioma_dol_MAX[i+1][n]);
        }
    }

    //najwieksze po lewej Po_lewej_max_poziomy[n][j-1]

    for (int j = 1; j <=n ; j++){
        for (int i = 1; i <= n; i++){
            if(i!=1){
                Po_lewej_max_poziomy[i][j] = max(Po_lewej_max_poziomy[i-1][j], prawo[i][j]);
            }else{
                Po_lewej_max_poziomy[i][j] = max(Po_lewej_max_poziomy[n][j-1], prawo[i][j]);
            }
        }
    }

    //najwieksze po prawej Po_prawej_max_poziomy[n][j+1]

    for (int j = n; j >= 1; j--){
        for (int i = 1; i <= n; i++){
            if (i!=1){
                Po_prawej_max_poziomy[i][j] = max(Po_prawej_max_poziomy[i-1][j], lewo[i][j]);
            }else{
                Po_prawej_max_poziomy[i][j] = max(Po_prawej_max_poziomy[n][j+1], lewo[i][j]);
            }
        }
    }

    // najwiekszy pionowy od gory Pionowa_gora_MAX[i-1][n]

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (j!=1){
                Pionowa_gora_MAX[i][j] = max(dol[i][j], Pionowa_gora_MAX[i][j-1]);
            }else{
                Pionowa_gora_MAX[i][j] = max(dol[i][j], Pionowa_gora_MAX[i-1][n]);
            }
        }
    }

    //najwiekszy pionowy od dolu Pionowa_dol_MAX[i+1][n]
    for (int i = n; i >= 1; i--){
        for (int j = 1; j <= n; j++){
            if(j!=1){
                Pionowa_dol_MAX[i][j] = max(gora[i][j], Pionowa_dol_MAX[i][j-1]);
            }else{
                Pionowa_dol_MAX[i][j] = max(gora[i][j], Pionowa_dol_MAX[i+1][n]);
            }
        }
    }

    //najwiekszy pionowy od lewej Pionowa_po_lewej_MAX[n][j-1])

    for (int j = 1; j<= n; j++){
        for (int i = 1; i <= n; i++){
            if (i!=1){
            Pionowa_po_lewej_MAX[i][j] = max(dol[i][j], Pionowa_po_lewej_MAX[i-1][j]);
            }else{
                Pionowa_po_lewej_MAX[i][j] = max(dol[i][j], Pionowa_po_lewej_MAX[n][j-1]);
            }
        }
    }

    //najwieksza pionowa od prawej strony Pionowa_po_prawejMAX[n][j+1];

    for (int j = n; j >= 1; j--){
        for (int i = 1; i<=n; i++){
            if (i!=1){
                Pionowa_po_prawejMAX[i][j] = max(dol[i][j],Pionowa_po_prawejMAX[i-1][j]);
            }else{
                Pionowa_po_prawejMAX[i][j] = max(dol[i][j],Pionowa_po_prawejMAX[n][j+1]);
            }
        }
    }

    //przechodzimy w prawo


    int maksymalnaPrawa = 0;

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {

            int temp = prawo[i][j];
            Najwieksza = max(Najwieksza,temp);
            if (temp!=0){
                if (Pozioma_gora_MAX[i-1][n] >= temp || Pozioma_dol_MAX[i+1][n] >= temp || Po_lewej_max_poziomy[n][j-temp] >= temp || Po_prawej_max_poziomy[n][j+1] >= temp || Pionowa_gora_MAX[i-1][n] >= temp || Pionowa_dol_MAX[i+1][n] >= temp || Pionowa_po_lewej_MAX[n][j-temp] >= temp || Pionowa_po_prawejMAX[n][j+1] >= temp){
                maksymalnaPrawa = max(maksymalnaPrawa,temp);
                }
            }
        }
    }

    //przechodzimy w lewo

    int maksymalnaLewa = 0;

    for (int i = 1; i <= n; i++) {
        for (int j = n; j >= 1; j--) {

            int temp = lewo[i][j];
            Najwieksza = max(Najwieksza,temp);
            if (temp!=0){
                if (Pozioma_gora_MAX[i-1][n] >= temp || Pozioma_dol_MAX[i+1][n] >= temp || Po_lewej_max_poziomy[n][j-1] >= temp || Po_prawej_max_poziomy[n][j+temp] >= temp || Pionowa_gora_MAX[i-1][n] >= temp || Pionowa_dol_MAX[i+1][n] >= temp || Pionowa_po_lewej_MAX[n][j-1] >= temp || Pionowa_po_prawejMAX[n][j+temp] >= temp){
                maksymalnaLewa = max(maksymalnaLewa,temp);
                }
            }
        }
    }

    //przechodzimy od gory


    int maksymalnaGora = 0;

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {

            int temp = dol[i][j];
            Najwieksza = max(Najwieksza,temp);
            if (temp!=0){
                if (Pozioma_gora_MAX[i-temp][n] >= temp || Pozioma_dol_MAX[i+1][n] >= temp || Po_lewej_max_poziomy[n][j-1] >= temp || Po_prawej_max_poziomy[n][j+1] >= temp || Pionowa_gora_MAX[i-temp][n] >= temp || Pionowa_dol_MAX[i+1][n] >= temp || Pionowa_po_lewej_MAX[n][j-1] >= temp || Pionowa_po_prawejMAX[n][j+1] >= temp){
                maksymalnaGora = max(maksymalnaGora,temp);
                }
            }
        }
    }

    //przechodzimy od dolu


    int maksymalnyDol = 0;

    for (int j = 1; j <= n; j++) {
        for (int i = n; i >= 1; i--) {

            int temp = gora[i][j];
            Najwieksza = max(Najwieksza,temp);
            if (temp!=0){
                if (Pozioma_gora_MAX[i-1][n] >= temp || Pozioma_dol_MAX[i+temp][n] >= temp || Po_lewej_max_poziomy[n][j-1] >= temp || Po_prawej_max_poziomy[n][j+1] >= temp || Pionowa_gora_MAX[i-1][n] >= temp || Pionowa_dol_MAX[i+temp][n] >= temp || Pionowa_po_lewej_MAX[n][j-1] >= temp || Pionowa_po_prawejMAX[n][j+1] >= temp){
                maksymalnyDol = max(maksymalnyDol,temp);
                }
            }
        }
    }
    if (m == 1){
        cout << Najwieksza;
    }else{
        cout << max(max(maksymalnaGora, maksymalnaLewa), max(maksymalnaPrawa, maksymalnyDol));
    }
}
