param([string]$vmName, [string]$action, [string]$floppy)

$argumentError = 0
$vmName="DOS"
# $action="vfd"
$floppy="D:\DRIVERS.vfd"


# Check for correct command-line arguments
If ($vmName -eq "")
 {$argumentError = 1}

If ($action -eq "")
 {$argumentError = 1}

If ($floppy -eq "")
 {
  if ((!([string]::Compare($action, "vfd", $True))) -or (!([string]::Compare($action, "physical", $True))))
  {$argumentError = 1}
 }

# Display usage information if wrong arguments are provided
If ($argumentError -eq 1)
 {
 write-host "Missing command-line argument."
 write-host "USage: FloppyDrive.ps1 -vmName `"Name of virtual machine`""
 write-host "                       -action info       - to display information about the current floppy configuration"
 write-host "                               disconnect - to disconnect any attached floppy disk or floppy disk image"
 write-host "                               vfd        - to attach a virtual floppy disk image"
 write-host "                               physical   - to attach a physical floppy disk"
 write-host "                               create     - to create a virtual floppy disk image"
 write-host
 write-host "                       -floppy name       - where name is either the full name and path for a virtual"
 write-host "                                            floppy disk or the letter of a physical disk to attach"
 exit
 }

# Connect to Virtual PC
$vpc=new-object -comobject VirtualPC.Application -strict

# Get virtual machine object
$vm = $vpc.FindVirtualMachine($vmName)

# Get the floppy drive
$vmFloppyDrive = $vm.FloppyDrives.item(1)

# Perform the specified action
switch ($action) 
   {

   # Display floppy disk information
   "info" {
      write-host "Floppy disk information"
      write-host "======================="

      # Different information is needed for each attachment type
      switch ($vmFloppyDrive.Attachment)
        {
        0 {
           write-host "Floppy Attachment : No floppy disk attached"
           write-host "Drive Number      : " $vmFloppyDrive.DriveNumber}
        1 { 
           write-host "Floppy Attachment : Floppy disk image attached"
           write-host "Drive Number      : " $vmFloppyDrive.DriveNumber
           write-host "Image File        : " $vmFloppyDrive.ImageFile }
        2 { 
           write-host "Floppy Attachment : Physical floppy disk attached"
           write-host "Drive Number      : " $vmFloppyDrive.DriveNumber
           write-host "Host Drive Letter : " $vmFloppyDrive.HostDriveLetter }
        }
      }

   # Disconnect the current floppy disk
   "disconnect" {

      write-host "Disconnecting the floppy disk."

      # A different method is used to disconnect a floppy disk image than for a physical disk 
      switch ($vmFloppyDrive.Attachment)
         {
         1 {$vmFloppyDrive.ReleaseImage()}
         2 {$vmFloppyDrive.ReleaseHostDrive()}
         }
      }

   # Attach a floppy disk image
   "vfd" {
      write-host "Attaching " $floppy " to the floppy drive."
      $vmFloppyDrive.AttachImage($floppy)
      }
      
   # Attach a physical floppy disk
   "physical"  {
      write-host "Attaching physical disk " $floppy ": to the floppy drive."
      $vmFloppyDrive.AttachHostDrive($floppy)
      }
   "create" {
      $vpc.CreateFloppyDiskImage($floppy, 2)
      $vmFloppyDrive.AttachImage($floppy)
      }
      
   # Catch invalid actions
   default {write-host "Invalid action provided. Info, disconnect, vfd and physical are valid options."}
   }