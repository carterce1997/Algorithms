#include <iostream>
#include "splay.h"

using std::cerr;
using std::endl;

int main() {
    Splay<int> *s = new Splay<int>(10);
    s->show();
    cerr << "\n\n";

    s = s->insert(15);
    s->show();

    cerr << "\n\n";

    s = s->insert(20);
    s->show();

    cerr << "\n\n";

    s = s->insert(3);
    s->show();
   
    cerr << "\n\n";

    s = s->insert(5);
    s->show();

    cerr << "\n\n";

    s = s->insert(8);
    s->show();

    cerr << "\n\n";

    s = s->insert(100);
    s->show();

   cerr << "\n\n";

    s = s->insert(74);
    s->show();

   cerr << "\n\n";

    s = s->insert(-1);
    s->show();


   cerr << "\n\n";

    s = s->insert(123);
    s->show();


    return 0;
}

