#include <iostream>
#include <string>
#include <vector>
#include <unordered_set>
#include <unordered_map>

using namespace std;

struct Commit {
    string hash;
    unordered_set<string> fonctions;
};

struct Annonce {
    string hash;
    string etat;
    string fonction;
};

int main() {
    int h;
    cin >> h;

    vector<Commit> commits(h);
    unordered_map<string, int> position;

    unordered_set<string> presentes;

    // Lecture des commits et construction de l'historique
    for (int i = 0; i < h; i++) {
        string action;
        int k;

        cin >> commits[i].hash >> action >> k;

        position[commits[i].hash] = i;

        for (int j = 0; j < k; j++) {
            string fonction;
            cin >> fonction;

            if (action == "AJOUTE") {
                presentes.insert(fonction);
            } else if (action == "RETIRE") {
                presentes.erase(fonction);
            }
        }

        commits[i].fonctions = presentes;
    }

    // Lecture des annonces
    int a;
    cin >> a;

    vector<Annonce> annonces(a);

    for (int i = 0; i < a; i++) {
        cin >> annonces[i].hash
            >> annonces[i].etat
            >> annonces[i].fonction;
    }

    int mensonges = 0;

    // Vérification de chaque annonce
    for (int i = 0; i < a; i++) {
        const Annonce& annonce = annonces[i];

        int debut = position[annonce.hash];

        auto estFausse = [&](int indice) {
            bool existe = commits[indice].fonctions.count(
                annonce.fonction
            ) > 0;

            if (annonce.etat == "A_VENIR") {
                return existe;
            }

            return !existe;
        };

        // Vérification au dernier commit
        if (!estFausse(h - 1)) {
            cout << "ANNONCE " << i + 1 << " VRAI\n";
        } else {
            mensonges++;

            // Recherche du début du mensonge continu
            int debutMensonge = h - 1;

            while (debutMensonge > debut &&
                   estFausse(debutMensonge - 1)) {
                debutMensonge--;
            }

            cout << "ANNONCE " << i + 1
                 << " MENT "
                 << commits[debutMensonge].hash << "\n";
        }
    }

    cout << "MENSONGES " << mensonges << "\n";

    return 0;
}