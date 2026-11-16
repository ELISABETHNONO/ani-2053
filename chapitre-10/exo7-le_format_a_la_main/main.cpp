#include <iostream>
#include <vector>
#include <string>
#include <cstdint>
#include <cstddef>
#include <cstring>
#include <iomanip>
#include <cmath>
#include <limits>

using namespace std;

// --------------------------------------------------
// Lecture des données binaires
// --------------------------------------------------

struct Lecteur
{
    const vector<uint8_t>& octets;
    size_t position = 0;

    bool lireU8(uint8_t& valeur)
    {
        if (position >= octets.size())
            return false;

        valeur = octets[position++];
        return true;
    }

    bool lireU32(uint32_t& valeur)
    {
        if (octets.size() - position < 4)
            return false;

        valeur = static_cast<uint32_t>(octets[position])
               | (static_cast<uint32_t>(octets[position + 1]) << 8)
               | (static_cast<uint32_t>(octets[position + 2]) << 16)
               | (static_cast<uint32_t>(octets[position + 3]) << 24);

        position += 4;
        return true;
    }

    bool lireF32(float& valeur)
    {
        uint32_t bits;

        if (!lireU32(bits))
            return false;

        memcpy(&valeur, &bits, sizeof(valeur));
        return true;
    }

    bool sauter(size_t nombre)
    {
        if (nombre > octets.size() - position)
            return false;

        position += nombre;
        return true;
    }
};

// --------------------------------------------------
// Structures des données
// --------------------------------------------------

struct Image
{
    float x, y, echelle, rotation, opacite;
    uint8_t miroirX, miroirY;
    uint32_t largeur, hauteur, taille;
};

struct Point
{
    float x, y;
};

struct Trait
{
    uint8_t r, g, b, a;
    float epaisseur;
    vector<Point> points;
};

struct Planche
{
    float cx, cy, zoom;
    uint8_t theme, grille;

    vector<Image> images;
    vector<Trait> traits;
};

// --------------------------------------------------
// Affichage des nombres décimaux
// --------------------------------------------------

void afficherFloat(float valeur)
{
    if (fabs(valeur) < 0.005f)
        valeur = 0.0f;

    cout << fixed << setprecision(2) << valeur;
}

// --------------------------------------------------
// Lecture complète de la planche
// --------------------------------------------------

bool lirePlanche(Lecteur& lecteur, Planche& planche)
{
    // Lecture de la vue
    if (!lecteur.lireF32(planche.cx) ||
        !lecteur.lireF32(planche.cy) ||
        !lecteur.lireF32(planche.zoom))
        return false;

    // Lecture du thème et de la grille
    if (!lecteur.lireU8(planche.theme) ||
        !lecteur.lireU8(planche.grille))
        return false;

    // Deux octets de remplissage
    if (!lecteur.sauter(2))
        return false;

    // Nombre d'images
    uint32_t nombreImages;

    if (!lecteur.lireU32(nombreImages))
        return false;

    for (uint32_t i = 0; i < nombreImages; i++)
    {
        Image image;

        if (!lecteur.lireF32(image.x) ||
            !lecteur.lireF32(image.y) ||
            !lecteur.lireF32(image.echelle) ||
            !lecteur.lireF32(image.rotation) ||
            !lecteur.lireF32(image.opacite))
            return false;

        if (!lecteur.lireU8(image.miroirX) ||
            !lecteur.lireU8(image.miroirY))
            return false;

        // Deux octets ignorés
        if (!lecteur.sauter(2))
            return false;

        if (!lecteur.lireU32(image.largeur) ||
            !lecteur.lireU32(image.hauteur) ||
            !lecteur.lireU32(image.taille))
            return false;

        // Ignorer les données sources de l'image
        if (!lecteur.sauter(image.taille))
            return false;

        planche.images.push_back(image);
    }

    // Nombre de traits
    uint32_t nombreTraits;

    if (!lecteur.lireU32(nombreTraits))
        return false;

    for (uint32_t i = 0; i < nombreTraits; i++)
    {
        Trait trait;

        if (!lecteur.lireU8(trait.r) ||
            !lecteur.lireU8(trait.g) ||
            !lecteur.lireU8(trait.b) ||
            !lecteur.lireU8(trait.a))
            return false;

        if (!lecteur.lireF32(trait.epaisseur))
            return false;

        uint32_t nombrePoints;

        if (!lecteur.lireU32(nombrePoints))
            return false;

        for (uint32_t j = 0; j < nombrePoints; j++)
        {
            Point point;

            if (!lecteur.lireF32(point.x) ||
                !lecteur.lireF32(point.y))
                return false;

            trait.points.push_back(point);
        }

        planche.traits.push_back(trait);
    }

    return true;
}

// --------------------------------------------------
// Affichage de la planche
// --------------------------------------------------

void afficherPlanche(const Planche& planche)
{
    cout << "VUE ";
    afficherFloat(planche.cx);
    cout << " ";
    afficherFloat(planche.cy);
    cout << " ";
    afficherFloat(planche.zoom);
    cout << "\n";

    cout << "THEME "
         << (planche.theme != 0 ? "SOMBRE" : "CLAIR")
         << "\n";

    cout << "GRILLE "
         << (planche.grille == 0 ? "AFFICHEE" : "CACHEE")
         << "\n";

    cout << "IMAGES " << planche.images.size() << "\n";

    for (size_t i = 0; i < planche.images.size(); i++)
    {
        const Image& image = planche.images[i];

        cout << "IMAGE " << i + 1 << " ";

        afficherFloat(image.x);
        cout << " ";
        afficherFloat(image.y);
        cout << " ";
        afficherFloat(image.echelle);
        cout << " ";
        afficherFloat(image.rotation);
        cout << " ";
        afficherFloat(image.opacite);

        cout << " "
             << (image.miroirX != 0 ? 1 : 0)
             << " "
             << (image.miroirY != 0 ? 1 : 0)
             << " "
             << image.largeur
             << " "
             << image.hauteur
             << " "
             << image.taille
             << "\n";
    }

    cout << "TRAITS " << planche.traits.size() << "\n";

    for (size_t i = 0; i < planche.traits.size(); i++)
    {
        const Trait& trait = planche.traits[i];

        cout << "TRAIT " << i + 1 << " "
             << static_cast<int>(trait.r) << " "
             << static_cast<int>(trait.g) << " "
             << static_cast<int>(trait.b) << " "
             << static_cast<int>(trait.a) << " ";

        afficherFloat(trait.epaisseur);

        cout << " " << trait.points.size() << "\n";

        for (const Point& point : trait.points)
        {
            cout << "POINT ";
            afficherFloat(point.x);
            cout << " ";
            afficherFloat(point.y);
            cout << "\n";
        }
    }
}

// --------------------------------------------------
// Programme principal
// --------------------------------------------------

int main()
{
    size_t nombreOctets;

    if (!(cin >> nombreOctets))
    {
        cout << "TRONQUE\n";
        return 0;
    }

    vector<uint8_t> octets;

    for (size_t i = 0; i < nombreOctets; i++)
    {
        string valeur;

        if (!(cin >> valeur))
        {
            cout << "TRONQUE\n";
            return 0;
        }

        try
        {
            size_t position = 0;
            unsigned long nombre = stoul(valeur, &position, 16);

            if (position != valeur.size() || nombre > 255)
            {
                cout << "TRONQUE\n";
                return 0;
            }

            octets.push_back(static_cast<uint8_t>(nombre));
        }
        catch (...)
        {
            cout << "TRONQUE\n";
            return 0;
        }
    }

    // Vérification de la signature NKRF
    const uint8_t magic[] = {0x4E, 0x4B, 0x52, 0x46};

    if (octets.size() < 4)
    {
        cout << "TRONQUE\n";
        return 0;
    }

    for (size_t i = 0; i < 4; i++)
    {
        if (octets[i] != magic[i])
        {
            cout << "PAS_UNE_PLANCHE\n";
            return 0;
        }
    }

    Lecteur lecteur{octets};
    lecteur.position = 4;

    // Vérification de la version
    uint32_t version;

    if (!lecteur.lireU32(version))
    {
        cout << "TRONQUE\n";
        return 0;
    }

    if (version != 1)
    {
        cout << "VERSION_INCONNUE " << version << "\n";
        return 0;
    }

    // Lecture des données
    Planche planche;

    if (!lirePlanche(lecteur, planche))
    {
        cout << "TRONQUE\n";
        return 0;
    }

    // Affichage uniquement si tout est valide
    afficherPlanche(planche);

    return 0;
}