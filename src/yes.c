#include <unistd.h>

int main() {
    char* y = "y\n";
    int l = sizeof(char) * 2;

    while (1) {
        write(1, y, l);
    }
}
