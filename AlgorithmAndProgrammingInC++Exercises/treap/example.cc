namespace Treap {
    static const int N=60005;
    struct node *null;
    struct node {
        node *c[2];
        int s, val, key;
        void init(int _val, int _key) {
            c[0]=c[1]=null;
            val=_val;
            key=_key;
            s=1;
        }
        void up() {
            s=c[0]->s+c[1]->s+1;
        }
    }*Po, *iT=Po;
    node *newnode(int val=0, int key=rand()) {
        static const int L=60005;
        if(iT==Po) {
            Po=new node[L];
            iT=Po+L;
        }
        node *x=--iT;
        x->init(val, key);
        return x;
    }
    void rot(node *&x, bool d) {
        node *y=x->c[!d];
        x->c[!d]=y->c[d];
        y->c[d]=x;
        x->up();
        y->up();
        x=y;
    }
    void ins(node *&x, int val) {
        if(x==null) {
            x=newnode(val);
            return;
        }
        bool d=val>x->val;
        ins(x->c[d], val);
        if(x->c[d]->key<x->key) {
            rot(x, !d);
        }
        else {
            x->up();
        }
    }
    void del(node *&x, int val) {
        if(x==null) {
            return;
        }
        bool d=val>x->val;
        if(x->val==val) {
            d=x->c[0]->key>x->c[1]->key;
            if(x->c[d]==null) {
                x=null;
                return;
            }
            rot(x, !d);
            del(x->c[!d], val);
        }
        else {
            del(x->c[d], val);
        }
        x->up();
    }
    int _rd[N], _rnow;
    node *_build(int l, int r, int *key) {
        if(l>r) {
            return null;
        }
        int mid=(l+r)>>1;
        node *x=newnode(key[mid], _rd[++_rnow]);
        x->c[0]=_build(l, mid-1, key);
        x->c[1]=_build(mid+1, r, key);
        x->up();
        return x;
    }
    node *build(int *key, int n) {
        for(int i=1; i<=n; ++i) {
            _rd[i]=rand();
        }
        sort(_rd+1, _rd+1+n);
        _rnow=0;
        return _build(1, n, key);
    }
    int ask(node *x, int val) {
        if(x==null) {
            return 0;
        }
        bool d=x->val>val;
        return (d?x->c[1]->s+1:0)+ask(x->c[!d], val);
    }
    void init() {
        srand(2333);
        null=new node();
        null->init(0, ~0u>>1);
        null->s=0;
    }
}