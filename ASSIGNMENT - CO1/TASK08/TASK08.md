# TASK 08 – Evaluate CPU States and Protection

## 1. User Mode and Kernel Mode

The CPU uses two operating modes to protect the hospital system.

- **User mode:** Normal applications, such as patient-record software and monitor dashboards, run with restricted privileges.
- **Kernel mode:** The operating-system kernel runs with full access to hardware and protected system resources.
- **Privileged instructions:** Operations such as disabling interrupts and controlling memory-management hardware are restricted to kernel mode.
- **Mode bit:** A hardware status bit indicates whether the CPU is executing in user mode or kernel mode.

When an application needs an operating-system service, it makes a system call. The CPU switches to kernel mode to perform the permitted operation and then returns to user mode.

## 2. Interrupts, Traps and Timer Interrupts

- **Interrupt:** A hardware signal that requests CPU attention, such as a signal from a monitoring device.
- **Trap:** A synchronous event caused by the currently executing instruction, such as a system call or an arithmetic exception.
- **Timer interrupt:** A periodic hardware signal that allows the operating system to regain CPU control and schedule another process.

These mechanisms help the hospital operating system respond to devices and share CPU time between applications.

## 3. Risk of Disabling Interrupts

If any application could disable interrupts, a faulty or malicious program could prevent the CPU from responding promptly to monitor-device signals.

This could delay abnormal-reading notifications, interrupt handling and operating-system scheduling. Therefore, disabling interrupts must be restricted to trusted kernel code.

## 4. Memory Protection

The Memory Management Unit (MMU) uses page tables and access permissions to control which memory regions a process can access.

Each process receives its own protected virtual address space. If one program tries to access another program's restricted memory, the hardware raises a protection fault. The operating system can then stop the invalid access.

This protects patient records and prevents one application from reading another application's data without permission.

## 5. Alternative: Polling Instead of Interrupts

With polling, the CPU repeatedly checks the sensor at a fixed interval instead of waiting for an interrupt.

For example, if a monitor checks every 100 milliseconds, an abnormal reading may wait almost 100 milliseconds before being noticed, excluding processing time.

With interrupt-driven monitoring, the device signals the CPU when attention is needed. The response is generally faster because the CPU does not need to wait for the next polling cycle.

### Evaluation

| Factor | Polling | Interrupt-driven |
|---|---|---|
| Detection delay | Up to the polling interval | Usually interrupt latency plus processing time |
| CPU usage | Repeated checks consume CPU time | CPU can perform other work between interrupts |
| Power usage | Can be higher due to repeated checking | Usually more power-efficient |
| Suitability | Useful for simple, periodic checks | Better for prompt abnormal-reading notifications |

Polling can be acceptable for non-urgent periodic measurements, but interrupt-driven operation is more suitable for hospital monitors that must report abnormal readings promptly.

## 6. Conclusion

CPU modes, privileged instructions, interrupts, timer interrupts and MMU-based memory protection help protect the hospital system. User applications cannot directly control critical hardware or access another process's protected memory. Interrupt-driven monitoring is preferable to continuous polling when timely response to abnormal readings is important.