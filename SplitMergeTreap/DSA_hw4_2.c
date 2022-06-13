#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define ll long long
#define max_node 100000*5
#define INF 0x3f3f3f3f
/*
int seed = 233;
inline int rand(){
    
    return seed = int (seed * 48271LL % 2147483647);
}*/

int max(int a, int b){
    if (a > b){
        return a;
    }else{
        return b;
    }
}

int min(int a, int b){
    if (a < b){
        return a;
    }else{
        return b;
    }
}

void swap(int *a, int *b){
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

struct Treap{
    int value;
    int priority;
    int lazy;
    bool reverse;
    int size;
    ll sum;
    int right;
    int left;
    int max_treap;
    int sec_treap;
    int max_num;
};
typedef struct Treap treap;

treap fhq[max_node];

int cnt, root;

void init(){
    root = 0;
    cnt = 0;
    fhq[cnt].value = -INF;
    fhq[cnt].priority = 0;
    fhq[cnt].lazy = -INF;
    fhq[cnt].reverse = false;
    fhq[cnt].size = 0;
    fhq[cnt].sum = 0;
    fhq[cnt].right = 0;
    fhq[cnt].left = 0;
    fhq[cnt].max_treap = 0;
    fhq[cnt].sec_treap = 0;
    fhq[cnt].max_num = 0;
}

int create(int val){
    ++cnt;
    fhq[cnt].value = val;
    fhq[cnt].priority = rand();
    fhq[cnt].lazy = -INF;
    fhq[cnt].reverse = false;
    fhq[cnt].size = 1;
    fhq[cnt].sum = val;
    fhq[cnt].right = 0;
    fhq[cnt].left = 0;
    fhq[cnt].max_treap = val;
    fhq[cnt].sec_treap = 0;
    fhq[cnt].max_num = 1;
    return cnt;
}

void NIL(){
    fhq[0].value = -INF;
    fhq[0].priority = 0;
    fhq[0].lazy = -INF;
    fhq[0].reverse = false;
    fhq[0].size = 0;
    fhq[0].sum = 0;
    fhq[0].right = 0;
    fhq[0].left = 0;
    fhq[0].max_treap = 0;
    fhq[0].sec_treap = 0;
    fhq[0].max_num = 0;
}


void push_up(int cur){
    // leaf
    if (fhq[cur].left == 0 && fhq[cur].right == 0){
        fhq[cur].sum = fhq[cur].value;
        fhq[cur].size = 1;
        fhq[cur].max_treap = fhq[cur].value;
        fhq[cur].sec_treap = 0;
        fhq[cur].max_num = 1;
        return;
    }
    fhq[cur].sum = fhq[fhq[cur].left].sum + fhq[fhq[cur].right].sum + fhq[cur].value;
    fhq[cur].size = fhq[fhq[cur].left].size + fhq[fhq[cur].right].size + 1;
    

   if (fhq[fhq[cur].left].max_treap == fhq[fhq[cur].right].max_treap){
        if (fhq[cur].value > fhq[fhq[cur].right].max_treap){
            fhq[cur].max_treap = fhq[cur].value;
            fhq[cur].sec_treap = max(fhq[fhq[cur].right].max_treap, fhq[fhq[cur].left].max_treap);
            fhq[cur].max_num = 1;

        }
        else if (fhq[cur].value == fhq[fhq[cur].right].max_treap){
            fhq[cur].max_treap = fhq[cur].value;
            fhq[cur].sec_treap = max(fhq[fhq[cur].right].sec_treap, fhq[fhq[cur].left].sec_treap);
            fhq[cur].max_num = fhq[fhq[cur].left].max_num + fhq[fhq[cur].right].max_num + 1;

        }
        else if (fhq[cur].value < fhq[fhq[cur].right].max_treap){
            fhq[cur].max_treap = fhq[fhq[cur].right].max_treap;
            fhq[cur].sec_treap = max(max(fhq[fhq[cur].right].sec_treap, fhq[fhq[cur].left].sec_treap), fhq[cur].value);
            fhq[cur].max_num = fhq[fhq[cur].left].max_num + fhq[fhq[cur].right].max_num;
        }
    }
    else if (fhq[fhq[cur].left].max_treap > fhq[fhq[cur].right].max_treap){
        if (fhq[cur].value > fhq[fhq[cur].left].max_treap){
            fhq[cur].max_treap = fhq[cur].value;
            fhq[cur].sec_treap = fhq[fhq[cur].left].max_treap;
            fhq[cur].max_num = 1;
            
        }
        else if (fhq[cur].value == fhq[fhq[cur].left].max_treap){
            fhq[cur].max_treap = fhq[cur].value;
            fhq[cur].sec_treap = max(fhq[fhq[cur].right].max_treap, fhq[fhq[cur].left].sec_treap);
            fhq[cur].max_num = fhq[fhq[cur].left].max_num + 1;
        }
        else if (fhq[cur].value < fhq[fhq[cur].left].max_treap){
            fhq[cur].max_treap = fhq[fhq[cur].left].max_treap;
            fhq[cur].sec_treap = max(max(fhq[fhq[cur].right].max_treap, fhq[fhq[cur].left].sec_treap), fhq[cur].value);
            fhq[cur].max_num = fhq[fhq[cur].left].max_num;
        }
    }
    else{
        if (fhq[cur].value > fhq[fhq[cur].right].max_treap){
            fhq[cur].max_treap = fhq[cur].value;
            fhq[cur].sec_treap = fhq[fhq[cur].right].max_treap;
            fhq[cur].max_num = 1;
        }
        else if (fhq[cur].value == fhq[fhq[cur].right].max_treap){
            fhq[cur].max_treap = fhq[cur].value;
            fhq[cur].sec_treap = max(fhq[fhq[cur].left].max_treap, fhq[fhq[cur].right].sec_treap);
            fhq[cur].max_num = fhq[fhq[cur].right].max_num + 1;
        }
        else if (fhq[cur].value < fhq[fhq[cur].right].max_treap){
            fhq[cur].max_treap = fhq[fhq[cur].right].max_treap;
            fhq[cur].sec_treap = max(max(fhq[fhq[cur].left].max_treap, fhq[fhq[cur].right].sec_treap), fhq[cur].value);
            fhq[cur].max_num = fhq[fhq[cur].right].max_num;
        }
    }
       
}



void cover (int cur, int tag){
    if (fhq[cur].value > tag){
        fhq[cur].value = tag;
    }
    fhq[cur].sum = fhq[cur].sum + ((ll)(tag - fhq[cur].max_treap) * fhq[cur].max_num);
    fhq[cur].max_treap = fhq[cur].lazy = tag;
}

void upcase (int cur, int tag){ 
    if (fhq[cur].max_treap <= tag){
        return;
    }
    cover(cur, tag);
}

void down (int cur){
    if (fhq[cur].lazy != -INF){
        upcase(fhq[cur].left, fhq[cur].lazy);
        upcase(fhq[cur].right, fhq[cur].lazy);
        fhq[cur].lazy = -INF;
    }
} 

void update (int cur, int tag){
    if (fhq[cur].value > tag){
        fhq[cur].value = tag;
    }
    if (fhq[cur].max_treap <= tag){
        return;
    }
    if (fhq[cur].sec_treap < tag){
        cover(cur, tag);
        return;
    }
    
    down(cur);
    update(fhq[cur].left, tag);
    update(fhq[cur].right, tag);
    push_up(cur);
}


void push_down(int cur){
    if (fhq[cur].lazy != -INF){
        
        down(cur);
    }
    if (fhq[cur].reverse){
        swap(&fhq[fhq[cur].left].left, &fhq[fhq[cur].left].right);
        swap(&fhq[fhq[cur].right].left, &fhq[fhq[cur].right].right);
        fhq[fhq[cur].left].reverse ^= 1;
        fhq[fhq[cur].right].reverse ^= 1;
        fhq[cur].reverse = false;
    }
    NIL();
}

void fhq_print(){
    for (int cur = 1; cur<=cnt; cur++){
        printf("fhq[%d] value: %d, sum: %d, left: %d, right: %d, max: %d, maxnum: %d, sec: %d, lazy: %d\n", cur, fhq[cur].value, fhq[cur].sum, fhq[cur].left, fhq[cur].right, fhq[cur].max_treap, fhq[cur].max_num, fhq[cur].sec_treap, fhq[cur].lazy);
    }
}


int merge(int a, int b){
    if (a == 0 || b == 0){
        return a + b;
    }
    push_down(a);
    push_down(b);
    if (fhq[a].priority > fhq[b].priority){
        fhq[a].right = merge(fhq[a].right, b);
        push_up(a);
        return a;
    }else{
        fhq[b].left = merge(a, fhq[b].left);
        push_up(b);
        return b;
    }
}

void split(int cur, int k, int *a, int *b){
    if (cur == 0){
        *a = *b = 0;
        return;
    }
    push_down(cur);
    
    if (k <= fhq[fhq[cur].left].size){
        *b = cur;
        split(fhq[cur].left, k, a, &fhq[*b].left);
        push_up(*b);
    }else{
        *a = cur;
        split(fhq[cur].right, k - fhq[fhq[cur].left].size - 1, &fhq[*a].right, b);
        push_up(*a);
    }
}

void insert (int pos, int rt){
    int x, y;
    split(root, pos , &x, &y);
    root = merge (merge(x, rt), y);
}



void modify(int pos, int len, int mod){
    int x, y, z;
    split(root, pos - 1, &x, &y);
    split(y, len, &y, &z);
    update(y, mod);
    root = merge(merge(x, y), z);
}

void del (int pos, int len){
    int x, y, z;
    split(root, pos - 1, &x, &y);
    split(y, len, &y, &z);
    root = merge(x, z);
}

ll query(int l, int len){
    int x, y, z;
    split(root, l - 1, &x, &y);
    split(y, len, &y, &z);
    ll ret = fhq[y].sum;
    root = merge(merge(x, y), z);
    return ret;
}

void print(int cur){
    if (cur == 0){
        return;
    }
    push_down(cur);
    print(fhq[cur].left);
    printf("fhq[%d] value: %d, sum: %d, left: %d, right: %d, max: %d, maxnum: %d, sec: %d\n", cur, fhq[cur].value, fhq[cur].sum, fhq[cur].left, fhq[cur].right, fhq[cur].max_treap, fhq[cur].max_num, fhq[cur].sec_treap);
    print(fhq[cur].right);
    push_up(cur);
}


void operation(int cur, int k){
    if (cur == 0){
        return;
    }
    push_down(cur);
    if (k < fhq[cur].value){
        fhq[cur].value = k;
    }
    operation(fhq[cur].left, k);
    operation(fhq[cur].right, k);
    push_up(cur);
}

void brutal(int pos, int len, int mod){
    int x, y, z;
    split(root, pos - 1, &x, &y);
    split(y, len, &y, &z);
    operation(y, mod);
    root = merge(merge(x, y), z);
}

void build(int x){
    root = merge(root, create(x));
}

void reverse(int pos, int len){
    int x, y, z;
    split(root, pos - 1, &x, &y);
    split(y, len, &y, &z);
    fhq[y].reverse ^= 1;
    swap(&fhq[y].left, &fhq[y].right);
    root = merge(merge(x, y), z);
}

void change (int pos1, int len1, int pos2, int len2){
    if (pos1 < pos2){
        int x1, y1, z1;
        split(root, pos1 - 1, &x1, &y1);
        split(y1, len1, &y1, &z1);
        int x2, y2, z2;
        root = z1;
        split(root, pos2 - pos1 - len1, &x2, &y2);
        split(y2, len2, &y2, &z2);
        //root = y2;
        root = merge(merge(x1, y2), x2);
        root = merge(merge(root, y1), z2);
    }else{
        int x1, y1, z1;
        split(root, pos2 - 1, &x1, &y1);
        split(y1, len2, &y1, &z1);
        int x2, y2, z2;
        root = z1;
        split(root, pos1 - pos2 - len2, &x2, &y2);
        split(y2, len1, &y2, &z2);
        //root = y2;
        root = merge(merge(x1, y2), x2);
        root = merge(merge(root, y1), z2);
    }
    


}

void test(int a, int b, int mod, ll *arr){
    for (int i = a; i<=b ; i++){
        if (mod < arr[i]){
            arr[i] = mod;
        }
    }
}
ll test_query(int a, int b, ll *arr){
    ll sum = 0;
    for (int i = a; i<=b; i++){
        sum += arr[i];
    }
    return sum;
}
//ll q1[max_node], ll[max_node];
//ll arr[max_node];

int main(){
    int N, Q, a, issue, p, k, l, r, x, y;
    //
    
    int qq = 0;
    //
    init();
    scanf("%d%d", &N, &Q);
    for (int i = 1; i<=N; i++){
        scanf("%d", &a);
        build(a);
        //arr[i] = a;
    }
        
    //fhq_print();
    for (int i = 1; i <= Q ; i++){
        
        scanf("%d", &issue);
        if (issue == 1){
            scanf("%d%d", &p, &k);
            int rt = 0;
            rt = merge(rt, create(k));
            insert(p, rt);
        }
        else if(issue == 2){
            scanf("%d", &p);
            del(p, 1);
        }
        else if(issue == 3){
            scanf("%d%d", &l, &r);
            reverse(l, r-l+1);
        }
        else if(issue == 4){
            scanf("%d%d%d%d", &l, &r, &x, &y);
            change(l, r-l+1, x, y-x+1);
        }
        else if(issue == 5){
            scanf("%d%d%d", &l, &r, &k);
            modify(l, r-l+1, k);
            //test(l, r, k, arr);
        }
        else{
            scanf("%d%d", &l, &r);
            printf("%lld\n", query(l, r-l+1));
            
            //
            //q1[qq] = query(l, r-l+1);
            //q2[qq] = test_query(l, r, arr);
            //qq++;
            //
            //printf("%lld\n", test_query(l, r, arr));

        }
    }
    /*
    fhq_print();
    for (int i = 0; i<qq; i++){
        if (q1[i] != q2[i]){
            printf("false\n");
            return 0;
        }
    }
    printf("true\n");
    */
    //fhq_print();

    //printf("max: %d\n", fhq[5].max_num);
    //print(root);
    //printf("\n");
    return 0;
}
