# 2048

CLI 2048 written in 2 KiB.

```
$ wc *.c
     202     516    4930 2048.c
      33     170    2048 2048_minified.c
     201     514    3513 2048_renamed.c
     436    1200   10491 total
```


## Compile

```
$ make build
```

By default, `2048_minified.c` is compiled. If you want to use another source file, set `SUFFIX` like this: `SUFFIX= make build` (it compiles `2048.c`)


## Play

Execute the binary like this:

```
$ ./bin/2048
```

You can specify a grid size between 2 and 8. The default size is 4x4.

```
$ ./bin/2048 8x8    # large 2048
```


## Source Files

* `2048.c`
  * Human-friendly version.
* `2048_renamed.c`
  * All variables, functions and macros are renamed. It can be read to some extent.
* `2048_minified.c`
  * Minified version. Its file size is 2 KiB.
