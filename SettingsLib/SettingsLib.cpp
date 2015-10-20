#include <Settings.h>

void save() {
    freopen (name, "w", stdout);
    for (auto it = st.begin(); it != st.end(); it++) {
        cout << it->first << endl;
        cout << it->second << endl;
    }
}

settings(std::string const & filename) {
    name = filename;
    reload();
}

std::string const & get(std::string const & name, std::string const & def = "") const {
    if (st[name] != "")
        return st[name];
    else
        return def;
}

void set(std::string const &name, std::string const &value) {
    st[name] = value;
    save();
}

void reset() {
    st.clear();
}

void reload() {
    st.clear();
    freopen (name, "r", stdin);
    std::string key, value;
    while (std::getline(cin, key)) {
        std::getline(cin, value);
        st[key] = value;
    }
    fclose(name);
}
