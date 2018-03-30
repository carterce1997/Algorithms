#include <iostream>
#include "splay.h"

int main() {
    Splay<int> *s = new Splay<int>(4);

    s->insert(5);
    s->insert(2);
    s->insert(3);
    s->show();

    std::cout << s->search(3)->getValue() << std::endl;

    s->remove(3);
    s->show();

    return 0;
}
