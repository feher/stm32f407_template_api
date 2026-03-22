# References

https://github.com/erez-strauss/lockfree_mpmc_queue/blob/master/mpmc_queue.h

# Debugging

```
Note: Google Test filter = *Concurrency_N_Producer_M_Consumer
[==========] Running 1 test from 1 test suite.
[----------] 1 test from CircularQueue
[ RUN      ] CircularQueue.Concurrency_N_Producer_M_Consumer
ERROR: Didn't receive all items. Missing:  300 301 302
ERROR: Received more (bogus) items. Extra:  555555555
ERROR: Hole at index 299. Items:  299 303 304 305 306 
ERROR: Missing values:  300 301 302
ERROR: Duplicate at index 597. Items:  555555555 555555555 555555555 
ERROR: Duplicate values:  555555555 555555555
ERROR: Consumer 0 received duplicate items.
ERROR: Consumer 0 duplicate values:  555555555 555555555
/home/feher/d/prdev/stm32/udemy_001/libs/data_struct/test/data_struct_test.cpp:573: Failure
Value of: isFailed
  Actual: true
Expected: false
```

We read (consume) 555555555 instead of the real item (300).
Was 300 replaced by 555555555?
Was 300 never written to the queue?

```
Note: Google Test filter = *Concurrency_N_Producer_M_Consumer
[==========] Running 1 test from 1 test suite.
[----------] 1 test from CircularQueue
[ RUN      ] CircularQueue.Concurrency_N_Producer_M_Consumer
ERROR: Item count mismatch. In 600 != out 605
ERROR: Received more (bogus) items. Extra:  555555555
ERROR: Duplicate at index 600. Items:  555555555 555555555 555555555 555555555 555555555 
ERROR: Duplicate values:  555555555 555555555 555555555 555555555
ERROR: Consumer 0 received duplicate items.
ERROR: Consumer 0 duplicate values:  555555555 555555555 555555555 555555555
/home/feher/d/prdev/stm32/udemy_001/libs/data_struct/test/data_struct_test.cpp:573: Failure
Value of: isFailed
  Actual: true
Expected: false
```

Producers skipping free (555555555) slots?
Producers move the tail but they never write (all detects full)?
Producers move the reserved tail but they haven't written yet?


```
Note: Google Test filter = *Concurrency_N_Producer_M_Consumer
[==========] Running 1 test from 1 test suite.
[----------] 1 test from CircularQueue
[ RUN      ] CircularQueue.Concurrency_N_Producer_M_Consumer
ERROR: Didn't receive all items. Missing:  355
ERROR: Received more (bogus) items. Extra:  555555555
ERROR: Hole at index 354. Items:  354 356 357 358 359 
ERROR: Missing values:  355
/home/feher/d/prdev/stm32/udemy_001/libs/data_struct/test/data_struct_test.cpp:573: Failure
Value of: isFailed
  Actual: true
Expected: false
```

We consume the already consumed items (555555555).

Ideas:
- Producer1 tries to add()
  - Full
  - Gets rtail snapshot
  - Consumer moves head
  - Producer2 adds and moves rtail -> no tail update!
  - --prodCount
  - Producer1 sets tail to old rtail.
  

#

1P 2C

ERROR: Item count mismatch. In 300 != out 305
ERROR: Received more (bogus) items. Extra:  555555555
ERROR: Duplicate at index 300. Items:  555555555 555555555 555555555 555555555 555555555 
ERROR: Duplicate values:  555555555 555555555 555555555 555555555
ERROR: Consumer 0 received duplicate items.
ERROR: Consumer 0 duplicate values:  555555555 555555555 555555555
/home/feher/d/prdev/stm32/udemy_001/libs/data_struct/test/queue_2_test.cpp:598: Failure
Value of: isFailed
  Actual: true
Expected: false


2p 1c

ERROR: Item count mismatch. In 600 != out 595
ERROR: Didn't receive all items. Missing:  147 462 463 464 465
ERROR: Hole at index 146. Items:  146 148 149 150 151 
ERROR: Missing values:  147 462 463 464 465
/home/feher/d/prdev/stm32/udemy_001/libs/data_struct/test/queue_2_test.cpp:598: Failure
Value of: isFailed
  Actual: true
Expected: false

ABA problem?

-----------------------------

CircularQueueMpMcLf2<int, 1> --> k_internalCapacity == 2

1 consumer, 2 producers:

c1: h=0, t=0, rh=0, rt=0, d=[0,0]
p1: h=0, t=0, rh=0, rt=0, d=[0,0]
p2: h=0, t=0, rh=0, rt=0, d=[0,0]

1. p1 reads h and rt --> p1.h=0, p1.rt=0
2. p2 writes d[0] --> h=0, rh=0, t=1, rt=1, d=[p2,0]
3. c1 reads d[0] --> h=1, rh=1, t=1, rt=1, d=[x,0]
4. p2 writes d[1] --> h=1, rh=1, t=0, rt=0, d=[x,p2]
5. p1 continues
   p1.h=0, p1.rt!=p1.h-1 --> not full (empty) --> p1.rt==rt==0 --> can take reserve rt
   --> __overwrites__ p2 data
   --> h=1, rh=1, t=0, rt=1, d=[x,p1]
