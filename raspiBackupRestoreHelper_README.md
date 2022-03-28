Auxiliary script to restore a backup created by raspiBackup in a simple dialog-guided way.

Requirement is an installation of raspiBackup
https://www.linux-tips-and-tricks.de/en/raspberry/303-pi-creates-automatic-backups-of-itself/

It can simply be started without options.
Then a query appears if the last backup should be restored. (y/N)
If (N) an appropriate backup can be selected from a list. 
Then select the target medium and raspiBackup does the rest.

Possible Options --last or --select

If Option --last (the last backup is automatically selected)

If Option --select  (the desired backup can be selected from a list)


Update on 27.03.22
- Language German added.
  At program start you can choose between 
  German and English can be selected.

Update on 28.03.22

- Function backup added
   Available options

--last (last backup will be restored.)
--select ( Backup can be selected from a list)

--backup (a backup will be created)   
 - Selection options in the process (only the 2 default partitions,
 - ignore additional partitions, 
 - selection which additional partitions should be backed up as well.

without option 
(It is asked whether a backup should be created or restored. 
If backup is selected. (Procedure as for --backup)
If restore is selected, (query if "last backup" should be restored).

The procedures do not differ from the options "--last" and "--select".

