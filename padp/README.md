## PADP - Parallel Architecture and Distributed Programming

| #   | Desc           |
| --- | -------------- |
| 00  | Basic Programs |


### Execution shortform
```
for ARR_SIZE in {10000,100000,1000000,10000000}; do for OMP_NUM_THREADS in {1,2,4,8}; do echo "$ARR_SIZE $OMP_NUM_THREADS" && ARR_SIZE=$ARR_SIZE OMP_NUM_THREADS=$OMP_NUM_THREADS ./build/padp_40_cnfe ; done; done
```