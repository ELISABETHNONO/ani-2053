#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <unordered_map>

using namespace std;

struct Entree {
    string nom;
    int valeur;
    int cout;
    string etiquette;
    string genre;
    string cible;
    int ordre;
    bool gardee;
    string raison;
    string categorie;
};

int rangEtiquette(const string& etiquette) {
    if (etiquette == "MESUREE") {
        return 0;
    }

    if (etiquette == "OBSERVEE") {
        return 1;
    }

    return 2;
}

int rangCategorie(const string& categorie) {
    if (categorie == "MAINTENANT") {
        return 0;
    }

    if (categorie == "DECOUPER") {
        return 1;
    }

    if (categorie == "EN_PASSANT") {
        return 2;
    }

    return 3;
}

int main() {
    int n;
    cin >> n;

    vector<Entree> entrees;
    unordered_map<string, int> positions;

    for (int i = 0; i < n; i++) {
        Entree e;

        cin >> e.nom >> e.valeur >> e.cout
            >> e.etiquette >> e.genre;

        e.ordre = i;
        e.gardee = true;
        e.raison = "";
        e.categorie = "";

        if (e.genre == "SOCLE") {
            cin >> e.cible;
        }

        if (e.genre == "REECRITURE") {
            e.gardee = false;
            e.raison = "reecriture";
        } else if (e.genre == "CHOIX") {
            e.gardee = false;
            e.raison = "choix";
        } else if (e.etiquette == "-") {
            e.gardee = false;
            e.raison = "sans_etiquette";
        }

        positions[e.nom] = entrees.size();
        entrees.push_back(e);
    }

    // Calculer la valeur effective des SOCLES.
    for (Entree& e : entrees) {
        if (e.gardee && e.genre == "SOCLE") {
            auto it = positions.find(e.cible);

            if (it != positions.end()) {
                const Entree& cible = entrees[it->second];

                if (cible.gardee && cible.genre == "MANQUE") {
                    e.valeur = max(e.valeur, cible.valeur);
                }
            }
        }
    }

    // Classer les entrees conservees.
    vector<Entree> classees;
    vector<Entree> ecartees;

    for (const Entree& e : entrees) {
        if (!e.gardee) {
            ecartees.push_back(e);
            continue;
        }

        Entree copie = e;

        bool valeurForte = copie.valeur >= 3;
        bool coutEleve = copie.cout >= 3;

        if (valeurForte && !coutEleve) {
            copie.categorie = "MAINTENANT";
        } else if (valeurForte && coutEleve) {
            copie.categorie = "DECOUPER";
        } else if (!valeurForte && !coutEleve) {
            copie.categorie = "EN_PASSANT";
        } else {
            copie.categorie = "ON_NE_LE_FAIT_PAS";
        }

        classees.push_back(copie);
    }

    // Trier selon les regles de l'enonce.
    sort(classees.begin(), classees.end(),
        [](const Entree& a, const Entree& b) {
            if (rangCategorie(a.categorie) != rangCategorie(b.categorie)) {
                return rangCategorie(a.categorie) < rangCategorie(b.categorie);
            }

            if (rangEtiquette(a.etiquette) != rangEtiquette(b.etiquette)) {
                return rangEtiquette(a.etiquette) < rangEtiquette(b.etiquette);
            }

            if (a.valeur != b.valeur) {
                return a.valeur > b.valeur;
            }

            if (a.cout != b.cout) {
                return a.cout < b.cout;
            }

            return a.ordre < b.ordre;
        });

    // Afficher les entrees classees.
    bool refus = false;

    for (const Entree& e : classees) {
        cout << e.categorie << " "
             << e.nom << " "
             << e.etiquette << '\n';

        if (e.categorie == "ON_NE_LE_FAIT_PAS") {
            refus = true;
        }
    }

    // Afficher les entrees ecartees dans leur ordre initial.
    for (const Entree& e : ecartees) {
        cout << "HORS_LISTE "
             << e.nom << " "
             << e.raison << '\n';
    }

    // Afficher le verdict.
    if (refus) {
        cout << "VERDICT HONNETE\n";
    } else {
        cout << "VERDICT COMPLAISANT\n";
    }

    return 0;
}