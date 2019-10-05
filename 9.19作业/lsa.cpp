/*************************************************************************
	> File Name: lsa.cpp
	> Author: 
	> Mail: 
	> Created Time: 2019年09月23日 星期一 19时47分36秒
 ************************************************************************/
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
#include <dirent.h>

//\033(e)[显示方式;前景色;背景色m\033(e)[0m

void get_mode(struct stat buff)//得到当前的文件类型和三个权限
{
    char *ptr;
    unsigned int i,mask = 0700;
    static char *perm[]={"---","--x","-w-","-wx","r--","r-x","rw-","rwx"};//分别对应0 1 2 3 4 5 6 7
    if(S_ISREG(buff.st_mode))
        ptr="-";
    else if(S_ISDIR(buff.st_mode))
        ptr="d";
    else if(S_ISLNK(buff.st_mode))//符号连接
        ptr="l";
    printf("%s",ptr);
    for(i=3;i;i--)
    {
        printf("%3s",perm[(buff.st_mode&mask)>>(i-1)*3]);//我们得到的3位8进制数 从左到右分别是 右边没有参与运算的处理掉
        mask >>= 3;//mask是掩码
    }
}

void get_name(struct stat buff)//得到属主名字 和 属主所在的组 名字
{
    struct passwd *user=NULL;//定义一个用户的结构体
    struct group *group=NULL;//定义一个组的结构体
    user=getpwuid(buff.st_uid);//文件属主的用户身份标识
    printf(" %s",user->pw_name);//得到这个标识结构体中的用户名字
    group = getgrgid(buff.st_gid);//文件属主的分组身份标识
    printf("    %s",group->gr_name);
}

void get_time(struct stat buff)//最新的内容修改时间
{
    char *month[]={"1月","2月","3月","4月","5月","6月","7月","8月","9月","10月","11月","12月"};
    struct tm *mptr=NULL;//时间结构体
    mptr = localtime(&buff.st_mtime);//文件内容方面的上次被修改时间 atime上次被访问时间 ctime文件权限\属主\分组或内容方面的上次被修改时间 这个函数取得文件的时间
    printf(" %4s %2d ",month[mptr->tm_mon],mptr->tm_mday);
    printf("%02d:%02d",mptr->tm_hour,mptr->tm_min);
}

void list_info(struct stat buff)//文件类型的就列出各种函数得到的结果
{
    get_mode(buff);
    printf("%5d",buff.st_nlink);//得到硬链接
    get_name(buff);
    printf("%12ld",buff.st_size);//文件大小
    get_time(buff);
}

void list_dir(char *dir_path)//是目录类型的 就
{
    int i;
    static int count = 0;
    DIR *dirp=NULL;//一个文件目录指针
    struct dirent *dp=NULL;//存储目录中的文件信息的结构体
    struct stat buff;//存储文件信息的结构体
    dirp=opendir(dir_path);//打开一个子目录并建立一个子目录流
    chdir(dir_path);//进入这个子目录流
    while((dp=readdir(dirp)) != NULL)//读这个子目录流是否有内容readdir函数读取到的文件名存储在结构体dirent的d_name成员中
    {
        if(dp->d_name[0]=='.')//隐藏文件
            continue;
        if(lstat(dp->d_name,&buff)==-1)//函数lstat的作用就是获取文件名为d_name的文件的详细信息，存储在stat结构体中
        {
            printf("fail to get stat\n");
            continue;
        }
        /*for(i = 0;i<count;i++)//深入的次数
        {
            printf(" \t",count);
        }*/
        list_info(buff);
        if(S_ISREG(buff.st_mode))
        {
            printf(" %s\n",dp->d_name);
        }
        else if(S_ISDIR(buff.st_mode))
        {
            printf(" \e[1;34m%s\e[0m\n",dp->d_name);
            //count++;//再次深入
            //list_dir(dp->d_name);//自身递归 直到该层的目录中的文件列表读完了 才出来
            //count--;//递归出来深入减1
        }
        else if(S_ISLNK(buff.st_mode))//如果是链接
        {
            char sbuf[128];
            memset(sbuf,'\0',128);
            if(readlink(dp->d_name,sbuf,128)!=-1)//成功找到源
            {
                printf(" \e[0;36m%s\e[0m -> %s\n",dp->d_name,sbuf);
            }else{
            printf("error\n");
            }
        }
    }//一直读取到这一层目录文件列表完成*/
    chdir("..");//返回到上级目录
}

int main(int argc,char *argv[])
{
    int i;
    struct stat buff;//定义stat的结构体
    if(argc<2)//缺少给定的参数文件
    {
        printf("loss argument\n");
        return -1;
    }
    for(i=argc-1;i>=1;i--)
    {
        if(lstat(argv[i],&buff)==-1)// lstat,是一种文件描述词。意思是获取一些文件相关的信息，成功执行时，返回0。失败返回-1
        {
            printf("%s error\n",argv[i]);
            continue;
        }
        if(S_ISREG(buff.st_mode))//文件是一个普通文件
        {
            list_info(buff);
            printf(" %s\n",argv[i]);
        }
        else if(S_ISDIR(buff.st_mode))//文件是一个子目录
        {
            list_dir(argv[i]);
        }
        else if(S_ISLNK(buff.st_mode))//文件是一个符号链接
        {
            list_info(buff);
            char sbuf[128];
            memset(sbuf,'\0',128);//用‘\0’填充字符串sbuf
            if(readlink(argv[i],sbuf,128)!=-1)//readlink取得符号链接所指的文件readlink()会将参数path 的符号连接内容存到参数sbuf 所指的内存空间, 返回的内容不是以NULL作字符串结尾, 但会将字符串的字符数返回. 若参数bufsiz 小于符号连接的内容长度, 过长的内容会被截断.执行成功则传符号连接所指的文件路径字符串
            {
                printf(" \e[0;36m%s\e[0m -> %s\n",argv[i],sbuf);
            }else{
                printf("error\n");
                }
            }
            printf("\n");
    }
}
