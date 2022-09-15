# Barvinn Setup Document

## Description

This document contains a simple guide for setting up, simulating, and running [BARVINN](https://github.com/schegde/BARVINN)


BARVINN is a Barrel RISC-V Neural Network Accelerator. The main purpose of designing BARVINN was to fill the need for arbitrary precision neural network acceleration. The 
overall architecture of BARVINN is illustrated below: BARVINN is an FPGA-proven accelerator. The above figure illustrates the overall system design for BARVINN. It is consist of the following components:
   - Array of Matrix Vector Units
   - RISC-V Controller Core
   - Host Machine

## Getting Started

### Install Vivado 2019.1 
Install Xilinx Vivado 2019.1 WebPack (free version) from Xilinx archives. This is needed for running the sim, and generate some memory IPs.

### Installing Conda Environment for Windows

Go to the official [Conda](https://docs.conda.io/en/latest/miniconda.html) website and download the appropriate conda (miniconda) for your system. After installation, open the mini conda terminal and create an environment by entering `conda create --name myenv` 


After the conda environment is created, activate the environment by entering `conda activate myenv` and install fusesoc by runing the following command `python3 -m pip install fusesoc` once fusesoc and python are installed, open vscode through the conda terminal by entering `code .`

### Cloning Barvinn

Clone the barvinn repository on your local pc and update the submodules by entering `git clone https://github.com/schegde/BARVINN.git` > `cd BARVINN` > `git submodule update --init`

Next, setup Xilinx tools by executing the BAT script :`C:\Xilinx\Vivado\2019.1\settings64.bat`

Add mvu, pito and barvinn to your fusesoc libraries using the following commands:

```
cd deps/MVU
fusesoc library add mvu .
cd ../pito_riscv
fusesoc library add pito .
cd ../../
fusesoc library add barvinn .
```
Run the command `vivado -mode batch -nolog -nojournal -source gen_xilinx_ip.tcl` in the `deps/MVU/tclscripts/` directory to generate the Xilinx IPs for simulation.

Run the following command `fusesoc run --target=sim barvinn` in the barvinn root directory to generate simulation build directories.
This command will error out due to parameter defination issue on *windows pc*

In order to fix the error, update `VLOG_DEFINES  = --define XILINX=1` to `VLOG_DEFINES  = --define XILINX` in `config.mk` file present in `BARVINN\build\barvinn_0\sim-xsim\config.mk` 

Now run the simulation by first changing the directory to `BARVINN\build\barvinn_0\sim-xsim` and then entering `make run-gui` in the terminal. This should start Vivado for simulation.

To run the simulation you would need 4 files:

  - RISC-V Instruction Firmware file
  - RISC-V Data mem file
  - Input hex for Convolution
  - Weight hex for Convolution

The local paths for these files are hardcoded in different places within the BARVINN repository. Check commits for more details 

---
