# BackToTheFuture   

This is a simple compress / decompress application.

## Usage

### Building The Project

#### Git Clone

```bash
❯ mkdir ~/workspace
❯ cd ~/workspace
❯ git clone \
    https://github.com/emttiew/BackToTheFuture.git \
    my-project
❯ cd my-project
❯ git submodule init && git submodule update
```

#### Building Manually

```bash
❯ mkdir build && cd build
❯ cmake ..
❯ make && make install
```

#### Run App
```bash
❯ cd bin/
❯ ./BackToTheFuture c|compress|d|decompress <source_path> <archive_path> reporter(optional)
```
#### Run Tests
```bash
❯ cd bin/
❯ ./backToTheFutureTests
```
#### Release

You can download prebuild binary wiht .so zip library from Releases

```bash
❯ chmod +x run_binary.sh
❯ ./run_binary.sh
```
