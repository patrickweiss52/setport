#IN ORDER TO GET 
setport\_CO3 to work the following needs to be done in the BASH Session:

1: Must set a bash alias if wanting to run program from anywhere in a
BASH Session -in the .bash\_aliases file add the following line of code,
save the file and restart BASH Session (this only needs to be done
once):
    ```
    alias setport='cd /"path_to_parentDirectory"/;./setport.cpp.o'
    ```
    *literal example from my environment:*
    ```
    alias setport='cd /home/ubuntu/workspace/setport_CO2/;./setport.cpp.o'
    ```
    -if desired, setport.cpp.o is not required; do the following
        -in the desired directory run the following 
        ```
        make setport
        ```
        -this will create an executable in the same directory called setport
            -then an alias can be created for that executable (the following line would be added to the .bash_aliases file
                ```
                alias setport='cd /"path_to_parentDirectory"/;./setport'
                ```   
                *literal example from my environment:*
                ```
                alias setport='cd /home/ubuntu/workspace/setport_CO2/;./setport'
                ```
2: Must set environmental variables (this must be done once per BASH
Session) -run the following commands:
    ```
    export MY_PORT=123
   
    export YOUR_PORT=789
    ```
    
    -this will set the MY\_PORT and YOUR\_PORT environmental variables
    -to check that this was done right the following commands can be run:
    ```
    printenv | grep MY_PORT
    
    printenv | grep YOUR_PORT
    ```
