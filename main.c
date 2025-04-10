#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include "render.h"
#include "errors.h"

static void recur_render(FILE* fp, void* data) {

    render("test2.txt", fp, data);
}

static void render_string(FILE* fp, void* data) {

    fprintf(fp, "%s", (const char*)data);
}

int main(int argc, char** argv) {

    render_table_t* ptr = create_render();

    render_item_t item1 = {
        "pootater",
        (void*)"NOW",
        render_string
    };

    add_render(ptr, &item1);

    render_item_t item2 = {
        "asdf",
        (void*)"IS THE",
        render_string
    };

    add_render(ptr, &item2);

    render_item_t item3 = {
        "asd",
        (void*)"TIME!",
        render_string
    };

    add_render(ptr, &item3);

    render_item_t item4 = {
        "recursive",
        (void*)ptr,
        recur_render
    };

    add_render(ptr, &item4);

    render_item_t item5 = {
        "pasd",
        (void*)"OPTIONAL",
        render_string
    };


    add_render(ptr, &item5);

    FILE* outf = fopen("test1.out", "w");

    render("test1.txt", outf, ptr);

    return 0;
}
