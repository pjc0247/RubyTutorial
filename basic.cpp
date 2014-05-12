#include <Ruby/Ruby.h>
#include <stdio.h>

void test_eval(){
    VALUE v = rb_eval_string("1+(2*3)");
    
    printf("test_eval %d\n", NUM2INT(v));
}
void test_eval2(){
    printf("test_eval2 ");
    
    rb_eval_string("puts 1234");
}

void test_value(){
    /* type / c->r / r->c
     *
     * int : INT2NUM, NUM2INT
     * long : LONG2NUM, NUM2LONG
     * float : DBL2NUM, NUM2DBL
     * string : rb_str_new2, rb_string_value_cstr(&)
     */
    
    VALUE ruby_value = INT2NUM( 1234 );
    int c_value = NUM2INT( ruby_value );
    
    printf("test_value %d\n", c_value);
}
void test_value2(){
    VALUE nil = rb_eval_string("nil");
 
    /* keywords
     * 
     * nil -> Qnil
     * true -> Qtrue
     * false -> Qfalse
     */
    
    printf("test_value2 / %d %d\n",
        nil == NULL, nil == Qnil);
}
