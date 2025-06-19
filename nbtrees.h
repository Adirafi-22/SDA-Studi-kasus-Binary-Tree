#ifndef nbtrees_h
#define nbtrees_h

#include "boolean.h"

// Maksimal node yang dapat ditampung dalam array
#define jml_maks 20

// Arah traversal
#define kebawah  1
#define keatas   2
#define kekanan  3
#define nil      0

/***************************/
/*  Type data             */
/***************************/

/* Kamus */

/* Indeks dalam bahasa C dimulai dengan 0; tetapi indeks 0 tidak dipakai */

/* Kamus untuk setiap node */
typedef char infotype; // Tipe data info, bisa diganti karakter atau integer
typedef int address;   // Tipe data untuk posisi

typedef struct {
    infotype info;      // Informasi yang disimpan di node
    address ps_fs;      // Posisi anak pertama
    address ps_nb;      // Posisi saudara berikutnya
    address ps_pr;      // Posisi parent
} nbtree;

typedef nbtree Isi_Tree[jml_maks+1]; // Array untuk menampung semua node

/***************************/
/*  S P E S I F I K A S I  */
/***************************/

void Create_tree(Isi_Tree X, int Jml_Node);
// Create Non Binary Tree sebanyak Jml_Node
// Tujuan mengentrykan Non Binary Tree ke array Isi_Tree dengan pola
// Level Order

boolean IsEmpty (Isi_Tree P);
// Mengirimkan true jika Isi_Tree KOSONG

/***** Traversal *****/

void PreOrder (Isi_Tree P);
// Traversal PreOrder: Parent, fs, nb

void InOrder (Isi_Tree P);
// Traversal InOrder: fs, Parent, Sisa anak lain

void PostOrder (Isi_Tree P);
// Traversal PostOrder: fs, nb, Parent

void Level_order(Isi_Tree X, int Maks_node);
// Traversal LevelOrder

void PrintTree (Isi_Tree P);
// Menampilkan pohon ke layar

/***** Search *****/

boolean Search (Isi_Tree P, infotype X);
// Mengirimkan true jika ada node dari P yang bernilai X

/***** Fungsi Lain *****/

int nbElmt (Isi_Tree P);
// Mengirimkan banyak elemen (node) di pohon non biner P

int nbDaun (Isi_Tree P);
// Mengirimkan banyak daun (node) pohon non biner P

int Level (Isi_Tree P, infotype X);
// Mengirimkan level dari node X yang merupakan salah satu simpul

int Depth (Isi_Tree P);
// Mengirimkan tinggi dari Pohon

int Max (infotype Data1, infotype Data2);
// Mengirimkan Nilai terbesar dari dua data

#endif

