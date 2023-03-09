#include<stdio.h>
#include<string.h>
#include<arpa/inet.h>

int main(int argc, char const *argv[])
{
    struct sockaddr_in addr1,addr2;
    char *str_ptr;
    char str_arr[20];

    addr1.sin_addr.s_addr = htonl(0x20202020);
    addr2.sin_addr.s_addr = htonl(0x10101001);

    str_ptr = inet_ntoa(addr1.sin_addr);
    strcpy(str_arr,str_ptr);
    printf("Dotted-Decimal notation1: %s \n",str_ptr);

    printf("str_ptr's address : %p\n",str_ptr);
    printf("str_arr's address : %p\n",str_arr);

    printf("str_arr'sdotted-decimal : %s\n",str_arr);

    inet_ntoa(addr2.sin_addr);//这里覆盖了str_ptr的那块地址
    printf("new str_ptr's address : %p\n",str_ptr);
    printf("Dotted-Decimal notation2: %s \n",str_ptr);
    
    printf("new str_arr's address : %p\n",str_arr);
    printf("Dotted-Deciaml natation3: %s \n",str_arr);

    return 0;
}