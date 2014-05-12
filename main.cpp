#include <ruby/ruby.h>
#include <stdio.h>

int main(int argc, char **argv){
    ruby_sysinit( &argc, &argv );
    ruby_init();

    test_eval();
    test_eval2();
    test_value();
    test_value2();
    test_funcall();
    test_deffunc();
    test_deffunc2();
    test_defclass();
    test_defmethod();
    
    ruby_cleanup( 0 );
    return 0;
}
