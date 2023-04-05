/* OffByOne.c
 * If you run this program in gdb, it shows it's hacked.
 * But if you run it directly in shell, it doesn't show it's hacked.
 * -O0 -fno-stack-protector does not help.
 * Is the address different when running in gdb?
*/
#include <stdio.h>
#include <string.h>
void foo()
{
    char buf[96];
    char in[96];
    scanf("%s", in);
    strncpy(buf, in, sizeof(buf));
    buf[sizeof(buf)] = '\0'; //whups off by one!
    printf("%s\n", buf);
}

void bar(const char* in)
{
    printf("=======================\n");
    printf("Augh! I've been hacked!\n");
    printf("=======================\n");
}

void test()
{
    char msg[16] = "= Off By One =\n";
    printf(msg);
    foo();
}

int main(int argc, char* argv[])
{
    char msg[32];
    printf("Address of foo is %p, address of bar is %p\n", foo, bar);
    test();
    return 0;
}
