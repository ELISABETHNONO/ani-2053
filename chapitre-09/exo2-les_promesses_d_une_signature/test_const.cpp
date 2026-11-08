#include "NkRef/NkRefView.h"

int main()
{
    // Création d'une vue constante
    const nkref::NkRefView vue{};

    // Déclaration des coordonnées
    const nkref::NkVec2f pixel{100.0f, 150.0f};
    const nkref::NkVec2f viewport{800.0f, 600.0f};

    // Appels de méthodes autorisées sur un objet constant
    vue.PixelToWorld(pixel, viewport);
    vue.GridSpacing(20.0f);

    
    //vue.PanByPixels(1.0f, 0.0f);

    return 0;
}