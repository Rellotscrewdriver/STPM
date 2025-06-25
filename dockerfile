# Use the ArchLinux base image
FROM archlinux:latest

# Set the environment variables
ENV CMAKE_PREFIX_PATH=/usr/lib/cmake

# Set the working directory to /app
WORKDIR /app

# Install CMake and git
RUN pacman -Sy --noconfirm cmake ninja clang

# Copy the source
COPY . .

# Build the project using CMake
RUN cmake -S . -B build -G "Ninja"
RUN cmake --build build

# Copy the executable
RUN cp -r build/template template

CMD ["./template"]