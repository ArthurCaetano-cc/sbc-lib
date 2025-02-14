#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <iomanip>
#include <float.h>

using namespace std;

struct point {
    double x, y;  //double is more precise than float!
};

bool compareX(const point& a, const point& b) { return a.x < b.x; }

bool compareY(const point& a, const point& b) { return a.y < b.y; }

double distance(point p1, point p2) {
    return sqrt(pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2));
}

// O(n^2)
double bruteForceClosestPair(vector<point>& points, int n) {
    double minDistance = DBL_MAX;

    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            double actualDistance = distance(points[i], points[j]);
            if (actualDistance < minDistance) {
                minDistance = actualDistance;
            }
        }
    }

    return minDistance;
}

// O(n log n)
double efficientClosestPair(vector<point>& p, vector<point>& q, int n) {
    if (n <= 3) {
        return bruteForceClosestPair(p, n);
    }

    int m = n / 2;
    vector<point> pl(p.begin(), p.begin() + m);
    vector<point> pr(p.begin() + m, p.end());
    vector<point> ql, qr;

    double midX = p[m].x;

    for (auto& pt : q) {
        if (pt.x <= midX)
            ql.push_back(pt);
        else
            qr.push_back(pt);
    }

    double dl = efficientClosestPair(pl, ql, m);
    double dr = efficientClosestPair(pr, qr, n - m);
    double d = min(dl, dr);

    vector<point> strip;
    for (auto& pt : q) {
        if (abs(pt.x - midX) <= d + 1e-9) {
            strip.push_back(pt);
        }
    }

    double minDistStrip = d;
    for (size_t i = 0; i < strip.size(); i++) {
        for (size_t j = i + 1; j < strip.size() && (strip[j].y - strip[i].y) < minDistStrip; j++) {
            minDistStrip = min(minDistStrip, distance(strip[i], strip[j]));
        }
    }

    return min(minDistStrip, d);
}

// Initializer of the efficientClosestPair function
double closestPair(vector<point> points, int n) {
    vector<point> P = points, Q = points;

    sort(P.begin(), P.end(), compareX);
    sort(Q.begin(), Q.end(), compareY);

    double minDistance = efficientClosestPair(P, Q, n);

    return minDistance;
}

int main() {
    int n;
    cin >> n;
    while (n != 0) {
        vector<point> points(n);
        for (int i = 0; i < n; i++) {
            cin >> points[i].x >> points[i].y;
        }

        double distance = closestPair(points, n);

        if (distance >= 10000) {
            cout << "INFINITY" << endl;
        } else {
            cout << fixed << setprecision(4) << distance << endl;
        }

        cin >> n;
    }

    return 0;
}
