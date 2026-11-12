#include <iostream>
#include <iomanip>
#include <cmath>
#include <string>
using namespace std;

int main() {
    double W, H, cx = 0, cy = 0, zoom = 1;
    cin >> W >> H;

    string commande;
    cout << fixed << setprecision(2);

    while (cin >> commande) {
        double x, y, f;

        if (commande == "VERS_MONDE") {
            cin >> x >> y;
            x = cx + (x - W / 2) / zoom;
            y = cy + (y - H / 2) / zoom;

            if (abs(x) < 0.005) x = 0;
            if (abs(y) < 0.005) y = 0;

            cout << "MONDE " << x << " " << y << "\n";
        }

        else if (commande == "VERS_PIXEL") {
            cin >> x >> y;
            x = (x - cx) * zoom + W / 2;
            y = (y - cy) * zoom + H / 2;

            if (abs(x) < 0.005) x = 0;
            if (abs(y) < 0.005) y = 0;

            cout << "PIXEL " << x << " " << y << "\n";
        }

        else if (commande == "DEPLACE") {
            cin >> x >> y;
            cx -= x / zoom;
            cy -= y / zoom;
        }

        else if (commande == "ZOOM") {
            cin >> f >> x >> y;

            double ax = cx + (x - W / 2) / zoom;
            double ay = cy + (y - H / 2) / zoom;

            zoom *= f;
            if (zoom < 0.02) zoom = 0.02;
            if (zoom > 64) zoom = 64;

            cx = ax - (x - W / 2) / zoom;
            cy = ay - (y - H / 2) / zoom;
        }

        else if (commande == "GRILLE") {
            cin >> f;
            double s = 1;

            while (s * zoom < f)
                s *= 2;

            while (s * 0.5 * zoom >= f)
                s *= 0.5;

            cout << setprecision(6) << "GRILLE " << s << "\n";
            cout << setprecision(2);
        }

        else if (commande == "ORIGINE") {
            cx = 0;
            cy = 0;
            zoom = 1;
        }
    }

    cout << "CENTRE " << cx << " " << cy << "\n";
    cout << "ZOOM " << zoom << "\n";

    return 0;
}