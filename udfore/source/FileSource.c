#include "udfore/source/Source.h"

typedef struct
{
    Source source;
    FILE *file;
} FileSource;

void file_source_destroy(FileSource *source)
{
    fclose(source->file);
}

char file_source_next_char(FileSource *source)
{
    return fgetc(source->file);
}

bool file_source_is_EOF(FileSource *source)
{
    return feof(source->file);
}

Source *file_source_create(const char *path)
{
    FILE *file = fopen(path, "r");

    if (file == NULL)
    {
        return NULL;
    }

    FileSource *source = __create(FileSource);

    source->file = file;

    SOURCE(source)->destroy = (SourceDestroyCallback)file_source_destroy;
    SOURCE(source)->next_char = (SourceNextCharCallback)file_source_next_char;
    SOURCE(source)->is_EOF = (SourceIsEOFCallback)file_source_is_EOF;

    source_initialize(SOURCE(source));

    return SOURCE(source);
}