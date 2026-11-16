#include <iostream>
#include <cmath>
#include "NkRef/NkRefView.h"

using namespace std;
using namespace nkref;

bool proche(float a, float b) {
    return fabs(a - b) <= 0.001f;
}

// Test 1 : conversion pixel -> monde -> pixel
bool aller_retour() {
    NkRefView camera;
    camera.center = {30.0f, -20.0f};
    camera.zoom = 2.5f;

    NkVec2f viewport{800.0f, 600.0f};
    NkVec2f pixel{150.0f, 250.0f};

    NkVec2f monde = camera.PixelToWorld(pixel, viewport);
    NkVec2f retour = camera.WorldToPixel(monde, viewport);

    return proche(pixel.x, retour.x) &&
           proche(pixel.y, retour.y);
}

// Test 2 : le point sous le curseur reste fixe pendant le zoom
bool point_fixe() {
    NkRefView camera;
    NkVec2f viewport{800.0f, 600.0f};
    NkVec2f pixel{200.0f, 150.0f};

    NkVec2f avant = camera.PixelToWorld(pixel, viewport);
    camera.ZoomAtPixel(2.0f, pixel, viewport);
    NkVec2f apres = camera.PixelToWorld(pixel, viewport);

    return proche(avant.x, apres.x) &&
           proche(avant.y, apres.y);
}

// Test 3 : le zoom respecte ses limites
bool bornes() {
    NkRefView camera;
    NkVec2f viewport{800.0f, 600.0f};
    NkVec2f pixel{400.0f, 300.0f};

    camera.ZoomAtPixel(1000.0f, pixel, viewport);
    bool maximum = camera.zoom <= NkRefView::kZoomMax &&
                   camera.zoom >= NkRefView::kZoomMin;

    camera.ZoomAtPixel(0.00001f, pixel, viewport);
    bool minimum = camera.zoom >= NkRefView::kZoomMin &&
                   camera.zoom <= NkRefView::kZoomMax;

    return maximum && minimum;
}

// Test 4 : la grille ne devient pas plus serrée quand on dézoome
bool grille() {
    NkRefView camera;
    camera.zoom = 4.0f;
    float grande = camera.GridSpacing(20.0f);

    camera.zoom = 2.0f;
    float moyenne = camera.GridSpacing(20.0f);

    camera.zoom = 1.0f;
    float petite = camera.GridSpacing(20.0f);

    return moyenne >= grande && petite >= moyenne;
}

// Test 5 : Reset remet la caméra à son état initial
bool origine() {
    NkRefView camera;
    NkVec2f viewport{800.0f, 600.0f};
    NkVec2f pixel{200.0f, 150.0f};

    camera.ZoomAtPixel(3.0f, pixel, viewport);
    camera.PanByPixels(50.0f, 30.0f);
    camera.Reset();

    return proche(camera.center.x, 0.0f) &&
           proche(camera.center.y, 0.0f) &&
           proche(camera.zoom, 1.0f);
}

int main() {
    cout << "TEST aller_retour : "
         << (aller_retour() ? "OK" : "ECHEC") << "\n";

    cout << "TEST point_fixe : "
         << (point_fixe() ? "OK" : "ECHEC") << "\n";

    cout << "TEST bornes : "
         << (bornes() ? "OK" : "ECHEC") << "\n";

    cout << "TEST grille : "
         << (grille() ? "OK" : "ECHEC") << "\n";

    cout << "TEST origine : "
         << (origine() ? "OK" : "ECHEC") << "\n";

    return 0;
}