#SETPORT INSTRUCTIONS

###Run make

1. Open terminal in the workspace
2. run: ```make setport```
3. run: ```make test```

*note: this will create to executables in the directory: setport and test; test is the 
automated program to run each line in tests.txt. More tests can be added to tests.txt,
however before ./test is run again after adding new tests, save tests.txt.

###Set a bash alias

For C9 *(this only needs to be done once; best to do this in a blank workspace)*:

1. Open a terminal in the workspace
2. run: ```cd ~```
3. run: ```ls -a```
4. double click on .bash_aliases
5. add the following line (entering your own directory path to "path\_to\_parentDirectory") 
  * ```alias setport='cd /"path_to_parentDirectory"/;./setport'```
6. save 
7. restart terminal
    
*literal example from my environment* ```alias setport='cd /home/ubuntu/workspace/setport/;./setport'```

*note: The workspace root directory is aliased to whatever the workspace is named in C9,
so if the workspace is named 'setport' then 'workspace/setport' wouldn't be needed like in
my example. However if the workspace is named 'CS_3370' and the program is run out of a subdirectory,
then it would be formatted like my example.*

###Set custom Environment Variables

Must be done once per BASH session:

1. run: ```export MY_PORT=123```
  * this will set the MY\_PORT environmental variable
  * to check that this was done right the following commands can be run:
  * ```printenv | grep MY_PORT```
  * Now commands like ```setport -p -e ``` or ```setport -p -e MY_PORT``` will work

2. Language variables:
3. run: ```export LANGUAGE=es``` or whatever language variable that needs to be set

###ENJOY!