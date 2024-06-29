# DU-C
`du-c` is a project with the goal to "replicate" `du`'s behavior. It was coded in C, as the name suggests.

# How it works
`du-c` expects you to give a file name as argument, like so:

```shell
$ ./du-c text_file.txt
```

And it will then print the file size:
```shell
$ ./du-c text_file.txt
943 KB -> text_file.txt
```

By default, it will try to print the "biggest" size; however, you can force it to output the size in any "base" with an argument:
```shell
$ ./du-c text_file.txt -b # Print in bytes.
966240 B -> text_file.txt

$ ./du-c text_file.txt -k # Print in kilobytes. (default for this specific file.)
943 KB -> text_file.txt

$ ./du-c text_file.txt -m # Print in megabytes.
0 MB -> text_file.txt

$ ./du-c text_file.txt -g # Print in gigabytes.
0 GB -> text_file.txt
```

Note: The argument order does not matter, as long as the file name does not start with a `-`, it will be considered as the file name argument.

Note 2: Since I'm not using floating points (*yet*) in the codebase, some files that are smaller than a forced base will display as `0`.

# Compiling
Pre-requisites:
- A `GCC` version that supports `C17`, any recent one should work.
- `make`.

To build the source, just run:
```shell
$ make
```

And it will start compiling and linking.

Note: I don't recall how it works on Windows, but users would probably want to add `.exe` in the [Makefile](Makefile#L1).