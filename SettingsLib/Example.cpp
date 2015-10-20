#include <algorithm>
#include <iostream>
#include <memory>
#include <string>

class lazy_string;

std::ostream & operator <<(std::ostream & out, lazy_string const & str);
std::istream & operator >>(std::istream & in, lazy_string & str);

class lazy_string {
private:
	class proxy {
	public:
		operator char() {
			return (*str.data)[pos];
		}

		proxy & operator=(char c) {
			if (!str.data.unique()) {
				std::cout << "COPY!" << std::endl;
				str.data = std::make_shared<std::string>(*str.data);
			}
			(*str.data)[pos] = c;
		}
	private:
		proxy(lazy_string & s, size_t p) : str(s), pos(p) {}
		proxy(proxy && operator[]) = default;

		lazy_string & str;
		size_t pos;
		friend class lazy_string;
	};
public:
	lazy_string(std::string const & s) : data(std::make_shared<std::string>(s)){

	}

	const char operator [](size_t i) const {
		return (*data)[i];
	}

	proxy && operator [](size_t i) {
		return std::move(proxy(*this, i));
	}
private:
	std::shared_ptr<std::string> data;
	friend std::ostream & operator <<(std::ostream & out, lazy_string const & str);
	friend std::istream & operator >>(std::istream & in, lazy_string & str);

};

std::ostream & operator <<(std::ostream & out, lazy_string const & str) {
	return out << (*str.data);
}

std::istream & operator >>(std::istream & in, lazy_string & str) {
	std::string s;
	in >> s;
	str.data = std::make_shared<std::string>(s);
	return in;
}

int main()
{
	lazy_string s("hello");
	std::cout << s << std::endl;
	auto w = s;
	std::cout << s << " " << w << std::endl;
	w[0] = 'a';
	std::cout << s << " " << w << std::endl;
	w[1] = 'b';
	std::cout << s << " " << w << std::endl;
	return 0;
}
