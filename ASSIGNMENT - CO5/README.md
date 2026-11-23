# CSA04 - Operating Systems - Assignment 5 (CO5)
**Name:** [your name]  **Register Number:** [your register number]
**Linux distribution / version:** [e.g. Ubuntu 24.04]  **Docker:** [version]  **minikube/kind:** [version]
**Compile/run commands:** shell scripts run with `bash`; Python app with `gunicorn`; no C programs in this assignment (if you add any: `gcc -std=c11 -Wall -Wextra -pthread file.c`).

## Files in this package and the task each belongs to
| File | Task | Purpose |
|---|---|---|
| Assignment5_Report.docx | A1-A5, B1-B4 | Full report (design, comparison tables, fill-in tables) |
| Diagram_A1_linux_architecture.png, Diagram_A5_cloud_design.png | A1, A5 | Diagrams used in the report |
| B1_observe_system.sh | B1.1 | ps, top, free, vmstat, iostat, df, ss capture |
| B1_log_summary.sh (+ B1_log_summary_output.txt) | B1.2 | Completed TODO 1 and TODO 2 (tested, matches expected output) |
| B1_crontab.txt | B1.2 | Hourly cron line plus disk alert and backup |
| B1_disk_alert.sh, B1_backup.sh | B1.2 | Disk-space alert, nightly backup |
| B1_portal.service, B1_nginx_portal.conf, B1_setup_server.sh | B1.3 | systemd service, Nginx reverse proxy, ufw (22/80/443 only) |
| app.py, requirements.txt | B2/B3 | Sample Flask portal (/, /health, /result/<regno>, /visits) |
| Dockerfile | B2 | Completed TODO 1-3 |
| Dockerfile.multistage, Dockerfile.ubuntu | B2 | Image-size comparison |
| docker-compose.yml, B2_commands.sh | B2 | Portal + PostgreSQL with volume and limits |
| deployment.yaml, hpa.yaml | B3.3 | Completed TODO 1-2; autoscaler |
| B3_commands.sh | B3 | Bare metal vs VM vs container, minikube steps |
| docker-compose.b4.yml, B4_capacity_estimate.py (+ example output) | B4 | Second service; capacity calculation |

## How to run
1. Part B1: `bash B1_log_summary.sh`; `bash B1_observe_system.sh | tee B1_observe_output.txt`; install cron lines with `crontab -e`.
2. B2: `bash B2_commands.sh` step by step (copy one command at a time and save outputs).
3. B3/B4: follow `B3_commands.sh`; `python3 B4_capacity_estimate.py <your_rps>`.


