#include <stdio.h>
#include <string.h>

struct Book{
    char name[100];
    char *content;
    int price;
};

int main()
{
    struct Book book;
    
    book.content = "这是内容";
    book.price = 123;
    strcpy(book.name,"书的名字");

    printf("书本的内容  book.content : %s\n",book.content);
    printf("书本的价格  book.price : %d\n",book.price);
    return 0;
}