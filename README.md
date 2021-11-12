# 2048

CLI 2048 written in 2 KiB.

```
$ wc -c *.c
    2048 2048.c
    4930 2048_clean.c
    6978 total
```


## Compile

```
$ make build
```

By default, `2048.c` is compiled. If you want to compile another source file, set `SUFFIX` like this: `SUFFIX=_clean make build` (it compiles `2048_clean.c`)


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
  * Minified version. Its file size is 2 KiB.
* `2048_clean.c`
  * Human-friendly version.
