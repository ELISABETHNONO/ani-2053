#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
using namespace std;

struct Operation {
    string type, a, b;
    int ligne;
};

int main() {
    int n;
    cin >> n;

    vector<Operation> ops;
    vector<string> variables;
    unordered_map<string, int> ids;
    vector<int> refus;

    auto ajouter = [&](string nom) {
        if (!ids.count(nom)) {
            ids[nom] = variables.size();
            variables.push_back(nom);
        }
    };

    for (int i = 1; i <= n; i++) {
        Operation op;
        op.ligne = i;
        cin >> op.type;

        if (op.type == "NEW" || op.type == "RESET" ||
            op.type == "USE") {
            cin >> op.a;
            ajouter(op.a);
        }
        else {
            cin >> op.a >> op.b;
            ajouter(op.a);
            ajouter(op.b);

            if (op.type == "COPY")
                refus.push_back(i);
        }

        ops.push_back(op);
    }

    if (!refus.empty()) {
        for (int k : refus)
            cout << "REFUSE " << k << '\n';
        return 0;
    }

    vector<int> objets(variables.size(), 0);
    int crees = 0, detruits = 0, nuls = 0;

    auto detruire = [&](int objet) {
        if (objet != 0) {
            cout << "DETRUIT " << objet << '\n';
            detruits++;
        }
    };

    for (auto op : ops) {
        int a = ids[op.a];

        if (op.type == "NEW") {
            int nouveau = ++crees;
            detruire(objets[a]);
            objets[a] = nouveau;
        }
        else if (op.type == "MOVE") {
            int b = ids[op.b];
            int objet = objets[a];
            objets[a] = 0;
            detruire(objets[b]);
            objets[b] = objet;
        }
        else if (op.type == "RESET") {
            detruire(objets[a]);
            objets[a] = 0;
        }
        else if (op.type == "USE") {
            if (objets[a] == 0) {
                cout << "NUL " << op.ligne << " " << op.a << '\n';
                nuls++;
            }
        }
    }

    for (int i = objets.size() - 1; i >= 0; i--)
        detruire(objets[i]);

    cout << "CREES " << crees << '\n';
    cout << "DETRUITS " << detruits << '\n';
    cout << "NULS " << nuls << '\n';
}