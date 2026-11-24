# Illustrative workload model; change assumptions to match measured deployment.
videos=1200
average_gb=1.0
replicas=2
users=200_000
peak_concurrency=0.10
bitrate_mbps=4
print("catalogue_TB =", videos*average_gb)
print("replicated_TB =", videos*average_gb*replicas)
print("peak_Gbit_s =", users*peak_concurrency*bitrate_mbps/1000)
