#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main() {
    string mot;
    int intervalle;
    string document;

    cin >> mot >> intervalle >> mot >> document;

    // Variables du composant
    int tempsEcoule = 0;
    int tempsTotal = 0;

    bool change = false;
    bool disqueOK = true;

    // Compteurs
    int sauvegardes = 0;
    int echecs = 0;

    vector<string> resultats;

    string commande;

    while (cin >> commande) {

        if (commande == "TOUCH") {
            change = true;
        }

        else if (commande == "TICK") {
            int d;
            cin >> d;

            if (d > 0) {
                tempsEcoule += d;
                tempsTotal += d;
            }

            if (change && tempsEcoule >= intervalle) {

                if (disqueOK) {
                    resultats.push_back(
                        to_string(tempsTotal) + " SECOURS"
                    );

                    sauvegardes++;

                    change = false;
                    tempsEcoule = 0;
                }
                else {
                    resultats.push_back(
                        to_string(tempsTotal) + " ECHEC"
                    );

                    echecs++;
                }
            }
        }

        else if (commande == "CTRL_S") {

            if (disqueOK) {
                resultats.push_back(
                    to_string(tempsTotal) + " MANUELLE"
                );

                change = false;
                tempsEcoule = 0;
            }
            else {
                resultats.push_back(
                    to_string(tempsTotal) + " MANUELLE_ECHEC"
                );

                echecs++;
            }
        }

        else if (commande == "DISQUE") {
            string etat;
            cin >> etat;

            disqueOK = (etat == "OK");
        }
    }

    // Affichage des tentatives
    for (const string& resultat : resultats) {
        cout << resultat << '\n';
    }

    // Calcul du nom du fichier de secours
    string nomSecours;

    if (document == "-") {
        nomSecours = "planche-sans-nom.nkref.auto";
    }
    else {
        nomSecours = document + ".auto";
    }

    // Affichage du bilan
    cout << "SAUVEGARDES " << sauvegardes << '\n';

    cout << "ECHECS " << echecs << '\n';

    cout << "EN_ATTENTE "
         << (change ? "OUI" : "NON") << '\n';

    cout << "SECOURS_NOM " << nomSecours << '\n';

    return 0;
}