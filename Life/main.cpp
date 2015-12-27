#include <iostream>
#include <algorithm>
#include <fstream>

using namespace std;
bool **life;
int width = -1, length = -1, st_population = 0, population, born, death;
int mm[4];

void min_max() {
    mm[0] = 2 * width;
    mm[1] = 0;
    mm[2] = 2 * length;
    mm[3] = 0;
    for (int i = 0; i < 2 * width; i++)
        for (int j = 0; j < 2 * length; j++)
            if (life[i][j]) {
                if (mm[0] > i) mm[0] = i;
                if (mm[1] < i) mm[1] = i;
                if (mm[2] > j) mm[2] = j;
                if (mm[3] < j) mm[3] = j;
            }
}

void write_field(int show_width, int show_length) {
    min_max();
    char ch = ' ';
    if (show_width >= mm[1] - mm[0] && show_length >= mm[3] - mm[2]) {
        for (int i = mm[0]; i <= mm[1]; i++) {
            for (int j = mm[2]; j <= mm[3]; j++)
                (life[i][j]) ? cout << "x" : cout << ".";
            cout << endl;
        }
        cout << "The field is fully visible in frame view." << endl;
    }
    else
        while (ch != 'q') {
            for (int i = mm[0]; i < mm[0] + show_width; i++) {
                for (int j = mm[2]; j < mm[2] + show_length; j++)
                    (life[i][j]) ? cout << "x" : cout << ".";
                cout << endl;
            }
            cout << "You in the cell at coordinates " << mm[0] << " " << mm[2] << ", field size : " << 2 * width <<
            "x" << 2 * length << ". Where is go? (w, a, s, d) or q for quit" << endl;
            cin >> ch;
            cout << endl << endl << endl << endl << endl << endl << endl;
            switch (ch) {
                case 'w':
                    if (mm[0] > 0) mm[0]--;
                    continue;
                case 'a':
                    if (mm[2] > 0) mm[2]--;
                    continue;
                case 's':
                    if (mm[0] + show_width < 2 * width - 1) mm[0]++;
                    continue;
                case 'd':
                    if (mm[2] + show_length < 2 * length - 1) mm[2]++;
                    continue;
                case 'q':
                    continue;
                default:
                    cout << "You in the cell at coordinates " << mm[0] << " " << mm[2] << ", field size : " <<
                    2 * width << "x" << 2 * length << ". Where is go? (w, a, s, d) or q for quit" << endl;
                    cin >> ch;
            }
        }
}

void memory_allocation() {
    bool **over_life = new bool *[4 * width];
    for (int i = 0; i < 4 * width; i++)
        over_life[i] = new bool[4 * length];
    int x = width, y = length;
    for (int i = 0; i < 4 * width; i++)
        for (int j = 0; j < 4 * length; j++) {
            if (i - x >= 2 * width || j - y >= 2 * length || i - x < 0 || j - y < 0)
                over_life[i][j] = false;
            else
                over_life[i][j] = life[i - x][j - y];
        }
    width *= 2;
    length *= 2;
    delete[] life;
    life = over_life;
}

void free_memory(int x, int y) {
    bool **del_life = new bool *[width + width % 2];
    for (int i = 0; i <= width; i++)
        del_life[i] = new bool[length + length % 2];
    for (int i = 0; i < (width + width % 2); i++)
        for (int j = 0; j < (length + length % 2); j++) {
            if (x + i >= 2 * width || y + j >= 2 * length || x + i < 0 || y + j < 0)
                del_life[i][j] = false;
            else
                del_life[i][j] = life[x + i][y + j];
        }
    delete[] life;
    width = (width + width % 2) / 2;
    length = (length + length % 2) / 2;
    life = del_life;
}

int cast_number(string s) {
    int num = 0;
    for (int j = 0; j < s.length(); j++) {
        if ('0' < s[j] && s[j] > '9') {
            return -1;
        }
        num = num * 10 + (int) (s[j] - '0');
    }
    return num;
}

void check_new() {
    min_max();
    if (mm[0] == 0 || mm[3] == 0 || mm[1] == 2 * width - 1 || mm[3] == 2 * length - 1) {
        memory_allocation();
    }
}

void check_delete() {
    if (width < 5 || length < 5)
        return;
    min_max();
    if (mm[3] - mm[2] <= length / 2 && mm[1] - mm[0] <= width / 2) {
        int a = mm[0] - ((width - mm[1] + mm[0]) / 2);
        int b = mm[2] - ((length - mm[3] + mm[2]) / 2);
        cout << endl;
        free_memory(a, b);
    }
}

bool check(int i, int j) {
    if (i < 0 || j < 0 || i > 2 * width - 1 || j > 2 * length - 1)
        return false;
    return life[i][j];
}

bool check_round(int i, int j) {
    int count = 0;
    for (int k = -1; k <= 1; k++)
        for (int s = -1; s <= 1; s++)
            count += check(i + k, j + s) ? 1 : 0;
    if (life[i][j])
        return (count == 3 || count == 4);
    else
        return (count == 3);
}

void step() {
    born = 0;
    death = 0;
    bool **time_life = new bool *[2 * width];
    for (int i = 0; i < 2 * width; i++)
        time_life[i] = new bool[2 * length];
    for (int i = 0; i < 2 * width; i++)
        for (int j = 0; j < 2 * length; j++) {
            time_life[i][j] = check_round(i, j);
            if (time_life[i][j] && !life[i][j])
                born++;
            if (!time_life[i][j] && life[i][j])
                death++;
        }
    delete[] life;
    life = time_life;
    check_new();
    check_delete();
    return;
}


void random_size() {
    width = rand() % 100;
    length = rand() % 100;
}

int refilling (int pop) {
    for (int i = width / 2; i < 3 * width / 2; i++)
        for (int j = length / 2; j < 3 * length / 2 && pop > 0; j++) {
            if (!life[i][j]) {
                life[i][j] = true;
                pop--;
            }
        }
    return pop;
}

void random_field() {
    int pop = -1;
    string s;
    cout << "Enter height and width with a space or enter '-1 -1' for random size :" << endl;
    cin >> s;
    width = cast_number(s);
    cin >> s;
    length = cast_number(s);
    if (width < 0 && length < 0) {
        random_size();
    }
    cout << "Field size : " << width << "x" << length << " = " << width * length << endl;
    while (pop < 0 || pop > width * length) {
        cout << "Enter population : " << endl;
        cin >> s;
        pop = cast_number(s);
        if (pop >  width * length)
            cout << "The field doesn't contains it!" << endl;

    }
    life = new bool *[2 * width];
    for (int i = 0; i < 2 * width; i++)
        life[i] = new bool[2 * length];
    for (int i = 0; i < 2 * width; i++)
        for (int j = 0; j < 2 * length; j++)
            life[i][j] = false;
    st_population = pop;
    while (pop > 0) {
        for (int i = width / 2; i < 3 * width / 2; i++)
            for (int j = length / 2; j < 3 * length / 2 && pop > 0; j++) {
                life[i][j] = (rand() % 2 == 1);
                if (life[i][j]) {
                    pop--;
                }
            }
        if (pop > 0)
            pop = refilling (pop);
    }
}

void keyboad_enter() {
    char si;
    string s;
    while (width < 0 || length < 0) {
        cout << "Enter height and width with a space : ";
        cin >> s;
        width = cast_number(s);
        cin >> s;
        length = cast_number(s);
    }
    life = new bool *[2 * width];
    for (int i = 0; i < 2 * width; i++)
        life[i] = new bool[2 * length];
    for (int i = 0; i < 2 * width; i++)
        for (int j = 0; j < 2 * length; j++)
            life[i][j] = false;
    cout << "Enter the field. '.' - empty, 'x' - populated. Enter " << width << "x" << length << " = " <<
    width * length << " symbols without spaces :" << endl;
    for (int i = width / 2; i < 3 * width / 2; i++)
        for (int j = length / 2; j < 3 * length / 2; j++) {
            cin >> si;
            life[i][j] = (si != '.');
            if (life[i][j])
                st_population++;
        }
}

void file_enter(string def = "Life.txt") {
    char si;
    ifstream cin(def);
    cin >> width >> length;
    life = new bool *[2 * width];
    for (int i = 0; i < 2 * width; i++)
        life[i] = new bool[2 * length];
    for (int i = width / 2; i < 3 * width / 2; i++)
        for (int j = length / 2; j < 3 * length / 2; j++) {
            cin >> si;
            life[i][j] = (si != '.');
            if (life[i][j])
                st_population++;
        }
}

int enter() {
    int k = 0, steps = -1;
    string s;
    while (k < 1 || k > 3) {
        cout << "Select input method : 1 - random field, 2 - input from file, 3 - keyboard input" << endl;
        cin >> s;
        k = cast_number(s);
    }
    if (k == 1)
        random_field();
    else if (k == 2)
        file_enter();
    else
        keyboad_enter();
    while (steps < 0) {
        cout << "Enter the amount of steps : " << endl;
        cin >> s;
        steps = cast_number(s);
    }
    return steps;
}


int main() {
    int k = 0, steps, show_width = -1, show_length = -1;
    string s;
    steps = enter();
    while (show_width < 0 || show_length < 0) {
        cout << "Enter height and width of the displayed field with a space ";
        cin >> s;
        show_width = cast_number(s);
        cin >> s;
        show_length = cast_number(s);
    }
    cout << "The initial population : " << st_population << endl;
    population = st_population;
    born = population;
    death = 0;
    {
        int born_10 = 0;
        int death_10 = 0;
        int pop_step = -1;
        bool check_stop_pop = true;
        while ((born != 0 || death != 0) && k != steps) {
            k++;
            step();
            born_10 += born;
            death_10 += death;
            if (born == death) {
                if (check_stop_pop) {
                    pop_step = k;
                    check_stop_pop = false;
                }
            }
            else
                check_stop_pop = true;
            if (k % 10 == 0) {
                cout << "The number of occupied cells : " << born_10 << "." << endl;
                cout << "The average ratio born/death : " << (double) born_10 / death_10 << "." << endl;
                population += born_10 - death_10;
                born_10 = 0;
                death_10 = 0;
                cout << endl;
            }
        }
        population += born_10 - death_10;
        cout << "Population increase : " << population - st_population << endl;
        cout << "The population has not changed";
        (pop_step == -1) ? cout << "." << endl : cout << " in " << pop_step << " steps." << endl;
        cout << "The program ended on " << k << " step" << endl;
        cout << "The final location on the field :" << endl;
        write_field(show_width, show_length);
        if (mm[1] == 0 && mm[3] == 0 && mm[0] == 2 * width && mm[2] == 2 * length)
            cout << "No one survived";
    }
    return 0;
}
