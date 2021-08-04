# A Botched Base64 Decoder
We have been recently admitted to the technical preview of [GitHub's Copilot](https://copilot.github.com) and so we thought about testing it on a small-scale project. We decided to write a rather simple Base64 decoder in C. We also took the time to set up [GPG keys](https://docs.github.com/en/github/authenticating-to-github/managing-commit-signature-verification/signing-commits) and to also give [GitHub CLI](https://cli.github.com) a go.

## Compiling the Code
We have provided a simple `Makefile` in the source directory. Compiling the project should be as easy as running `make` from within the `src/` directory. We have developed and tested the code on `macOS`, but it should run out of the bow on `Linux`-based systems too.

## Installing the Program
As we believe this to be a rather silly program we have **not** included a `Makefile` target for installing the program itself. Feel free to copy the generated binary to a location on your system's `PATH`, such as `/bin`or wherever you have decided to place scripts written or compiled by yourself :P

## Background on Base64
We have personally never had to deal with Base64 ourselves, so we first had to get acquainted with it on [Wikipedia](https://en.wikipedia.org/wiki/Base64). That article¡s got a ton on information on Base64 and it was the sole source of information we relied on. You can also take a look at [RFC 4648](https://datatracker.ietf.org/doc/html/rfc4648) for a more technical discussion.
