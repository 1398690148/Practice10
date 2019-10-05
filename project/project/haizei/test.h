/*************************************************************************
	> File Name: test.h
	> Author: hug
	> Mail:   hug@haizeix.com
	> Created Time: 四  9/26 19:57:45 2019
 ************************************************************************/

#ifndef _TEST_H
#define _TEST_H

#define COLOR(a, b) "\033[0" #b "m" a "\033[0m"
#define GREEN(a) COLOR(a, 32)
#define RED(a) COLOR(a, 31)
#define BLUE(a) COLOR(a, 34)
#define YELLOW(a) COLOR(a, 33) 

#define TEST(a, b) \
void a##_haizei_##b(); \
__attribute__((constructor)) \
void add##_haizei_##a##_haizei_##b() { \
    add_function(a##_haizei_##b, #a "." #b); \
} \
void a##_haizei_##b()

#define EXPECT(a, b, comp) { \
    __typeof(a) _a = a, _b = b; \
    printf(GREEN("[-----------] ") #a " " #comp " " #b); \
    printf(" %s\n", (_a) comp (_b) ?  GREEN("TRUE") : RED("FALSE")); \
    if (_a comp _b) { \
        haizei_test_info.success += 1; \
    } else { \
        printf("\n"); \
        printf(YELLOW("\t%s %d Failure\n"), __FILE__, __LINE__); \
        printf("\n"); \
    } \
} 

#define EXPECT_EQ(a, b) EXPECT(a, b, ==)

typedef void (*TestFuncT)();

struct Function {
    TestFuncT func;
    const char *str;
};

struct FunctionInfo {
    int total, success;
};

extern struct FunctionInfo haizei_test_info;

int RUN_ALL_TESTS();
void add_function(TestFuncT, const char *);

#endif
