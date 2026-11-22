cat > Task05.md <<'EOF'
# TASK 05 – System Calls

## 1. Introduction

A system call is an interface through which a user application requests a service from the operating-system kernel. System calls allow programs to access protected resources such as files, devices and processes.

## 2. Categories of System Calls

| Category | Purpose | Examples |
|---|---|---|
| Process control | Creates and manages processes | fork(), exec(), wait(), exit() |
| File management | Creates, reads and writes files | open(), read(), write(), close() |
| Device management | Accesses and controls devices | ioctl(), read(), write() |
| Information maintenance | Gets system and process information | getpid(), time(), uname() |
| Communication | Exchanges information between processes | pipe(), socket(), send(), recv() |
| Protection | Controls permissions and access | chmod(), chown(), access() |

## 3. Steps Involved in read()

When a C program calls read(), the following operations occur:

1. The application calls the read() library interface.
2. The system-call interface requests the kernel service.
3. The processor switches from user mode to kernel mode.
4. The kernel checks the file descriptor and validates the requested operation.
5. The kernel obtains available data and transfers it to the user buffer.
6. The kernel returns the number of bytes read or an error.
7. Execution returns to user mode.

## 4. System-Call Parameter Passing

System-call parameters can be passed using:

- Registers: Parameters are placed in processor registers.
- Memory block: Parameters are stored in a memory block and its address is passed.
- Stack: Parameters are placed on the program stack.

The exact method depends on the processor architecture and operating-system system-call convention.

## 5. Practical C Program

The program syscall_demo.c opens input.txt, reads its contents using read(), displays the data and closes the file.

Compilation:

gcc -std=c11 -Wall -Wextra syscall_demo.c -o syscall_demo

Execution:

./syscall_demo

## 6. strace Evidence

The program is traced using:

strace -e trace=openat,read,close ./syscall_demo

The trace shows file-opening, reading and closing system calls. The trace may also include calls made by the C runtime and dynamic loader.

Actual command output is saved in strace_output.txt.

## 7. Alternative: C Library File Operations vs Direct System Calls

### C Library Functions

fopen(), fread() and fwrite() provide buffered file operations. The library can collect data in a buffer and reduce the number of kernel system calls.

### Direct System Calls

open(), read() and write() provide direct access to kernel file operations. The application controls when data is requested or written.

| Factor | C Library Functions | Direct System Calls |
|---|---|---|
| Interface | Higher-level | Lower-level |
| Buffering | Usually provides buffering | Application manages buffering |
| Control | Simpler | More control |
| System-call frequency | Can be reduced by buffering | Depends on application buffer size |
| Complexity | Easier to use | Requires more error handling |

For a file of n bytes and a buffer of b bytes, an application may need approximately ceil(n/b) read operations, excluding extra calls and end-of-file handling.

## 8. Conclusion

System calls provide a controlled interface between user applications and the operating-system kernel. The read() experiment and strace output demonstrate how a user program requests file access from Linux. Buffered library functions can reduce system-call frequency and improve efficiency.
EOF