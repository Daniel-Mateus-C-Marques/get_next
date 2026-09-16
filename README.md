# get_next_line

42 School project — a function that reads a file (or any file descriptor)
line by line, one call at a time, without relying on any built-in
line-reading function such as `getline` or `fgets`.

## Description

`get_next_line` returns the next line of a file each time it is called,
keeping track internally of what has already been read so the same file
descriptor can be read progressively — one line per call — without
re-reading the file from the start.

The mandatory part handles a single file descriptor at a time. The
**bonus** part extends this to handle **multiple file descriptors
simultaneously**, reading several files in parallel without losing each
one's individual progress.

## How it works

The core idea is a persistent buffer (the "stash") that survives between
calls thanks to a `static` variable:

- **`read_file`** — reads the file descriptor in chunks of `BUFFER_SIZE`
  bytes at a time and appends each chunk to the stash, until a newline
  (`\n`) is found or the file ends.
- **`line`** — extracts the first complete line (up to and including the
  `\n`) from the stash.
- **`rest`** — keeps whatever is left in the stash after that line, ready
  for the next call.
- **`get_next_line`** — orchestrates the three functions above and
  returns one line per call, or `NULL` when there is nothing left to
  read.

In the bonus version, the stash becomes an array indexed by file
descriptor (`static char *stash[1024]`), so each open file keeps its own
independent reading progress.

## Files

| File                          | Description                                   |
| ------------------------------ | ---------------------------------------------- |
| `get_next_line.c`              | Mandatory part — single file descriptor        |
| `get_next_line.h`              | Header with prototypes and `BUFFER_SIZE`       |
| `get_next_line_utils.c`        | Helper functions (`ft_strchr`, `ft_strjoin`, `ft_strlen`) |
| `get_next_line_bonus.c`        | Bonus part — multiple file descriptors         |
| `get_next_line_bonus.h`        | Header for the bonus version                   |
| `get_next_line_utils_bonus.c`  | Helper functions for the bonus version         |
| `main.c`                       | Simple test program                            |
| `text.txt`                     | Sample file used for testing                   |

## Usage

Compile with a custom buffer size (default behaviour depends on
`BUFFER_SIZE` defined in the header):

```bash
gcc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line.c get_next_line_utils.c main.c -o gnl
./gnl
```

Basic example:

```c
#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>

int main(void)
{
    int fd;
    char *line;

    fd = open("text.txt", O_RDONLY);
    while ((line = get_next_line(fd)))
    {
        printf("%s", line);
        free(line);
    }
    close(fd);
    return (0);
}
```

## What this project reinforces

- File I/O with `read`, buffering, and handling partial reads.
- Manual, careful memory management (`malloc`/`free`) across multiple
  function calls, avoiding leaks between successive calls.
- The behaviour of `static` variables to preserve state between function
  calls.
- Edge cases: empty files, files without a trailing newline, invalid file
  descriptors, and (in the bonus) reading several file descriptors at the
  same time without mixing up their contents.