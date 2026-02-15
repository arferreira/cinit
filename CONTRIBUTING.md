# Contributing to cinit

cinit is a small project and contributions are welcome. Whether it's a bug fix, a new feature, or better docs — open a PR.

## Getting started

Fork the repo and clone it:

```bash
git clone https://github.com/<your-username>/cinit.git
cd cinit
make build
```

That's it. The project is a single C file with no external dependencies.

## Making changes

1. Create a branch from `main`.
2. Make your changes in `main.c`.
3. Test manually by building and running `cinit new testproject` to verify the scaffolding works.
4. Clean up any test directories you created.
5. Open a pull request against `main`.

## Code style

The codebase is intentionally simple. Keep it that way.

- Standard C, no external dependencies.
- Functions should do one thing. Each generated file has its own function.
- Check return values. If `fopen` or `mkdir` fails, handle it.
- Use `snprintf` for path construction, not `sprintf`.

## Ideas for contributions

- Add a `--help` / `--version` flag
- Generate a `.clang-format` in new projects
- Add more gitignore entries (binaries, build dirs)
- Support additional templates or project layouts
- Add a LICENSE file to generated projects
- Improve error messages

## Reporting issues

Open an issue on GitHub. Include what you expected, what happened, and your OS/compiler version if relevant.

## License

By contributing, you agree that your contributions will be licensed under the MIT License.
