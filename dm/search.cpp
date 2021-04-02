#include <cstdint>
#include <iostream>
#include <vector>
#include <deque>
#include <utility>
using namespace std;

using AdjList = vector<vector<size_t>>;

struct Matrix {
    vector<uint8_t> v;
    size_t n;
    bool has_edge(size_t from, size_t to) const { return v[n * from + to] & 1; }
    bool been_visited(size_t k) const { return v[k] & 2; }
    void mark_as_visited(size_t k) { v[k] |= 2; }
    void reset() {
        for (size_t i = 0; i < n; ++i)
            v[i] &= 1;
    }

    pair<AdjList, size_t> to_adj_list() const {
        size_t m = 0;
        AdjList a(n);
        for (size_t i = 0; i < n; ++i) {
            for (size_t j = 0; j < n; ++j) {
                if (has_edge(i, j)) {
                    a[i].push_back(j);
                    ++m;
                }
            }
        }
        return {a, m};
    }
};

void bfs(Matrix &m, size_t start) {
    deque<size_t> d = {start};
    m.mark_as_visited(start);
    cout << start << ' ';
    size_t k = 0;
    while (!d.empty()) {
        size_t n = d.size();
        for (size_t i = 0; i < n; ++i) {
            for (size_t j = 0; j < m.n; ++j) {
                if (m.has_edge(d[i], j) && !m.been_visited(j)) {
                    d.push_back(j);
                    m.mark_as_visited(j);
                    cout << j << ' ';
                }
                ++k;
            }
        }
        d.erase(d.begin(), d.begin() + n);
    }
    cout << " --- " << k << " iterations in total";
}

void dfs(Matrix &m, size_t from) {
    m.mark_as_visited(from);
    cout << from << ' ';
    for (size_t to = 0; to < m.n; ++to) {
        if (m.has_edge(from, to) && !m.been_visited(to)) {
            dfs(m, to);
        }
    }
}


void bfs(const AdjList &a, size_t start) {
    deque<size_t> d = {start};
    vector<bool> visited(a.size(), false);
    visited[start] = true;
    cout << start << ' ';
    size_t k = 0;
    while (!d.empty()) {
        size_t n = d.size();
        for (size_t i = 0; i < n; ++i) {
            for (size_t j: a[d[i]]) {
                if (!visited[j]) {
                    d.push_back(j);
                    visited[j] = true;
                    cout << j << ' ';
                }
                ++k;
            }
        }
        d.erase(d.begin(), d.begin() + n);
    }
    cout << " --- " << k << " iterations in total";
}

void dfs_impl(const AdjList &a, size_t from, vector<bool> &visited) {
    visited[from] = true;
    cout << from << ' ';
    for (size_t to: a[from]) {
        if (!visited[to])
            dfs_impl(a, to, visited);
    }
}

void dfs(const AdjList &a, size_t start) {
    vector<bool> visited(a.size(), false);
    dfs_impl(a, start, visited);
}

int main() {
    Matrix m;
    size_t k;
    cin >> m.n >> k;
    m.v.resize(m.n*m.n);
    for (size_t i = 0; i < m.n; ++i)
        for (size_t j = 0; j < m.n; ++j)
            cin >> m.v[i * m.n + j];
    auto p = m.to_adj_list();

    cout << "Matrix is " << (m.n * m.n) << " bytes (might be up to 8 times less)\n";
    cout << "AdjList is " << (p.second*sizeof(size_t)+p.first.size()*sizeof(vector<size_t>)) << " bytes\n";

    cout << "BFS on matrix:   ";
    bfs(m, k);
    cout << "\nDFS on matrix:   ";
    m.reset();
    dfs(m, k);

    cout << "\nBFS on adj list: ";
    bfs(p.first, k);
    cout << "\nDFS on adj list: ";
    dfs(p.first, k);
}

