#include <iostream>
#include "splay.h"

using std::cerr;
using std::endl;

int main() {
    Splay<int> *s = new Splay<int>(6);

    s->insert(7);
    s->insert(1);
    s->insert(2);
    s->insert(5);
    s->show();

    s->zig(s->search(1));
    s->show();
    s->zigzag(s->search(2));
    s->show(); 
    return 0;
}

