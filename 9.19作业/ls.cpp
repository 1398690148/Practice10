/*************************************************************************
    > File Name: ls.cpp
    > Author: 
    > Mail:
    > Created Time: 2019年09月20日 星期五 15时55分25秒
 ************************************************************************/
#include <iostream>
#include <cstring>
#include <algorithm>
#include <sys/types.h>
#include <cerrno>
#include <dirent.h>
#include<sys/ioctl.h>
#include<unistd.h>
#include<termios.h>

using namespace std;
#define MAX_N 2000

struct NAME{
    string name;
    int length;
};

struct NAME names[MAX_N + 5];

void readFile(int &i, char *argv[]) {
	DIR *dp = NULL;
	dp = opendir(argv[1]);
    if (!dp) {
        fprintf(stderr, "opendir: %s\n", strerror(errno));
        return ;
    }
    struct dirent *dirp;
    while ((dirp = readdir(dp))) {
        if (strcmp(dirp->d_name, ".") == 0 || strcmp(dirp->d_name, "..") == 0)
        continue;
		names[i].name = dirp->d_name;
        names[i].length = names[i].name.length();
		i++;
    }
    closedir(dp);
}


bool cmp(struct NAME a, struct NAME b) {
	return a.name < b.name;
}

bool cmp1(struct NAME a, struct NAME b) {
    return a.length < b.length;
}

int main(int argc, char *argv[]) {
	int len = 0;
    int max_size = 0;
	if (argc < 2) {
        fprintf(stdout, "Usage: too few paramters!\n");
        return 0;
    }
	readFile(len, argv);
	sort(names, names + len, cmp1);
    max_size = names[len - 1].length;
    struct winsize size;
    //TIOCSWINSZ命令可以将此结构的新值存放到内核中
    ioctl(STDIN_FILENO,TIOCGWINSZ,&size);
    max_size = size.ws_col / max_size;
    for (int i = 0; i < len; i++) {
        cout << names[i].name;
        if (max_size < 1) {
            cout << endl;
            continue;
        }
        for (int j = 0, I = size.ws_col / max_size - names[i].name.length(); j < I; j++)
        cout << " ";
        if ((i + 1) % max_size == 0) cout << endl;
	}
    cout << endl;
	return 0;
}
