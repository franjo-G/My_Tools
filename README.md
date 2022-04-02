Help script for creating a backup with raspiBackup, as well as restoring a backup created with raspiBackup in a simple, dialog-guided way.

Prerequisite is an installation of raspiBackup
https://www.linux-tips-and-tricks.de/en/raspberry/303-pi-creates-automatic-backups-of-itself

It can simply be started without any options.
Then you will be asked if you want to create a backup or restore an existing backup. 

Possible options

 --last (The last backup will be selected automatically)
 
 --select (the backup can be selected from a list)
If option --last (the last backup is selected automatically)
--backup (a dialog for creating a backup is started)


Updated on 27.03.22
- Language German added.
  At program start you can choose between 
  German and English can be selected.


Updated on 28.03.22
- Backup function added
  
---backup (a backup will be created)   
 - Selection options in the process 
 - only the 2 default partitions,
 - ignore additional partitions, 
 - selection which additional partitions 
    should be backed up.

without option 
(It is asked whether a backup should be created or restored. 
If backup is selected. (Proceed as for --backup)
If restore is selected (Asking if "last backup" should be restored).

The procedures do not differ from the options "--last" ,"--select" and --backup.


