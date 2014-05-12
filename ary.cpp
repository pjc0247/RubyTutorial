#include <Ruby/Ruby.h>
#include <stdio.h>

void test_array(){
    VALUE ary = rb_ary_new();
    
    rb_ary_push( ary, INT2NUM(1) );
    rb_ary_push( ary, INT2NUM(2) );
    rb_ary_push( ary, INT2NUM(3) );

    //=> test_array 3 2 1
    printf("test_array %d %d %d\n",
        NUM2INT(rb_ary_pop(ary)),
        NUM2INT(rb_ary_pop(ary)),
        NUM2INT(rb_ary_pop(ary)) );
}
void test_array2(){
    VALUE ary = rb_ary_new2( 3 );
    
    rb_ary_store( ary, 1, INT2NUM(3) );
    rb_ary_store( ary, 2, INT2NUM(1) );
    rb_ary_store( ary, 3, INT2NUM(2) );
    
    VALUE v1, v2, v3;
    
    v1 = rb_ary_entry( ary, 1 );
    v2 = rb_ary_entry( ary, 2 );
    v3 = rb_ary_entry( ary, 3 );
    
    //=> test_array2 3 1 2
    printf("test_array2 %d %d %d\n",
        NUM2INT(v1), NUM2INT(v2), NUM2INT(v3));
}

void test_array_clear(){
    VALUE ary = rb_ary_new();
    ID fSize = rb_intern("size");
    
    rb_ary_push( ary, INT2NUM(1) );
    rb_ary_push( ary, INT2NUM(2) );
    rb_ary_push( ary, INT2NUM(3) );
    
    rb_ary_clear( ary );
    
    VALUE size =
        rb_funcall( ary, fSize, 0 );
    
    //=> test_array_clear 0
    printf("test_array_clear %d\n",
        NUM2INT(size));
}

VALUE array_iteration_block(VALUE obj, VALUE context, int argc, VALUE *argv){
    printf("%d\n", NUM2INT(argv[0]));
    return Qnil;
}
void test_array_iterate(){
    VALUE ary = rb_ary_new();
    ID fEach = rb_intern("each");
    
    rb_ary_push( ary, INT2NUM(1) );
    rb_ary_push( ary, INT2NUM(2) );
    rb_ary_push( ary, INT2NUM(3) );
    
    printf("test_array_iterate\n");
    rb_block_call(
        ary, fEach,
        0, nullptr,
        (VALUE(*)(...))array_iteration_block, Qnil );
}
