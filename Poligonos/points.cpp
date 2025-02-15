#include <iostream>
#include <cmath>
#include <iomanip>

/*
    This program implements basic point functions:
        - Distance between two points;
        - Distance from a point to a line.
*/

using namespace std;

class Point {
private:
    float x;
    float y;

public:
    // Default constructor
    Point() : x(0), y(0) {}

    // Parameterized constructor
    Point(float positionX, float positionY) {
        x = positionX;
        y = positionY;
    }

    // Function to compute the distance between two points
    float distance(const Point &p1) const {
        return sqrt(pow(x - p1.x, 2) + pow(y - p1.y, 2));
    }

    // Function to compute the distance from the point to the line ax + by + c = 0
    float distanceFromLine(float a, float b, float c) const {
        float numerator = abs(a * x + b * y + c);
        float denominator = sqrt(a * a + b * b);
        return numerator / denominator;
    }

    // Function to display the point
    void display() const {
        cout << "(" << x << ", " << y << ")";
    }
};

int main() {
    Point p1(1.5, 2.5);
    Point p2(2, 3);

    // Print the distance between the points:
    cout << fixed << setprecision(2);
    cout << "Distance between ";
    p1.display();
    cout << " and ";
    p2.display();
    cout << ": " << p1.distance(p2) << endl;

    // Define a line equation: 3x + 4y - 5 = 0
    float a = 3, b = 4, c = -5;
    
    // Print the distance from p1 to the line:
    cout << "Distance from ";
    p1.display();
    cout << " to line 3x + 4y - 5 = 0: " << p1.distanceFromLine(a, b, c) << endl;

    return 0;
}
