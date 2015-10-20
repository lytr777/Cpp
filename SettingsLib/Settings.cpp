#include <fstream>
#include "Settings.h"

using namespace std;

void settings::save() {
    ofstream cout (name);
    for (auto it = st.begin(); it != st.end(); it++) {
        cout << it->first << endl;
        cout << it->second << endl;
    }
    cout.close();
}

settings::settings(string const &filename) {
    name = filename;
    if (name == "")
        name = "default.st";
    reload();
}

std::string const &settings::get(std::string const &name, std::string const &def = "") const {
    if (st[name] != "")
        return st[name];
    else
        return def;
}

void settings::set(std::string const &name, std::string const &value) {
    st[name] = value;
    save();
}

void settings::reset() {
    st.clear();
}

void settings::reload() {
    st.clear();
    ifstream cin (name);
    std::string key, value;
    while (std::getline(cin, key)) {
        std::getline(cin, value);
        st[key] = value;
    }
    cin.close();
}