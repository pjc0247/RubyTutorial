#include <ruby/ruby.h>
#include <stdio.h>




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
