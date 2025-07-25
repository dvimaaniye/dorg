# Directory Organizer
#### Video Demo:  <URL HERE>
#### Description: Organizes files in a directory into a set of defined directories

## Prerequisites
Before installing, ensure the following dependencies are available on your system:
- `Boost` >= 1.83
- `cmake` >= 3.31
- `make` >= 4.4 or `ninja` >= 1.12 _(Older version might work, but are not tested)_
- `clang` >= 20 _(Older version might work, but are not tested)_

## Installation
#### Step 1. Clone this repo on your system
```bash
git clone --depth 1 https://github.com/dvimaaniye/dorg.git
```

#### Step 2. `cd` into the cloned repo
```bash
cd dorg
```

#### Step 3. Ensure that the installation script `install.sh` is executable.
```bash
chmod +x ./install.sh
```

#### Step 4. Run the installation script.
```bash
./install.sh
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
  -h, --help                          Print the help menu
```
