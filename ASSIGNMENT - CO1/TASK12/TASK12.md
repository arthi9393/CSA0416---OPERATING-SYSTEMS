# TASK 12 – Day-4 Design Challenge

## 1. Introduction

The hospital system has a new requirement: patients use home monitoring devices to send health readings over the internet, and patient records are stored in a cloud service shared with partner hospitals.

This change requires improvements to the operating system design, networking, security, and reliability.

## 2. Impact on the Original OS Plan

The original plan used:
- Embedded RTOS for medical equipment.
- Linux servers for centralized hospital services.
- Desktop operating systems for administration computers.

The new requirements introduce remote devices and cloud-based record sharing. The original plan can support some of these requirements, but it needs additional components for secure internet communication and distributed data access.

## 3. Operating Systems and Services Required

### A. Home Monitoring Devices

Embedded operating systems or embedded RTOS are suitable for home monitoring devices.

Required services include:
- Device and sensor management.
- Reliable collection of readings.
- Network communication.
- Local data buffering when internet access is unavailable.
- Secure authentication and transmission.

### B. Cloud Services

Cloud-hosted server operating systems can manage patient records and provide access to authorized partner hospitals.

Required services include:
- Distributed data management.
- Network and file services.
- Authentication and authorization.
- Encryption and secure communication.
- Logging, monitoring, and backup.

### C. Hospital Computers

Hospital computers continue using desktop operating systems to access authorized cloud and hospital services.

Access should be restricted according to staff roles.

## 4. Security and Protection

The new design creates additional security risks because data travels through the internet and is shared between organizations.

Recommended protections include:
- Encryption during data transmission and storage.
- Strong authentication for users and devices.
- Role-based access control.
- Secure network connections.
- Regular software and firmware updates.
- Audit logs to track access to patient records.
- Backups and recovery procedures.

Only authorized staff and partner hospitals should access the records they need.

## 5. Response Time and Reliability

Home monitoring devices should collect readings reliably and transmit them promptly. Local buffering can temporarily store readings during internet outages.

Cloud services can make records accessible from multiple hospitals. However, internet delays or cloud-service failures may temporarily prevent access.

To improve reliability:
- Use redundant cloud services.
- Maintain regular backups.
- Monitor network and server availability.
- Keep essential local hospital services available.
- Provide procedures for temporary network outages.

Time-critical medical decisions should not depend entirely on a remote cloud connection.

## 6. Adapted System Design

The original design should be extended into a distributed hospital system.

The proposed architecture is:

1. Home monitoring devices use embedded RTOS or suitable embedded operating systems.
2. Devices send readings through secure internet connections.
3. Cloud servers store and manage shared patient records.
4. Hospital servers synchronize required information with the cloud.
5. Authorized staff access records through protected hospital computers.

This design supports remote monitoring and information sharing while keeping access controlled.

## 7. Trade-offs and Limitations

**Advantages:**
- Patients can be monitored remotely.
- Authorized partner hospitals can share records.
- Centralized cloud services simplify data access.
- Local buffering helps during temporary network interruptions.

**Limitations:**
- Internet connectivity affects data transmission.
- Cloud services introduce dependence on external infrastructure.
- Security management becomes more complex.
- Distributed systems require synchronization and careful handling of conflicting updates.
- Cloud processing and network delays may affect response time.

## 8. Final Recommendation

The hospital should adopt a secure distributed architecture. Embedded operating systems should be used for home monitoring devices, while cloud-hosted server systems manage shared patient records. Hospital servers should retain essential local services and synchronize with the cloud when connectivity is available.

Encryption, strong authentication, role-based access, backups, monitoring, and redundant services are necessary.

This adapted design supports remote patient monitoring and secure information sharing while maintaining reliability and protecting patient information.