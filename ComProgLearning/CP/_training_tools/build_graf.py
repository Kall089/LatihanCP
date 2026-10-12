#!/usr/bin/env python3
"""Reproducible, seeded graph training packs. Run from any directory."""
from pathlib import Path
import random, collections, itertools, json

ROOT = Path(__file__).resolve().parents[1]
RNG = random.Random(20260905)
HEADER = '''#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <algorithm>
#include <numeric>
#include <functional>
#include <string>
#include <tuple>
#include <utility>
#include <limits>
using namespace std;
using ll = long long;
const ll INF = 4000000000000000000LL;
'''
DSU = '''struct DSU {
 vector<int> p,sz;
 DSU(int n):p(n),sz(n,1){iota(p.begin(),p.end(),0);}
 int find(int x){while(x!=p[x]){p[x]=p[p[x]];x=p[x];}return x;}
 bool join(int a,int b){a=find(a);b=find(b);if(a==b)return false;if(sz[a]<sz[b])swap(a,b);p[b]=a;sz[a]+=sz[b];return true;}
};
'''
SCC = '''// Tarjan: hanya tetangga yang masih aktif boleh menurunkan low-link.
vector<int> scc(const vector<vector<int>>& g){
 int n=g.size(),timer=0,cc=0; vector<int> tin(n,-1),low(n),active(n),st,id(n,-1);
 function<void(int)> dfs=[&](int u){
  tin[u]=low[u]=timer++;st.push_back(u);active[u]=1;
  for(int v:g[u]){if(tin[v]<0){dfs(v);low[u]=min(low[u],low[v]);}else if(active[v])low[u]=min(low[u],tin[v]);}
  if(low[u]==tin[u]){while(true){int v=st.back();st.pop_back();active[v]=0;id[v]=cc;if(v==u)break;}++cc;}
 };
 for(int u=0;u<n;++u)if(tin[u]<0)dfs(u);return id;
}
'''
DINIC = '''struct Dinic {
 struct Edge{int v,rev;ll cap;};int n;vector<vector<Edge>>g;vector<int>level,ptr;
 Dinic(int n):n(n),g(n),level(n),ptr(n){}
 void add(int u,int v,ll c){if(u==v)return;int a=g[u].size(),b=g[v].size();g[u].push_back({v,b,c});g[v].push_back({u,a,0});}
 bool bfs(int s,int t){fill(level.begin(),level.end(),-1);queue<int>q;q.push(s);level[s]=0;while(!q.empty()){int u=q.front();q.pop();for(auto e:g[u])if(e.cap>0&&level[e.v]<0){level[e.v]=level[u]+1;q.push(e.v);}}return level[t]>=0;}
 ll dfs(int u,int t,ll f){if(u==t)return f;for(int &i=ptr[u];i<(int)g[u].size();++i){auto &e=g[u][i];if(e.cap<=0||level[e.v]!=level[u]+1)continue;ll pushed=dfs(e.v,t,min(f,e.cap));if(pushed){e.cap-=pushed;g[e.v][e.rev].cap+=pushed;return pushed;}}return 0;}
 ll flow(int s,int t){ll ans=0;while(bfs(s,t)){fill(ptr.begin(),ptr.end(),0);while(ll f=dfs(s,t,INF))ans+=f;}return ans;}
};
'''

def ints(s): return list(map(int,s.split()))
def grid(rows, extra=''): return f'{len(rows)} {len(rows[0])}'+(f' {extra}' if extra else '')+'\n'+'\n'.join(rows)+'\n'
def graph(n,edges,extra='',prefix=''):
    return f'{n} {len(edges)}'+(f' {extra}' if extra else '')+'\n'+prefix+''.join(' '.join(map(str,e))+'\n' for e in edges)
def reach(n,edges):
    a=[[i==j for j in range(n)] for i in range(n)]
    for e in edges:a[e[0]-1][e[1]-1]=True
    for k in range(n):
        for i in range(n):
            if a[i][k]:
                for j in range(n):a[i][j]|=a[k][j]
    return a
def components(n,edges,skipedge=-1,skipvertex=-1):
    g=[[] for _ in range(n)]
    for i,e in enumerate(edges):
        u,v=e[0]-1,e[1]-1
        if i==skipedge or skipvertex in (u,v):continue
        g[u].append(v);g[v].append(u)
    seen={skipvertex};ans=[]
    for s in range(n):
        if s in seen:continue
        q=[s];seen.add(s)
        for u in q:
            for v in g[u]:
                if v not in seen:seen.add(v);q.append(v)
        ans.append(q)
    return ans

PACKS=[]
def add(day,title,ppt,theory,problems,tasks):
    PACKS.append(dict(day=day,title=title,ppt=ppt,theory=theory,problems=problems,tasks=tasks))
def problem(title,level,story,io,limits,cpp,oracle,cases,idea,proof,complexity,traps):
    assert len(cases)>=8
    return dict(title=title,level=level,story=story,io=io,limits=limits,cpp=HEADER+cpp,oracle=oracle,cases=cases,idea=idea,proof=proof,complexity=complexity,traps=traps)

# 117: implicit graphs; the independent oracle explores with a Python stack.
def grid_regions(rows):
    n,m=len(rows),len(rows[0]);seen=set();out=[]
    for r in range(n):
        for c in range(m):
            if rows[r][c]!='.' or (r,c) in seen:continue
            q=[(r,c)];seen.add((r,c));cells=[];perimeter=0
            while q:
                x,y=q.pop();cells.append((x,y))
                for dx,dy in ((1,0),(-1,0),(0,1),(0,-1)):
                    a,b=x+dx,y+dy
                    if not(0<=a<n and 0<=b<m) or rows[a][b]=='#':perimeter+=1
                    elif (a,b) not in seen:seen.add((a,b));q.append((a,b))
            out.append((cells,perimeter))
    return out
def flood_oracle(mode,s):
    z=s.split();n,m=map(int,z[:2]);rows=z[2:];rs=grid_regions(rows)
    if mode==1:return f'{len(rs)} {max([len(x) for x,p in rs]+[0])}\n'
    if mode==2:return f'{max([p for x,p in rs]+[0])}\n'
    ans=max([len(x) for x,p in rs]+[0])
    for r in range(n):
        for c in range(m):
            if rows[r][c]=='#':
                b=rows.copy();b[r]=b[r][:c]+'.'+b[r][c+1:]
                ans=max(ans,max(len(x) for x,p in grid_regions(b)))
    return f'{ans}\n'
def flood_cpp(mode):
    return '''int main(){ios::sync_with_stdio(false);cin.tie(nullptr);
 int n,m;cin>>n>>m;vector<string>a(n);for(auto&s:a)cin>>s;
 vector<vector<int>>id(n,vector<int>(m,-1));vector<int>sz,per;int dx[]={1,-1,0,0},dy[]={0,0,1,-1};
 for(int r=0;r<n;++r)for(int c=0;c<m;++c)if(a[r][c]=='.'&&id[r][c]<0){
  int k=sz.size(),cnt=0,p=0;queue<pair<int,int>>q;q.push({r,c});id[r][c]=k;
  while(!q.empty()){auto[x,y]=q.front();q.pop();++cnt;for(int d=0;d<4;++d){int u=x+dx[d],v=y+dy[d];if(u<0||u>=n||v<0||v>=m||a[u][v]=='#'){++p;continue;}if(id[u][v]<0){id[u][v]=k;q.push({u,v});}}}sz.push_back(cnt);per.push_back(p);
 }
 int best=sz.empty()?0:*max_element(sz.begin(),sz.end());
''' + (''' cout<<sz.size()<<' '<<best<<'\n';
''' if mode==1 else ''' cout<<(per.empty()?0:*max_element(per.begin(),per.end()))<<'\n';
''' if mode==2 else ''' for(int r=0;r<n;++r)for(int c=0;c<m;++c)if(a[r][c]=='#'){
  vector<int>near;for(int d=0;d<4;++d){int x=r+dx[d],y=c+dy[d];if(x>=0&&x<n&&y>=0&&y<m&&id[x][y]>=0)near.push_back(id[x][y]);}
  sort(near.begin(),near.end());near.erase(unique(near.begin(),near.end()),near.end());int cur=1;for(int k:near)cur+=sz[k];best=max(best,cur);
 }cout<<best<<'\n';
''')+'}\n'

def build117():
    cases=[grid(['.']),grid(['#']),grid(['..#','.##','#..']),grid(['.#.','###','.#.']),grid(['...','.#.','...']),grid(['.....']),grid(['.','#','.','#','.']),grid(['####','####'])]
    cases += [grid([''.join(RNG.choice('.#') for _ in range(RNG.randrange(1,7)))])] if False else []
    for _ in range(16):
        n,m=RNG.randint(1,7),RNG.randint(1,7);cases.append(grid([''.join(RNG.choice('.#') for _ in range(m)) for _ in range(n)]))
    ps=[]
    configs=[('Kampung di Atas Peta','Pemanasan','Relawan memetakan tanah kering `.` dan banjir `#`. Satu kampung adalah komponen tanah kering yang terhubung lewat sisi, bukan diagonal. Hitung jumlah kampung dan luas kampung terbesar.','Dua bilangan: jumlah komponen dan luas maksimum. Jika tidak ada tanah, keduanya 0.','Mulai BFS dari setiap sel tanah yang belum diberi label. Hitung ukuran saat memproses antrean.','BFS mencapai tepat sel dalam komponen titik awal; pelabelan saat masuk antrean memastikan setiap sel dihitung sekali. Setiap komponen mempunyai satu titik awal pertama.','Diagonal bukan tetangga; semua banjir menghasilkan 0 0.'),
    ('Pagar Kebun Bersama','Menengah','Setiap komponen `.` merupakan kebun. Setiap sisi sel yang berbatasan dengan `#` atau luar peta membutuhkan satu meter pagar, termasuk tepi lubang di dalam kebun. Cari perimeter terbesar di antara seluruh kebun.','Satu bilangan: perimeter maksimum, atau 0 bila semua sel `#`.','Untuk setiap sel yang diambil BFS, periksa empat arah; arah yang bukan tanah menambah perimeter komponen.','Setiap unit pagar bersisian dengan tepat satu sel kebun dan satu arah keluar. Menghitung arah tersebut menghitung setiap unit sekali.','Keliling lubang ikut dihitung; luas terbesar belum tentu perimeter terbesar.'),
    ('Satu Jembatan Tanah','Tantangan','Pemerintah boleh mengeringkan paling banyak satu sel `#` menjadi `.`. Pilih tindakan agar komponen tanah terbesar sesudahnya seluas mungkin. Boleh tidak mengubah sel.','Satu bilangan: luas komponen terbesar yang mungkin.','Label semua komponen, simpan ukurannya. Untuk setiap `#`, jumlahkan 1 dan ukuran label tetangga yang berbeda.','Komponen baru hanya berisi sel yang dibuka dan komponen lama yang menempel padanya. Semua terhubung lewat sel baru; label sama harus ditambahkan sekali. Memeriksa semua kandidat mencakup setiap keputusan.','Empat tetangga dapat berasal dari satu komponen; deduplikasi label wajib.')]
    for i,(title,lev,story,out,idea,proof,traps) in enumerate(configs,1):
        ps.append(problem(title,lev,story,'Baris pertama `n m`; berikutnya n string panjang m berisi `.` atau `#`.\n\n**Keluaran:** '+out,'1 ≤ n,m ≤ 500.',flood_cpp(i),lambda s,i=i:flood_oracle(i,s),cases,idea,proof,'Waktu O(nm), memori O(nm).',traps))
    add(117,'Connected Component dan Flood Fill pada Grid','Day-117 - Flood Fill & Komponen Terhubung.pptx',
    '''Grid adalah graf implisit: simpul adalah sel yang boleh dilalui, dan sisi berasal dari empat perpindahan ortogonal. Diagonal tidak termasuk kecuali kontrak soal mengatakannya.

**Invarian BFS.** Setiap sel dalam antrean telah mendapat label. Tetangga yang belum berlabel langsung ditandai sebelum dimasukkan. Dengan demikian antrean tidak mempunyai duplikat dan setiap sel diproses sekali. Menyapu seluruh grid menemukan juga komponen yang tidak terjangkau dari sel pertama.

**Trace.** Pada `..# / .## / #..`, mulai (1,1): antrean berturut-turut menemukan (2,1),(1,2); ukuran pertama 3. Sel (3,2) memulai komponen kedua berukuran 2. Hasil 2 komponen, maksimum 3. Pada pola `... / .#. / ...`, delapan tanah berada dalam satu komponen dengan perimeter 16: batas luar 12 dan lubang 4.

**Dari traversal menjadi praproses.** `id[r][c]` dan `size[id]` membuat jawaban lokal murah. Satu sel yang dibuka menyambungkan paling banyak empat label. Dua tetangga dapat punya label sama; mengabaikan deduplikasi akan menggandakan luas.

**Batas dan implementasi.** Luas 500×500 memuat 250.000 sel. Gunakan queue/stack eksplisit; DFS rekursif pada koridor panjang dapat menghabiskan stack. Cek batas koordinat sebelum membaca grid. Waktu O(nm), ruang O(nm).
''',ps,[('Kebun Delapan Arah','Gunakan delapan arah, termasuk diagonal. Input seperti latihan 1. Keluarkan jumlah komponen `.`. Batas n,m ≤ 500.','2 2\n.#\n#.\n','1\n','1 3\n.#.\n','2\n'),('Kolam Tertutup','Grid `.` adalah air, `#` tanah. Hitung total sel air dalam komponen empat arah yang tidak menyentuh tepi peta. Input n m dan grid; n,m ≤ 500.','3 3\n###\n#.#\n###\n','1\n','2 2\n..\n##\n','0\n'),('Kampung Berukuran K','Input n m k, lalu grid. Hitung komponen empat arah `.` yang luasnya minimal k; 1 ≤ k ≤ nm, n,m ≤ 500.','3 3 2\n..#\n###\n.#.\n','1\n','1 1 1\n#\n','0\n')])

def edgecases():
    a=[(1,[]),(1,[(1,1)]),(3,[(1,2),(2,3),(3,1)]),(4,[(1,2),(1,3),(2,4),(3,4)]),(3,[(1,2),(1,2)]),(6,[(4,5),(5,6),(6,4)]),(5,[(i,i+1) for i in range(1,5)]),(4,[])]
    for _ in range(16):
        n=RNG.randint(1,9);a.append((n,[(RNG.randint(1,n),RNG.randint(1,n)) for _ in range(RNG.randint(0,22))]))
    return a
def cycle_oracle(mode,s):
    a=ints(s);n,m=a[:2];e=list(zip(a[2::2],a[3::2]))
    if mode==2:return f'{m-n+len(components(n,e))}\n'
    def cyclic(es):
        r=reach(n,es)
        return any(u==v or r[v-1][u-1] for u,v in es)
    if mode==1:return ('SIKLUS' if cyclic(e) else 'AMAN')+'\n'
    return str(next((i for i in range(1,m+1) if cyclic(e[:i])),0))+'\n'
KAHN='''bool cyclic(int n,const vector<pair<int,int>>&e,int take){vector<vector<int>>g(n);vector<int>d(n);for(int i=0;i<take;++i){auto[u,v]=e[i];g[u].push_back(v);++d[v];}queue<int>q;for(int u=0;u<n;++u)if(!d[u])q.push(u);int done=0;while(!q.empty()){int u=q.front();q.pop();++done;for(int v:g[u])if(--d[v]==0)q.push(v);}return done<n;}
'''
def build118():
    cases=[graph(n,e) for n,e in edgecases()]
    ps=[]
    cfg=[('Antrean Dapur Festival','Pemanasan','Di dapur festival, aturan u v berarti menu u harus selesai sebelum menu v dapat dimulai. Tentukan apakah aturan memuat ketergantungan melingkar.','Graf berarah. Keluarkan `SIKLUS` jika ada siklus, atau `AMAN`.','Jalankan Kahn: masukkan semua simpul dengan indegree nol lalu hapus sisi keluar.','DAG tak kosong selalu punya simpul berderajat masuk nol. Jika algoritma berhenti sebelum semua simpul terhapus, sisa graf mempunyai siklus. Sebaliknya simpul pada siklus tidak dapat menjadi yang pertama dihapus.',KAHN+'''int main(){int n,m;cin>>n>>m;vector<pair<int,int>>e(m);for(auto&[u,v]:e){cin>>u>>v;--u;--v;}cout<<(cyclic(n,e,m)?"SIKLUS":"AMAN")<<'\n';}''','O(n+m) waktu dan memori.','Sisi menuju simpul yang sudah pernah dikunjungi belum tentu siklus: dua cabang dapat bertemu di hilir.'),
    ('Kabel Cadangan Posko','Menengah','Jaringan kabel tak berarah boleh memiliki kabel paralel dan kabel yang kembali ke posko sama. Lepas sesedikit mungkin kabel agar tidak ada siklus; jaringan boleh tetap terpisah.','Graf tak berarah. Keluarkan jumlah minimum sisi yang harus dibuang. Loop panjang 1 dan dua sisi paralel membentuk siklus.','Proses sisi dengan DSU; sisi yang gagal menggabungkan dua komponen dibuang.','Hutan yang mempertahankan keterhubungan awal mempunyai n−c sisi, dengan c jumlah komponen awal. Setiap solusi bebas siklus memiliki paling banyak n−c sisi. DSU menyisakan tepat n−c, sehingga m−n+c penghapusan optimal.',DSU+'''int main(){int n,m;cin>>n>>m;DSU d(n);int removed=0;while(m--){int u,v;cin>>u>>v;if(!d.join(u-1,v-1))++removed;}cout<<removed<<'\n';}''','O((n+m) α(n)) waktu, O(n) memori.','Melewati semua sisi menuju parent simpul membuat dua kabel paralel tak terdeteksi; gunakan ID sisi pada DFS.'),
    ('Aturan yang Membuat Macet','Tantangan','Panitia menambahkan aturan berarah satu demi satu sesuai urutan input. Cari indeks pertama yang membuat jadwal mustahil karena siklus.','Graf berarah. Keluarkan indeks sisi pertama yang menimbulkan siklus, atau 0 jika semua aturan aman.','Predikat “prefix memuat siklus” monoton. Binary search indeks pertama true; tiap pemeriksaan memakai Kahn.','Penambahan sisi tidak menghilangkan siklus. Karena itu semua prefix aman mendahului semua prefix bersiklus. Binary search mempertahankan batas dan menemukan prefix true paling kecil.',KAHN+'''int main(){int n,m;cin>>n>>m;vector<pair<int,int>>e(m);for(auto&[u,v]:e){cin>>u>>v;--u;--v;}if(!cyclic(n,e,m)){cout<<0<<'\n';return 0;}int l=1,r=m;while(l<r){int mid=l+(r-l)/2;if(cyclic(n,e,mid))r=mid;else l=mid+1;}cout<<l<<'\n';}''','O((n+m) log(m+1)) waktu, O(n+m) memori.','Duplicate aturan searah tidak menciptakan siklus sendiri; self-loop langsung menciptakan siklus.')]
    for i,(t,l,story,out,idea,proof,cpp,comp,trap) in enumerate(cfg,1):ps.append(problem(t,l,story,'Baris pertama n m; m baris berikutnya u v, simpul 1..n. Loop dan sisi paralel diizinkan.\n\n**Keluaran:** '+out,'1 ≤ n ≤ 100000; 0 ≤ m ≤ 200000.',cpp,lambda s,i=i:cycle_oracle(i,s),cases,idea,proof,comp,trap))
    add(118,'Deteksi Siklus pada Graf Berarah dan Tak Berarah','Day-118 - Deteksi Siklus & Uji Bipartit.pptx',
    '''**Graf berarah.** Dalam DFS tiga warna, putih belum ditemukan, abu-abu masih berada di stack DFS, hitam telah selesai. Sisi u→v ke abu-abu menutup jalur v→…→u dan membuktikan siklus. Sisi ke hitam dapat merupakan cross/forward edge dan bukan bukti siklus. Untuk n besar, latihan memakai Kahn yang iteratif; hasil terhapus < n tepat ketika ada siklus.

**Graf tak berarah.** DFS harus mengabaikan ID sisi parent, bukan seluruh tetangga dengan nomor parent. Dua sisi paralel adalah siklus panjang dua. Alternatif DSU memproses tiap sisi sekali: jika kedua ujung sudah terhubung, sisi baru menutup siklus. Self-loop selalu gagal union.

**Trace.** Sisi 1→2,1→3,2→4,3→4 adalah DAG walaupun 4 ditemukan dari dua cabang. Tambah 4→1 dan tidak ada simpul indegree nol. Pada dua kabel 1—2, kabel pertama menggabungkan komponen; kabel kedua menutup siklus.

**Hitungan.** Hutan pada n simpul dan c komponen memiliki n−c sisi. Jumlah sisi berlebih m−n+c memberikan ukuran minimum penghapusan, termasuk pada multigraf. Deteksi prefix dapat memakai binary search karena predikat siklus tidak berubah dari true menjadi false setelah sisi ditambahkan.

**Pitfall.** Jalankan traversal dari semua komponen, jangan hanya simpul 1. Siklus ganjil terkait bipartit, tetapi siklus genap juga siklus; kedua pertanyaan tidak identik. PPT yang sama menjadi sumber Day 121 sesuai ROADMAP.
''',ps,[('Sertifikat Pohon','Input n m dan m sisi graf tak berarah, boleh paralel/loop. Keluarkan YA bila graf terhubung dan tanpa siklus, TIDAK selainnya. n≤100000,m≤200000.','1 0\n','YA\n','3 2\n1 2\n1 2\n','TIDAK\n'),('Siklus dari Posko','Input n m s dan sisi berarah. Keluarkan YA jika ada siklus yang dapat dicapai dari s, TIDAK selainnya. n≤100000,m≤200000.','4 3 1\n1 2\n3 4\n4 3\n','TIDAK\n','2 2 1\n1 2\n2 2\n','YA\n'),('Pekerjaan yang Bisa Selesai','Input n m dan aturan u v. Hitung banyak simpul yang terhapus oleh algoritma Kahn. n≤100000,m≤200000.','4 3\n1 2\n2 1\n3 4\n','2\n','3 2\n1 2\n2 3\n','3\n')])

def bip_oracle(mode,s):
    a=ints(s);n,m=a[:2];idx=2;w=[1]*n
    if mode==3:w=a[idx:idx+n];idx+=n
    e=list(zip(a[idx::2],a[idx+1::2]));valid=[]
    for mask in range(1<<n):
        if all(((mask>>(u-1))&1)!=((mask>>(v-1))&1) for u,v in e):valid.append(mask)
    if mode==1:return ('YA' if valid else 'TIDAK')+'\n'
    if mode==2:return str(len(valid)%1000000007)+'\n'
    return str(min((sum(w[i] for i in range(n) if mask>>i&1) for mask in valid),default=-1))+'\n'
def bip_cpp(mode):
    return '''int main(){ios::sync_with_stdio(false);cin.tie(nullptr);int n,m;cin>>n>>m;vector<ll>w(n,1);
'''+('for(auto&x:w)cin>>x;\n' if mode==3 else '')+'''vector<vector<int>>g(n);while(m--){int u,v;cin>>u>>v;--u;--v;g[u].push_back(v);g[v].push_back(u);}vector<int>col(n,-1);bool ok=true;ll ways=1,cost=0;
 for(int s=0;s<n;++s)if(col[s]<0){ll sum[2]={0,0};queue<int>q;q.push(s);col[s]=0;while(!q.empty()){int u=q.front();q.pop();sum[col[u]]+=w[u];for(int v:g[u]){if(col[v]<0){col[v]=col[u]^1;q.push(v);}else if(col[v]==col[u])ok=false;}}ways=ways*2%1000000007;cost+=min(sum[0],sum[1]);}
'''+('cout<<(ok?"YA":"TIDAK")' if mode==1 else 'cout<<(ok?ways:0)' if mode==2 else 'cout<<(ok?cost:-1)')+"<<'\n';}\n"
def build121():
    base=edgecases();ps=[]
    cfg=[('Dua Dapur, Satu Festival','Pemanasan','Setiap pasangan relawan u v harus berada di dapur berbeda. Semua relawan harus ditugaskan ke dapur A atau B. Tentukan apakah mungkin.','YA jika pembagian ada, TIDAK jika tidak.','BFS memberi warna lawan kepada setiap tetangga.','Jika BFS menemukan sisi sewarna, jalur dalam pohon BFS beserta sisi itu membentuk siklus ganjil. Tanpa konflik, pewarnaan yang dibangun memenuhi setiap sisi.'),('Berapa Jadwal Dua Shift','Menengah','Setiap relawan mendapat shift Pagi atau Malam. Pasangan u v wajib berbeda shift. Hitung banyak penugasan; nama shift berbeda, sehingga menukar seluruh shift menghasilkan penugasan lain.','Jumlah penugasan modulo 1000000007.','Graf bipartit dengan c komponen mempunyai 2^c pewarnaan bernama.','Dalam satu komponen, pilihan warna satu akar memaksa seluruh warna lain. Terdapat tepat dua pilihan bila konsisten. Pilihan antar komponen bebas, termasuk simpul terisolasi.'),('Subsidi Shift Malam','Tantangan','Relawan i mendapat subsidi w_i jika ditempatkan di shift Malam; shift Pagi gratis. Setiap pasangan u v harus berbeda shift. Minimumkan total subsidi.','Biaya minimum, atau -1 jika pembagian mustahil.','Jumlahkan biaya pada kedua kelas warna tiap komponen; pilih orientasi dengan total lebih kecil.','Setiap komponen bipartit mempunyai tepat dua orientasi warna. Biaya global adalah jumlah biaya tiap komponen yang independen; memilih minimum lokal memberi minimum global.')]
    for i,(t,l,story,out,idea,proof) in enumerate(cfg,1):
        cs=[graph(n,e,prefix=(' '.join(str(RNG.randint(0,50)) for _ in range(n))+'\n') if i==3 else '') for n,e in base]
        ps.append(problem(t,l,story,'Baris pertama n m. '+('Baris kedua n biaya w_i. ' if i==3 else '')+'Berikutnya m pasangan u v tak berarah. Loop dan sisi paralel boleh.\n\n**Keluaran:** '+out,'1 ≤ n ≤ 100000; 0 ≤ m ≤ 200000; 0 ≤ w_i ≤ 10^9.',bip_cpp(i),lambda s,i=i:bip_oracle(i,s),cs,idea,proof,'O(n+m) waktu, O(n+m) memori.','Periksa semua komponen. Self-loop selalu mustahil. Simpul terisolasi memberi faktor 2 untuk menghitung cara, tetapi biaya minimum 0.'))
    add(121,'Uji Bipartit dan 2-Coloring','Day-118 - Deteksi Siklus & Uji Bipartit.pptx',
    '''Graf bipartit mempunyai pembagian dua kelas sehingga setiap sisi melintasi kelas. Algoritma BFS menyimpan color[u]∈{−1,0,1}; −1 belum diberi warna. Mulai setiap komponen dari warna 0 dan berikan color[v]=color[u] XOR 1. Sisi dengan ujung sewarna adalah konflik.

**Teorema.** Graf bipartit jika dan hanya jika tidak memiliki siklus ganjil. Pada pewarnaan sah, berjalan sepanjang siklus harus berganti warna setiap langkah sehingga panjangnya genap. Sebaliknya, jika BFS menemukan konflik, kedua jalur dari leluhur bersama menuju ujung sisi ditambah sisi konflik membentuk siklus ganjil.

**Trace.** Pada rantai 1—2—3, warna 0,1,0 sah. Tambah sisi 3—1: kedua ujung 0, sehingga mustahil. Empat simpul melingkar mendapat 0,1,0,1, tetap sah. Dua simpul terisolasi dapat diwarnai secara independen dan menghasilkan 4 penugasan.

**Aplikasi.** Bila komponen bipartit berjumlah c, ada 2^c pewarnaan dengan dua warna bernama. Bila biaya hanya dibayar untuk satu warna, hitung total kedua sisi dan ambil yang lebih kecil per komponen. Warna sebuah simpul terisolasi dapat dipilih gratis.

**Implementasi.** Queue eksplisit aman pada rantai 100.000 simpul. Gunakan long long untuk biaya; maksimum 10^14. Paralel tidak mengubah konsistensi, tetapi self-loop langsung konflik. Materi ini mengambil bagian bipartit PPT bernomor 118; penempatan Day 121 mengikuti ROADMAP.
''',ps,[('Shift Relawan yang Dikunci','Input n m k, m pasangan berbeda shift, lalu k baris v c (c 0=Pagi,1=Malam). Setiap simpul dikunci paling sekali. Hitung penugasan memenuhi semuanya modulo 1000000007. n≤100000,m≤200000.','3 1 1\n1 2\n1 0\n','2\n','2 1 2\n1 2\n1 0\n2 0\n','0\n'),('Warna Deterministik','Input n m, lalu m sisi tak berarah. Jika mustahil keluarkan TIDAK; jika mungkin keluarkan string n bit dengan urutan leksikografis terkecil. n≤100000,m≤200000.','3 1\n1 2\n','010\n','1 1\n1 1\n','TIDAK\n'),('Komponen yang Bermasalah','Input n m dan sisi tak berarah. Keluarkan jumlah komponen terhubung yang tidak bipartit. n≤100000,m≤200000.','4 3\n1 2\n2 3\n3 1\n','1\n','4 2\n1 2\n3 4\n','0\n')])

def state_oracle(mode,s):
    import heapq
    lines=s.splitlines();a=ints(lines[0]);n,m=a[:2];k=a[2] if mode==1 else 0;rows=lines[1:]
    start=next((r,c) for r in range(n) for c in range(m) if rows[r][c]=='S')
    dist={(*start,0):0};pq=[(0,*start,0)]
    while pq:
        d,r,c,z=heapq.heappop(pq)
        if dist[(r,c,z)]!=d:continue
        if rows[r][c]=='T':return f'{d}\n'
        moves=[(1,0),(-1,0),(0,1),(0,-1)]+([(0,0)] if mode==2 else [])
        for dr,dc in moves:
            x,y=r+dr,c+dc
            if not(0<=x<n and 0<=y<m):continue
            ch=rows[x][y];v=z
            if mode==1:
                v+=ch=='#'
                if v>k:continue
            elif mode==2:
                if ch=='#':continue
                v=(d+1)%2
                if (dr or dc) and ch in '01' and int(ch)!=v:continue
            else:
                if ch=='#' or (ch in 'ABCDEF' and not z>>(ord(ch)-65)&1):continue
                if ch in 'abcdef':v|=1<<(ord(ch)-97)
            node=(x,y,v)
            if d+1<dist.get(node,10**9):dist[node]=d+1;heapq.heappush(pq,(d+1,x,y,v))
    return '-1\n'
def state_cpp(mode):
    return '''int main(){int n,m,k=0;cin>>n>>m;
'''+('cin>>k;\n' if mode==1 else '')+'''vector<string>a(n);for(auto&s:a)cin>>s;int layers='''+('k+1' if mode==1 else '2' if mode==2 else '64')+''';vector<int>d(n*m*layers,-1);auto id=[&](int r,int c,int z){return (r*m+c)*layers+z;};queue<tuple<int,int,int>>q;
for(int r=0;r<n;++r)for(int c=0;c<m;++c)if(a[r][c]=='S'){q.push({r,c,0});d[id(r,c,0)]=0;}
int dx[]={1,-1,0,0,0},dy[]={0,0,1,-1,0};while(!q.empty()){auto[r,c,z]=q.front();q.pop();int cur=d[id(r,c,z)];if(a[r][c]=='T'){cout<<cur<<'\n';return 0;}for(int j=0;j<'''+('5' if mode==2 else '4')+''';++j){int x=r+dx[j],y=c+dy[j],v=z;if(x<0||x>=n||y<0||y>=m)continue;char ch=a[x][y];
'''+('''v+=(ch=='#');if(v>k)continue;''' if mode==1 else '''if(ch=='#')continue;v=(cur+1)%2;if(j<4&&(ch=='0'||ch=='1')&&ch-'0'!=v)continue;''' if mode==2 else '''if(ch=='#')continue;if(ch>='A'&&ch<='F'&&!(z&(1<<(ch-'A'))))continue;if(ch>='a'&&ch<='f')v|=1<<(ch-'a');''')+'''if(d[id(x,y,v)]<0){d[id(x,y,v)]=cur+1;q.push({x,y,v});}}}cout<<-1<<'\n';}
'''
def build124():
    configs=[('Relawan dan Tiket Tembok','Pemanasan','Relawan bergerak dari S ke T. Setiap masuk ke sel # menghabiskan satu tiket; tersedia k tiket. Tembok tidak berubah setelah dilewati, sehingga masuk lagi menghabiskan tiket lagi. Semua langkah empat arah memakan satu menit.','Baris pertama n m k, lalu n baris grid dengan karakter S,T,.,#.','0 ≤ k ≤ 8; 1 ≤ n,m ≤ 120; nm ≥ 2.','State (r,c,b) menyimpan banyak tiket yang telah dipakai.','Posisi yang sama dengan pemakaian tiket berbeda mempunyai pilihan masa depan berbeda. Setiap langkah sah tepat bersesuaian dengan satu sisi state graph. BFS memberi jumlah langkah minimum pada graf tersebut.','O(nm(k+1)) waktu dan memori.',['S#T','S.T','S##T']),('Gerbang Pasang Surut','Menengah','Mulai di S pada waktu 0. Bergerak empat arah atau menunggu satu menit di sel saat ini. # tidak dapat dilalui. Sel 0 hanya boleh dimasuki pada waktu genap, sel 1 hanya pada waktu ganjil. Menunggu di sel gerbang selalu boleh; aturan hanya berlaku ketika masuk dari sel lain.','Baris pertama n m, lalu grid berisi S,T,.,#,0,1.','1 ≤ n,m ≤ 200; nm ≥ 2.','State (r,c,waktu mod 2). Sertakan transisi menunggu.','Dua kedatangan dengan paritas sama memiliki pilihan kelanjutan identik. BFS menemukan kedatangan terawal pada setiap state; semua transisi mempunyai durasi satu.','O(nm) waktu dan memori.',['S0T','S1T','S#T']),('Kunci Museum Kota','Tantangan','Mulai di S dengan kantong kosong. Huruf a..f adalah kunci yang diambil otomatis dan dapat dipakai selamanya. Gerbang A..F membutuhkan kunci huruf kecil pasangannya sebelum dimasuki. Kunci tidak hilang dari peta. # adalah tembok. Bergerak empat arah, satu menit per langkah.','Baris pertama n m, lalu grid berisi S,T,.,#,a..f,A..F. Kunci/gerbang boleh muncul berulang atau tidak muncul.','1 ≤ n,m ≤ 100; nm ≥ 2.','State (r,c,mask) memuat seluruh enam bit kunci.','Kumpulan kunci menentukan semua pintu yang boleh dilalui. State yang sama mempunyai masa depan sama, sehingga satu jarak minimum cukup. Mengambil kunci memperbarui mask sebelum menandai visited.','O(64nm) waktu dan memori.',['SaAT','SAT','S.aAT'])]
    ps=[]
    for mode,(t,l,story,inp,lim,idea,proof,comp,first) in enumerate(configs,1):
        cases=[grid([x],str(j) if mode==1 else '') for j,x in enumerate(first)]
        cases += [grid(['S.T'], '0' if mode==1 else ''),grid(['S#','#T'],'1' if mode==1 else ''),grid(['S..','##.','T..'],'0' if mode==1 else ''),grid(['S..','.##','..T'],'2' if mode==1 else ''),grid(['S...T'],'0' if mode==1 else '')]
        if mode==3:cases += [grid(['S.A.T','.###.','a....']),grid(['SaB.T','.#.#.','b.A..'])]
        for _ in range(16):
            n,m=RNG.randint(2,6),RNG.randint(2,6);alphabet='..###' if mode==1 else '...#01' if mode==2 else '...#abAB';r=[[RNG.choice(alphabet) for c in range(m)] for i in range(n)];r[0][0]='S';r[-1][-1]='T';cases.append(grid([''.join(x) for x in r],str(RNG.randint(0,3)) if mode==1 else ''))
        ps.append(problem(t,l,story,inp+' Tepat satu S dan satu T.\n\n**Keluaran:** Waktu minimum mencapai T, atau -1 jika tidak mungkin.',lim,state_cpp(mode),lambda s,mode=mode:state_oracle(mode,s),cases,idea,proof,comp,'Visited harus mencakup seluruh state, bukan hanya koordinat. S dan T bukan gerbang huruf. Hitung ukuran ruang state sebelum mengalokasikan.'))
    add(124,'BFS pada State Space - Puzzle, Kunci dan Multi-Layer','Day-124 - BFS pada Ruang State.pptx',
    '''BFS bekerja pada **state**, bukan harus pada lokasi fisik. State harus menyimpan tepat informasi yang memengaruhi langkah berikutnya: jumlah tiket, waktu modulo periode, kumpulan kunci. Dua riwayat boleh digabung bila posisi dan seluruh informasi relevan sama.

**Mendesain state.** (1) Tentukan aksi; (2) tulis prasyarat aksi; (3) simpan semua data yang dibutuhkan prasyarat; (4) hitung produk ukuran dimensi; (5) pastikan tiap aksi berbobot sama. Pada tiket, ukuran nm(k+1); paritas 2nm; enam kunci 64nm.

**Trace paritas.** Peta S0T: pada waktu 1 belum boleh masuk 0. Tunggu di S hingga waktu 1, masuk gerbang waktu 2, tiba T waktu 3. Peta S1T selesai waktu 2. Tanpa aksi menunggu, jawaban pertama salah.

**Trace kunci.** Peta SaAT memberi mask 000001 setelah a. Mask tetap 1 ketika masuk A, lalu mencapai T dalam 3 langkah. Pada SAT, tidak ada a sehingga T tak dapat dicapai. Kembali ke posisi lama membawa kunci baru adalah state baru yang sah.

**Bukti BFS.** Setiap rute nyata dapat dipetakan menjadi lintasan di state graph, dan setiap transisi graph dibuat hanya bila aksi nyata sah. Semua sisi berdurasi satu; FIFO memproses jarak meningkat. Kedatangan pertama ke state adalah yang terpendek.

**Pitfall.** Jangan gunakan BFS biasa untuk bobot aksi berbeda. Sisa tiket bukan tembok yang sudah dihancurkan: model tiket dalam latihan sengaja mendefinisikan setiap masuk kembali tetap berbiaya. Menyamakan kedua model tanpa mengubah state menghasilkan jawaban berbeda.
''',ps,[('Portal Sekali Pakai','Input n m lalu grid S,T,.,#,P; tepat dua P. Langkah empat arah berbiaya 1; boleh sekali berpindah dari satu P ke P lainnya dengan biaya 1. Keluarkan waktu minimum S ke T atau -1. n,m≤120.','1 7\nSP#P..T\n','5\n','1 3\nSPT\n','2\n'),('Arah Langkah Bergantian','Input n m dan grid S,T,.,#. Langkah pertama harus horizontal, kedua vertikal, ketiga horizontal, dan seterusnya; tidak boleh menunggu. Keluarkan langkah minimum atau -1. n,m≤150.','2 3\nS..\n..T\n','3\n','1 3\nS.T\n','-1\n'),('Dua Stempel Wajib','Input n m dan grid S,T,.,#,a,b; tepat satu a,b. Sebelum tiba T harus mengunjungi keduanya, urutan bebas. T boleh dilewati sebelum syarat lengkap. Langkah empat arah berbiaya 1. Keluarkan minimum atau -1. n,m≤150.','1 4\nSabT\n','3\n','2 3\nS#T\na#b\n','-1\n')])

def bf_oracle(mode,s):
    a=ints(s);n,m=a[:2];off=2;k=0
    if mode!=3:source,target=a[off]-1,a[off+1]-1;off+=2
    if mode==2:k=a[off];off+=1
    es=list(zip(a[off::3],a[off+1::3],a[off+2::3]))
    if mode==2:
        d=[10**30]*n;d[source]=0
        for _ in range(k):
            nd=d.copy()
            for u,v,w in es:
                if d[u-1]<10**30:nd[v-1]=min(nd[v-1],d[u-1]+w)
            d=nd
        return ('TIDAK' if d[target]==10**30 else str(d[target]))+'\n'
    d=[[10**30]*n for _ in range(n)]
    for i in range(n):d[i][i]=0
    for u,v,w in es:d[u-1][v-1]=min(d[u-1][v-1],w)
    for k in range(n):
        for i in range(n):
            for j in range(n):
                if d[i][k]<10**30 and d[k][j]<10**30:d[i][j]=min(d[i][j],d[i][k]+d[k][j])
    if mode==3:return ('YA' if any(d[i][i]<0 for i in range(n)) else 'TIDAK')+'\n'
    if d[source][target]==10**30:return 'TIDAK\n'
    if any(d[source][i]<10**30 and d[i][i]<0 and d[i][target]<10**30 for i in range(n)):return 'TAK_TERBATAS\n'
    return str(d[source][target])+'\n'
def bf_cpp(mode):
    return '''int main(){int n,m,s=0,t=0,k=0;cin>>n>>m;'''+('cin>>s>>t;--s;--t;' if mode!=3 else '')+('cin>>k;' if mode==2 else '')+'''vector<tuple<int,int,ll>>e;vector<vector<int>>g(n);for(int i=0;i<m;++i){int u,v;ll w;cin>>u>>v>>w;--u;--v;e.push_back({u,v,w});g[u].push_back(v);}vector<ll>d(n,'''+('0' if mode==3 else 'INF')+''');'''+('d[s]=0;' if mode!=3 else '')+('''for(int z=0;z<k;++z){auto nd=d;for(auto[u,v,w]:e)if(d[u]!=INF)nd[v]=min(nd[v],d[u]+w);d.swap(nd);}if(d[t]==INF)cout<<"TIDAK";else cout<<d[t];''' if mode==2 else '''int changed=-1;for(int z=0;z<n;++z){changed=-1;for(auto[u,v,w]:e)if(d[u]!=INF&&d[v]>d[u]+w){d[v]=d[u]+w;changed=v;'''+('' if mode==3 else 'if(z==n-1)bad[v]=1;')+'''}if(changed<0)break;}''')+('''cout<<(changed<0?"TIDAK":"YA");''' if mode==3 else '''queue<int>q;for(int i=0;i<n;++i)if(bad[i])q.push(i);while(!q.empty()){int u=q.front();q.pop();for(int v:g[u])if(!bad[v]){bad[v]=1;q.push(v);}}if(bad[t])cout<<"TAK_TERBATAS";else if(d[t]==INF)cout<<"TIDAK";else cout<<d[t];''' if mode==1 else '')+"cout<<'\n';}\n"
def build129():
    base=[(1,[]),(2,[(1,2,-5)]),(4,[(1,2,1),(2,2,-1),(1,4,7)]),(4,[(1,2,0),(2,3,-1),(3,2,0),(3,4,2)]),(3,[(2,3,-1),(3,2,0)]),(3,[(1,2,3),(1,2,-2),(2,3,4)]),(2,[(1,1,-1),(1,2,0)]),(2,[(1,2,5),(2,1,0)])]
    for n,e in edgecases()[8:]:base.append((n,[(u,v,RNG.randint(-8,12)) for u,v in e]))
    ps=[];cfg=[('Ongkir dengan Cashback','Pemanasan','Ruas pengiriman u→v memiliki biaya w, dapat negatif karena cashback. Paket berangkat dari s menuju t dan boleh mengulang ruas. Tentukan ongkir minimum; jika dapat dibuat sekecil apa pun, nyatakan tak terbatas.','n m s t','Biaya minimum; `TIDAK` jika t tidak terjangkau; `TAK_TERBATAS` jika tak ada batas bawah.','Setelah n−1 putaran, tandai simpul yang masih dapat diperbaiki pada putaran n. Sebarkan tanda melalui sisi keluar dan cek target.','Siklus negatif hanya memengaruhi target bila terjangkau dari sumber dan dapat mencapai target. Relaksasi putaran n menandai pengaruh siklus tersebut; propagasi menemukan seluruh simpul yang ongkirnya tak berbatas.'),('Ekspedisi Maksimal K Etape','Menengah','Paket boleh memakai paling banyak k ruas berarah, dengan biaya negatif maupun positif. Siklus boleh dilewati selama batas ruas dipenuhi. Pilih total biaya minimum dari s ke t. Perjalanan tanpa ruas sah jika s=t.','n m s t k','Biaya minimum atau `TIDAK`.','Gunakan snapshot: nd=d untuk opsi tidak menambah ruas; setiap nd[v] dibarui hanya dari d[u] lapis sebelumnya.','Induksi k: solusi dengan ≤k sisi tidak memakai sisi ke-k, atau memiliki sisi terakhir u→v setelah lintasan dengan ≤k−1 sisi. Kedua pilihan tepat tercakup recurrence.'),('Audit Voucher Nasional','Tantangan','Auditor dapat memulai perjalanan di kota mana pun. Cari apakah ada rangkaian ruas berarah yang kembali ke kota asal dengan total biaya negatif.','n m','YA jika terdapat siklus negatif di bagian mana pun, TIDAK selainnya.','Inisialisasi semua jarak nol, setara sumber super dengan sisi nol ke semua simpul. Cek relaksasi pada putaran n.','Semua simpul kini terjangkau. Tanpa siklus negatif, lintasan minimum sederhana memakai ≤n−1 sisi; perbaikan pada putaran n mustahil. Jika siklus negatif ada, jumlah ketidaksamaan relaksasi di siklus menunjukkan setidaknya satu sisi selalu dapat memperbaiki.')]
    for i,(t,l,story,head,out,idea,proof) in enumerate(cfg,1):
        cases=[graph(n,e,('1 '+str(n)+(f' {j%6}' if i==2 else '')) if i!=3 else '') for j,(n,e) in enumerate(base)]
        cpp=bf_cpp(i)
        if i==1:cpp=cpp.replace('int changed=-1;','vector<int>bad(n);int changed=-1;')
        ps.append(problem(t,l,story,f'Baris pertama {head}; m baris u v w. Graf berarah, simpul 1..n, loop dan sisi paralel boleh.\n\n**Keluaran:** '+out,'1 ≤ n ≤ 250; 0 ≤ m ≤ 2000; |w| ≤ 10^9; 0 ≤ k ≤ 300.',cpp,lambda s,i=i:bf_oracle(i,s),cases,idea,proof,'Waktu O(nm+n+m) untuk deteksi, O(km+n k) untuk batas etape; memori O(n+m).','Jangan menjumlahkan bobot ke INF. Siklus negatif yang tidak menuju target tidak membuat ongkir target tak terbatas. Snapshot wajib untuk pembatasan etape.'))
    add(129,'Bellman-Ford dan Deteksi Negative Cycle','Day-129 - Bellman-Ford & Siklus Negatif.pptx',
    '''Bellman-Ford merelaksasi semua sisi: jika d[u] hingga dan d[v]>d[u]+w, perbarui d[v]. Inisialisasi d[s]=0 dan lainnya INF. Tanpa siklus negatif yang relevan, lintasan optimal dapat dipilih sederhana sehingga cukup n−1 sisi.

**Nuansa penting terhadap slide.** Dengan dua array (snapshot), sesudah putaran k nilai tepat mewakili minimum lintasan dengan paling banyak k sisi. Dengan pembaruan in-place, satu putaran dapat merambat melalui beberapa sisi; yang tetap benar adalah jaminan semua lintasan ≤k sisi sudah dipertimbangkan. Jangan memakai versi in-place untuk batas jumlah etape.

**Trace.** Sisi berurutan 1→2 biaya 3, 2→3 biaya −5: satu putaran in-place sudah memberi d[3]=−2; snapshot putaran pertama masih INF di 3, putaran kedua baru −2. Itulah perbedaan yang diuji latihan 2.

**Siklus negatif.** Relaksasi pada putaran n berarti ada pengaruh siklus negatif terjangkau. Untuk menjawab satu target, sebar semua simpul yang diperbaiki pada putaran n melalui BFS; hanya target bertanda yang tak terbatas. Siklus negatif di komponen lain harus diabaikan. Untuk audit seluruh graf, isi semua d=0.

**Keamanan nilai.** INF=4×10^18 dan cek d[u]!=INF. Batas n=250,m=2000,|w|≤10^9 menjaga seluruh relaksasi in-place jauh di dalam long long, termasuk jika siklus diulang pada tiap putaran. Early stop aman jika tidak ada perubahan.

**Bukti singkat deteksi.** Tanpa siklus negatif, penghapusan siklus tak meningkatkan biaya, sehingga n−1 putaran mencukupi. Di siklus negatif, semua sisi tidak mungkin sekaligus memenuhi d[v]≤d[u]+w: menjumlahkannya akan menyatakan 0≤jumlah negatif. Karena itu relaksasi terus muncul.
''',ps,[('Harga Tepat K Etape','Input n m s t k dan m sisi berarah u v w. Keluarkan biaya minimum dengan tepat k sisi atau TIDAK. n≤200,m≤2000,k≤300,|w|≤10^9; loop/paralel boleh.','2 1 1 2 2\n1 2 3\n','TIDAK\n','1 1 1 1 2\n1 1 -4\n','-8\n'),('Kota Terkena Promo Tak Terbatas','Input n m s dan sisi u v w. Hitung simpul yang ongkir dari s tidak memiliki batas bawah. n≤250,m≤2000,|w|≤10^9.','4 3 1\n1 2 0\n2 2 -1\n2 3 2\n','2\n','2 1 1\n2 2 -1\n','0\n'),('Siklus Negatif yang Pulang','Input n m s dan sisi u v w. Keluarkan YA jika perjalanan dari s dapat kembali ke s dengan biaya negatif, TIDAK selainnya. n≤250,m≤2000,|w|≤10^9.','2 2 1\n1 2 0\n2 2 -1\n','TIDAK\n','2 2 1\n1 2 -3\n2 1 1\n','YA\n')])

def floyd_oracle(mode,s):
    import heapq
    a=ints(s);n,m=a[:2];off=2 if mode==2 else 3;es=[tuple(a[off+3*i:off+3*i+3]) for i in range(m)] if mode!=2 else list(zip(a[off::2],a[off+1::2]))
    if mode==2:
        r=reach(n,es);return str(sum(r[i][j] for i in range(n) for j in range(n) if i!=j))+'\n'
    qs=list(zip(a[off+3*m::2],a[off+3*m+1::2]));g=[[] for _ in range(n)]
    for u,v,w in es:g[u-1].append((v-1,w))
    out=[]
    for s,t in qs:
        d=[10**30]*n;d[s-1]=0;pq=[(0,s-1)]
        while pq:
            x,u=heapq.heappop(pq)
            if x!=d[u]:continue
            for v,w in g[u]:
                nd=x+w if mode==1 else max(x,w)
                if nd<d[v]:d[v]=nd;heapq.heappush(pq,(nd,v))
        out.append(str(-1 if d[t-1]==10**30 else d[t-1]))
    return '\n'.join(out)+'\n'
def floyd_cpp(mode):
    if mode==2:return '''int main(){int n,m;cin>>n>>m;vector<vector<int>>r(n,vector<int>(n));for(int i=0;i<n;++i)r[i][i]=1;while(m--){int u,v;cin>>u>>v;r[u-1][v-1]=1;}for(int k=0;k<n;++k)for(int i=0;i<n;++i)for(int j=0;j<n;++j)r[i][j]|=r[i][k]&&r[k][j];ll ans=0;for(int i=0;i<n;++i)for(int j=0;j<n;++j)if(i!=j)ans+=r[i][j];cout<<ans<<'\n';}'''
    return '''int main(){ios::sync_with_stdio(false);cin.tie(nullptr);int n,m,q;cin>>n>>m>>q;vector<vector<ll>>d(n,vector<ll>(n,INF));for(int i=0;i<n;++i)d[i][i]=0;while(m--){int u,v;ll w;cin>>u>>v>>w;--u;--v;d[u][v]=min(d[u][v],w);}for(int k=0;k<n;++k)for(int i=0;i<n;++i)for(int j=0;j<n;++j)if(d[i][k]!=INF&&d[k][j]!=INF)d[i][j]=min(d[i][j],'''+('d[i][k]+d[k][j]' if mode==1 else 'max(d[i][k],d[k][j])')+''');while(q--){int u,v;cin>>u>>v;ll ans=d[u-1][v-1];cout<<(ans==INF?-1:ans)<<'\n';}}'''
def build131():
    base=edgecases();ps=[]
    cfg=[('Meja Informasi Angkot','Pemanasan','Meja informasi menerima banyak pertanyaan ongkos minimum dari kota u ke kota v pada jaringan angkot berarah. Semua ongkos tak negatif.','Setiap query menghasilkan ongkos minimum, atau -1 jika tidak terjangkau.','Gunakan Floyd-Warshall dengan operasi min dan penjumlahan.','Definisikan D_k(i,j) sebagai rute terpendek dengan simpul perantara dari 1..k. Rute optimal tidak melalui k, atau dipisah menjadi i→k dan k→j. Keduanya tepat recurrence min.'),('Jangkauan Kabar Kampung','Menengah','Kabar dapat diteruskan mengikuti arah setiap jalur u→v. Hitung banyak pasangan terurut (u,v), u berbeda v, sehingga kabar dari u dapat mencapai v melalui satu atau lebih jalur.','Satu bilangan jumlah pasangan terurut yang terjangkau.','Ganti min/+ dengan OR/AND untuk transitive closure.','Setelah perantara k diizinkan, i mencapai j jika sebelumnya sudah bisa, atau i mencapai k dan k mencapai j. Induksi pada k memberikan seluruh keterjangkauan.'),('Rute Ambulans Paling Tenang','Tantangan','Setiap ruas berarah memiliki tingkat guncangan w. Nilai rute adalah guncangan terbesar di antara ruasnya. Untuk banyak pasangan kota, cari nilai rute minimum. Rute tanpa ruas dari kota ke dirinya bernilai 0.','Setiap query menghasilkan minimum guncangan maksimum, atau -1 jika tidak terjangkau.','Ganti penggabungan biaya dengan max; pilihan antar rute tetap min.','Rute melalui k mempunyai bottleneck maksimum dari bottleneck kedua bagian. Mengambil minimum antara rute lama dan rute melalui k mempertahankan invarian perantara.')]
    for i,(t,l,story,out,idea,proof) in enumerate(cfg,1):
        cases=[]
        for n,e in base:
            if i==2:cases.append(graph(n,e))
            else:
                we=[(u,v,RNG.choice([0,1,7,10**9])) for u,v in e];qs=[(1,n),(n,1),(1,1)];cases.append(graph(n,we,str(len(qs)))+''.join(f'{u} {v}\n' for u,v in qs))
        ps.append(problem(t,l,story,('Baris pertama n m. Berikutnya m baris u v.' if i==2 else 'Baris pertama n m q. Berikutnya m baris u v w, lalu q baris u v.')+' Simpul 1..n; graf berarah, loop dan sisi paralel boleh.\n\n**Keluaran:** '+out,'1 ≤ n ≤ 200; 0 ≤ m ≤ 40000; 1 ≤ q ≤ 100000; 0 ≤ w ≤ 10^9.',floyd_cpp(i),lambda s,i=i:floyd_oracle(i,s),cases,idea,proof,'O(n³+m+q) waktu untuk query (tanpa q pada latihan 2), O(n²) memori.','Loop k harus paling luar. Inisialisasi diagonal nol/true. Ambil minimum sisi paralel, bukan sisi terakhir.'))
    add(131,'Floyd-Warshall dan Transitive Closure','Day-131 - Floyd-Warshall (Jarak Semua Pasangan).pptx',
    '''Floyd-Warshall adalah DP dengan state (k,i,j): rute i→j yang hanya memakai perantara 1..k. Basis diagonal 0, sisi langsung berbobot minimum, lainnya INF. Transisi D_k(i,j)=min(D_{k−1}(i,j),D_{k−1}(i,k)+D_{k−1}(k,j)).

**Urutan loop.** k harus paling luar karena mewakili lapis DP. Untuk bobot nonnegatif atau tanpa siklus negatif, D[k][k]=0 dan lapis dapat diperbarui in-place. Loop i,j boleh saling bertukar. Menggunakan i,k,j secara umum tidak mempertahankan invarian.

**Trace.** 1→2 biaya 4, 2→3 biaya 5, 1→3 biaya 20. Sebelum k=2, d[1][3]=20; ketika k=2 diperbarui menjadi min(20,4+5)=9. Untuk minimax, nilai yang sama menjadi min(20,max(4,5))=5. Untuk closure boolean, false berubah true karena true AND true.

**Aljabar yang sama.** Shortest path memilih min dan menggabungkan +. Bottleneck memilih min dan menggabungkan max. Reachability memilih OR dan menggabungkan AND. Basis dan arti elemen kosong harus tetap mengikuti definisi soal.

**Batas.** n=200 memberi 8 juta iterasi inti. Banyak query dijawab O(1). Simpan long long karena rute dapat melebihi int. Selalu cek kedua bagian hingga sebelum menjumlahkan INF. Versi berbobot latihan menggunakan w≥0 agar nilai semua pasangan terdefinisi; untuk bobot negatif perlu mendeteksi d[k][k]<0 dan pengaruhnya pada pasangan.
''',ps,[('Kota Paling Sentral','Input n m lalu sisi berarah u v w, w≥0. Pilih kota yang dapat mencapai semua kota dan meminimalkan jumlah jarak ke semuanya. Tie pilih nomor terkecil. Keluarkan nomor kota atau -1. n≤200,m≤40000,w≤10^9.','3 3\n1 2 1\n2 3 1\n3 1 5\n','1\n','2 0\n','-1\n'),('Rute Terkuat','Input n m q, sisi berarah u v kapasitas (1..10^9), lalu q pasangan berbeda u v. Untuk tiap query maksimumkan kapasitas minimum rute; keluarkan 0 jika tidak ada rute. n≤200,m≤40000,q≤100000.','3 3 1\n1 2 8\n2 3 6\n1 3 3\n1 3\n','6\n','2 0 1\n1 2\n','0\n'),('Berapa Pasang Bisa Pulang','Input n m dan sisi berarah u v. Hitung pasangan tidak terurut {u,v}, u≠v, yang saling dapat mencapai. n≤200,m≤40000.','3 3\n1 2\n2 1\n2 3\n','1\n','3 3\n1 2\n2 3\n3 1\n','3\n')])

def mst_oracle(mode,s):
    import heapq
    a=ints(s);n,m=a[:2];off=2;cost=[]
    if mode==3:cost=a[off:off+n];off+=n
    es=[tuple(a[off+i*3:off+i*3+3]) for i in range(m)]
    if mode==2:
        if n==1:return '0\n'
        for w in sorted(set(w for u,v,w in es)):
            if len(components(n,[(u,v) for u,v,x in es if x<=w]))==1:return f'{w}\n'
        return '-1\n'
    if mode==3:es += [(n+1,i+1,cost[i]) for i in range(n)];n+=1
    g=[[] for _ in range(n)]
    for u,v,w in es:g[u-1].append((v-1,w));g[v-1].append((u-1,w))
    q=[(0,0)];seen=set();ans=0
    while q:
        w,u=heapq.heappop(q)
        if u in seen:continue
        seen.add(u);ans+=w
        for v,w in g[u]:
            if v not in seen:heapq.heappush(q,(w,v))
    return str(ans if len(seen)==n else -1)+'\n'
def mst_cpp(mode):
    return DSU+'''int main(){ios::sync_with_stdio(false);cin.tie(nullptr);int n,m;cin>>n>>m;vector<tuple<ll,int,int>>e;
'''+('''for(int i=0;i<n;++i){ll w;cin>>w;e.push_back({w,i,n});}''' if mode==3 else '')+'''for(int i=0;i<m;++i){int u,v;ll w;cin>>u>>v>>w;e.push_back({w,u-1,v-1});}'''+('++n;' if mode==3 else '')+'''sort(e.begin(),e.end());DSU d(n);ll total=0,big=0;int used=0;for(auto[w,u,v]:e)if(d.join(u,v)){total+=w;big=max(big,w);++used;}if(used!=n-1)cout<<-1;else cout<<'''+('big' if mode==2 else 'total')+";cout<<'\n';}\n"
def build136():
    base=edgecases();ps=[]
    cfg=[('Serat Optik Kepulauan','Pemanasan','Pilih kabel tak berarah sehingga semua pulau terhubung dengan biaya total minimum. Kabel yang tidak dipilih tidak dibayar.','Total biaya minimum, atau -1 jika tidak mungkin.','Urutkan kabel berdasarkan biaya dan ambil sisi yang menggabungkan dua komponen DSU.','Sisi termurah yang melintasi cut antar komponen aman dimasukkan ke suatu MST: menambahkannya membentuk siklus pada MST lama, dan membuang sisi cut yang tak lebih murah tidak menaikkan biaya.'),('Kapal Pengangkut Kabel','Menengah','Kapal hanya mampu membawa kabel dengan tingkat kesulitan paling tinggi B. Tentukan B minimum agar kabel yang dapat dibawa cukup untuk menghubungkan semua pulau. Semua kabel boleh dipasang dan tidak ada batas biaya total.','B minimum; 0 untuk satu pulau; -1 jika mustahil.','Saat Kruskal berhasil menghubungkan semua simpul, bobot sisi terakhir adalah ambang minimum.','Sebelum bobot terakhir diproses, terdapat cut yang belum terhubung oleh sisi lebih ringan. Ambang lebih rendah mustahil. Sisi yang sudah diambil membuktikan ambang terakhir cukup.'),('Bandara dan Jalan Perintis','Tantangan','Setiap pulau i dapat dibangun bandara berbiaya a_i. Jalan dua arah berbiaya w juga tersedia. Setiap pulau wajib mempunyai jalur darat ke setidaknya satu bandara; bandara antar pulau dianggap terhubung lewat penerbangan gratis. Minimumkan biaya bandara dan jalan.','Total biaya minimum.','Tambahkan simpul super 0; sisi 0—i berbiaya a_i mewakili bandara. Cari MST pada graf tambahan.','Jaringan sah menghubungkan setiap pulau ke setidaknya satu bandara sehingga graf dengan simpul super terhubung. Sebaliknya, koneksi ke super di spanning tree memberikan bandara bagi setiap komponen jalan. Dengan biaya nonnegatif, solusi terhubung dapat dipangkas menjadi spanning tree tanpa menambah biaya.')]
    for i,(t,l,story,out,idea,proof) in enumerate(cfg,1):
        cases=[]
        for n,e in base:
            es=[(u,v,RNG.choice([0,2,11,10**9])) for u,v in e];prefix=' '.join(str(RNG.choice([0,4,20,10**9])) for _ in range(n))+'\n' if i==3 else '';cases.append(graph(n,es,prefix=prefix))
        ps.append(problem(t,l,story,'Baris pertama n m. '+('Baris kedua n biaya bandara a_i. ' if i==3 else '')+'Berikutnya m baris u v w, sisi tak berarah dengan simpul 1..n. Loop dan sisi paralel boleh.\n\n**Keluaran:** '+out,'1 ≤ n ≤ 100000; 0 ≤ m ≤ 200000; 0 ≤ w,a_i ≤ 10^9.',mst_cpp(i),lambda s,i=i:mst_oracle(i,s),cases,idea,proof,'O((m+n) log(m+n)) waktu dan O(m+n) memori; tanpa supervertex dapat ditulis O(m log(m+1)+n).','Kruskal menghasilkan hutan jika graf terputus; cek banyak sisi terpilih n−1. MST meminimalkan total, bukan jarak dari satu sumber.'))
    add(136,'Minimum Spanning Tree - Kruskal','Day-136 - Minimum Spanning Tree (Kruskal & Prim).pptx',
    '''Spanning tree menyambungkan semua simpul menggunakan n−1 sisi tanpa siklus. MST memilih spanning tree dengan jumlah bobot minimum. Graf terputus hanya mempunyai spanning forest; jangan melaporkan jumlah bobot forest sebagai MST.

**Kruskal.** Urutkan sisi naik menurut bobot. Jika find(u)≠find(v), ambil sisi dan union; selainnya lewatkan. DSU menjaga bahwa sisi terpilih selalu hutan. Tie bobot bebas karena latihan meminta nilai saja.

**Bukti cut/exchange.** Saat sisi e dipilih, tidak ada sisi lebih murah yang bisa melintasi cut antara dua komponen DSU tersebut. Jika suatu MST tidak memakai e, menambah e menciptakan siklus. Ada sisi f pada siklus yang melintasi cut; w(f)≥w(e). Ganti f dengan e, masih sebuah MST. Induksi membenarkan seluruh keputusan.

**Trace.** Kabel 1—2:2, 2—3:3, 1—3:8. Ambil 2 dan 3, lewati 8 karena satu komponen. Biaya 5, bottleneck 3. Menambah pulau 4 tanpa kabel menyebabkan jumlah sisi terpilih 2, kurang dari 3: MST tidak ada.

**Prim sebagai pembanding dari PPT.** Mulai satu simpul, simpan bobot sisi termurah yang menghubungkan setiap simpul luar ke pohon, lalu pilih minimum dengan heap. Kuncinya bobot satu sisi, bukan jarak kumulatif seperti Dijkstra. Prim dan Kruskal memberi nilai MST sama; oracle paket ini memakai Prim untuk membandingkan implementasi Kruskal.

**Pemodelan supervertex.** Pilihan fasilitas per simpul dapat berubah menjadi sisi menuju simpul virtual. Biaya nonnegatif menjamin menghapus siklus tidak memperburuk solusi. long long diperlukan: 100.000 sisi bernilai 10^9 dapat berjumlah sekitar 10^14.
''',ps,[('Hutan K Klaster','Input n m k dan kabel u v w tak berarah, w≥0. Pilih hutan dengan tepat k komponen dan biaya minimum; keluarkan -1 jika mustahil. 1≤k≤n≤100000,m≤200000,w≤10^9.','3 3 2\n1 2 4\n2 3 2\n1 3 8\n','2\n','3 0 2\n','-1\n'),('Penghematan Kabel','Input n m dan kabel u v w. Biaya awal adalah jumlah semua kabel. Pertahankan keterhubungan setiap komponen awal dengan biaya minimum. Keluarkan biaya yang bisa dihemat. n≤100000,m≤200000,0≤w≤10^9.','3 3\n1 2 2\n2 3 3\n1 3 8\n','8\n','3 1\n1 2 7\n','0\n'),('Kabel Wajib Dipasang','Input n m dan m baris u v w b. b=1 berarti sisi wajib dipilih. Cari spanning tree termurah memuat seluruh sisi wajib, atau -1. n≤100000,m≤200000,0≤w≤10^9,b∈{0,1}.','3 3\n1 2 8 1\n2 3 2 0\n1 3 1 0\n','9\n','2 2\n1 2 1 1\n1 2 2 1\n','-1\n')])

def scc_oracle(mode,s):
    a=ints(s);n,m=a[:2];off=2;w=[]
    if mode==3:w=a[off:off+n];off+=n
    e=list(zip(a[off::2],a[off+1::2]));r=reach(n,e);id=[-1]*n;groups=[]
    for i in range(n):
        if id[i]>=0:continue
        cur=[j for j in range(n) if r[i][j] and r[j][i]]
        for j in cur:id[j]=len(groups)
        groups.append(cur)
    if mode==1:return str(len(groups))+'\n'+' '.join(map(str,sorted(map(len,groups))))+'\n'
    arcs={(id[u-1],id[v-1]) for u,v in e if id[u-1]!=id[v-1]}
    if mode==2:return str(len(groups)-len({v for u,v in arcs}))+'\n'
    weights=[sum(w[x] for x in g) for g in groups];best=[None]*len(groups)
    def rec(u):
        if best[u] is None:best[u]=weights[u]+max([rec(v) for x,v in arcs if x==u]+[0])
        return best[u]
    return str(max(rec(u) for u in range(len(groups))))+'\n'
def scc_cpp(mode):
    return SCC+'''int main(){int n,m;cin>>n>>m;vector<ll>w(n,1);'''+('for(auto&x:w)cin>>x;' if mode==3 else '')+'''vector<vector<int>>g(n);vector<pair<int,int>>e;while(m--){int u,v;cin>>u>>v;--u;--v;g[u].push_back(v);e.push_back({u,v});}auto id=scc(g);int c=*max_element(id.begin(),id.end())+1;vector<int>sz(c),indeg(c);vector<ll>sum(c);vector<vector<int>>dag(c);for(int u=0;u<n;++u){++sz[id[u]];sum[id[u]]+=w[u];}for(auto[u,v]:e)if(id[u]!=id[v]){dag[id[u]].push_back(id[v]);++indeg[id[v]];}
'''+('''sort(sz.begin(),sz.end());cout<<c<<'\n';for(int i=0;i<c;++i)cout<<sz[i]<<(i+1==c?'\n':' ');''' if mode==1 else '''cout<<count(indeg.begin(),indeg.end(),0)<<'\n';''' if mode==2 else '''queue<int>q;vector<ll>dp=sum;for(int u=0;u<c;++u)if(!indeg[u])q.push(u);while(!q.empty()){int u=q.front();q.pop();for(int v:dag[u]){dp[v]=max(dp[v],dp[u]+sum[v]);if(--indeg[v]==0)q.push(v);}}cout<<*max_element(dp.begin(),dp.end())<<'\n';''')+'}\n'
def build225():
    base=edgecases();ps=[]
    cfg=[('Zona Antar-Jemput','Pemanasan','Dua halte berada dalam satu zona jika setiap halte dapat mencapai yang lain melalui jalan berarah. Hitung zona kuat dan ukurannya.','Baris pertama jumlah SCC. Baris kedua ukuran semua SCC terurut menaik, dipisahkan spasi.','Jalankan Tarjan lalu hitung frekuensi ID komponen dan urutkan ukurannya.','Tarjan mengeluarkan satu blok stack saat low[u]=tin[u]. Blok tersebut adalah komponen maksimal yang saling terjangkau. Menghitung setiap ID memberi tepat ukuran SCC.'),('Pengeras Suara Pertama','Menengah','Kabar mengikuti jalan berarah. Panitia boleh menempatkan pengeras suara di beberapa halte; dari sana kabar menyebar mengikuti semua jalan. Cari jumlah minimum pengeras suara agar semua halte mendengar.','Jumlah minimum simpul awal yang dibutuhkan.','Kerutkan SCC dan hitung komponen dengan indegree nol.','Setiap SCC sumber tidak dapat menerima kabar dari SCC lain sehingga memerlukan satu alat. Setiap simpul DAG dapat dicapai dari suatu sumber. Satu alat di tiap SCC sumber cukup.'),('Kurir Pengumpul Donasi','Tantangan','Halte i menyimpan w_i koin nonnegatif. Kurir boleh memilih tempat mulai dan berhenti, berjalan mengikuti sisi berarah, dan mengulang simpul/ruas. Koin tiap halte hanya dapat diambil sekali. Cari koin maksimum.','Jumlah koin maksimum.','Jumlahkan koin per SCC, bangun DAG kondensasi, lalu DP jalur maksimum dengan urutan topologis Kahn.','Di sebuah SCC kurir dapat mengunjungi semua simpul lalu menuju pintu keluar mana pun, karena saling terjangkau dan kunjungan ulang boleh. DAG tak dapat kembali ke SCC lama. Maka setiap perjalanan sesuai jalur DAG dengan bobot jumlah SCC; DP memilih yang terbaik.')]
    for i,(t,l,story,out,idea,proof) in enumerate(cfg,1):
        cases=[graph(n,e,prefix=(' '.join(str(RNG.randint(0,10**9)) for _ in range(n))+'\n') if i==3 else '') for n,e in base]
        ps.append(problem(t,l,story,'Baris pertama n m. '+('Baris kedua w_1..w_n. ' if i==3 else '')+'Berikutnya m sisi berarah u v; simpul 1..n, loop dan sisi paralel boleh.\n\n**Keluaran:** '+out,'1 ≤ n ≤ 2000; 0 ≤ m ≤ 20000; 0 ≤ w_i ≤ 10^9.',scc_cpp(i),lambda s,i=i:scc_oracle(i,s),cases,idea,proof,'O(n+m) waktu, kecuali pengurutan ukuran O(n log n) pada latihan 1; O(n+m) memori.','low pada sisi menuju simpul yang sudah keluar stack tidak boleh diperbarui. Jangan mengasumsikan nomor SCC Tarjan terurut topologis maju.'))
    add(225,'Strongly Connected Component - Tarjan','Day-225 - Strongly Connected Component.pptx',
    '''SCC adalah kelas ekuivalensi dari relasi “u mencapai v dan v mencapai u”. Komponen terhubung biasa mengabaikan arah sehingga tidak cukup. Pengerutan setiap SCC menjadi satu simpul menghasilkan DAG: siklus antar beberapa SCC akan membuat seluruhnya saling terjangkau dan seharusnya menjadi satu SCC.

**Tarjan sesuai ROADMAP Day 225.** tin[u] adalah waktu penemuan; low[u] menyimpan tin terkecil yang dapat dijangkau dari subtree DFS menuju simpul yang masih aktif. Dorong setiap simpul ke stack aktif. Untuk tree edge u→v, setelah DFS gunakan low[v]. Untuk sisi ke simpul aktif yang sudah ditemukan, gunakan tin[v]. Sisi ke simpul yang telah keluar stack diabaikan.

**Menutup komponen.** Jika low[u]=tin[u], u adalah akar SCC. Pop stack sampai u dan beri semua simpul tersebut ID sama. Mereka belum dapat keluar menuju komponen aktif yang lebih tua; keterhubungan balik yang dicatat low mengikat blok itu. Setiap simpul dipush dan dipop sekali, total O(n+m).

**Trace.** 1→2,2→1,2→3: tin 1=0, tin 2=1; sisi 2→1 menurunkan low[2] menjadi 0. Simpul 3 selesai sendiri dan dipop sebagai SCC {3}; setelah kembali, 1 mempop {2,1}. Sisi keluar ke SCC yang sudah selesai tidak menyatukan keduanya.

**Hubungan dengan PPT.** PPT225 menjelaskan Kosaraju dua DFS (graf asli lalu transpose dalam urutan selesai terbalik). Materi itu tetap sumber konsep SCC dan condensation; implementasi inti paket ini Tarjan mengikuti ROADMAP. Kosaraju ditempatkan sebagai pembanding Day226. Nomor komponen bergantung algoritma, maka DP menggunakan Kahn eksplisit.

**Aplikasi dan batas.** Ukuran SCC, banyak sumber DAG, dan DP keuntungan. Donasi nonnegatif dan kunjungan ulang membuat jumlah semua koin SCC dapat dikoleksi sebelum keluar. Implementasi edukatif rekursif dibatasi n≤2000; saat memperluas ke ratusan ribu simpul gunakan DFS dengan frame eksplisit atau sesuaikan stack setelah mengukur lingkungan.
''',ps,[('Pertanyaan Saling Mencapai','Input n m q, m sisi berarah, lalu q pasangan u v. Keluarkan YA jika keduanya saling mencapai (u=v juga YA), TIDAK selainnya. n≤2000,m≤20000,q≤100000.','3 2 2\n1 2\n2 1\n1 2\n1 3\n','YA\nTIDAK\n','1 0 1\n1 1\n','YA\n'),('Terminal yang Tak Bisa Keluar','Input n m dan sisi berarah. Hitung SCC yang tidak mempunyai sisi keluar menuju SCC lain. n≤2000,m≤20000.','3 2\n1 2\n1 3\n','2\n','2 2\n1 2\n2 1\n','1\n'),('Simpul di Siklus','Input n m dan sisi berarah. Hitung simpul yang berada pada setidaknya satu siklus berarah; self-loop dihitung. n≤2000,m≤20000.','3 3\n1 2\n2 1\n2 3\n','2\n','2 1\n2 2\n','1\n')])

def bridge_oracle(mode,s):
    a=ints(s);n,m=a[:2];e=list(zip(a[2::2],a[3::2]));cc=components(n,e)
    if mode==1:return str(sum(len(components(n,e,skipedge=i))>len(cc) for i in range(m)))+'\n'
    if mode==2:return str(sum(len(components(n,e,skipvertex=i))>len(cc) for i in range(n)))+'\n'
    pairs=lambda cs:sum(len(c)*(len(c)-1)//2 for c in cs)
    return str(sum(pairs(cc)-pairs(components(n,e,skipedge=i)) for i in range(m)))+'\n'
def bridge_cpp(mode):
    return '''int main(){int n,m;cin>>n>>m;vector<vector<pair<int,int>>>g(n);for(int i=0;i<m;++i){int u,v;cin>>u>>v;--u;--v;g[u].push_back({v,i});g[v].push_back({u,i});}
 vector<int>tin(n,-1),low(n),sub(n),art(n);int timer=0,bridges=0;ll impact=0;vector<int>parts;
 function<void(int,int)>dfs=[&](int u,int pe){tin[u]=low[u]=timer++;sub[u]=1;int children=0;for(auto[v,id]:g[u]){if(id==pe)continue;if(tin[v]>=0){low[u]=min(low[u],tin[v]);continue;}++children;dfs(v,id);sub[u]+=sub[v];low[u]=min(low[u],low[v]);if(low[v]>tin[u]){++bridges;parts.push_back(sub[v]);}if(pe!=-1&&low[v]>=tin[u])art[u]=1;}if(pe==-1&&children>1)art[u]=1;};
 for(int s=0;s<n;++s)if(tin[s]<0){parts.clear();dfs(s,-1);ll size=sub[s];for(int x:parts)impact+=1LL*x*(size-x);}
 cout<<'''+('bridges' if mode==1 else 'accumulate(art.begin(),art.end(),0)' if mode==2 else 'impact')+"<<'\n';}\n"
def build227():
    cases=[graph(n,e) for n,e in edgecases()];ps=[]
    cfg=[('Kabel Terakhir Posko','Pemanasan','Sebuah kabel disebut kritis jika menghapus kabel itu saja menambah jumlah komponen terhubung jaringan. Hitung kabel kritis.','Jumlah bridge.','DFS low-link: tree edge u—v adalah bridge jika low[v]>tin[u].','Jika low[v]≤tin[u], subtree v memiliki jalan balik yang menghindari tree edge. Jika lebih besar, semua jalur keluar subtree harus melalui u—v, sehingga menghapusnya memisahkan komponen.'),('Menara yang Tak Boleh Mati','Menengah','Menara kritis adalah simpul yang jika dihapus beserta seluruh kabel insidennya menambah jumlah komponen terhubung dibanding jaringan awal. Hitung menara kritis.','Jumlah articulation point.','Untuk simpul nonroot u, cari anak v dengan low[v]≥tin[u]. Root kritis tepat jika punya ≥2 anak DFS.','Anak dengan low[v]≥tin[u] tidak mempunyai jalan menuju leluhur ketat u tanpa melewati u. Menghapus u memisahkan subtree itu. Root tidak memiliki leluhur; komponen pecah tepat bila sedikitnya dua subtree anak.'),('Total Gangguan Satu Kabel','Tantangan','Uji setiap kabel secara terpisah: hapus kabel itu dari jaringan asli, lalu hitung pasangan tidak terurut {u,v} yang semula terhubung tetapi sesudahnya terputus. Kembalikan jaringan sebelum menguji kabel berikutnya. Jumlahkan dampak semua pengujian.','Jumlah seluruh pasangan yang kehilangan koneksi, dijumlahkan atas semua kabel. Pasangan sama boleh terhitung lagi pada pengujian lain.','Untuk bridge dengan ukuran subtree x di komponen ukuran C, dampaknya x(C−x). Nonbridge berdampak nol.','Bridge membagi komponen menjadi bagian x dan C−x. Tepat pasangan dengan satu ujung di masing-masing bagian kehilangan koneksi. Hasil kali menghitung setiap pasangan sekali untuk pengujian itu.')]
    for i,(t,l,story,out,idea,proof) in enumerate(cfg,1):ps.append(problem(t,l,story,'Baris pertama n m; m baris u v kabel tak berarah. Simpul 1..n. Loop dan kabel paralel boleh dan setiap baris adalah kabel berbeda.\n\n**Keluaran:** '+out,'1 ≤ n ≤ 2000; 0 ≤ m ≤ 20000.',bridge_cpp(i),lambda s,i=i:bridge_oracle(i,s),cases,idea,proof,'O(n+m) waktu dan memori.','Skip ID sisi parent saja. Bridge memakai >; articulation memakai ≥. Untuk dampak gunakan ukuran komponen asal, bukan n global.'))
    add(227,'Bridge dan Articulation Point','Day-227 - Bridge & Articulation Point.pptx',
    '''Bridge adalah sisi yang penghapusannya menambah jumlah komponen; articulation point adalah simpul dengan sifat sama setelah semua sisi insidennya ikut dihapus. Definisi membandingkan dengan graf semula, jadi tetap berlaku pada graf terputus.

**Low-link tak berarah.** tin[u] ialah waktu masuk. low[u] adalah tin terkecil dari u/subtree DFS u yang dapat dicapai menggunakan tree edges turun dan paling banyak satu back edge. Inisialisasi low=tin. Untuk anak v gunakan low[v] sesudah DFS; untuk tetangga yang sudah dikunjungi gunakan tin[v]. Skip hanya edge ID parent agar kabel paralel ke parent menjadi back edge yang sah.

**Dua ketidaksamaan.** Edge u—v adalah bridge bila low[v]>tin[u], sebab tidak ada jalan kembali ke u atau leluhur. Nonroot u adalah articulation bila ada anak v dengan low[v]≥tin[u]; kembali tepat ke u tidak membantu setelah u dihapus. Root perlu perlakuan khusus: minimal dua anak DFS.

**Trace.** Segitiga 1—2—3—1 dengan ekor 3—4: low[3] turun ke tin[1], maka sisi segitiga bukan bridge. low[4]>tin[3], jadi 3—4 bridge. Simpul 3 articulation. Jika sisi 3—4 digandakan, kabel kedua adalah back edge, dan keduanya bukan bridge.

**Dampak.** DFS juga menghitung sub[u]. Bridge ke anak v membagi komponen berukuran C menjadi sub[v] dan C−sub[v]. Perkalian keduanya adalah banyak pasangan terputus. Simpan ukuran bagian bridge hingga DFS akar selesai agar C diketahui.

**Batas dan pengujian.** Kode rekursif edukatif dibatasi n≤2000. Oracle menghapus satu sisi/simpul dan menghitung ulang komponen, berbeda dari low-link; kasus acak mencakup loop, paralel, dan komponen terisolasi. Untuk n jauh lebih besar gunakan frame DFS eksplisit agar tidak mengandalkan stack proses.
''',ps,[('Daftar Kabel Kritis','Input n m dan m kabel u v. Keluarkan jumlah bridge pada baris pertama; baris kedua ID bridge terurut menaik, atau baris kosong bila tidak ada. ID dimulai 1 sesuai input. n≤2000,m≤20000.','3 2\n1 2\n2 3\n','2\n1 2\n','2 2\n1 2\n1 2\n','0\n\n'),('Sesudah Semua Bridge Dilepas','Input n m dan kabel tak berarah. Hapus sekaligus semua bridge graf awal. Keluarkan jumlah komponen hasilnya. n≤2000,m≤20000.','4 4\n1 2\n2 3\n3 1\n3 4\n','2\n','3 0\n','3\n'),('Kabel Paling Berbahaya','Input n m dan kabel tak berarah. Keluarkan dampak maksimum satu penghapusan: banyak pasangan tidak terurut yang semula terhubung lalu terputus. Jika m=0 keluarkan 0. n≤2000,m≤20000.','4 3\n1 2\n2 3\n3 4\n','4\n','3 3\n1 2\n2 3\n3 1\n','0\n')])

def sat_clauses(mode,s):
    a=ints(s);n,m=a[:2]
    if mode!=2:return n,[tuple(a[2+2*i:4+2*i]) for i in range(m)]
    out=[]
    for i in range(m):
        u,v,t=a[2+3*i:5+3*i]
        out.extend([(u,v),(-u,-v)] if t else [(-u,v),(u,-v)])
    return n,out
def sat_oracle(mode,s):
    n,clauses=sat_clauses(mode,s)
    def ok(k):
        return any(all(((bool(mask>>(abs(a)-1)&1))==(a>0)) or ((bool(mask>>(abs(b)-1)&1))==(b>0)) for a,b in clauses[:k]) for mask in range(1<<n))
    if mode==3:return str(next((k-1 for k in range(1,len(clauses)+1) if not ok(k)),len(clauses)))+'\n'
    return ('YA' if ok(len(clauses)) else 'TIDAK')+'\n'
def sat_cpp(mode):
    return SCC+'''int main(){int n,m;cin>>n>>m;vector<pair<int,int>>cs;'''+('''for(int i=0;i<m;++i){int u,v,t;cin>>u>>v>>t;if(t){cs.push_back({u,v});cs.push_back({-u,-v});}else{cs.push_back({-u,v});cs.push_back({u,-v});}}''' if mode==2 else '''for(int i=0;i<m;++i){int a,b;cin>>a>>b;cs.push_back({a,b});}''')+'''auto lit=[](int x){return 2*(abs(x)-1)+(x<0);};auto ok=[&](int k){vector<vector<int>>g(2*n);for(int i=0;i<k;++i){auto[a,b]=cs[i];int u=lit(a),v=lit(b);g[u^1].push_back(v);g[v^1].push_back(u);}auto id=scc(g);for(int i=0;i<n;++i)if(id[2*i]==id[2*i+1])return false;return true;};'''+('''int l=0,r=m;while(l<r){int mid=l+(r-l+1)/2;if(ok(mid))l=mid;else r=mid-1;}cout<<l;''' if mode==3 else '''cout<<(ok(cs.size())?"YA":"TIDAK");''')+"cout<<'\n';}\n"
def build229():
    base=[(1,[]),(1,[(1,1),(-1,-1)]),(2,[(1,2),(-1,2),(1,-2)]),(2,[(1,1),(-2,-2)]),(2,[(1,2),(-1,-2),(1,-2),(-1,2)]),(3,[(1,-2),(2,-3),(3,-1)]),(1,[(1,-1)]),(3,[])]
    for _ in range(16):
        n=RNG.randint(1,7);base.append((n,[(RNG.choice([-1,1])*RNG.randint(1,n),RNG.choice([-1,1])*RNG.randint(1,n)) for _ in range(RNG.randint(0,18))]))
    cfg=[('Sakelar Panggung','Pemanasan','Setiap sakelar bernilai benar atau salah. Syarat (a,b) mengharuskan sedikitnya satu literal benar. Literal i berarti sakelar i benar; literal -i berarti sakelar i salah. Apakah semua syarat dapat dipenuhi?','n m, lalu m baris a b.','YA jika ada penugasan, TIDAK selainnya.','Ubah (a∨b) menjadi ¬a→b dan ¬b→a, lalu cari SCC.','Jika x dan ¬x satu SCC, masing-masing memaksa yang lain sehingga kontradiksi. Jika tidak, condensation DAG dapat diproses dengan urutan topologis untuk menetapkan literal berlawanan secara konsisten; semua implikasi dan klausa terpenuhi.'),('Lampu Seragam dan Kontras','Menengah','Setiap lampu memilih mode 0 atau 1. Aturan u v t berarti kedua lampu harus sama jika t=0, berbeda jika t=1. Periksa konsistensi seluruh aturan.','n m, lalu m baris u v t.','YA jika konsisten, TIDAK selainnya.','Sama: (¬u∨v)∧(u∨¬v). Berbeda: (u∨v)∧(¬u∨¬v). Jalankan 2-SAT.','Tabel kebenaran empat kemungkinan menunjukkan masing-masing pasangan klausa tepat ekuivalen dengan aturan. Reduksi tidak mengubah himpunan solusi; teorema SCC 2-SAT menyelesaikannya.'),('Janji Panitia yang Bertahan','Tantangan','Janji berupa klausa dua literal dimasukkan berurutan. Cari banyak janji awal maksimum yang masih dapat dipenuhi bersama. Menghapus janji hanya boleh dari akhir daftar.','n m, lalu m baris literal a b.','Panjang prefix maksimum yang satisfiable, antara 0 dan m.','Binary search panjang prefix, menggunakan SCC sebagai pemeriksa satisfiability.','Menghapus klausa tidak mengurangi himpunan solusi. Jadi prefix satisfiable membentuk rentang [0,K], dan binary search menemukan batas terakhirnya.')]
    ps=[]
    for i,(t,l,story,inp,out,idea,proof) in enumerate(cfg,1):
        cases=[graph(n,[(abs(a),abs(b),RNG.randint(0,1)) for a,b in e] if i==2 else e) for n,e in base]
        ps.append(problem(t,l,story,inp+' Indeks variabel 1..n; literal bukan nol. Literal/variabel yang sama boleh muncul berulang.\n\n**Keluaran:** '+out,'1 ≤ n ≤ 500; 0 ≤ m ≤ 2000; 1 ≤ |a|,|b|,u,v ≤ n; t∈{0,1}.',sat_cpp(i),lambda s,i=i:sat_oracle(i,s),cases,idea,proof,'O(n+m) waktu per pemeriksaan, O((n+m) log(m+1)) pada prefix; O(n+m) memori.','Satu klausa menghasilkan dua implikasi. Gunakan negasi literal, bukan negasi indeks variabel. (x∨x) memaksa x benar; (x∨¬x) selalu benar.'))
    add(229,'2-SAT dan Implication Graph','Day-229 - 2-SAT.pptx',
    '''2-SAT mencari penugasan boolean yang memenuhi konjungsi klausa, masing-masing berisi dua literal. Literal adalah x atau ¬x. Satu klausa (a∨b) setara (¬a⇒b) dan (¬b⇒a); kedua sisi wajib dibuat.

**Representasi.** Untuk variabel i berbasis nol, simpul 2i mewakili literal positif dan 2i+1 negatif. Negasi cukup XOR 1. Input menggunakan ±(i+1), sehingga pemetaan C++ adalah 2*(abs(x)−1)+(x<0).

**Kriteria SCC.** Formula tidak satisfiable tepat ketika ada x dan ¬x di SCC sama. Arah perlu jelas: jalur literal berarti implikasi. Jika kedua arah ada, memilih salah satu nilai memaksa lawannya. Untuk arah kecukupan, SCC membentuk DAG dengan pasangan komponen negasi; urutan topologis memungkinkan memilih komponen yang tidak memaksa komponen salah. Ini memberikan penugasan konsisten tanpa mencoba 2^n kemungkinan.

**Trace kontradiksi.** Klausa (x∨x) memberi ¬x→x. Klausa (¬x∨¬x) memberi x→¬x. Keduanya menyatu di SCC dan formula mustahil. Sebaliknya (x∨¬x) hanya memberi self-loop dan tidak membatasi x.

**Reduksi umum.** x=y memberi (¬x∨y)∧(x∨¬y). x≠y memberi (x∨y)∧(¬x∨¬y). “Tidak keduanya benar” memberi (¬x∨¬y). “Sedikitnya satu benar” memberi (x∨y). Bedakan OR dari XOR.

**Batas dan validasi.** Graf implikasi punya 2n simpul dan 2m sisi (hingga 4m untuk aturan dua klausa). Tarjan rekursif aman untuk batas paket 2n≤1000. Oracle enumerasi seluruh penugasan untuk kasus kecil menguji reduksi secara independen. Latihan hanya meminta keputusan atau panjang prefix agar output tunggal; jika kelak mengeluarkan assignment, pastikan orientasi ID SCC sesuai implementasi.
''',ps,[('Tidak Boleh Dua Stand Bersama','Input n m k; m baris u v berarti u,v tidak boleh sama-sama aktif, lalu k nomor stand yang wajib aktif (unik). Keluarkan YA/TIDAK. n≤500,m≤2000.','3 2 1\n1 2\n2 3\n2\n','YA\n','2 1 2\n1 2\n1 2\n','TIDAK\n'),('Memaksa Satu Pilihan','Input n m x, diikuti m klausa literal a b. Dijamin formula awal satisfiable. Keluarkan BENAR jika x benar dalam semua solusi, SALAH jika x salah dalam semua solusi, atau BEBAS. n≤500,m≤2000,1≤x≤n.','1 1 1\n1 1\n','BENAR\n','2 1 1\n1 2\n','BEBAS\n'),('Jarak Jadwal','Setiap acara memilih slot 0 atau 1. Input n m, lalu m baris u a v b melarang kombinasi acara u pada slot a dan acara v pada slot b. Keluarkan YA jika jadwal sah ada, TIDAK selainnya. n≤500,m≤2000.','1 2\n1 0 1 0\n1 1 1 1\n','TIDAK\n','2 1\n1 0 2 0\n','YA\n')])

def euler_type(n,e,directed):
    if not e:return 'TERTUTUP',0
    active={x-1 for a in e for x in a};cc=components(n,e)
    if sum(bool(active.intersection(c)) for c in cc)>1:return 'TIDAK',0
    delta=[0]*n;deg=[0]*n
    for u,v in e:
        deg[u-1]+=1;deg[v-1]+=1;delta[u-1]+=1;delta[v-1]-=1
    if not directed:
        odd=[i for i in range(n) if deg[i]%2]
        if len(odd) not in (0,2):return 'TIDAK',0
        return ('TERBUKA',odd[0]) if odd else ('TERTUTUP',min(active))
    if all(d==0 for d in delta):return 'TERTUTUP',min(active)
    if delta.count(1)==1 and delta.count(-1)==1 and all(-1<=x<=1 for x in delta):return 'TERBUKA',delta.index(1)
    return 'TIDAK',0
def euler_oracle(mode,s):
    a=ints(s);n,m=a[:2];e=list(zip(a[2::2],a[3::2]));kind,start=euler_type(n,e,mode==2)
    if mode!=3 or kind=='TIDAK':return kind+'\n'
    g=[[] for _ in range(n)]
    for i,(u,v) in enumerate(e):g[u-1].append((i,v-1));g[v-1].append((i,u-1))
    used=set();route=[]
    def rec(u):
        for eid,v in g[u]:
            if eid not in used:used.add(eid);rec(v)
        route.append(u+1)
    rec(start);return ' '.join(map(str,route[::-1]))+'\n'
def euler_cpp(mode):
    return DSU+'''int main(){int n,m;cin>>n>>m;DSU d(n);vector<int>deg(n),delta(n);vector<vector<pair<int,int>>>g(n);for(int id=0;id<m;++id){int u,v;cin>>u>>v;--u;--v;d.join(u,v);++deg[u];++deg[v];++delta[u];--delta[v];g[u].push_back({id,v});g[v].push_back({id,u});}
 int root=-1,start=0;bool ok=true;vector<int>odd;int plus=0,minus=0;for(int u=0;u<n;++u){if(deg[u]){if(root<0){root=d.find(u);start=u;}else if(root!=d.find(u))ok=false;}if(deg[u]%2)odd.push_back(u);if(delta[u]==1)++plus;else if(delta[u]==-1)++minus;else if(delta[u]!=0)'''+('ok=false;' if mode==2 else '{}')+'''}
 bool open=false;'''+('''if(!(plus==0&&minus==0)&&!(plus==1&&minus==1))ok=false;open=plus==1;''' if mode==2 else '''if(odd.size()!=0&&odd.size()!=2)ok=false;open=odd.size()==2;if(open)start=odd[0];''')+'''if(!ok){cout<<"TIDAK"<<'\n';return 0;}
'''+('''cout<<(open?"TERBUKA":"TERTUTUP")<<'\n';''' if mode!=3 else '''vector<int>ptr(n),used(m),st={start},route;while(!st.empty()){int u=st.back();while(ptr[u]<(int)g[u].size()&&used[g[u][ptr[u]].first])++ptr[u];if(ptr[u]==(int)g[u].size()){route.push_back(u);st.pop_back();}else{auto[id,v]=g[u][ptr[u]++];used[id]=1;st.push_back(v);}}reverse(route.begin(),route.end());for(int i=0;i<(int)route.size();++i)cout<<route[i]+1<<(i+1==(int)route.size()?'\n':' ');''')+'}\n'
def build230():
    base=edgecases();base += [(6,[(1,2),(2,3),(3,1),(4,5),(5,6),(6,4)]),(3,[(1,2),(2,3),(3,1),(1,1)])];ps=[]
    cfg=[('Mobil Penyapu Kampung','Pemanasan','Mobil ingin melewati setiap jalan tak berarah tepat sekali. Tempat mulai boleh dipilih. Tentukan apakah rute dapat kembali ke awal, hanya bisa berakhir di tempat lain, atau mustahil.','TERTUTUP jika sirkuit ada; TERBUKA jika hanya lintasan terbuka ada; TIDAK jika keduanya tidak ada.','Cek keterhubungan simpul berderajat positif dan banyak simpul berderajat ganjil.','Setiap kunjungan internal berpasangan masuk-keluar, sehingga derajat genap kecuali dua ujung lintasan. Dengan keterhubungan, prosedur Hierholzer menyusun semua sisi dan membuktikan syarat cukup.'),('Pengantar Surat Satu Arah','Menengah','Kurir harus memakai setiap jalan berarah tepat sekali. Ia bebas memilih mulai dan selesai. Klasifikasikan kemungkinan rutenya.','TERTUTUP jika semua jalan dapat dilalui dan kembali ke awal; TERBUKA jika hanya lintasan terbuka ada; TIDAK selainnya.','Periksa weak connectivity simpul aktif. Sirkuit perlu out=in semua simpul; lintasan terbuka perlu satu out−in=1 dan satu out−in=−1, sisanya nol.','Konservasi banyak masuk/keluar memberi syarat perlu. Menambah sisi dari akhir ke awal pada kasus terbuka menyeimbangkan derajat. Graf seimbang dengan weak connectivity aktif dapat ditelusuri Hierholzer sebagai sirkuit; hapus sisi tambahan untuk lintasan.'),('Log Perjalanan Penyapu','Tantangan','Bangun log rute Euler graf tak berarah menggunakan aturan deterministik berikut. Jika ada dua simpul ganjil, mulai dari yang nomornya lebih kecil; jika semua genap, mulai dari simpul aktif terkecil. Gunakan stack Hierholzer: dari puncak pilih sisi belum dipakai dengan ID terkecil, tandai dan dorong ujung lain. Jika buntu, pop simpul ke daftar. Setelah stack habis, balik daftar untuk keluaran. ID sisi adalah urutan input.','TIDAK jika tidak ada rute. Selainnya keluarkan m+1 nomor simpul hasil aturan stack tersebut, dipisahkan spasi.','Implementasikan Hierholzer iteratif dengan pointer adjacency dan used[edge_id].','Sisi ditandai sekali, sementara pop menghasilkan subrute tertutup yang disisipkan ketika daftar dibalik. Syarat Euler memastikan seluruh m sisi habis dalam satu komponen. Memproses adjacency dalam urutan input menegakkan tie-break persis.')]
    for i,(t,l,story,out,idea,proof) in enumerate(cfg,1):ps.append(problem(t,l,story,'Baris pertama n m; m baris u v. Simpul 1..n. '+('Jalan berarah u→v.' if i==2 else 'Jalan tak berarah.')+' Loop dan sisi paralel boleh. Jika m=0, rute diam di simpul 1 dianggap sirkuit; latihan 3 menghasilkan satu angka 1. Simpul terisolasi lain tidak wajib dikunjungi.\n\n**Keluaran:** '+out,'1 ≤ n ≤ 100000; 0 ≤ m ≤ 200000.',euler_cpp(i),lambda s,i=i:euler_oracle(i,s),[graph(n,e) for n,e in base],idea,proof,'O(n+m) waktu selain operasi DSU O(m α(n)); O(n+m) memori.','Derajat saja tidak cukup: dua sirkuit terpisah mustahil. Loop tak berarah menambah derajat dua. Dua entri adjacency kabel paralel/loop harus berbagi ID yang benar.'))
    add(230,'Eulerian Path dan Circuit - Hierholzer','Day-121 - Lintasan & Sirkuit Euler.pptx',
    '''Lintasan Euler menghabiskan setiap **sisi** sekali. Simpul boleh diulang; inilah pembeda dari Hamilton yang meminta simpul. Paket mengikuti ROADMAP Day230, walaupun slide Euler bernomor Day121; Day121 ROADMAP sendiri adalah bipartit.

**Tak berarah.** Abaikan simpul terisolasi ketika mengecek keterhubungan. Semua derajat genap memberi sirkuit; tepat dua derajat ganjil memberi lintasan terbuka; jumlah ganjil lain mustahil. Self-loop menyumbang derajat dua. Graf tanpa sisi punya rute diam di simpul 1 sesuai kontrak.

**Berarah.** Semua out=in memberi sirkuit. Untuk lintasan terbuka, satu simpul memiliki out−in=1 (awal), satu in−out=1 (akhir), lainnya seimbang. Periksa keterhubungan lemah atas simpul aktif. Menambahkan sisi akhir→awal mengubah kasus lintasan menjadi sirkuit.

**Hierholzer.** Dorong awal ke stack. Selama puncak mempunyai sisi belum dipakai, ambil sisi dan dorong tetangga. Jika buntu, pop ke hasil. Balik hasil pada akhir. Simpan pointer per simpul dan used per ID sisi, sehingga setiap entri adjacency diperiksa sekali. Panjang hasil harus m+1 untuk rute lengkap.

**Trace.** Sisi ID1:1—2, ID2:2—3, ID3:3—1. Stack tumbuh [1],[1,2],[1,2,3],[1,2,3,1]; pop menghasilkan [1,3,2,1], balik menjadi [1,2,3,1]. Dua segitiga terpisah semuanya genap tetapi gagal keterhubungan.

**Determinisme.** Latihan rekonstruksi mendefinisikan aturan ID terkecil pada prosedur stack. Ini adalah aturan operasional yang tunggal; tidak mengklaim sebagai urutan simpul leksikografis terkecil. Jangan mencetak urutan saat mendorong saja: cabang yang baru disisipkan membutuhkan pencatatan saat pop.
''',ps,[('Awal Rute yang Sah','Input n m dan sisi tak berarah. Keluarkan semua simpul yang dapat menjadi awal rute Euler dalam urutan naik, atau TIDAK. Untuk m=0, semua simpul dapat menjadi awal. n≤100000,m≤200000.','3 2\n1 2\n2 3\n','1 3\n','3 0\n','1 2 3\n'),('Domino Melingkar','Input m lalu m pasangan a b, 0≤a,b≤6. Setiap domino boleh dibalik. Keluarkan YA jika semua dapat disusun melingkar cocok ujungnya, TIDAK selainnya; m=0 dianggap YA. m≤200000.','3\n0 1\n1 2\n2 0\n','YA\n','2\n0 1\n2 3\n','TIDAK\n'),('Rute Berarah dari S','Input n m s t, lalu m sisi berarah. Keluarkan YA jika ada rute memakai semua sisi sekali dari s ke t, TIDAK selainnya. Jika m=0 perlu s=t. n≤100000,m≤200000.','3 2 1 3\n1 2\n2 3\n','YA\n','3 2 3 1\n1 2\n2 3\n','TIDAK\n')])
