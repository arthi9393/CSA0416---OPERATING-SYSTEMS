# TASK 07 – Evaluate Process Control System Calls

## 1. Aim
To study and evaluate Linux process-control system calls: `fork()`, `exec()`, `waitpid()`, and process termination using `exit()`.

## 2. System Calls

- **fork():** Creates a child process by duplicating the calling process.
- **exec():** Replaces the current process image with a new program. In this experiment, `execlp()` executes the `expr` command.
- **waitpid():** Allows the parent process to wait for a particular child process to finish and collect its status.
- **exit():** Terminates a process and flushes standard I/O streams.
- **_exit():** Terminates a process immediately without flushing standard I/O streams.

## 3. Program Description
The program creates two child processes.

- Job 1 uses `fork()` and `execlp()` to execute `expr 6 * 7`. The result is `42`, and the parent collects the child's exit status using `waitpid()`.
- Job 2 uses `fork()` to create another child. The child terminates with status `3`, and the parent collects that status using `waitpid()`.

## 4. Normal Execution Output

```text
shell: running job 1
42
job 1 exit status 0
shell: running job 2
job 2 exit status 3
```

The output confirms that the first child executed successfully and the second child returned exit status 3.

## 5. Output Buffering Experiment

The second `fflush(stdout)` was removed and `_exit(3)` was changed to `exit(3)`. The output was redirected to a file.

The line `job 1 exit status 0` and the line `shell: running job 2` appeared twice.

### Explanation
When output is redirected to a file, standard output is normally fully buffered. The second `fork()` copies the parent's buffered output into the child process. When the child calls `exit(3)`, it flushes its copy of the buffer. The parent later flushes its own copy. Therefore, the buffered lines appear twice.

Using `_exit(3)` avoids flushing the child's copied standard I/O buffer.

## 6. Zombie and Orphan Processes

- **Zombie process:** A child process that has terminated but whose exit status has not yet been collected by its parent.
- **Orphan process:** A child process whose parent terminates before it does. The child is then adopted by a system process.

Using `waitpid()` helps the parent collect the child's termination status and prevents an unreaped child from remaining a zombie.

## 7. Why Use fork() and exec()?

Separating process creation (`fork()`) from program replacement (`exec()`) gives a shell flexibility. It can configure a child process before executing another program, for example by setting up input/output redirection or pipes.

## 8. Alternative Approaches

`posix_spawn()` combines process creation and program execution in a convenient interface. It can be more efficient for launching programs in some environments.

Threads are another alternative for concurrent work, but threads share the same process address space. Separate processes provide stronger memory isolation.

## 9. Conclusion

The experiment demonstrated how Linux creates processes, executes programs, waits for child processes, and collects exit statuses. It also showed how buffered output can be duplicated when `fork()` is followed by `exit()` without flushing the output first.