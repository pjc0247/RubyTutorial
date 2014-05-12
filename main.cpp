#include <Ruby/Ruby.h>
#include <stdio.h>

int main(int argc, char **argv){
    ruby_sysinit( &argc, &argv );
    ruby_init();

    /*
        testcode here
    */
    
    ruby_cleanup( 0 );
    return 0;
}
