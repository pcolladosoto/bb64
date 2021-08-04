# Test Source
These tests are based on the contents of the Wikipedia article covering Base64 which you can find [here](https://en.wikipedia.org/wiki/Base64). The binary files were generated through `macOS`'s (i.e. `BSD`'s) `/dev/random` device (which has a similar counterpart in `Linux`). The thing is, it was providing data at a huge pace for our purposes: we only wanted to generate small binary files to test our code.

In order to throttle the rate at which we were writing to a file we leveraged [`pv`](https://linux.die.net/man/1/pv). The following command limits the rate at which we write to the file to `1 kiB/s`. We only had to run the commadn for a couple of seconds before interrupting it with `^C` (i.e. `CTRL + C`) to gather all the data we needed:

    pv -L 1k /dev/random > bin.target
