#include <iostream>
#include "splay.h"

using std::cerr;
using std::endl;

int main() {
    Splay<int> *s = new Splay<int>(14);
    s->show();
  
    while(1) {
        cout << endl;
        cout << endl;
        cout << "Insert a number :";
        int x;
        cin >> x;

        if (x == -1) break;
        s = s->insert(x);
        s->show();
        
    }
    
 
    while(1) {
        cout << endl;
        cout << endl;
        cout << "search a number :";
        int x;
        cin >> x;

        if (x == -1) break;
        s = s->search(x);
        s->show();
    }

    while(1) {
        cout << endl;
        cout << endl;
        cout << "delete a number :";
        int x;
        cin >> x;

        if (x == -1) break;
        s = s->remove(x);
        s->show();
    }

    return 0;
}

