## Keeping a Radeon GPU busy

This code launches 2,560 wavefronts of 64 threads each, i.e., the maximum number of wavefronts for a Fiji (tune
the code for other Radeon GPUs). Each thread does n iterations of 1000 consecutive fused multiply-add instructions.
Current running time is about three minutes on a Radeon R9 Nano; tune the number of iterations for a different
running time, or for different hardware.

### Usage

#### Compiling
```shell
make
```

#### Running
```shell
./fiji_workout
```

#### Dump GPU ISA
```shell
make isa
```

### Prerequisites
This code assumes a Linux (Ubuntu) system with the ROCm stack installed. For full ROCm installation
instructions, see [ROCm](https://raw.githubusercontent.com/RadeonOpenCompute/ROCm/master/README.md).

#### Quick start (copied from the full instructions):
##### Add the ROCm apt repository
For Debian based systems, like Ubuntu, configure the Debian ROCm repository as
follows:

```shell
wget -qO - http://packages.amd.com/rocm/apt/debian/rocm.gpg.key | sudo apt-key add -
sudo sh -c 'echo deb [arch=amd64] http://packages.amd.com/rocm/apt/debian/ xenial main > /etc/apt/sources.list.d/rocm.list'
```
The gpg key might change, so it may need to be updated when installing a new 
release.

##### Install or Update
Next, update the apt-get repository list and install/update the rocm package:

>**Warning**: Before proceeding, make sure to completely
>[uninstall any previous ROCm package](https://github.com/RadeonOpenCompute/ROCm#removing-pre-release-packages):

```shell
sudo apt-get update
sudo apt-get install rocm
```
Then, make the ROCm kernel your default kernel. If using grub2 as your
bootloader, you can edit the `GRUB_DEFAULT` variable in the following file:

```shell
sudo vi /etc/default/grub
sudo update-grub
```

Once complete, reboot your system.
