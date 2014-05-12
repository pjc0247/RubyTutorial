#include <Ruby/Ruby.h>
#include <stdio.h>

void test_funcall(){
    ID fPuts = rb_intern("puts"); /* id of 'puts' */
    
    printf("test_funcall\n");
    
    /* rb_cObject -> top-level object */
    /* rb_funcall( class, method_id, argc, ... ) */
    rb_funcall(
        rb_cObject, fPuts,
        2, INT2NUM(4), rb_str_new2("hello"));
}

VALUE func_minsoo(VALUE self, VALUE a,VALUE b){
    /* self -> rb_cObject */
    return INT2NUM( NUM2INT(a) + NUM2INT(b) );
}
void test_deffunc(){
    /* rb_define_method( define_under, method_name, c_func_ptr, argc ) */
    rb_define_method(
        rb_cObject, "minsoo",
        (VALUE(*)(...))func_minsoo, 2 );
    
    printf("test_deffunc\n");
    rb_eval_string("puts minsoo(14,31)");
}

VALUE func_genius(long argc, VALUE *args){
    printf("argc - %ld\n", argc);
    for(int i=0;i<argc;i++)
        printf("%d ", NUM2INT(args[i]));
    printf("\n");
    
    return Qnil;
}
void test_deffunc2(){
    rb_define_method(
        rb_cObject, "genius",
        (VALUE(*)(...))func_genius, -1 );
    
    printf("test_deffunc2\n");
    rb_eval_string("genius(1,2,3,4)");
}
