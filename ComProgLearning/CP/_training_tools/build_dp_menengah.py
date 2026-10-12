"""Rebuild original training packs 155..168; fixed seed, brute-force audits."""
from pathlib import Path
import random,itertools,functools,math,json,subprocess,tempfile,time,sys
ROOT=Path(__file__).resolve().parents[1]
MOD=1000000007
R=random.Random(155168)
SPECS={}
HEAD='''#include <iostream>\n#include <vector>\n#include <algorithm>\n#include <numeric>\n#include <string>\n#include <queue>\n#include <functional>\n#include <iomanip>\n#include <bitset>\n#include <cstdint>\n#include <limits>\nusing namespace std;\nusing ll=long long;\nconst ll MOD=1000000007, INF=4000000000000000000LL;\n'''
def cpp(body):return HEAD+'int main(){ios::sync_with_stdio(false);cin.tie(nullptr);\n'+body+'\n}\n'
def nums(a):return ' '.join(map(str,a))+'\n'
def mat(a):return ''.join(nums(row) for row in a)
def add(day,title,story,io,co,body,solve,brute,cases,rand,idea,proof,complexity):
    p=dict(title=title,story=story,io=io,constraints=co,code=cpp(body),solve=solve,brute=brute,cases=cases,rand=rand,idea=idea,proof=proof,complexity=complexity)
    SPECS.setdefault(day,[]).append(p)

# 155: three genuinely different sufficient-state decisions.
def stock(s):
    a=list(map(int,s.split()));n,f=a[:2];prices=a[2:];free,hold,sold=0,-10**30,-10**30
    for x in prices:free,hold,sold=max(free,sold),max(hold,free-x),hold+x-f
    return str(max(free,sold))+'\n'
def stock_b(s):
    a=list(map(int,s.split()));n,f=a[:2];p=a[2:]
    def go(i,h,c):
        if i==n:return -10**30 if h else 0
        ans=go(i+1,h,0)
        if h:ans=max(ans,p[i]-f+go(i+1,0,1))
        elif not c:ans=max(ans,-p[i]+go(i+1,1,0))
        return ans
    return str(go(0,0,0))+'\n'
add(155,'Kios Kamera Sekaten','Nara memperdagangkan satu kamera bekas. Setiap hari ia boleh diam, membeli bila tidak memegang kamera, atau menjual kamera yang sudah dipegang sejak hari sebelumnya. Sesudah menjual, hari berikutnya wajib istirahat dari pembelian. Setiap penjualan dikenai biaya F. Ia mulai tanpa kamera dan harus berakhir tanpa kamera. Hitung laba maksimum; tidak bertransaksi diperbolehkan.','Baris pertama N F. Baris kedua N harga. Keluaran satu bilangan: laba maksimum.','1 ≤ N ≤ 100000; 0 ≤ F,harga ≤ 10^9.',r'''int n;ll f;cin>>n>>f;ll a=0,b=-INF,c=-INF;for(int i=0;i<n;i++){ll x;cin>>x;ll na=max(a,c),nb=max(b,a-x),nc=(b==-INF?-INF:b+x-f);a=na;b=nb;c=nc;}cout<<max(a,c)<<'\n';''',stock,stock_b,['1 0\n5\n','5 0\n1 2 3 0 2\n','6 2\n1 3 2 8 4 9\n','4 9\n5 4 3 2\n','4 0\n0 0 0 0\n','4 0\n0 1000000000 0 1000000000\n','2 3\n1 5\n','3 0\n5 1 7\n'],lambda: f'{(n:=R.randint(1,9))} {R.randint(0,7)}\n'+nums([R.randint(0,15) for _ in range(n)]),'Simpan free (boleh membeli), hold (memegang), sold (baru menjual). Dari hari lama: free′=max(free,sold), hold′=max(hold,free−harga), sold′=hold+harga−F. Awal (0,−∞,−∞); jawaban max(free,sold).','Induksi hari: tiga keadaan saling lepas dan mencakup seluruh riwayat sah. Membeli hanya dari free menegakkan jeda; menjual hanya dari hold menegakkan kepemilikan. Setiap aksi sah muncul tepat pada salah satu transisi.','Waktu O(N), memori O(1).')
def residues(s):
    a=list(map(int,s.split()));n,m=a[:2];dp=[1]+[0]*(m-1)
    for x in a[2:]:
        nd=dp[:]
        for j,v in enumerate(dp):nd[(j+x)%m]=(nd[(j+x)%m]+v)%MOD
        dp=nd
    return str((dp[0]-1)%MOD)+'\n'
def residues_b(s):
    a=list(map(int,s.split()));n,m=a[:2];a=a[2:]
    return str(sum(sum(a[i] for i in range(n) if mask>>i&1)%m==0 for mask in range(1,1<<n))%MOD)+'\n'
add(155,'Paket Kue Sisa Nol','Panitia membentuk satu paket dari sebagian kotak kue berlabel berbeda. Kotak i berisi A_i kue. Paket tidak boleh kosong dan total kue harus habis dibagi M. Dua pilihan kotak berbeda dihitung berbeda, meskipun jumlah kuenya sama. Hitung banyak paket modulo 1000000007.','N M, diikuti N bilangan A_i. Keluaran banyak paket modulo 1000000007.','1 ≤ N ≤ 2000; 1 ≤ M ≤ 100; 0 ≤ A_i ≤ 10^9.',r'''int n,m;cin>>n>>m;vector<ll>d(m);d[0]=1;while(n--){ll x;cin>>x;vector<ll>e=d;for(int j=0;j<m;j++)e[(j+x)%m]=(e[(j+x)%m]+d[j])%MOD;d.swap(e);}cout<<(d[0]+MOD-1)%MOD<<'\n';''',residues,residues_b,['3 3\n1 2 3\n','1 7\n0\n','3 1\n0 4 9\n','1 2\n1\n','4 5\n0 0 0 0\n','4 3\n1 1 1 1\n','2 100\n1000000000 1000000000\n','5 7\n2 4 6 8 10\n'],lambda:f'{(n:=R.randint(1,12))} {R.randint(1,8)}\n'+nums([R.randint(0,20) for _ in range(n)]),'dp[r] menghitung subset prefiks bersisa r, termasuk subset kosong. Untuk setiap kotak, salin pilihan lewati dan tambahkan pilihan ambil ke (r+A_i)%M. Kurangi satu dari dp[0] di akhir.','Dua riwayat dengan sisa sama memberi sisa akhir sama untuk pilihan kotak masa depan mana pun. Pembagian subset menurut apakah memuat kotak terakhir bersifat unik; dua cabang itu tidak tumpang tindih.','Waktu O(NM), memori O(M).')
def nonadj(s):
    a=list(map(int,s.split()));n,k=a[:2];a=a[2:];d={(0,0):0}
    for x in a:
        nd={}
        for (c,t),v in d.items():
            nd[c,0]=max(nd.get((c,0),-10**30),v)
            if not t and c<k:nd[c+1,1]=max(nd.get((c+1,1),-10**30),v+x)
        d=nd
    v=max([v for (c,t),v in d.items() if c==k],default=None)
    return ('IMPOSSIBLE' if v is None else str(v))+'\n'
def nonadj_b(s):
    a=list(map(int,s.split()));n,k=a[:2];a=a[2:];v=[sum(a[i] for i in comb) for comb in itertools.combinations(range(n),k) if all(y>x+1 for x,y in zip(comb,comb[1:]))]
    return str(max(v) if v else 'IMPOSSIBLE')+'\n'
add(155,'Panggung Tanpa Bentrok','Tersedia N slot panggung berurutan dengan nilai kepuasan A_i, yang boleh negatif. Pilih tepat K slot; dua slot bertetangga tidak boleh sama-sama dipilih. Hitung kepuasan maksimum atau IMPOSSIBLE jika tidak ada pilihan sah.','N K, diikuti N nilai. Keluaran nilai maksimum atau teks IMPOSSIBLE.','1 ≤ N ≤ 2000; 0 ≤ K ≤ min(N,100); −10^9 ≤ A_i ≤ 10^9.',r'''int n,k;cin>>n>>k;vector<vector<ll>>d(k+1,vector<ll>(2,-INF));d[0][0]=0;while(n--){ll x;cin>>x;vector<vector<ll>>e(k+1,vector<ll>(2,-INF));for(int j=0;j<=k;j++){e[j][0]=max(d[j][0],d[j][1]);if(j&&d[j-1][0]!=-INF)e[j][1]=d[j-1][0]+x;}d.swap(e);}ll z=max(d[k][0],d[k][1]);if(z==-INF)cout<<"IMPOSSIBLE\n";else cout<<z<<'\n';''',nonadj,nonadj_b,['5 2\n8 9 3 10 4\n','1 0\n-5\n','3 2\n-3 -1 -4\n','2 2\n5 9\n','1 1\n1000000000\n','4 2\n0 0 0 0\n','5 3\n1 100 1 100 1\n','3 3\n1 2 3\n'],lambda:f'{(n:=R.randint(1,11))} {R.randint(0,n)}\n'+nums([R.randint(-10,15) for _ in range(n)]),'State dp[j][t] menyimpan nilai terbaik setelah prefiks diproses, memilih tepat j, dengan t menyatakan slot terakhir dipilih. Lewati membaca kedua t lama; ambil hanya membaca dp[j−1][0].','Induksi prefiks memisahkan pilihan menurut slot terakhir. Menyimpan j mencegah solusi memilih terlalu sedikit saat nilai negatif, dan t memastikan larangan tetangga. Nilai −∞ menyatakan state yang sungguh mustahil.','Waktu O(NK), memori O(K).')
# 156: TSP, Hamilton counting, coupon. Diagonal ignored, -1 forbids an arc.
def route_solve(s,mode,brute=False):
    z=list(map(int,s.split()));n=z[0];a=[z[1+i*n:1+(i+1)*n] for i in range(n)]
    if n==1:return '1\n' if mode==1 else '0\n'
    if brute:
        vals=[]
        for p in itertools.permutations(range(1,n)):
            q=(0,)+p+(() if mode==1 else (0,))
            if mode==1 and q[-1]!=n-1:continue
            w=[a[u][v] for u,v in zip(q,q[1:])]
            if min(w)<0:continue
            vals.append(sum(w)-(max(w) if mode==2 else 0))
        return str(len(vals)%MOD if mode==1 else min(vals,default=-1))+'\n'
    d={(1,0):0 if mode!=1 else 1};e={(1,0):10**30}
    for mask in range(1,1<<n,2):
        for u in range(n):
            if (mask,u) not in d:continue
            for v in range(1,n):
                if mask>>v&1 or a[u][v]<0:continue
                key=(mask|1<<v,v);w=a[u][v]
                if mode==1:d[key]=(d.get(key,0)+d[mask,u])%MOD
                else:
                    d[key]=min(d.get(key,10**30),d[mask,u]+w)
                    e[key]=min(e.get(key,10**30),e.get((mask,u),10**30)+w,d[mask,u])
    full=(1<<n)-1
    if mode==1:return str(d.get((full,n-1),0))+'\n'
    ans=10**30
    for u in range(1,n):
        if a[u][0]>=0:
            ans=min(ans,d.get((full,u),10**30)+a[u][0])
            if mode==2:ans=min(ans,e.get((full,u),10**30)+a[u][0],d.get((full,u),10**30))
    return str(ans if ans<10**30 else -1)+'\n'
routebody=r'''int n;cin>>n;vector<vector<ll>>a(n,vector<ll>(n));for(auto&r:a)for(auto&x:r)cin>>x;const int MODE=MODEV;int z=1<<n;if(n==1){cout<<(MODE==1?1:0)<<'\n';return 0;}vector<vector<ll>>d(z,vector<ll>(n,MODE==1?0:INF)),e(z,vector<ll>(n,INF));d[1][0]=MODE==1?1:0;for(int m=1;m<z;m+=2)for(int u=0;u<n;u++){if(MODE!=1&&d[m][u]==INF)continue;for(int v=1;v<n;v++)if(!(m>>v&1)&&a[u][v]>=0){int t=m|(1<<v);if(MODE==1)d[t][v]=(d[t][v]+d[m][u])%MOD;else{d[t][v]=min(d[t][v],d[m][u]+a[u][v]);e[t][v]=min({e[t][v],e[m][u]+a[u][v],d[m][u]});}}}if(MODE==1){cout<<d[z-1][n-1]<<'\n';return 0;}ll ans=INF;for(int u=1;u<n;u++)if(a[u][0]>=0){ans=min(ans,d[z-1][u]+a[u][0]);if(MODE==2)ans=min({ans,e[z-1][u]+a[u][0],d[z-1][u]});}cout<<(ans==INF?-1:ans)<<'\n';'''
route_cases=['1\n0\n','3\n0 4 10\n3 0 2\n7 6 0\n','3\n0 1 -1\n-1 0 1\n-1 -1 0\n','2\n0 -1\n5 0\n','2\n0 0\n0 0\n','4\n0 8 2 9\n4 0 7 3\n5 6 0 1\n2 4 9 0\n','2\n0 1000000000\n1000000000 0\n','4\n0 1 1 1\n1 0 1 1\n1 1 0 1\n1 1 1 0\n']
def route_rand():
    n=R.randint(1,7);return nums([n])+mat([[0 if i==j else (R.randint(0,15) if R.random()>.2 else -1) for j in range(n)]for i in range(n)])
for mode,title,story,idea in [
(0,'Tur Perpustakaan Keliling','Mobil pustaka mulai di desa 1, mengunjungi setiap desa lain tepat sekali, lalu kembali ke desa 1. Biaya jalan berarah boleh berbeda. Nilai −1 berarti tidak ada jalan langsung; melewati desa lain sebagai perantara tidak diperbolehkan. Hitung biaya minimum atau −1 bila mustahil. Untuk N=1, tur kosong berbiaya 0.','dp[mask][u] = biaya minimum mengunjungi mask dan berhenti di u. Awal dp[1][0]=0. Tambah desa v yang belum dikunjungi melalui sisi sah. Jawaban min_u dp[full][u]+biaya[u][0].'),
(1,'Estafet Paket Nusantara','Paket mulai di desa 1 dan harus berakhir di desa N setelah mengunjungi setiap desa tepat sekali. Nilai −1 menandakan tidak ada jalan; nilai nonnegatif hanya penanda jalan sah (besar biaya diabaikan). Hitung banyak urutan kunjungan modulo 1000000007. N=1 memiliki satu urutan kosong perpindahan.','dp[mask][u] menghitung rute prefiks. Awal 1, setiap perpindahan sah menambahkan banyak cara; jawaban hanya dp[full][N−1]. Jangan menambahkan sisi pulang.'),
(2,'Kupon Kapal Terakhir','Kurir harus melakukan tur seperti berikut: mulai di pelabuhan 1, kunjungi semua pelabuhan tepat sekali, lalu kembali ke 1. Ia mempunyai paling banyak satu kupon yang membuat SATU lintasan yang tersedia gratis, termasuk lintasan pulang. −1 berarti tidak ada lintasan dan kupon tidak boleh menciptakan lintasan itu. Cari biaya minimum atau −1. N=1 membutuhkan 0.','Tambahkan dimensi kupon terpakai. Pada setiap sisi boleh membayar; dari kupon belum terpakai boleh pindah ke terpakai tanpa biaya. Evaluasi opsi kupon pada sisi pulang juga.')]:
    add(156,title,story,'Baris pertama N; berikutnya matriks biaya N×N. Keluaran satu bilangan sesuai tugas.','1 ≤ N ≤ 15; diagonal 0; elemen lain −1 atau 0..10^9.',routebody.replace('MODEV',str(mode)),lambda s,m=mode:route_solve(s,m),lambda s,m=mode:route_solve(s,m,True),route_cases,route_rand,idea,'Setiap rute sah mempunyai satu desa terakhir dan satu prefiks yang unik. Menghapus langkah terakhir menghasilkan state dengan satu bit lebih sedikit. Induksi jumlah bit membuktikan transisi mencakup seluruh rute sah. Dimensi akhir dan kupon (jika diperlukan) menyimpan semua informasi yang memengaruhi kelanjutan.','Waktu O(N² 2^N), memori O(N 2^N).')
# 157: one dimension, three objective algebras.
def assignment(s,mode,brute=False):
    z=list(map(int,s.split()));n=z[0];a=[z[1+i*n:1+(i+1)*n] for i in range(n)]
    if brute:
        v=[[a[i][p[i]] for i in range(n)]for p in itertools.permutations(range(n))];v=[w for w in v if min(w)>=0]
        return str(len(v)%MOD if mode==1 else min((sum(w) if mode==0 else max(w) for w in v),default=-1))+'\n'
    d=[0 if mode==1 else 10**30]*(1<<n);d[0]=1 if mode==1 else 0
    for mask in range((1<<n)-1):
        i=mask.bit_count()
        for j in range(n):
            if mask>>j&1 or a[i][j]<0:continue
            t=mask|1<<j
            if mode==1:d[t]=(d[t]+d[mask])%MOD
            else:d[t]=min(d[t],d[mask]+a[i][j] if mode==0 else max(d[mask],a[i][j]))
    return str(d[-1] if d[-1]<10**30 else -1)+'\n'
assignbody=r'''int n;cin>>n;vector<vector<ll>>a(n,vector<ll>(n));for(auto&r:a)for(auto&x:r)cin>>x;const int MODE=MODEV;int z=1<<n;vector<ll>d(z,MODE==1?0:INF);d[0]=MODE==1?1:0;for(int mask=0;mask<z-1;mask++){int i=__builtin_popcount((unsigned)mask);for(int j=0;j<n;j++)if(!(mask>>j&1)&&a[i][j]>=0){int t=mask|(1<<j);if(MODE==1)d[t]=(d[t]+d[mask])%MOD;else if(d[mask]!=INF)d[t]=min(d[t],MODE==0?d[mask]+a[i][j]:max(d[mask],a[i][j]));}}cout<<(d.back()==INF?-1:d.back())<<'\n';'''
for mode,title,story,idea in [(0,'Relawan dan Posko','N relawan harus dipasangkan satu-satu dengan N posko. Biaya penempatan i ke j adalah C_ij; −1 berarti relawan tidak memenuhi syarat. Minimalkan jumlah biaya atau cetak −1 bila mustahil.','dp[mask] biaya minimum menempatkan popcount(mask) relawan pertama. Relawan berikutnya i=popcount(mask); coba posko belum terpakai.'),(1,'Kunci Ruang Arsip','N kunci bernomor dan N pintu harus dipasangkan satu-satu. C_ij=−1 berarti tidak cocok; nilai nonnegatif berarti cocok dan besar nilainya diabaikan. Hitung banyak pemasangan sah modulo 1000000007.','dp[mask] banyak pemasangan untuk relawan/kunci pertama. Inisialisasi dp[0]=1, gabungkan menggunakan penjumlahan modulo.'),(2,'Evakuasi Serentak','N tim bergerak serentak, masing-masing menuju satu dari N titik jemput berbeda. Waktu tim i ke titik j adalah C_ij; −1 berarti tidak bisa. Seluruh operasi selesai ketika tim paling lambat tiba. Minimalkan waktu selesai tersebut; cetak −1 bila mustahil.','Gunakan dp[mask] waktu selesai minimum. Transisi bukan jumlah, melainkan min(dp[baru],max(dp[mask],C_ij)).')]:
    add(157,title,story,'N lalu N baris masing-masing N nilai C_ij. Keluaran satu bilangan.','1 ≤ N ≤ 18; −1 ≤ C_ij ≤ 10^9.',assignbody.replace('MODEV',str(mode)),lambda s,m=mode:assignment(s,m),lambda s,m=mode:assignment(s,m,True),['1\n0\n','2\n5 1\n2 6\n','2\n-1 -1\n3 4\n','1\n-1\n','3\n1 1 1\n1 1 1\n1 1 1\n','2\n1000000000 1000000000\n1000000000 1000000000\n','3\n0 -1 -1\n-1 0 -1\n-1 -1 0\n','3\n1 100 100\n1 100 100\n100 1 1\n'],route_rand,idea,'Setiap pemasangan untuk i relawan mempunyai himpunan posko terpakai tertentu. Urutan relawan selalu tetap sehingga i dapat disimpulkan dari popcount, tidak perlu dimensi lain. Pilihan posko terakhir mempartisi semua pemasangan; operasi jumlah/min/max sesuai definisi objektif menghasilkan nilai benar.','Waktu O(N 2^N), memori O(2^N).')
# 158: SOS and exact subset convolution.
def sos(s,mode,brute=False):
    z=list(map(int,s.split()));b=z[0];n=1<<b;a=z[1:1+n]
    if mode==2:
        c=z[1+n:];o=[]
        for m in range(n):
            t=m;v=0
            while True:
                v+=a[t]*c[m^t]
                if t==0:break
                t=(t-1)&m
            o.append(v%MOD)
        return nums(o)
    if brute:f=[sum(a[t] for t in range(n) if t&m==t) for m in range(n)]
    else:
        f=a[:]
        for j in range(b):
            for m in range(n):
                if m>>j&1:f[m]+=f[m^(1<<j)]
    if mode==0:return nums(f)
    ans=sum(a[m]*f[(n-1)^m] for m in range(n))-a[0]
    return str(ans//2)+'\n'
sosbody=r'''int b;cin>>b;int n=1<<b;vector<ll>a(n),f;for(ll&x:a)cin>>x;const int MODE=MODEV;if(MODE==2){vector<ll>c(n);for(ll&x:c)cin>>x;for(int m=0;m<n;m++){ll z=0;for(int t=m;;t=(t-1)&m){z=(z+a[t]*c[m^t])%MOD;if(t==0)break;}cout<<z<<(m+1==n?'\n':' ');}return 0;}f=a;for(int j=0;j<b;j++)for(int m=0;m<n;m++)if(m>>j&1)f[m]+=f[m^(1<<j)];if(MODE==0){for(int m=0;m<n;m++)cout<<f[m]<<(m+1==n?'\n':' ');}else{ll z=0;for(int m=0;m<n;m++)z+=a[m]*f[(n-1)^m];cout<<(z-a[0])/2<<'\n';}'''
for mode,title,story,co,idea in [(0,'Buku Resep Semua Bahan','Terdapat B jenis bahan. Mask m menyatakan bahan yang tersedia; A[m] adalah banyak resep yang membutuhkan tepat mask tersebut. Untuk SETIAP m, hitung banyak resep yang seluruh bahannya tersedia di m. Resep tanpa bahan (mask 0) tetap dihitung.','0 ≤ B ≤ 20; 0 ≤ A[m] ≤ 10^6.','Mulai f=A. Untuk bit j, bila bit itu menyala pada m, tambah f[m tanpa bit j]. Setelah j diproses, perbedaan subset hanya boleh pada j bit yang sudah diproses.'),(1,'Dua Regu Tanpa Tumpang Tindih','A[m] regu memiliki himpunan keahlian m. Semua regu adalah individu berbeda. Pilih dua regu BERBEDA, tanpa memperhatikan urutan, dengan irisan keahlian kosong. Hitung banyak pasangan; regu bermask 0 bisa dipasangkan dengan regu kosong lain.','0 ≤ B ≤ 20; A[m] ≥ 0; jumlah A[m] ≤ 10^6.','SOS frekuensi memberi banyak pasangan berarah A[m]·f[full XOR m]. Kurangi A[0] untuk pasangan individu dengan dirinya sendiri, kemudian bagi 2.'),(2,'Dua Dapur Satu Pesanan','Untuk setiap mask S, A[S] adalah pilihan menu dapur pertama yang memakai tepat S, dan C[S] pilihan dapur kedua. Untuk setiap pesanan M, bahan harus dibagi tanpa irisan dan seluruh M dipakai. Hitung jumlah A[S]·C[M\\S] untuk seluruh S subset M, modulo 1000000007. Kedua dapur berlabel; subset kosong diperbolehkan.','0 ≤ B ≤ 13; 0 ≤ A[m],C[m] < 1000000007.','Enumerasi setiap submask S dari M, termasuk 0. Tambahkan A[S]C[M XOR S]. Ini subset convolution langsung O(3^B), bukan sekadar perkalian dua hasil SOS.')]:
    cases=['0\n2\n','2\n1 2 3 4\n','1\n0 0\n','1\n3 0\n','2\n0 1 1 0\n','3\n1 0 0 0 0 0 0 1\n','2\n0 0 0 1000000\n','0\n0\n']
    if mode==2:cases=[s+nums([i+1 for i in range(1<<int(s.split()[0]))]) for s in cases]
    def rand(m=mode):
        b=R.randint(0,5);n=1<<b;s=nums([b])+nums([R.randint(0,8)for _ in range(n)]);return s+(nums([R.randint(0,8)for _ in range(n)]) if m==2 else '')
    add(158,title,story,'B lalu 2^B nilai A menurut urutan mask 0..2^B−1.'+(' Berikutnya 2^B nilai C.' if mode==2 else '')+' Keluaran '+('satu bilangan.' if mode==1 else '2^B jawaban berurutan.'),co,sosbody.replace('MODEV',str(mode)),lambda s,m=mode:sos(s,m),lambda s,m=mode:sos(s,m,True),cases,rand,idea,'Untuk SOS, pisahkan subset berdasarkan apakah bit j dihapus: kedua bagian saling lepas dan tepat digabung oleh transisi. Untuk convolution, memilih S menentukan komplemennya M\\S secara tunggal; enumerasi tersebut bijektif dengan seluruh pembagian bahan sah. Pada pasangan regu, hanya mask kosong mempunyai irisan kosong dengan dirinya, sehingga koreksi diagonal tepat.','SOS/pasangan O(B2^B) waktu, O(2^B) memori; convolution langsung O(3^B) waktu, O(2^B) memori. Batas B=13 sengaja untuk versi langsung.')
# 159 digit boundaries: zero represented canonically; leading zero ignored.
def digit(s,mode,brute=False):
    z=list(map(int,s.split()));lo,hi,m,k=z
    def good(x):
        st=str(x)
        if mode==0:return sum(map(int,st))%m==0
        if mode==1:return all(a!=b for a,b in zip(st,st[1:]))
        return sum(c!='0' for c in st)==k and x%m==0
    if brute:return str(sum(good(x) for x in range(lo,hi+1)))+'\n'
    def f(x):
        if x<0:return 0
        st=str(x)
        @functools.lru_cache(None)
        def go(i,t,r,last,c):
            if i==len(st):return int((r==0) if mode==0 else (True if mode==1 else c==k and r==0))
            ans=0
            for d in range((int(st[i]) if t else 9)+1):
                if mode==1 and last!=10 and d==last:continue
                nr=(r+d)%m if mode==0 else ((r*10+d)%m if mode==2 else 0)
                nl=10 if last==10 and d==0 else d
                nc=c+(d!=0) if mode==2 else 0
                if mode==2 and nc>k:continue
                ans+=go(i+1,t and d==int(st[i]),nr,nl if mode==1 else 10,nc)
            return ans
        return go(0,True,0,10,0)
    return str(f(hi)-f(lo-1))+'\n'
digitbody=r'''ll L,R;int m,k;cin>>L>>R>>m>>k;const int MODE=MODEV;auto count=[&](ll x){if(x<0)return 0LL;string s=to_string(x);int n=s.size();vector<ll>memo(20*2*m*11*20,-1);function<ll(int,bool,int,int,int)>go=[&](int i,bool t,int r,int last,int c)->ll{if(i==n)return MODE==0?r==0:(MODE==1?1:(c==k&&r==0));int key=((((i*2+t)*m+r)*11+last)*20+c);ll&ans=memo[key];if(ans!=-1)return ans;ans=0;int hi=t?s[i]-'0':9;for(int d=0;d<=hi;d++){if(MODE==1&&last!=10&&d==last)continue;int nr=MODE==0?(r+d)%m:(MODE==2?(r*10+d)%m:0);int nl=last==10&&d==0?10:d;int nc=MODE==2?c+(d!=0):0;if(MODE==2&&nc>k)continue;ans+=go(i+1,t&&d==hi,nr,MODE==1?nl:10,nc);}return ans;};return go(0,true,0,10,0);};cout<<count(R)-count(L-1)<<'\n';'''
for mode,title,story,idea in [(0,'Nomor Antrean Seimbang','Nomor antrean adalah bilangan bulat dalam [L,R]. Hitung nomor yang jumlah digit desimalnya habis dibagi M. Angka 0 termasuk dan jumlah digitnya 0. Parameter K dibaca tetapi tidak digunakan pada soal ini.','State (pos,tight,sisaJumlah). Digit d mengubah sisa menjadi (r+d)%M. Leading zero tidak mengubah jumlah digit.'),(1,'Nomor Bus Tanpa Gema','Nomor bus berupa bilangan dalam [L,R] dengan penulisan desimal biasa tanpa nol di depan. Dua digit berdampingan tidak boleh sama. Nomor 0 sah. M dan K dibaca tetapi tidak dipakai pada soal ini.','State (pos,tight,last). last=10 artinya digit signifikan belum dimulai. Nol pengisi di depan mempertahankan sentinel; sesudah mulai, digit yang sama dengan last dilarang.'),(2,'Lampion Digital Hemat','Display menunjukkan bilangan dalam [L,R] tanpa nol di depan. Tepat K digitnya harus bukan nol, dan nilai bilangannya harus habis dibagi M. Angka 0 memiliki nol digit bukan nol. Hitung banyak nomor yang sah.','State (pos,tight,r,c), dengan r sisa NILAI bilangan dan c jumlah digit bukan nol. r′=(10r+d)%M, c′=c+[d≠0].')]:
    add(159,title,story,'Satu baris L R M K. Keluaran banyak bilangan yang memenuhi syarat.','0 ≤ L ≤ R ≤ 10^18; 1 ≤ M ≤ 50; 0 ≤ K ≤ 19.',digitbody.replace('MODEV',str(mode)),lambda s,m=mode:digit(s,m),lambda s,m=mode:digit(s,m,True),['0 0 1 0\n','1 30 3 1\n','98 112 7 2\n','0 9 5 0\n','100 100 2 1\n','999 1001 3 3\n','1 1 50 19\n','90 110 10 1\n'],lambda: f'{(l:=R.randint(0,500))} {l+R.randint(0,300)} {R.randint(1,10)} {R.randint(0,4)}\n',idea+' Definisikan F(x)=jumlah sah di [0,x]; F(x)=0 bila x<0. Jawaban F(R)−F(L−1).','Induksi posisi: tight menjamin prefiks tidak pernah melampaui batas. Setiap bilangan memiliki satu representasi panjang tetap dengan nol pengisi, sehingga muncul sekali. State tambahan persis menentukan apakah sufiks dapat diterima. Memo direset untuk setiap F agar batas atas lama tidak bocor.','Panjang D≤19. Waktu O(D·M·20·11·10) batas atas, memori O(D·M·20·11); hanya dimensi relevan yang terjangkau.')
# Tree parsing / iterative parent order.
TREE=r'''int n;cin>>n;vector<ll>a(n);for(ll&x:a)cin>>x;vector<vector<int>>g(n);for(int i=1,u,v;i<n;i++){cin>>u>>v;--u;--v;g[u].push_back(v);g[v].push_back(u);}vector<int>p(n,-1),ord(1,0);p[0]=0;for(int i=0;i<n;i++){int u=ord[i];for(int v:g[u])if(v!=p[u]){p[v]=u;ord.push_back(v);}}'''
def tree_parse(s,extra=False):
    z=list(map(int,s.split()));n=z[0];k=z[1]if extra else None;st=2 if extra else 1;a=z[st:st+n];es=list(zip(z[st+n::2],z[st+n+1::2]));g=[[]for _ in range(n)]
    for u,v in es:g[u-1].append(v-1);g[v-1].append(u-1)
    p=[-1]*n;p[0]=0;o=[0]
    for u in o:
        for v in g[u]:
            if v!=p[u]:p[v]=u;o.append(v)
    return n,k,a,g,p,o
def treecase(a,edges,k=None):return nums([len(a)]+([]if k is None else[k]))+nums(a)+mat(edges)
def treerand(extra=False):
    n=R.randint(1,10);return treecase([R.randint(0,15)for _ in range(n)],[(i+1,R.randint(1,i))for i in range(1,n)],R.randint(0,n)if extra else None)
treecases=[treecase([5],[]),treecase([6,8,7],[(1,2),(2,3)]),treecase([10,4,4,4],[(1,2),(1,3),(1,4)]),treecase([0],[]),treecase([0,0],[(1,2)]),treecase([10**9]*3,[(1,2),(2,3)]),treecase([1,9,1,9,1],[(1,2),(2,3),(3,4),(4,5)]),treecase([3,7,5,2,8],[(1,2),(1,3),(3,4),(3,5)])]
def treebasic(s,mode,brute=False):
    n,k,a,g,p,o=tree_parse(s)
    if brute:
        vals=[]
        for mask in range(1<<n):
            ok=all(((mask>>u&1) or (mask>>v&1)) if mode==2 else not((mask>>u&1)and(mask>>v&1)) for u in range(n)for v in g[u]if u<v)
            if ok:vals.append(sum(a[i]for i in range(n)if mask>>i&1))
        return str(len(vals)%MOD if mode==1 else (min(vals)if mode==2 else max(vals)))+'\n'
    d=[[0,0]for _ in range(n)]
    for u in reversed(o):
        d[u]=[1,1]if mode==1 else[0,a[u]]
        for v in g[u]:
            if p[v]!=u:continue
            if mode==0:d[u][0]+=max(d[v]);d[u][1]+=d[v][0]
            elif mode==1:d[u][0]=d[u][0]*sum(d[v])%MOD;d[u][1]=d[u][1]*d[v][0]%MOD
            else:d[u][0]+=d[v][1];d[u][1]+=min(d[v])
    return str(sum(d[0])%MOD if mode==1 else(min(d[0])if mode==2 else max(d[0])))+'\n'
for mode,title,story,idea in [(0,'Pentas Kampung Bertetangga','Desa-desanya membentuk pohon. Desa i memberi kepuasan A_i jika menjadi lokasi pentas. Dua desa yang dihubungkan langsung tidak boleh sama-sama dipilih. Maksimalkan total kepuasan; memilih kosong diperbolehkan.','d[u][0]=Σ max(d[v][0],d[v][1]); d[u][1]=A_u+Σd[v][0].'),(1,'Lampu Malam Desa','Pada pohon desa, beberapa desa akan menyalakan lampu. Dua desa bertetangga tidak boleh sama-sama menyala. Hitung banyak pola termasuk semua padam, modulo 1000000007. Nilai A_i dibaca sebagai metadata desa dan tidak memengaruhi syarat.','d[u][0]=Π(d[v][0]+d[v][1]); d[u][1]=Πd[v][0]. Nilai daun (1,1).'),(2,'Pos Jaga Setiap Jalan','Bangun pos jaga di beberapa desa pada pohon, dengan biaya A_i. Setiap jalan harus memiliki pos di sedikitnya satu ujungnya. Hitung total biaya minimum. Pohon satu desa tidak membutuhkan pos.','d[u][0]=Σd[v][1]; d[u][1]=A_u+Σmin(d[v][0],d[v][1]).')]:
    body=TREE+r'''const int MODE=MODEV;vector<vector<ll>>d(n,vector<ll>(2));for(int i=n-1;i>=0;i--){int u=ord[i];d[u][0]=MODE==1?1:0;d[u][1]=MODE==1?1:a[u];for(int v:g[u])if(p[v]==u){if(MODE==0){d[u][0]+=max(d[v][0],d[v][1]);d[u][1]+=d[v][0];}else if(MODE==1){d[u][0]=d[u][0]*((d[v][0]+d[v][1])%MOD)%MOD;d[u][1]=d[u][1]*d[v][0]%MOD;}else{d[u][0]+=d[v][1];d[u][1]+=min(d[v][0],d[v][1]);}}}cout<<(MODE==1?(d[0][0]+d[0][1])%MOD:(MODE==0?max(d[0][0],d[0][1]):min(d[0][0],d[0][1])))<<'\n';'''
    add(160,title,story,'N; lalu N nilai A_i; lalu N−1 jalan u v tak berarah. Keluaran satu bilangan.','1 ≤ N ≤ 200000; 0 ≤ A_i ≤ 10^9; 1 ≤ u,v ≤ N; input dijamin pohon.',body.replace('MODEV',str(mode)),lambda s,m=mode:treebasic(s,m),lambda s,m=mode:treebasic(s,m,True),treecases,lambda:treerand(),idea+' Akar sementara desa 1. Susun parent dan urutan secara iteratif; proses urutan terbalik agar anak selesai lebih dulu.','Setelah status u dipilih, subtree anak saling bebas karena satu-satunya penghubung adalah u. Larangan atau kewajiban pada sisi u−v tepat diberikan oleh pilihan status v pada rumus. Induksi tinggi subtree membuktikan nilai; pilihan status akar menghasilkan jawaban seluruh pohon.','Waktu O(N), memori O(N). Traversal iteratif aman untuk pohon rantai.')
# 161 connected/root-closed cardinality convolution.
def treeknap(s,mode,brute=False):
    n,k,a,g,p,o=tree_parse(s,True)
    if brute:
        vals=[]
        for comb in itertools.combinations(range(n),k):
            st=set(comb)
            if not st:
                if mode==2:vals.append(0)
                continue
            if mode in(0,2) and 0 not in st:continue
            stack=[next(iter(st))];vis=set(stack)
            for u in stack:
                for v in g[u]:
                    if v in st and v not in vis:vis.add(v);stack.append(v)
            if vis==st:vals.append(sum(a[u]for u in st))
        return str(len(vals)%MOD if mode==2 else max(vals,default='IMPOSSIBLE'))+'\n'
    d=[None]*n
    for u in reversed(o):
        v=[0,1]if mode==2 else[-10**30,a[u]]
        for ch in g[u]:
            if p[ch]!=u:continue
            w=d[ch];nd=[0 if mode==2 else -10**30]*min(k+1,len(v)+len(w)-1)
            for i in range(1,min(k+1,len(v))):
                for j in range(min(len(w),k-i+1)):
                    if mode==2:nd[i+j]=(nd[i+j]+v[i]*(1 if j==0 else w[j]))%MOD
                    else:nd[i+j]=max(nd[i+j],v[i]+(0 if j==0 else w[j]))
            v=nd
        d[u]=v
    if mode==2:return str(1 if k==0 else (d[0][k]if k<len(d[0])else 0))+'\n'
    val=max((v[k]for v in (d if mode==1 else[d[0]])if k<len(v)),default=-10**30)
    return str(val if k>0 and val>-10**29 else 'IMPOSSIBLE')+'\n'
knapbody=r'''int n,k;cin>>n>>k;vector<ll>a(n);for(ll&x:a)cin>>x;vector<vector<int>>g(n);for(int i=1,u,v;i<n;i++){cin>>u>>v;--u;--v;g[u].push_back(v);g[v].push_back(u);}vector<int>p(n,-1),ord(1,0);p[0]=0;for(int i=0;i<n;i++)for(int v:g[ord[i]])if(v!=p[ord[i]]){p[v]=ord[i];ord.push_back(v);}const int MODE=MODEV;vector<vector<ll>>d(n);for(int z=n-1;z>=0;z--){int u=ord[z];d[u]={MODE==2?0:-INF,MODE==2?1:a[u]};for(int v:g[u])if(p[v]==u){vector<ll>e(min(k+1,int(d[u].size()+d[v].size()-1)),MODE==2?0:-INF);for(int i=1;i<(int)d[u].size()&&i<=k;i++)for(int j=0;j<(int)d[v].size()&&i+j<=k;j++){if(MODE==2)e[i+j]=(e[i+j]+d[u][i]*(j?d[v][j]:1))%MOD;else if(d[u][i]!=-INF&&(j==0||d[v][j]!=-INF))e[i+j]=max(e[i+j],d[u][i]+(j?d[v][j]:0));}d[u].swap(e);}}if(MODE==2){cout<<(k==0?1:(k<(int)d[0].size()?d[0][k]:0))<<'\n';return 0;}ll ans=-INF;if(k>0)for(int u=0;u<(MODE==1?n:1);u++)if(k<(int)d[u].size())ans=max(ans,d[u][k]);if(ans==-INF)cout<<"IMPOSSIBLE\n";else cout<<ans<<'\n';'''
for mode,title,story,idea in [(0,'Jaringan Internet dari Balai','Pilih tepat K desa terhubung pada pohon dan wajib memuat desa 1. Nilai manfaat A_i boleh negatif. Maksimalkan jumlah manfaat. K=0 tidak sah karena desa 1 wajib dipilih; cetak IMPOSSIBLE.','dp[u][j] nilai terbaik himpunan terhubung berukuran j di subtree u, WAJIB memuat u. Awal dp[u][1]=A_u. Saat menggabung anak, ambil 0 simpul atau himpunan yang memuat anak.'),(1,'Koridor Wisata Pilihan','Pilih tepat K desa yang membentuk satu komponen terhubung pada pohon. Tidak ada desa wajib. Nilai A_i boleh negatif. Maksimalkan total manfaat. K=0 dinyatakan IMPOSSIBLE.','Gunakan state terhubung memuat u, lalu ambil maksimum dp[u][K] atas seluruh u; u menjadi simpul tertinggi dari komponen terpilih.'),(2,'Paket Pelatihan Berprasyarat','Pohon berakar di desa 1 menyatakan prasyarat: memilih desa selain akar mewajibkan seluruh leluhurnya. Pilih tepat K desa. Hitung banyak pilihan modulo 1000000007; himpunan kosong diperbolehkan. A_i adalah metadata yang diabaikan.','dp[u][j] banyak himpunan terhubung memuat u ukuran j. Konvolusi anak menggunakan perkalian banyak cara dan penjumlahan, serta satu cara untuk melewati anak. Jawaban khusus K=0 adalah 1.')]:
    cases=[treecase([5],[],1),treecase([5,3,8,2],[(1,2),(1,3),(2,4)],2),treecase([-10,9,8],[(1,2),(2,3)],2),treecase([0],[],0),treecase([1,2,3],[(1,2),(1,3)],3),treecase([0,0,0,0],[(1,2),(1,3),(1,4)],2),treecase([-5,-2,-9],[(1,2),(2,3)],1),treecase([10**9]*4,[(1,2),(2,3),(3,4)],4)]
    add(161,title,story,'N K; N nilai A_i; N−1 sisi u v. Keluaran satu bilangan atau IMPOSSIBLE sesuai aturan.','1 ≤ N ≤ 200; 0 ≤ K ≤ N; −10^9 ≤ A_i ≤ 10^9; input pohon.',knapbody.replace('MODEV',str(mode)),lambda s,m=mode:treeknap(s,m),lambda s,m=mode:treeknap(s,m,True),cases,lambda:treerand(True),idea+' Gabung ke array BARU dan batasi indeks oleh ukuran tabel yang telah dibangun serta K.','Komponen terhubung yang memuat u memotong setiap subtree anak menjadi himpunan kosong atau komponen terhubung yang memuat anak tersebut. Pembagian j=i+t unik, sehingga konvolusi mencakup semua dan hanya pilihan sah. Untuk akar bebas, tiap komponen mempunyai satu simpul dengan kedalaman minimum.','Batas sederhana O(NK²) waktu dan O(NK) memori; dengan batas ukuran subtree total merge lebih tajam O(NK). Batas N≤200 aman untuk kedua analisis.')
# 162 all-root answers: mass, maxima, and products without inverses.
def reroot(s,mode,brute=False):
    n,k,a,g,p,o=tree_parse(s)
    if brute:
        if mode==2:
            ans=[0]*n
            for mask in range(1,1<<n):
                st=[(mask&-mask).bit_length()-1];seen=set(st)
                for u in st:
                    for v in g[u]:
                        if mask>>v&1 and v not in seen:seen.add(v);st.append(v)
                if len(seen)==mask.bit_count():
                    ways=math.prod(a[u]for u in seen)%MOD
                    for u in seen:ans[u]=(ans[u]+ways)%MOD
            return nums(ans)
        ans=[]
        for u in range(n):
            dist=[-1]*n;dist[u]=0;q=[u]
            for v in q:
                for w in g[v]:
                    if dist[w]<0:dist[w]=dist[v]+1;q.append(w)
            ans.append(sum(dist[v]*a[v]for v in range(n))if mode==0 else max(dist[v]+a[v]for v in range(n)))
        return nums(ans)
    if mode==0:
        sub=a[:];down=[0]*n
        for u in reversed(o[1:]):sub[p[u]]+=sub[u];down[p[u]]+=down[u]+sub[u]
        ans=down[:]
        for u in o[1:]:ans[u]=ans[p[u]]+sub[0]-2*sub[u]
        return nums(ans)
    down=a[:];up=[-10**30 if mode==1 else 0]*n;ans=[0]*n
    for u in reversed(o):
        for v in g[u]:
            if p[v]!=u:continue
            if mode==1:down[u]=max(down[u],down[v]+1)
            else:down[u]=down[u]*(1+down[v])%MOD
    for u in o:
        ch=[v for v in g[u]if p[v]==u]
        if mode==1:
            tops=sorted([(a[u],-1),(up[u],-2)]+[(down[v]+1,v)for v in ch],reverse=True)
            ans[u]=tops[0][0]
            for v in ch:up[v]=(tops[1][0]if tops[0][1]==v else tops[0][0])+1
        else:
            pre=[a[u]*(1+up[u])%MOD]
            for v in ch:pre.append(pre[-1]*(1+down[v])%MOD)
            ans[u]=pre[-1];suf=1
            for i in range(len(ch)-1,-1,-1):v=ch[i];up[v]=pre[i]*suf%MOD;suf=suf*(1+down[v])%MOD
    return nums(ans)
rrbody=TREE+r'''const int MODE=MODEV;vector<ll>sub=a,d=a,up(n,MODE==1?-INF:0),ans(n);if(MODE==0){fill(d.begin(),d.end(),0);for(int i=n-1;i>0;i--){int u=ord[i];sub[p[u]]+=sub[u];d[p[u]]+=d[u]+sub[u];}ans[0]=d[0];for(int i=1;i<n;i++){int u=ord[i];ans[u]=ans[p[u]]+sub[0]-2*sub[u];}}else{for(int i=n-1;i>=0;i--){int u=ord[i];for(int v:g[u])if(p[v]==u){if(MODE==1)d[u]=max(d[u],d[v]+1);else d[u]=d[u]*((1+d[v])%MOD)%MOD;}}for(int u:ord){vector<int>ch;for(int v:g[u])if(p[v]==u)ch.push_back(v);if(MODE==1){pair<ll,int>b1={a[u],-1},b2={-INF,-3};auto offer=[&](ll x,int v){pair<ll,int>q={x,v};if(q>b1){b2=b1;b1=q;}else if(q>b2)b2=q;};offer(up[u],-2);for(int v:ch)offer(d[v]+1,v);ans[u]=b1.first;for(int v:ch)up[v]=(b1.second==v?b2.first:b1.first)+1;}else{vector<ll>pre(ch.size()+1);pre[0]=a[u]*((1+up[u])%MOD)%MOD;for(int i=0;i<(int)ch.size();i++)pre[i+1]=pre[i]*((1+d[ch[i]])%MOD)%MOD;ans[u]=pre.back();ll suf=1;for(int i=(int)ch.size()-1;i>=0;i--){int v=ch[i];up[v]=pre[i]*suf%MOD;suf=suf*((1+d[v])%MOD)%MOD;}}}}for(int u=0;u<n;u++)cout<<ans[u]<<(u+1==n?'\n':' ');'''
for mode,title,story,idea in [(0,'Gudang Bantuan untuk Semua Desa','Desa i mempunyai A_i keluarga. Setiap jalan membutuhkan satu satuan perjalanan. Untuk setiap kemungkinan lokasi gudang u, hitung jumlah A_v×jarak(u,v) atas seluruh desa v.','sub[u] adalah total keluarga di subtree, bukan banyak simpul. ans[v]=ans[u]+total−2sub[v]. Bergerak satu sisi mendekatkan keluarga di subtree v dan menjauhkan sisanya.'),(1,'Sirene dan Waktu Persiapan','Sirene dari desa u merambat satu jalan per menit pada pohon. Desa v baru siap A_v menit setelah sinyal tiba. Untuk setiap u, hitung waktu ketika semua desa telah siap: max_v(jarak(u,v)+A_v), termasuk v=u.','down[u]=max(A_u,1+down[v]). Pesan dari arah parent harus mengecualikan kontribusi anak tujuan. Simpan dua kandidat terbesar BESERTA asalnya agar ties tidak salah.'),(2,'Festival Desa Berwarna','Pilih himpunan desa tidak kosong yang terhubung. Desa i yang dipilih memiliki A_i pilihan dekorasi berbeda; bila A_i=0 desa itu tidak dapat dipilih. Untuk setiap desa u, hitung banyak konfigurasi yang memuat u, modulo 1000000007.','Pesan u→parent adalah A_uΠ_anak(1+pesan anak). Angka 1 berarti melewati cabang. Untuk pesan u→v, kalikan seluruh kontribusi selain v memakai prefix/suffix, sehingga tidak perlu invers modulo.')]:
    add(162,title,story,'N; N nilai A_i; N−1 sisi pohon u v. Keluaran N jawaban, urut u=1..N.','1 ≤ N ≤ 200000; 0 ≤ A_i ≤ 10^9; input pohon.',rrbody.replace('MODEV',str(mode)),lambda s,m=mode:reroot(s,m),lambda s,m=mode:reroot(s,m,True),treecases,lambda:treerand(),idea,'Memotong sisi u−v membagi pohon menjadi dua komponen. Pesan dari setiap arah merangkum tepat komponen pada arah itu. Tahap bawah menghitung pesan anak, tahap atas menghitung pesan parent dengan mengeluarkan cabang tujuan. Gabungan akhir mencakup setiap desa atau pilihan cabang sekali.','Waktu O(N), memori O(N). Dua traversal iteratif; two-largest dan prefix/suffix total linear terhadap derajat.')
# 163 probability with rational-independent oracle.
def prob(s,mode,brute=False):
    z=list(map(int,s.split()));n,k=z[:2];w=z[2:]
    if mode==0:
        if brute:
            ans=0.0
            for comb in itertools.combinations(range(n),k):
                st=set(comb);ans+=math.prod((w[i]/100 if i in st else 1-w[i]/100)for i in range(n))
        else:
            d=[1.0]+[0.0]*n
            for i,p in enumerate(w):
                for j in range(i+1,-1,-1):d[j]=d[j]*(1-p/100)+(d[j-1]*p/100 if j else 0)
            ans=d[k]if k<=n else 0
    elif mode==1:
        # Weighted dice 1..k, overshoot stays; exact Fraction oracle.
        if brute:
            from fractions import Fraction
            d=[Fraction(0)for _ in range(n+1)]
        else:d=[0.]*(n+1)
        for i in range(n-1,-1,-1):
            valid=min(k,n-i);tot=sum(w)
            val=tot+sum(w[j-1]*d[i+j] for j in range(1,valid+1))
            if brute:
                from fractions import Fraction
                d[i]=Fraction(val,sum(w[:valid]))
            else:d[i]=val/sum(w[:valid])
        ans=float(d[0])
    else:
        total=sum(w)
        if brute:
            # Inclusion-exclusion on missing sticker sets, independent of mask recurrence.
            ans=sum((1 if mask.bit_count()%2 else -1)*total/sum(w[i]for i in range(n)if mask>>i&1) for mask in range(1,1<<n))
        else:
            d=[0.]*(1<<n)
            for mask in range((1<<n)-2,-1,-1):
                miss=[i for i in range(n)if not(mask>>i&1)]
                d[mask]=(total+sum(w[i]*d[mask|1<<i]for i in miss))/sum(w[i]for i in miss)
            ans=d[0]
    return f'{ans:.10f}\n'
probbody=r'''int n,k;cin>>n>>k;const int MODE=MODEV;vector<ll>w(MODE==1?k:n);ll total=0;for(ll&x:w){cin>>x;total+=x;}long double ans;if(MODE==0){vector<long double>d(n+1);d[0]=1;for(int i=0;i<n;i++)for(int j=i+1;j>=0;j--)d[j]=d[j]*(1-w[i]/100.L)+(j?d[j-1]*w[i]/100.L:0);ans=k<=n?d[k]:0;}else if(MODE==1){vector<long double>d(n+1);for(int i=n-1;i>=0;i--){long double t=total;ll valid=0;for(int j=1;j<=k&&i+j<=n;j++){t+=w[j-1]*d[i+j];valid+=w[j-1];}d[i]=t/valid;}ans=d[0];}else{int z=1<<n;vector<long double>d(z);for(int mask=z-2;mask>=0;mask--){ll miss=0;long double t=total;for(int i=0;i<n;i++)if(!(mask>>i&1)){miss+=w[i];t+=w[i]*d[mask|(1<<i)];}d[mask]=t/miss;}ans=d[0];}cout<<fixed<<setprecision(10)<<ans<<'\n';'''
for mode,title,story,co,idea in [(0,'Tepat K Lampion Menyala','Lampion i berhasil menyala dengan probabilitas P_i persen, saling independen. Hitung probabilitas tepat K dari N lampion menyala.','1 ≤ N ≤ 1000; 0 ≤ K ≤ N; 0 ≤ P_i ≤ 100.','d[j] peluang j sukses pada prefiks. d′[j]=d[j](1−p)+d[j−1]p. Loop j menurun memungkinkan in-place.'),(1,'Dadu di Ujung Jembatan','Pion mulai pada petak 0 menuju tepat petak N. Dadu memiliki hasil 1..K dengan peluang hasil j proporsional bobot W_j positif. Tiap lemparan dihitung, termasuk yang melewati N; jika melewati, pion tetap di tempat. Hitung harapan jumlah lemparan sampai tiba.','1 ≤ N ≤ 10000; 1 ≤ K ≤ 20; 1 ≤ W_j ≤ 100.','E[N]=0. Dari i, E[i]=1+(Σ_valid w_jE[i+j]+Σ_invalid w_jE[i])/W. Jadi E[i]=(W+Σ_valid w_jE[i+j])/Σ_valid w_j. Jangan mengganti W dengan jumlah bobot valid.'),(2,'Album Stiker Pasar Malam','Setiap pembelian memberi satu dari N jenis stiker, independen, dengan peluang jenis i sebesar W_i/ΣW. Awalnya belum punya stiker. Hitung harapan jumlah pembelian sampai semua jenis terkumpul. Parameter K=0 adalah kode album dan tidak memengaruhi peluang.','1 ≤ N ≤ 15; K=0; 1 ≤ W_i ≤ 100.','E[mask] sisa pembelian. Pembelian jenis yang sudah dimiliki menghasilkan self-loop. Setelah memindahkan self-loop, E[mask]=(W+Σ_i_belum w_iE[mask∪i])/Σ_i_belum w_i. E[full]=0.')]:
    if mode==0:cases=['1 0\n0\n','3 2\n50 50 50\n','2 1\n100 0\n','1 1\n0\n','2 0\n100 100\n','4 4\n100 100 100 100\n','3 1\n1 99 50\n','5 2\n20 40 60 80 100\n']
    elif mode==1:cases=['1 6\n1 1 1 1 1 1\n','5 6\n1 1 1 1 1 1\n','4 2\n1 3\n','1 1\n100\n','8 1\n1\n','2 3\n1 1 100\n','3 2\n100 1\n','10 4\n1 2 3 4\n']
    else:cases=['1 0\n7\n','2 0\n1 1\n','3 0\n1 2 3\n','2 0\n1 100\n','4 0\n1 1 1 1\n','3 0\n100 100 100\n','5 0\n1 2 4 8 16\n','2 0\n100 1\n']
    def rand(m=mode):
        n=R.randint(1,9);k=R.randint(0,n)if m==0 else(R.randint(1,6)if m==1 else 0)
        return nums([n,k])+nums([R.randint(0 if m==0 else 1,100)for _ in range(k if m==1 else n)])
    add(163,title,story,'N K; lalu '+('K bobot W_j.' if mode==1 else ('N probabilitas persen P_i.'if mode==0 else'N bobot W_i.'))+' Keluaran satu bilangan real; galat absolut atau relatif ≤10^−6 diterima.',co,probbody.replace('MODEV',str(mode)),lambda s,m=mode:prob(s,m),lambda s,m=mode:prob(s,m,True),cases,rand,idea,'Gunakan hukum probabilitas total atas hasil percobaan pertama/terakhir. Cabang hasil saling lepas dan jumlah peluangnya satu. Untuk harapan, seluruh state selain self-loop lebih dekat ke terminal, sehingga setelah koefisien self-loop dipindahkan, induksi urutan evaluasi berlaku. Bobot positif menjamin penyebut tidak nol dan penyerapan hampir pasti.','Lampion O(N²) waktu/O(N) memori; jembatan O(NK)/O(N); album O(N2^N)/O(2^N).')
    SPECS[163][-1]['float']=True
# 164 machine-word parallel Boolean states.
def bitdp(s,mode,brute=False):
    z=list(map(int,s.split()));n,k=z[:2];a=z[2:2+n];q=z[2+n:]
    if brute:
        sums={sum(a[i]for i in range(n)if mask>>i&1)for mask in range(1<<n)if mode!=2 or mask.bit_count()==k}
    elif mode==2:
        d=[1]+[0]*k
        for x in a:
            for j in range(k,0,-1):d[j]|=d[j-1]<<x
        bits=d[k];sums={i for i in range(sum(a)+1)if bits>>i&1}
    else:
        bits=1
        for x in a:bits|=bits<<x
        sums={i for i in range(sum(a)+1)if bits>>i&1}
    if mode==0:return '\n'.join('YA'if x in sums else'TIDAK'for x in q)+'\n'
    if mode==1:return str(min(abs(sum(a)-2*x)for x in sums))+'\n'
    return str(len(sums))+'\n'
bitbody=r'''int n,k;cin>>n>>k;vector<int>a(n);int total=0;for(int&x:a){cin>>x;total+=x;}const int MODE=MODEV;const int S=200001;if(MODE==2){vector<bitset<S>>d(k+1);d[0][0]=1;for(int x:a)for(int j=k;j>=1;j--)d[j]|=d[j-1]<<x;cout<<d[k].count()<<'\n';}else{bitset<S>d;d[0]=1;for(int x:a)d|=d<<x;if(MODE==0){while(k--){int x;cin>>x;cout<<(x<S&&d[x]?"YA":"TIDAK")<<'\n';}}else{int ans=total;for(int i=0;i<=total;i++)if(d[i])ans=min(ans,abs(total-2*i));cout<<ans<<'\n';}}'''
for mode,title,story,idea in [(0,'Timbang Oleh-Oleh','N paket memiliki berat A_i. Untuk setiap target, tentukan apakah ada subset paket dengan berat tepat target. Paket hanya boleh dipakai sekali, dan subset kosong diperbolehkan.','Bit ke-s menyatakan apakah jumlah s bisa dibuat. Awal hanya bit 0. Untuk paket x, dp |= dp<<x memperbarui semua kemungkinan sekaligus.'),(1,'Dua Perahu Seimbang','Bagikan seluruh paket ke dua perahu; salah satu perahu boleh kosong. Minimalkan selisih total berat. K=0 dibaca sebagai penanda dua perahu.','Setelah subset sum dengan bitset, setiap jumlah s terjangkau memberi pembagian (s,total−s). Minimalkan |total−2s|.'),(2,'Ragam Berat Parcel','Pilih tepat K dari N paket berlabel. Hitung banyak NILAI TOTAL BERAT berbeda yang dapat terbentuk, bukan banyak subset. K=0 menghasilkan satu berat, yaitu 0.','Gunakan dp[j] bitset jumlah dari tepat j paket. Update j menurun: dp[j] |= dp[j−1]<<x. Jawaban popcount seluruh dp[K].')]:
    base=[([1,3,4],2),([0],0),([2,2,2],2),([63,64,65],2),([200000],1),([0,0,0],2),([5,10],2),([1,2,3,4],3)]
    cases=[]
    for a,k in base:
        q=[0,1,sum(a),sum(a)+1]
        cases.append(nums([len(a),len(q)if mode==0 else(k if mode==2 else0)])+nums(a)+(nums(q)if mode==0 else''))
    def rand(m=mode):
        n=R.randint(1,12);a=[R.randint(0,30)for _ in range(n)];k=R.randint(0,n);q=[R.randint(0,sum(a)+5)for _ in range(5)]
        return nums([n,5 if m==0 else(k if m==2 else0)])+nums(a)+(nums(q)if m==0 else'')
    add(164,title,story,'N '+('Q'if mode==0 else'K')+'; N berat A_i.'+(' Lalu Q target T (boleh satu baris).'if mode==0 else'')+' Keluaran '+('YA/TIDAK untuk tiap query, satu per baris.'if mode==0 else'satu bilangan bulat.'),'1 ≤ N ≤ 1000; 0 ≤ A_i; ΣA_i ≤ 200000; '+('1 ≤ Q ≤ 100000; 0 ≤ T ≤ 10^9.'if mode==0 else('K=0.'if mode==1 else'0 ≤ K ≤ min(N,30).')),bitbody.replace('MODEV',str(mode)),lambda s,m=mode:bitdp(s,m),lambda s,m=mode:bitdp(s,m,True),cases,rand,idea,'Induksi paket: subset sah terbagi menjadi yang melewati x (bit lama) dan yang mengambil x (bit lama digeser). OR menyatakan keberadaan, bukan penjumlahan banyak cara. Pada kardinalitas, loop menurun memastikan satu paket tidak dipakai dua kali.','Misalkan S=200001 dan w ukuran word mesin. Subset/partisi O(NS/w+S+Q), memori O(S/w); tepat K O(NKS/w), memori O(KS/w).')
# 165 games: scalar, DAG, independent disjoint sums.
def games(s,mode,brute=False):
    z=list(map(int,s.split()))
    if mode==1:
        n,m,start=z[:3];g=[[]for _ in range(n)]
        for u,v in zip(z[3::2],z[4::2]):g[u-1].append(v-1)
        @functools.lru_cache(None)
        def win(u):return any(not win(v)for v in g[u])
        d=[False]*n
        for u in range(n-1,-1,-1):d[u]=any(not d[v]for v in g[u])
        cand=[v+1 for v in g[start-1]if not(win(v)if brute else d[v])]
        return str(min(cand,default=0))+'\n'
    n,k=z[:2];moves=z[2:2+k];heaps=z[2+k:]if mode==2 else[n]
    if mode==0:
        @functools.lru_cache(None)
        def win(x):return any(not win(x-a)for a in moves if a<=x)
        d=[False]*(n+1)
        for x in range(n+1):d[x]=any(not d[x-a]for a in moves if a<=x)
        return str(min((a for a in moves if a<=n and not(win(n-a)if brute else d[n-a])),default=0))+'\n'
    if brute:
        @functools.lru_cache(None)
        def win(h):return any(not win(h[:i]+(x-a,)+h[i+1:])for i,x in enumerate(h)for a in moves if a<=x)
        ans=win(tuple(heaps))
    else:
        d=[0]*(max(heaps)+1)
        for x in range(1,len(d)):
            seen={d[x-a]for a in moves if a<=x};t=0
            while t in seen:t+=1
            d[x]=t
        ans=bool(functools.reduce(lambda a,b:a^b,(d[x]for x in heaps),0))
    return ('PERTAMA'if ans else'KEDUA')+'\n'
gamebody=r'''const int MODE=MODEV;if(MODE==1){int n,m,s;cin>>n>>m>>s;--s;vector<vector<int>>g(n);while(m--){int u,v;cin>>u>>v;g[u-1].push_back(v-1);}vector<bool>d(n);for(int u=n-1;u>=0;u--)for(int v:g[u])if(!d[v])d[u]=true;int ans=n+1;for(int v:g[s])if(!d[v])ans=min(ans,v+1);cout<<(ans==n+1?0:ans)<<'\n';}else{int n,k;cin>>n>>k;vector<int>a(k);for(int&x:a)cin>>x;if(MODE==0){vector<bool>d(n+1);for(int x=1;x<=n;x++)for(int v:a)if(v<=x&&!d[x-v])d[x]=true;int ans=1000000000;for(int v:a)if(v<=n&&!d[n-v])ans=min(ans,v);cout<<(ans==1000000000?0:ans)<<'\n';}else{vector<int>h(n);int mx=0;for(int&x:h){cin>>x;mx=max(mx,x);}vector<int>d(mx+1);for(int x=1;x<=mx;x++){vector<bool>seen(k+1);for(int v:a)if(v<=x&&d[x-v]<=k)seen[d[x-v]]=true;while(d[x]<=k&&seen[d[x]])d[x]++;}int z=0;for(int x:h)z^=d[x];cout<<(z?"PERTAMA":"KEDUA")<<'\n';}}'''
for mode,title,story,co,idea in [(0,'Congklak Satu Lubang','Ada N biji. Dua pemain bergantian mengambil sebanyak salah satu nilai di himpunan langkah. Pemain tanpa langkah kalah. Keduanya optimal. Cetak jumlah biji terkecil yang dapat diambil sebagai langkah pertama yang menjamin kemenangan, atau 0 bila pemain pertama kalah.','0 ≤ N ≤ 100000; 1 ≤ K ≤ 30; langkah berbeda, 1..100000.','win[0]=false, win[x]=ada a≤x dengan !win[x−a]. Pilih langkah menang terkecil agar output deterministik.'),(1,'Pion di Lorong Museum','Pion mulai di ruangan S pada graf berarah. Setiap jalan u→v dijamin u<v. Pemain bergantian memindahkan pion; yang tidak bisa bergerak kalah. Cetak nomor ruangan tujuan terkecil untuk langkah menang, atau 0 bila tidak ada.','1 ≤ N ≤ 200000; 0 ≤ M ≤ 300000; 1 ≤ S ≤ N; 1 ≤ u < v ≤ N; tidak ada sisi ganda.','Karena u<v, urutan N..1 adalah urutan DP mundur. win[u]=ada tetangga v dengan win[v]=false.'),(2,'Festival Banyak Congklak','Ada N lubang dengan H_i biji. Dalam satu giliran, pilih tepat satu lubang lalu ambil biji sebanyak salah satu dari K langkah yang diizinkan. Pemain tanpa langkah kalah. Tentukan pemenang optimal, PERTAMA atau KEDUA.','1 ≤ N ≤ 100000; 1 ≤ K ≤ 30; 0 ≤ H_i ≤ 100000; langkah berbeda, 1..100000.','Hitung Grundy g[x]=mex{g[x−a]}. Jawaban menang bila XOR semua g[H_i] bukan nol. Meng-XOR boolean win tidak cukup.')]:
    if mode==0:cases=['0 2\n1 3\n','7 2\n1 3\n','8 3\n1 3 4\n','1 1\n2\n','2 1\n2\n','6 2\n3 1\n','15 3\n2 5 7\n','4 1\n1\n']
    elif mode==1:cases=['1 0 1\n','4 4 1\n1 2\n1 3\n2 4\n3 4\n','4 2 1\n1 3\n1 2\n','2 1 2\n1 2\n','3 2 1\n1 2\n2 3\n','4 3 1\n1 2\n1 4\n2 3\n','5 0 3\n','5 4 2\n1 2\n2 3\n2 4\n4 5\n']
    else:cases=['1 2\n1 3\n0\n','2 2\n1 3\n1 1\n','3 2\n1 3\n1 2 3\n','2 1\n2\n1 3\n','3 3\n1 2 3\n2 2 2\n','2 2\n2 3\n4 5\n','4 1\n1\n0 0 0 0\n','1 2\n4 7\n3\n']
    def rand(m=mode):
        if m==1:
            n=R.randint(1,9);es=[(i,j)for i in range(1,n+1)for j in range(i+1,n+1)if R.random()<.3];return nums([n,len(es),R.randint(1,n)])+mat(es)
        k=R.randint(1,4);a=R.sample(range(1,8),k);n=R.randint(0,20)if m==0 else R.randint(1,3)
        return nums([n,k])+nums(a)+(nums([R.randint(0,6)for _ in range(n)])if m==2 else'')
    add(165,title,story,('N M S, lalu M sisi u v.'if mode==1 else'N K, lalu K langkah.'+(' Lalu N nilai H_i.'if mode==2 else''))+' Keluaran sesuai tugas.',co,gamebody.replace('MODEV',str(mode)),lambda s,m=mode:games(s,m),lambda s,m=mode:games(s,m,True),cases,rand,idea,'Terminal kalah. Pada DAG, satu langkah ke posisi kalah cukup untuk memaksa lawan kalah, sedangkan jika semua langkah menuju posisi menang, lawan selalu punya strategi menang. Untuk gabungan permainan impartial normal-play, mex memberi nilai Grundy dan teorema Sprague–Grundy memberi XOR; setiap langkah mengubah satu komponen saja.','Satu lubang O(NK)/O(N); graf O(N+M)/O(N+M); banyak lubang O(max(H)K+N)/O(max(H)+N).')
# 166 cell-by-cell frontier with independent exact-cover brute force.
def profile(s,mode,brute=False):
    lines=s.splitlines();r,c,k=map(int,lines[0].split());board=''.join(lines[1:1+r]);h,v=map(int,lines[1+r].split())if mode==2 else(0,0);n=r*c
    if brute:
        used={i for i,x in enumerate(board)if x=='#'}
        def go(used,mon):
            if len(used)==n:return (1 if mon==k else 0)if mode!=2 else 0
            i=next(i for i in range(n)if i not in used);res=[]
            if mode==1 and mon<k:res.append(go(used|{i},mon+1))
            for j,cost in ((i+1,h),(i+c,v)):
                if j>=n or j in used or(j==i+1 and i%c==c-1):continue
                x=go(used|{i,j},mon)
                res.append(x+cost if mode==2 and x<10**30 else x)
            return min(res,default=10**30)if mode==2 else sum(res)%MOD
        ans=go(used,0);return str(ans if ans<10**30 else-1)+'\n'
    d={(0,0):0 if mode==2 else1}
    for i,x in enumerate(board):
        nd={}
        def push(mask,j,value):
            key=mask,j
            if mode==2:nd[key]=min(nd.get(key,10**30),value)
            else:nd[key]=(nd.get(key,0)+value)%MOD
        for (mask,j),value in d.items():
            if x=='#':
                if not(mask&1):push(mask>>1,j,value)
            elif mask&1:push(mask>>1,j,value)
            else:
                if mode==1 and j<k:push(mask>>1,j+1,value)
                if i%c+1<c and board[i+1]!='#'and not(mask&2):push((mask>>1)|1,j,value+(h if mode==2 else0))
                if i+c<n and board[i+c]!='#':push((mask>>1)|(1<<(c-1)),j,value+(v if mode==2 else0))
        d=nd
    ans=d.get((0,k),10**30 if mode==2 else0)
    return str(ans if ans<10**30 else-1)+'\n'
profilebody=r'''int r,c,k;cin>>r>>c>>k;string b,t;for(int i=0;i<r;i++){cin>>t;b+=t;}const int MODE=MODEV;ll h=0,v=0;if(MODE==2)cin>>h>>v;int z=1<<c;vector<vector<ll>>d(z,vector<ll>(k+1,MODE==2?INF:0));d[0][0]=MODE==2?0:1;for(int i=0;i<r*c;i++){vector<vector<ll>>e(z,vector<ll>(k+1,MODE==2?INF:0));auto push=[&](int m,int j,ll x){if(MODE==2)e[m][j]=min(e[m][j],x);else e[m][j]=(e[m][j]+x)%MOD;};for(int m=0;m<z;m++)for(int j=0;j<=k;j++){ll val=d[m][j];if(MODE==2?val==INF:val==0)continue;if(b[i]=='#'){if(!(m&1))push(m>>1,j,val);}else if(m&1)push(m>>1,j,val);else{if(MODE==1&&j<k)push(m>>1,j+1,val);if(i%c+1<c&&b[i+1]!='#'&&!(m&2))push((m>>1)|1,j,val+(MODE==2?h:0));if(i+c<r*c&&b[i+c]!='#')push((m>>1)|(1<<(c-1)),j,val+(MODE==2?v:0));}}d.swap(e);}ll ans=d[0][k];cout<<(ans==INF?-1:ans)<<'\n';'''
for mode,title,story,idea in [(0,'Ubin Pendopo Berlubang','Tutup semua petak titik pada papan dengan domino 1×2 yang boleh diputar. Petak # adalah tiang dan tidak boleh ditutup. Domino tidak boleh tumpang tindih atau keluar papan. Hitung banyak tiling modulo 1000000007. Papan tanpa petak kosong memiliki satu tiling kosong. K=0.','Profil mask menyimpan keterisian C posisi mulai dari sel sekarang. Jika bit0 sudah terisi, geser; jika kosong, pasang domino horizontal/vertikal yang sah. Di akhir wajib mask=0.'),(1,'Mosaik dengan Ubin Tunggal','Tutup seluruh petak titik dengan domino 1×2 dan TEPAT K ubin 1×1. Tiang # tidak boleh ditutup. Hitung banyak tiling modulo 1000000007. Ubin sejenis tidak berlabel.','Tambah penghitung monomer j. Selain domino, sel kosong dapat memakai satu ubin tunggal bila j<K. Jangan hanya menghitung sisa area: posisi monomer mengubah jumlah tiling.'),(2,'Biaya Renovasi Pendopo','Tutup seluruh petak titik dengan domino; petak # tidak boleh ditutup. Setiap domino horizontal berbiaya H dan vertikal berbiaya V. Tentukan biaya minimum atau −1 jika mustahil. K=0.','Profil sama, tetapi gabungkan dengan minimum biaya. Horizontal menambah H, vertikal menambah V; state mustahil diberi +∞. Papan penuh tiang berbiaya 0.')]:
    base=[(1,1,['#'],0),(2,2,['..','..'],0),(2,3,['.#.','...'],1),(1,1,['.'],1),(1,4,['....'],0),(3,3,['...','.#.','...'],2),(2,3,['###','###'],0),(3,2,['..','##','..'],2)]
    cases=[nums([r,c,k if mode==1 else0])+'\n'.join(b)+'\n'+('9 2\n'if mode==2 else'')for r,c,b,k in base]
    def rand(m=mode):
        r=R.randint(1,4);c=R.randint(1,4);k=R.randint(0,3)if m==1 else0
        return nums([r,c,k])+'\n'.join(''.join('#'if R.random()<.25 else'.'for _ in range(c))for _ in range(r))+'\n'+(nums([R.randint(0,10),R.randint(0,10)])if m==2 else'')
    add(166,title,story,'R C K; R baris papan panjang C;'+(' lalu H V.'if mode==2 else'')+' Keluaran satu bilangan.','1 ≤ R ≤ 100; 1 ≤ C ≤ 8; '+('0 ≤ K ≤ 6.'if mode==1 else'K=0.')+(' 0 ≤ H,V ≤ 10^9.'if mode==2 else''),profilebody.replace('MODEV',str(mode)),lambda s,m=mode:profile(s,m),lambda s,m=mode:profile(s,m,True),cases,rand,idea,'Ambil sel kosong pertama yang belum diproses. Dalam setiap tiling akhir, sel itu ditutup tepat satu potongan yang dicoba transisi. Menghapus potongan tersebut memberikan satu state lanjutan unik. Riwayat jauh di belakang tidak lagi berinteraksi; seluruh potongan yang melintasi batas dicatat oleh profil. Induksi posisi membuktikan hasil.','Waktu O(RC2^C(K+1)), memori O(2^C(K+1)); untuk domino saja K=0. Jika memutar papan berbobot, biaya horizontal dan vertikal harus ikut ditukar.')
# 167 integrated set, not relabelled repeats.
def exactcoins(s,brute=False):
    z=list(map(int,s.split()));n,target,k=z[:3];a=z[3:]
    if brute:
        def go(i,left,total):
            if i==n:return int(left==0 and total==0)
            return sum(go(i+1,left-j,total-j*a[i])for j in range(min(left,total//a[i])+1))
        ans=go(0,k,target)
    else:
        d=[[0]*(target+1)for _ in range(k+1)];d[0][0]=1
        for x in a:
            for j in range(1,k+1):
                for t in range(x,target+1):d[j][t]=(d[j][t]+d[j-1][t-x])%MOD
        ans=d[k][target]
    return str(ans%MOD)+'\n'
add(167,'Tiket Pecahan Tepat','Loket menerima N jenis token bernilai A_i yang berbeda, masing-masing tersedia tanpa batas. Bayar tepat S memakai tepat K token. Hitung banyak vektor jumlah token tiap jenis modulo 1000000007; urutan penyerahan token tidak membedakan cara.','N S K; N nilai A_i. Keluaran banyak cara.','1 ≤ N ≤ 30; 0 ≤ S ≤ 2000; 0 ≤ K ≤ 30; nilai A_i berbeda dan 1..2000.',r'''int n,s,k;cin>>n>>s>>k;vector<int>a(n);for(int&x:a)cin>>x;vector<vector<ll>>d(k+1,vector<ll>(s+1));d[0][0]=1;for(int x:a)for(int j=1;j<=k;j++)for(int t=x;t<=s;t++)d[j][t]=(d[j][t]+d[j-1][t-x])%MOD;cout<<d[k][s]<<'\n';''',exactcoins,lambda s:exactcoins(s,True),['2 6 3\n1 2\n','3 6 3\n1 2 3\n','2 0 0\n3 5\n','1 4 3\n2\n','1 6 3\n2\n','2 1 0\n1 2\n','2 6 2\n3 4\n','3 9 3\n1 3 5\n'],lambda: nums([(n:=R.randint(1,5)),R.randint(0,25),R.randint(0,6)])+nums(R.sample(range(1,11),n)),'State dp[j][s] setelah beberapa jenis token, tepat j token dengan total s. Loop jenis di luar menghindari penghitungan permutasi. Loop j menaik mengizinkan jenis yang sama dipakai kembali.','Untuk satu jenis x, solusi terbagi menurut jumlah token x yang dipakai. Rekurensi d_new[j][s]=d_old[j][s]+d_new[j−1][s−x] menggabungkan nol token x atau minimal satu token x. Bagian kedua menghapus satu token x secara unik.','O(NSK) waktu, O(SK) memori.')
def wl(s,brute=False):
    z=list(map(int,s.split()));n=z[0];a=z[1:1+n];w=z[1+n:]
    if brute:
        ans=0
        for mask in range(1<<n):
            idx=[i for i in range(n)if mask>>i&1]
            if all(a[i]<a[j]for i,j in zip(idx,idx[1:])):ans=max(ans,sum(w[i]for i in idx))
    else:
        keys=sorted(set(a));bit=[0]*(len(keys)+1);ans=0
        for h,v in zip(a,w):
            import bisect
            rank=bisect.bisect_left(keys,h)+1;x=rank-1;best=0
            while x:best=max(best,bit[x]);x-=x&-x
            val=best+v;ans=max(ans,val);x=rank
            while x<len(bit):bit[x]=max(bit[x],val);x+=x&-x
    return str(ans)+'\n'
add(167,'Kirab Menara Berhadiah','Terdapat N menara dalam urutan kunjungan. Pilih subsekuens menara sehingga tinggi meningkat KETAT. Menara i memberikan hadiah W_i, yang boleh negatif. Maksimalkan total hadiah; subsekuens kosong diperbolehkan.','N; N tinggi H_i; N hadiah W_i. Keluaran hadiah maksimum.','1 ≤ N ≤ 200000; 1 ≤ H_i ≤ 10^9; −10^9 ≤ W_i ≤ 10^9.',r'''int n;cin>>n;vector<ll>h(n),w(n),key;for(ll&x:h)cin>>x;for(ll&x:w)cin>>x;key=h;sort(key.begin(),key.end());key.erase(unique(key.begin(),key.end()),key.end());vector<ll>bit(key.size()+1);ll ans=0;for(int i=0;i<n;i++){int r=lower_bound(key.begin(),key.end(),h[i])-key.begin()+1;ll val=0;for(int x=r-1;x;x-=x&-x)val=max(val,bit[x]);val+=w[i];ans=max(ans,val);for(int x=r;x<(int)bit.size();x+=x&-x)bit[x]=max(bit[x],val);}cout<<ans<<'\n';''',wl,lambda s:wl(s,True),['1\n5\n-7\n','4\n2 1 3 4\n10 4 6 5\n','3\n2 2 2\n4 8 5\n','3\n3 2 1\n1 2 3\n','3\n1 2 3\n-1 -2 -3\n','3\n1 2 3\n1000000000 1000000000 1000000000\n','4\n1 100 2 3\n5 100 50 50\n','3\n9 1 9\n7 3 8\n'],lambda:nums([(n:=R.randint(1,12))])+nums([R.randint(1,8)for _ in range(n)])+nums([R.randint(-10,20)for _ in range(n)]),'dp[i]=W_i+max(0,max dp[j] untuk j<i,H_j<H_i). Kompres tinggi; Fenwick tree menyimpan maksimum prefiks. Query rank−1, bukan rank, untuk meningkat ketat.','Setiap subsekuens tidak kosong punya elemen terakhir i dan, bila ada, pendahulu j dengan tinggi lebih kecil. Fenwick sebelum memproses i hanya memuat j<i, sehingga query tepat mencakup semua pendahulu sah. Opsi 0 mengawali subsekuens baru.','O(N log N) waktu, O(N) memori. Fenwick maksimum hanya mendukung update yang menaikkan nilai.')
def paritytree(s,brute=False):
    n,k,a,g,p,o=tree_parse(s)
    if brute:
        ans=0
        for mask in range(1,1<<n):
            st=[(mask&-mask).bit_length()-1];seen=set(st)
            for u in st:
                for v in g[u]:
                    if mask>>v&1 and v not in seen:seen.add(v);st.append(v)
            if len(seen)==mask.bit_count() and sum(a[u]for u in seen)%2==0:ans+=1
        return str(ans%MOD)+'\n'
    d=[[0,0]for _ in range(n)];ans=0
    for u in reversed(o):
        d[u][a[u]%2]=1
        for v in g[u]:
            if p[v]!=u:continue
            e=d[u][:]
            for i in range(2):
                for j in range(2):e[i^j]=(e[i^j]+d[u][i]*d[v][j])%MOD
            d[u]=e
        ans=(ans+d[u][0])%MOD
    return str(ans)+'\n'
add(167,'Rombongan dengan Lampion Genap','Setiap desa pada pohon memiliki A_i lampion. Pilih himpunan desa tidak kosong yang terhubung dan memiliki jumlah lampion genap. Hitung banyak himpunan modulo 1000000007.','N; N nilai A_i; N−1 sisi pohon. Keluaran banyak himpunan.','1 ≤ N ≤ 200000; 0 ≤ A_i ≤ 10^9; input pohon.',TREE+r'''vector<vector<ll>>d(n,vector<ll>(2));ll ans=0;for(int z=n-1;z>=0;z--){int u=ord[z];d[u][a[u]%2]=1;for(int v:g[u])if(p[v]==u){vector<ll>e=d[u];for(int i=0;i<2;i++)for(int j=0;j<2;j++)e[i^j]=(e[i^j]+d[u][i]*d[v][j])%MOD;d[u].swap(e);}ans=(ans+d[u][0])%MOD;}cout<<ans<<'\n';''',paritytree,lambda s:paritytree(s,True),treecases,lambda:treerand(),'dp[u][p] banyak komponen terhubung di subtree u yang memuat u dan berparitas p. Untuk anak, lewati atau gabung; paritas bergabung dengan XOR. Jumlahkan dp[u][0] atas semua u.','Sebuah komponen tidak kosong punya satu simpul tertinggi u. Memotong di u menghasilkan komponen anak yang independen dan wajib memuat akar anak jika tidak kosong. Maka konvolusi paritas menghitungnya tepat sekali, dan penjumlahan semua u tidak menggandakan.','O(N) waktu dan O(N) memori.')
