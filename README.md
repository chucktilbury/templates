# Templates
I need a simple C library that can do HTML-like templates. I seem to write a lot of filters these days and a template for outputing formatted text seems to be the right thing. However, I don't want to write a full parser and state machine. I simply don't want to go to all of that effort. Also, the filters I am writing are in C. Normally I would just do things like that in Python and call it done, but I cannot do that for the projects that I am actually doing for various reasons.

The code that implements this should be easy to embed in another applicaiton or run as a stand-alone program with a stock of facilities to load and render common types of data.

So here is the high level view of what I am thinking. The template will be a text file with a simple tag format that contains a name that has been placed in a hash table prior to rendering. The hash table contains a data structure that has all of the information needed to render the tag, including a function pointer that will do the actual rendering. That way, the simple tag can reference any kind of data from very simple to very complex. All the template driver does is create the hash table and filter the text, executing the render function as needed.

Example of the contents of a template file, which is plain text.
```
some arbitrary text
{{the_tag}}
some other text
```

The data structure might look like this. It can literally be anything as long as the render function knows how to convert the ``void*`` to the correct data type. The 3 data fields are required and must have known names. Other than that, the only limit to what can be in the structure is what can exist in a C data structure.
```
struct data {
  const char* tag;  // name in the hash table
  void (*render_func)(void*); // render funciton knows how to cast the data
  const char* data[]; // arbitrary data with a known name
};
```

The code that runs when a tag is recognized in the template might look like this. It simply finds the name in the hash table and calls the render function.
```
void render(FILE* out, const char* name) {
  struct data* ptr = find_name(name);
  ptr->render_func((void*)ptr->data):
}
```

The render function simply takes the data defined in the data structure and renders it to the file pointer, which is the output. 
