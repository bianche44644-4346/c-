///*学习使用宽字符类型*/
//#include <wchar.h> /*支持宽字节的头文件*/
//#include <locale.h> /*支持setlocale函数*/
//
//int main()
//{
//	/*windows不支持utf-16,所以无法正确输出*/
//	/*wchar_t是使用utf-16编码的,但是vs不支持,所以有些字符无法正确输出*/
//
//	/*字符前面加上L表示宽字符(占用2个字节或者4个字节的内存)*/
//	wchar_t a = L'?'; /*使用一个简单的字符类型无法输出这种特殊符号,以及中文字符*/
//	wchar_t b =L'中';
//
//	/*将本地环境设置为简体中文*/
//	setlocale(LC_ALL, "zh_CN");
//
//	/*宽字节类型,转义字符使用%lc*/
//	//wprintf("%lc", a);
//	wprintf(L"%lc\n", a);
//
//	putwchar(a);
//
//	return 0;
//}