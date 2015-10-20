#include <iostream>
#include <bits/stl_map.h>

using namespace std;

template < typename T > class Heap {
private:
    int size = 0;
    T elements[10000];

    void siftDown(int i) {
        int left = 2 * i + 1;
        int right = 2 * i + 2;
        if (left >= size)
            return;
        int mx = left;
        if ((right < size) && (elements[right] < elements[left]))
            mx = right;
        if (elements[i] <= elements[mx])
            return;
        swap(elements[i], elements[mx]);
        siftDown(mx);
    }

    void siftUp(int i) {
        if (elements[i] < elements[(i - 1) / 2]) {
            swap(elements[i], elements[(i - 1) / 2]);
            siftUp ((i - 1) / 2);
        }
    }

public:
    void insert(T key) {
        elements[size++] = key;
        siftUp(size - 1);
    }

    T extract() {
        if (size == 0)
            return 0;
        T min = elements[0];
        elements[0] = elements[--size];
        siftDown(0);
        return min;
    }

    void decrease_key(int pos, T key) {
        if (key > elements[pos]) {
            elements[pos] = key;
            siftDown(pos);
        }
        else {
            elements[pos] = key;
            siftUp(pos);
        }
    }
};



int main() {
    int n, key;
    string s, type;
    cout << "Enter start size and type: " << endl;
    cin >> n >> type;
        Heap <int> A;
    int element;
    cout << "Enter elements :" << endl;
    for (int i = 0; i < n; i++) {
        cin >> element;
        A.insert(element);
    }
    cout << "Enter operation :" << endl;
    while (cin >> s) {
        if (s == "insert") {
            cin >> element;
            A.insert(element);
        }
        if (s == "extract")
            cout << A.extract() << endl;
        if (s == "deacrease_key") {
            cin >> key >> element;
            A.decrease_key(key, element);
        }
        cout << "Enter operation :" << endl;
    }
    return 0;
}