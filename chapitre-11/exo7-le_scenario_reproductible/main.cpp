#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include <tuple>

using namespace std;

struct Evenement {
    long long tour;
    int priorite;
    int ordre;
    string resultat;
};

vector<string> decouper(const string& texte, char separateur) {
    vector<string> morceaux;
    string morceau;
    stringstream flux(texte);

    while (getline(flux, morceau, separateur)) {
        morceaux.push_back(morceau);
    }

    if (!texte.empty() && texte.back() == separateur) {
        morceaux.push_back("");
    }

    return morceaux;
}

bool lireNombre(const string& texte, long long& nombre) {
    if (texte.empty()) {
        return false;
    }

    try {
        size_t position;
        nombre = stoll(texte, &position);

        return position == texte.size();
    }
    catch (...) {
        return false;
    }
}

int main() {
    vector<Evenement> evenements;

    int ignores = 0;
    int ordre = 0;

    long long sortie = 0;

    int captures = 0;
    int clics = 0;
    int depots = 0;

    string ligne;

    while (getline(cin, ligne)) {
        if (!ligne.empty() && ligne.back() == '\r') {
            ligne.pop_back();
        }

        size_t egal = ligne.find('=');

        if (egal == string::npos) {
            ignores++;
            continue;
        }

        string nom = ligne.substr(0, egal);
        string valeur = ligne.substr(egal + 1);

        // CAPTURES
        if (nom == "NK_AGENT_SHOT") {
            vector<string> elements = decouper(valeur, ',');

            for (const string& element : elements) {
                long long n;

                if (!lireNombre(element, n)) {
                    ignores++;
                    continue;
                }

                if (captures >= 8) {
                    ignores++;
                    continue;
                }

                captures++;

                if (n > 0) {
                    evenements.push_back({
                        n - 1, 7, ordre++, "CAPTURE"
                    });
                }
            }
        }

        // SORTIE
        else if (nom == "NK_AGENT_EXIT") {
            if (!lireNombre(valeur, sortie)) {
                ignores++;
            }
        }

        // PAN
        else if (nom == "NK_AGENT_PAN") {
            vector<string> champs = decouper(valeur, ':');

            long long n, dx, dy;

            if (champs.size() < 3 ||
                !lireNombre(champs[0], n) ||
                !lireNombre(champs[1], dx) ||
                !lireNombre(champs[2], dy)) {
                ignores++;
                continue;
            }

            if (n > 0) {
                evenements.push_back({
                    n, 0, ordre++,
                    "PAN " + to_string(dx) + " " + to_string(dy)
                });
            }
        }

        // ZOOM
        else if (nom == "NK_AGENT_ZOOM") {
            vector<string> champs = decouper(valeur, ':');

            long long n, f, px, py;

            if (champs.size() < 4 ||
                !lireNombre(champs[0], n) ||
                !lireNombre(champs[1], f) ||
                !lireNombre(champs[2], px) ||
                !lireNombre(champs[3], py)) {
                ignores++;
                continue;
            }

            if (n > 0) {
                evenements.push_back({
                    n, 1, ordre++,
                    "ZOOM " + to_string(f) + " " +
                    to_string(px) + " " + to_string(py)
                });
            }
        }

        // DEPOTS
        else if (nom == "NK_AGENT_DROP") {
            vector<string> elements = decouper(valeur, ';');

            for (const string& element : elements) {
                size_t p1 = element.find(':');
                size_t p2 = element.find(':', p1 == string::npos ? 0 : p1 + 1);
                size_t p3 = element.find(':', p2 == string::npos ? 0 : p2 + 1);

                long long n, px, py;

                if (p1 == string::npos ||
                    p2 == string::npos ||
                    p3 == string::npos) {
                    ignores++;
                    continue;
                }

                string sn = element.substr(0, p1);
                string sx = element.substr(p1 + 1, p2 - p1 - 1);
                string sy = element.substr(p2 + 1, p3 - p2 - 1);
                string chemin = element.substr(p3 + 1);

                if (!lireNombre(sn, n) ||
                    !lireNombre(sx, px) ||
                    !lireNombre(sy, py) ||
                    chemin.empty()) {
                    ignores++;
                    continue;
                }

                if (depots >= 8) {
                    ignores++;
                    continue;
                }

                depots++;

                if (n > 0) {
                    evenements.push_back({
                        n, 2, ordre++,
                        "DEPOT " + chemin + " " +
                        to_string(px) + " " + to_string(py)
                    });
                }
            }
        }

        // CLICS
        else if (nom == "NK_AGENT_CLICK") {
            vector<string> elements = decouper(valeur, ';');

            for (const string& element : elements) {
                vector<string> champs = decouper(element, ':');

                long long n, px, py;

                if (champs.size() < 3 ||
                    !lireNombre(champs[0], n) ||
                    !lireNombre(champs[1], px) ||
                    !lireNombre(champs[2], py)) {
                    ignores++;
                    continue;
                }

                if (clics >= 8) {
                    ignores++;
                    continue;
                }

                clics++;

                if (n > 0) {
                    evenements.push_back({
                        n, 3, ordre++,
                        "CLIC " + to_string(px) + " " + to_string(py)
                    });
                }
            }
        }

        // DEPLACEMENT
        else if (nom == "NK_AGENT_MOVE") {
            vector<string> champs = decouper(valeur, ':');

            long long n, dx, dy;

            if (champs.size() < 3 ||
                !lireNombre(champs[0], n) ||
                !lireNombre(champs[1], dx) ||
                !lireNombre(champs[2], dy)) {
                ignores++;
                continue;
            }

            if (n > 0) {
                evenements.push_back({
                    n, 4, ordre++,
                    "MOVE " + to_string(dx) + " " + to_string(dy)
                });
            }
        }

        // RANGEMENT
        else if (nom == "NK_AGENT_PACK") {
            long long n;

            if (!lireNombre(valeur, n)) {
                ignores++;
                continue;
            }

            if (n > 0) {
                evenements.push_back({
                    n, 5, ordre++, "RANGE"
                });
            }
        }

        // GRILLE
        else if (nom == "NK_AGENT_GRID") {
            vector<string> champs = decouper(valeur, ':');

            long long n;

            if (champs.size() < 2 ||
                !lireNombre(champs[0], n)) {
                ignores++;
                continue;
            }

            if (n > 0) {
                evenements.push_back({
                    n, 6, ordre++,
                    "GRILLE " + champs[1]
                });
            }
        }

        // NOM INCONNU
        else {
            ignores++;
        }
    }

    // Classement chronologique des événements
    sort(evenements.begin(), evenements.end(),
        [](const Evenement& a, const Evenement& b) {
            return tie(a.tour, a.priorite, a.ordre) <
                   tie(b.tour, b.priorite, b.ordre);
        }
    );

    int jamais = 0;

    // Affichage des événements exécutés
    for (const Evenement& evenement : evenements) {
        bool execute = (sortie <= 0 || evenement.tour < sortie);

        if (execute) {
            cout << "TOUR " << evenement.tour
                 << " " << evenement.resultat << "\n";
        } else {
            jamais++;
        }
    }

    // Affichage final
    if (sortie > 0) {
        cout << "ARRET " << sortie - 1 << "\n";
    } else {
        cout << "SANS_ARRET\n";
    }

    cout << "JAMAIS " << jamais << "\n";
    cout << "IGNORES " << ignores << "\n";

    return 0;
}