#include <Ruby/Ruby.h>
#include <stdio.h>

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

VALUE func_block(VALUE obj, VALUE context, int argc, VALUE *argv){
    printf("hello world\n");
    return Qnil;
}
void test_block2(){
    ID fTimes = rb_intern("times");
    
    printf("test_block2\n");
    /* rb_block_call(
     *      obj, method_id,
     *      argc, argv,
     *      c_block_func_ptr, context ); */
    rb_block_call(
        INT2NUM(4), fTimes,
        0, nullptr,
        (VALUE(*)(...))func_block, Qnil );

}
