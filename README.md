# Time estimated
how to estimate time？

## 间隔计数器(>1s)
利用的方法是读进程的累积计数器

### time
linux命令获取用户模式执行时间，内核模式执行时间，以及总时间，通常总时间大于Tu + Ts，因为缺页和IO的处理;


### times

```python
#include <sys/time.h>

struct tms {
	clock_t tms_utime;
	clock_t tms_stime;
	clock_t tms_cutime;
	clock_t tms_cstime;
};

clock_t times(struct tms *buf);

```
返回的是时间单位是时钟滴答，需要除以CLK_TCK; CLK_TCK表示每秒的时钟滴答数;


### clock
需要除以CLOCKS_PER_SEC来表示秒;


## 周期计数器(<1s推荐)

### gettimeofday

```python
#include <sys/time.h>
struct timeval {
	long tv_sec;
	long tv_usec;
}

int gettimeofday(struct timeval *tv, NULL);
```

### rdtsc汇编指令
见当前文档
