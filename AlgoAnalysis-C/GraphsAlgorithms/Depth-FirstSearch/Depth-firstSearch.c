#include <stdio.h>
#include <stdlib.h>

#define NODE_NUMBER 10

// Yığın (Stack) yapısı tanımları
typedef struct stack
{
    int capacity;
    int top;
    int* items;
}stack;

// Stack fonksiyon prototipleri
stack* NewStack(int size);
int StackEmpty(stack* pt);
int StackFull(stack* pt);
void Push(int element, stack* pt);
int Pop(stack* pt);

// Global komşuluk matrisi (0: Kenar yok, 1: Kenar var)
int graf[NODE_NUMBER][NODE_NUMBER] = {};

// Yardımcı fonksiyonlar
void AddEdge(int v1,int v2);
void ShowMatris();
void DFS(int start);

int main(){
    // 1. ADIM: GRAF YAPISININ OLUŞTURULMASI
    // AddEdge fonksiyonu ile düğümler arasındaki bağlantılar (kenarlar) tanımlanıyor.
    // Bu bir yönsüz graf olduğu için matrise simetrik ekleme yapılır.
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
    // Bağlantıların doğru kurulup kurulmadığını görmek için matrisi ekrana basar.
    ShowMatris();

    // 3. ADIM: DFS ALGORİTMASININ BAŞLATILMASI
    // Algoritma 0 numaralı düğümden başlasın diyoruz.
    // Çıktıda 0'dan başlayıp komşularına (derinlemesine) gittiğini göreceksiniz.
    // DİPNOT: İstediğin numaralı düğümden başlayabilirsin.
    printf("\n--- DFS Basliyor (Baslangic: 0) ---\n");
    DFS(0);

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
// DETAYLI ANLATIM: DFS FONKSİYONU
// Kaynak: Ders Notları Sayfa 8 (DFS Algoritması Adımları)
// ---------------------------------------------------------
void DFS(int start){
    // Yığın (Stack) Oluşturma:
    // DFS mantığı gereği, gidilecek düğümleri hafızada tutmak için yığın kullanılır.
    stack *myStack = NewStack(NODE_NUMBER);

    int visited_node; // Yığından o an çıkardığımız ve işleyeceğimiz düğüm.

    // Ziyaret Edildi Dizisi (Visited Array):
    // Döngüye girmemek için hangi düğümlere daha önce gittiğimizi not etmeliyiz.
    // Başlangıçta hepsi 0 (ziyaret edilmedi).
    int visited[NODE_NUMBER] = {};

    // 1. ADIM: Başlangıç düğümünü yığına ekle.
    Push(start,myStack);

    // 2. ADIM: Yığın boşalana kadar döngüye devam et.
    // Yığında eleman olması, hala gidilebilecek veya geri dönüp bakılacak yollar var demektir.
    while (!StackEmpty(myStack)) {

        // 3. ADIM: Yığından bir eleman al (Pop) ve onu işle.
        // En son eklenen düğümü (LIFO mantığı) alıyoruz.
        visited_node = Pop(myStack);

        // Alınan düğümü "ziyaret edildi" (1) olarak işaretle.
        // Eğer bu düğüm daha önce işlenmediyse ekrana yazdırırız.
        visited[visited_node] = 1;
        printf("%d is visited.\n", visited_node);


        // 4. ADIM: Komşuları Bul ve Yığına Ekle.
        // Matris üzerinde o anki düğümün (visited_node) tüm sütunlarını geziyoruz.
        // Döngünün tersten (NODE_NUMBER - 1'den 0'a) dönmesinin sebebi:
        // Stack tersine (LIFO) çalıştığı için, küçük numaralı komşunun (örn: 0)
        // stack'in en üstünde kalmasını ve ilk onun ziyaret edilmesini sağlamaktır.
        for (int i = NODE_NUMBER - 1; i >= 0; i--) {

            // İki şart kontrol edilir:
            // 1. graf[i][visited_node] == 1 -> Aralarında bir kenar (bağlantı) var mı?
            // 2. visited[i] == 0 -> Bu komşu daha önce ziyaret edilmemiş mi?
            if (graf[i][visited_node] == 1 && visited[i] == 0) {

                // Eğer komşuysa ve ziyaret edilmediyse yığına ekle.
                Push(i,myStack);
            }
        }
    }
    // Yığın boşaldığında (StackEmpty), gidilebilecek tüm düğümler gezilmiş demektir.
}


stack* NewStack(int size)
{
    struct stack *pt = (stack*)malloc(sizeof(stack));

    pt->capacity = size;
    pt->top = -1;
    pt->items = (int*)malloc(sizeof(int) * size);

    return pt;
}

int StackEmpty(stack *pt)
{
    return (pt->top == -1);
}

int StackFull(stack *pt)
{
    return (pt->top == pt->capacity-1);
}

void Push(int element, stack* pt)
{
    if(StackFull(pt))
    {
        printf("Stack doldu! Yeni eleman eklenemez!\n");
    }
    else
    {
        pt->top++;
        pt->items[pt->top] = element;
        //        printf("%d elemani eklendi\n",element);
    }
}

int Pop(stack* pt)
{
    if(StackEmpty(pt))
    {
        printf("Stack bos!\n");
        exit(-1);
    }
    else
    {
        pt->top--;
        //        printf("%d elemani siliniyor.\n",pt->items[pt->top+1]);
        return pt->items[pt->top+1];
    }
}