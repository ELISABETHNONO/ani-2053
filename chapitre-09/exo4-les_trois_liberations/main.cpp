#include <iostream>
#include <vector>
using namespace std;

int main() {
    int S, V, F, N;
    cin >> S >> V >> F >> N;

    vector<int> tableau;
    vector<bool> liberees(1, false);
    int creees = 0;

    auto liberer = [&](int t, int fois, string k) {
        for (int j = 0; j < fois; j++) {
            if (liberees[t]) {
                cout << "PLANTAGE " << k << " TEXTURE " << t << '\n';
                return false;
            }
            liberees[t] = true;
        }
        return true;
    };

    for (int k = 1; k <= N; k++) {
        string operation;
        cin >> operation;

        if (operation == "AJOUTE") {
            tableau.push_back(++creees);
            liberees.push_back(false);
        }
        else if (operation == "SUPPRIME") {
            int i;
            cin >> i;
            int t = tableau[i];

            if (!liberer(t, S, to_string(k)))
                return 0;

            tableau.erase(tableau.begin() + i);
        }
        else if (operation == "VIDE") {
            for (int t : tableau)
                if (!liberer(t, V, to_string(k)))
                    return 0;

            tableau.clear();
        }
    }

    for (int t : tableau)
        if (!liberer(t, F, "FIN"))
            return 0;

    cout << "CREEES " << creees << '\n';

    int fuites = 0;
    for (int t = 1; t <= creees; t++)
        if (!liberees[t])
            fuites++;

    cout << "FUITES " << fuites << '\n';
    cout << "PERDUES";

    for (int t = 1; t <= creees; t++)
        if (!liberees[t])
            cout << " " << t;

    if (fuites == 0)
        cout << " AUCUN";

    cout << '\n';
}