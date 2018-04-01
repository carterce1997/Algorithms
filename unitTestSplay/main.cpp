#include <iostream>
#include "splay.h"

using std::cerr;
using std::endl;

int main() {
    Splay<int> *s = new Splay<int>(6);

    s->insert(2);
    s->insert(1);
    s->insert(4);
    s->insert(3);
    s->insert(5);
    s->insert(7);
    s->show();

    s->splay(s->search(5));
    s->show();
    s->splay(s->search(2));
    s->show();
    s->splay(s->search(7));
    s->show();

    return 0;
}
