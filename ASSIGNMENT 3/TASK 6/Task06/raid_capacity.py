n=6; disk=4 # TB each
print(f"RAID0 usable={n*disk} TB (no redundancy)")
print(f"RAID1 usable={disk} TB for six-way mirror (conservative layout)")
print(f"RAID5 usable={(n-1)*disk} TB")
print(f"RAID6 usable={(n-2)*disk} TB")
print(f"RAID10 usable={(n//2)*disk} TB")
