#include <iostream>
#include "splay.h"

using std::cerr;
using std::endl;

int main() {
    Splay<int> *s = new Splay<int>(1);

    s->insert(6);
    s->insert(2);
    s->insert(8);
    s->insert(5);
    s->insert(7);
    s->show();

    s->splay(s->search(5));
    s->show();
    return 0;
}

