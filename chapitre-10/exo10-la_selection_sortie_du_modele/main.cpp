#include <iostream>
#include <vector>
#include <string>
#include <set>
#include <algorithm>

using namespace std;

struct Image
{
    string nom;
    bool selectionnee = false;
};

bool existe(const vector<Image>& planche, int i)
{
    return i >= 0 && i < static_cast<int>(planche.size());
}

vector<string> nomsPlanche(const vector<Image>& planche)
{
    vector<string> resultat;

    for (const Image& image : planche)
        resultat.push_back(image.nom);

    return resultat;
}

vector<string> nomsSelection(
    const vector<Image>& planche,
    const set<int>& indices,
    const set<string>& identifiants,
    int conception)
{
    vector<string> resultat;

    for (size_t i = 0; i < planche.size(); i++)
    {
        bool choisie = false;

        if (conception == 0)
            choisie = planche[i].selectionnee;
        else if (conception == 1)
            choisie = indices.count(static_cast<int>(i)) > 0;
        else
            choisie = identifiants.count(planche[i].nom) > 0;

        if (choisie)
            resultat.push_back(planche[i].nom);
    }

    return resultat;
}

void afficherListe(const string& prefixe, const vector<string>& liste)
{
    cout << prefixe;

    if (liste.empty())
        cout << " AUCUN";
    else
        for (const string& nom : liste)
            cout << " " << nom;

    cout << "\n";
}

void echanger(vector<Image>& planche, int i, int j)
{
    if (existe(planche, i) && existe(planche, j))
        swap(planche[i], planche[j]);
}

void retirer(vector<Image>& planche, int i)
{
    if (existe(planche, i))
        planche.erase(planche.begin() + i);
}

void supprimerSelection(
    vector<Image>& planche,
    const set<int>& indices,
    const set<string>& identifiants,
    int conception)
{
    vector<Image> restante;

    for (size_t i = 0; i < planche.size(); i++)
    {
        bool supprimer = false;

        if (conception == 0)
            supprimer = planche[i].selectionnee;
        else if (conception == 1)
            supprimer = indices.count(static_cast<int>(i)) > 0;
        else
            supprimer = identifiants.count(planche[i].nom) > 0;

        if (!supprimer)
            restante.push_back(planche[i]);
    }

    planche = restante;
}

int main()
{
    vector<Image> dansItem;
    vector<Image> parIndex;
    vector<Image> parId;

    set<int> selectionIndices;
    set<string> selectionIds;

    string commande;

    while (cin >> commande)
    {
        if (commande == "AJOUTE")
        {
            string nom;
            cin >> nom;

            dansItem.push_back({nom, false});
            parIndex.push_back({nom, false});
            parId.push_back({nom, false});
        }

        else if (commande == "CLIC")
        {
            int i;
            cin >> i;

            for (Image& image : dansItem)
                image.selectionnee = false;

            selectionIndices.clear();
            selectionIds.clear();

            if (existe(dansItem, i))
            {
                dansItem[i].selectionnee = true;
                selectionIndices.insert(i);
                selectionIds.insert(parId[i].nom);
            }
        }

        else if (commande == "AJOUTE_SEL")
        {
            int i;
            cin >> i;

            if (existe(dansItem, i))
            {
                dansItem[i].selectionnee = true;
                selectionIndices.insert(i);
                selectionIds.insert(parId[i].nom);
            }
        }

        else if (commande == "ECHANGE")
        {
            int i, j;
            cin >> i >> j;

            echanger(dansItem, i, j);
            echanger(parIndex, i, j);
            echanger(parId, i, j);
        }

        else if (commande == "RETIRE")
        {
            int i;
            cin >> i;

            retirer(dansItem, i);
            retirer(parIndex, i);
            retirer(parId, i);
        }

        else if (commande == "SUPPRIME")
        {
            supprimerSelection(dansItem, selectionIndices,
                               selectionIds, 0);

            supprimerSelection(parIndex, selectionIndices,
                               selectionIds, 1);

            supprimerSelection(parId, selectionIndices,
                               selectionIds, 2);

            selectionIndices.clear();
            selectionIds.clear();
        }
    }

    // Affichage de DANS_ITEM
    vector<string> plan1 = nomsPlanche(dansItem);
    vector<string> sel1 = nomsSelection(
        dansItem, selectionIndices, selectionIds, 0);

    afficherListe("DANS_ITEM PLANCHE", plan1);
    afficherListe("DANS_ITEM SELECTION", sel1);

    // Affichage de PAR_INDEX
    vector<string> plan2 = nomsPlanche(parIndex);
    vector<string> sel2 = nomsSelection(
        parIndex, selectionIndices, selectionIds, 1);

    afficherListe("PAR_INDEX PLANCHE", plan2);
    afficherListe("PAR_INDEX SELECTION", sel2);

    // Affichage de PAR_ID
    vector<string> plan3 = nomsPlanche(parId);
    vector<string> sel3 = nomsSelection(
        parId, selectionIndices, selectionIds, 2);

    afficherListe("PAR_ID PLANCHE", plan3);
    afficherListe("PAR_ID SELECTION", sel3);

    cout << "FAUX";

    if (plan1 != plan2 || sel1 != sel2)
        cout << " PAR_INDEX";

    if (plan1 != plan3 || sel1 != sel3)
        cout << " PAR_ID";

    if (plan1 == plan2 && plan1 == plan3 &&
        sel1 == sel2 && sel1 == sel3)
        cout << " AUCUN";

    cout << "\n";

    return 0;
}