#include <Ruby/Ruby.h>
#include <stdio.h>

VALUE func_thread(void *arg){
    int cnt = 5;
    
    while( cnt --> 0 ){
        printf("hello world\n");
        rb_thread_sleep( 1 );
    }
    
    return INT2NUM(1234);
}
void test_thread(){
    ID fValue = rb_intern("value");
    
    VALUE thread =
        rb_thread_create( (VALUE(*)(...))func_thread, nullptr );
    
    printf("test_thread\n");
    
    /* join & return thread's value */
    VALUE ret = rb_funcall( thread, fValue, 0 );
    
    printf("thread exited : %d\n",
        NUM2INT(ret));
}

VALUE func_thread_tls(void *arg){
    VALUE this_thread;
    ID  iFoo = rb_intern("foo"),
        iBar = rb_intern("bar");
    
    this_thread = rb_thread_current();
    
    /* write value to tls */
    rb_thread_local_aset(
        this_thread, iFoo, rb_str_new2("hello") );
    rb_thread_local_aset(
        this_thread, iBar, rb_str_new2("world") );
    
    /* read value from tls */
    VALUE v1, v2;
    v1 = rb_thread_local_aref(
        this_thread, iFoo);
    v2 = rb_thread_local_aref(
        this_thread, iBar);
    
    printf("thread - %s %s\n",
        rb_string_value_cstr(&v1), rb_string_value_cstr(&v2));
    
    return Qnil;
}
void test_thread_tls(){
    /* tls : thread local storage */
    ID fJoin = rb_intern("join");
    ID  iFoo = rb_intern("foo"),
        iBar = rb_intern("bar");
    VALUE this_thread = rb_thread_current();
    
    printf("test_thread_tls\n");
    
    /* write value to tls */
    rb_thread_local_aset(
        this_thread, iFoo, rb_str_new2("minsoo") );
    rb_thread_local_aset(
        this_thread, iBar, rb_str_new2("genius") );
    
    /* read value from tls */
    VALUE v1, v2;
    v1 = rb_thread_local_aref(
        this_thread, iFoo);
    v2 = rb_thread_local_aref(
        this_thread, iBar);
    
    printf("thread - %s %s\n",
           rb_string_value_cstr(&v1), rb_string_value_cstr(&v2));
    
    VALUE thread =
        rb_thread_create( (VALUE(*)(...))func_thread_tls, nullptr );
    
    /* wait for 'thread' to complete */
    rb_thread_sleep( 1 );
}
