# NautyToChapel - Nauty Integration for the Arachne Framework

![NautyToChapel Logo](https://github.com/mdindoost/NautyToChapel/blob/main/logo.png?raw=true)

## Table of Contents

- [Overview](#overview)
- [Features](#features)
- [Repository Structure](#repository-structure)
- [Requirements](#requirements)
- [Installation](#installation)
  - [1. Clone the Repository](#1-clone-the-repository)
  - [2. Install Nauty](#2-install-nauty)
  - [3. Build the Nauty Integration](#3-build-the-nauty-integration)
- [Usage](#usage)
  - [Function Interface](#function-interface)
  - [Chapel Integration Example](#chapel-integration-example)
- [Example Test](#example-test)
  - [C++ Test Code](#c-test-code)
  - [Expected Output](#expected-output)
- [Compilation Instructions](#compilation-instructions)
  - [C++ Compilation](#c-compilation)
  - [Chapel Compilation](#chapel-compilation)
- [Dependencies](#dependencies)
- [Contributing](#contributing)
- [License](#license)
- [Contact](#contact)

## Overview

**NautyToChapel** is a project that integrates the **Nauty** library with the **Chapel** programming language to perform graph canonicalization within the **Arachne Framework**. This integration allows developers to efficiently convert graphs, represented as flattened adjacency matrices, into their canonical forms, enabling tasks such as graph isomorphism checks and pattern recognition within Chapel-based applications.

## Features

- **Graph Canonicalization**: Leverage Nauty's optimized algorithms to compute canonical labelings of graphs.
- **Chapel Integration**: Seamlessly call C++ functions from Chapel, enabling high-performance graph processing.
- **Simplified Interface**: The `nautyClassify` function abstracts away memory management, requiring only the adjacency matrix, its size, and a results array.
- **Flexible Usage**: Suitable for both directed and undirected graphs.
- **Extensible**: Easily extendable to accommodate more complex graph structures or additional functionalities.

## Repository Structure

NautyToChapel/ ├── NautyProject/ │ ├── include/ │ │ └── nautyCaller.h │ ├── src/ │ │ ├── nautyCaller.cpp │ │ └── main.cpp │ ├── tests/ │ │ └── test_nauty.cpp │ ├── examples/ │ │ └── chapel_integration.chpl │ ├── README.md │ └── LICENSE └── .gitignore


- **NautyProject/**: Contains all source code, headers, and test files.
  - **include/**: Header files.
  - **src/**: Source code files.
  - **tests/**: Test programs to verify functionality.
  - **examples/**: Example Chapel code demonstrating integration.
- **README.md**: Project documentation.
- **LICENSE**: Licensing information.
- **.gitignore**: Specifies intentionally untracked files to ignore.

## Requirements

Before setting up NautyToChapel, ensure the following dependencies are met:

- **Nauty Library**: For graph canonicalization.
- **C++ Compiler**: Such as `g++` for compiling the C++ integration code.
- **Chapel**: The Chapel programming language environment.
- **Build Tools**: Tools like `make` for building the project (optional but recommended).

## Installation

### 1. Clone the Repository

Clone the NautyToChapel repository to your local machine:

```bash
git clone https://github.com/mdindoost/NautyToChapel.git
cd NautyToChapel/NautyProject
```
Usage
Function Interface
The nautyClassify function provides a simplified interface for canonicalizing graphs. It encapsulates all necessary memory allocations and deallocations internally.

Function Signature:


void nautyClassify(
    int* subgraph,        // Adjacency matrix as flat array
    int subgraphSize,     // Number of nodes
    int* results          // Output canonical labeling
);
Parameters:
subgraph: A flattened adjacency matrix representing the graph.
subgraphSize: The number of nodes in the graph.
results: An array to store the canonical labeling of the graph.

Contributing
Contributions are welcome! To contribute:

Fork the Repository:

Click the "Fork" button at the top right of this page to create your own fork.

Clone Your Fork:

```bash

git clone https://github.com/mdindoost/NautyToChapel.git
cd NautyToChapel/NautyProject
Create a New Branch:

bash

git checkout -b feature/your-feature-name
Make Your Changes:

Implement your feature or bug fix.

Commit Your Changes:

```bash


git commit -m "Add feature: your feature description"
Push to Your Fork:

```bash


git push origin feature/your-feature-name
Submit a Pull Request:

Navigate to your fork on GitHub and click the "Compare & pull request" button.

License
This project is licensed under the MIT License.

