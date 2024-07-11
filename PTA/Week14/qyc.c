#include <stdio.h>
int main (){
    int N, s[1050];
    int i, j, min, k=0, cmp, index;
    int degree[1050], cmpdegree[1050], a[1050];
    scanf("%d",&N);
    for(i=0;i<N;i++){
        scanf("%d",&s[i]);
        if (s[i] < 0){
            degree[i] = -1;
        }else{
            degree[i] = (i - s[i] % N + N) % N;
        }
        cmpdegree[i] = degree[i];
    }
    while (k < N) {
        min = -1;
        for (i=0; i<N; i++){
            if (degree[i] == 0){
                if (min == -1 || s[i] < min){
                    min = s[i];
                    index=i;
                }
            }
        }
        for (j = 0; j < N; j++) {
            cmp = (j - index + N) % N;
            if (degree[j] >= 0 && cmp <= cmpdegree[j])
                degree[j]--;
        }
        a[k] = min;
        k++;
    }
    for (k = 0; k < N; k++) {
        if (a[k] == -1)
            break;
        if (k != 0)
            printf(" ");
        printf("%d", a[k]);
    }
    return 0;
}