# TASK 1 – Evaluate the Requirements of Each Computing Environment

## 1. Introduction

A smart hospital uses different computing environments to provide safe and efficient healthcare services. These include bedside patient monitors, nurses' handheld tablets, doctors' desktop workstations, a central patient-record database, an MRI imaging server and communication systems connecting partner hospitals.

Each environment has different operating-system requirements. Patient monitors need predictable response times, while database servers require high reliability, security and the ability to handle many users. Therefore, one operating-system design may not be suitable for every environment.

## 2. Requirements of Each Computing Environment

### 2.1 Bedside Patient Monitors

Bedside patient monitors continuously collect patient readings and detect abnormal conditions.

Their requirements are:

- **Response time – Highest priority:** An abnormal reading must trigger an alarm within 10 milliseconds.
- **Reliability – Very high:** The monitor must operate continuously without unexpected failure.
- **Throughput – Moderate:** It must process sensor readings and alarms efficiently.
- **Battery usage – Important:** Efficient power consumption is necessary, especially for portable monitoring equipment.
- **Security – Very high:** Patient readings must be protected from unauthorized access or modification.

A real-time operating system is suitable because it can provide predictable scheduling and support deadline-sensitive operations.

### 2.2 Nurses' Handheld Tablets

Nurses use handheld tablets to view patient records, receive notifications and update treatment information.

Their requirements are:

- **Response time – High:** Applications should open quickly and respond smoothly.
- **Reliability – High:** Nurses must be able to access important patient information.
- **Throughput – Moderate:** The device handles several applications and communication activities.
- **Battery usage – Very high:** Tablets should operate throughout working shifts.
- **Security – Very high:** Authentication and encryption are required to protect patient information.

A mobile operating system is appropriate because it supports portable devices, wireless communication and power management.

### 2.3 Doctors' Desktop Workstations

Doctors use desktop computers to review patient records, prepare reports and communicate with other departments.

Their requirements are:

- **Response time – High:** Applications should respond quickly.
- **Reliability – High:** Workstations should remain available during clinical activities.
- **Throughput – High:** They may run several applications simultaneously.
- **Battery usage – Low priority:** Desktop computers generally use a continuous power supply.
- **Security – Very high:** Access control is necessary to protect confidential patient records.

A desktop operating system provides a graphical interface, multitasking and support for medical applications.

### 2.4 Central Patient-Record Database

The central database stores patient details, medical histories, prescriptions and treatment information.

Its requirements are:

- **Response time – High:** Patient records should be retrieved quickly.
- **Reliability – Highest priority:** The database must remain available to authorized hospital users.
- **Throughput – Very high:** It must handle many simultaneous requests.
- **Battery usage – Not important:** The server uses a continuous power supply.
- **Security – Highest priority:** Patient information must be protected using authentication, authorization, encryption and auditing.

A server operating system with database support, backup facilities and clustering is suitable.

### 2.5 MRI Imaging Server

The imaging server processes large MRI images and performs computationally intensive operations.

Its requirements are:

- **Response time – High:** Image processing should complete efficiently.
- **Reliability – Very high:** Processing errors or failures could interrupt medical workflows.
- **Throughput – Very high:** It must process large image files and multiple workloads.
- **Battery usage – Not important:** The server is connected to continuous power.
- **Security – Very high:** Medical images must be protected against unauthorized access.

A multiprocessor operating system is suitable because it can use multiple processors to perform computational tasks in parallel.

### 2.6 Partner-Hospital Communication Link

The hospital shares authorized patient records with two partner hospitals.

Its requirements are:

- **Response time – High:** Information should be exchanged without unnecessary delays.
- **Reliability – Very high:** Communication should remain available.
- **Throughput – High:** The system must support record sharing and multiple network requests.
- **Battery usage – Not important:** Communication is handled by network infrastructure and servers.
- **Security – Highest priority:** Data must be encrypted and exchanged only with authorized systems.

A distributed operating-system environment supports communication and resource sharing between hospitals.

## 3. Ranked Requirement Table

| Environment | 1st priority | 2nd priority | 3rd priority |
|---|---|---|---|
| Patient monitors | Response time | Reliability | Security |
| Nurses' tablets | Battery usage | Security | Response time |
| Doctors' workstations | Security | Response time | Throughput |
| Patient database | Reliability | Security | Throughput |
| MRI imaging server | Throughput | Reliability | Response time |
| Partner-hospital link | Security | Reliability | Throughput |

The rankings are based on the main purpose of each environment. All listed requirements remain important, even when they are not ranked first.

## 4. Conflicting Requirements

Some operating-system requirements may conflict with one another.

**Fast response time versus high throughput:** A system processing many requests may experience resource competition. This can increase the time taken to respond to an individual request. Patient monitors therefore require priority scheduling for alarm-related operations.

**Security versus performance:** Encryption and authentication require processing resources. Although they can introduce additional overhead, they are essential for protecting confidential patient information.

**Battery usage versus performance:** Running several applications and performing continuous wireless communication can consume more battery power. Tablets need power-management features to balance performance and battery life.

**Reliability versus cost:** Redundant servers and backup systems improve availability but increase infrastructure and maintenance costs.

## 5. Patient-Safety-Critical Requirements

Patient safety is the most important consideration in the smart hospital design.

The following requirements are critical:

1. Bedside monitors must detect abnormal readings and raise alarms within the specified 10-millisecond deadline.
2. Patient monitors must continue operating reliably.
3. Patient records must remain accurate and available to authorized healthcare professionals.
4. Network communication failures must not silently cause important medical information to be lost.
5. Access controls must prevent unauthorized modification of patient information.
6. Backup and recovery systems must protect important medical records.

The bedside monitor alarm requirement is particularly important because delayed alarms may affect clinical response. A hard real-time operating system with predictable scheduling is a suitable design choice, provided the complete hardware and software system is validated against the 10-millisecond deadline.

## 6. Lessons from the History of Operating Systems

### 6.1 Batch Operating Systems

Batch operating systems execute groups of jobs without continuous user interaction. Their main lesson is efficient processing of large workloads.

This concept is useful for scheduled database backups and large-scale image-processing jobs. However, batch processing is unsuitable for immediate bedside alarms because it does not provide the required immediate response.

### 6.2 Time-Sharing Operating Systems

Time-sharing systems allow multiple users and processes to share computing resources.

This concept is useful for the central patient-record database and doctors' workstations because many users may access hospital applications simultaneously.

### 6.3 Personal Computer Operating Systems

Personal computer operating systems provide graphical interfaces, multitasking and application support.

These features are useful for doctors' desktop workstations, where users need to access medical applications, prepare reports and review patient information.

### 6.4 Mobile Operating Systems

Mobile operating systems support portable devices, wireless communication and battery management.

These features are suitable for nurses' handheld tablets because nurses need to access patient records and receive notifications while moving between hospital departments.

## 7. Alternative Concept: Using One General-Purpose Operating System Everywhere

An alternative design would use one general-purpose operating system across all hospital devices and servers.

However, this approach has several disadvantages.

### 7.1 Worst-Case Alarm Response Time

A general-purpose operating system is designed to support many different applications and workloads. Its scheduling behaviour may not guarantee that an alarm-processing task always runs within 10 milliseconds.

A hard real-time operating system can provide bounded scheduling behaviour when correctly configured and validated.

Therefore, using a general-purpose operating system for bedside monitors introduces a risk of missing the alarm deadline.

### 7.2 Memory Requirements

General-purpose operating systems usually include additional services, drivers and background processes.

These features require more memory and storage than a small embedded real-time operating system.

Using a lightweight operating system for bedside monitors can reduce memory requirements and unnecessary processing.

### 7.3 Administration Effort

Using one operating system may simplify some software management and staff training.

However, the same operating system may require different configurations for monitors, tablets, desktops and servers. This can create unnecessary complexity and may not provide the specialised features required by every environment.

Using suitable operating systems for each environment requires more planning, but provides better control over performance, security and reliability.

## 8. Comparison of the Two Designs

| Factor | One general-purpose OS | Different suitable OS types |
|---|---|---|
| Alarm response | No guaranteed hard deadline by default | Can provide predictable real-time scheduling |
| Memory usage | May require more memory | Lightweight options for embedded devices |
| Administration | Some standardisation | Requires managing different platforms |
| Performance | General-purpose workloads | Can be optimised for each environment |
| Reliability | Depends on common OS configuration | Can use specialised reliability features |
| Suitability | Less suitable for all hospital environments | Better fit for different requirements |

## 9. Conclusion

The smart hospital requires different operating-system characteristics for different computing environments. Bedside monitors need predictable real-time response, tablets need battery efficiency and mobility, desktops need multitasking, databases need high availability and security, and imaging servers need high processing throughput.

Therefore, using different operating-system types according to each environment is more suitable than using one general-purpose operating system everywhere. This approach provides a better balance of patient safety, performance, reliability, security and resource usage.