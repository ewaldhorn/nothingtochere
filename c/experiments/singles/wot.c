#include "wot.h"

whole entrypoint() {
    say("I'm about to print some lines of text.\n");

    justLeaveABlankLineAlready

    whole lineCount = 1;
    repeatIf(lineCount isNotYet 20) {
        say("%2d This is a line of text.\n", lineCount);
        lineCount slapOn 1;
    }

    justLeaveABlankLineAlready

    say("That was some spam!\n");

    chuck 0;
}