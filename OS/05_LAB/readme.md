# Lab 05: Inter Process Communication

## Task 1:
The parent process is a task manager requesting the child to check whether the string sent is
a palindrome or not. The parent sends a task request (e.g., &quot;Rotator&quot;) to the child through
one pipe. Once the task is completed, the child responds with a status update (e.g., &quot;Yes
Palindrome&quot;) through another pipe, acknowledging the completion of the task. Then the
parent will then read that message and print that “ Task Manager is exiting now”.
### Example:
Parent sends: &quot;Rotator&quot;
Child replies: &quot;Yes Palindrome&quot;
Parent :” Task Manager exiting now.”

## Task2:
The parent process is a client requesting a mathematical operation (e.g., &quot;Multiply 3 by 4&quot;)
to the child process, which acts as a calculator. The child receives the operation, performs
the calculation, and sends the result back to the parent. Parent will check whether the
answer is correct or not. If the answer is correct Parent will print “Correct Answer” else it
will print “Incorrect Answer”.
### Example:
Parent sends: &quot;Multiply 3 by 4&quot;
Child calculates 3 * 4 and replies: &quot;Result: 12&quot;
Parent: “Correct Answer”