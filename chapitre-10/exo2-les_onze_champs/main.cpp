#include <iostream>
#include <string>
using namespace std;

int main() {
    int n;
    cin >> n;

    int restent = 0, changes = 0;

    for (int i = 1; i <= n; i++) {
        int id, miroirX, miroirY, largeur, hauteur, selectionne;
        double x, y, echelle, rotation, opacite;
        string chemin;
        long long octets;

        cin >> id >> x >> y >> echelle >> rotation
            >> opacite >> miroirX >> miroirY
            >> largeur >> hauteur >> selectionne
            >> chemin >> octets;

        if (octets == 0) {
            cout << "ITEM " << i << " SAUTE\n";
            continue;
        }

        restent++;
        int nb = 0;

        cout << "ITEM " << i << " " << restent;

        if (id != 0) {
            cout << " id";
            nb++;
        }

        if (selectionne != 0) {
            cout << " selected";
            nb++;
        }

        if (chemin != "-") {
            cout << " sourcePath";
            nb++;
        }

        if (nb == 0)
            cout << " AUCUN";

        cout << "\n";
        changes += nb;
    }

    cout << "RESTENT " << restent << "\n";
    cout << "CHANGES " << changes << "\n";

    return 0;
}