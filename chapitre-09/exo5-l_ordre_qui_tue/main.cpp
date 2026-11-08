#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <unordered_map>
using namespace std;

struct Objet {
    string nom;
    bool libere = false;
    vector<int> dependances;
};

int main() {
    vector<Objet> objets;
    unordered_map<string, int> id;
    vector<vector<int>> blocs(1);
    string ligne;

    auto liberer = [&](int x, string action) {
        for (int b : objets[x].dependances) {
            if (objets[b].libere) {
                cout << "PLANTAGE " << objets[x].nom
                     << " " << objets[b].nom << '\n';
                return false;
            }
        }
        objets[x].libere = true;
        cout << action << " " << objets[x].nom << '\n';
        return true;
    };

    while (getline(cin, ligne)) {
        istringstream in(ligne);
        string op, a, b;
        in >> op;

        if (op == "DECL") {
            in >> a;
            int x = objets.size();
            id[a] = x;
            objets.push_back({a});
            blocs.back().push_back(x);
        }
        else if (op == "DEPEND") {
            in >> a >> b;
            objets[id[a]].dependances.push_back(id[b]);
        }
        else if (op == "FERME") {
            in >> a;
            if (!objets[id[a]].libere)
                if (!liberer(id[a], "FERME")) return 0;
        }
        else if (op == "{") {
            blocs.push_back({});
        }
        else if (op == "}") {
            for (int i = blocs.back().size() - 1; i >= 0; i--)
                if (!objets[blocs.back()[i]].libere)
                    if (!liberer(blocs.back()[i], "DETRUIT"))
                        return 0;
            blocs.pop_back();
        }
    }

    for (int i = blocs[0].size() - 1; i >= 0; i--)
        if (!objets[blocs[0][i]].libere)
            if (!liberer(blocs[0][i], "DETRUIT"))
                return 0;

    cout << "PROPRE\n";
}