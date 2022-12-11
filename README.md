Help script for creating a backup with raspiBackup, as well as restoring a backup created with raspiBackup in a simple, dialog-guided way.

Prerequisite is an installation of raspiBackup
https://www.linux-tips-and-tricks.de/en/raspberry/303-pi-creates-automatic-backups-of-itself

https://github.com/framps/raspiBackup/blob/master/helper/raspiBackupDialog.sh

It can simply be started without any options.
Then you will be asked if you want to create a backup or restore an existing backup. 

# Possible options

 --last (The last backup will be selected automatically)
 
 --select (the backup can be selected from a list)
 
 --backup (a dialog for creating a backup is started)
 
 --delete (A Backup to delete can be selected from a list)    (update from 07/2022)

# Updated on 27.03.22
- Language German added.
  At program start you can choose between 
  German and English can be selected.

 
# Update 2022_07_26
 Added a function to mount and unmount the Backup-directory optional with mount-unit or fstab-entry (dynamic mount)
 
 --mountfs "Name of the mount-unit or fstab"
 
Example:

sudo raspiBackupRestoreHelper.sh --mountfs "backup.mount"

or 

sudo raspiBackupRestoreHelper.sh --mountfs "fstab"

These two Options must be set as first and second. Behind it is possible to set another option like --select or --last


 In case of an automatic backup via crontab, you have to add the option
--cron at the end, so that there is no dialogue and the defaults from the 
from the raspiBackup.conf are used.

Example:
* * * * * /raspiBackupRestoreHelper.sh --mountfs "fstab" --cron   (no further dialog guided option possible)


  
