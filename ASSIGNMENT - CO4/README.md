# CSA04 – Operating Systems – Assignment 4 (CO4)

## Student details
- Name: ARTHI A 
- GCC version: `gcc --version`

## Contents
- `CSA04_Assignment4_Report_1.5_Line_Spacing.docx` – report with 1.5 line spacing.
- `Task02/alloc.c` – completed first-fit contiguous and indexed allocation program.
- `Task04/disk_schedule.c` – completed SSTF program plus FCFS/SCAN/C-SCAN output.
- `Task04/sstf_batch.c` – 10,000-request static SSTF movement simulation scaffold.
- `Task06/streaming_simulation.py` – illustrative CDN/origin workload model.
- `Screenshots/` – add actual Linux command outputs and execution screenshots.

## Compile and run
```bash
gcc -std=c11 -Wall -Wextra Task02/alloc.c -o Task02/alloc
./Task02/alloc

gcc -std=c11 -Wall -Wextra Task04/disk_schedule.c -o Task04/disk_schedule
./Task04/disk_schedule

gcc -std=c11 -Wall -Wextra Task04/sstf_batch.c -o Task04/sstf_batch
./Task04/sstf_batch

python3 Task06/streaming_simulation.py
```

## Notes
- Execute all programs on your own Linux environment and save terminal screenshots in `Screenshots/`.
- Task 3 inspection commands (`stat`, `df -i`, `ls -i`, `tune2fs -l` or `dumpe2fs -h`) must be run against your own file system. Do not submit fabricated command output.
- Fill in the report cover page, GitHub link, OS/GCC versions, and actual measurements before submission.
- Commit progressively, with at least one commit for each task, as required by the assignment handout.
