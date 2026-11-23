 #include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <tuple>

using namespace std;

struct Evenement {
    long long tour;
    int priorite;
    int ordre;
    string texte;
    bool possible;
};

vector<string> decouper(const string& s, char sep) {
    vector<string> resultat;
    size_t debut = 0;

    while (true) {
        size_t fin = s.find(sep, debut);

        if (fin == string::npos) {
            resultat.push_back(s.substr(debut));
            break;
        }

        resultat.push_back(s.substr(debut, fin - debut));
        debut = fin + 1;
    }

    return resultat;
}

bool lireNombre(const string& s, long long& n) {
    if (s.empty()) {
        return false;
    }

    try {
        size_t pos;
        n = stoll(s, &pos);
        return pos == s.size();
    }
    catch (...) {
        return false;
    }
}

int main() {
    vector<Evenement> evenements;

    int ignores = 0;
    int ordre = 0;

    int captures = 0;
    int clics = 0;
    int depots = 0;

    long long sortie = 0;
    string ligne;

    auto ajouter = [&](long long n, int priorite,
                       const string& texte, bool capture = false) {
        long long tour = capture ? n - 1 : n;

        evenements.push_back({
            tour, priorite, ordre++, texte, n > 0
        });
    };

    while (getline(cin, ligne)) {
        size_t egal = ligne.find('=');

        if (egal == string::npos) {
            ignores++;
            continue;
        }

        string nom = ligne.substr(0, egal);
        string valeur = ligne.substr(egal + 1);

        if (nom == "NK_AGENT_SHOT") {
            vector<string> elements = decouper(valeur, ',');

            for (const string& e : elements) {
                long long n;

                if (!lireNombre(e, n)) {
                    ignores++;
                    continue;
                }

                if (captures >= 8) {
                    ignores++;
                    continue;
                }

                captures++;
                ajouter(n, 7, "CAPTURE", true);
            }
        }

        else if (nom == "NK_AGENT_EXIT") {
            if (!lireNombre(valeur, sortie)) {
                ignores++;
            }
        }

        else if (nom == "NK_AGENT_PAN") {
            vector<string> c = decouper(valeur, ':');
            long long n;

            if (c.size() < 3 || !lireNombre(c[0], n)) {
                ignores++;
                continue;
            }

            ajouter(n, 0, "PAN " + c[1] + " " + c[2]);
        }

        else if (nom == "NK_AGENT_ZOOM") {
            vector<string> c = decouper(valeur, ':');
            long long n;

            if (c.size() < 4 || !lireNombre(c[0], n)) {
                ignores++;
                continue;
            }

            ajouter(n, 1, "ZOOM " + c[1] + " " +
                    c[2] + " " + c[3]);
        }

        else if (nom == "NK_AGENT_DROP") {
            vector<string> elements = decouper(valeur, ';');

            for (const string& e : elements) {
                size_t p1 = e.find(':');
                size_t p2 = e.find(':', p1 == string::npos ? 0 : p1 + 1);
                size_t p3 = e.find(':', p2 == string::npos ? 0 : p2 + 1);

                if (p1 == string::npos ||
                    p2 == string::npos ||
                    p3 == string::npos) {
                    ignores++;
                    continue;
                }

                string sn = e.substr(0, p1);
                string px = e.substr(p1 + 1, p2 - p1 - 1);
                string py = e.substr(p2 + 1, p3 - p2 - 1);
                string chemin = e.substr(p3 + 1);

                long long n;

                if (!lireNombre(sn, n)) {
                    ignores++;
                    continue;
                }

                if (depots >= 8) {
                    ignores++;
                    continue;
                }

                depots++;

                ajouter(n, 2, "DEPOT " + chemin + " " +
                        px + " " + py);
            }
        }

        else if (nom == "NK_AGENT_CLICK") {
            vector<string> elements = decouper(valeur, ';');

            for (const string& e : elements) {
                vector<string> c = decouper(e, ':');
                long long n;

                if (c.size() < 3 || !lireNombre(c[0], n)) {
                    ignores++;
                    continue;
                }

                if (clics >= 8) {
                    ignores++;
                    continue;
                }

                clics++;

                ajouter(n, 3, "CLIC " + c[1] + " " + c[2]);
            }
        }

        else if (nom == "NK_AGENT_MOVE") {
            vector<string> c = decouper(valeur, ':');
            long long n;

            if (c.size() < 3 || !lireNombre(c[0], n)) {
                ignores++;
                continue;
            }

            ajouter(n, 4, "MOVE " + c[1] + " " + c[2]);
        }

        else if (nom == "NK_AGENT_PACK") {
            long long n;

            if (!lireNombre(valeur, n)) {
                ignores++;
                continue;
            }

            ajouter(n, 5, "RANGE");
        }

        else if (nom == "NK_AGENT_GRID") {
            vector<string> c = decouper(valeur, ':');
            long long n;

            if (c.size() < 2 || !lireNombre(c[0], n)) {
                ignores++;
                continue;
            }

            ajouter(n, 6, "GRILLE " + c[1]);
        }

        else {
            ignores++;
        }
    }

    sort(evenements.begin(), evenements.end(),
        [](const Evenement& a, const Evenement& b) {
            return tie(a.tour, a.priorite, a.ordre) <
                   tie(b.tour, b.priorite, b.ordre);
        }
    );

    int jamais = 0;

    for (const Evenement& e : evenements) {
        bool execute = e.possible &&
                       (sortie <= 0 || e.tour < sortie);

        if (execute) {
            cout << "TOUR " << e.tour << " "
                 << e.texte << "\n";
        }
        else {
            jamais++;
        }
    }

    if (sortie > 0) {
        cout << "ARRET " << sortie - 1 << "\n";
    }
    else {
        cout << "SANS_ARRET\n";
    }

    cout << "JAMAIS " << jamais << "\n";
    cout << "IGNORES " << ignores << "\n";

    return 0;
}