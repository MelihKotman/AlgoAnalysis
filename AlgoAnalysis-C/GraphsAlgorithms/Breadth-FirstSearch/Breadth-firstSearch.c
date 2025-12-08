#include <stdio.h>
#include <stdlib.h>

#define NODE_NUMBER 10

// Kuyruk (Queue) yapısı tanımları
// BFS algoritması "İlk Giren İlk Çıkar" (FIFO) mantığıyla çalıştığı için Kuyruk kullanılır.
typedef struct Queue {
    int front;
    int rear;
    int numberOfElements;
    int capacity;
    int* array;
}Queue;

// Global komşuluk matrisi
int graf[NODE_NUMBER][NODE_NUMBER] = {};

// Yardımcı fonksiyonlar
void AddEdge(int v1,int v2);
void ShowMatris();
void BFS(int start);

// Kuyruk fonksiyon prototipleri
Queue* createQueue(int size);
int isFull(Queue* queue);
int isEmpty(Queue* queue);
void enqueue(Queue* queue, int item);
int dequeue(Queue* queue);

int main(){
    // 1. ADIM: GRAF YAPISININ OLUŞTURULMASI
    // AddEdge ile düğümler arasındaki kenarlar tanımlanır.
    // Matrise 1 yazılarak bağlantı kurulur.
    AddEdge(0,1); // 0 ile 1 bağlı
    AddEdge(0,2); // 0 ile 2 bağlı
    AddEdge(0,3); // 0 ile 3 bağlı
    AddEdge(1,4); // 1 ile 4 bağlı
    AddEdge(4,8); // 4 ile 8 bağlı
    AddEdge(2,5); // 2 ile 5 bağlı
    AddEdge(2,6); // 2 ile 6 bağlı
    AddEdge(5,9); // 5 ile 9 bağlı
    AddEdge(3,7); // 3 ile 7 bağlı

    // 2. ADIM: MATRİSİN GÖRÜNTÜLENMESİ
    // Bağlantıların matris üzerinde doğru olup olmadığını kontrol eder.
    ShowMatris();

    // 3. ADIM: BFS ALGORİTMASININ BAŞLATILMASI
    // Algoritma 0 numaralı düğümden başlasın diyoruz.
    // Çıktıda 0'dan başlayıp, seviye seviye (önce 0'ın komşuları, sonra onların komşuları) ilerlediğini göreceksiniz.
    printf("\n--- BFS Basliyor (Baslangic: 0) ---\n");
    BFS(0);

    return 0;
}

void AddEdge(int v1,int v2)
{
    graf[v1][v2] = 1;
    graf[v2][v1] = 1;
}

void ShowMatris()
{
    int i,j;
    for(i = 0; i < NODE_NUMBER; i++)
    {
        for(j = 0; j < NODE_NUMBER; j++)
        {
            printf("%d ",graf[i][j]);
        }
        printf("\n");
    }
}

// ---------------------------------------------------------
// DETAYLI ANLATIM: BFS FONKSİYONU
// ---------------------------------------------------------
void BFS(int start){
    // Kuyruk (Queue) Oluşturma:
    // BFS, o anki düğümün komşularını sıraya koymak için kuyruk kullanır.
    Queue *myQueue = createQueue(NODE_NUMBER);

    int visited_node; // Kuyruktan o an çıkardığımız ve işleyeceğimiz düğüm.

    // Ziyaret Edildi Dizisi (Visited Array):
    // Aynı düğüme tekrar tekrar gitmemek için tutulan kayıt.
    // Başlangıçta hepsi 0 (ziyaret edilmedi).
    int visited[NODE_NUMBER] = {};

    // 1. ADIM: Başlangıç düğümünü kuyruğa ekle.
    enqueue(myQueue,start);

    // 2. ADIM: Kuyruk boşalana kadar döngüye devam et.
    // Kuyrukta eleman olması, hala bakılacak komşular var demektir.
    while (!isEmpty(myQueue)) {

        // 3. ADIM: Kuyruktan bir eleman al (Dequeue).
        // İlk giren ilk çıkar (FIFO) mantığıyla sıradaki düğümü alıyoruz.
        visited_node = dequeue(myQueue);

        // Alınan düğümü "ziyaret edildi" (1) olarak işaretle.
        // Not: Bu kodda işaretleme kuyruktan çıkarınca yapılıyor.
        // (Daha güvenli yöntem, kuyruğa eklerken işaretlemektir ama bu da çalışır).
        visited[visited_node] = 1;
        printf("%d is visited.\n",visited_node);

        // 4. ADIM: Komşuları Bul ve Kuyruğa Ekle.
        // Matris üzerinde o anki düğümün (visited_node) tüm komşularını geziyoruz.
        for (int i = 0; i < NODE_NUMBER;i++) {

            // İki şart kontrol edilir:
            // 1. graf[i][visited_node] == 1 -> Aralarında bağlantı var mı?
            // 2. visited[i] == 0 -> Bu komşu daha önce ziyaret edilmemiş mi?
            if (graf[i][visited_node] == 1 && visited[i] == 0) {

                // Eğer komşuysa ve ziyaret edilmediyse kuyruğa ekle.
                // Bu sayede bir sonraki adımda (veya döngüde) bu komşulara bakılacak.
                enqueue(myQueue,i);
            }
        }
    }
    // Kuyruk boşaldığında, graf üzerinde ulaşılabilecek tüm düğümler seviye seviye gezilmiş olur.
}

struct Queue* createQueue(int size)
{
    Queue* queue = (Queue*)malloc(sizeof(struct Queue));
    queue->capacity = size;
    queue->front = 0;
    queue->numberOfElements = 0;
    queue->rear = 0;
    queue->array = (int*)malloc(queue->capacity * sizeof(int));
    return queue;
}

int isFull(Queue* queue)
{
    return (queue->numberOfElements == queue->capacity);
}

int isEmpty(Queue* queue)
{
    return (queue->numberOfElements == 0);
}

void enqueue(Queue* queue, int item)
{
    if (isFull(queue))
    {
        printf("Ekleme yapilamaz, sira dolu!\n");
        return;
    }
    queue->array[queue->rear] = item;
    queue->rear = (queue->rear + 1) % queue->capacity;
    queue->numberOfElements = queue->numberOfElements + 1;
}

int dequeue(struct Queue* queue)
{
    if (isEmpty(queue))
    {
        printf("Sira bos! Program sonlandiriliyor!\n");
        exit(-1);
    }
    int item = queue->array[queue->front];
    queue->front = (queue->front + 1) % queue->capacity;
    queue->numberOfElements = queue->numberOfElements - 1;
    return item;
}