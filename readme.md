# Pocha's Game Engine

Simple game engine library built on top of [SDL](https://libsdl.org).
It is made to ease the creation of basic 2D games while also keeping
them readable and easy to debug.

Compiles for GNU+Linux and Mingw (from within GNU+Linux).

Still on development, not recommended to use just yet.

## Installation

Available at the [AUR](https://aur.archlinux.org/packages/pge)

**dependencies:**

- [SDL](https://libsdl.org/download-2.0.php) (make & runtime)
- [pul](https://gitlab.com/ICanOnlySuffer/pul) (make)

**commands:**

	# make install clean

## Usage

**compilation:**

	$ cc main.c -lpge -lpul -lSDL2 -lSDL_ttf -lSDL2_image

## Examples

- [pge-examples](https://gitlab.com/ICanOnlySuffer/pge-examples)
- [connect-4](https://gitlab.com/ICanOnlySuffer/connect-4)

## Contributing

Bug reports, suggestions and pull requests are welcome!

