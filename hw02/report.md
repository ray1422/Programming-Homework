# HW02
## 測試環境
- sp1.cs.ccu.edu.tw 系統程式開的
- 大小：10M

## 測試結果
### Merge Sort
```bash
s409410005@sp1:~/workspace/Programming-Homework/hw02$ time ./mergesort > /dev/null

real    0m1.735s
user    0m1.683s
sys     0m0.052s
```

### Quick Sort

```bash
s409410005@sp1:~/workspace/Programming-Homework/hw02$ time ./quicksort > /dev/null

real    0m1.574s
user    0m1.542s
sys     0m0.032s

```

### Heap Sort
```bash
s409410005@sp1:~/workspace/Programming-Homework/hw02$ time ./heapsort > /dev/null

real    0m2.588s
user    0m2.556s
sys     0m0.032s
```

## 額外測試
### MultiThreading QuickSort
- size: 1e9
- 32 cores CPU
```
排序部分時間：13.389705 s
real    0m27.998s
user    2m48.570s
sys     0m4.793s 
```
