#include <iostream>
#include <vector>
#include <string>

using namespace std;

struct Composant {
    string nom;
    string lieu;
    string touche;
    string filet;
};

int main() {
    int k;
    string mot;

    // Lecture des parties intouchables
    cin >> mot >> k;

    vector<string> intouchables(k);

    for (int i = 0; i < k; i++) {
        cin >> intouchables[i];
    }

    // Lecture du nombre de composants
    int n;
    cin >> n;

    vector<Composant> composants;

    int purs = 0;
    int a_revoir = 0;
    int filets_a_poser = 0;

    vector<string> prets;

    for (int i = 0; i < n; i++) {
        Composant c;

        int b, t, e;

        cin >> c.nom;

        // Lecture des besoins
        cin >> b;

        bool glue = false;
        bool decouper = false;

        for (int j = 0; j < b; j++) {
            string besoin;
            cin >> besoin;

            if (besoin == "FENETRE" ||
                besoin == "SOURIS" ||
                besoin == "CLAVIER" ||
                besoin == "GPU") {
                glue = true;
            }

            if (besoin == "DISQUE" ||
                besoin == "HORLOGE" ||
                besoin == "RESEAU") {
                decouper = true;
            }
        }

        // Détermination du lieu
        if (glue) {
            c.lieu = "GLUE";
        }
        else if (decouper) {
            c.lieu = "DECOUPER";
        }
        else {
            c.lieu = "FICHIER_PUR";
        }

        if (c.lieu == "FICHIER_PUR") {
            purs++;
        }

        // Lecture des parties modifiées
        cin >> t;

        vector<string> modifications(t);

        for (int j = 0; j < t; j++) {
            cin >> modifications[j];
        }

        // Recherche de la première partie intouchable
        c.touche = "INTACT";

        for (int j = 0; j < t; j++) {
            for (int h = 0; h < k; h++) {
                if (modifications[j] == intouchables[h]) {
                    c.touche = "REVOIR " + modifications[j];
                    break;
                }
            }

            if (c.touche != "INTACT") {
                break;
            }
        }

        if (c.touche != "INTACT") {
            a_revoir++;
        }

        // Lecture du nombre de tests existants
        cin >> e;

        if (e == 0) {
            c.filet = "FILET_D_ABORD";
            filets_a_poser++;
        }
        else {
            c.filet = "FILET_EXISTANT";
        }

        // Vérification si le composant est prêt
        if (c.touche == "INTACT" &&
            c.filet == "FILET_EXISTANT") {
            prets.push_back(c.nom);
        }

        composants.push_back(c);
    }

    // Affichage des résultats de chaque composant
    for (const Composant& c : composants) {
        cout << c.nom << " "
             << c.lieu << " "
             << c.touche << " "
             << c.filet << '\n';
    }

    // Affichage des statistiques
    cout << "PURS " << purs << '\n';
    cout << "A_REVOIR " << a_revoir << '\n';
    cout << "FILETS_A_POSER " << filets_a_poser << '\n';

    cout << "PRETS";

    if (prets.empty()) {
        cout << " AUCUN";
    }
    else {
        for (const string& nom : prets) {
            cout << " " << nom;
        }
    }

    cout << '\n';

    return 0;
}