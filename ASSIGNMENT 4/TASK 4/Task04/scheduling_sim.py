import random, statistics
random.seed(42)
def sstf(head, requests):
    pending=requests[:]; total=0; waits=[]; now=0
    while pending:
        nxt=min(pending,key=lambda x:abs(x-head))
        total+=abs(nxt-head); head=nxt; pending.remove(nxt); now+=1
    return total
for load,n in [("light",100),("medium",1000),("heavy",10000)]:
    q=[random.randrange(200) for _ in range(n)]
    print(f"{load:6} requests={n:5} SSTF total movement={sstf(53,q)}")
