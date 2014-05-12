#include <Ruby/Ruby.h>
#include <stdio.h>

void test_string(){
    VALUE str = rb_str_new2("hello world");
    
    printf("test_string %s\n",
        rb_string_value_cstr(&str) );
}
void test_string2(){
    VALUE str1 = rb_str_new2("hello ");
    VALUE str2 = rb_str_new2("world");
    
    VALUE str3 = rb_str_append( str1, str2 );
    
    printf("test_string2 %s\n",
        rb_string_value_cstr(&str3) );
}
