# 离散化

> 兴许是不常用的原因，离散化我总是忘。。。记下来记下来

分三步

- 排序
- 去重
- 找编号

``` cpp
int n,k[N],cnt,st[N];

inline void Disc(){
    scanf("%d",&n);
    for (int i = 1;i <= n;i ++){
        scanf("%d",&k[i]);
        st[i] = k[i];
    }
    sort(st + 1,st + n + 1);
    cnt = unique(st + 1,st + n + 1) - st - 1;
    for (int i = 1;i <= n;i ++)
      k[i] = lower_bound(st + 1,st + n + 1,k[i]) - st;
}
```



