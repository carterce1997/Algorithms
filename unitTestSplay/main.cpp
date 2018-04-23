#include <iostream>
#include "splay.h"

using std::cerr;
using std::endl;

int main() {
    Splay<int> *s = new Splay<int>(10);
    s->show();
    cerr << "--\n";

    s->insert(15);
    s->show();
    cerr << "--\n";

    s->insert(14);
    s->show();
    cerr << "--\n";

    s->insert(13);
    s->show();
    cerr << "--\n";

    s->insert(16);
    s->show();
    cerr << "--\n";

    //s->insert(4);
    //s->show();
    //cerr << "--\n";
/*
    s->insert(6);
    s->show();
    cerr << "--\n";

    s->insert(2);
    s->show();
    cerr << "--\n";

    s->insert(7);
    s->show();
    cerr << "--\n";

    s->insert(9);
    s->show();
    cerr << "--\n";

    s->insert(5);
    s->show();
    cerr << "--\n";
*/
    //s->show();
    //cerr << "--\n";
    //s->splay(s->search(6));
    //s->show();
    return 0;
}

