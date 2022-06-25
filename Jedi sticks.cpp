// https://contest.yandex.ru/contest/38500/run-report/69178880/
#include <iostream>
#include <vector>
#include <string>
#include <set>
#include <algorithm>
#include <cmath>

namespace jedi_namespace {
    using std::cin;
    using std::cout;
    using std::vector;
    using std::set;
    using std::max;
    using std::min;
    using std::sort;
    using std::to_string;
    using std::make_pair;
    using std::swap;
    using std::pair;
    using std::abs;

    const double EPS = 1E-9;
    struct Point {
        int x;
        int y;
    };
}
using namespace jedi_namespace;

struct Stick {
    Point init;
    Point term;
    size_t id;

    [[nodiscard]] double get_y(double x) const {
        if (abs(init.x - term.x) < EPS)
            return init.y;
        return init.y + (term.y - init.y) * (x - init.x) / (term.x - init.x);
    }
};

bool operator<(const Stick &first, const Stick &second) {
    double x = max(min(first.init.x, first.term.x), min(second.init.x, second.term.x));
    return first.get_y(x) < second.get_y(x) - EPS;
}


class JediSticks {
private:
    static int orientation(Point p, Point q, Point r) {
        int val = (q.y - p.y) * (r.x - q.x) -
                  (q.x - p.x) * (r.y - q.y);

        if (val == 0) return 0;

        return (val > 0) ? 1 : 2;
    }

    static bool onSegment(Point p, Point q, Point r) {
        if (q.x <= max(p.x, r.x) && q.x >= min(p.x, r.x) &&
            q.y <= max(p.y, r.y) && q.y >= min(p.y, r.y))
            return true;

        return false;
    }

    static bool intersect(const Stick s1, const Stick s2) {
        Point p1 = s1.init, q1 = s1.term, p2 = s2.init, q2 = s2.term;

        int o1 = orientation(p1, q1, p2);
        int o2 = orientation(p1, q1, q2);
        int o3 = orientation(p2, q2, p1);
        int o4 = orientation(p2, q2, q1);

        if (o1 != o2 && o3 != o4)
            return true;

        // Special Cases
        // p1, q1 and p2 are collinear and p2 lies on segment p1q1
        if (o1 == 0 && onSegment(p1, p2, q1)) return true;

        // p1, q1 and q2 are collinear and q2 lies on segment p1q1
        if (o2 == 0 && onSegment(p1, q2, q1)) return true;

        // p2, q2 and p1 are collinear and p1 lies on segment p2q2
        if (o3 == 0 && onSegment(p2, p1, q2)) return true;

        // p2, q2 and q1 are collinear and q1 lies on segment p2q2
        if (o4 == 0 && onSegment(p2, q1, q2)) return true;

        return false; // Doesn't fall in any of the above cases
    }

    struct status {
        double x{};
        int tp{}, id{};

        status() = default;

        status(double x, int tp, int id) : x(x), tp(tp), id(id) {}

        bool operator<(const status &other) const { // Used for sort
//        return std::make_tuple(x, other.x) < std::make_tuple(other.x, other.y);
            if (abs(x - other.x) > EPS)
                return x < other.x;
            return tp > other.tp;
        }
    };

    static set<Stick>::iterator previous(const set<Stick> &stick, set<Stick>::iterator it) {
        return it == stick.begin() ? stick.end() : --it;
    }

    static set<Stick>::iterator next(set<Stick>::iterator it) {
        return ++it;
    }

public:
    pair<int, int> solve(vector<Stick> &sticks) {
        vector<status> check_status;
        for (int i = 0; i < sticks.size(); ++i) {
            check_status.emplace_back(min(sticks[i].init.x, sticks[i].term.x), +1, i);
            check_status.emplace_back(max(sticks[i].init.x, sticks[i].term.x), -1, i);
        }
        sort(check_status.begin(), check_status.end());
        set<Stick> checked_sticks;
        checked_sticks.clear();
        location.resize(sticks.size());
        for (auto &item: check_status) {
            int id = item.id;
            if (item.tp == +1) {
                auto nxt = checked_sticks.lower_bound(sticks[id]), prv = previous(checked_sticks, nxt);
                if (nxt != checked_sticks.end() && intersect(*nxt, sticks[id]))
                    return make_pair(nxt->id, id);
                if (prv != checked_sticks.end() && intersect(*prv, sticks[id]))
                    return make_pair(prv->id, id);
                location[id] = checked_sticks.insert(nxt, sticks[id]);
            } else {
                auto nxt = next(location[id]), prv = previous(checked_sticks, location[id]);
                if (nxt != checked_sticks.end() && prv != checked_sticks.end() && intersect(*nxt, *prv))
                    return make_pair(prv->id, nxt->id);
                checked_sticks.erase(location[id]);
            }
        }

        return make_pair(-1, -1);
    }

private:;
    vector<set<Stick>::iterator> location;
};

int main() {
    size_t number_of_sticks;
    cin >> number_of_sticks;

    vector<Stick> sticks(number_of_sticks);
    for (size_t i = 0; i < number_of_sticks; i++) {
        cin >> sticks[i].init.x >> sticks[i].init.y;
        cin >> sticks[i].term.x >> sticks[i].term.y;
        sticks[i].id = i;
    }
    JediSticks jediSticks;
    auto output = jediSticks.solve(sticks);

    cout << (output == pair<int, int>{-1, -1} ? "NO" : "YES\n" + std::to_string(output.first + 1) + " " +
                                                       std::to_string(output.second + 1));

    return 0;
}
