#SETPORT INSTRUCTIONS

###Set a bash alias

For C9 *(this only needs to be done once)*:

1. Open a terminal in the workspace
2. run: ```cd ~```
3. run: ```ls -a```
4. double click on .bash_aliases
5. add the following line (entering your own directory path to "path\_to\_parentDirectory") 
  * ```alias setport='cd /"path_to_parentDirectory"/;./setport.cpp.o'```
6. save 
7. restart terminal
    
*literal example from my environment* ```alias setport='cd /home/ubuntu/workspace/setport/;./setport.cpp.o'```

*note: The workspace root directory is aliased to whatever the workspace is named in C9,
so if the workspace is named 'setport' then 'workspace/setport' wouldn't be needed like in
my example. However if the workspace is named 'CS_3370' and the program is run out of a subdirectory,
then it would be formatted like my example.*



Alternitavely, one can create an executable that isn't an object file
(ex: a file called setport will exist versus setport.cpp.o):

1. run in the directory containing setport.cpp: ```make setport```
  * this will create an executable in the same directory called setport
  * then an alias can be created for that executable
2. do steps 1-4 from above
3. add the following line (entering your own directory path to "path\_to\_parentDirectory): 
  * ```alias setport='cd /"path_to_parentDirectory"/;./setport'``` 
4. save
5. restart terminal
    
*literal example from my environment:*  ```alias setport='cd /home/ubuntu/workspace/setport/;./setport'```

###Set custom Environment Variables
Must be done once per BASH session:

1. run: ```export MY_PORT=123```
  * this will set the MY\_PORT environmental variable
  * to check that this was done right the following commands can be run:
  * ```printenv | grep MY_PORT```
  * Now commands like ```setport -p -e ``` or ```setport -p -e MY_PORT``` will work


###ENJOY!