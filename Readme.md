# 🐦‍⬛ Super Bird Swarm

Super Bird Swarm is a simulation of bird flocking behaviour using the [Boids](https://en.wikipedia.org/wiki/Boids) algorithm. The simulation demonstrates how birds (boids) can exhibit complex flocking behaviour through simple rules:

- Alignment - Birds steer towards the average direction of birds around them.
- Cohesion - Birds steer towards the average position of the birds around it.
- Separation - Birds steer to avoid crowding other birds around them.

Within the simulation, you can adjust the weights of each of the simulation's rules to see how they impact the flocking behaviour of the birds.

![example swarm](docs/resources/swarm.gif)

## 🛠️ How do I build and install Super Bird Swarm?

### 📋 Prerequisites

- CMake 3.10 or higher
- SFML 2.5 or higher
- A C++20 compatible compiler

### 🏗️ Building

1. Clone the repository:
    ```sh
    git clone https://github.com/andrew-t97/super-bird-swarm.git
    cd super-bird-swarm
    ```

2. Configure the project with Cmake:
    ```sh
    cmake -B build
    ```

4. Build the project:
    ```sh
    cmake --build build
    ```

### 🚀 Running the simulation

After building, you can navigate to the build's source dir where you can run the executable:
```sh
cd ./build/src
./swarm_demo
```

### 📦 Installing the project for easier simulation running.

If you don't want to navigate the build files to run the simulation you can install it into a directory instead. Just run the following in the project's root after you've built the simulation.

```sh
cmake --install build --prefix <dir-to-install-into>
```

You can then run the simulation with the following:
```sh
cd <dir-to-install-into>/bin
./swarm_demo
```