#include <iostream>

static const char quit = 'q';
using namespace std;

class Token {
public:
    Token(char k): kind(k) {}
    Token(char k, string a): kind(k), atom(a) {}
    bool isAtom() { return this->kind == 'a'; }
    bool isQuit() { return this->kind == quit; }
private:
    char kind;
    string atom;
};

class Token_stream {
public:
    Token_stream();
    Token get();
private:
    bool full;
    Token buffer;
};

Token Token_stream::get() {
    if(full) {
        full = false;
        return buffer;
    }

    char ch;
    cin >> ch;
    switch (ch) {
        case '(': case ')':
            return {ch};
        case ';':
            return {quit};
        default: {
            string s;
            s += ch;
            while(cin >> ch && (isalpha(ch) || isdigit(ch) || ch == '_')) s += ch;
            return {'a', s};
        }
    }
}

Token_stream::Token_stream(): full(false), buffer('a') {
}

Token_stream ts;

int main() {
    cout << "Please enter an atom: ";
    while(cin) {
        Token t = ts.get();

        if(t.isQuit()) break;

        cout << "is atom: " << boolalpha << t.isAtom() << endl;
        cout << "Please enter an atom: ";
    }
}
