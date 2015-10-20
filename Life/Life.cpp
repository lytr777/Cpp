#include <iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <list>
#include <queue>
#include <stack>
#include <sstream>

using namespace std;
bool** life;
int width, length;

void create () {
    bool** over_life = new bool*[2 * width];
    for (int i = 0; i < 2 * width; i++)
        over_life[i] = new bool[2 * length];
    for (int i = 0; i < width; i++)
        for (int j = 0; j < length; j++){
            over_life[i + width / 2][j + length / 2] = life[i][j];
        }
    //for (int i = 0; i < 2 * width; i++)
        //delete[] life[i];
    delete[] life;
    life = over_life;
    width *= 2;
    length *= 2;
}

void del (int x, int y) {
    bool** del_life = new bool*[width / 2];
    for (int i = 0; i <= width / 2; i++)
        del_life[i] = new bool[length / 2];
    width /= 2;
    length /= 2;
    for (int i = 0; i < width / 2; i++)
        for (int j = 0; j < length / 2; j++){
            del_life[i + width / 2][j + length / 2] = life[x + i][y + j];
        }
    delete[] life;
    life = del_life;
}

int main(){
    char si;
    freopen("Life.txt", "r", stdin);
    cin >> width >> length;
    life = new bool*[2 * width];
    for (int i = 0; i < 2 * width; i++)
        life[i] = new bool[2 * length];
    for (int i = width / 2; i < 3 * width / 2; i++)
        for (int j = length / 2; j < 3 * length / 2; j++){
            cin >> si;
            life[i][j] = ((si == '.')? false : true);
        }

    del (0, 0);


    for (int i = width / 2; i < 3 * width / 2; i++) {
        for (int j = length / 2; j < 3 * length / 2; j++)
                cout << life[i][j] << " ";
        cout << endl;
    }
    return 0;
}

