# cinit

A minimal project scaffolding tool for C. Think `cargo new` but for C projects.

Run one command and get a ready-to-compile project with a proper directory structure, Makefile, and boilerplate already in place.

## Usage

```bash
cinit new myproject
```

This creates the following structure:

```
myproject/
├── src/
│   └── main.c
├── Makefile
├── README.md
└── .gitignore
```

The generated project compiles immediately:

```bash
cd myproject
make build
./myproject
# Hello, World!
```

## Installation

### From source

Requires GCC and Make.

```bash
git clone https://github.com/arferreira/cinit.git
cd cinit
make build
make install
```

This compiles the binary and copies it to `/usr/local/bin/`.

To uninstall:

```bash
make uninstall
```

## What gets generated

**src/main.c** — A hello world starter file.

**Makefile** — `build` and `clean` targets using GCC. The binary name matches your project name.

**README.md** — A blank project readme with your project name as the title.

**.gitignore** — Ignores object files (`*.o`).

## Requirements

- GCC
- Make
- A project name longer than 3 characters

## License

MIT
