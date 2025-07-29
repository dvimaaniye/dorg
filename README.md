# Directory Organizer
#### Organizes files in a directory into a set of pre-defined directories (based on file extension)
#### Video demo: [youtube](https://youtu.be/XtjhkAGHGkM)

## Prerequisites
Before installing, ensure the following dependencies are available on your system:
- `Boost` >= 1.83
- `cmake` >= 3.31
- `ninja` >= 1.12 or `make` >= 4.4 _(recommended: ninja)_ _(Older versions might work but are not tested.)_
- `clang` >= 20 _(Older versions might work but are not tested.)_

## Installation
Supported OS: GNU/Linux
#### Step 1. Clone this repo on your system:
```bash
git clone --depth 1 https://github.com/dvimaaniye/dorg.git
```

#### Step 2. `cd` into the cloned repo:
```bash
cd dorg
```

#### Step 3. Run the installation script:
```bash
bash install
```
Or

Ensure that the installation script is executable:
```bash
chmod +x ./install
```
Then execute the installation script:
```bash
./install
```
`dorg` should be installed on your system now, yay!

## Usage
You can also see this help menu by running `dorg -h`, once you have dorg installed on your system.
```
Usage:
  dorg -s <path>
       [-d | --dest <path>]
       [-i | --insensitive-case]
       [-o | --override]
       [-k | --skip]
       [-q | --quiet]
       [-v | --verbose]
       [-h | --help]
       [--dry-run]

To get default config:
  dorg get-config

Note: Symlinks and directories are never moved
Options: 
  -s DIRECTORY, --source DIRECTORY    Directory to organize the files of (required)
  -d DIRECTORY, --dest DIRECTORY      Directory to where the organized files are saved (default: source)
  -c FILE_PATH, --config FILE_PATH    Path to custom config
  -i, --insensitive-case              Whether to treat, for ex: jpg and JPG, as same. (default: false, i.e., they are different)
  -o, --override                      Override existing files without asking
  -k, --skip                          Skip existing files without asking
  --dry-run                           Does not move any file or create any directory
  -q, --quiet                         Run without logs (will display errors)
  -v, --verbose                       Logs debug info
  -h, --help                          Print the help menu

```

## Summary of files
- `external/*`: External libraries
- `libs/*`: All internal libraries
- `libs/libutility/`: A library for common shared functions, classes, and namespaces
- `libs/liblogger/`: Custom logging solution. _I wanted to keep it independent of shared libraries, therefore, it's a separate library_
- `libs/liborganizer/`: The Organizer class that handles the main logic for organizing files. Uses libutility and liblogger
- `main.cpp`: The entrypoint and main orchestrating file that is a CLI program utilizing all the libraries we have mentioned so far

If anything is a common shared utility, it goes into `libs/libutility` unless it's independent of `libs/libutility` in which case it becomes its own library, like `libs/liblogger`.

## A note on the project structure
The file structure of the project was inspired by [Canonical Project Structure](https://www.open-std.org/jtc1/sc22/wg21/docs/papers/2018/p1204r0.html) but later drifted from it to distinguish internal libraries from external libraries via the `external` directory. This avoids unnecessary confusion and provides clarity on external dependencies of the project.
