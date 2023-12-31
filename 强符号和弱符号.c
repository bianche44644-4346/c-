/*1. 如果我们在两个源程序中定义了相同的全局变量,并且都对其初始化了,或者定义了相同的函数,那么程序在链接阶段就会报错:变量重复
定义*/
/*2. 但是,链接器是区分强弱符号的, 强符号: 1.定义一个函数
                                          2.定义一个全局变量并且初始化
                                  弱符号: 1.定义但是没有赋值的全局变量
                                          2. 使用_attribute_((weak))将强符号强制转换为弱符号,当然此函数是gcc下的,vs可能
                                             不支持,因为它很多都不支持*/

/*3. 强符号和弱符号的特性: 1.在不同源文件中如果定义了同名的强符号和弱符号,那么强符号会被弱符号替代(在链接成可执行文件之后)
                           2.如果在不同的源文件定义的都是同名的弱符号,那就看谁占的内存大,谁大就使用谁
                           3.不能出现同名的强符号*/
/*4. 强符号的弱符号的使用场景: 当我们自己开发库时,可将当中的符号设置为弱符号(使用_attribute_((weak))),这样即使用户定义的
与库中源文件的符号相同,那么外界的强符号也会代替库内的强符号*/

/*5. 注意事项: 强符号和弱符号的概念是相对与链接器的(源文件之间),编译器并不会区分强符号的弱符号,也就是说只要同一个源文件
内出现相同的符号,就会出错*/

//#include <stdio.h>
//
//int nub = 10; /*已赋值的全局变量,是一个强符号*/
//int nus; /*未赋值的全局变量,是一个弱符号*/
////_attribute_((weak)) , 抱歉了,windows下vs可能不支持强制转换为弱符号
//
//int main() /*函数,是一个强符号*/
//{
//
//    return 0;
//}
