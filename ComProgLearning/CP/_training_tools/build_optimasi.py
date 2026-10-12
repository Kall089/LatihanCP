"""Original optimization exercises, answers from quadratic/cubic oracles."""
from authoring import write_day
import random
from functools import lru_cache
R=random.Random(267270)
HEAD='''#include <iostream>
#include <vector>
#include <algorithm>
#include <deque>
#include <limits>
#include <string>
#include <functional>
using namespace std;
using ll=long long;
const ll INF=4000000000000000000LL;
'''
def program(body,helpers=''):
 return HEAD+helpers+'\nint main(){ios::sync_with_stdio(false);cin.tie(nullptr);\n'+body+'\n}\n'
def prob(title,level,story,fmt,out,constraints,solution,explanation,complexity,cases,oracle,hint=''):
 checked=[(name,inp,str(oracle(inp)).strip()+'\n') for name,inp in cases]
 return dict(title=title,level=level,statement=story,input=fmt,output=out,constraints=constraints,
  solution=solution,explanation=explanation,complexity=complexity,samples=[(i,o) for _,i,o in checked[:3]],tests=checked[3:],hint=hint,
  sample_explanation='Contoh pertama melatih beberapa pilihan yang bersaing. Contoh kedua dan ketiga menyoroti kondisi batas; bandingkan semua pilihan legal untuk memeriksa hasilnya.')
def task(title,story,fmt,out,constraints,samples,hint=''):
 return dict(title=title,statement=story,input=fmt,output=out,constraints=constraints,samples=samples,hint=hint)
def arrcase(a,k,extra=''):
 return f'{len(a)} {k}'+(f' {extra}' if extra!='' else '')+'\n'+' '.join(map(str,a))+'\n'
def cases_arr():
 cases=[('sample_mix',arrcase([4,1,2,3],2)),('sample_single',arrcase([7],1)),('sample_zero',arrcase([0,0,0],3)),('one_group',arrcase([9,1,9,1],1)),('each_item',arrcase([1,8,2,9],4)),('overflow_int',arrcase([1000000]*8,3))]
 for t in range(18):
  n=R.randint(2,14);cases.append((f'random_{t:02}',arrcase([R.randint(0,30) for _ in range(n)],R.randint(1,n))))
 return cases
DC_HELP='''
vector<ll> optimize(int n,int groups,const function<ll(int,int)>&cost){
 vector<ll> prev(n+1,INF),cur(n+1,INF),answers(groups+1,INF);prev[0]=0;
 for(int g=1;g<=groups;++g){
  fill(cur.begin(),cur.end(),INF);
  function<void(int,int,int,int)> solve=[&](int l,int r,int lo,int hi){
   if(l>r)return; int mid=l+(r-l)/2,best=lo;
   for(int j=lo;j<=min(hi,mid-1);++j){
    if(prev[j]==INF)continue;
    ll candidate=prev[j]+cost(j+1,mid);
    if(candidate<cur[mid]){cur[mid]=candidate;best=j;}
   }
   solve(l,mid-1,lo,best);solve(mid+1,r,best,hi);
  };
  solve(g,n,g-1,n-1);prev.swap(cur);answers[g]=prev[n];
 }
 return answers;
}
'''
def brute_partition(a,k,kind=0,fee=0):
 n=len(a);p=[0]
 for x in a:p.append(p[-1]+x)
 def cost(l,r):
  if kind==1:
   m=(l+r)//2;return sum(abs(a[i]-a[m]) for i in range(l,r+1))
  return (p[r+1]-p[l])**2
 dp=[10**60]*(n+1);dp[0]=0;ans=[]
 for g in range(1,k+1):
  cur=[10**60]*(n+1)
  for i in range(g,n+1):cur[i]=min(dp[j]+cost(j,i-1) for j in range(g-1,i))
  dp=cur;ans.append((dp[n]+fee*g,g))
 return min(ans) if kind==2 else dp[n]
def dcoracle(inp,kind=0):
 v=list(map(int,inp.split()));n,k=v[:2]
 if kind==2:
  cost,g=brute_partition(v[3:],k,kind,v[2]);return f'{cost} {g}'
 return brute_partition(v[2:],k,kind)

def build_dc():
 base=cases_arr()
 cpp=program('int n,k;cin>>n>>k;vector<ll> p(n+1);for(int i=1;i<=n;++i){cin>>p[i];p[i]+=p[i-1];}\nauto cost=[&](int l,int r){ll s=p[r]-p[l-1];return s*s;};cout<<optimize(n,k,cost)[k]<<"\\n";',DC_HELP)
 p1=prob('Konvoi Logistik Festival','Menengah','Peti dengan bobot a[i] berbaris dan urutannya tidak boleh berubah. Bagilah seluruh barisan menjadi tepat K rombongan tak kosong yang masing-masing berisi peti berurutan. Biaya rombongan adalah kuadrat total bobotnya. Cari total biaya minimum; peti berbobot nol tetap harus mendapat rombongan.','N K, kemudian N bobot.','Satu bilangan: biaya minimum.','1 <= K <= min(N,30); 1 <= N <= 20000; 0 <= a[i] <= 10^6.',cpp,'Gunakan dp[g][i] untuk i peti pertama dalam tepat g grup. Pisahan terakhir j memberi dp[g-1][j]+(P[i]-P[j])^2. Basis dp[0][0]=0, lainnya INF. Untuk massa nonnegatif, selisih quadrangle adalah 2*x*z >= 0 sehingga opt j tidak menurun. D&C mempertahankan rentang kandidat yang mengandung optimum; induksi baris memastikan jawaban benar. Kandidat sama dipilih j terkecil.','O(K*N*log N) waktu, O(N+K) memori.',base,lambda s:dcoracle(s), 'Tulis dahulu O(KN^2). Mengapa bobot negatif merusak alasan monotonisitas?')
 # Stress answer via exact convex distribution, independent formula.
 n=20000;k=30;q,r=divmod(n,k);inp=arrcase([1]*n,k)
 p1['tests'].append(('maximum_balanced',inp,str((k-r)*q*q+r*(q+1)**2)))
 villages=[]
 for name,inp in base:
  v=list(map(int,inp.split()));a=sorted(v[2:]);villages.append((name,arrcase(a,v[1])))
 cpp2=program('''int n,k;cin>>n>>k;vector<ll>a(n+1),p(n+1);for(int i=1;i<=n;++i){cin>>a[i];p[i]=p[i-1]+a[i];}
 auto cost=[&](int l,int r){int m=(l+r)/2;return a[m]*(m-l+1)-(p[m]-p[l-1])+(p[r]-p[m])-a[m]*(r-m);};
 cout<<optimize(n,k,cost)[k]<<"\\n";''',DC_HELP)
 p2=prob('Posko di Jalan Panjang','Sulit','N kampung berada pada satu garis, diberikan menurut posisi tidak menurun. Bagi kampung menjadi tepat K wilayah berurutan tak kosong. Setiap wilayah membangun satu posko di posisi salah satu kampungnya dan membayar jumlah jarak seluruh kampung ke posko. Beberapa kampung boleh mempunyai posisi yang sama. Tentukan biaya total terkecil.','N K, kemudian N posisi x[i] terurut.','Total jarak minimum.','1 <= N <= 20000; 1 <= K <= min(N,30); 0 <= x[i] <= 10^6; x tidak menurun.',cpp2,'Median meminimalkan jumlah jarak absolut: menggeser posko melewati titik tengah tidak menurunkan biaya. Prefix sum membuat biaya interval ke median bisa dihitung O(1). Biaya median pada titik terurut memenuhi Monge (kontribusi setiap gap adalah jarak gap dikali min(banyak titik di kiri, banyak titik di kanan)); opt monoton mengizinkan D&C. DP membagi pada batas wilayah terakhir sehingga setiap pembagian dihitung dan yang termurah dipilih.','O(K*N*log N) waktu, O(N+K) memori.',villages,lambda s:dcoracle(s,1))
 p2['tests'].append(('maximum_same_position',arrcase([1000000]*20000,30),'0'))
 fee_cases=[]
 for name,inp in base:
  v=list(map(int,inp.split()));fee_cases.append((name,arrcase(v[2:],v[1],R.choice([-20,0,5,100]))))
 cpp3=program('''int n,k;ll fee;cin>>n>>k>>fee;vector<ll>p(n+1);for(int i=1;i<=n;++i){cin>>p[i];p[i]+=p[i-1];}
 auto c=[&](int l,int r){ll x=p[r]-p[l-1];return x*x;};auto a=optimize(n,k,c);
 ll best=INF;int groups=0;for(int g=1;g<=k;++g)if(a[g]+fee*g<best){best=a[g]+fee*g;groups=g;}
 cout<<best<<" "<<groups<<"\\n";''',DC_HELP)
 p3=prob('Bus Tambahan, Anggaran Tambahan','Sulit','Barisan penumpang memiliki beban a[i]. Operator boleh memakai antara 1 dan K bus. Tiap bus mendapat segmen berurutan tak kosong dan biaya kuadrat total bebannya, ditambah biaya tetap F. F boleh negatif karena subsidi. Minimizasikan biaya, dan bila sama pilih jumlah bus paling sedikit.','N K F, kemudian N beban.','Biaya minimum dan jumlah bus terpilih.','1 <= N <= 20000; 1 <= K <= min(N,30); 0 <= a[i] <= 10^6; -10^9 <= F <= 10^9.',cpp3,'Hitung biaya muatan terbaik untuk setiap tepat g bus menggunakan DP sebelumnya. Biaya tetap g*F sama untuk seluruh pembagian dengan g bus, sehingga baru ditambahkan setelah dp[g][N] selesai. Minimum pasangan (biaya,g) memilih kebijakan yang diminta. Tidak boleh langsung memakai K bus karena biaya tetap positif dapat membuat grup tambahan lebih mahal.','O(K*N*log N) waktu, O(N+K) memori.',fee_cases,lambda s:dcoracle(s,2))
 p3['tests'].append(('maximum_fee_tradeoff',arrcase([0]*20000,30,100),'100 1'))
 tasks=[task('Batas Grup Nol','Hitung minimum kuadrat total bobot untuk tepat K grup tak kosong. Bobot hanya 0 atau 1.','N K lalu N bobot.','Biaya minimum.','1<=K<=N<=10^5; a[i] dalam {0,1}.',[('4 2\n1 0 1 1\n','5'),('3 3\n0 0 0\n','0')],'Manfaatkan sedikitnya bobot berbeda dan bandingkan hasil dengan D&C kecil.'),
 task('Banyaknya Posko','Untuk tiap k dari 1 sampai K, cetak biaya minimum pelayanan kampung terurut oleh tepat k posko wilayah. Biaya wilayah adalah jumlah jarak ke median.','N K lalu N posisi terurut.','K baris biaya untuk k=1..K.','1<=K<=min(N,30);N<=20000;0<=x[i]<=10^6.',[('3 3\n0 2 4\n','4\n2\n0'),('2 2\n5 5\n','0\n0')]),
 task('Partisi Wajib pada Gerbang','Bagilah array menjadi tepat K segmen tak kosong dengan biaya kuadrat jumlah tiap segmen. Batas setelah posisi B wajib menjadi pemisah.','N K B lalu N bobot.','Biaya minimum.','2<=N<=3000;2<=K<=min(N,20);1<=B<N;0<=a[i]<=1000.',[('4 2 2\n1 2 3 4\n','58'),('3 3 1\n2 0 1\n','5')],'Gabungkan dua tabel biaya, dengan total grup K.')]
 theory='''## Intuisi dan desain state

D&C optimization mempercepat satu baris DP ketika lokasi pemisah terbaik bergerak ke kanan. Untuk pembagian prefix, `dp[g][i]` berarti biaya minimum i benda pertama dalam **tepat g segmen tak kosong**. Dengan prefix sum P, biaya segmen adalah `(P[i]-P[j])²` dan transisi mencoba `g-1 <= j < i`. Basis hanya `dp[0][0]=0`; prefix tidak kosong tanpa grup mustahil.

```text
prefix sampai j | grup terakhir j+1 ... i
  dp[g-1][j]   +       cost(j+1,i)
```

## Mengapa rentang opt boleh dipangkas

Untuk bobot tidak negatif dan empat batas a<=b<=c<=d, tulis jumlah pada tiga bagian berurutan sebagai x,y,z. Selisih `(x+y+z)²+y²-(x+y)²-(y+z)² = 2xz >= 0`. Inilah sifat Monge biaya kuadrat. Menambahkan dp baris sebelumnya ke kolom kandidat mempertahankan sifat itu. Dengan tie-break pemisah terkecil, lokasi minimum baris tidak menurun. Jika opt tengah = j, semua optimum di kiri berada <=j dan di kanan >=j.

**Koreksi catatan PPT:** menguji opt pada n kecil dapat menemukan counterexample, tetapi tidak membuktikan syarat berlaku untuk semua input. Bobot negatif dapat merusak argumen xz>=0. Lihat [syarat optimasi D&C](https://cp-algorithms.com/dynamic_programming/divide-and-conquer-dp.html).

## Pseudocode dan implementasi

```text
solve(l,r,optL,optR):
  mid=(l+r)/2
  cari best j pada [optL,min(optR,mid-1)]
  isi dp[mid]
  solve(l,mid-1,optL,j)
  solve(mid+1,r,j,optR)
```

Implementasi C++17 lengkap ada pada `../solusi/solution_1.cpp`; fungsi `optimize` menerima biaya interval O(1). Satu tingkat rekursi memeriksa total O(N) kandidat, ada O(log N) tingkat. Total O(KN log N), memori O(N+K), kedalaman rekursi O(log N).

## Trace yang dapat diperiksa

Bobot `[4,1,2,3]`, K=2. Baris satu grup untuk prefix berukuran 1..4 ialah `16,25,49,100`. Untuk i=2 hanya j=1 memberi17. Untuk i=3: j=1 memberi25, j=2 memberi29; optimum1. Untuk i=4: j=1 memberi52, j=2 memberi50, j=3 memberi58; optimum2. Hasil50, pembagian `[4,1] | [2,3]`.

## Perluasan

Exercise2 mengganti biaya kuadrat dengan jarak ke median. Posisi wajib terurut dan prefix sum menghitung biaya kiri/kanan median. Exercise3 memisahkan biaya isi grup dari biaya tetap bus; tepat K dan paling banyak K adalah state tujuan yang berbeda.

## Jebakan dan cek mandiri

- Jangan mengizinkan j=i: grup kosong melanggar definisi.
- Saat g>i state mustahil, jangan memprosesnya.
- Jangan menjumlahkan INF dengan biaya. Batas total bobot 2*10^10 membuat kuadrat melampaui 64 bit; **latihan kuadrat membatasi total bobot <=10^9** agar jawaban dan kandidat aman.
- Untuk K=1 jawabannya harus satu biaya seluruh array. Untuk K=N jawabannya jumlah biaya singleton.
- Sertakan nol, banyak optimum sama, dan bandingkan dengan O(KN²) kecil sebelum menjalankan ukuran besar.
'''
 # Ensure 64-bit constraints match all costs.
 for p in (p1,p3):p['constraints']+=' Jumlah seluruh a[i] <= 10^9.'
 write_day(day=267,title='Divide and Conquer DP Optimization',ppt='CP/_PPT-09-DP/Day-248 - Optimasi DP - Divide and Conquer dan Knuth.pptx',objectives=['Membuktikan syarat Monge untuk biaya yang digunakan.','Menghitung satu baris DP memakai D&C.','Membedakan tepat K dengan paling banyak K grup.'],prerequisites='Day 151, 153 dan prefix sum.',theory=theory,problems=[p1,p2,p3],tasks=tasks)

CHT='''
struct Line{ll m,b;ll at(ll x)const{return m*x+b;}};
struct Hull{
 deque<Line> h;
 static bool bad(Line a,Line b,Line c){
  return (__int128)(b.b-a.b)*(b.m-c.m)>=(__int128)(c.b-b.b)*(a.m-b.m);
 }
 void add(ll m,ll b){
  Line z{m,b};
  if(!h.empty()&&h.back().m==m){if(h.back().b<=b)return;h.pop_back();}
  while(h.size()>=2&&bad(h[h.size()-2],h.back(),z))h.pop_back();h.push_back(z);
 }
 ll query(ll x){while(h.size()>=2&&h[1].at(x)<=h[0].at(x))h.pop_front();return h[0].at(x);}
};
'''
def frog_oracle(inp):
 v=list(map(int,inp.split()));n,c=v[:2];a=v[2:];dp=[0]*n
 for i in range(1,n):dp[i]=min(dp[j]+(a[i]-a[j])**2+c for j in range(i))
 return dp[-1]
def build_cht():
 tariff=[]
 def tc(lines,x):return f'{len(lines)} {len(x)}\n'+''.join(f'{m} {b}\n' for m,b in lines)+' '.join(map(str,x))+'\n'
 tariff=[('mixed',tc([(3,0),(2,2),(1,9),(0,12)],[0,1,2,5,7,10])),('one',tc([(1,5)],[-3,0,2])),('same_slope',tc([(2,7),(2,1),(2,9)],[0,2,2])),('negative',tc([(3,-5),(0,0),(-2,6)],[-10,0,20])),('equal_intersection',tc([(3,0),(2,2),(1,4)],[2,2,3])),('large_values',tc([(10**6,10**12),(-10**6,-10**12)],[-10**6,10**6]))]
 for i in range(20):tariff.append((f'random_{i}',tc(sorted([(R.randint(-20,20),R.randint(-50,50)) for _ in range(12)],reverse=True),sorted(R.randint(-50,50) for _ in range(12)))))
 def taroracle(inp):
  v=list(map(int,inp.split()));n,q=v[:2];lines=list(zip(v[2:2+2*n:2],v[3:2+2*n:2]));return '\n'.join(str(min(m*x+b for m,b in lines)) for x in v[2+2*n:])
 p1=prob('Tarif Angkot di Hari Festival','Menengah','Tersedia N tarif y=m*x+b. Semua tarif diberikan dengan m tidak menaik. Q jarak perjalanan datang tidak menurun; jarak boleh negatif sebagai koordinat simulasi. Untuk setiap jarak, cetak nilai tarif minimum. Intersep negatif adalah subsidi, dan tarif boleh memiliki kemiringan sama.','N Q; N baris m b; satu baris Q nilai x tidak menurun.','Q baris, tarif minimum setiap query.','1<=N,Q<=200000; |m|,|x|<=10^6; |b|<=10^12; slope tidak menaik, x tidak menurun.',program('int n,q;cin>>n>>q;Hull h;for(int i=0;i<n;++i){ll m,b;cin>>m>>b;h.add(m,b);}while(q--){ll x;cin>>x;cout<<h.query(x)<<"\\n";}',CHT),'Untuk slope menurun, garis optimal sepanjang query menaik hanya bergerak ke kanan. Hapus garis tengah bila titik potong kiri tidak mendahului titik potong kanan. Perkalian silang memakai __int128. Slope sama cukup menyisakan intersep minimum. Garis yang kalah oleh tetangga berikutnya pada query kini akan tetap kalah untuk semua x selanjutnya, sehingga boleh dikeluarkan dari depan.','O(N+Q) waktu amortisasi, O(N) memori.',tariff,taroracle)
 frog=[('jump_options',arrcase([1,3,4,10],5)),('one_stone',arrcase([5],100)),('equal_heights',arrcase([2,2,2],0)),('negative_heights',arrcase([-10,-3,0,9],7)),('large_square',arrcase([-1000000,1000000],1000000000000)),('ties',arrcase([0,1,2],2))]
 for i in range(20):frog.append((f'random_{i}',arrcase(sorted(R.randint(-50,50) for _ in range(15)),R.randint(0,50))))
 body='int n;ll c;cin>>n>>c;Hull h;ll x,dp=0;cin>>x;h.add(-2*x,x*x);for(int i=1;i<n;++i){cin>>x;dp=x*x+c+h.query(x);h.add(-2*x,dp+x*x);}cout<<dp<<"\\n";'
 p2=prob('Katak dan Batu Berkabut','Menengah','Katak mulai pada batu 1 dan boleh melompat dari j ke i mana pun dengan j<i. Ketinggian batu tidak menurun. Biaya satu lompatan adalah (h[i]-h[j]) kuadrat ditambah C. Cari biaya minimum mencapai batu N; bila N=1 katak belum melompat dan biaya nol.','N C lalu N ketinggian tidak menurun.','Biaya minimum.','1<=N<=200000; -10^6<=h[i]<=10^6; 0<=C<=10^12.',program(body,CHT),'Ekspansi kuadrat memberi dp[i]=h[i]^2+C+min_j(-2*h[j]*h[i]+dp[j]+h[j]^2). Sebelum query i, hull tepat memuat kandidat j<i. Query dahulu baru insert mencegah lompatan dari diri sendiri. Karena h tidak menurun, slope -2h tidak menaik dan query h tidak menurun. Induksi i membuktikan hasil sama dengan semua lompatan sah.','O(N) waktu amortisasi, O(N) memori.',frog,frog_oracle)
 p2['tests'].append(('maximum_equal',arrcase([7]*200000,10),'10'))
 def lin_case(a,b):return str(len(a))+'\n'+' '.join(map(str,a))+'\n'+' '.join(map(str,b))+'\n'
 linear=[('reuse_station',lin_case([1,2,3],[5,3,1])),('no_trip',lin_case([10],[4])),('free_station',lin_case([0,0,0],[0,0,0])),('same_rate',lin_case([1,2,5],[2,2,2])),('change_rate',lin_case([1,2,10,20],[10,5,1,0])),('large',lin_case([0,1000000],[1000000,0]))]
 for i in range(20):linear.append((f'random_{i}',lin_case(sorted(R.randint(0,50) for _ in range(15)),sorted((R.randint(0,30) for _ in range(15)),reverse=True))))
 def lin_oracle(inp):
  v=list(map(int,inp.split()));n=v[0];a=v[1:n+1];b=v[n+1:];d=[0]*n
  for i in range(1,n):d[i]=min(d[j]+b[j]*a[i] for j in range(i))
  return d[-1]
 p3=prob('Relai Pengiriman di Jalur Pantai','Sulit','Pos 1 telah aktif dengan biaya nol. Untuk mengaktifkan pos i>1, pilih salah satu pos sebelumnya j<i dan bayar biaya aktivasi j ditambah b[j]*a[i]. Nilai a tidak menurun dan b tidak menaik. Hanya biaya minimum untuk mengaktifkan satu pos tujuan yang dihitung; tidak wajib membayar semua pos. Tentukan biaya aktivasi pos N.','N, baris N nilai a, baris N nilai b.','Biaya aktivasi minimum pos N.','1<=N<=200000;0<=a[i],b[i]<=10^6; a tidak menurun dan b tidak menaik.',program('int n;cin>>n;vector<ll>a(n),b(n);for(ll&x:a)cin>>x;for(ll&x:b)cin>>x;Hull h;h.add(b[0],0);ll d=0;for(int i=1;i<n;++i){d=h.query(a[i]);h.add(b[i],d);}cout<<d<<"\\n";',CHT),'Setiap pos j adalah garis b[j]*x+dp[j]. Setelah semua pos sebelum i diproses, nilai minimum di x=a[i] persis recurrence aktivasi. Garis disisipkan setelah jawabannya diketahui. Syarat monoton berlaku dari urutan kedua array; b sama harus ditangani agar pembagian titik potong tidak diperlukan.','O(N) waktu amortisasi, O(N) memori.',linear,lin_oracle)
 tasks=[task('Taksi Paling Mahal','Untuk setiap x terurut, cari MAKSIMUM m*x+b. Garis datang dengan slope tidak menurun.','N Q; N baris m b; Q nilai x tidak menurun.','Q baris tarif maksimum.','1<=N,Q<=200000;|m|,|x|<=10^6;|b|<=10^12.',[('2 2\n1 0\n2 -1\n0 3\n','0\n5'),('1 2\n0 -4\n-5 5\n','-4\n-4')]),task('Katak dengan Pajak Pendaratan','Katak melompat maju dengan biaya (h[i]-h[j])²+C+p[i]. h terurut, p adalah pajak batu tujuan. Batu awal tidak dipajaki.','N C; N nilai h terurut; N pajak p.','Biaya minimum ke batu N.','1<=N<=200000;|h[i]|<=10^6;0<=C,p[i]<=10^9.',[('3 0\n0 1 2\n9 10 0\n','4'),('1 8\n5\n100\n','0')]),task('Biaya pada Semua Pos','Gunakan aturan relai pada exercise3. Cetak dp untuk SEMUA pos, bukan hanya pos N.','N; array a tidak menurun; array b tidak menaik.','N nilai dp[1]..dp[N].','1<=N<=200000;0<=a[i],b[i]<=10^6.',[('3\n1 2 3\n5 3 1\n','0 10 15'),('2\n0 1\n0 0\n','0 0')])]
 theory='''## Dari recurrence ke garis

Jika `dp[i]=min_{j<i}(dp[j]+b[j]*a[i])`, bagian milik j adalah garis `y=b[j]*x+dp[j]`, sedangkan x=a[i]. Hull menyimpan garis yang mungkin menjadi minimum. Jangan menggunakan CHT sebelum menulis recurrence lambat yang benar.

```text
state j -> (slope b[j], intercept dp[j])
state i -> query x=a[i] -> dp[i] -> tambahkan garis i
```

## Syarat versi deque

Pada versi minimum di sini, slope masuk **tidak menaik**, query x **tidak menurun**. Ketika dua garis punya slope sama, intersep lebih kecil mendominasi di semua x. Untuk tiga garis a,b,c dengan slope ketat menurun, b dibuang bila titik potong(a,b) >= titik potong(b,c). Bandingkan perkalian silang, jangan pecahan. `__int128` hanya dipakai untuk perkalian silang; nilai jawaban sesuai batas tetap long long. Ini ekstensi compiler GCC/Clang yang tersedia di lingkungan latihan.

Setiap garis ditambahkan sekali dan dihapus paling banyak sekali dari setiap sisi. Total O(N+Q), memori O(N). Query yang tidak monoton membatalkan alasan membuang depan: gunakan Li Chao di Day269. [Referensi bentuk recurrence dan Li Chao](https://cp-algorithms.com/geometry/convex_hull_trick.html).

## Pseudocode dan C++

```text
add(m,b):
  gabungkan slope yang sama
  selama dua garis terakhir bersama garis baru membuat garis tengah dominasi: pop_back
  push_back garis baru
query(x):
  selama garis kedua <= garis pertama di x: pop_front
  return garis depan di x
```

Implementasi `Hull` yang langsung dapat dikompilasi bersama main tersedia di `../solusi/solution_1.cpp`. Telusuri ekspresi cross product pada fungsi `bad` sebelum menyalinnya. Hull tidak boleh di-query ketika kosong.

## Trace

Garis `(3,0),(2,2),(1,9),(0,12)`. Garis (1,9) tidak pernah optimal setelah garis konstan12 masuk. Untuk x=0,1,2,5,7,10 jawabannya `0,3,6,12,12,12`. Nilai sama pada titik potong aman karena hanya nilai minimum yang diminta.

Untuk katak h=[1,3,4,10], C=5: dp1=0. dp2=9. dp3=min(9+5,9+1+5)=14. dp4=min(81+5,9+49+5,14+36+5)=55. Setiap h_i menambah garis `(-2h_i,dp_i+h_i²)` setelah query selesai.

## Bukti kebenaran

Antara dua garis beda slope, perbedaan nilai adalah fungsi linear yang hanya berganti tanda sekali. Ini membenarkan penghapusan tengah lewat urutan titik potong dan penghapusan depan setelah garis berikutnya lebih baik pada x yang semakin besar. Induksi jumlah insert/query mempertahankan nilai minimum seluruh garis yang pernah sah. Untuk DP, induksi indeks i menghubungkan nilai query itu dengan recurrence asli.

## Perangkap

- Slope sama, koordinat duplikat, dan semua biaya nol harus diuji.
- Jangan insert state i sebelum meng-query i.
- Hindari `int` pada m*x dan h*h; perkalian harus sudah dalam tipe lebar.
- Jangan menganggap semua input CHT sudah terurut. Hanya urutkan bila itu mempertahankan arti soal.
- Tie-break jalur tidak otomatis didukung deque nilai saja.
'''
 write_day(day=268,title='Convex Hull Trick - Kasus Monoton',ppt='CP/_PPT-09-DP/Day-244 - Convex Hull Trick & Li Chao Tree.pptx',objectives=['Mengubah DP menjadi query garis.','Membuktikan kapan garis dapat dibuang.','Menangani slope sama dan overflow perkalian silang.'],prerequisites='Day143,151 dan konsep garis linear.',theory=theory,problems=[p1,p2,p3],tasks=tasks)

LICHAO='''
struct Line{ll m=0,b=INF;ll at(ll x)const{return m*x+b;}};
struct LiChao{
 vector<ll>x;vector<Line>t;
 LiChao(vector<ll> coords):x(coords){sort(x.begin(),x.end());x.erase(unique(x.begin(),x.end()),x.end());t.resize(4*x.size()+4);}
 void add(Line z,int v,int l,int r){
  int mid=(l+r)/2;bool left=z.at(x[l])<t[v].at(x[l]);bool middle=z.at(x[mid])<t[v].at(x[mid]);
  if(middle)swap(z,t[v]);if(l==r)return;
  if(left!=middle)add(z,v*2,l,mid);else add(z,v*2+1,mid+1,r);
 }
 void add(ll m,ll b){if(!x.empty())add({m,b},1,0,(int)x.size()-1);}
 void segment(Line z,ll a,ll b,int v,int l,int r){
  if(x[r]<a||x[l]>b)return;if(a<=x[l]&&x[r]<=b){add(z,v,l,r);return;}
  int mid=(l+r)/2;segment(z,a,b,v*2,l,mid);segment(z,a,b,v*2+1,mid+1,r);
 }
 void segment(ll m,ll b,ll l,ll r){if(!x.empty())segment({m,b},l,r,1,0,(int)x.size()-1);}
 ll query(ll k,int v,int l,int r){ll ans=t[v].at(k);if(l==r)return ans;int mid=(l+r)/2;return min(ans,k<=x[mid]?query(k,v*2,l,mid):query(k,v*2+1,mid+1,r));}
 ll query(ll k){return query(k,1,0,(int)x.size()-1);}
};
'''
def build_li():
 def opscase(ops):return str(len(ops))+'\n'+'\n'.join(ops)+'\n'
 cases=[('mixed',opscase(['2 3','1 2 1','2 3','1 -1 8','2 -2','2 10'])),('empty',opscase(['2 0'])),('same_x',opscase(['1 0 5','1 0 -3','2 1','2 1'])),('reverse_queries',opscase(['1 2 0','1 -2 0','2 10','2 -10'])),('late_better',opscase(['1 5 100','2 0','1 0 0','2 0'])),('large',opscase(['1 1000000 1000000000000','2 1000000']))]
 for i in range(20):
  ops=[]
  for _ in range(30):ops.append(f'1 {R.randint(-30,30)} {R.randint(-100,100)}' if R.randrange(2) else f'2 {R.randint(-50,50)}')
  ops.append('2 0');cases.append((f'random_{i}',opscase(ops)))
 def oracle(inp,segment=False):
  lines=[];ans=[]
  for row in inp.strip().splitlines()[1:]:
   v=list(map(int,row.split()))
   if v[0]==1:lines.append(v[1:])
   else:
    x=v[1];valid=[m*x+b for m,b,*bounds in lines if not bounds or bounds[0]<=x<=bounds[1]];ans.append(str(min(valid)) if valid else 'EMPTY')
  return '\n'.join(ans)
 main='''int q;cin>>q;struct Op{int t;ll m,b,l,r;};vector<Op>a;vector<ll>x;
 while(q--){Op z{};cin>>z.t;if(z.t==1){cin>>z.m>>z.b;EXTRA_READ}else{cin>>z.m;x.push_back(z.m);}a.push_back(z);}LiChao tree(x);
 for(auto z:a){if(z.t==1){INSERT_LINE}else{ll v=tree.query(z.m);if(v==INF)cout<<"EMPTY\\n";else cout<<v<<"\\n";}}'''
 p1=prob('Papan Tarif yang Terus Berubah','Menengah','Penyedia layanan menambahkan tarif linear sepanjang hari. Operasi 1 m b menambahkan tarif y=m*x+b secara permanen, dan operasi 2 x menanyakan tarif minimum dari tarif yang sudah masuk. Urutan slope dan query bebas. Cetak EMPTY jika belum ada tarif pada saat query.','Q lalu Q operasi 1 m b atau 2 x.','Satu baris per operasi2: nilai minimum atau EMPTY.','1<=Q<=200000; minimal satu query; |m|,|x|<=10^6;|b|<=10^12.',program(main.replace('EXTRA_READ','').replace('INSERT_LINE','tree.add(z.m,z.b);'),LICHAO),'Kompresi hanya koordinat query, sambil mempertahankan urutan waktu operasi. Pada setiap node, simpan garis terbaik di titik tengah; garis yang kalah mungkin lebih baik hanya pada satu sisi karena dua garis berpotongan paling sekali. Query mengambil minimum pada root-to-leaf path. Pembacaan semua operasi tidak berarti tarif masa depan boleh dipakai: replay tetap kronologis.','O(Q log Q) waktu termasuk sort, O(Q) memori.',cases,oracle)
 frog=[('unsorted',arrcase([1,10,3,8],5)),('one',arrcase([4],20)),('same',arrcase([2,2,2],0)),('zigzag',arrcase([0,10,-10,5,-5],3)),('large',arrcase([-1000000,1000000],1000000000000)),('ties',arrcase([2,0,2,0],0))]
 for i in range(20):frog.append((f'random_{i}',arrcase([R.randint(-50,50) for _ in range(15)],R.randint(0,50))))
 cpp=program('int n;ll c;cin>>n>>c;vector<ll>h(n);for(ll&x:h)cin>>x;LiChao t(h);t.add(-2*h[0],h[0]*h[0]);ll dp=0;for(int i=1;i<n;++i){dp=h[i]*h[i]+c+t.query(h[i]);t.add(-2*h[i],dp+h[i]*h[i]);}cout<<dp<<"\\n";',LICHAO)
 p2=prob('Katak di Pegunungan Acak','Sulit','Aturan lompatan sama: dari j ke i dengan j<i, biaya (h[i]-h[j])²+C. Kali ini tinggi batu bebas naik turun. Urutan batu tidak boleh diubah. Tentukan biaya minimum dari batu1 ke batuN.','N C lalu N ketinggian.','Biaya minimum.','1<=N<=200000;|h[i]|<=10^6;0<=C<=10^12.',cpp,'Ekspansi kuadrat sama dengan CHT monoton, tetapi tinggi yang tidak terurut membuat penghapusan depan deque tidak sah. Li Chao menyimpan semua kandidat yang masih relevan tanpa asumsi urutan. Hanya tinggi query yang dikompresi; urutan batu tetap utuh. Induksi indeks i dan invariant Li Chao membuktikan minimum recurrence.','O(N log N) waktu, O(N) memori.',frog,frog_oracle)
 p2['tests'].append(('maximum_constant',arrcase([1]*200000,100),'100'))
 seg=[('partial_validity',opscase(['1 2 1 0 5','2 -1','2 3','1 -1 8 3 10','2 10'])),('one_point',opscase(['1 5 2 3 3','2 3','2 4'])),('empty',opscase(['2 0'])),('negative_interval',opscase(['1 -2 1 -5 -1','2 -5','2 -1','2 0'])),('overlap',opscase(['1 0 7 0 10','1 0 3 5 6','2 4','2 5','2 6','2 7'])),('large',opscase(['1 1000000 1000000000000 -1000000 1000000','2 1000000']))]
 for i in range(20):
  ops=[]
  for _ in range(30):
   if R.randrange(2):
    l,r=sorted([R.randint(-30,30),R.randint(-30,30)]);ops.append(f'1 {R.randint(-20,20)} {R.randint(-40,40)} {l} {r}')
   else:ops.append(f'2 {R.randint(-40,40)}')
  ops.append('2 0');seg.append((f'random_{i}',opscase(ops)))
 p3=prob('Promo Hanya untuk Zona Tertentu','Sulit','Tarif promosi berlaku hanya pada koordinat L<=x<=R dan sejak saat ia ditambahkan. Operasi 1 m b L R memasukkan promo y=m*x+b. Operasi 2 x menanyakan minimum semua promo yang sudah masuk dan mencakup x. Jika tidak ada, cetak EMPTY.','Q kemudian operasi 1 m b L R atau 2 x.','Minimum atau EMPTY per query.','1<=Q<=100000;minimal satu query;|m|,|x|,|L|,|R|<=10^6;|b|<=10^12;L<=R.',program(main.replace('EXTRA_READ','cin>>z.l>>z.r;').replace('INSERT_LINE','tree.segment(z.m,z.b,z.l,z.r);'),LICHAO),'Pecah rentang berlaku menjadi O(log Q) node kanonik segment tree atas koordinat query. Pada setiap node yang sepenuhnya tertutup, insert garis dengan Li Chao. Garis di node hanya berlaku bagi seluruh titik node itu, sehingga query path tidak pernah mengambil promo di luar zona. Semua titik yang sah terliput tepat oleh dekomposisi kanonik. Replay menjaga waktu aktivasi.','O(Q log^2 Q) waktu, O(Q) memori.',seg,oracle)
 tasks=[task('Harga Maksimum Dinamis','Operasi1 menambah garis dan operasi2 mencari maksimum garis aktif. Jika kosong cetak EMPTY.','Q lalu 1 m b atau 2 x.','Maksimum atau EMPTY per query.','Q<=200000;|m|,|x|<=10^6;|b|<=10^12.',[('3\n1 2 1\n1 -1 5\n2 3\n','7'),('1\n2 0\n','EMPTY')]),task('Katak Berpajak Acak','Ketinggian tidak terurut. Lompatan j ke i>j membayar kuadrat selisih tinggi ditambah p[i]. Batu1 tidak dipajaki.','N; N tinggi; N pajak.','Biaya minimum mencapai N.','1<=N<=200000;|h[i]|<=10^6;0<=p[i]<=10^9.',[('3\n0 10 1\n0 0 2\n','3'),('1\n7\n8\n','0')]),task('Promo Titik Akhir','Semua tarif diberikan di awal dan memiliki zona inklusif. Jawab Q titik bebas.','N Q; N baris m b L R; Q titik x.','Minimum atau EMPTY per titik.','1<=N,Q<=100000;|m|,|L|,|R|,|x|<=10^6;|b|<=10^12;L<=R.',[('1 3\n1 2 0 1\n0 1 2\n','2\n3\nEMPTY'),('1 2\n0 -5 -2 -2\n-2 0\n','-5\nEMPTY')])]
 theory='''## Invariant Li Chao

Li Chao menyimpan fungsi garis pada pohon rentang koordinat x. Satu node menyimpan garis terbaik **di titik tengah node** di antara garis yang dibandingkan di sana; ia tidak harus terbaik di seluruh interval. Garis lain diturunkan ke sisi tempat ia masih mungkin menang. Dua garis linear berbeda berpotongan paling sekali, jadi satu insert mengikuti paling banyak satu cabang.

```text
          [seluruh x], simpan pemenang di mid
                  /                    
       sisi yang masih mungkin       sisi aman
             mengalahkan
```

## Desain koordinat dan pseudocode

Semua koordinat query diketahui setelah input dibaca. Sort dan unique koordinat itu; replay operasi dalam urutan aslinya. Garis masa depan tidak diaktifkan lebih awal. Urutan asli tinggi katak juga tidak berubah.

```text
insert(new,node):
  bandingkan new dengan old pada x[left] dan x[mid]
  simpan pemenang di mid
  jika selisih tanda menunjukkan persilangan kiri: recurse kiri
  selainnya recurse kanan
query(x): minimum garis pada setiap node di jalur x
```

Fungsi C++ lengkap `LiChao` ada pada `../solusi/solution_1.cpp`. Implementasi memakai array 4Q node, garis awal `(0,INF)`, dan handle set koordinat kosong ketika tidak ada query. Untuk input latihan paling sedikit satu query wajib. Insert/query O(log Q), sorting O(Q log Q), memori O(Q).

## Trace

Operasi `query3, add(2,1), query3, add(-1,8), query(-2), query10` memberi `EMPTY,7,-3,-2`. Kedua garis berpotongan di x=7/3. Query boleh melompat dari kanan ke kiri; tidak ada garis yang dibuang hanya karena query sebelumnya.

## DP dan interval berlaku

Katak dengan urutan tinggi bebas tetap memakai `dp[i]=h[i]^2+C+min(-2h[j]*h[i]+dp[j]+h[j]^2)`. Insert setelah query memastikan j<i. Untuk promo [L,R], dekomposisi rentang ke O(log Q) node; masing-masing melakukan insert Li Chao O(log Q). Query tetap O(log Q). Pada node batas, bandingkan dengan koordinat asli x[l],x[r], bukan nomor hasil kompresi.

## Bukti dan jebakan

Query mengambil minimum semua garis pada jalur. Setiap garis yang bisa menjadi optimum di x disimpan di salah satu node jalur tersebut, karena setiap proses penurunan membuang hanya sisi tempat ia terbukti kalah. Invariant ini dipertahankan oleh pertukaran garis di midpoint. Untuk interval berlaku, hanya node yang seluruh rentangnya legal menerima garis.

- INF harus lebih besar dari semua nilai legal. Nilai latihan jauh di bawah 4e18.
- `EMPTY` berbeda dengan minimum0 atau minimum negatif.
- Satu koordinat, slope sama, dan interval L=R harus bekerja.
- Array 4Q jauh lebih terkendali daripada mengalokasikan seluruh domain koordinat besar.
- Li Chao tidak berlaku otomatis bagi fungsi yang dapat saling berpotongan berkali-kali.
'''
 write_day(day=269,title='Li Chao Tree untuk CHT Dinamis',ppt='CP/_PPT-09-DP/Day-244 - Convex Hull Trick & Li Chao Tree.pptx',objectives=['Menjaga invariant garis di midpoint.','Memakai query tidak monoton tanpa mengubah urutan data.','Menambahkan garis yang hanya berlaku pada interval.'],prerequisites='Day268 dan segment tree dasar.',theory=theory,problems=[p1,p2,p3],tasks=tasks)

KNUTH='''
ll mergeCost(const vector<ll>&a){
 int n=(int)a.size();if(n<=1)return 0;vector<ll>p(n+1);for(int i=0;i<n;++i)p[i+1]=p[i]+a[i];
 vector<vector<ll>>d(n,vector<ll>(n));vector<vector<int>>opt(n,vector<int>(n));
 for(int i=0;i<n;++i)opt[i][i]=i;
 for(int len=2;len<=n;++len)for(int l=0;l+len<=n;++l){int r=l+len-1;d[l][r]=INF;
  for(int k=opt[l][r-1];k<=min(r-1,opt[l+1][r]);++k){ll cand=d[l][k]+d[k+1][r]+p[r+1]-p[l];if(cand<=d[l][r]){d[l][r]=cand;opt[l][r]=k;}}
 }
 return d[0][n-1];
}
'''
def merge_brute(a):
 @lru_cache(None)
 def go(l,r):
  if l==r:return 0
  return sum(a[l:r+1])+min(go(l,k)+go(k+1,r) for k in range(l,r))
 return go(0,len(a)-1)
def build_knuth():
 cases=[('greedy_trap','4\n4 1 2 3\n'),('one','1\n9\n'),('zeros','4\n0 0 0 0\n'),('equal','5\n2 2 2 2 2\n'),('heavy_ends','5\n100 1 1 1 100\n'),('overflow_int','3\n1000000000 1000000000 1000000000\n')]
 for i in range(20):cases.append((f'random_{i}',str(12)+'\n'+' '.join(str(R.randint(0,40)) for _ in range(12))+'\n'))
 def oracle(s):return merge_brute(list(map(int,s.split()))[1:])
 p1=prob('Peti yang Hanya Bisa Digabung dari Samping','Menengah','N peti berurutan akan digabung menjadi satu. Satu operasi memilih dua kelompok peti yang bersebelahan, membayar total bobot kedua kelompok, dan menggantinya dengan satu kelompok. Posisi relatif peti tidak boleh berubah. Cari total biaya minimum seluruh operasi.','N lalu N bobot.','Biaya minimum.','1<=N<=2000;0<=a[i]<=10^9.',program('int n;cin>>n;vector<ll>a(n);for(ll&x:a)cin>>x;cout<<mergeCost(a)<<"\\n";',KNUTH),'Pada operasi terakhir, rentang [l,r] pasti dipecah menjadi [l,k] dan [k+1,r]. Maka dp[l][r]=sum(l,r)+min(dp[l][k]+dp[k+1][r]). Bobot tidak negatif memberi monotonic interval dan quadrangle equality untuk sum. Teorema Knuth membatasi opt[l][r-1] <= opt[l][r] <= opt[l+1][r]. Pilih k TERBESAR ketika biaya sama agar konsisten dengan konvensi teorema. Induksi panjang rentang memberi biaya optimal.','O(N^2) waktu dan memori.',cases,oracle)
 p1['tests'].append(('maximum_power_two','1024\n'+' '.join(['1']*1024)+'\n',str(1024*10)))
 # Stick cutting reduces to ordered merge of gaps.
 cuts=[('three_cuts','10 3\n2 4 7\n'),('no_cut','100 0\n'),('one_cut','9 1\n4\n'),('near_edges','100 4\n1 2 98 99\n'),('uniform','8 3\n2 4 6\n'),('large','1000000000 2\n1 999999999\n')]
 for i in range(20):
  p=sorted(R.sample(range(1,50),8));cuts.append((f'random_{i}',f'50 8\n'+ ' '.join(map(str,p))+'\n'))
 def cutoracle(s):
  v=list(map(int,s.split()));L,m=v[:2];p=[0]+v[2:]+[L]
  return merge_brute([p[i+1]-p[i] for i in range(m+1)])
 cpp=program('ll length;int m;cin>>length>>m;vector<ll>p(m+2),a(m+1);p[m+1]=length;for(int i=1;i<=m;++i)cin>>p[i];for(int i=0;i<=m;++i)a[i]=p[i+1]-p[i];cout<<mergeCost(a)<<"\\n";',KNUTH)
 p2=prob('Memotong Pita Panggung','Menengah','Pita panjang L harus dipotong pada M posisi yang diberikan terurut ketat. Memotong sebuah potongan pita membayar panjang potongan itu sebelum dipotong. Setiap posisi harus dipotong tepat sekali, dengan urutan bebas. Cari total biaya minimum. Jika M=0, tidak ada biaya.','L M kemudian M posisi potong menaik (baris ini boleh kosong untuk M=0).','Biaya pemotongan minimum.','1<=L<=10^9;0<=M<=1999;0<p[1]<...<p[M]<L.',cpp,'Tambahkan batas0 dan L, ubah selisih posisi menjadi bobot celah. Membalik urutan pemotongan menghasilkan penggabungan dua rentang celah bersebelahan, dengan biaya sama. Jadi minimum potong sama dengan minimum merge berurutan. Bobot celah positif memenuhi syarat Knuth. M=0 menghasilkan satu celah dan biaya0.','O((M+1)^2) waktu dan memori.',cuts,cutoracle)
 ring=[('rotation_matters','4\n4 1 2 3\n'),('single','1\n8\n'),('two','2\n2 5\n'),('zeros','4\n0 0 0 0\n'),('heavy','5\n100 1 1 1 1\n'),('large','3\n1000000000 1000000000 1000000000\n')]
 for i in range(20):ring.append((f'random_{i}','9\n'+' '.join(str(R.randint(0,30)) for _ in range(9))+'\n'))
 ringcpp=program('''int n;cin>>n;vector<ll>a(2*n),p(2*n+1);for(int i=0;i<n;++i){cin>>a[i];a[i+n]=a[i];}for(int i=0;i<2*n;++i)p[i+1]=p[i]+a[i];
 vector<vector<ll>>d(2*n,vector<ll>(2*n));vector<vector<int>>o(2*n,vector<int>(2*n));for(int i=0;i<2*n;++i)o[i][i]=i;
 for(int len=2;len<=n;++len)for(int l=0;l+len<=2*n;++l){int r=l+len-1;d[l][r]=INF;for(int k=o[l][r-1];k<=min(r-1,o[l+1][r]);++k){ll v=d[l][k]+d[k+1][r]+p[r+1]-p[l];if(v<=d[l][r]){d[l][r]=v;o[l][r]=k;}}}
 ll ans=INF;for(int l=0;l<n;++l)ans=min(ans,d[l][l+n-1]);cout<<ans<<"\\n";''')
 def ringoracle(s):
  a=list(map(int,s.split()))[1:];return min(merge_brute(a[i:]+a[:i]) for i in range(len(a)))
 p3=prob('Lampion dalam Lingkaran','Sulit','N kelompok lampion tersusun melingkar. Gabungkan dua kelompok bertetangga dengan biaya jumlah bobotnya sampai tersisa satu. Tetangga pertama dan terakhir juga boleh digabung. Cari total biaya minimum; orientasi lingkaran tidak boleh diubah.','N lalu N bobot mengikuti lingkaran.','Biaya minimum.','1<=N<=1000;0<=a[i]<=10^9.',ringcpp,'Setiap urutan merge melingkar memiliki batas antara dua kelompok pada merge terakhir yang tidak pernah dilintasi sebelumnya. Memotong di batas itu menghasilkan merge linear dengan biaya sama. Gandakan array dan hitung Knuth hanya sampai panjang N. Minimum seluruh N jendela panjang N mencakup semua pilihan batas. Algoritma menghitung seluruh rentang dalam satu tabel, bukan menjalankan Knuth N kali.','O(N^2) waktu dan memori; tabel memakai (2N)^2 sel.',ring,ringoracle)
 p3['tests'].append(('maximum_power_two','512\n'+' '.join(['1']*512)+'\n',str(512*9)))
 tasks=[task('Biaya Alat Tetap','Merge peti bersebelahan seperti exercise1, tetapi setiap operasi juga membayar F.','N F lalu N bobot.','Total biaya minimum.','1<=N<=2000;0<=a[i],F<=10^9.',[('3 5\n1 2 3\n','19'),('1 99\n8\n','0')],'Berapa operasi yang selalu dilakukan?'),task('Memulihkan Potongan Awal','Pita panjang L sudah dipotong di posisi B. Biaya pemotongan awal tidak dihitung. Potong posisi wajib lain dengan biaya panjang segmen saat dipotong.','L B M, kemudian M posisi terurut yang berbeda dari B.','Biaya lanjutan minimum.','1<B<L<=10^9;0<=M<=1998;semua posisi ada di (0,L).',[('10 5 2\n2 8\n','10'),('10 5 0\n','0')]),task('Biaya Seluruh Subrentang','Bobot N peti diberikan. Untuk tiap query L R, jawab biaya minimum menggabungkan subrentang itu saja.','N Q; N bobot; Q baris L R (indeks1).','Q biaya minimum.','1<=N<=2000;Q<=100000;0<=a[i]<=10^9;1<=L<=R<=N.',[('3 3\n1 2 3\n1 3\n1 2\n2 2\n','9\n3\n0'),('1 1\n7\n1 1\n','0')])]
 theory='''## Range DP sebelum optimasi

Untuk menggabungkan peti berurutan, operasi terakhir selalu menggabungkan dua rentang. `dp[l][r]` menyimpan biaya minimum menggabungkan peti l..r. Basis `dp[i][i]=0`. Rumusnya `dp[l][r]=sum(l,r)+min_{l<=k<r}(dp[l][k]+dp[k+1][r])`. DP biasa O(N³); urutan isi adalah panjang interval yang meningkat.

```text
[l ........ k] + [k+1 ........ r]
  biaya kiri       biaya kanan   + sum(l,r)
```

## Syarat dan bukti yang harus diperiksa

Dengan bobot nonnegatif, biaya C(l,r)=sum(l,r) monoton terhadap perluasan interval, dan memenuhi quadrangle inequality (untuk jumlah interval bahkan berupa persamaan). Syarat ini mengizinkan teorema Knuth: dengan konvensi opt sebagai pemisah terbesar yang optimal, `opt[l][r-1] <= opt[l][r] <= opt[l+1][r]`. Batas ini mengurangi kandidat yang harus dicoba. Bukti DP tetap memakai operasi terakhir; optimasi sah karena optimum tidak dikeluarkan dari rentang pencarian.

**Koreksi PPT:** tabel opt kecil yang tampak monoton bukan bukti universal. Bobot negatif melanggar syarat monotonic biaya. Periksa kedua syarat sebelum memakai template. [Syarat formal Knuth](https://cp-algorithms.com/dynamic_programming/knuth-optimization.html).

## Implementasi dan kompleksitas

```text
opt[i][i]=i
for len=2..N:
  for l:
    r=l+len-1
    for k=opt[l][r-1]..min(r-1,opt[l+1][r]):
      relaksasi biaya; pada tie simpan k terbesar
```

C++17 lengkap ada di `../solusi/solution_1.cpp`, fungsi `mergeCost`. Menjumlahkan lebar rentang kandidat sepanjang diagonal menghasilkan batas yang saling menghapus (telescoping), sehingga total O(N²). Dua tabel berukuran N² menyimpan biaya long long dan opt int; N=2000 sekitar48 MB di luar overhead vektor.

## Trace

Untuk [4,1,2,3], biaya rentang panjang2 ialah5,3,5. Panjang3: [4,1,2] bernilai10 (merge1+2 dulu), [1,2,3] bernilai9. Pada rentang penuh, tiga kandidat biaya adalah23,20,20. Jawaban20 dan konvensi tie memilih k=2 dalam indeks0.

## Pemotongan dan lingkaran

Memotong pita dibalik menjadi merge celah di antara posisi potong, termasuk batas0 dan L. Contoh L=10 dan potong2,4,7 memberi bobot celah[2,2,3,3]. Memotong di4 dulu lalu2 dan7 memberi biaya10+4+6=20.

Pada lingkaran, menggandakan array memungkinkan seluruh rotasi sebagai jendela panjang N. Isi hanya panjang<=N; ambil minimum semua jendela awal0..N-1. Jangan menjalankan O(N²) sebanyak N rotasi. N=1 selalu biaya0.

## Jebakan dan checkpoint

- Huffman bebas memilih dua kelompok termurah; ia tidak mematuhi batas bersebelahan.
- Inisialisasikan diagonal opt sebelum panjang2.
- Batasi k<=r-1 agar rentang kanan tidak kosong.
- Batas atas nilai latihan <= (N-1)*sum(a), tetap aman dalam long long.
- Bandingkan dengan enumerasi semua pemisah O(N³) kecil, termasuk nol dan banyak tie.
'''
 write_day(day=270,title='Knuth Optimization dan Quadrangle Inequality',ppt='CP/_PPT-09-DP/Day-248 - Optimasi DP - Divide and Conquer dan Knuth.pptx',objectives=['Membedakan merge bersebelahan dari Huffman.','Memeriksa syarat Knuth dan tie-break opt.','Menerapkan range DP ke pita dan lingkaran.'],prerequisites='Day151 dan Day267.',theory=theory,problems=[p1,p2,p3],tasks=tasks)
if __name__=='__main__':
 build_dc();build_cht();build_li();build_knuth()
