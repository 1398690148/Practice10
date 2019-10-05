/*************************************************************************
    > File Name: practice4.cpp
    > Author: 
    > Mail:
    > Created Time: 2019年09月15日 星期日 14时37分25秒
 ************************************************************************/

#include <stdio.h>
#include <string.h>

int main() {
	int n;
	char str[10];
	while(~scanf("%d", &n)) {
		sprintf(str, "%x", n);
		printf("%s has %lu\n", str, strlen(str));
	}
	return 0;
}
