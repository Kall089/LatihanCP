"""Reproducible source for eight DP training days. Run with bundled Python 3."""
from pathlib import Path
from functools import lru_cache
from itertools import product, combinations
import random
MOD=1_000_000_007
R=random.Random(20260905)
DAYS=[]
HEAD='''#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <array>
#include <functional>
#include <limits>
#include <cstdlib>
#include <numeric>
using namespace std;
'''
def cpp(body): return HEAD+'\nint main() {\n    ios::sync_with_stdio(false); cin.tie(nullptr);\n'+body.strip()+'\n}\n'
def lines(*xs): return '\n'.join(' '.join(map(str,x)) if isinstance(x,(list,tuple)) else str(x) for x in xs)+'\n'
def exercise(title,level,statement,inp,out,cons,hint,body,editorial,inputs,oracle):
    cases=[(s,str(oracle(s)).rstrip()+'\n') for s in inputs]
    assert len(cases)>=8
    return dict(title=title,level=level,statement=statement,input=inp,output=out,constraints=cons,hint=hint,solution=cpp(body),editorial=editorial,cases=cases,oracle=oracle)
def task(title,statement,inp,out,cons,samples):
    return dict(title=title,statement=statement,input=inp,output=out,constraints=cons,samples=samples)
def day(num,title,source,theory,exercises,tasks):
    DAYS.append(dict(number=num,title=title,source=source,theory=theory,exercises=exercises,tasks=tasks))

# Day 66: reference oracles deliberately use iterative evaluation rather than memoized C++.
def stairs(s):
    n,b=map(int,s.splitlines()[0].split()); blocked=set(map(int,s.splitlines()[1].split())) if b else set()
    d=[0]*(n+1);d[0]=1
    for i in range(1,n+1):
        if i not in blocked:d[i]=sum(d[i-j] for j in (1,3) if i>=j)%MOD
    return d[n]
def frog(s):
    t=list(map(int,s.split()));n=t[0];a=t[1:];d=[0]+[10**30]*(n-1)
    for i in range(1,n):d[i]=min(d[j]+abs(a[i]-a[j]) for j in range(max(0,i-2),i))
    return d[-1]
def gridways(s):
    ls=s.splitlines();n,m=map(int,ls[0].split());g=ls[1:];d=[[0]*m for _ in range(n)]
    for i in range(n):
        for j in range(m):
            if g[i][j]!='#':d[i][j]=((d[i-1][j] if i else 0)+(d[i][j-1] if j else 0)+(i==j==0))%MOD
    return d[-1][-1]
e66=[exercise('Lampion di Tangga Kampung','Mudah',
 'Warga memasang lampion di anak tangga 0 sampai N. Kamu mulai di 0 dan boleh naik tepat 1 atau 3 anak tangga. Beberapa anak tangga rapuh tidak boleh diinjak, tetapi boleh dilompati. Hitung banyak urutan lompatan yang berakhir tepat di N. Untuk N=0, diam di tempat dihitung satu cara.',
 'Baris pertama N B. Baris kedua berisi B indeks tangga rapuh; baris ini kosong bila B=0.',
 'Satu bilangan: banyak urutan modulo 1 000 000 007.', '0 <= N <= 400; 0 <= B <= N; indeks rapuh berbeda, 1..N.',
 'F(i) menghitung cara mencapai i; jawaban nol tetap perlu ditandai sudah dihitung.',
 '''int n,b;cin>>n>>b;vector<char> blocked(n+1),seen(n+1);vector<long long> memo(n+1);
for(int i=0,x;i<b;i++){cin>>x;blocked[x]=1;}
function<long long(int)> f=[&](int i)->long long{
 if(i<0)return 0; if(i==0)return 1; if(blocked[i])return 0;
 if(seen[i])return memo[i]; seen[i]=1;
 return memo[i]=(f(i-1)+f(i-3))%1000000007LL;
};cout<<f(n)<<'\\n';''',
 'State F(i) adalah banyak urutan yang mencapai i. Basis F(0)=1, F(i<0)=0, dan F(i)=0 untuk tangga rapuh. Selain itu F(i)=F(i-1)+F(i-3). Setiap urutan memiliki tepat satu langkah terakhir (1 atau 3), sehingga kedua kelompok terpisah dan mencakup semua jawaban. Induksi atas i membuktikan recurrence. Memoisasi menghitung setiap i sekali: O(N+B) waktu, O(N) tabel dan stack. N dibatasi 400 untuk latihan rekursi; jangan menyalin rekursi panjang tanpa menilai stack.',
 [lines(4,[]) if False else lines([4,0],[]),lines([3,1],[1]),lines([0,0],[]),lines([1,1],[1]),lines([6,2],[2,5]),lines([8,1],[8]),lines([15,0],[]),lines([400,0],[])]+[lines([n,len(b)],b) for n,b in [(R.randint(2,30),[]) for _ in range(8)]],stairs),
 exercise('Kurir di Pematang Sawah','Sedang',
 'Kurir berdiri di petak 1 pada deretan N petak dengan tinggi H. Ia boleh menuju petak berikutnya atau melewati satu petak. Energi perpindahan i ke j adalah |H[i]-H[j]|. Hitung energi minimum mencapai petak N; untuk N=1 energinya nol.',
 'Baris pertama N. Baris kedua N tinggi.', 'Satu bilangan energi minimum.',
 '1 <= N <= 400; 0 <= H[i] <= 1 000 000 000.', 'Memoisasi biaya terbaik dari suatu posisi sampai tujuan, bukan riwayat seluruh jalur.',
 '''int n;cin>>n;vector<long long> h(n),memo(n);vector<char> seen(n);for(auto &x:h)cin>>x;
function<long long(int)> f=[&](int i)->long long{
 if(i==n-1)return 0;if(seen[i])return memo[i];seen[i]=1;
 long long ans=numeric_limits<long long>::max()/4;
 for(int j=i+1;j<n&&j<=i+2;j++)ans=min(ans,llabs(h[i]-h[j])+f(j));
 return memo[i]=ans;
};cout<<f(0)<<'\\n';''',
 'F(i)=energi minimum dari petak i ke N. Basis F(N)=0. Coba seluruh tujuan legal j=i+1,i+2 dan minimalkan |H[i]-H[j]|+F(j). Setiap jalur memilih salah satu j; suffix yang tidak optimal dapat diganti suffix optimal tanpa mengubah biaya langkah pertama. Induksi menurun membuktikan optimum. O(N) waktu, O(N) memori termasuk stack. Gunakan long long karena penjumlahan banyak beda tinggi dapat melampaui int.',
 [lines(4,[10,30,20,40]),lines(1,[99]),lines(3,[5,100,5]),lines(2,[0,10**9]),lines(6,[2]*6),lines(7,[1,2,3,4,5,6,7]),lines(5,[9,1,8,2,7]),lines(400,[10**9 if i%2 else 0 for i in range(400)])]+[lines(10,[R.randrange(100) for _ in range(10)]) for _ in range(8)],frog),
 exercise('Denah Festival Batik','Menantang',
 'Denah festival berbentuk N kali M. Petak . bisa dilalui dan # ditutup. Mulai di kiri atas, pengunjung hanya berjalan satu petak ke kanan atau ke bawah sampai kanan bawah. Hitung banyak jalur. Jika petak awal atau akhir ditutup, jawabannya nol.',
 'Baris pertama N M. N baris berikutnya masing-masing string sepanjang M berisi . atau #.',
 'Satu bilangan jumlah jalur modulo 1 000 000 007.', '1 <= N,M <= 100.',
 'Posisi (r,c) harus menjadi dua parameter cache. Periksa batas sebelum akses array.',
 '''int n,m;cin>>n>>m;vector<string>g(n);for(auto &s:g)cin>>s;
vector<vector<long long>>memo(n,vector<long long>(m));vector<vector<char>>seen(n,vector<char>(m));
function<long long(int,int)> f=[&](int r,int c)->long long{
 if(r>=n||c>=m)return 0;if(g[r][c]=='#')return 0;if(r==n-1&&c==m-1)return 1;
 if(seen[r][c])return memo[r][c];seen[r][c]=1;
 return memo[r][c]=(f(r+1,c)+f(r,c+1))%1000000007LL;
};cout<<f(0,0)<<'\\n';''',
 'F(r,c)=jumlah jalur dari sel (r,c) ke tujuan. Sel di luar/tertutup bernilai 0, tujuan terbuka bernilai 1. Sel lain menjumlah F(r+1,c) dan F(r,c+1). Kelompok berdasarkan langkah pertama saling lepas. Jarak Manhattan ke tujuan selalu berkurang; induksi menurut jarak membuktikan kebenaran sekaligus terminasi. O(NM) waktu/tabel, stack O(N+M). Cache perlu penanda terpisah agar nilai nol tidak dihitung ulang.',
 [lines([3,3],'...','.#.','...'),lines([1,1],'.'),lines([1,1],'#'),lines([1,5],'..#..'),lines([2,2],'#.','..'),lines([2,2],'..','.#'),lines([4,4],'....','####','....','....'),lines([100,100],*(['.'*100]*100))]+[lines([5,6],*[''.join(R.choice('...#') for _ in range(6)) for _ in range(5)]) for _ in range(8)],gridways)]
t66=[task('Antrian Buku Perpustakaan','N buku dapat dikelompokkan berurutan menjadi paket berisi 2 atau 3 buku. Hitung jumlah urutan ukuran paket yang menghabiskan semuanya, modulo 1 000 000 007. N=0 memiliki satu susunan kosong.', 'Satu bilangan N.','Jumlah susunan.','0 <= N <= 400.',[(lines(5),lines(2)),(lines(1),lines(0))]),task('Robot Pengurang','Robot mulai pada bilangan N. Setiap operasi mengurangi 1, atau membagi 2 jika genap, atau membagi 3 jika habis dibagi 3. Cari operasi minimum sampai 1.', 'Satu bilangan N.','Jumlah operasi minimum.','1 <= N <= 400.',[(lines(10),lines(3)),(lines(1),lines(0))]),task('Pita Tanpa Tetangga','Hitung string biner sepanjang N tanpa dua angka 1 berdampingan, modulo 1 000 000 007. String kosong dihitung satu.', 'Satu bilangan N.','Banyak string.','0 <= N <= 400.',[(lines(3),lines(5)),(lines(0),lines(1))])]
day(66,'Memoization - Jembatan dari Rekursi ke DP','_PPT-05-REKURSI/Day-066 - Memoization (Jembatan Rekursi ke DP).pptx',
'''Memoisasi adalah evaluasi rekursif dengan cache berdasarkan semua parameter yang menentukan jawaban. Dua riwayat boleh memakai cache yang sama hanya bila pilihan masa depannya identik. Data input boleh global selama tidak berubah selama perhitungan; cache wajib direset ketika input berubah.

Tulis fungsi rekursif yang benar, tentukan basis, lalu tambahkan `seen`, pemeriksaan cache, dan penyimpanan hasil. `seen` berbeda dari nilai: jawaban 0 atau -1 bisa sah. Memoisasi tidak otomatis menghilangkan siklus; tiga latihan memakai dependensi yang selalu maju atau mengecil.

Untuk tangga dengan langkah 1/3 tanpa hambatan, F(0..6) = [1,1,1,2,3,4,6]. Saat F(6) meminta F(3), F(3) sudah dihitung ketika cabang F(5) turun. Pohon pemanggilan berulang berubah menjadi graf dependensi berisi N+1 state. Waktu = jumlah state yang dihitung × transisi per state, ditambah pembacaan input. Jangan menyebut semua memoisasi O(N): pada denah, jumlah state N×M.

Top-down untuk petak membaca suffix yang lebih dekat tujuan. Oracle latihan memakai tabulasi dari awal agar arah penalarannya berbeda. Buktikan recurrence sebelum mengukur kecepatan; cache hanya mempercepat jawaban yang sama, termasuk jawaban salah.

Stack tetap dipakai: memori bukan hanya tabel. Kedalaman aman bergantung platform dan ukuran frame; tidak ada ambang 100 ribu yang dijamin aman. Batas latihan dibuat kecil untuk fokus memoization. Untuk ratusan ribu posisi, pelajari tabulasi di Day 142.

Pitfall: akses indeks negatif sebelum basis; lupa modulo; cache lintas input; lupa memasukkan posisi kolom; memakai nilai 0 sebagai tanda belum dihitung; menganggap blocked boleh menjadi tempat mendarat. Pada setiap solusi, tulis state, basis, transisi, ukuran cache, serta alasan dependensi tidak bersiklus.''',e66,t66)

# Day 142.
def activities(s):
    t=list(map(int,s.split()));n=t[0];a=[t[1+3*i:4+3*i] for i in range(n)]
    @lru_cache(None)
    def f(i,prev):return 0 if i==n else max(a[i][j]+f(i+1,j) for j in range(3) if j!=prev)
    return f(0,3)
def coupon(s):
    t=list(map(int,s.split()));n=t[0];h=t[1:]
    @lru_cache(None)
    def f(i,free):
        if i==n-1:return 0
        v=[abs(h[i]-h[j])+f(j,free) for j in range(i+1,min(n,i+3))]
        if free:v += [f(j,0) for j in range(i+1,min(n,i+3))]
        return min(v)
    return f(0,1)
def exactones(s):
    n,k=map(int,s.split())
    # Combinatorial oracle: choose k nonadjacent positions, C(n-k+1,k).
    import math
    return math.comb(n-k+1,k)%MOD if 0<=k<=n-k+1 else 0
e142=[exercise('Pekan Komunitas Kreatif','Mudah','Selama N hari kamu wajib memilih tepat satu kegiatan: musik, lukis, atau tari. Kegiatan yang sama tidak boleh dipilih dua hari berturut-turut. Baris i memberi kepuasan ketiga kegiatan hari itu; nilainya boleh negatif. Cari total kepuasan maksimum.',
 'N, diikuti N baris masing-masing tiga bilangan.', 'Total maksimum.', '1 <= N <= 300; -1 000 000 000 <= nilai <= 1 000 000 000.',
 'Hari saja belum cukup: dua riwayat dengan kegiatan terakhir berbeda punya pilihan esok yang berbeda.',
 '''int n;cin>>n;array<long long,3>prev{},cur{};for(int i=0;i<n;i++){
 array<long long,3>a;for(auto &x:a)cin>>x;
 for(int j=0;j<3;j++){cur[j]=numeric_limits<long long>::lowest()/4;for(int k=0;k<3;k++)if(k!=j)cur[j]=max(cur[j],prev[k]+a[j]);}
 prev=cur;
}cout<<*max_element(prev.begin(),prev.end())<<'\\n';''',
 'dp[i][j]=nilai maksimum setelah hari i dengan kegiatan terakhir j. Untuk hari pertama dp[1][j]=a[1][j]; implementasi memakai tiga nilai virtual 0 di hari 0 yang memberikan hasil sama. Transisi a[i][j]+max(dp[i-1][k], k!=j). Semua jadwal legal punya satu kegiatan sebelumnya; mengganti prefix dengan optimum tidak mengubah legalitas esok karena j diketahui. Induksi hari membuktikan optimum. O(9N)=O(N) waktu, O(1) memori. Nol tidak boleh mengalahkan jadwal negatif: wajib memilih setiap hari.',
 [lines(3,[10,40,70],[20,50,80],[30,60,90]),lines(1,[-5,-2,-9]),lines(2,[9,0,0],[9,0,0]),lines(1,[0,0,0]),lines(4,*([[-3,-3,-3]]*4)),lines(3,*([[10**9]*3]*3)),lines(2,[-1,-100,-100],[-1,-100,-100]),lines(300,*([[1,2,3]]*300))]+[lines(6,*[[R.randint(-9,9) for _ in range(3)] for _ in range(6)]) for _ in range(8)],activities),
 exercise('Satu Kupon di Jalur Dieng','Sedang','Ada N pos dengan tinggi H. Dari i kamu boleh maju ke i+1 atau i+2, membayar |H[i]-H[j]| energi. Tersedia satu kupon yang dapat menggratiskan satu perpindahan; boleh tidak dipakai. Cari energi minimum dari pos 1 ke N.',
 'N, kemudian N tinggi.', 'Energi minimum.', '1 <= N <= 300; 0 <= H[i] <= 1 000 000 000.',
 'Dua jalur di pos yang sama tidak setara bila salah satunya sudah menghabiskan kupon.',
 '''int n;cin>>n;vector<long long>h(n);for(auto &x:h)cin>>x;const long long INF=numeric_limits<long long>::max()/4;
vector<array<long long,2>>dp(n,array<long long,2>{INF,INF});dp[0][0]=0;
for(int i=0;i<n;i++)for(int used=0;used<2;used++)if(dp[i][used]<INF){
 for(int j=i+1;j<n&&j<=i+2;j++){
 dp[j][used]=min(dp[j][used],dp[i][used]+llabs(h[i]-h[j]));
 if(!used)dp[j][1]=min(dp[j][1],dp[i][0]);
 }}cout<<min(dp[n-1][0],dp[n-1][1])<<'\\n';''',
 'dp[i][u]=energi minimum mencapai i setelah memakai u kupon, u=0/1. Basis hanya dp[1][0]=0; status sudah terpakai tidak reachable di awal. Setiap sisi legal menambah biaya normal dengan u tetap, atau biaya nol jika u=0 lalu menjadi 1. Urutan i menaik valid sebab setiap perpindahan maju. Semua jalur masuk melalui salah satu transisi dan setiap transisi legal, maka induksi i membuktikan nilai optimum. Ambil minimum dua status karena kupon opsional. O(N) waktu/memori. Menyimpan satu angka per pos dapat membuang prefix lebih mahal yang masih punya kupon.',
 [lines(4,[0,9,10,100]),lines(1,[88]),lines(2,[0,10**9]),lines(5,[0,0,100,100,100]),lines(6,[10]*6),lines(7,[0,5,100,6,200,7,300]),lines(3,[5,100,7]),lines(300,[R.randrange(10**9) for _ in range(300)])]+[lines(10,[R.randrange(30) for _ in range(10)]) for _ in range(8)],coupon),
 exercise('Lampu Taman Sejumlah K','Menantang','Ada N tiang berjajar. Pilih tepat K tiang untuk dinyalakan, dengan larangan dua tiang bersebelahan menyala. Hitung banyak konfigurasi; tiang berbeda menghasilkan pilihan berbeda. N=K=0 memiliki satu konfigurasi kosong.',
 'Dua bilangan N K.', 'Banyak konfigurasi modulo 1 000 000 007.', '0 <= N <= 300; 0 <= K <= N.',
 'State (posisi, jumlah menyala, status tiang terakhir); jumlah menyala tidak bisa dibuang.',
 '''int n,k;cin>>n>>k;const long long MOD=1000000007;vector<array<long long,2>>dp(k+1),nxt(k+1);dp[0][0]=1;
for(int i=0;i<n;i++){
 fill(nxt.begin(),nxt.end(),array<long long,2>{0,0});
 for(int c=0;c<=k;c++){nxt[c][0]=(dp[c][0]+dp[c][1])%MOD;if(c<k)nxt[c+1][1]=dp[c][0];}
 dp.swap(nxt);
}cout<<(dp[k][0]+dp[k][1])%MOD<<'\\n';''',
 'dp[i][c][b]=jumlah konfigurasi i tiang pertama, tepat c menyala, dengan status terakhir b. Matikan berikutnya dari kedua b; nyalakan hanya dari b=0 sambil menaikkan c. Basis dp[0][0][0]=1. Setiap konfigurasi memiliki prefix unik dan pilihan terakhir unik; transisi legal mencakup seluruh konfigurasi tanpa menghitung ganda. O(NK) waktu, O(K) memori setelah rolling; tabel baru harus direset. Oracle memakai bijeksi posisi terpilih x_j -> x_j-(j-1), menghasilkan C(N-K+1,K), sebagai pembanding independen.',
 [lines([5,2]),lines([3,2]),lines([0,0]),lines([1,1]),lines([6,0]),lines([4,3]),lines([300,100]),lines([300,300])]+[lines([n,R.randint(0,n)]) for n in range(5,13)],exactones)]
t142=[task('Playlist Tanpa Genre Berulang','Ada N slot dan G genre berlabel. Isi setiap slot satu genre, tanpa genre sama berdampingan. Hitung jumlah playlist modulo 1 000 000 007; slot kosong memiliki satu playlist.','N G.','Jumlah playlist.','0 <= N <= 300; 1 <= G <= 20.',[(lines([3,2]),lines(2)),(lines([1,4]),lines(4))]),task('Kupon Harus Habis','Gunakan model pos dan energi Exercise 2, tetapi N>=2 dan kupon wajib digunakan tepat sekali. Cetak energi minimum.','N, kemudian N tinggi.','Energi minimum.','2 <= N <= 300; 0 <= H[i] <= 10^9.',[(lines(2,[7,99]),lines(0)),(lines(4,[0,4,8,12]),lines(4))]),task('Tepat K Tanpa Tiga','Hitung string biner panjang N dengan tepat K angka 1 dan tanpa substring 111, modulo 1 000 000 007.','N K.','Jumlah string.','0 <= N <= 100; 0 <= K <= N.',[(lines([3,2]),lines(3)),(lines([3,3]),lines(0))])]
day(142,'Top-Down vs Bottom-Up dan Cara Mendesain State','_PPT-09-DP/Day-142 - Top-Down, Bottom-Up & Desain State.pptx',
'''Top-down dan bottom-up mengevaluasi recurrence yang sama dengan urutan berbeda. Top-down memanggil dependensi ketika dibutuhkan; bottom-up memilih urutan topologis dependensi. Bukan semua bottom-up berarti indeks naik: suffix bisa menurun dan interval memakai panjang.

Empat uji state: dapat dijelaskan satu kalimat; cukup untuk menentukan pilihan berikutnya; semua riwayat yang masuk state memiliki masa depan setara; jumlah state dan transisinya sesuai batas. Nilai optimum yang sudah terkumpul biasanya isi tabel, bukan dimensi tambahan. Status kupon dan kegiatan terakhir justru menentukan masa depan dan wajib disimpan.

Pada kegiatan dua hari dengan nilai [9,0,0], [9,0,0], baris pertama [9,0,0], baris kedua [9,9,9], optimum 9. State salah `dp[hari]` bisa mengira 9+9=18 legal. Untuk kupon, `F(i,sisa)` top-down mencoba biaya normal dan gratis; tabulasi menyebarkan biaya dari (i,used) ke posisi lebih besar. Kedua state berbeda orientasi tetapi setara setelah arti status dijelaskan.

Pada lampu N=3,K=2, satu-satunya string 101. Setelah dua tiang: (c=0,akhir0)=1, (c=1,akhir0)=1, (c=1,akhir1)=1. Tiang ketiga dapat dinyalakan hanya dari akhir0. Tepat K berbeda dari paling banyak K: jawaban harus dibaca pada c=K.

Bukti DP terdiri dari basis benar, seluruh keputusan legal tercakup, transisi tidak menciptakan keputusan ilegal, dan dependensi dihitung lebih dahulu. Untuk counting, buktikan kelompok transisi terpisah. Estimasi kerja N×K×2×2 untuk lampu; jangan menganggap 10^8 operasi selalu aman pada semua bahasa/platform.

Pitfall: meniadakan pilihan wajib ketika semua skor negatif; mengisi semua state awal dengan nol pada minimisasi; lupa reset rolling; menggabungkan status kupon; salah akhir jawaban. Cache top-down harus direset ketika input berubah. Stack aman tidak memiliki angka universal; pilih iteratif untuk rantai panjang.''',e142,t142)

# Day 144: denomination-multiplicity recursion is an independent oracle.
def unbounded_oracle(s,mode):
    t=list(map(int,s.split()));n,W=t[:2];z=1 if mode=='coins' else 2;a=[t[2+z*i:2+z*(i+1)] for i in range(n)]
    @lru_cache(None)
    def f(i,remaining):
        if i==n:return 0 if remaining==0 or mode=='max' else 10**30
        w=a[i][0];v=1 if mode=='coins' else a[i][1]
        vals=[k*v+f(i+1,remaining-k*w) for k in range(remaining//w+1)]
        return max(vals) if mode=='max' else min(vals)
    ans=f(0,W);return -1 if ans>=10**30 else ans
# For larger capacity, separate shortest-path BFS for minimum coin count.
def coin_oracle(s):
    from collections import deque
    t=list(map(int,s.split()));n,W=t[:2];cs=t[2:];d=[-1]*(W+1);d[0]=0;q=deque([0])
    while q:
        u=q.popleft()
        for c in cs:
            if u+c<=W and d[u+c]<0:d[u+c]=d[u]+1;q.append(u+c)
    return d[W]
e144=[exercise('Keping Pasar Malam','Mudah','Pasar malam menerima N nilai keping. Setiap nilai tersedia tanpa batas. Untuk membayar tepat X, cari jumlah keping minimum. Pilihan terbesar lebih dahulu tidak selalu optimal. X=0 dapat dibayar tanpa keping.',
 'Baris pertama N X. Baris kedua N nilai keping berbeda.', 'Jumlah keping minimum, atau -1 bila tidak mungkin.',
 '1 <= N <= 60; 0 <= X <= 100 000; 1 <= nilai keping <= 100 000.',
 'Gunakan INF untuk nominal yang belum terjangkau; bukan nol.',
 '''int n,x;cin>>n>>x;vector<int>c(n);for(int &v:c)cin>>v;const int INF=1000000000;vector<int>dp(x+1,INF);dp[0]=0;
for(int s=1;s<=x;s++)for(int v:c)if(v<=s&&dp[s-v]!=INF)dp[s]=min(dp[s],dp[s-v]+1);
cout<<(dp[x]==INF?-1:dp[x])<<'\\n';''',
 'dp[s]=jumlah keping minimum untuk nominal tepat s. Basis dp[0]=0, sisanya INF. Coba nilai keping terakhir c: dp[s]=min(dp[s-c]+1). Menghapus keping terakhir mengubah solusi menjadi solusi sah untuk s-c; prefix yang lebih buruk dapat diganti optimum. Semua c dicoba sehingga induksi s membuktikan minimum. O(NX) waktu, O(X) memori. Oracle menggunakan BFS pada graf nominal karena setiap keping adalah satu sisi berbiaya 1.',
 [lines([3,6],[1,3,4]),lines([2,7],[4,6]),lines([2,0],[5,9]),lines([1,12],[3]),lines([1,2],[3]),lines([3,18],[5,7,9]),lines([2,100000],[1,99999]),lines([1,99999],[2])]+[lines([4,40],R.sample(range(1,20),4)) for _ in range(8)],coin_oracle),
 exercise('Cetak Stiker Komunitas','Sedang','Mesin memiliki W unit tinta. Ada N desain; mencetak desain i memakai w[i] tinta dan memberi v[i] poin. Setiap desain boleh dicetak berulang tanpa batas. Tinta boleh tersisa dan boleh tidak mencetak. Cari poin maksimum.',
 'N W, lalu N baris w[i] v[i].', 'Poin maksimum.', '1 <= N <= 100; 0 <= W <= 20 000; 1 <= w[i] <= 20 000; 0 <= v[i] <= 10^9.',
 'Kapasitas berarti paling banyak. Loop kapasitas maju memungkinkan desain sekarang dipakai kembali.',
 '''int n,W;cin>>n>>W;vector<long long>dp(W+1);for(int i=0;i<n;i++){int w;long long v;cin>>w>>v;
 for(int s=w;s<=W;s++)dp[s]=max(dp[s],dp[s-w]+v);
}cout<<dp[W]<<'\\n';''',
 'Setelah jenis i diproses, dp[s] adalah poin maksimum dengan tinta paling banyak s dari jenis 1..i. Pilihan tidak memakai i mempertahankan nilai lama; pilihan memakai i mengambil dp[s-w_i] yang sudah boleh memakai i, lalu menambah v_i. Loop maju menjamin dependensi tersebut tersedia. Mengeluarkan satu cetakan i dari solusi yang memakainya membuktikan kelengkapan. O(NW) waktu, O(W) memori. Semua nol benar karena kapasitas boleh tersisa dan pilihan kosong sah; tipe long long menampung W×v maksimum.',
 [lines([2,7],[3,5],[4,6]),lines([1,10],[3,4]),lines([1,0],[1,100]),lines([2,5],[6,99],[7,999]),lines([1,20],[2,10**9]),lines([2,11],[5,10],[3,7]),lines([2,10],[2,0],[3,0]),lines([1,20000],[1,10**9])]+[lines([3,25],*[[R.randint(2,9),R.randint(0,20)] for _ in range(3)]) for _ in range(8)],lambda s:unbounded_oracle(s,'max')),
 exercise('Paket Bibit Tepat Pesanan','Menantang','Koperasi harus membeli tepat X bibit. Ada N jenis paket; jenis i memuat b[i] bibit dan berharga c[i]. Paket tiap jenis tersedia tanpa batas. Cari harga minimum, dengan larangan membeli bibit berlebih. Harga paket dapat nol.',
 'N X, lalu N baris b[i] c[i].', 'Harga minimum untuk tepat X bibit, atau -1 jika mustahil.',
 '1 <= N <= 100; 0 <= X <= 20 000; 1 <= b[i] <= 20 000; 0 <= c[i] <= 10^9.',
 'Minimum jumlah paket tidak sama dengan minimum harga. Hanya dp[0] yang diawali nol.',
 '''int n,x;cin>>n>>x;const long long INF=numeric_limits<long long>::max()/4;vector<long long>dp(x+1,INF);dp[0]=0;
for(int i=0;i<n;i++){int b;long long c;cin>>b>>c;for(int s=b;s<=x;s++)if(dp[s-b]!=INF)dp[s]=min(dp[s],dp[s-b]+c);}
cout<<(dp[x]==INF?-1:dp[x])<<'\\n';''',
 'dp[s]=harga minimum membentuk jumlah tepat s. Basis dp[0]=0 dan INF untuk lainnya. Setelah jenis i, pilihan tidak menggunakan paket i mempertahankan dp lama; jika digunakan, kurangi satu paket i dan tambahkan c_i pada dp[s-b_i] yang sudah boleh memakainya. Induksi jenis dan jumlah membuktikan recurrence loop maju. Output hanya dp[X], bukan minimum rentang yang membolehkan kurang/lebih. O(NX) waktu dan O(X) memori. Cek INF sebelum penjumlahan; b_i>0 menjamin dependensi menurun meskipun biaya nol.',
 [lines([2,6],[3,8],[2,3]),lines([2,5],[2,0],[4,9]),lines([1,0],[7,3]),lines([1,8],[2,0]),lines([2,10],[5,10],[2,3]),lines([1,3],[4,1]),lines([1,8],[1,10**9]),lines([1,20000],[1,10**9])]+[lines([3,25],*[[R.randint(2,9),R.randint(0,20)] for _ in range(3)]) for _ in range(8)],lambda s:unbounded_oracle(s,'cost'))]
t144=[task('Pola Gelang Berurutan','Setiap manik memiliki ukuran dari N bilangan berbeda dan tersedia tanpa batas. Hitung banyak urutan ukuran yang totalnya tepat X, modulo 1 000 000 007. Urutan berbeda dihitung berbeda. X=0 memiliki satu urutan kosong.','N X, lalu N ukuran.','Jumlah urutan.','1 <= N <= 50; 0 <= X <= 10 000; 1 <= ukuran <= 10 000.',[(lines([2,3],[1,2]),lines(3)),(lines([1,3],[2]),lines(0))]),task('Kantong Koin Tanpa Urutan','Seperti Exercise 1, tetapi hitung banyak pilihan jumlah keping tiap nilai yang totalnya X, modulo 1 000 000 007. Urutan keping tidak membedakan pilihan; nilai keping berbeda.','N X, lalu N nilai keping.','Jumlah kombinasi.','1 <= N <= 50; 0 <= X <= 10 000; 1 <= nilai <= 10 000.',[(lines([2,3],[1,2]),lines(2)),(lines([2,0],[3,7]),lines(1))]),task('Tiket dengan Batas Banyak','Setiap paket jenis i berisi b[i] tiket dan boleh dibeli berulang. Ada N jenis berukuran berbeda. Tentukan apakah tepat X tiket bisa didapat dengan paling banyak K paket.','N X K, lalu N ukuran.','YES atau NO.','1 <= N <= 50; 0 <= X <= 10 000; 0 <= K <= 10 000; 1 <= b[i] <= 10 000.',[(lines([2,6,2],[1,3]),lines('YES')),(lines([2,6,1],[1,3]),lines('NO'))])]
day(144,'Coin Change Minimum dan Unbounded Knapsack','_PPT-09-DP/Day-144 - Coin Change Minimum & Unbounded Knapsack.pptx',
'''Unbounded berarti setiap jenis tersedia tanpa batas, bukan setiap perpindahan bebas biaya. Nominal/berat harus positif agar transisi menuju kapasitas lebih kecil. Koin minimum, nilai maksimum, dan harga minimum memiliki operator berbeda walaupun indeks tabelnya mirip.

Untuk nominal tepat, dp[0]=0 dan keadaan lain INF pada minimisasi; pada maksimisasi tepat gunakan -INF. Untuk kapasitas paling banyak, seluruh dp[s]=0 sah bila boleh tidak memilih dan nilai nonnegatif. Contoh paket 4 bibit, target 3: init semua nol akan keliru menyatakan harga nol.

Trace minimum keping {1,3,4}, target 6: dp[0..6]=[0,1,2,1,1,2,2]. Greedy 4+1+1 berjumlah tiga, sedangkan 3+3 dua. Ini counterexample konkret bahwa strategi nominal terbesar tidak universal.

Dua formulasi: berdasarkan keping terakhir, dp[s]=min_c(dp[s-c]+1), dengan s naik; atau berdasarkan jenis, dp_i[s]=min(dp_(i-1)[s], dp_i[s-c]+1). Mengompresi formulasi kedua memakai s menaik karena bagian kedua membaca baris sekarang. Sebaliknya 0/1 harus membaca baris sebelumnya dan kapasitas menurun.

Untuk menghitung cara, loop sum di luar menghitung urutan; loop jenis di luar menghitung kombinasi. Dengan {1,2}, target 3: urutan 111,12,21 = 3, kombinasi 111,12 = 2. Ini tidak berarti loop tersebut memberi minimum berbeda: operator min tidak menghitung multiplisitas, dan keduanya dapat benar untuk minimisasi.

Bukti selalu klasifikasikan solusi menurut keputusan terakhir/jenis terakhir, lalu gunakan optimal substructure. Banyak state X+1, transisi N, jadi O(NX). Batas target adalah bagian penting model pseudo-polynomial: nilai X besar tidak dapat diatasi hanya karena N kecil. Simpan biaya dalam long long; jangan menambah ke sentinel tanpa cek.

Pitfall: loop mundur membuat stok menjadi satu; memakai target sebagai jumlah paket; membolehkan kelebihan pada soal tepat; menerima paket ukuran nol; lupa X=0; memilih nilai maksimum rasio tanpa bukti. Ketiga latihan memisahkan ketiga tujuan tersebut.''',e144,t144)

# Day 147: reference enumerates each original stock, never binary bundles.
def bounded_oracle(s,mode):
    t=list(map(int,s.split()));n,W=t[:2];z=3 if mode=='max' else 2;a=[t[2+z*i:2+z*(i+1)] for i in range(n)]
    d={0:0}
    for item in a:
        w,v,c=(item if mode=='max' else [item[0],1,item[1]])
        nd={}
        for old,score in d.items():
            for k in range(min(c,(W-old)//w)+1):
                s2=old+k*w;v2=score+k*v
                if s2 not in nd or (v2>nd[s2] if mode=='max' else v2<nd[s2]):nd[s2]=v2
        d=nd
    return max(d.values()) if mode=='max' else (len(d)-1 if mode=='reach' else d.get(W,-1))
bounded_max_cpp='''int n,W;cin>>n>>W;vector<long long>dp(W+1);
for(int i=0;i<n;i++){int w,c;long long v;cin>>w>>v>>c;c=min(c,W/w);
 for(int p=1;c>0;p*=2){int q=min(p,c);c-=q;int weight=q*w;long long value=q*v;
 for(int s=W;s>=weight;s--)dp[s]=max(dp[s],dp[s-weight]+value);}}
cout<<dp[W]<<'\\n';'''
bounded_min_cpp='''int n,W;cin>>n>>W;const int INF=1000000000;vector<int>dp(W+1,INF);dp[0]=0;
for(int i=0;i<n;i++){int w,c;cin>>w>>c;c=min(c,W/w);
 for(int p=1;c>0;p*=2){int q=min(p,c);c-=q;int weight=q*w;
 for(int s=W;s>=weight;s--)if(dp[s-weight]!=INF)dp[s]=min(dp[s],dp[s-weight]+q);}}
cout<<(dp[W]==INF?-1:dp[W])<<'\\n';'''
bounded_reach_cpp='''int n,W;cin>>n>>W;vector<char>dp(W+1);dp[0]=1;
for(int i=0;i<n;i++){int w,c;cin>>w>>c;c=min(c,W/w);
 for(int p=1;c>0;p*=2){int q=min(p,c);c-=q;int weight=q*w;
 for(int s=W;s>=weight;s--)if(dp[s-weight])dp[s]=1;}}
cout<<count(dp.begin()+1,dp.end(),char(1))<<'\\n';'''
e147=[exercise('Paket Logistik Pulau','Mudah','Perahu berkapasitas W membawa N jenis bantuan. Satu unit jenis i memiliki berat w[i], manfaat v[i], dan stok c[i]. Pilih nol atau lebih unit setiap jenis tanpa melebihi stok maupun kapasitas. Maksimalkan manfaat; perahu boleh menyisakan kapasitas.',
 'N W, kemudian N baris w[i] v[i] c[i].', 'Manfaat maksimum.',
 '1 <= N <= 60; 0 <= W <= 20 000; 1 <= w[i] <= 20 000; 0 <= v[i] <= 10^9; 0 <= c[i] <= 10^9.',
 'Stok 13 dapat diwakili paket 1,2,4,6. Nilai dan berat paket harus dikalikan jumlah unit.',bounded_max_cpp,
 'Batasi stok efektif min(c_i, floor(W/w_i)); kelebihannya mustahil dipakai. Pecah stok menjadi paket 1,2,4,...,sisa, lalu jalankan 0/1 knapsack kapasitas menurun. Setiap jumlah asli 0..c_i dapat dibentuk paket, dan total paket tepat c_i sehingga tidak ada jumlah ilegal. Manfaat dan berat aditif membuat kedua representasi ekuivalen. Induksi paket membuktikan dp[s] optimum kapasitas paling banyak s. O(W × sum log(c_eff+1)) waktu, O(W) memori; clipping menjaga perkalian berat/pangkat tetap aman. Nilai memakai long long.',
 [lines([2,10],[2,3,5],[3,5,1]),lines([1,10],[2,3,2]),lines([1,0],[1,8,10]),lines([1,26],[2,3,13]),lines([1,11],[2,3,5]),lines([2,8],[2,10,0],[9,99,8]),lines([1,20000],[1,10**9,10**9]),lines([1,1],[20000,999,10**9])]+[lines([3,25],*[[R.randint(1,7),R.randint(0,30),R.randint(0,6)] for _ in range(3)]) for _ in range(8)],lambda s:bounded_oracle(s,'max')),
 exercise('Kasir dengan Laci Terbatas','Sedang','Kasir harus membuat kembalian tepat X. Ada N jenis keping; nilai w[i] tersedia paling banyak c[i] keping. Cari jumlah keping paling sedikit, atau nyatakan mustahil. Dua jenis boleh bernilai sama tetapi stoknya tetap masing-masing.',
 'N X, kemudian N baris w[i] c[i].', 'Jumlah keping minimum, atau -1.',
 '1 <= N <= 60; 0 <= X <= 20 000; 1 <= w[i] <= 20 000; 0 <= c[i] <= 10^9.',
 'Paket q keping menambah biaya q, bukan 1. Gunakan INF untuk jumlah tepat yang tak terjangkau.',bounded_min_cpp,
 'Gunakan pemecahan stok seperti Exercise 1, tetapi isi dp[0]=0 dan dp[s>0]=INF. Paket q keping bernilai q*w menaikkan jumlah keping sebanyak q. Transisi mundur dp[s]=min(dp[s],dp[s-q*w]+q) menjaga setiap paket dipakai paling banyak sekali. Kelengkapan representasi paket mempertahankan semua pilihan stok asli dan jumlah kepingnya, sehingga optimum juga dipertahankan. O(X × sum log(c_eff+1)) waktu, O(X) memori. Paket bukan sebuah keping fisik; menambah 1 adalah bug yang diuji stok 13.',
 [lines([2,6],[3,2],[1,6]),lines([1,6],[3,1]),lines([1,0],[9,0]),lines([1,26],[2,13]),lines([2,8],[4,1],[4,1]),lines([1,7],[2,10]),lines([1,20000],[1,10**9]),lines([2,10],[6,1],[4,0])]+[lines([3,25],*[[R.randint(1,7),R.randint(0,6)] for _ in range(3)]) for _ in range(8)],lambda s:bounded_oracle(s,'min')),
 exercise('Nominal Donasi yang Mungkin','Menantang','Panitia memiliki N jenis kupon donasi; jenis i bernilai w[i] dan tersedia c[i] lembar. Hitung berapa nominal berbeda dalam 1 sampai S yang bisa dibentuk memakai sebagian kupon. Yang dihitung nominal, bukan banyak cara memilih. Nominal nol tidak dihitung.',
 'N S, kemudian N baris w[i] c[i].', 'Jumlah nominal terjangkau dalam 1..S.',
 '1 <= N <= 60; 0 <= S <= 20 000; 1 <= w[i] <= 20 000; 0 <= c[i] <= 10^9.',
 'Gunakan boolean dan OR. Dekomposisi biner bisa menggandakan representasi jumlah, sehingga tidak langsung valid untuk menghitung cara.',bounded_reach_cpp,
 'bisa[s]=apakah total tepat s tercapai dari paket yang diproses. Basis bisa[0]=true. Paket q*w memperbarui bisa[s] |= bisa[s-q*w] secara menurun. Representasi jumlah stok lengkap menjamin seluruh nominal asli terjangkau, dan total paket tidak melewati stok. OR idempoten: representasi ganda tidak menggandakan jawaban. Hasil ialah banyak true pada s=1..S. O(S × sum log(c_eff+1)) waktu, O(S) memori. Tidak benar mengganti OR dengan penjumlahan untuk menghitung kombinasi asli: stok 5 dipecah 1,2,2 memiliki dua cara paket mencapai dua unit.',
 [lines([2,10],[2,2],[3,1]),lines([1,5],[1,5]),lines([1,0],[1,5]),lines([1,10],[2,0]),lines([1,30],[2,13]),lines([2,6],[2,1],[2,1]),lines([1,20000],[1,10**9]),lines([2,7],[8,10],[9,10])]+[lines([3,25],*[[R.randint(1,7),R.randint(0,6)] for _ in range(3)]) for _ in range(8)],lambda s:bounded_oracle(s,'reach'))]
t147=[task('Bagi Stok Sama Berat','Jenis barang i berbobot w[i] sebanyak c[i]. Tentukan apakah seluruh stok dapat dibagi ke dua kelompok dengan berat sama. Barang satu jenis identik dan boleh tersebar di kedua kelompok.','N, kemudian N baris w[i] c[i].','YES atau NO.','1 <= N <= 50; 1 <= w[i] <= 1000; 0 <= c[i] <= 1000; total berat <= 50 000.',[(lines(2,[2,2],[3,2]),lines('YES')),(lines(1,[3,3]),lines('NO'))]),task('Pesanan Wajib Penuh','Seperti Exercise 1, tetapi berat total wajib tepat W. Nilai manfaat nonnegatif. Cetak manfaat maksimum atau -1 bila mustahil.','N W, lalu N baris w v c.','Manfaat maksimum atau -1.','1 <= N <= 50; 0 <= W <= 10 000; 1 <= w <= 10 000; 0 <= v <= 10^9; 0 <= c <= 10^9.',[(lines([1,5],[2,9,3]),lines(-1)),(lines([1,6],[2,9,3]),lines(27))]),task('Hitung Pilihan Stok Asli','Hitung vektor jumlah (q1,...,qN) dengan 0<=qi<=ci dan sum(qi*wi)=S, modulo 1 000 000 007. Jenis berbeda tetap membedakan pilihan walau wi sama. Jangan menghitung pemilihan paket biner.','N S, lalu N baris w c.','Jumlah vektor.','1 <= N <= 30; 0 <= S <= 2000; 1 <= w <= 2000; 0 <= c <= 20.',[(lines([1,2],[1,5]),lines(1)),(lines([2,2],[1,2],[1,2]),lines(3))])]
day(147,'Bounded Knapsack dan Optimasi Dekomposisi Biner','_PPT-09-DP/Day-147 - Bounded Knapsack & Dekomposisi Biner.pptx',
'''Bounded knapsack membatasi jumlah unit tiap jenis: 0<=q_i<=c_i. Menyalin barang c_i kali benar tetapi mahal. Sebelum optimasi, recurrence referensi adalah D_i[s]=opt atas q=0..min(c_i,s/w_i) dari D_(i-1)[s-q*w_i]+q*v_i. Recurrence ini dipakai oracle, sedangkan solusi C++ memakai paket biner.

Stok 13 -> 1,2,4,6. Tiga paket awal mewakili 0..7; memilih paket 6 memberi 6..13. Gabungan interval menutup 0..13. Secara umum, paket terakhir q<=S+1 setelah paket lama mencakup 0..S; interval [0,S] dan [q,q+S] bersentuhan/bertumpang tindih. Induksi membuktikan tidak ada jumlah terlewat. Jumlah seluruh paket tepat stok sehingga tidak ada jumlah berlebih.

Contoh berat 2, manfaat 3, stok 5 -> paket (2,3),(4,6),(4,6). Kapasitas 10 memberi 15, kapasitas 11 tetap 15. Semua paket diperlakukan 0/1 dengan kapasitas menurun. Loop maju akan mengizinkan paket dipakai berulang dan melanggar stok.

Clipping c_eff=min(c,W/w) aman karena bahkan seluruh kapasitas tidak menampung lebih banyak unit. Lakukan sebelum mengalikan stok besar dengan berat. Kompleksitas O(W×sum_i log(c_eff_i+1)), bukan O(W×sum_i c_i). Untuk stok nol, tidak ada paket. Nilai paket q*v harus long long.

Paket biner mempertahankan kemungkinan dan optimum aditif, tetapi bukan banyak representasi. Stok 5 -> 1,2,2: dua unit dapat diambil dengan salah satu paket 2. Mengganti max dengan penjumlahan akan menghitung cara asli dua kali. Tugas 3 memakai recurrence asli per jenis untuk melatih batas teknik ini.

Minimal keping: biaya paket q adalah q. Reachability: gunakan OR dan hitung nominal positif saja. Tepat kapasitas: hanya dp[0] reachable; paling banyak kapasitas dengan nilai nonnegatif: semua nol sah. Menukar initialisasi ini adalah kesalahan yang lebih mendasar daripada salah arah loop.

Pitfall: membuang sisa nonpangkat dua; menggandakan sisa tanpa mengurangi; stok nol; perkalian int overflow; menganggap paket sama dengan satu keping; menghitung nominal nol; memakai pemecahan untuk counting tanpa menguji keunikan representasi.''',e147,t147)

# Day 151. Recursive oracle for interval exercises; palindrome oracle checks slices directly.
def chain(s):
    t=list(map(int,s.split()));n=t[0];p=t[1:]
    @lru_cache(None)
    def f(l,r):return 0 if l==r else min(f(l,k)+f(k+1,r)+p[l]*p[k+1]*p[r+1] for k in range(l,r))
    return f(0,n-1)
def merge(s):
    t=list(map(int,s.split()));n=t[0];a=t[1:]
    @lru_cache(None)
    def f(l,r):return 0 if l==r else sum(a[l:r+1])+min(f(l,k)+f(k+1,r) for k in range(l,r))
    return f(0,n-1)
def palindrome(s):
    s=s.strip();n=len(s)
    @lru_cache(None)
    def f(i):return 0 if i==n else min(1+f(j) for j in range(i+1,n+1) if s[i:j]==s[i:j][::-1])
    return f(0)-1
# Avoid deep recursion in longest adversarial palindrome oracle.
def palindrome_iter(s):
    s=s.strip();d=[0]+[len(s)+1]*len(s)
    for j in range(1,len(s)+1):d[j]=min(d[i]+1 for i in range(j) if s[i:j]==s[i:j][::-1])
    return d[-1]-1
e151=[exercise('Rantai Filter Citra Batik','Mudah','Laboratorium harus mengalikan N matriks dalam urutan tetap A1*A2*...*AN. Matriks i berukuran p[i-1] kali p[i]. Mengalikan matriks a kali b dengan b kali c memerlukan a*b*c perkalian skalar. Pilih pengelompokan tanda kurung untuk meminimalkan total perkalian skalar; urutan matriks tidak boleh ditukar.',
 'N, lalu N+1 bilangan p[0] sampai p[N].', 'Jumlah perkalian skalar minimum.',
 '1 <= N <= 180; 1 <= p[i] <= 100 000.', 'Pisahkan berdasarkan perkalian terakhir, bukan perkalian pertama.',
 '''int n;cin>>n;vector<long long>p(n+1);for(auto &x:p)cin>>x;vector<vector<long long>>dp(n,vector<long long>(n));
for(int len=2;len<=n;len++)for(int l=0;l+len<=n;l++){int r=l+len-1;dp[l][r]=numeric_limits<long long>::max()/4;
 for(int k=l;k<r;k++)dp[l][r]=min(dp[l][r],dp[l][k]+dp[k+1][r]+p[l]*p[k+1]*p[r+1]);}
cout<<dp[0][n-1]<<'\\n';''',
 'dp[l][r]=biaya minimum mengalikan matriks indeks 0-based l..r. Matriks hasil berukuran p[l]×p[r+1]. Bila perkalian terakhir memisah di k, biayanya dp[l][k]+dp[k+1][r]+p[l]*p[k+1]*p[r+1]. Semua struktur kurung punya satu split terakhir; mengganti kedua subtree dengan optimum tidak mengubah dimensinya. Induksi panjang interval membuktikan optimum. Basis dp[i][i]=0. O(N^3) waktu, O(N^2) memori. Batas biaya <=(N-1)*10^15=1.79×10^17, muat long long tetapi bukan int.',
 [lines(3,[10,30,5,60]),lines(1,[7,11]),lines(2,[100000]*3),lines(4,[40,20,30,10,30]),lines(5,[1]*6),lines(3,[100,1,100,1]),lines(6,[3,7,2,9,4,6,5]),lines(180,[100000]*181)]+[lines(8,[R.randint(1,30) for _ in range(9)]) for _ in range(8)],chain),
 exercise('Menggabungkan Gudang Kopi','Sedang','Ada N karung kopi berjajar dengan berat a[i]. Satu operasi menggabungkan tepat dua kelompok bersebelahan menjadi satu kelompok, dengan biaya sama dengan total berat keduanya. Urutan karung harus tetap. Gabungkan semuanya menjadi satu kelompok dengan biaya total minimum; N=1 membutuhkan nol operasi.',
 'N, lalu N berat.', 'Biaya total minimum.', '1 <= N <= 180; 0 <= a[i] <= 1 000 000 000.',
 'Penggabungan terakhir membagi interval menjadi dua. Gunakan prefix sum untuk berat interval.',
 '''int n;cin>>n;vector<long long>pref(n+1);for(int i=0;i<n;i++){long long x;cin>>x;pref[i+1]=pref[i]+x;}
vector<vector<long long>>dp(n,vector<long long>(n));
for(int len=2;len<=n;len++)for(int l=0;l+len<=n;l++){int r=l+len-1;dp[l][r]=numeric_limits<long long>::max()/4;
 for(int k=l;k<r;k++)dp[l][r]=min(dp[l][r],dp[l][k]+dp[k+1][r]+pref[r+1]-pref[l]);}
cout<<dp[0][n-1]<<'\\n';''',
 'dp[l][r]=biaya menggabungkan karung l..r menjadi satu. Operasi terakhir pasti menggabungkan dua kelompok interval [l,k] dan [k+1,r], lalu membayar sum(l..r). Coba semua k; biaya sum dihitung O(1) dari prefix sum. Subproblem independen dan total berat tidak bergantung urutan internalnya, sehingga mengganti dua subsolusi dengan optimum mempertahankan kelayakan. Induksi panjang membuktikan hasil. O(N^3) waktu, O(N^2) memori. Greedy dua bobot terkecil global ilegal bila tidak bersebelahan; bahkan pilihan pasangan tetangga termurah memerlukan bukti tersendiri dan tidak dipakai.',
 [lines(3,[10,20,30]),lines(1,[999]),lines(3,[0,0,0]),lines(4,[40,30,30,50]),lines(2,[10**9,10**9]),lines(5,[1,100,1,100,1]),lines(5,[5]*5),lines(180,[10**9]*180)]+[lines(8,[R.randint(0,30) for _ in range(8)]) for _ in range(8)],merge),
 exercise('Potongan Sandi Palindrom','Menantang','Sandi festival adalah string huruf kecil. Potong di antara karakter sehingga setiap bagian tidak kosong dan merupakan palindrom (sama saat dibaca terbalik). Cari jumlah garis potong minimum, bukan jumlah bagian. String yang sudah palindrom membutuhkan nol potongan.',
 'Satu string S tanpa spasi.', 'Jumlah garis potong minimum.', '1 <= |S| <= 1200; karakter a..z.',
 'Bangun tabel palindrom interval, lalu DP prefix minimum banyak bagian. Garis potong = bagian - 1.',
 '''string s;cin>>s;int n=(int)s.size();vector<vector<char>>pal(n,vector<char>(n));
for(int len=1;len<=n;len++)for(int l=0;l+len<=n;l++){int r=l+len-1;pal[l][r]=(s[l]==s[r]&&(len<=2||pal[l+1][r-1]));}
vector<int>dp(n+1,n+1);dp[0]=0;for(int r=1;r<=n;r++)for(int l=0;l<r;l++)if(pal[l][r-1])dp[r]=min(dp[r],dp[l]+1);
cout<<dp[n]-1<<'\\n';''',
 'pal[l][r] benar bila dua ujung sama dan bagian dalam palindrom, dengan panjang <=2 sebagai basis. Induksi panjang membuktikan tabel ini. dp[r]=minimum banyak bagian untuk prefix r karakter, dp[0]=0. Setiap partisi punya bagian terakhir S[l..r-1] yang palindrom; memilih seluruh l dan meminimalkan dp[l]+1 mencakup semua partisi. Induksi r membuktikan optimum. Jawaban dp[n]-1 karena antar k bagian terdapat k-1 garis. O(n^2) waktu dan memori; berbeda dari matrix chain, transisi tabel palindrom O(1) per interval.',
 [lines('aab'),lines('racecar'),lines('abc'),lines('a'),lines('abbae'),lines('abacdc'),lines('ababbbabbababa'),lines('a'*1200)]+[lines(''.join(R.choice('abc') for _ in range(15))) for _ in range(8)],palindrome_iter)]
t151=[task('Papan yang Dipotong','Papan panjang L harus dipotong di N posisi berbeda. Satu potong membayar panjang potongan papan yang sedang dipotong. Pilih urutan pemotongan dengan biaya total minimum.','L N, kemudian N posisi berbeda menaik (baris kosong jika N=0).','Biaya minimum.','1 <= L <= 10^9; 0 <= N <= 150; 0 < posisi < L.',[(lines([10,2],[4,7]),lines(16)),(lines([10,0],[]),lines(0))]),task('Sisipan Cermin','Pada string S, satu operasi menyisipkan satu huruf di posisi mana pun. Cari operasi minimum supaya seluruh string menjadi palindrom.','S.','Banyak sisipan minimum.','1 <= |S| <= 1000; huruf kecil.',[(lines('ab'),lines(1)),(lines('aba'),lines(0))]),task('Bagian Palindrom Tepat K','Hitung cara memberi K-1 garis potong pada string S sehingga tepat K bagian tidak kosong semuanya palindrom, modulo 1 000 000 007. Dua cara berbeda bila posisi garis potong berbeda.','String S dan bilangan K dipisah spasi.','Jumlah cara.','1 <= |S| <= 250; 1 <= K <= |S|.',[(lines('aaa 2'),lines(2)),(lines('abc 2'),lines(0))])]
day(151,'Range DP - Matrix Chain dan Palindrome Partition','_PPT-09-DP/Day-151 - Range DP.txt'.replace('.txt','.pptx'),
'''Range DP memakai interval [l,r] sebagai state. Jumlah interval O(N²); biaya per state menentukan apakah total O(N²) atau O(N³). Matrix chain dan penggabungan karung mencoba split O(N), sedangkan pengenalan palindrom membaca satu interval bagian dalam.

Pola split: D[l][r]=min_(l<=k<r)(D[l][k]+D[k+1][r]+biaya(l,k,r)), dengan D[i][i]=0 bila satu elemen tidak membutuhkan operasi. Isi panjang 2,3,...,N agar kedua anak lebih pendek. Alternatif urutan l menurun dan r menaik juga dapat benar jika dependensi tersedia; panjang adalah pola yang paling mudah dibuktikan, bukan satu-satunya urutan legal.

Trace dimensi [10,30,5,60]: biaya A1A2=1500, A2A3=9000. Split setelah A1: 0+9000+10×30×60=27000. Split setelah A2: 1500+0+10×5×60=4500. Nilai hasil matriks sama, biaya evaluasi berbeda. Untuk karung [10,20,30], gabung kiri dulu membayar 30+60=90, kanan dulu 50+60=110.

Bukti dengan operasi terakhir: sebelum operasi terakhir ada dua kelompok bersebelahan. Setiap solusi pasti memiliki satu split terakhir, dan seluruh split diperiksa. Jika anak tidak optimal, gantikan dengan anak lebih murah tanpa mengubah keadaan yang dilihat induknya. Ini alasan ukuran matriks atau total berat cukup mewakili hasil internal.

Palindrom memakai P[l][r]=(S[l]==S[r]) AND (panjang<=2 OR P[l+1][r-1]). Setelah itu F[r]=minimum bagian pada r karakter pertama; F[0]=0 dan F[r]=min(F[l]+1) untuk P[l][r-1]. Untuk `aab`, F=[0,1,1,2], maka satu garis potong `aa|b`. Garis potong dan bagian jangan tertukar.

O(N³) bukan izin otomatis N=500 dalam batas berapa pun. Batas latihan 180 memberi sekitar sejuta split aktual dan memungkinkan fokus desain. Prefix sum membuat biaya interval O(1). Perkalian dimensi harus dilakukan dalam long long sejak operand pertama; jawaban maksimum dinyatakan dan diperiksa.

Pitfall: membaca interval yang belum diisi; indeks dimensi salah satu; lupa diagonal; menambahkan berat interval berkali-kali; greedy tanpa menghormati posisi; menganggap semua range DP dapat dirolling; menganggap semua recurrence bisa dioptimasi Knuth tanpa memeriksa syaratnya. Materi ini belum membutuhkan optimasi tersebut.''',e151,t151)

# Day 152: tuple-path oracles independently enforce exact deterministic tie rules.
def frog_path(s):
    t=list(map(int,s.split()));n=t[0];h=t[1:]
    @lru_cache(None)
    def f(i):
        if i==n-1:return (0,(i+1,))
        return min((abs(h[i]-h[j])+f(j)[0],(i+1,)+f(j)[1]) for j in range(i+1,min(n,i+3)))
    cost,path=f(0);return lines(cost,len(path),path)
def coin_path(s):
    t=list(map(int,s.split()));n,x=t[:2];cs=sorted(t[2:]);best=[None]*(x+1);best[0]=()
    for s2 in range(1,x+1):
        cand=[best[s2-c]+(c,) for c in cs if c<=s2 and best[s2-c] is not None]
        if cand:best[s2]=min(cand,key=lambda z:(len(z),z))
    return lines(-1) if best[x] is None else lines(len(best[x]),best[x] if best[x] else 'EMPTY')
def subset_path(s):
    t=list(map(int,s.split()));n,W=t[:2];items=[t[2+2*i:4+2*i] for i in range(n)]
    # Enumerate every bitmask (small test instances) to avoid trusting suffix reconstruction.
    best=None
    for mask in range(1<<n):
        weight=sum(items[i][0] for i in range(n) if mask>>i&1)
        if weight==W:
            cost=sum(items[i][1] for i in range(n) if mask>>i&1)
            bits=''.join(str(mask>>i&1) for i in range(n))
            best=min(best,(cost,bits)) if best is not None else (cost,bits)
    return lines(-1) if best is None else lines(*best)
e152=[exercise('Rute Foto Pematang','Mudah','Fotografer melewati N pos dari 1 ke N. Dari i boleh maju ke i+1 atau i+2; energi perpindahan adalah selisih mutlak tinggi. Cetak energi minimum dan daftar indeks pos yang dikunjungi. Bila ada banyak jalur optimal, pilih daftar indeks yang terkecil secara leksikografis: pada perbedaan pertama, indeks yang lebih kecil menang.',
 'N, lalu N tinggi.', 'Baris 1 energi minimum. Baris 2 jumlah pos L. Baris 3 L indeks pos, termasuk 1 dan N. Untuk N=1, daftar hanya 1.',
 '1 <= N <= 300; 0 <= H[i] <= 10^9.',
 'Hitung biaya suffix, lalu pilih indeks berikutnya terkecil yang masih memungkinkan optimum.',
 '''int n;cin>>n;vector<long long>h(n),dp(n);for(auto &x:h)cin>>x;
for(int i=n-2;i>=0;i--){dp[i]=numeric_limits<long long>::max()/4;for(int j=i+1;j<n&&j<=i+2;j++)dp[i]=min(dp[i],llabs(h[i]-h[j])+dp[j]);}
vector<int>path{1};for(int i=0;i<n-1;){for(int j=i+1;j<n&&j<=i+2;j++)if(dp[i]==llabs(h[i]-h[j])+dp[j]){i=j;path.push_back(i+1);break;}}
cout<<dp[0]<<'\\n'<<path.size()<<'\\n';for(int i=0;i<(int)path.size();i++)cout<<(i?" ":"")<<path[i];cout<<'\\n';''',
 'dp[i]=biaya suffix optimal dari i ke tujuan. Isi i menurun. Rekonstruksi mulai 1, mencoba j=i+1 lalu i+2; pilih pertama yang memenuhi dp[i]=|h[i]-h[j]|+dp[j]. Persamaan memastikan prefix pilihan masih dapat dilengkapi menjadi optimum. Di antara seluruh suffix optimal, perbedaan indeks pertama menentukan leksikografi, sehingga pilihan feasible terkecil di setiap langkah membuktikan tie-break global. Posisi selalu bertambah, maka berhenti di N. O(N) waktu dan memori. Tidak perlu membalik path karena dibangun dari awal.',
 [lines(4,[10,30,20,40]),lines(1,[8]),lines(3,[5,5,5]),lines(2,[0,10**9]),lines(5,[0,2,4,6,8]),lines(5,[0,100,0,100,0]),lines(7,[7,6,5,4,3,2,1]),lines(300,[0]*300)]+[lines(10,[R.randrange(20) for _ in range(10)]) for _ in range(8)],frog_path),
 exercise('Daftar Keping Terkecil','Sedang','Tersedia N nilai keping berbeda tanpa batas. Bentuk nominal tepat X dengan jumlah keping minimum. Di antara seluruh urutan keping yang minimum, cetak urutan nilai terkecil secara leksikografis (bandingkan nilai bilangan pada posisi pertama yang berbeda). Urutan merupakan bagian keluaran, sehingga kamu boleh menyusun keping dengan bebas.',
 'N X, lalu N nilai keping berbeda.', 'Jika mustahil, cetak -1 saja. Jika mungkin: baris pertama jumlah keping K, baris kedua urutan K nilai. Jika K=0, baris kedua teks EMPTY.',
 '1 <= N <= 50; 0 <= X <= 3000; 1 <= nilai keping <= 3000.',
 'Urutkan denominasi. Pilih nilai terkecil c dengan dp[s]=1+dp[s-c].',
 '''int n,x;cin>>n>>x;vector<int>c(n);for(auto &v:c)cin>>v;sort(c.begin(),c.end());const int INF=1000000000;vector<int>dp(x+1,INF);dp[0]=0;
for(int s=1;s<=x;s++)for(int v:c)if(v<=s&&dp[s-v]!=INF)dp[s]=min(dp[s],dp[s-v]+1);
if(dp[x]==INF){cout<<-1<<'\\n';return 0;}cout<<dp[x]<<'\\n';if(x==0){cout<<"EMPTY\\n";return 0;}
bool first=true;while(x>0){for(int v:c)if(v<=x&&dp[x]==dp[x-v]+1){if(!first)cout<<' ';cout<<v;first=false;x-=v;break;}}cout<<'\\n';''',
 'dp[s] menyimpan minimum keping untuk s. Saat menelusuri s, nilai c layak bila dp[s]=1+dp[s-c]; ini menjamin ada penyelesaian optimum setelah c. Coba denominasi menaik dan ambil yang pertama. Bila urutan optimum lain berbeda pertama kali pada posisi ini, nilainya tidak mungkin lebih kecil dari pilihan feasible pertama. Induksi s membuktikan urutan leksikografis terkecil. Jumlah langkah menurun satu per pilihan dan s turun karena c>0. O(NX) waktu termasuk rekonstruksi paling banyak X langkah, O(X+N) memori. Aturan lokal parent saat menghitung minimum saja belum tentu menjamin leksikografi seluruh jalur.',
 [lines([3,6],[4,3,2]),lines([2,7],[4,6]),lines([2,0],[3,9]),lines([1,9],[3]),lines([4,8],[7,1,4,2]),lines([3,12],[5,4,3]),lines([2,1],[2,3]),lines([1,3000],[1])]+[lines([4,30],R.sample(range(1,15),4)) for _ in range(8)],coin_path),
 exercise('Kurasi Paket Tepat Berat','Menantang','Ada N benda berurutan, masing-masing berat w[i] dan biaya c[i]. Setiap benda boleh dipilih paling banyak sekali. Pilih total berat tepat W dengan biaya minimum. Cetak string keputusan panjang N: 1 dipilih, 0 dilewati. Bila biaya minimum seri, pilih string leksikografis terkecil dengan 0 lebih kecil daripada 1.',
 'N W, lalu N baris w[i] c[i].', 'Jika mustahil, -1 saja. Jika mungkin: baris 1 biaya minimum, baris 2 string keputusan panjang N.',
 '1 <= N <= 200; 0 <= W <= 3000; 1 <= w[i] <= 3000; 0 <= c[i] <= 10^9.',
 'Suffix dp[i][s] memungkinkan memutuskan dari indeks pertama. Jika skip tetap optimal, pilih 0.',
 '''int n,W;cin>>n>>W;vector<int>w(n);vector<long long>c(n);for(int i=0;i<n;i++)cin>>w[i]>>c[i];const long long INF=numeric_limits<long long>::max()/4;
vector<vector<long long>>dp(n+1,vector<long long>(W+1,INF));dp[n][0]=0;
for(int i=n-1;i>=0;i--)for(int s=0;s<=W;s++){dp[i][s]=dp[i+1][s];if(s>=w[i]&&dp[i+1][s-w[i]]!=INF)dp[i][s]=min(dp[i][s],c[i]+dp[i+1][s-w[i]]);}
if(dp[0][W]==INF){cout<<-1<<'\\n';return 0;}cout<<dp[0][W]<<'\\n';int s=W;
for(int i=0;i<n;i++)if(dp[i][s]==dp[i+1][s])cout<<'0';else{cout<<'1';s-=w[i];}cout<<'\\n';''',
 'dp[i][s]=biaya minimum mencapai berat tepat s menggunakan benda i..N-1. Basis dp[N][0]=0; yang lain INF. Transisi skip dp[i+1][s], atau take c_i+dp[i+1][s-w_i] jika reachable. Induksi i menurun membuktikan minimum dan aturan 0/1. Rekonstruksi dari i=0 memilih 0 bila skip menyamai optimum, selain itu 1. Karena bit yang lebih awal mendominasi leksikografi dan hanya kelanjutan optimal dipilih, string akhir terkecil di antara semua optimum. O(NW) waktu/memori; penelusuran O(N). Tie-break ini berbeda dari daftar indeks terkecil, maka format keputusan dinyatakan jelas.',
 [lines([3,3],[1,2],[2,3],[3,5]),lines([2,0],[1,0],[2,0]),lines([1,3],[2,5]),lines([3,2],[1,1],[1,1],[2,2]),lines([3,3],[1,0],[2,0],[3,0]),lines([1,1],[1,10**9]),lines([4,4],[2,3],[2,3],[2,3],[2,3]),lines([16,16],*([[1,10**9]]*16))]+[lines([10,15],*[[R.randint(1,7),R.randint(0,20)] for _ in range(10)]) for _ in range(8)],subset_path)]
# Add maximum-size case with closed-form expected output, outside exponential oracle.
e152[2]['cases'].append((lines([200,3000],*([[15,10**9]]*200)),lines(200*10**9,'1'*200)))
t152=[task('Rute Grid dengan D Lebih Dahulu','Grid N×M memiliki biaya sel nonnegatif. Jalan dari kiri atas ke kanan bawah hanya D (bawah) atau R (kanan), membayar semua sel termasuk awal/akhir. Cetak biaya minimum dan string gerakan terkecil secara leksikografis dengan D<R. Grid 1×1 mencetak EMPTY sebagai gerakan.','N M, lalu N baris M biaya.','Biaya minimum, lalu string gerakan pada baris kedua.','1 <= N,M <= 100; 0 <= biaya <= 10^9.',[(lines([2,2],[1,1],[1,1]),lines(3,'DR')),(lines([1,1],[7]),lines(7,'EMPTY'))]),task('Potongan Palindrom Terawal','Partisikan string S menjadi jumlah bagian palindrom minimum. Cetak banyak bagian lalu daftar posisi akhir setiap bagian (indeks 1-based, termasuk |S|). Pilih daftar posisi akhir yang leksikografis terkecil.','S.','Banyak bagian, lalu daftar akhir di baris kedua.','1 <= |S| <= 500; huruf kecil.',[(lines('aab'),lines(2,[2,3])),(lines('abab'),lines(2,[1,4]))]),task('LIS dengan Indeks Terkecil','Cari subsequence meningkat ketat terpanjang dari array A. Cetak panjang dan daftar indeks terpilih yang leksikografis terkecil di antara semua LIS. Indeks mulai 1.','N, lalu N bilangan A.','Panjang, lalu daftar indeks pada baris kedua.','1 <= N <= 500; -10^9 <= A[i] <= 10^9.',[(lines(4,[2,1,3,4]),lines(3,[1,3,4])),(lines(3,[7,7,7]),lines(1,[1]))])]
day(152,'Rekonstruksi Jalur dan Penelusuran Jawaban DP','_PPT-09-DP/Day-152 - Rekonstruksi Jalur DP.pptx',
'''Nilai optimum belum menyebut keputusan yang menghasilkan nilai tersebut. Rekonstruksi memerlukan informasi kelanjutan: tabel nilai lengkap, parent yang konsisten, keputusan tersimpan, atau perhitungan ulang. Pilih desain sejak membaca format output.

Dua pola dasar: saat dp berubah, simpan parent state dan keputusan; atau setelah tabel selesai, cari transisi yang memenuhi persamaan optimalitas. Parent cocok bila dependensi tidak berubah versi. Pada 0/1 knapsack satu dimensi, parent kapasitas yang kemudian tertimpa bisa merujuk versi barang berbeda dan menyebabkan barang terulang. Gunakan tabel per indeks atau keputusan yang mempertahankan versi.

Untuk keluaran deterministik, tiga latihan menentukan tie-break secara eksplisit. Leksikografis membandingkan elemen pertama yang berbeda, bukan jumlah elemen, jumlah indeks, atau pilihan terakhir. Pada tinggi [5,5,5], semua jalur berenergi nol; [1,2,3] lebih kecil daripada [1,3]. Karena itu jangan otomatis memilih langkah lebih panjang demi lebih sedikit pos.

Teknik suffix: simpan biaya optimal dari state saat ini ke akhir. Pilih keputusan terkecil yang masih memenuhi nilai optimum, kemudian lanjut. Syarat `biaya_keputusan + nilai_suffix == nilai_sekarang` adalah sertifikat bahwa pilihan dapat diselesaikan secara optimal. Induksi atas posisi pertama yang berbeda membuktikan leksikografi global.

Pada keping {4,3,2}, nominal 6, dp[6]=2. Coba 2: dp[4]+1=2, maka mulai 2 dan hasil [2,4] lebih kecil dari [3,3] serta [4,2]. Untuk benda (berat,biaya) [(1,2),(2,3),(3,5)], W=3: dua solusi biaya 5 ialah 110 dan 001; aturan 0<1 memilih 001. Memilih indeks barang paling kecil justru memberi aturan lain.

Setiap langkah rekonstruksi harus mengurangi suatu ukuran: sisa nominal, sisa posisi, atau jarak ke tujuan. Ini membuktikan terminasi. Setelah selesai cek jumlah biaya/berat, semua indeks legal, larangan stok, panjang output, dan optimalitas. Membalik jawaban diperlukan hanya jika dibangun dari akhir.

Rolling array biasa membuang riwayat untuk penelusuran tabel. Ini keterbatasan metode langsung, bukan larangan matematis: parent khusus, checkpoint, perhitungan ulang, atau algoritma rekonstruksi hemat memori dapat dipakai pada masalah tertentu. Pada latihan ini pilih tabel suffix agar bukti serta tie-break mudah ditinjau.

Pitfall: parent hanya diperbarui nilainya; tie pada langkah terakhir disamakan dengan leksikografi seluruh jalur; output kosong tanpa aturan; menelusuri unreachable; mencetak indeks 0-based; memakai parent 0/1 yang kehilangan versi.''',e152,t152)

# Day 153.
def gridcost(s):
    t=list(map(int,s.split()));n,m=t[:2];a=[t[2+i*m:2+(i+1)*m] for i in range(n)];d=[[0]*m for _ in range(n)]
    for i in range(n):
        for j in range(m):d[i][j]=a[i][j]+(0 if i==j==0 else min(d[i-1][j] if i else 10**30,d[i][j-1] if j else 10**30))
    return d[-1][-1]
def edit(s):
    a,b=s.split();a='' if a=='-' else a;b='' if b=='-' else b
    # Full-table oracle intentionally differs from rolling C++.
    d=[list(range(len(b)+1))]+[[i]+[0]*len(b) for i in range(1,len(a)+1)]
    for i in range(1,len(a)+1):
        for j in range(1,len(b)+1):d[i][j]=min(d[i-1][j]+1,d[i][j-1]+1,d[i-1][j-1]+(a[i-1]!=b[j-1]))
    return d[-1][-1]
def exact_value(s):
    t=list(map(int,s.split()));n,W=t[:2];a=[t[2+2*i:4+2*i] for i in range(n)];best=None
    for mask in range(1<<n):
        if sum(a[i][0] for i in range(n) if mask>>i&1)==W:
            v=sum(a[i][1] for i in range(n) if mask>>i&1);best=max(best,v) if best is not None else v
    return best if best is not None else -1
e153=[exercise('Arus Logistik Berkas Besar','Mudah','Biaya melewati sel pada peta N×M dibaca baris demi baris. Mulai di kiri atas dan bergerak hanya kanan atau bawah ke kanan bawah. Biaya jalur adalah jumlah semua sel yang dilalui termasuk awal dan akhir. Cari biaya minimum dengan menyimpan paling banyak satu baris DP; jalur tidak perlu dicetak.',
 'N M, kemudian N baris masing-masing M biaya.', 'Biaya jalur minimum.',
 '1 <= N,M <= 2000; 0 <= biaya <= 10^9. Batas memori algoritma O(M); jangan menyimpan seluruh grid.',
 'Saat kolom j diproses, dp[j] masih nilai atas, dp[j-1] sudah nilai kiri.',
 '''int n,m;cin>>n>>m;const long long INF=numeric_limits<long long>::max()/4;vector<long long>dp(m,INF);
for(int i=0;i<n;i++)for(int j=0;j<m;j++){long long x;cin>>x;
 if(i==0&&j==0)dp[j]=x;else dp[j]=x+min(dp[j],j?dp[j-1]:INF);
}cout<<dp[m-1]<<'\\n';''',
 'Sebelum sel (i,j), dp[j] menyimpan biaya optimum sel atas (i-1,j), sedangkan dp[j-1] menyimpan biaya optimum kiri (i,j-1) karena kolom diproses menaik. Setiap jalur masuk dari atas atau kiri, sehingga g[i][j]+min(keduanya) benar. Awal diinisialisasi g[0][0]; tetangga luar bernilai INF. Induksi urutan baris-kolom membuktikan invariant satu baris. O(NM) waktu, O(M) memori termasuk input yang langsung diproses. Menyimpan grid penuh akan menghilangkan tujuan optimasi.',
 [lines([2,3],[1,7,1],[2,1,1]),lines([1,1],[10**9]),lines([1,4],[1,2,3,4]),lines([4,1],[1],[2],[3],[4]),lines([2,2],[0,0],[0,0]),lines([3,3],[1,99,1],[1,99,1],[1,1,1]),lines([2,2],[10**9,10**9],[10**9,10**9]),lines([30,40],*([[1]*40]*30))]+[lines([8,9],*[[R.randrange(100) for _ in range(9)] for _ in range(8)]) for _ in range(8)],gridcost),
 exercise('Menyunting Nama Arsip','Sedang','Ubah string A menjadi B menggunakan penyisipan, penghapusan, atau penggantian satu karakter. Setiap operasi berbiaya 1; karakter sama dapat dipertahankan tanpa biaya. Cari biaya minimum. Tanda - pada input mewakili string kosong, dan bukan karakter alfabet.',
 'Dua token A B. Setiap token huruf kecil, atau - untuk kosong.', 'Jumlah operasi minimum.',
 '0 <= |A|,|B| <= 4000; karakter a..z. Gunakan O(min(|A|,|B|)) memori DP.',
 'Baris sekarang membutuhkan atas, kiri, dan diagonal lama. Dua baris lebih mudah dibuktikan daripada menimpa diagonal.',
 '''string a,b;cin>>a>>b;if(a=="-")a.clear();if(b=="-")b.clear();if(b.size()>a.size())swap(a,b);
int n=(int)a.size(),m=(int)b.size();vector<int>prev(m+1),cur(m+1);iota(prev.begin(),prev.end(),0);
for(int i=1;i<=n;i++){cur[0]=i;for(int j=1;j<=m;j++)cur[j]=min({prev[j]+1,cur[j-1]+1,prev[j-1]+(a[i-1]!=b[j-1])});prev.swap(cur);}
cout<<prev[m]<<'\\n';''',
 'D[i][j]=minimum edit prefix A sepanjang i menjadi prefix B sepanjang j. Basis D[0][j]=j dan D[i][0]=i. Operasi terakhir menghapus (atas+1), menyisipkan (kiri+1), atau menyelaraskan karakter terakhir (diagonal+beda). Semua alignment memiliki salah satu langkah tersebut, dan masing-masing menghasilkan transformasi legal; induksi i+j membuktikan optimum. Simpan prev dan cur; cur[0] ditulis ulang dan setiap cur[j] ditimpa, jadi tidak perlu fill nol. Simetri biaya edit memungkinkan string lebih pendek menjadi kolom. O(|A||B|) waktu, O(min(|A|,|B|)) memori DP; input string O(|A|+|B|).',
 [lines('kitten sitting'),lines('- abc'),lines('- -'),lines('abc abc'),lines('abc -'),lines('abc cba'),lines('aaaa bbbb'),lines('a'*100+' '+'b'*100)]+[lines(''.join(R.choice('abc') for _ in range(15))+' '+''.join(R.choice('abc') for _ in range(18))) for _ in range(8)],edit),
 exercise('Manifest Kapasitas Penuh','Menantang','Kontainer harus berisi berat tepat W dari N barang. Barang i berbobot w[i] dan bernilai v[i], masing-masing boleh dipakai paling banyak sekali. Maksimalkan total nilai, atau laporkan mustahil. Tidak perlu mencetak barang; gunakan satu array DP kapasitas.',
 'N W, kemudian N baris w[i] v[i].', 'Nilai maksimum, atau -1 bila berat tepat W mustahil.',
 '1 <= N <= 500; 0 <= W <= 30 000; 1 <= w[i] <= 30 000; 0 <= v[i] <= 10^9. Memori DP O(W).',
 'Loop kapasitas menurun menjaga baris lama. Hanya berat nol yang reachable sebelum barang pertama.',
 '''int n,W;cin>>n>>W;const long long NEG=-1;vector<long long>dp(W+1,NEG);dp[0]=0;
for(int i=0;i<n;i++){int w;long long v;cin>>w>>v;for(int s=W;s>=w;s--)if(dp[s-w]!=NEG)dp[s]=max(dp[s],dp[s-w]+v);}
cout<<dp[W]<<'\\n';''',
 'Setelah i barang, dp[s] ialah nilai maksimum mencapai berat tepat s. Basis dp[0]=0, state lain -1 aman karena semua nilai sah nonnegatif. Kapasitas menurun memastikan dp[s-w_i] masih berasal dari sebelum barang i, sehingga tidak mengambil barang berulang. Pilihan skip/take mencakup semua subset legal dan induksi barang membuktikan maksimum. O(NW) waktu, O(W) memori termasuk input yang diproses langsung. Untuk nilai barang negatif, sentinel -1 tidak boleh digunakan tanpa penanda terpisah atau NEG yang memadai.',
 [lines([2,5],[2,3],[3,4]),lines([1,4],[2,3]),lines([1,0],[1,99]),lines([2,4],[2,3],[2,3]),lines([1,1],[1,0]),lines([3,3],[1,10**9],[1,10**9],[1,10**9]),lines([2,1],[2,10],[3,20]),lines([16,16],*([[1,1]]*16))]+[lines([10,20],*[[R.randint(1,8),R.randint(0,20)] for _ in range(10)]) for _ in range(8)],exact_value)]
e153[0]['cases'].append((lines([2000,2000],*([' '.join(['1']*2000)]*2000)),lines(3999)))
e153[1]['cases'].append((lines('a'*4000+' '+'b'*4000),lines(4000)))
e153[2]['cases'].append((lines([500,30000],*([[60,10**9]]*500)),lines(500*10**9)))
t153=[task('Festival Tanpa Stan Bertetangga','Pilih beberapa stan dari deret N stan, tanpa dua stan bersebelahan, untuk memaksimalkan jumlah nilai. Nilai bisa negatif dan memilih kosong sah. Proses dalam O(1) memori tambahan, input dibaca berurutan.','N, lalu N nilai.','Nilai maksimum.','1 <= N <= 200 000; -10^9 <= nilai <= 10^9.',[(lines(4,[2,7,9,3]),lines(11)),(lines(3,[-1,-2,-3]),lines(0))]),task('Panjang Kemiripan Dua Arsip','Cari panjang longest common subsequence dua string A dan B, memakai dua baris DP. Tanda - mewakili string kosong. Subsequence boleh melewati karakter tetapi urutannya tetap.','Dua token A B.','Panjang LCS.','0 <= |A|,|B| <= 3000; huruf kecil.',[(lines('abc ac'),lines(2)),(lines('- abc'),lines(0))]),task('Jalur Festival Bergelombang','Grid . dan # dilalui dari kiri atas ke kanan bawah hanya kanan/bawah. Hitung jalur modulo 1 000 000 007 memakai satu baris DP; blocked harus menghapus nilai lama.','N M, lalu N string panjang M.','Jumlah jalur.','1 <= N,M <= 1000.',[(lines([2,3],'...','.#.'),lines(1)),(lines([1,1],'#'),lines(0))])]
day(153,'Optimasi Memori DP - Rolling Array','_PPT-09-DP/Day-153 - Optimasi Memori DP.pptx',
'''Optimasi memori mempertahankan hanya nilai yang akan dibaca lagi. Mulai dengan recurrence dua dimensi yang benar, gambarkan dependensi, lalu buktikan kapan sel lama boleh ditimpa. Menghapus dimensi tanpa invariant dapat mengubah soal.

Grid satu baris: sebelum kolom j, dp[j]=atas lama dan dp[j-1]=kiri baru. Contoh biaya [[1,7,1],[2,1,1]]: setelah baris pertama [1,8,9]; baris kedua memperbarui menjadi [3,4,5]. Membalik kolom membuat kiri belum berisi baris sekarang. Input dapat dibaca sambil dihitung sehingga tidak menyimpan grid.

0/1 knapsack: dp_i[s]=max(dp_(i-1)[s],dp_(i-1)[s-w]+v). Loop s menurun memastikan s-w belum ditimpa. Satu barang (2,3), W=4 yang wajib penuh seharusnya mustahil; loop maju menghasilkan 6 dengan memakai barang dua kali. Unbounded membaca dp_i[s-w], sehingga justru butuh s menaik.

Edit distance membaca atas lama, diagonal lama, dan kiri baru. Dua baris `prev`/`cur` memberi ketiganya. Basis cur[0]=i harus ditulis setiap baris. Semua sel cur lain ditimpa sekali, sehingga tidak perlu reset tambahan. Bila transisi memakai += pada baris baru, reset mungkin wajib. Satu baris edit distance juga bisa dengan variabel diagonal lama, tetapi dua baris memudahkan latihan invariant.

Perkiraan memori dihitung dengan jumlah sel × sizeof(tipe), ditambah input, kontainer, stack, dan overhead. Pada platform umum long long berukuran 8 byte; gunakan sizeof untuk pengukuran portabel. Grid 2000×2000 long long sekitar 32 MB desimal, satu baris sekitar 16 KB. DP knapsack 501×30001 long long sekitar 120 MB, satu baris sekitar 240 KB. Edit dua baris 4001 int sekitar 32 KB pada int 4 byte.

Rekonstruksi langsung dari tabel penuh tidak tersedia setelah rolling membuang riwayat. Namun rekonstruksi hemat memori tetap mungkin pada masalah tertentu melalui parent yang mempertahankan versi, checkpoint, hitung ulang, atau teknik khusus. Klaim absolut bahwa rekonstruksi selalu melarang penghematan memori terlalu kuat. Untuk hari ini, keluaran hanya nilai.

Jumlah buffer ditentukan jadwal baca-tulis. DP yang melihat i-1 dan i-2 bisa memakai dua nilai lama ditambah nilai hasil sementara; aturan 'selalu jangkauan+1 array' bukan keharusan. Range DP umum membaca banyak interval lama sehingga pola rolling sederhana tidak langsung cocok.

Pitfall: memadatkan DP tetapi tetap menyimpan input grid besar; update alias; lupa basis kolom nol; memakai nol untuk unreachable pada target tepat; lupa diagonal; mengecilkan tipe sampai overflow. Tuliskan invariant sebelum dan sesudah satu iterasi sebagai bukti bahwa pemadatan tidak mengubah nilai.''',e153,t153)

# Day 154: review problems combine patterns; independent brute-force oracles.
def no_adj_budget(s):
    t=list(map(int,s.split()));n,W=t[:2];a=[t[2+2*i:4+2*i] for i in range(n)];best=0
    for mask in range(1<<n):
        if mask&(mask<<1):continue
        if sum(a[i][0] for i in range(n) if mask>>i&1)<=W:best=max(best,sum(a[i][1] for i in range(n) if mask>>i&1))
    return best
def weighted_lis(s):
    t=list(map(int,s.split()));n=t[0];a=[t[1+2*i:3+2*i] for i in range(n)];best=None
    for mask in range(1,1<<n):
        ids=[i for i in range(n) if mask>>i&1]
        if all(a[x][0]<a[y][0] for x,y in zip(ids,ids[1:])):
            val=sum(a[i][1] for i in ids);best=max(best,val) if best is not None else val
    return best
def grid_best_count(s):
    ls=s.splitlines();n,m=map(int,ls[0].split());a=[row.split() for row in ls[1:]]
    # Enumerate every monotone route; no DP cache for the small random reference.
    best=None;cnt=0
    def walk(i,j,score):
        nonlocal best,cnt
        if i>=n or j>=m or a[i][j]=='#':return
        score+=int(a[i][j])
        if i==n-1 and j==m-1:
            if best is None or score>best:best=score;cnt=1
            elif score==best:cnt+=1
        else:walk(i+1,j,score);walk(i,j+1,score)
    walk(0,0,0)
    return lines('IMPOSSIBLE') if best is None else lines([best,cnt%MOD])
e154=[exercise('Agenda Stan dan Anggaran','Mudah','N stan festival berjajar. Mengunjungi stan i memakai biaya w[i] dan memberi kepuasan v[i]. Pilih subset stan dengan biaya total paling banyak W, tanpa memilih dua stan yang bersebelahan. Boleh tidak memilih apa pun. Cari kepuasan maksimum.',
 'N W, lalu N baris w[i] v[i].', 'Kepuasan maksimum.',
 '1 <= N <= 200; 0 <= W <= 5000; 1 <= w[i] <= 5000; 0 <= v[i] <= 10^9.',
 'Gabungkan house robber dan knapsack. Jika mengambil i, prefix terakhir yang boleh dipakai berhenti di i-2.',
 '''int n,W;cin>>n>>W;vector<long long>older(W+1),prev(W+1),cur(W+1);
for(int i=0;i<n;i++){int w;long long v;cin>>w>>v;for(int s=0;s<=W;s++){cur[s]=prev[s];if(s>=w)cur[s]=max(cur[s],older[s-w]+v);}older.swap(prev);prev.swap(cur);}
cout<<prev[W]<<'\\n';''',
 'D[i][s]=kepuasan maksimum pada i stan pertama, biaya paling banyak s. Skip stan i memberi D[i-1][s]. Take i memberi v_i+D[i-2][s-w_i] agar tetangganya tidak diambil. Basis prefix kosong dan virtual sebelum awal bernilai nol. Setiap subset legal skip atau take; dalam kasus take, sisa subset persis berada pada prefix i-2. Induksi i membuktikan optimum. Tiga buffer menyimpan i-2, i-1, hasil i; swap dilakukan setelah seluruh kapasitas selesai. O(NW) waktu, O(W) memori. Memakai i-1 pada take menghilangkan syarat tidak bersebelahan.',
 [lines([3,4],[2,5],[2,100],[2,5]),lines([1,0],[1,9]),lines([3,4],[2,6],[2,7],[2,6]),lines([2,2],[1,10],[1,10]),lines([3,1],[2,99],[3,99],[4,99]),lines([4,4],[1,0],[1,0],[1,0],[1,0]),lines([3,3],[1,10**9],[1,10**9],[1,10**9]),lines([16,8],*([[1,1]]*16))]+[lines([10,15],*[[R.randint(1,7),R.randint(0,30)] for _ in range(10)]) for _ in range(8)],no_adj_budget),
 exercise('Rangkaian Pameran Bertumbuh','Sedang','Ada N karya dalam urutan kedatangan. Karya i memiliki tingkat a[i] dan nilai kurasi v[i] yang boleh negatif. Pilih subsequence tidak kosong dengan tingkat meningkat ketat. Maksimalkan jumlah nilai kurasi, bukan panjang subsequence. Urutan indeks harus tetap meningkat.',
 'N, kemudian N baris a[i] v[i].', 'Jumlah nilai maksimum dari subsequence meningkat ketat yang tidak kosong.',
 '1 <= N <= 2000; -10^9 <= a[i],v[i] <= 10^9.',
 'State terbaik yang berakhir tepat di i. Setiap i juga boleh memulai subsequence baru.',
 '''int n;cin>>n;vector<long long>a(n),v(n),dp(n);for(int i=0;i<n;i++)cin>>a[i]>>v[i];long long ans=numeric_limits<long long>::lowest();
for(int i=0;i<n;i++){dp[i]=v[i];for(int j=0;j<i;j++)if(a[j]<a[i])dp[i]=max(dp[i],dp[j]+v[i]);ans=max(ans,dp[i]);}
cout<<ans<<'\\n';''',
 'dp[i]=nilai maksimum subsequence meningkat ketat yang berakhir di i. Awali v_i untuk subsequence satu karya. Jika ada pendahulu j<i dengan a_j<a_i, kandidat dp[j]+v_i. Setiap subsequence nontrivial punya satu pendahulu terakhir yang dicoba; mengganti prefix dengan optimum menjaga indeks/tingkat legal. Induksi i membuktikan dp, lalu ambil max seluruh akhir. O(N^2) waktu, O(N) memori. Tails untuk LIS panjang tidak langsung menyelesaikan objektif jumlah nilai; dp terakhir juga belum tentu jawaban. Nol bukan jawaban sah bila semua nilai negatif.',
 [lines(4,[1,5],[3,100],[2,6],[4,7]),lines(1,[9,-5]),lines(3,[1,-8],[2,-3],[3,-9]),lines(3,[4,5],[4,9],[4,7]),lines(4,[4,4],[3,3],[2,2],[1,1]),lines(3,[1,10**9],[2,10**9],[3,10**9]),lines(4,[1,10],[2,-100],[3,10],[4,1]),lines(16,*[[i,1] for i in range(16)])]+[lines(10,*[[R.randint(-5,5),R.randint(-20,30)] for _ in range(10)]) for _ in range(8)],weighted_lis),
 exercise('Rute Hadiah dan Banyak Pemenang','Menantang','Peta festival N×M berisi sel tertutup # atau hadiah bilangan bulat yang boleh negatif. Dari kiri atas ke kanan bawah hanya boleh kanan atau bawah. Nilai jalur adalah jumlah hadiah semua sel yang dikunjungi termasuk awal/akhir. Cetak nilai maksimum dan jumlah jalur yang mencapai nilai maksimum. Jalur berbeda bila urutan gerak berbeda.',
 'N M, lalu N baris masing-masing M token (# atau bilangan hadiah).',
 'Jika tujuan tak terjangkau, cetak IMPOSSIBLE. Selain itu cetak nilai maksimum dan banyak jalur optimum modulo 1 000 000 007 pada satu baris.',
 '1 <= N,M <= 200; -10^9 <= hadiah <= 10^9.',
 'Setiap state menyimpan pasangan (nilai terbaik, banyak cara). Bila kandidat seri, jumlahkan cara; bila lebih baik, ganti cara.',
 '''int n,m;cin>>n>>m;const long long NEG=numeric_limits<long long>::lowest()/4,MOD=1000000007;vector<vector<long long>>best(n,vector<long long>(m,NEG)),ways(n,vector<long long>(m));
for(int i=0;i<n;i++)for(int j=0;j<m;j++){string token;cin>>token;if(token=="#")continue;long long x=stoll(token);
 if(i==0&&j==0){best[i][j]=x;ways[i][j]=1;continue;}
 for(int d=0;d<2;d++){int r=i-(d==0),c=j-(d==1);if(r<0||c<0||best[r][c]==NEG)continue;long long candidate=best[r][c]+x;
 if(candidate>best[i][j]){best[i][j]=candidate;ways[i][j]=ways[r][c];}else if(candidate==best[i][j])ways[i][j]=(ways[i][j]+ways[r][c])%MOD;
 }}if(best[n-1][m-1]==NEG)cout<<"IMPOSSIBLE\\n";else cout<<best[n-1][m-1]<<' '<<ways[n-1][m-1]<<'\\n';''',
 'best[r][c]=nilai maksimum ke sel, ways[r][c]=jumlah jalur yang meraihnya. Basis awal terbuka (hadiah_awal,1), state lain (NEG,0). Dari atas/kiri: nilai lebih besar mengganti best dan ways; seri menambah ways; lebih kecil diabaikan. Induksi r+c: semua jalur masuk dari tepat salah satu arah, kelompok atas dan kiri terpisah, sehingga counting tidak ganda. Prefix bukan maksimum tidak bisa membantu karena tambahan hadiah suffix sama untuk semua riwayat pada sel tersebut. O(NM) waktu/memori. Nilai negatif harus tetap reachable; ways modulo nol juga tidak berarti unreachable, maka cek best==NEG.',
 [lines([2,2],[1,1],[1,1]),lines([1,1],[-7]),lines([2,2],[1,'#'],['#',1]),lines([2,2],['#',0],[0,0]),lines([2,2],[0,5],[1,0]),lines([2,2],[-1,-2],[-2,-1]),lines([1,3],[10**9,10**9,10**9]),lines([5,5],*([[0]*5]*5))]+[lines([5,5],*[[R.choice(['#',-3,-1,0,2,4]) for _ in range(5)] for _ in range(5)]) for _ in range(8)],grid_best_count)]
e154[0]['cases'].append((lines([200,5000],*([[25,10**9]]*200)),lines(100*10**9)))
e154[1]['cases'].append((lines(2000,*[[i,10**9] for i in range(2000)]),lines(2000*10**9)))
import math
e154[2]['cases'].append((lines([200,200],*([[0]*200]*200)),lines([0,math.comb(398,199)%MOD])))
t154=[task('Ekspedisi Tepat K Stan','Pilih tepat K stan dari deret N, tanpa dua bersebelahan, biaya total paling banyak W, dan maksimalkan nilai. Cetak -1 bila mustahil; nilai nonnegatif.','N W K, lalu N baris biaya nilai.','Nilai maksimum atau -1.','1 <= N <= 60; 0 <= W <= 500; 0 <= K <= 30; 1 <= biaya <= 500; 0 <= nilai <= 10^9.',[(lines([3,2,2],[1,5],[1,100],[1,5]),lines(10)),(lines([2,10,2],[1,5],[1,9]),lines(-1))]),task('Cara Partisi Paling Sedikit','Potong string menjadi bagian palindrom tidak kosong. Cetak jumlah bagian minimum dan banyak cara mencapai minimum modulo 1 000 000 007. Cara berbeda bila posisi garis potong berbeda.','S.','Jumlah bagian minimum dan banyak cara pada satu baris.','1 <= |S| <= 800; huruf kecil.',[(lines('abab'),lines([2,2])),(lines('aaa'),lines([1,1]))]),task('Benda Terbaik dengan Jumlah Seri','Ada N barang berbeda masing-masing biaya w dan nilai v nonnegatif. Pilih subset biaya paling banyak W. Cetak nilai maksimum dan banyak subset berbeda yang mencapainya, modulo 1 000 000 007. Subset kosong sah, barang bernilai nol tetap dapat membedakan subset.','N W, lalu N baris w v.','Nilai maksimum dan banyak subset optimum.','1 <= N <= 100; 0 <= W <= 2000; 1 <= w <= 2000; 0 <= v <= 10^9.',[(lines([2,1],[1,5],[1,5]),lines([5,2])),(lines([1,1],[1,0]),lines([0,2]))])]
day(154,'REVIEW DP Dasar','_PPT-09-DP/Day-154 - REVIEW DP Dasar.pptx',
'''Review ini menggabungkan pola Day 141–153: state, transisi, basis, urutan, letak jawaban, serta kebutuhan memori/rekonstruksi. Ketiga latihan sengaja mengubah satu aspek dari pola yang sudah dikenal agar kamu tidak menyalin template tanpa membaca tujuan.

Latihan 1 menggabungkan kapasitas knapsack dan larangan tetangga house robber. D[i][s]=max(D[i-1][s], v_i+D[i-2][s-w_i]). Dengan tiga stan bernilai [6,7,6], biaya masing-masing 2 dan W=4, memilih stan 1/3 menghasilkan 12. Knapsack biasa dapat memilih 6+7=13 tetapi ilegal; house robber biasa tanpa kapasitas juga tidak cukup untuk model umum.

Latihan 2 mengganti panjang LIS menjadi jumlah nilai. D[i]=v_i atau D[j]+v_i untuk j<i dan a_j<a_i. Contoh (tingkat,nilai) [(1,5),(3,100),(2,6),(4,7)] menghasilkan dp=[5,105,11,112]. Tails minimum pada LIS panjang tidak menyimpan seluruh informasi nilai. State 'berakhir tepat di i' menjaga syarat tingkat terakhir; jawaban max semua i.

Latihan 3 menggabungkan optimasi dan counting. State (best,ways), dengan operator gabung: pilih best lebih besar, jumlahkan ways bila seri. Di grid 2×2 hadiah semua 1, dua jalur berbeda bernilai 3. Jika hadiah atas-kanan dinaikkan menjadi 5 dan bawah-kiri tetap 1, nilai terbaik 7 dengan satu cara. Nilai NEG dan ways=0 mempunyai arti berbeda: ways dapat nol setelah modulo walaupun state reachable.

Checklist desain: (1) apa satu state artinya, (2) apa keputusan pertama/terakhir, (3) apakah semua riwayat pada state memiliki masa depan sama, (4) mana basis reachable, (5) dependensi mana wajib lebih dulu, (6) tepat atau paling banyak, (7) maksimum/minimum/jumlah cara, (8) tipe serta sentinel, (9) seluruh kemungkinan akhir, (10) butuh keputusan atau hanya nilai.

Checklist debug dengan counterexample: satu item berat 2 kapasitas 4 menggagalkan loop maju 0/1; semua skor negatif menguji pilihan tidak kosong; nilai tingkat sama menguji strict LIS; grid awal blocked menguji basis; target nol menguji subset kosong; stok 5 -> 1,2,2 menguji counting keliru pada binary split; dua optimum menguji jumlah cara dan tie-break.

Membuktikan solusi: klasifikasikan semua solusi menurut keputusan terakhir, tunjukkan transisi legal dan lengkap, buktikan optimal substructure, lalu induksi atas urutan pengisian. Counting juga perlu kelompok terpisah. Kompleksitas dihitung dari state×transisi, bukan sekadar melihat banyak loop karena batas loop bisa berubah.

Gunakan 90 menit sebagai simulasi: 20 menit latihan 1, 25 menit latihan 2, 35 menit latihan 3, 10 menit menguji counterexample. Setelah selesai, tulis state tiap tugas sebelum coding. Siap ke Day 155 bila dapat menjelaskan mengapa dimensi ditambah/dibuang dan dapat menemukan sendiri kasus yang membedakan varian soal.''',e154,t154)

PREREQ={66:'Rekursi, array, aritmetika modular, analisis kompleksitas.',142:'Day 66 dan Day 141.',144:'Day 141–143.',147:'Day 144–146 (knapsack dan subset sum).',151:'Day 149–150, prefix sum.',152:'Day 144–151, terutama knapsack dan grid.',153:'Day 145, 149, 150, dan 152.',154:'Day 141–153.'}
COMPLEXITY={66:['O(N+B) waktu; O(N) memori dan stack.','O(N) waktu; O(N) memori dan stack.','O(NM) waktu/tabel; O(N+M) stack.'],142:['O(N) waktu; O(1) memori.','O(N) waktu dan memori.','O(NK) waktu; O(K) memori.'],144:['O(NX) waktu; O(X+N) memori.','O(NW) waktu; O(W) memori.','O(NX) waktu; O(X) memori.'],147:['O(W × sum log(c_eff+1)) waktu; O(W) memori.','O(X × sum log(c_eff+1)) waktu; O(X) memori.','O(S × sum log(c_eff+1)) waktu; O(S) memori.'],151:['O(N^3) waktu; O(N^2) memori.','O(N^3) waktu; O(N^2) memori.','O(|S|^2) waktu dan memori.'],152:['O(N) waktu dan memori.','O(NX) waktu; O(X+N) memori.','O(NW) waktu dan memori.'],153:['O(NM) waktu; O(M) memori.','O(|A||B|) waktu; O(min(|A|,|B|)) memori DP, ditambah input string.','O(NW) waktu; O(W) memori.'],154:['O(NW) waktu; O(W) memori.','O(N^2) waktu; O(N) memori.','O(NM) waktu dan memori.']}

def build():
    from authoring import write_day
    for d in DAYS:
        ps=[]
        for i,p in enumerate(d['exercises']):
            q={k:v for k,v in p.items() if k not in ('cases','oracle','editorial')}
            q['samples']=p['cases'][:3]
            labels=['minimal_boundary','zero_or_duplicate_trap','greedy_or_stock_trap','overflow_or_unreachable','large_structural_case']
            q['tests']=[((labels[j] if j<len(labels) else ('random_seed_20260905_'+str(j-len(labels)+1).zfill(2) if j<13 else 'maximum_constraint')),a,b) for j,(a,b) in enumerate(p['cases'][3:])]
            q['explanation']=p['editorial'];q['complexity']=COMPLEXITY[d['number']][i]
            q['sample_explanation']='Contoh 1 menunjukkan kasus utama; contoh 2 dan 3 menguji perubahan aturan atau kasus batas. Telusuri basis dan transisi secara manual sebelum menjalankan solusi.'
            if d['number']==153:q['memory_limit']='64 MB';q['time_limit']='3 detik'
            ps.append(q)
        folder=write_day(day=d['number'],title=d['title'],ppt=d['source'],objectives=[
            'Menuliskan state, basis, transisi, urutan evaluasi, dan letak jawaban dengan jelas.',
            'Membuktikan recurrence serta membedakan pilihan tepat, paling banyak, dan tidak kosong.',
            'Menyelesaikan tiga latihan bertingkat dan tiga tugas mandiri dengan contoh tandingan.',
            'Memeriksa overflow, sentinel, arah loop, dan kompleksitas sesuai batas soal.'
        ],theory=d['theory'],problems=ps,tasks=d['tasks'],prerequisites=PREREQ[d['number']])
        print(folder.name)
if __name__=='__main__':build()
