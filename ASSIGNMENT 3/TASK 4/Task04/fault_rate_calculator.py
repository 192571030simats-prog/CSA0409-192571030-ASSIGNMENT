memory_ns=100
fault_ns=8_000_000
for rate in (1/1000,1/100000,1/1000000):
    eat=(1-rate)*memory_ns+rate*fault_ns
    print(f"fault rate={rate:.8f}, EAT={eat:.2f} ns, slowdown={eat/memory_ns:.2f}x")
# 10% slowdown: (1-p)*100 + p*8,000,000 <= 110
p=10/(fault_ns-memory_ns)
print(f"maximum rate for 10% slowdown = {p:.10g} (about 1 in {1/p:,.0f})")
