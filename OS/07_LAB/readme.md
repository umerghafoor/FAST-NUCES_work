Task 1: Redirecting stderr to a File


In
this task, you will redirect the standard error (stderr)
to a file:


Open a
file for writing.
Use dup2() to duplicate the file descriptor of
the opened file and replace stderr's
file descriptor.
Write
an error message to stderr.
Close
the file.


Task 2: Redirection with fork()


Write
a program where a parent process creates a child process using fork().
The child process will:


Redirect its stdout to a file using dup2().
Execute a command like ls or date using execlp() to demonstrate that the output is redirected to the file.
The parent process should wait for the child to complete.



Expected
Output: The output of the ls or date command
executed by the child should be written to the file.