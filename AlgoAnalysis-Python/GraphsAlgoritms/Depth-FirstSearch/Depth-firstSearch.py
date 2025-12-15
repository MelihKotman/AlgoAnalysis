import sys

# --- AYARLAR VE GLOBAL DEĞİŞKENLER ---
NODE_NUMBER = 10
# 10x10'luk boş matris (0 ile dolu)
graf = [[0 for _ in range(NODE_NUMBER)] for _ in range(NODE_NUMBER)]


# --- STACK YAPISI (C'deki struct ve fonksiyonların karşılığı) ---
class Stack:
    def __init__(self, capacity):
        self.capacity = capacity
        self.items = []

    def is_empty(self):
        return len(self.items) == 0

    def is_full(self):
        return len(self.items) == self.capacity

    def push(self, element):
        if self.is_full():
            print("Stack doldu! Yeni eleman eklenemez!")
        else:
            self.items.append(element)

    def pop(self):
        if self.is_empty():
            print("Stack bos!")
            sys.exit(-1)
        else:
            return self.items.pop()


# --- YARDIMCI FONKSİYONLAR ---
def AddEdge(v1, v2):
    graf[v1][v2] = 1
    graf[v2][v1] = 1


def ShowMatris():
    for row in graf:
        # Listeyi yan yana yazdırmak için
        print(" ".join(map(str, row)))
    print()


# --- DFS FONKSİYONU  ---
def DFS(start):

    # Yığın (Stack) Oluşturma:
    # DFS mantığı gereği, gidilecek düğümleri hafızada tutmak için yığın kullanılır.
    myStack = Stack(NODE_NUMBER)

    # Ziyaret Edildi Dizisi (Visited Array):
    # Döngüye girmemek için hangi düğümlere daha önce gittiğimizi not etmeliyiz.
    # Başlangıçta hepsi 0 (ziyaret edilmedi).
    visited = [0] * (NODE_NUMBER)

    # 1. ADIM: Başlangıç düğümünü yığına ekle.
    myStack.push(start)
    # 2. ADIM: Yığın boşalana kadar döngüye devam et.
    # Yığında eleman olması, hala gidilebilecek veya geri dönüp bakılacak yollar var demektir.
    while (not myStack.is_empty()):

        # 3. ADIM: Yığından bir eleman al (Pop) ve onu işle.
        # En son eklenen düğümü (LIFO mantığı) alıyoruz.
        visited_node = myStack.pop()

        # Alınan düğümü "ziyaret edildi" (1) olarak işaretle.
        # Eğer bu düğüm daha önce işlenmediyse ekrana yazdırırız.
        visited[visited_node] = 1
        print(f"{visited_node} is visited\n")

        # 4. ADIM: Komşuları Bul ve Yığına Ekle.
        # Matris üzerinde o anki düğümün (visited_node) tüm sütunlarını geziyoruz.
        # Döngünün tersten (NODE_NUMBER - 1'den 0'a) dönmesinin sebebi:
        # Stack tersine (LIFO) çalıştığı için, küçük numaralı komşunun (örn: 0)
        # stack'in en üstünde kalmasını ve ilk onun ziyaret edilmesini sağlamaktır.
        for i in range(NODE_NUMBER - 1,-1,-1):

            # İki şart kontrol edilir:
            # 1. graf[i][visited_node] == 1 -> Aralarında bir kenar (bağlantı) var mı?
            # 2. visited[i] == 0 -> Bu komşu daha önce ziyaret edilmemiş mi?
            if graf[i][visited_node] == 1 and visited[i] == 0:

                # Eğer komşuysa ve ziyaret edilmediyse yığına ekle.
                myStack.push(i)

        # Yığın boşaldığında (StackEmpty), gidilebilecek tüm düğümler gezilmiş demektir.


# --- MAIN (ANA) ---
if __name__ == "__main__":

    # 1. ADIM: GRAF YAPISININ OLUŞTURULMASI
    # AddEdge fonksiyonu ile düğümler arasındaki bağlantılar (kenarlar) tanımlanıyor.
    # Bu bir yönsüz graf olduğu için matrise simetrik ekleme yapılır.
    AddEdge(0,1) # 0 ile 1 bağlı
    AddEdge(0,2) # 0 ile 2 bağlı
    AddEdge(0,3) # 0 ile 3 bağlı
    AddEdge(1,4) # 1 ile 4 bağlı
    AddEdge(4,8) # 4 ile 8 bağlı
    AddEdge(2,5) # 2 ile 5 bağlı
    AddEdge(2,6) # 2 ile 6 bağlı
    AddEdge(5,9) # 5 ile 9 bağlı
    AddEdge(3,7) # 3 ile 7 bağlı

    # 2. ADIM: MATRİSİN GÖRÜNTÜLENMESİ
    # Bağlantıların doğru kurulup kurulmadığını görmek için matrisi ekrana basar.
    ShowMatris();

    # 3. ADIM: DFS ALGORİTMASININ BAŞLATILMASI
    # Algoritma 0 numaralı düğümden başlasın diyoruz.
    # Çıktıda 0'dan başlayıp komşularına (derinlemesine) gittiğini göreceksiniz.
    # DİPNOT: İstediğin numaralı düğümden başlayabilirsin.
    print("\n--- DFS Basliyor (Baslangic: 0) ---\n");
    DFS(0)

