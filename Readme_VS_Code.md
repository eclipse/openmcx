# Getting Started in Visual Studio Code

The OpenMCx-repository provides an easy way to get the project
compiling and running from within Visual Studio Code.
The `devcontainer.json` configuration file tells Visual Studio Code
how to provide a development environment with everything that is
needed to build and debug OpenMCx.

Follow these steps to make use of the development container:

- Load the OpenMCx repository into Visual Studio Code:

  - Open folder where you cloned the repository

  - Reopen in development container

    Visual Studio Code will recognize the `devcontainer.json` and
    offer to **Reopen in Dev Container** in a small window at the bottom
    right of Visual Studio Code.

  - When Visual Studio Code asks you to **Select a Kit for openmcx**,
    choose `GCC 9.3.0 x86_64-linux-gnu`.

- Build OpenMCx

  Run the following command from the Command Palette (`Ctrl+Shift+P`):

  > **CMake: Build**

- Run OpenMCx using the sample Launch configuration

  The folder `.vscode.sample` contains a sample `launch.json` which
  tells VS Code how to run and debug OpenMC.x

  - Copy `.vscode.sample` to `.vscode`

    The sample configuration is set up to start the currently opened
    file with OpenMCx, but you can adapt and modify the launch
    configuration to your needs.

  - Start OpenMCx with a `model.ssd`

    Open a `model.ssd` file and run **debug (gdb) Launch openmcx** from the Command
    Palette. This starts `openmcx` in the parent folder of the opened
    `model.ssd` file. The `simulation.log` and the `results` folder will
    be written to the parent folder as well.

- Optionally: Install helpful extensions

  - [joaompinto.vscode-graphviz](https://marketplace.visualstudio.com/items?itemName=joaompinto.vscode-graphviz)
    for opening `.dot` files containing the graph of the model that is
    generated when adding `-g` to the command line arguments
  - [randomfractalsinc.vscode-data-preview](https://marketplace.visualstudio.com/items?itemName=RandomFractalsInc.vscode-data-preview)
    for opening and plotting result `.csv` files
