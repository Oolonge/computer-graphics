#ifndef ERRORS_H
#define ERRORS_H

enum errors
{
    NONE,
    FILE_NOT_FOUND,
    FILE_FORMAT_ERR,
    FILE_CONTENT_ERR,
    PTR_ALLOC_ERR,
    NO_DOTS,
    NO_CONNECTIONS,
    UNKNOWN_COMMAND
};

void error_message(errors err);

#endif // ERRORS_H
