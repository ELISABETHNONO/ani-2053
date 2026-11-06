
#include <iostream>
#include <string>
#include <array>
#include <algorithm>

using namespace std;

int main() {

    string C;
    getline(cin, C);

    array<string, 5> noms = {
        "DESTRUCTEUR",
        "COPIE",
        "AFFECTATION_COPIE",
        "DEPLACEMENT",
        "AFFECTATION_DEPLACEMENT"
    };

    array<string, 5> etats = {
        "ABSENT", "ABSENT", "ABSENT", "ABSENT", "ABSENT"
    };

    string ligne;

    while (getline(cin, ligne)) {

        // Supprimer les commentaires
        size_t commentaire = ligne.find("//");

        if (commentaire != string::npos) {
            ligne = ligne.substr(0, commentaire);
        }

        // Supprimer les espaces
        ligne.erase(
            remove(ligne.begin(), ligne.end(), ' '),
            ligne.end()
        );

        if (ligne.empty()) {
            continue;
        }

        // Déterminer l'état du membre
        string etat = "ECRIT";

        if (ligne.size() >= 8 &&
            ligne.substr(ligne.size() - 8) == "=delete;") {
            etat = "SUPPRIME";
        }
        else if (ligne.size() >= 9 &&
                 ligne.substr(ligne.size() - 9) == "=default;") {
            etat = "DEFAUT";
        }

        // Reconnaître le destructeur
        if (ligne.find("~" + C + "(") != string::npos) {
            etats[0] = etat;
        }

        // Reconnaître le constructeur de copie
        string copie = C + "(const" + C + "&";

        if (ligne.rfind(copie, 0) == 0 &&
            (ligne.size() == copie.size() ||
             ligne[copie.size()] != '&')) {
            etats[1] = etat;
        }

        // Reconnaître l'affectation par copie
        string affectationCopie =
            C + "&operator=(const" + C + "&";

        if (ligne.rfind(affectationCopie, 0) == 0 &&
            (ligne.size() == affectationCopie.size() ||
             ligne[affectationCopie.size()] != '&')) {
            etats[2] = etat;
        }

        // Reconnaître le constructeur de déplacement
        string deplacement = C + "(" + C + "&&";

        if (ligne.rfind(deplacement, 0) == 0) {
            etats[3] = etat;
        }

        // Reconnaître l'affectation par déplacement
        string affectationDeplacement =
            C + "&operator=(" + C + "&&";

        if (ligne.rfind(affectationDeplacement, 0) == 0) {
            etats[4] = etat;
        }
    }

    // Afficher les cinq états
    for (int i = 0; i < 5; i++) {
        cout << noms[i] << " " << etats[i] << '\n';
    }

    // Déterminer la règle
    int nombre = 0;

    for (int i = 0; i < 5; i++) {
        if (etats[i] != "ABSENT") {
            nombre++;
        }
    }

    string regle;

    if (nombre == 0) {
        regle = "ZERO";
    }
    else if (nombre == 5) {
        regle = "CINQ";
    }
    else if (etats[0] != "ABSENT" &&
             etats[1] != "ABSENT" &&
             etats[2] != "ABSENT" &&
             etats[3] == "ABSENT" &&
             etats[4] == "ABSENT") {
        regle = "TROIS";
    }
    else {
        regle = "INCOMPLETE";
    }

    cout << "REGLE " << regle << '\n';

    // Déterminer la possession
    cout << "POSSEDE "
         << (etats[0] == "ECRIT" ? "OUI" : "NON")
         << '\n';

    // Déterminer si la classe est unique
    bool unique =
        etats[1] == "SUPPRIME" &&
        (etats[3] == "ECRIT" || etats[3] == "DEFAUT");

    cout << "UNIQUE " << (unique ? "OUI" : "NON") << '\n';

    // Afficher les membres manquants
    if (regle == "INCOMPLETE") {

        bool deplacementDeclare =
            etats[3] != "ABSENT" || etats[4] != "ABSENT";

        int limite = deplacementDeclare ? 5 : 3;

        for (int i = 0; i < limite; i++) {
            if (etats[i] == "ABSENT") {
                cout << "MANQUE " << noms[i] << '\n';
            }
        }
    }

    return 0;
}