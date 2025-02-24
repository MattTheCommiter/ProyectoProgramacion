#include "set.h"

int main(){
    Set *s;
    s = set_create();
    set_add(s, 1);
    set_add(s, 2);
    set_add(s, 3);
    set_add(s, 4);

    set_print(s);
    set_del(s, 2);
    set_print(s);
}