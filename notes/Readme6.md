Meme for grub/boot process for dual boot for Archlinux and Ubuntu.

Archlinux is close to upstream, it is good dependency check and no extra modification.
However, commerical software XMind or other software basially are targeting to Ubunut.

Since each opensources are parts or components, as computer system, Ubuntu has most users and de-fact configurations.
To minimize the impact of Ubuntu Installer (https://wiki.ubuntu.com/Ubiquity), I need to understand what Ubuntu/Debian patched Grub

You can search the patch files for Grub2 in https://launchpad.net/ubuntu/+source/grub2

1. First of all, Ubuntu/Debian had never accepted upstream 2.06, stop in 2.04
I still don't know the reason.

As of 20.10 Ubunut, there are 110 patches !!??? This proves that FSF/GNU actually doesn't accept patches from Canonical lol 

One of the most import patch is set default prefix folder in EFI directory in EFS partition.
Since, each vendor? (even Microsoft) makes their own folder. so ubuntu set default grub's prefix path to 'ubuntu' (of course), if you use Ubuntu's grub, you have to put the first grub.cfg in 'ubuntu'

2. In UEFI, EFS filesystem will be fat32(in default). You can put the kernal image and initramfs image in EFS. However. long long age, Debian(Ubuntu) decided that since linux or initramfs heavily depends on the kernel version, when the kernel version updates, they want to keep old versions also, so they will use the image file name with the version number. Then how we know which version is default, well they decided to use Symbolic Link. FAT32 never had Symbolic Link functions, the manner had never worked. so in the default, you cannot put kernel and initramfs image in EFS for Debian(Ubuntu)


So I ended up, I moved only grub (module) folder to EFS and manually made (EFS)/EFI/ubuntu diretory and put grub.cfg which Ubiquity generated. This one changes prefix to /boot/grub then indicate real grub.cfg which has boot entry and  then, replace upstream grubx64.efi to Ubunut's grubx64.efi

And then, mount /dev/sda1 /mnt/EFS , then mount --bind /mnt/EFS/grub /boot/grub


