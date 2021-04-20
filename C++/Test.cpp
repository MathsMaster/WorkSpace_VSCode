#include <stdio.h>
#include <iostream>

int main()
{
    printf("C++ Hello World!\n");
	std::cout << 1 << std::endl;
    std::cout << 100000000000000000 << std::endl;
	std::cout << 1.23456 << std::endl;
	std::cout << "输出整数: " << 1 << std::endl;
	std::cout << "输出小数: " << 123.456 << std::endl;
	std::cout << 1 << 2 << "." << 3 << 4 << std::endl;

    char str[100];  
    std::cout << "请输入算术表达式(功能：+，-，*，/)" << std::endl;  
    std::cin >> str; 

    printf("C++中进行的输入 : %s \n",str);
}