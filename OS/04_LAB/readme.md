## Task 1: Forking
### Processes to Manage Concurrent Tasks

You are tasked with building a multi-process task manager for a company's server
that handles multiple concurrent jobs. Each job represents a task that needs to
be completed, and you want to manage them using separate processes. Your task
manager should:

- Launch multiple jobs (each as a separate process) to simulate real-world tasks.

- Ensure that
the main server process (the parent) waits for each task to
finish before reporting the results.

- Each job should be
assigned a unique ID (based on the process’s position in the
task queue) and complete its work (simulated by printing a message).

- After all jobs are
done, the server should print a message indicating that all tasks are complete along
with the list of all the values of mods given by the jobs.

You decide to
implement this using the `fork()` system call to create child processes
for each job, and `wait()` to synchronize the completion of
tasks. Each child process will terminate with an exit code representing the
task it completed.

## Task 2: Basic Usage of `execvp()`


Write a C
program that creates a child process using `fork()`. In the child process,
replace the current process image with a new program using the `execvp()`
system call. The new program should be a simple script that should “ls” or
“date”. In the parent process, print a message indicating that the parent is
waiting for the child to complete.

## Task 3: Passing Arguments with `execve()`

Write a C
program that uses `fork()` to create a child process. In the child process, use
`execve()` to replace the current process with the `/bin/echo` program, passing
a custom message as an argument (e.g., `echo "Hello, from execve!"`).
The parent process should wait for the child to complete before exiting.