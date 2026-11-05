# TASK 06 – Evaluate the Cost of System Calls

## 1. Introduction

System calls provide an interface between user programs and the operating-system kernel. They allow applications to request services such as file reading, writing, opening and closing.

Examples include `read()`, `write()`, `open()` and `close()`.

System calls have additional overhead compared with ordinary function calls because they involve switching from user mode to kernel mode.

## 2. Why System Calls Are More Expensive

An ordinary function call generally executes within the same process and execution mode.

A system call requires additional steps:

1. The application requests an operating-system service.
2. The processor transfers control to the kernel.
3. The processor switches from user mode to kernel mode.
4. The kernel checks the request and performs the operation.
5. The result is returned to the application.
6. Execution continues in user mode.

These additional operations introduce system-call overhead.

## 3. Effect of Buffer Size on System Calls

In this experiment, a C program copies a 10,000-byte file using three different buffer sizes.

The program counts the number of `read()` calls required for each buffer size.

### Experimental results

| Buffer size | Number of read() calls |
|---|---:|
| 1 byte | 10001 |
| 512 bytes | 21 |
| 4096 bytes | 4 |

The results show that a smaller buffer requires more system calls, while a larger buffer reduces the number of calls.

The final read operation returns zero to indicate the end of the file.

## 4. System Call Measurement Using strace

The `strace` command is used to observe system calls made by a Linux program.

Command used:

```bash
strace -c -e trace=read,write ./copy_demo
```

This command displays a summary of read and write system calls, including their counts and execution time.

The `strace` summary can include additional calls made during program startup, so its total may differ from the read-call count printed by the C program.

## 5. Library Buffering

C library functions such as `fread()` and `fwrite()` provide buffering.

Instead of making a system call for every small data operation, the library collects data in a buffer and performs larger operations.

For a file containing n bytes and a buffer size of b bytes, the approximate number of read operations is:

**Number of calls ≈ n / b**

Buffering reduces system-call overhead and improves file-processing efficiency.

## 6. Time and Space Complexity

For copying a file containing n bytes:

- **Time complexity:** O(n), because each byte must be processed.
- **Additional buffer space:** O(b), where b is the buffer size.

A larger buffer reduces the number of system calls but uses more memory.

## 7. Alternative Concept – Memory-Mapped Files

An alternative method is memory-mapped file access using `mmap()`.

Memory mapping allows a file to be accessed through virtual memory rather than repeatedly using explicit `read()` and `write()` operations.

| Factor | Buffered read/write | Memory mapping |
|---|---|---|
| Data access | Explicit read and write | Access through mapped memory |
| System calls | Repeated read/write calls | Mapping and memory-management operations |
| Memory usage | Depends on buffer size | Depends on mapped region |
| Large files | Can process in smaller chunks | Can map sections of a file |

Memory mapping can be useful for certain large-file workloads, but it requires careful management of mapped memory.

## 8. Application to the Smart Hospital

The hospital database and MRI backup systems may process large amounts of data.

Using suitable buffer sizes can reduce unnecessary system calls during backup operations.

However, the buffer size must be selected by considering:

- Available memory
- File size
- System-call overhead
- Measured execution time
- Reliability of backup operations

A suitable buffer can improve performance without using excessive memory.

## 9. Conclusion

This experiment demonstrates that system calls introduce additional overhead because they require transitions between user mode and kernel mode.

The experiment shows that increasing the buffer size from 1 byte to 4096 bytes reduces the number of read calls from 10001 to 4.

Therefore, buffering is an effective method for reducing system-call overhead during file-copying and backup operations.

The best buffer size should be selected using actual performance measurements and available system memory.