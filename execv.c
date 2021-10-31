void main() {
    if (fork() == 0) { /* Child process */
        char *newargs[4];
        printf(“Hello, I am the child process.\n”);
        newargs[0] = “/bin/ls”;
        newargs[1] = “-l”;
        newargs[2] = “/usr/include”; 
        newargs[3] = NULL; /* Indicate end of args array */
        if (execv(“/bin/ls”, newargs)) {
            printf(“warning: execv returned an error.\n”);
        exit(-1);
        }
    }
}
