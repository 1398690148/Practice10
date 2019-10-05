/*************************************************************************
	> File Name: a.cpp
	> Author: 
	> Mail: 
	> Created Time: 2019年09月21日 星期六 18时39分38秒
 ************************************************************************/
#include<stdio.h>
#include<sys/types.h>
#include<sys/ioctl.h>
#include<unistd.h>
#include<termios.h>

int main()
{
    //定义winsize 结构体变量
    struct winsize size;
    //TIOCSWINSZ命令可以将此结构的新值存放到内核中
    ioctl(STDIN_FILENO,TIOCGWINSZ,&size);
    printf("%d\n",size.ws_col);
    printf("%d\n",size.ws_row);
    return 0;
}
