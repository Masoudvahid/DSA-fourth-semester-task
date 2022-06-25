// https://contest.yandex.ru/contest/38500/run-report/69170890/
#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <iomanip>
#include <stack>


using std::cin;
using std::cout;
using std::vector;
using std::sort;
using std::swap;
using std::stack;


struct Point {
    double x;
    double y;

    bool operator<(const Point &other) const {
        //declare how 2 variable of type posToMove should be compared with <
        return std::make_tuple(x, y) < std::make_tuple(other.x, other.y);
    }

    bool operator==(const Point &other) const {
        //declare how 2 variable of type posToMove should be compared with ==
        return std::make_tuple(x, y) == std::make_tuple(other.x, other.y);
    }
};


Point p0;

double distSq(Point p1, Point p2) {
    return (p1.x - p2.x) * (p1.x - p2.x) +
           (p1.y - p2.y) * (p1.y - p2.y);
}

double orientation(Point p, Point q, Point r) {
    double val = (q.y - p.y) * (r.x - q.x) -
                 (q.x - p.x) * (r.y - q.y);

    if (val == 0) return 0; // collinear
    return (val > 0) ? 1 : 2; // clock or counterclock wise
}

int compare(const void *vp1, const void *vp2) {
    Point *p1 = (Point *) vp1;
    Point *p2 = (Point *) vp2;

    double o = orientation(p0, *p1, *p2);
    if (o == 0)
        return (distSq(p0, *p2) >= distSq(p0, *p1)) ? -1 : 1;

    return (o == 2) ? -1 : 1;
}

class RabbitFence {
private:
    static double CalculateDistance(Point &x, Point &y) {
        return sqrt(pow(x.x - y.x, 2) +
                    pow(x.y - y.y, 2));
    }

public:
    void swap(Point &p1, Point &p2) {
        Point temp = p1;
        p1 = p2;
        p2 = temp;
    }


    void OuterHoles(vector<Point> points) {
        double ymin = points[0].y, min = 0;
        for (int i = 1; i < points.size(); i++) {
            int y = points[i].y;

            if ((y < ymin) || (ymin == y &&
                               points[i].x < points[min].x))
                ymin = points[i].y, min = i;
        }

        swap(points[0], points[min]);

        p0 = points[0];
        qsort(&points[1], points.size() - 1, sizeof(Point), compare);

        int m = 1; // Initialize size of modified array
        for (int i = 1; i < points.size(); i++) {
            while (i < points.size() - 1 && orientation(p0, points[i],
                                                        points[i + 1]) == 0)
                i++;
            points[m] = points[i];
            m++; // Update size of modified array
        }

        if (m < 3) return;
        outer_holes.push_back(points[0]);
        outer_holes.push_back(points[1]);
        outer_holes.push_back(points[2]);

        for (int i = 3; i < m; i++) {
            while (outer_holes.size() > 1 &&
                   orientation(outer_holes[outer_holes.size() - 2], outer_holes.back(), points[i]) != 2)
                outer_holes.pop_back();
            outer_holes.push_back(points[i]);
        }
    }


    double PrintLength() {
        double sum = 0;
        for (int i = 0; i < outer_holes.size(); i++) {
            sum += CalculateDistance(outer_holes[i], outer_holes[(i + 1) % outer_holes.size()]);
        }
        return sum;
    }

private:
    vector<Point> outer_holes;
};

int main() {
    int number_of_holes;
    cin >> number_of_holes;
    vector<Point> holes(number_of_holes);
    for (int i = 0; i < number_of_holes; i++) {
        cin >> holes[i].x >> holes[i].y;
    }
    holes.erase(std::unique(holes.begin(), holes.end()), holes.end());


    RabbitFence rabbitFence;
    rabbitFence.OuterHoles(holes);
    std::cout << std::fixed << std::setprecision(9);
    cout << rabbitFence.PrintLength();
}
