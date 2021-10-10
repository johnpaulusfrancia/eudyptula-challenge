# Steps I used to build and install a custom kernel
I mostly followed along with this tutorial: https://www.freecodecamp.org/news/building-and-installing-the-latest-linux-kernel-from-source-6d8df5345980/

### Note: all of the following commands, except for `git clone`, were executed from the kernel source root directory
1. Clone the kernel tree: `git clone git://git.kernel.org/pub/scm/linux/kernel/git/stable/linux-stable.git`
2. Install some dependencies:
    * `sudo apt-get install git fakeroot build-essential ncurses-dev xz-utils libssl-dev bc`
    * `sudo apt-get install libncurses-dev gawk flex bison openssl libssl-dev dkms libelf-dev libudev-dev libpci-dev libiberty-dev autoconf`
3. Copy the current config file: `cp /boot/config-$(uname -r) .config`   
4. To update `.comfig` with the appropriate values, execute `make localmodconfig` and then hold down `Enter` to accept all of the default options. (I believe that `localmodconfig` creates a config file based on the modules that are currently installed on the machine; i.e., those that are returned by `lsmod`)
5. Open .config and manually changed the value of `CONFIG_LOCALVERSION_AUTO` from `is not set` to `=y` and from `CONFIG_FRAME_WARN=1024` to `CONFIG_FRAME_WARN=2048`

6. Build the kernel with `make -j 4 ARCH=X86_64`. `j -4` specifies the number of cores to use in the build and `ARCH=X86_64` specifies the architecture that the kernel will be run on.

7. Installed modules with `sudo make modules_install`
8. Copy the new kernel to `/boot` with `sudo make install`

9. Make the newly build kernel available for selection in the boot-loader by executing ` sudo update-initramfs -c -k all` and `sudo update-grub`.

10. Restart your computer and select new kernel while booting

## Steps to verify that my machine booted with the newly build kernel

1. Execute `uname -r` to get the name of the current kernel
2. Execute `make prepare && ./scripts/setlocalversion` to get the version of your local source tree
3. Verify that the output of (1) and (2) match

### This is the output when I executed the verification commands on my machine

<font color="#8AE234"><b>john@john-HP-Pavilion-Notebook</b></font>:<font color="#729FCF"><b>\~/Documents/linux-git</b></font>$ make prepare\
  CALL    scripts/checksyscalls.sh \
  CALL    scripts/atomic/check-atomics.sh\
  DESCEND objtool\
<font color="#8AE234"><b>john@john-HP-Pavilion-Notebook</b></font>:<font color="#729FCF"><b>~/Documents/linux-git</b></font>$ ./scripts/setlocalversion  
-00015-g60a9483534ed
