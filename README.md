IN ORDER TO GET setport\_CO3 to work the following needs to be done in the BASH Session:

1: Must set a bash alias if wanting to run program from anywhere in a
BASH Session -in the .bash\_aliases file add the following line of code,
save the file and restart BASH Session (this only needs to be done
once):

To get to this in C9 do the following
    1: Open a terminal in the workspace
    2: run: ```cd ~```
    3. run: ```ls -a```
    4. double click on .bash_aliases
    5. add the following line (entering your own directory path to "path\_to\_parentDirectory):
        ```alias setport='cd /"path_to_parentDirectory"/;./setport.cpp.o'```
    6. save 
    7. restart terminal
    
    *literal example from my environment:* ```alias setport='cd /home/ubuntu/workspace/setport_CO2/;./setport.cpp.o'```

If desired, setport.cpp.o is not required; do the following in the desired directory: run the following 
    1:run: ```make setport```
        *this will create an executable in the same directory called setport*
        *then an alias can be created for that executable*
    2. do steps 1-4 from above
    3. add the following line (entering your own directory path to "path\_to\_parentDirectory): 
     ``` alias setport='cd /"path_to_parentDirectory"/;./setport' ``` 
    4. save
    5. restart terminal
    
    *literal example from my environment:*  ```alias setport='cd /home/ubuntu/workspace/setport_CO2/;./setport'```


    
2: Must set environmental variables (this must be done once per BASH Session) -run the following commands:
    1. run: ```export MY_PORT=123```
    2. run: ```export YOUR_PORT=789```
    -this will set the MY\_PORT and YOUR\_PORT environmental variables
    -to check that this was done right the following commands can be run:
    ```printenv | grep MY_PORT```
    ```printenv | grep YOUR_PORT```
