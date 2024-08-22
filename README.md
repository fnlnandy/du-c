# DU-C
`du-c` is a hobby project that I started, with the goal being to "replicate" as much as possible `du`'s behavior (a command on *most* Linux distros). The whole project is in C, hence why I named it this way.

# How it works
`du-c` expects a file name as argument, so you would invoke it like so:
```shell
$ ./du-c text_file.txt
```

And it will then print the file size:
```shell
$ ./du-c text_file.txt
943 KB      text_file.txt
```

However, it's possible to not provide any argument. If `du-c` realizes you aren't passing anything, it will operate on the current working directory.

By default, it will search for the *widest* and *most appropriate* size type to print, that behavior can however be altered with a **forced type** argument. The list of possible arguments to force a type are:
|---|-----------|
|-b |Byte(s)    |
|---|-----------|
|-k |Kilobyte(s)|
|---|-----------|
|-m |Megabyte(s)|
|---|-----------|
|-g |Gigabyte(s)|
|---|-----------|

Here are some examples of how it would work:
```shell
$ ./du-c text_file.txt -b # Print in bytes.
966240 B        text_file.txt

$ ./du-c text_file.txt -k # Print in kilobytes. (default for this specific file.)
943 KB      text_file.txt

$ ./du-c text_file.txt -m # Print in megabytes.
0 MB        text_file.txt

$ ./du-c text_file.txt -g # Print in gigabytes.
0 GB        text_file.txt
```

__Note__: By the way the software is laid out right now, it has no real way to guess which argument is supposed to be the file name. So, any argument that *does not* begin with an `-` will overwrite the current `filePath` variable (on which the software operates).

__Note 2__: Since I am not using `float`s within this project, sizes that are smaller than the minimum for the passed forced size type, will be displayed as `0`.

# Compiling
Prerequisites:
If you're on Windows, you probably want to use `msys2`.

- Any C Compiler that supports `C17` should *supposedly* work.
- GNU `make`.

__Note__: If the compiler *is not* `gcc`, you may want to update the appropriate `Makefile` line:
```Makefile
CC := gcc
```
And replace `gcc` with whatever your compiler's name is. Note that `gcc` is also used for linking in the process.

To build the source, just run:
```shell
$ make -j$(nproc)
```

Now, if everything went well, it should start building.

To clean the repository, e.g. after making a change to a header etc... One can just run:
```shell
$ make clean -j$(nproc)

```
