The goal of this project allows me to become familiar with compiling and installing a new kernel an  adding new system calls to the Linux operating systems. This was kernel was using the linux 5.8 kernel on a 64 bit Fedora 32 system.

This system call will allow a program in user-mode to get detailed information about a certain process such as parent ID, process state, priority, etc. 




* Compiling and Installing the kernel 
	> cd code/kernel-code/linux-5.8

* To build the kernel
	> make O=../build 
	> cd ../build 

* Install the new kernel
	> make modules_install install 

* Reboot machine 
	> reboot 
	
