//
// Created by vozak on 2024. 11. 08..
//

#include <bits/stdc++.h>
#include "common_child.h"

using namespace std;

typedef int EdgeIndex;
typedef int NodeIndex;

bool hasOppositeSign(int a, int b) {
    return (a > 0 && b < 0) || (a < 0 && b > 0);
}

struct Point {
    int x;
    int y;

    Point(int x, int y) : x(x), y(y) {}

    Point operator-(const Point &other) const {
        return Point(this->x - other.x, this->y - other.y);
    }
    int operator*(const Point &other) const {
        return this->x * other.y + this->y * other.x;
    }

    bool operator==(const Point & other) const {
        return x == other.x && y == other.y;
    }
};

struct Segment {
    Point start;
    Point end;

    Segment(Point start, Point end) : start(start), end(end) {}

    [[nodiscard]] int h(const Point &p) const {
        return (end-start)*(p-start);
    }

    [[nodiscard]] bool intersects(const Segment &other) const {
        return start == other.start || end == other.end || ((h(other.start) * h(other.end) <= 0) && (other.h(start) * other.h(end) <= 0));
    }
};

struct Edge {
    static EdgeIndex ID;
    EdgeIndex id;
    NodeIndex from;
    NodeIndex to;
    vector<Edge*> collisions;
    Edge(const NodeIndex from, const NodeIndex to): from(from), to(to), id(ID++){}

    bool operator==(const Edge &other) const {
        return id == other.id;
    }
    bool operator==(const EdgeIndex &other) const {
        return id == other;
    }
    bool operator<(const Edge &other) const {
        return collisions.size() < other.collisions.size() || collisions.size() == other.collisions.size() && id < other.id;
    }
    bool operator>(const Edge &other) const {
        return collisions.size() > other.collisions.size();
    }
    bool operator!=(const Edge &other) const {
        return id != other.id;
    }
    void deleteCollision(const Edge* other) {
        if (collisions.size() == 0) {
            return;
        }
        auto it = find(collisions.begin(), collisions.end(), other);
        if (it != collisions.end()) {
            collisions.erase(it);
        }
    }
    ~Edge() {
        collisions.clear();
    }
};
EdgeIndex Edge::ID = 0;

class Graph {
    vector<Edge> edges;
    set<Edge*> orderedEdges;

public:
    [[nodiscard]] vector<Edge*> &getCollisionsOf(const EdgeIndex e) {
        return edges[e].collisions;
    }
    void addCollision(const EdgeIndex e, const EdgeIndex collision) {
        getCollisionsOf(e).emplace_back(getEdge(collision));
    }
    void addEdge(const NodeIndex from, const NodeIndex to) {
        edges.emplace_back(from, to);
    }
    void deleteEdge(const Edge* e) {
        for (auto c : e->collisions) {
            c->deleteCollision(e);
            orderedEdges.erase(orderedEdges.find(c));
            orderedEdges.insert(c);
        }
        orderedEdges.erase(find(orderedEdges.begin(), orderedEdges.end(), e));
    }
    [[nodiscard]] int getNumberOfCollisionsOf(const EdgeIndex e) const {
        return edges[e].collisions.size();
    }
    [[nodiscard]] int getNumberOfEdges() const {
        return edges.size();
    }
    Edge* getEdge(const EdgeIndex e) {
        return &edges[e];
    }
    vector<Edge>::iterator getEdgeIterator(const EdgeIndex e) {
        return edges.begin() + e;
    }
    bool isIntersecting(EdgeIndex e, EdgeIndex f) {
        int i = getEdge(e)->from;
        int j = getEdge(e)->to;
        int fi = getEdge(f)->from;
        int fj = getEdge(f)->to;
        auto edge = Segment(Point(i,0), Point(0,j));
        auto fEdge = Segment(Point(fi,0), Point(0, fj));

        return edge.intersects(fEdge);
    }

    int maxNumberOfPairs() {
        for (auto edge : edges) {
            orderedEdges.insert(&edge);
        }
        int count = 0;
        while (!orderedEdges.empty()) {
            auto best = orderedEdges.begin();
            const int numberOfCollisions = (*best)->collisions.size();
            orderedEdges.erase(best);
            for (int i = 0; i < numberOfCollisions; i++) {
                deleteEdge((*best)->collisions.front());
            }
            count++;
        }

        return count;

    }
};


/*
 * Complete the 'commonChild' function below.
 *
 * The function is expected to return an INTEGER.
 * The function accepts following parameters:
 *  1. STRING s1
 *  2. STRING s2
 */

int commonChild(string s1, string s2) {
    string* str1 = &s1;
    string* str2 = &s2;
    if (s1.size() < s2.size()) {
        str1 = &s2;
        str2 = &s1;
    }

    map<char, vector<NodeIndex>> indices2;
    for (int i = 0; i < str2->size(); i++) {
        indices2[(*str2)[i]].push_back(i);
    }

    Graph graph;

    for (int i = 0; i < str1->size(); i++) {
        auto it = indices2.find((*str1)[i]);
        if (it != indices2.end()) {
            for (auto j : it->second) {
                graph.addEdge(i,j);
            }
        }
    }

    for (EdgeIndex e = 0; e < graph.getNumberOfEdges(); e++) {
        EdgeIndex next = e+1;
        while (next < graph.getNumberOfEdges()) {
            if (graph.isIntersecting(e, next)) {
                graph.getCollisionsOf(e).push_back(graph.getEdge(next));
                graph.getCollisionsOf(next).push_back(graph.getEdge(e));
            }
            next++;
        }
    }

    return graph.maxNumberOfPairs();

    /*
    for (auto c : indices2) {
        c.second.first = 0;
    }
    */

    //return commonChild(*str1, *str2, indices2, 0, 0, 0);

}


void test_common_child()
{
    //ifstream input("C:\\Projects\\hackerrank\\cpp\\hackerrank\\resources\\common_child_testcase_1_input.txt");
    ifstream input("C:\\Projects\\hackerrank\\cpp\\hackerrank\\resources\\common_child_testcase_2_input.txt");
    //ifstream input("C:\\Projects\\hackerrank\\cpp\\hackerrank\\resources\\common_child_test_custom_input.txt");

    string s1;
    getline(input, s1);

    string s2;
    getline(input, s2);

    int result = commonChild(s1, s2);

    cout << result << "\n";
}
