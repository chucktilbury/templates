#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include "template.h"
#include "errors.h"

static void render_string(FILE* fp, void* data) {

    fprintf(fp, "%s", (const char*)data);
}

int main(int argc, char** argv) {

    const char* infn = "test1.txt";
    const char* outfn = "test1.out";

    FILE* inf = fopen(infn, "r");
    ASSERT(inf != NULL, "cannot open input file: \"%s\": %s\n", infn, strerror(errno));
    FILE* outf = fopen(outfn, "w");
    ASSERT(outf != NULL, "cannot open output file: \"%s\": %s\n", infn, strerror(errno));

    template_t* ptr = create_render(inf, outf);

    template_item_t item1 = {
        "pootater",
        (void*)"NOW ",
        render_string
    };

    add_render(ptr, &item1);

    template_item_t item2 = {
        "asdf",
        (void*)"IS THE ",
        render_string
    };

    add_render(ptr, &item2);

    template_item_t item3 = {
        "asd",
        (void*)"TIME!",
        render_string
    };

    add_render(ptr, &item3);

    render(ptr);

    return 0;
}
