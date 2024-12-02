#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int MAX_SIZE = 500005;

struct RozszerzonaPara {
    pair<long long, long long> para;
    int oryginalna_pozycja;
};

int main() {
    cin.tie(0);
    ios_base::sync_with_stdio(0);
    cout.tie(0);

    //wczytuje pary
    long long liczba_par;
    cin >> liczba_par;

    if(liczba_par == 1)
    {
        std::cout << 0 << std::endl;
        return 0;
    }

    vector<pair<long long, long long>> tablica_par(liczba_par + 1);
    for (int i = 1; i <= liczba_par; i++) {
        cin >> tablica_par[i].first >> tablica_par[i].second;
    }


    vector<RozszerzonaPara> rozszerzone_pary(liczba_par + 1);
    for (int i = 1; i <= liczba_par; ++i) {
        rozszerzone_pary[i] = {tablica_par[i], i};
    }


    sort(rozszerzone_pary.begin(), rozszerzone_pary.end(),
    [](const RozszerzonaPara& a, const RozszerzonaPara& b) {
        // Najpierw porównujemy drugi element pary, sortowanie rosnące
        if (a.para.second != b.para.second) return a.para.second < b.para.second;
        // Jeśli drugie elementy są równe, porównujemy pierwszy element, sortowanie malejące
        return a.para.first > b.para.first;
    });

    int licznik_wykladow = 1;
    int licznik_zastepstw = 1;


    vector<long long> wyklady;
    vector<long long> zastepstwa;


    wyklady.push_back(rozszerzone_pary[1].oryginalna_pozycja);

    zastepstwa.push_back(rozszerzone_pary[2].oryginalna_pozycja);


    pair aktualny_wyklad = make_pair(rozszerzone_pary[1].para.first, rozszerzone_pary[1].para.second);

    pair Przedostatni_wyklad = make_pair(rozszerzone_pary[1].para.first, rozszerzone_pary[1].para.second);

    pair aktualne_zastepstwo = make_pair(rozszerzone_pary[2].para.first, rozszerzone_pary[2].para.second);

    pair przedostatnie_zastepstwo = make_pair(rozszerzone_pary[2].para.first, rozszerzone_pary[2].para.second);

    if (liczba_par > 2){
        for (int i = 3; i <= liczba_par; i++) {

            if(licznik_wykladow == licznik_zastepstw){
                if(rozszerzone_pary[i].para.first >= aktualne_zastepstwo.second && rozszerzone_pary[i].para.first >= aktualny_wyklad.second){

                    Przedostatni_wyklad = aktualny_wyklad;

                    aktualny_wyklad = make_pair(rozszerzone_pary[i].para.first, rozszerzone_pary[i].para.second);

                    wyklady.push_back(rozszerzone_pary[i].oryginalna_pozycja);

                    licznik_wykladow++;
                    continue;
                }
                else if (rozszerzone_pary[i].para.first >= aktualny_wyklad.second){

                    przedostatnie_zastepstwo = aktualne_zastepstwo;

                    aktualne_zastepstwo = make_pair(rozszerzone_pary[i].para.first, rozszerzone_pary[i].para.second);

                    zastepstwa.push_back(rozszerzone_pary[i].oryginalna_pozycja);

                    licznik_zastepstw++;
                    continue;
                }
            }

            if(licznik_zastepstw > licznik_wykladow){
                if (rozszerzone_pary[i].para.first >= przedostatnie_zastepstwo.second){

                    Przedostatni_wyklad = aktualny_wyklad;
                    aktualny_wyklad = make_pair(rozszerzone_pary[i].para.first, rozszerzone_pary[i].para.second);

                    wyklady.push_back(rozszerzone_pary[i].oryginalna_pozycja);

                    licznik_wykladow++;
                    continue;
                }
            }
            if (licznik_wykladow > licznik_zastepstw){
                if (rozszerzone_pary[i].para.first >= Przedostatni_wyklad.second){

                    przedostatnie_zastepstwo = aktualne_zastepstwo;

                    aktualne_zastepstwo = make_pair(rozszerzone_pary[i].para.first, rozszerzone_pary[i].para.second);

                    zastepstwa.push_back(rozszerzone_pary[i].oryginalna_pozycja);

                    licznik_zastepstw++;
                    continue;
                }
            }
        }
    }
    vector <pair<long long, long long>> wykladziki;

    for (int i = 0; i<wyklady.size(); i++){
        wykladziki.push_back(make_pair(wyklady[i],zastepstwa[i]));
    }

    vector<long long> wyklady_2_opcja(MAX_SIZE);

    wyklady_2_opcja[1] = rozszerzone_pary[1].oryginalna_pozycja;

    pair aktualny_wyklad_2_opcja = make_pair(rozszerzone_pary[1].para.first, rozszerzone_pary[1].para.second);

    int licznik_2_opcja = 0;

    vector <pair<long long, long long> > wykladziki2;

    for (int i = 2; i<=liczba_par; i++){
        if (rozszerzone_pary[i].para.first >= aktualny_wyklad_2_opcja.second){

            //wyklady_2_opcja.push_back(rozszerzone_pary[i].oryginalna_pozycja);

            wykladziki2.push_back(make_pair(rozszerzone_pary[i].oryginalna_pozycja, wyklady_2_opcja[1]));

            aktualny_wyklad_2_opcja = make_pair(rozszerzone_pary[i].para.first, rozszerzone_pary[i].para.second);

            licznik_2_opcja++;
        }
    }


   cout << max(licznik_2_opcja, min(licznik_wykladow,licznik_zastepstw)) << '\n';

    if (licznik_2_opcja > min(licznik_wykladow,licznik_zastepstw)){

        for (int i = 0; i < wykladziki2.size(); i++){

            if (wykladziki2[i].first != 0 && wykladziki2[i].second != 0){
                cout << wykladziki2[i].first << " " << wykladziki2[i].second << '\n';
            }

        }

    }else {
        for (int i = 0; i<wyklady.size(); i++){

            if (wykladziki[i].first != 0 && wykladziki[i].second != 0){
                cout << wykladziki[i].first << " " << wykladziki[i].second << '\n';
            }

        }
    }

}
