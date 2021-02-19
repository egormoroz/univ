#include <iostream>
#include <vector>
using namespace std;

template<typename T>
struct GenericNode {
    int left, right;
    T value;
};

template<typename T>
struct BST {
    using Node = GenericNode<T>;
    vector<Node> nodes;

    bool insert(T x) {
        if (nodes.empty()) {
            nodes.push_back(Node{-1, -1, x});
            return true;
        }
        int idx = 0;
        while (true) {
            Node &n = nodes[idx];
            if (x == n.value)
                return false;
            if (x < n.value) {
                if (n.left > -1) {
                    idx = n.left;
                } else {
                    n.left = nodes.size();
                    nodes.push_back(Node{-1, -1, x}); //(!) invalidates n reference
                    return true;
                }
            }
            if (x > n.value) {
                if (n.right > -1) {
                    idx = n.right;
                } else {
                    n.right = nodes.size();
                    nodes.push_back(Node{-1, -1, x}); //(!) invalidates n reference
                    return true;
                }
            }
        }
        //unreachable
    }

    const Node& node(int idx) const {
        return nodes[idx];
    }

    int find(T x) const {
        if (nodes.empty())
            return -1;
        int idx = 0;
        while (idx != -1) {
            const Node &n = nodes[idx];
            if (x == n.value)
                return idx;
            if (x < n.value)
                idx = n.left;
            if (x > n.value)
                idx = n.right;
        }
        return -1;
    }

    template<typename F>
    void traverse(F && f) {
        if (nodes.empty())
            return;
        traverse_impl(f, 0);
    }

    //TODO: get rid of recursion
    template<typename F>
    void traverse_impl(F && f, int idx) {
        if (nodes[idx].left > -1)
            traverse_impl(f, nodes[idx].left);
        f(nodes[idx].value);
        if (nodes[idx].right > -1)
            traverse_impl(f, nodes[idx].right);
    }
};

int main() {
    BST<int> a;
    const int N = 9;
    int b[N] = { 5, 1, 3, 4, 6, 7, 9, 8, 2 };
    for (int i= 0; i < N /*size(b)*/; ++i)
        a.insert(b[i]);
    a.traverse([](int x) {
        cout << x << ' ';
    });
    cout << endl;
}

