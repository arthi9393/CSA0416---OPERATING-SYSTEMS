# TASK 10 – Measure and Compare

## 1. Aim
To measure system-call activity, CPU time, and the creation time of processes and threads on Linux.

## 2. System-call Measurements

Command used:

`strace -c ./copy_demo`

| System call | Number of calls |
|---|---:|
| read | 10,027 |
| write | 10,046 |
| openat | 9 |
| close | 9 |
| **Total** | **20,120** |

The copy program reported:

| Buffer size | read() calls |
|---|---:|
| 1 byte | 10,001 |
| 512 bytes | 21 |
| 4096 bytes | 4 |

Larger buffers reduce the number of read operations and improve system-call efficiency.

## 3. User and Kernel Time

Command used:

`/usr/bin/time -v ./copy_demo`

| Measurement | Result |
|---|---:|
| User time | 0.08 seconds |
| System time | 2.26 seconds |
| Elapsed time | 24.84 seconds |
| CPU usage | 9% |
| Maximum resident memory | 1,784 KB |

The system time was greater than user time, indicating that the program spent more CPU time in operating-system operations than in its own instructions. The elapsed time was much higher than CPU time, indicating that the process spent considerable time waiting or being descheduled.

## 4. Process and Thread Comparison

A C benchmark created and joined 1,000 child processes using `fork()` and 1,000 threads using `pthread_create()`.

Measured results:

| Test | Time |
|---|---:|
| 1,000 processes | 0.320569 seconds |
| 1,000 threads | 0.132836 seconds |

Threads completed faster in this experiment. They share the process address space and many resources, whereas separate processes have independent address spaces and require additional setup.

## 5. Alternative Concept and Complexity Analysis

If threads are created instead of processes, creation is generally faster because threads share code, data and other process resources. Each thread still has its own stack and execution state.

Processes provide stronger isolation but generally require more memory-management resources. Threads use less additional memory in many workloads, but an error in one thread can affect the entire process.

The measured times are specific to this WSL environment and are not universal performance values.

## 6. Evaluation

The measurements support the expectation that larger I/O buffers reduce system-call counts and that thread creation can be faster than process creation.

The copy-program measurements also show that system-call overhead can be significant. However, actual performance depends on the operating system, hardware, workload and storage environment.

## 7. Conclusion

The experiment demonstrated the impact of buffer size on system-call frequency and compared process and thread creation. Threads were faster in the measured test, while processes provide stronger memory isolation. These results help guide operating-system design decisions for the hospital system.