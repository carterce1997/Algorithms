#include <iostream>
#include "splay.h"

using std::cerr;
using std::endl;

int main() {
    Splay<int> *s = new Splay<int>(14);
    s->show();
    cerr << "\n\n";

    s = s->insert(2);
    s->show();
    cerr << "\n\n";

    s = s->insert(1);
    s->show();
    cerr << "\n\n";

/* while(1){
        cout<<endl;
        cout<<endl;
                cout<<"Enter a number :";
        int x;
        cin>>x;

        s = s->insert(x);
        s->show();
        if(x == 1) break;
    }
    */
 
 while(1){
        cout<<endl;
        cout<<endl;
                cout<<"search a number :";
        int x;
        cin>>x;

        s = s->search(x);
        s->show();
        if(x == -1) break;
    }

    cout<< s->getType()<<endl;

    return 0;
}

