#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
using namespace std;

struct M {
    string nom;
    bool c, mod;
    vector<int> appels;
};

int main() {
    int n;
    cin >> n;
    vector<M> m(n);
    unordered_map<string, int> id;
    vector<vector<string>> noms(n);

    for (int i = 0; i < n; i++) {
        string c;
        int mod, k;
        cin >> m[i].nom >> c >> mod >> k;
        id[m[i].nom] = i;
        m[i].c = (c == "const");
        m[i].mod = mod;
        while (k--) {
            string s;
            cin >> s;
            noms[i].push_back(s);
        }
    }

    for (int i = 0; i < n; i++)
        for (auto s : noms[i])
            m[i].appels.push_back(id[s]);

    vector<bool> p(n);
    for (int i = 0; i < n; i++)
        p[i] = !m[i].c && !m[i].mod;

    bool change = true;
    while (change) {
        change = false;
        vector<bool> q = p;
        for (int i = 0; i < n; i++)
            if (p[i])
                for (int a : m[i].appels)
                    if (!m[a].c && !p[a])
                        q[i] = false, change = true;
        p = q;
    }

    auto affiche = [&](string titre, vector<bool> v) {
        cout << titre;
        bool ok = false;
        for (int i = 0; i < n; i++)
            if (v[i]) cout << " " << m[i].nom, ok = true;
        if (!ok) cout << " AUCUN";
        cout << '\n';
    };

    affiche("POURRAIT", p);

    vector<bool> racines(n);
    for (int i = 0; i < n; i++) {
        racines[i] = p[i];
        for (int a : m[i].appels)
            if (!m[a].c) racines[i] = false;
    }
    affiche("RACINES", racines);

    vector<bool> d(n);
    int reste = 0, passes = 0;
    for (int i = 0; i < n; i++)
        d[i] = m[i].c, reste += p[i];

    while (reste) {
        vector<int> prets;
        for (int i = 0; i < n; i++) if (p[i] && !d[i]) {
            bool ok = true;
            for (int a : m[i].appels)
                if (!d[a]) ok = false;
            if (ok) prets.push_back(i);
        }
        for (int i : prets) d[i] = true, reste--;
        passes++;
    }

    cout << "PASSES " << passes << '\n';
}