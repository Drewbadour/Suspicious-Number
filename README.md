
# Suspicious Number

**Suspicious Number** is an [Alfred.app](https://www.alfredapp.com/) workflow that can be used to convert numbers from one base to another. Its primary goal is to allow you to take a random number you've found in a memory register and determine what that memory might refer to.

## Features

- Convert from:
	- Decimal [LLONG_MIN,ULONG_MAX];
	- Hex
	- Binary
- Convert to:
	- Decimal
	- Hex
	- Binary
	- ASCII
	- Unicode

### Future Improvements

- Arbitrary length decimal numbers. They are currently limited to `int64_t`/`uint64_t` sizes.

## Building

The project compiles multiple targets using `make`. Consider checking `make help` for help.

```bash
→ make help
usage: make [target]
	build - Compile all binaries in a debug build for the local architecture
	test - Compile the unit tests for the local architecture
	release - Compile all binaries in a release build for the local architecture
	package - Create a universal suspicious-number.alfredworkflow for distribution
	link - Link the workflow into the install of Alfred
	unlink - Unlink the workflow from Alfred
	clean - Delete all of the build products
	help - This menu
```

### Unit Tests

To run the unit tests, compile with:

```bash
make test && ./bin/test_runner
```

### Linking to Test

This will allow you to test the builds and soon as you make them in Alfred:

```bash
make link
```

When you are done testing, make sure to unlink with:

```bash
make unlink
```

### Packaging

In order to build for both macOS architectures, and get a valid `.alfredworkflow`, run:

```bash
make package
```
