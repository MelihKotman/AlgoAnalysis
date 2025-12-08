import sys

# --- AYARLAR VE GLOBAL DEĞİŞKENLER ---
NODE_NUMBER = 10
# 10x10'luk boş matris (0 ile dolu)
graf = [[0 for _ in range(NODE_NUMBER)] for _ in range(NODE_NUMBER)]


# --- QUEUE YAPISI (C'deki struct ve fonksiyonların karşılığı) ---
class Queue:
    def __init__(self, capacity):
        self.capacity = capacity
        self.items = []

    def is_empty(self):
        return len(self.items) == 0

    def is_full(self):
        return len(self.items) == self.capacity

    def enqueue(self, item):
        if self.is_full():
            print("Ekleme yapilamaz, sira dolu!")
        else:
            self.items.append(item)

    def dequeue(self):
        if self.is_empty():
            print("Sira bos! Program sonlandiriliyor!")
            sys.exit(-1)
        else:
            # Kuyruğun başındaki elemanı al (index 0)
            return self.items.pop(0)


# --- YARDIMCI FONKSİYONLAR ---
def AddEdge(v1, v2):
    graf[v1][v2] = 1
    graf[v2][v1] = 1


def ShowMatris():
    for row in graf:
        print(" ".join(map(str, row)))
    print()


# --- BFS FONKSİYONU  ---
def BFS(start):

    # Kuyruk (Queue) Oluşturma:
    # BFS, o anki düğümün komşularını sıraya koymak için kuyruk kullanır.
    myQueue = Queue(NODE_NUMBER)

    # Ziyaret Edildi Dizisi (Visited Array):
    # Aynı düğüme tekrar tekrar gitmemek için tutulan kayıt.
    # Başlangıçta hepsi 0 (ziyaret edilmedi).
    visited = [0] * (NODE_NUMBER)

    # 1. ADIM: Başlangıç düğümünü kuyruğa ekle.
    myQueue.enqueue(start)

    # 2. ADIM: Kuyruk boşalana kadar döngüye devam et.
    # Kuyrukta eleman olması, hala bakılacak komşular var demektir.
    while(not myQueue.is_empty()):

        # 3. ADIM: Kuyruktan bir eleman al (Dequeue).
        # İlk giren ilk çıkar (FIFO) mantığıyla sıradaki düğümü alıyoruz.
        visited_node = myQueue.dequeue()

        # Alınan düğümü "ziyaret edildi" (1) olarak işaretle.
        visited[visited_node] = 1
        print(f"{visited_node} is visited\n")

        # 4. ADIM: Komşuları Bul ve Kuyruğa Ekle.
        # Matris üzerinde o anki düğümün (visited_node) tüm komşularını geziyoruz.
        for i in range(0,NODE_NUMBER,1):

            # İki şart kontrol edilir:
            # 1. graf[i][visited_node] == 1 -> Aralarında bağlantı var mı?
            # 2. visited[i] == 0 -> Bu komşu daha önce ziyaret edilmemiş mi?
            if graf[i][visited_node] == 1 and visited[i] == 0:

                # Eğer komşuysa ve ziyaret edilmediyse kuyruğa ekle.
                # Bu sayede bir sonraki adımda (veya döngüde) bu komşulara bakılacak.
                myQueue.enqueue(i)

        # Kuyruk boşaldığında, graf üzerinde ulaşılabilecek tüm düğümler seviye seviye gezilmiş olur.


# --- MAIN (ANA) ---
if __name__ == "__main__":

    # 1. ADIM: GRAF YAPISININ OLUŞTURULMASI
    # AddEdge fonksiyonu ile düğümler arasındaki bağlantılar (kenarlar) tanımlanıyor.
    # Bu bir yönsüz graf olduğu için matrise simetrik ekleme yapılır.
    AddEdge(0, 1)  # 0 ile 1 bağlı
    AddEdge(0, 2)  # 0 ile 2 bağlı
    AddEdge(0, 3)  # 0 ile 3 bağlı
    AddEdge(1, 4)  # 1 ile 4 bağlı
    AddEdge(4, 8)  # 4 ile 8 bağlı
    AddEdge(2, 5)  # 2 ile 5 bağlı
    AddEdge(2, 6)  # 2 ile 6 bağlı
    AddEdge(5, 9)  # 5 ile 9 bağlı
    AddEdge(3, 7)  # 3 ile 7 bağlı

    # 2. ADIM: MATRİSİN GÖRÜNTÜLENMESİ
    # Bağlantıların doğru kurulup kurulmadığını görmek için matrisi ekrana basar.
    ShowMatris();

    # 3. ADIM: BFS ALGORİTMASININ BAŞLATILMASI
    # Algoritma 0 numaralı düğümden başlasın diyoruz.
    # Çıktıda 0'dan başlayıp komşularına (derinlemesine) gittiğini göreceksiniz.
    # DİPNOT: İstediğin numaralı düğümden başlayabilirsin.
    print("\n--- BFS Basliyor (Baslangic: 0) ---\n");
    BFS(0)

