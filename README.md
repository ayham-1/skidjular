# skidjular

A project schedular, so that I would be able to work on multiple projects daily.

## Getting started

To download a release, go the the releases page.

### Building from source

Download the soure from the git repository (Note: this might not be stable).

#### Prerequisites

##### Using ```nix```:

```shell
$ nix-shell
```

##### Install prerequisities of the project on ```ubuntu```:

```shell
$ sudo apt install cmake gcc
```

##### Install prerequisities of the project on ```arch```:

```shell
$ pacman -S cmake gcc
```

##### Install prerequisites of the project on ```gentoo```:

```shell
# sudo emerege --ask sys-devel/gcc sys-devel/make dev-util/cmake
```

#### Building

For release:

```shell
$  nix-shell
$ ./buildRelease.sh
```

For debug:

```shell
$  nix-shell
$ ./build.sh
```

#### Cleaning the directory

To clean the project directory:

```shell
$ ./clean.sh
```

## Contributing

Feel free to contribute to the project
TODO: Add an actuall CONTRIBUTING.md file.

## Authors

* **realaltffour** - *Initial Work* - [Profile](https://gitlab.com/realaltffour)

## License

This project is licensed under the GNU General Public License v3.0 - see the [LICENSE.md](LICENSE) file for details.
