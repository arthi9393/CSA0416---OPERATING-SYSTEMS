cd "/workspaces/CSA0416---OPERATING-SYSTEMS/ASSIGNMENT - CO1"

cat > TASK04/Task04.md <<'EOF'
# TASK 04 – Evaluation of Operating-System Services

## 1. Introduction

An operating system provides services that help users and application programs interact with computer hardware. A smart hospital requires different OS services for bedside monitors, nurses' tablets, doctors' workstations, database servers and MRI imaging systems.

## 2. Important Operating-System Services

| OS Service | Purpose | Hospital Application |
|---|---|---|
| User Interface | Provides interaction between users and the system | Doctors' workstations and nurses' tablets |
| Program Execution | Loads and runs application programs | Patient monitoring and medical applications |
| I/O Operations | Controls input and output devices | Patient sensors, printers and MRI equipment |
| File-System Management | Creates, reads, writes and organizes files | Patient records and medical images |
| Communication | Allows processes and computers to exchange information | Sharing records between hospitals |
| Error Detection | Detects hardware and software errors | Detecting sensor, storage and network failures |
| Resource Allocation | Allocates CPU, memory and devices | Managing MRI processing and database workloads |
| Accounting | Tracks resource usage | Monitoring CPU, storage and network usage |
| Protection and Security | Controls access to resources and information | Protecting confidential patient records |

## 3. Services Required in Each Hospital Environment

| Environment | Essential Services | Reason |
|---|---|---|
| Bedside patient monitors | Program execution, I/O, error detection, resource allocation, protection | Must process sensor readings and generate timely alarms |
| Nurses' tablets | User interface, communication, file access, security, power management | Supports mobile access to patient information |
| Doctors' workstations | User interface, program execution, file management, communication, security | Supports clinical applications and record access |
| Central database server | File management, communication, protection, error detection, resource allocation, accounting | Maintains and protects patient information |
| MRI imaging server | Program execution, I/O, resource allocation, memory management, error detection | Processes large medical imaging workloads |
| Partner hospital network | Communication, protection, authentication, error detection | Enables secure sharing of records |

## 4. Services That Can Be Removed or Reduced on Bedside Monitors

Bedside patient monitors are specialized devices. They do not need every service found in a desktop operating system.

The following services can be removed or reduced where they are not required:

- Full graphical desktop interface: A simple monitoring interface is sufficient.
- General-purpose printing support: Not necessary if the monitor does not directly print.
- Unnecessary file-system features: Only essential configuration and event storage may be needed.
- Unused networking services: Disable services that are not required for monitoring.
- Unnecessary background applications: Reduce CPU and memory usage.

The monitor must retain essential services such as sensor input/output, alarm processing, scheduling, error detection, communication and security.

Removing unnecessary services reduces resource usage and can reduce the system's attack surface.

## 5. Essential Services for the Central Database Server

The central patient-record database requires:

1. File-system management to store and retrieve patient records.
2. Communication services to connect authorized hospital applications.
3. Protection and security to prevent unauthorized access.
4. Error detection to identify storage and system problems.
5. Resource allocation to manage CPU, memory and storage.
6. Program execution to run database software.
7. Accounting and auditing to record access and resource usage.
8. Backup and recovery support to protect records from failures.

These services support database reliability, availability and confidentiality.

## 6. Protecting One Patient's Records from Another Program

The hospital must prevent unauthorized programs and users from accessing patient information.

The following protection mechanisms should be used:

- User authentication: Verify the identity of each user.
- Role-based access control: Give doctors, nurses and administrators only the permissions required for their duties.
- Process isolation: Prevent one application from accessing another application's memory.
- File permissions: Restrict access to patient-record files.
- Encryption: Protect patient information during storage and network transmission.
- Audit logs: Record who accessed or modified patient records.
- Least privilege: Give applications only the permissions they need.

For example, a nurse should access records needed for assigned patient care, while an unrelated application should not be able to read those records.

## 7. Alternative Design: Full Desktop OS vs Reduced Handheld OS

### Option A: Full Desktop Operating System on Tablets

Advantages:
- Supports many applications.
- Provides extensive features and compatibility.
- Offers a familiar desktop environment.

Disadvantages:
- Requires more memory and storage.
- May take longer to start.
- Background services can consume battery power.
- Provides unnecessary features for a dedicated nursing device.

### Option B: Reduced Handheld Operating System

Advantages:
- Uses fewer resources.
- Can start more quickly.
- Better suited to touch-based applications.
- Can reduce background power consumption.
- Provides a smaller set of required services.

Disadvantages:
- Some desktop applications may not be supported.
- Requires careful application compatibility testing.
- Specialized features may need separate development.

### Comparison

| Factor | Full Desktop OS | Reduced Handheld OS |
|---|---|---|
| Memory usage | Generally higher | Generally lower |
| Storage usage | Generally higher | Generally lower |
| Startup time | May be longer | Can be shorter |
| Battery life | More background resource use may reduce battery life | Can improve battery efficiency |
| Application support | Broad | Focused on required applications |
| Complexity | More features to manage | Fewer unnecessary services |

## 8. Final Recommendation

The hospital should use a reduced handheld operating system for nurses' tablets to improve resource efficiency and battery management.

Bedside monitors should use a specialized real-time operating system with only essential services. Doctors' workstations can use full desktop operating systems. The central database server must provide strong file management, communication, protection, auditing and recovery services.

## 9. Conclusion

Operating-system services must be selected according to the needs of each hospital environment. Removing unnecessary services from specialized devices improves efficiency, while retaining essential security and reliability services protects patient information and supports hospital operations.
EOF