# Building Mapped

This document describes the various ways to build the Mapped application.

## Requirements

- CMake 3.14 or higher
- C++17 compatible compiler
- Git for cloning the repository

## Building with Docker

The easiest way to build Mapped is to use Docker, which handles all dependencies automatically.

### Using Docker Compose

```bash
# Build all platforms
docker-compose up --build

# Build specific platform
docker-compose up --build mapped-build-linux
docker-compose up --build mapped-build-windows
```

Output files will be in the `build/` directory, organized by platform.

### Using Docker directly

```bash
# Build Linux version
docker build -f docker/linux.Dockerfile -t mapped-linux-build .
docker create --name mapped-linux-container mapped-linux-build
docker cp mapped-linux-container:/output/. build/linux/
docker rm mapped-linux-container

# Build Windows version
docker build -f docker/windows.Dockerfile -t mapped-windows-build .
docker create --name mapped-windows-container mapped-windows-build
docker cp mapped-windows-container:/output/. build/windows/
docker rm mapped-windows-container
```

### Using the build script

```bash
chmod +x docker/build.sh
./docker/build.sh
```

## Manual Building

### Linux

```bash
mkdir build && cd build
cmake ..
make
```

### Windows

```bash
mkdir build && cd build
cmake ..
cmake --build . --config Release
```

### macOS

```bash
mkdir build && cd build
cmake ..
make
```

## GitHub Actions

The repository is set up with GitHub Actions workflows that will:

1. Run CI tests on pull requests (ci.yml)
2. Build and publish releases when tags are pushed (release.yml)

To create a new release, push a tag in the format `v{major}.{minor}.{patch}` (e.g., v0.1.0).
