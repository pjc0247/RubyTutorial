#include <ruby/ruby.h>
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

void test_global(){
    VALUE gWhite =
        rb_gv_set( "$white", INT2NUM(1234) );
    
    printf("test_global\n");
    rb_eval_string("puts $white");
}

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

VALUE graphic_draw(VALUE self, VALUE x,VALUE y){
    /* self -> class(Graphic) instance */
    
    printf("draw at (%d, %d)\n", NUM2INT(x), NUM2INT(y));
    return Qnil;
}
void test_defclass(){
    /* rb_define_class( class_name, define_under ) */
    VALUE cGraphic =
        rb_define_class( "Graphic", rb_cObject );
    
    rb_define_method(
        cGraphic, "draw",
        (VALUE(*)(...))graphic_draw, 2 );
    
    rb_eval_string(
        "a = Graphic.new\r\n"
        "a.draw(12,34)" );
}

VALUE input_pressed(VALUE self){
    /* self -> class(Input) instance */
    
    printf("minsoo genius\n");
    return Qnil;
}
void test_defmethod(){
    VALUE cInput =
        rb_define_class( "Input", rb_cObject );
    
    /* define static(singleton) method */
    rb_define_singleton_method(
        cInput, "pressed",
        (VALUE(*)(...))input_pressed, 0 );

    rb_eval_string( "Input.pressed" );
}

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


VALUE func_call_block(VALUE self, VALUE a,VALUE b){
    printf("%d / %d\n", NUM2INT(a), NUM2INT(b));
    
    if( rb_block_given_p() ){
        rb_yield(
            INT2NUM( NUM2INT(a) + NUM2INT(b) ) );
    }
    return Qnil;
}
void test_block(){
    rb_define_method(
        rb_cObject, "call_block",
        (VALUE(*)(...))func_call_block, 2 );
    
    printf("test_block\n");
    rb_eval_string(
        "call_block(1,2) do |v|\r\n"
        "  puts \"1 + 2 = #{v}\"\r\n"
        "end" );
}
