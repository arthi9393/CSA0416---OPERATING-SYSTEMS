# TASK 09 – Evaluate the Memory Hierarchy and I/O Systems

## 1. Memory Hierarchy

A computer uses different storage levels to balance speed, capacity and cost.

| Level | Typical access time | Typical capacity |
|---|---|---|
| CPU Registers | Less than 1 ns | Bytes to KB |
| CPU Cache (L1/L2/L3) | About 1–20 ns | KB to tens of MB |
| Main Memory (RAM) | About 50–100 ns | GBs |
| SSD | About 50–500 µs | Hundreds of GB to TB |
| Hard Disk (HDD) | About 5–15 ms | TBs |
| Network Storage | About 1–100+ ms | GBs to PBs |

Access times are approximate and depend on hardware, workload and network conditions.

## 2. Storage Plan for the Hospital

| Data | Recommended storage | Reason |
|---|---|---|
| MRI images | SSD for active processing and secure network storage for long-term archiving | Large files need fast access and reliable storage |
| Patient records | Main memory cache for frequently accessed records, backed by SSD or secure database storage | Fast look-up with persistent storage |
| Monitor readings | RAM buffers for immediate processing and reliable database storage for history | Quick response and long-term records |

Important patient information must be backed up and protected with access controls and encryption.

## 3. I/O Methods

### Programmed I/O
The CPU repeatedly checks the device and transfers data itself. This is simple but wastes CPU time while waiting.

### Interrupt-driven I/O
The device interrupts the CPU when it needs attention or has data ready. This avoids continuous checking but can generate many interrupts for large transfers.

### Direct Memory Access (DMA)
DMA allows a device to transfer blocks of data directly between the device and main memory. The CPU configures the transfer and is notified when it completes.

### Recommended Methods

| Device | Suitable method | Reason |
|---|---|---|
| Patient monitor | Interrupt-driven I/O | Prompt notification of new readings |
| MRI scanner | DMA | Efficient transfer of large image data |
| Simple low-speed device | Programmed I/O | Suitable when transfers are small and infrequent |

## 4. Effect of Caching on Patient Record Look-up

Frequently accessed patient records can be cached in RAM. A cache hit avoids slower SSD or network access, reducing lookup time.

A cache miss requires fetching the data from the backing storage. Cache entries must be updated or invalidated when records change to avoid displaying outdated information.

## 5. Alternative: Interrupt-driven Transfer Instead of DMA

Assume an MRI image is 500 MB and each interrupt transfers one 4-byte word.

Using decimal units:

- Image size = 500 × 1,000,000 = 500,000,000 bytes
- Word size = 4 bytes
- Number of words = 500,000,000 ÷ 4
- **Number of interrupts = 125,000,000**

This would generate 125 million interrupts, creating significant CPU overhead.

If each interrupt required an illustrative 2 microseconds of CPU processing:

125,000,000 × 2 microseconds = 250 seconds of CPU time.

This is an example estimate, not a measured result. Actual interrupt-handling time depends on the hardware and operating system.

## 6. Buffer Requirements

- **Interrupt-driven I/O:** Requires buffers to temporarily hold incoming data while the CPU handles transfers. Frequent interrupts and buffer-management work increase overhead.
- **DMA:** Requires memory buffers for larger blocks or transfer regions. The DMA controller transfers data without requiring the CPU to handle every word individually.

DMA is more efficient for large MRI images because it reduces the number of CPU interruptions and allows the processor to perform other tasks.

## 7. Conclusion

The memory hierarchy provides a balance between speed and storage capacity. Frequently accessed patient records should use caching, monitor readings should be processed promptly, and MRI images should use DMA for efficient transfer. DMA is the most suitable method for large image transfers because it reduces CPU overhead compared with one interrupt per word.