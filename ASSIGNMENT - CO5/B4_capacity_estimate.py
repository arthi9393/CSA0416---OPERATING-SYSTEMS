#!/usr/bin/env python3
"""B4.2 capacity estimate.
Usage: python3 B4_capacity_estimate.py <measured_rps_per_container> [requests_per_student] [peak_factor] [target_utilisation]
Replace the first argument with YOUR ab/wrk result for ONE container (limited to 0.5 CPU)."""
import math, sys

rps_one   = float(sys.argv[1]) if len(sys.argv) > 1 else 400.0   # EXAMPLE value - use your own measurement
req_per_s = float(sys.argv[2]) if len(sys.argv) > 2 else 10      # page loads + API calls per login session
peak      = float(sys.argv[3]) if len(sys.argv) > 3 else 5.0     # peak-to-average ratio (burst in first minutes)
util      = float(sys.argv[4]) if len(sys.argv) > 4 else 0.7     # keep 30 % head-room
students, window_s = 150_000, 2 * 3600

total_req  = students * req_per_s
avg_rps    = total_req / window_s
peak_rps   = avg_rps * peak
containers = math.ceil(peak_rps / (rps_one * util))
cpu_cores  = containers * 0.5
mem_gb     = containers * 0.25
print(f"Total requests        : {total_req:,.0f}")
print(f"Average load          : {avg_rps:,.0f} req/s")
print(f"Peak load (x{peak:g})     : {peak_rps:,.0f} req/s")
print(f"Capacity / container  : {rps_one:,.0f} req/s (usable {rps_one*util:,.0f} at {util:.0%})")
print(f"Containers needed     : {containers}")
print(f"CPU / memory (limits) : {cpu_cores:g} cores / {mem_gb:g} GB")
