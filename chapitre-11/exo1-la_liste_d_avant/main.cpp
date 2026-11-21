#include <iostream>
#include <string>
#include <vector>
#include <unordered_set>

using namespace std;

int main() {
    string mot;
    int n, c, a;

    // Lecture de la liste AVANT
    cin >> mot >> n;

    vector<string> avant(n);
    unordered_set<string> ensembleAvant;

    for (int i = 0; i < n; i++) {
        cin >> avant[i];
        ensembleAvant.insert(avant[i]);
    }

    // Lecture de la liste CORRIGE
    cin >> mot >> c;

    unordered_set<string> corrige;

    for (int i = 0; i < c; i++) {
        string cle;
        cin >> cle;
        corrige.insert(cle);
    }

    // Lecture de la liste APRES
    cin >> mot >> a;

    vector<string> apres(a);
    unordered_set<string> ensembleApres;

    for (int i = 0; i < a; i++) {
        cin >> apres[i];
        ensembleApres.insert(apres[i]);
    }

    // Initialisation des compteurs
    int vraies = 0;
    int fausses = 0;
    int oubliees = 0;
    int nouvelles = 0;

    // Classification des clés de AVANT
    for (int i = 0; i < n; i++) {
        const string& cle = avant[i];

        if (corrige.count(cle)) {
            fausses++;
            cout << i + 1 << " " << cle << " DEVENUE_FAUSSE\n";
        }
        else if (ensembleApres.count(cle)) {
            vraies++;
            cout << i + 1 << " " << cle << " ENCORE_VRAIE\n";
        }
        else {
            oubliees++;
            cout << i + 1 << " " << cle << " OUBLIEE\n";
        }
    }

    // Comptage des nouvelles clés dans APRES
    for (const string& cle : apres) {
        if (!ensembleAvant.count(cle)) {
            nouvelles++;
        }
    }

    // Calcul du pourcentage de clés oubliées
    int partOubliee = 0;

    if (vraies + oubliees > 0) {
        partOubliee = static_cast<int>(
            100LL * oubliees / (vraies + oubliees)
        );
    }

    // Affichage des statistiques
    cout << "VRAIES " << vraies << "\n";
    cout << "FAUSSES " << fausses << "\n";
    cout << "OUBLIEES " << oubliees << "\n";
    cout << "NOUVELLES " << nouvelles << "\n";
    cout << "PART_OUBLIEE " << partOubliee << "\n";

    return 0;
}