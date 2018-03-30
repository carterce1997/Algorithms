#include <iostream>
#include "splay.h"

using std::cerr;
using std::endl;

int main() {
    Splay<int> *s = new Splay<int>(5);

    s->insert(3);
    s->insert(4);
    s->insert(2);
    s->insert(6);
    s->show();

    cerr << "Right rotate (zig) about 3" << endl;

    s->zig(s->search(3));
    s->show();

    cerr << "Left rotate (zag) about 5" << endl;

    s->zag(s->search(5));
    s->show();

    return 0;
}
