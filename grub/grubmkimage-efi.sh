grub-mkimage -O x86_64-efi   -o grub.efi -p "" part_gpt part_msdos  fat ext2 normal boot configfile linux linuxefi multiboot