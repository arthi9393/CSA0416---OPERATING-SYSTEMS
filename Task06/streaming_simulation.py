#!/usr/bin/env python3
"""Simple illustrative origin-vs-CDN workload model; not a production benchmark."""
import random

def simulate(users=10000, bitrate_mbps=3.0, cache_hit=0.90, seed=42):
    random.seed(seed)
    # A fixed hit ratio is used to make the comparison reproducible.
    cdn_users = int(users * cache_hit)
    origin_users = users - cdn_users
    total_gbps = users * bitrate_mbps / 1000.0
    origin_only_gbps = total_gbps
    cdn_origin_gbps = origin_users * bitrate_mbps / 1000.0
    print(f"Concurrent viewers: {users}")
    print(f"Average bitrate: {bitrate_mbps:.1f} Mbit/s")
    print(f"Total delivery demand: {total_gbps:.2f} Gbit/s")
    print(f"Origin-only design origin load: {origin_only_gbps:.2f} Gbit/s")
    print(f"CDN cache hit ratio: {cache_hit:.0%}")
    print(f"CDN design origin load: {cdn_origin_gbps:.2f} Gbit/s")
    print(f"Origin load reduction: {(1-cache_hit)*100:.1f}%")

if __name__ == "__main__":
    simulate()
