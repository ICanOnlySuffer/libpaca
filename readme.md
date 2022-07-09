# libpaca

Simple game engine library built on top of [SDL](https://libsdl.org) 
made to ease the creation of basic 2D games while also keeping
them readable and easy to debug.

Compiles for GNU+Linux and Mingw (from within GNU+Linux).

Still on development, not recommended to use just yet.

## Installation

Available at the [AUR](
https://aur.archlinux.org/packages/libpaca)

**dependencies:**

- [libpocha](https://gitlab.com/ICanOnlySuffer/libpocha) (make)
- [SDL2](https://libsdl.org/download-2.0.php) (make & runtime)

**commands:**

	# make install clean

## Usage

**compilation:**

	$ cc main.c -lpaca -lpocha -lSDL2 -lSDL_ttf -lSDL2_image

## Examples

- [paca-examples](https://gitlab.com/ICanOnlySuffer/paca-examples)
- [connect-4](https://gitlab.com/ICanOnlySuffer/connect-4)

## Contributing

Bug reports, suggestions and pull requests are welcome!

