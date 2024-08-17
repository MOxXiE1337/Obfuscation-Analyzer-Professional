# Obfuscation Analyzer Professional

## Project Description
This is a multi-module C++ project developed using Visual Studio, aimed at analyzing and handling code obfuscation.

This project employs a recursive disassembly algorithm, supports multi-threaded concurrent disassembly analysis, and includes emulation of instruction flow tracking.

**Note**: This project is only supported on x64 platforms. Please ensure that your development and runtime environments are both x64 architecture.

## Directory Structure

- **freetype**: Code and configurations related to font handling.
- **imgui**: Source code and examples of the ImGui library.
- **tinyxml2**: Library for handling XML files.
- **zydis**: Library for disassembling and analyzing machine code.
- **oacore**: Core library, including data processing, analyzers, tools, and the simulator.
- **oaui**: User interface module.

## Installation Steps

### Prerequisites
- Visual Studio 2022 or later
- C++ development tools

### Cloning and Setup

1. Clone the repository:
    ```bash
    git clone https://github.com/MOxXiE1337/Obfuscation-Analyzer-Professional.git
    cd Obfuscation-Analyzer-Professional
    ```

2. Open Visual Studio.
3. From Visual Studio, choose **"Open Project/Solution"**.
4. Navigate to the project directory, select the solution file (`.sln`), and click **"Open"**.

### Build and Run

1. In Visual Studio, select **x64** as the target platform.
2. Choose the appropriate configuration (e.g., **Debug** or **Release**).
3. Right-click on the solution in Solution Explorer and select **"Build Solution"**.

4. After the build completes, select **"Debug"** > **"Start Debugging"** or press **F5** to run the program.

### Output Directory

The built executable file will be located in the `out\x64` directory.

## Usage Instructions

### Starting the Application

1. Run the `Obfuscation Analyzer Professional.exe` file located in the `out\x64` directory.

### Loading PE Files

1. In the application, choose **File** -> **Open**.
2. Select and load a PE file (executable file) for analysis.

### Loading Database

1. In the application, choose **File** -> **Open**.
2. Select and load the generated database file to continue analysis.

### Loading Examples

We provide an example obfuscated PE file and an already generated database file (ExampleExecutable.exe and ExampleDatabase.odb).  
You can load these examples to learn how to use the application.

### Using the GUI

1. Interact with the interface provided by ImGui.
2. Perform the following actions via the GUI:
    - View analysis results.
    - Configure parameters.
    - Perform other user interactions.

## Contributing

We welcome contributions from the community! To contribute, please follow these steps:

1. Fork the repository.
2. Create a feature branch (`git checkout -b feature-branch`).
3. Commit your changes (`git commit -am 'Add new feature'`).
4. Push to the branch (`git push origin feature-branch`).
5. Submit a Pull Request.

## License

This project is licensed under the [MIT License](LICENSE). Please refer to the `LICENSE` file for more details.

## Contact

- **Author**: [MOxXiE1337]
- **Project Homepage**: [Obfuscation Analyzer Professional](https://github.com/MOxXiE1337/Obfuscation-Analyzer-Professional)

## Additional Information

For more information, please refer to the `README.md` files and related documentation in each module.
