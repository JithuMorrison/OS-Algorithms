#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct process {
    int id, at, bt, st, ft, wt, tat, rt, rem, done;
};

struct table {
    struct process arr[100];
    int size;
};

void add(struct table *t, struct process *a) {
    t->arr[t->size] = *a;
    t->size++;
}

int alldone(struct process *a[], int n) {
    for (int i = 0; i < n; i++) {
        if (a[i]->done == 0) return 0;
    }
    return 1;
}

void rr(struct process *a[], int n, int ts) {
    struct table t1;
    t1.size = 0;
    int clk = 0, completed = 0;
    int ready[100], ready_count = 0;
    while (completed < n) {
        for (int i = 0; i < n; i++) {
            if (a[i]->at <= clk && a[i]->done == 0) {
                int already_ready = 0;
                for (int j = 0; j < ready_count; j++) {
                    if (ready[j] == i) {
                        already_ready = 1;
                        break;
                    }
                }
                if (!already_ready) ready[ready_count++] = i;
            }
        }
        if (ready_count > 0) {
            int k = ready[0];
            for (int i = 1; i < ready_count; i++) {
                ready[i - 1] = ready[i];
            }
            ready_count--;
            if (a[k]->rem == a[k]->bt) {
                a[k]->st = clk;
            }
            int t = ts;
            while (t > 0 && a[k]->rem > 0) {
                clk++;
                a[k]->rem--;
                for (int i = 0; i < n; i++) {
                    if (a[i]->at <= clk && a[i]->done == 0) {
                        int already_ready = 0;
                        for (int j = 0; j < ready_count; j++) {
                            if (ready[j] == i) {
                                already_ready = 1;
                                break;
                            }
                        }
                        if (!already_ready) ready[ready_count++] = i;
                    }
                }
                t--;
            }
            if (a[k]->rem == 0) {
                a[k]->done = 1;
                a[k]->ft = clk;
                completed++;
            } else {
                ready[ready_count++] = k;
            }
            add(&t1, a[k]);
        } else {
            clk++;
        }
    }

    printf("Gantt Chart:\n");
    for (int i = 0; i < t1.size; i++) {
        printf("(%d)|P%d", t1.arr[i].st, t1.arr[i].id);
    }
    printf("(%d)|\n", t1.arr[t1.size - 1].ft);

    float total_wt = 0, total_rt = 0, total_tat = 0;
    printf("\n|Pid|AT\t|BT\t|ST\t|FT\t|WT\t|TAT|RT\t|\n");
    for (int i = 0; i < t1.size; i++) {
        t1.arr[i].wt = t1.arr[i].st - t1.arr[i].at;
        t1.arr[i].tat = t1.arr[i].ft - t1.arr[i].at;
        t1.arr[i].rt = t1.arr[i].st - t1.arr[i].at;

        if (t1.arr[i].done) {
            total_wt += t1.arr[i].wt;
            total_rt += t1.arr[i].rt;
            total_tat += t1.arr[i].tat;
        }

        printf("|P%d\t|%d\t|%d\t|%d\t|%d\t|%d\t|%d\t|%d\t|\n",
               t1.arr[i].id, t1.arr[i].at, t1.arr[i].bt, t1.arr[i].st,
               t1.arr[i].ft, t1.arr[i].wt, t1.arr[i].tat, t1.arr[i].rt);
    }
    printf("Average waiting time: %f\n", total_wt / n);
    printf("Average response time: %f\n", total_rt / n);
    printf("Average turn around time: %f\n", total_tat / n);
}

int findmin(int k[], int n) {
  for (int i = 0; i < n; i++) {
    if (k[i] == 0) {
      return i;
    }
  }
  return -1;
}
int actmin(int bt[], int at[], int k[], int n, int v) {
  int s = 999;
  int vk = findmin(k, n);
  for (int i = 0; i < n; i++) {
    // printf("%d,%d\n",at[i],v);
    if (s > bt[i] && k[i] == 0 && at[i] <= v) {
      s = bt[i];
      vk = i;
    }
  }
  return vk;
}

int searchat(int at[], int n, int l) {
  for (int i = 0; i < n; i++) {
    if (at[i] <= l) {
      return 1;
    } else {
    }
  }
  return 0;
}

int find(int vt[], int n, int v) {
  for (int i = 0; i < n; i++) {
    if (vt[i] == v) {
      return 0;
    }
  }
  return 1;
}

void reversearray(int arr[], int size) {
  int start = 0;
  int end = size - 1;
  while (start < end) {
    int temp = arr[start];
    arr[start] = arr[end];
    arr[end] = temp;
    start++;
    end--;
  }
}

int secondocclast(int arr[], int n, int v) {
  int count = 0;
  reversearray(arr, n);
  for (int i = 0; i < n; i++) {
    if (arr[i] == v) {
      count++;
    }
    if (count == 2) {
      reversearray(arr, n);
      return n - i - 1;
    }
  }
  return -1;
}

int firstocclast(int arr[], int n, int v) {
  int count = 0;
  reversearray(arr, n);
  for (int i = 0; i < n; i++) {
    if (arr[i] == v) {
      count++;
    }
    if (count == 1) {
      reversearray(arr, n);
      return n - i - 1;
    }
  }
  return -1;
}

int firstocc(int arr[], int n, int v) {
  int count = 0;
  for (int i = 0; i < n; i++) {
    if (arr[i] == v) {
      count++;
    }
    if (count == 1) {
      return i;
    }
  }
  return -1;
}

void psjf(int sum,int n,int at[],int bt[],int k[],int f[]){
  int v=0;
  int str=0;
  int atp[sum];
  int kj[n];
  int fk=-1;
  int j=0;
  int fpi[sum];
  int spi[sum];
  int sti[sum];
  int fti[sum];
  int bti[sum];
  int wti[sum];
  int tati[sum];
  int rti[sum];
  int bop[n];
  int vt[n];
  for (int i=0;i<n;i++){
    k[i]=0;
    kj[i]=0;
    bop[i]=0;
  }
  for (int i=0;i<sum;i++){
    if(searchat(at, n, i)==1){
      int kr=actmin(bt,at,k,n,i);
      if(kr!=-1){
     atp[i]=at[kr];
     if(bt[kr]>kj[kr]){
     kj[kr]+=1;
     }
     if(bt[kr]==kj[kr]){
     k[kr]=1;
     }
     if(fk!=atp[i]){
     sti[j]=i;
     if(j>0){
       fti[j-1]=i;
       tati[j-1]=fti[j-1]-at[fpi[j-1]];
       if(firstocc(spi,j,spi[j])==-1){
              rti[j-1]=sti[j-1]-at[fpi[j-1]];
       }
       else{
        rti[j-1]=-1;
       }
     }
     if(find(vt, n, atp[i])==1){
       vt[kr]=atp[i];
     }
     fpi[j]=atp[i];
     spi[j]=f[kr];
    printf("(%d)|P%d",  i, fpi[j]+1);
     int kl = firstocc(spi,j,spi[j]);
     int spl = firstocclast(spi,j,spi[j]);
     if(kl==-1 & spl==-1){
            wti[j]=sti[j]-at[fpi[j]];
        }
        else{
            int bl = firstocclast(spi,j,spi[j])-1;
            if(bl!=-1){
              wti[j]=wti[bl]+(sti[j]-fti[bl]);
              tati[j-1]=fti[j-1]-at[fpi[j-1]];
            }
        }

     bti[j]=bt[kr]-bop[kr];
     bop[kr]=kj[j];
     j+=1;
     }
     }
      fk=atp[i];
      }
    }
  fti[j-1]=sum;
  tati[j-1]=fti[j-1]-at[fpi[j-1]];
  if(firstocc(spi,j,spi[j])==-1){
  rti[j-1]=sti[j-1]-at[fpi[j-1]];
  }
  else{
  rti[j-1]=-1;
  }
  printf("(%d)|",  fti[j-1]);
  printf("\n|Pid|AT\t|BT\t|ST\t|FT\t|WT\t|TAT|RT\t|\n");
  for (int i=0;i<5;i++){
    printf("|P%d\t|%d\t|%d\t|%d\t|%d\t|%d\t|%d\t|%d\t|\n",spi[i],at[fpi[i]],bti[i],sti[i],fti[i],wti[i],tati[i],rti[i]);
  }
}

int main() {
  int n;
  printf("enter the number of processes:");
  scanf("%d",&n);
  // n=4;
  int f[n];
  int at[n];
  int bt[n];
  int pt[n];
  int k[n];
  int sum = 0;
  
  struct process *arr[n];
  for (int i=0;i<n;i++)
  {
    arr[i]=(struct process*)malloc(sizeof(struct process));
    printf("enter the arrival time of process %d : ",i+1);
    int a;
    scanf("%d",&a);
    printf("enter the burst time of process %d : ",i+1);
    int b;
    scanf("%d",&b);
    printf("enter the priority of process %d : ",i+1);
    scanf("%d", &pt[i]);
    arr[i]->id=i+1;
    arr[i]->at=a;
    arr[i]->bt=b;
  arr[i]->rem=b;
    arr[i]->done=0;
    arr[i]->wt=-1;
    at[i]=a;
    bt[i]=b;
    sum += bt[i];
    k[i] = 0;
    f[i] = i + 1;
  }


  printf("\n\n\n----------------------------------FCFS----------------------------------\n");
  
  
  int st[n];
  int ft[n];
  int wt[n];
  int tat[n];
  int rt[n];
  int v = 0;
  int str = 0;
  for (int i = 0; i < n; i++) {
    int kr = findmin(k, n);
    if (kr != -1) {
      st[i] = str;
      if (st[i] < at[i]) {
        st[i] += at[i] - v, v += at[i] - v;
      }
      k[i] = 1;
      v += bt[i];
      printf("P%d(%d)|", f[i], v);
      ft[i] = v;
      wt[i] = st[i] - at[i];
      if (wt[i] + bt[i] == ft[i] - at[i]) {
        tat[i] = wt[i] + bt[i];
      } else {
        tat[i] = -1;
      }
      str = v;
      rt[i] = st[i] - at[i];
    }
  }
  printf("\n|Pid|AT\t|BT\t|ST\t|FT\t|WT\t|TAT|RT\t|\n");
  for (int i = 0; i < n; i++) {
    printf("|P%d\t|%d\t|%d\t|%d\t|%d\t|%d\t|%d\t|%d\t|\n", f[i],
           at[i], bt[i], st[i], ft[i], wt[i], tat[i], rt[i]);
  }



  printf("\n\n\n----------------------------------NPSJF----------------------------------\n");
  

  
  v = 0;
  str = 0;
  int vhk[n];
  for (int i = 0; i < n; i++) {
    k[i] = 0;
  }
  for (int i = 0; i < n; i++) {
    int kr = actmin(bt, at, k, n, str);
    if (kr != -1) {
      vhk[i] = kr;
      st[kr] = str;
      if (st[i] < at[i]) {
        st[kr] += at[kr] - v, v += at[kr] - v;
      }
      k[kr] = 1;
      v += bt[kr];
      printf("P%d(%d)|", f[kr], v);
      ft[kr] = v;
      wt[kr] = st[kr] - at[kr];
      if (wt[kr] + bt[kr] == ft[kr] - at[kr]) {
        tat[kr] = wt[kr] + bt[kr];
      } else {
        tat[kr] = -1;
      }
      str = v;
      rt[kr] = st[kr] - at[kr];
    }
  }
  printf("\n|Pid|AT\t|BT\t|ST\t|FT\t|WT\t|TAT|RT\t|\n");
  for (int i = 0; i < n; i++) {
    printf("|P%d\t|%d\t|%d\t|%d\t|%d\t|%d\t|%d\t|%d\t|\n",
           f[vhk[i]], at[vhk[i]], bt[vhk[i]], st[vhk[i]], ft[vhk[i]],
           wt[vhk[i]], tat[vhk[i]], rt[vhk[i]]);
  }




  printf("\n\n\n----------------------------------PSJF----------------------------------\n");

  

  psjf(sum, n, at, bt, k, f);



  printf("\n\n\n----------------------------------PPS----------------------------------\n");


  
  
  v = 0;
  str = 0;
  int atp[sum];
  int kj[n];
  int fk = -1;
  int j = 0;
  int fpi[sum];
  int spi[sum];
  int sti[sum];
  int fti[sum];
  int bti[sum];
  int wti[sum];
  int tati[sum];
  int rti[sum];
  int bop[n];
  int vt[n];
  for (int i = 0; i < n; i++) {
    k[i] = 0;
    kj[i] = 0;
    bop[i] = 0;
  }
  for (int i = 0; i < sum; i++) {
    if (searchat(at, n, i) == 1) {
      int kr = actmin(pt, at, k, n, i);
      if (kr != -1) {
        atp[i] = at[kr];
        if (bt[kr] > kj[kr]) {
          kj[kr] += 1;
        }
        if (bt[kr] == kj[kr]) {
          k[kr] = 1;
        }
        if (fk != atp[i]) {
          sti[j] = i;
          if (j > 0) {
            fti[j - 1] = i;
            tati[j - 1] = fti[j - 1] - at[fpi[j - 1]];
            if (firstocc(spi, j, spi[j]) == -1) {
              rti[j - 1] = sti[j - 1] - at[fpi[j - 1]];
            } else {
              rti[j - 1] = sti[j - 1] - at[fpi[j - 1]];
            }
          }
          if (find(vt, n, atp[i]) == 1) {
            vt[kr] = atp[i];
          }
          fpi[j] = atp[i];
          spi[j] = f[kr];
          printf("(%d)|P%d",  i, fpi[j]+1);
          int kl = firstocc(spi, j, spi[j]);
          int spl = firstocclast(spi, j, spi[j]);
          if (kl == -1 & spl == -1) {
            wti[j] = sti[j] - at[fpi[j]];
          } else {
            int bl = firstocclast(spi, j, spi[j]) - 1;
            if (bl != -1) {
              wti[j] = wti[bl] + (sti[j] - fti[bl]);
              tati[j - 1] = fti[j - 1] - at[fpi[j - 1]];
            }
          }

          bti[j] = bt[kr] - bop[kr];
          bop[kr] = kj[j];
          j += 1;
        }
      }
      fk = atp[i];
    }
  }
  fti[j - 1] = sum;
  tati[j - 1] = fti[j - 1] - at[fpi[j - 1]];
  if (firstocc(spi, j, spi[j]) == -1) {
    rti[j - 1] = sti[j - 1] - at[fpi[j - 1]];
  } else {
    rti[j - 1] = sti[j - 1] - at[fpi[j - 1]];
  }
  printf("(%d)|",  fti[j-1]);
  printf("\n|Pid|AT\t|BT\t|ST\t|FT\t|WT\t|TAT|RT\t|\n");
  for (int i = 0; i < j; i++) {
    printf("|P%d\t|%d\t|%d\t|%d\t|%d\t|%d\t|%d\t|%d\t|\n",
           f[fpi[i]], at[fpi[i]], bti[i], sti[i], fti[i], wti[i], tati[i],
           rti[i]);
  }

  printf("\n\n\n----------------------------------RR----------------------------------\n");

  printf("enter the time slice : ");
  int ts;
  scanf("%d",&ts);
  rr(arr,n,ts);
}
