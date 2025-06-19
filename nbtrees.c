#include <stdio.h>
#include <stdlib.h>
#include "nbtrees.h"

/***************************/
/*  Fungsi Utama          */
/***************************/

void Create_tree(Isi_Tree X, int Jml_Node) {
    int i;
    for (i = 1; i <= Jml_Node; i++) {
        X[i].info = ' ';   
        X[i].ps_fs = 0;    
        X[i].ps_nb = 0;    
        X[i].ps_pr = 0;    
    }
}

boolean IsEmpty(Isi_Tree P) {
    return (P[1].info == ' '); // Memeriksa apakah pohon kosong
}

// Fungsi pembantu untuk penelusuran PreOrder
void PreOrderHelper(Isi_Tree P, int idxNode) {
    if (idxNode == nil) return;  // Kasus dasar
    
    // Kunjungi node induk terlebih dahulu
    printf("%c ", P[idxNode].info);
    
    // Kunjungi anak pertama
    if (P[idxNode].ps_fs != nil) 
        PreOrderHelper(P, P[idxNode].ps_fs);
    
    // Kunjungi saudara berikutnya
    if (P[idxNode].ps_nb != nil) 
        PreOrderHelper(P, P[idxNode].ps_nb);
}

void PreOrder(Isi_Tree P) {
    PreOrderHelper(P, 1);  // mulai dari akar (indeks 1)
    printf("\n");
}

// Fungsi pembantu untuk penelusuran InOrder yang diperbaiki
void InOrderHelper(Isi_Tree P, int idxNode) {
    if (idxNode == nil) return;  

    // Simpan anak pertama
    int firstChild = P[idxNode].ps_fs;
    
    // 1. Kunjungi anak pertama
    if (firstChild != nil) {
        InOrderHelper(P, firstChild);
    }
    
    // 2. Kunjungi node induk
    printf("%c ", P[idxNode].info);
    
    // 3. Kunjungi sisa anak lain (saudara dari anak pertama)
    if (firstChild != nil) {
        int sibling = P[firstChild].ps_nb;
        while (sibling != nil) {
            InOrderHelper(P, sibling);
            sibling = P[sibling].ps_nb;
        }
    }
}

void InOrder(Isi_Tree P) {
    InOrderHelper(P, 1);  // mulai dari akar
    printf("\n");
}

// Fungsi pembantu untuk penelusuran PostOrder
void PostOrderHelper(Isi_Tree P, int idxNode) {
    if (idxNode == nil) return;  // Kasus dasar
    
    // Kunjungi anak pertama
    if (P[idxNode].ps_fs != nil) 
        PostOrderHelper(P, P[idxNode].ps_fs);
    
    // Kunjungi saudara berikutnya
    if (P[idxNode].ps_nb != nil) 
        PostOrderHelper(P, P[idxNode].ps_nb);
    
    // Setelah anak dan saudara, baru kunjungi node induk
    printf("%c ", P[idxNode].info);
}


void PostOrder(Isi_Tree P) {
    PostOrderHelper(P, 1);  
    printf("\n");
}

// Fungsi untuk penelusuran Level Order yang diperbaiki
void Level_order(Isi_Tree P, int Maks_node) {
    // Gunakan array sebagai implementasi antrian
    int queue[jml_maks];
    int front = 0, rear = 0;
    
    // Periksa jika pohon kosong
    if (IsEmpty(P)) {
        printf("Pohon kosong\n");
        return;
    }
    
    // Masukkan akar ke antrian
    queue[rear++] = 1; // Akar selalu di indeks 1
    
    while (front < rear) {
        // Keluarkan node saat ini dari antrian
        int current = queue[front++];
        
        // Cetak info node
        printf("%c ", P[current].info);
        
        // Masukkan semua anak dari node saat ini ke antrian
        int child = P[current].ps_fs;
        while (child != nil) {
            queue[rear++] = child;
            child = P[child].ps_nb;
        }
    }
    
    printf("\n");
}

// Fungsi untuk mencetak spasi
void printSpaces(int count) {
    int i;
    for (i = 0; i < count; i++) {
        printf(" ");
    }
}

// Fungsi PrintTree yang diperbaiki untuk menampilkan pohon secara visual
void PrintTree(Isi_Tree P) {
    if (IsEmpty(P)) {
        printf("Pohon kosong\n");
        return;
    }
    
    // Hitung kedalaman pohon untuk menentukan lebar
    int depth = Depth(P);
    
    // Membuat array karakter 2D untuk merepresentasikan visualisasi pohon
    // dimensi berdasarkan kedalaman
    int rows = (depth + 1) * 2;                 // Setiap level mendapat 2 baris (untuk node dan konektor)
    int cols = (1 << (depth + 1)) * 2 - 1;      // Lebar tumbuh secara eksponensial dengan kedalaman
    
    // Membuat dan menginisialisasi array tampilan dengan spasi
    char display[rows][cols + 1];  // +1 untuk terminator null
    int i, j;
    
    for (i = 0; i < rows; i++) {
        for (j = 0; j < cols; j++) {
            display[i][j] = ' ';
        }
        display[i][cols] = '\0';  // Null-terminate setiap baris
    }
    
    // Hitung posisi horizontal untuk setiap level
    int levelWidth[depth + 1];
    for (i = 0; i <= depth; i++) {
        levelWidth[i] = cols / (1 << i);
    }
    
    // Antrian untuk penelusuran level-order
    int queue[jml_maks];
    int posQueue[jml_maks];  // Untuk menyimpan posisi horizontal
    int parentPosQueue[jml_maks];  // Untuk menyimpan posisi induk
    int front = 0, rear = 0;
    
    // Masukkan akar dengan posisi yang dihitung
    queue[rear] = 1;  // Indeks akar
    posQueue[rear] = cols / 2;  // Akar di tengah
    parentPosQueue[rear] = -1;  // Tidak ada induk untuk akar
    rear++;
    
    int currentLevel = 0;
    int nodeCount = 0;
    int nodesAtCurrentLevel = 1;
    int nextLevelNodes = 0;
    
    // Lakukan penelusuran level-order dan isi array tampilan
    while (front < rear) {
        int current = queue[front];
        int pos = posQueue[front];
        int parentPos = parentPosQueue[front];
        front++;
        
        nodeCount++;
        
        // Tempatkan node ini di tampilan
        int row = currentLevel * 2;
        
        // Tempatkan karakter node
        display[row][pos] = P[current].info;
        
        // Gambar koneksi ke induk jika bukan akar
        if (parentPos != -1) {
            int parentRow = (currentLevel - 1) * 2;
            int r = parentRow + 1;  // Baris garis antara induk dan saat ini
            
            // Tentukan arah koneksi (kiri atau kanan)
            if (pos < parentPos) {
                // Koneksi ke kiri
                for (j = pos + 1; j < parentPos; j++) {
                    display[r][j] = '-';
                }
                display[r][pos] = '/';
            } else if (pos > parentPos) {
                // Koneksi ke kanan
                for (j = parentPos + 1; j < pos; j++) {
                    display[r][j] = '-';
                }
                display[r][pos] = '\\';
            } else {
                // Koneksi vertikal (jarang dalam pohon non-biner tapi mungkin)
                display[r][pos] = '|';
            }
        }
        
        // Masukkan anak-anak ke antrian
        int child = P[current].ps_fs;  // Anak pertama
        int childCount = 0;
        
        while (child != nil) {
            childCount++;
            nextLevelNodes++;
            
            // Hitung posisi untuk anak ini
            int childPos;
            
            // Hitung jarak antar saudara pada level berikutnya
            int spacing = levelWidth[currentLevel + 1];
            int offset = childCount * spacing;
            
            // Jika ini anak pertama, pusatkan di bawah induk
            // Jika tidak, posisikan di sebelah kanan saudaranya
            if (childCount == 1) {
                childPos = pos - (spacing * (0.5 * GetChildCount(P, current) - 0.5));
            } else {
                childPos = posQueue[rear - 1] + spacing;
            }
            
            // Pastikan posisi valid
            if (childPos < 0) childPos = 0;
            if (childPos >= cols) childPos = cols - 1;
            
            // Masukkan anak ini ke antrian
            queue[rear] = child;
            posQueue[rear] = childPos;
            parentPosQueue[rear] = pos;
            rear++;
            
            // Pindah ke saudara berikutnya
            child = P[child].ps_nb;
        }
        
        // Periksa apakah kita telah menyelesaikan level saat ini
        if (nodeCount == nodesAtCurrentLevel) {
            currentLevel++;
            nodeCount = 0;
            nodesAtCurrentLevel = nextLevelNodes;
            nextLevelNodes = 0;
        }
    }
    
    // Cetak visualisasi pohon
    for (i = 0; i < rows; i++) {
        // Hanya cetak baris yang memiliki konten
        int hasContent = 0;
        for (j = 0; j < cols; j++) {
            if (display[i][j] != ' ') {
                hasContent = 1;
                break;
            }
        }
        
        if (hasContent) {
            printf("%s\n", display[i]);
        }
    }
}

// Fungsi pembantu untuk menghitung jumlah anak dari sebuah node
int GetChildCount(Isi_Tree P, int nodeIdx) {
    if (nodeIdx == nil || P[nodeIdx].ps_fs == nil) {
        return 0;
    }
    
    int count = 0;
    int child = P[nodeIdx].ps_fs;
    
    while (child != nil) {
        count++;
        child = P[child].ps_nb;
    }
    
    return count;
}

/***** Pencarian *****/

boolean Search(Isi_Tree P, infotype X) {
    int i;
    for (i = 1; i <= jml_maks; i++) {
        if (P[i].info == X) {
            return true;
        }
    }
    return false;
}

/***** Fungsi Lain *****/

int nbElmt(Isi_Tree P) {
    int count = 0, i;
    for (i = 1; i <= jml_maks; i++) {
        if (P[i].info != ' ' && P[i].info != 0) {
            count++;
        }
    }
    return count;
}

int nbDaun(Isi_Tree P) {
    int count = 0, i;
    for (i = 1; i <= jml_maks; i++) {
        if (P[i].info != ' ' && P[i].info != 0 && P[i].ps_fs == 0) {
            count++;
        }
    }
    return count;
}

// Menghitung level node dari X dengan pendekatan rekursif
int LevelHelper(Isi_Tree P, int currentNode, infotype X, int currentLevel) {
    if (currentNode == nil) return -1;  // Node tidak ditemukan
    
    if (P[currentNode].info == X) {
        return currentLevel;  // Node ditemukan
    }
    
    // Cari di anak pertama
    int result = LevelHelper(P, P[currentNode].ps_fs, X, currentLevel + 1);
    if (result != -1) return result;
    
    // Cari di saudara
    return LevelHelper(P, P[currentNode].ps_nb, X, currentLevel);
}

int Level(Isi_Tree P, infotype X) {
    return LevelHelper(P, 1, X, 0);  // Mulai dari akar dengan level 0
}

// Menghitung kedalaman maksimum pohon dengan pendekatan rekursif
int DepthHelper(Isi_Tree P, int currentNode) {
    if (currentNode == nil) return -1;
    
    // Hitung kedalaman maksimum untuk anak-anak
    int maxChildDepth = -1;
    int child = P[currentNode].ps_fs;
    while (child != nil) {
        int childDepth = DepthHelper(P, child);
        if (childDepth > maxChildDepth) {
            maxChildDepth = childDepth;
        }
        child = P[child].ps_nb;
    }
    
    return maxChildDepth + 1;  // Kedalaman node saat ini
}

int Depth(Isi_Tree P) {
    return DepthHelper(P, 1);  // Mulai dari akar
}

int Max(infotype Data1, infotype Data2) {
    return (Data1 > Data2) ? Data1 : Data2;
}
