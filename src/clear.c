/**
 * clear - clear the current terminal. Uses escape sequences.
 */

#include <stdio.h>

int main() {

    printf("\x1b\x5b\x48\x1b\x5b\x32\x4a");

}
