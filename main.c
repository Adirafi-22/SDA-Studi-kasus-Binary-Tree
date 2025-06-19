#include <stdio.h>
#include "nbtrees.h"

int main() {
    Isi_Tree tree;   
    int jml_node = 10; // Jumlah node untuk pohon ini adalah 10

    // Membuat pohon dengan jumlah node yang dimasukkan
    Create_tree(tree, jml_node);

    // Input data untuk setiap node
    // Node A - Root (Level 0)
    tree[1].info = 'A';
    tree[1].ps_fs = 2;  // Anak pertama dari A adalah B
    tree[1].ps_nb = 0;  // Tidak ada saudara untuk root
    tree[1].ps_pr = 0;  // Tidak ada parent karena A adalah root

    // Node B - Level 1 (Anak dari A)
    tree[2].info = 'B';
    tree[2].ps_fs = 4;  // Anak pertama dari B adalah D
    tree[2].ps_nb = 3;  // Saudara berikutnya dari B adalah C
    tree[2].ps_pr = 1;  // Parent dari B adalah A

    // Node C - Level 1 (Anak dari A)
    tree[3].info = 'C';
    tree[3].ps_fs = 6;  // Anak pertama dari C adalah F
    tree[3].ps_nb = 0;  // Tidak ada saudara berikutnya dari C
    tree[3].ps_pr = 1;  // Parent dari C adalah A

    // Node D - Level 2 (Anak dari B)
    tree[4].info = 'D';
    tree[4].ps_fs = 0;  // Tidak ada anak
    tree[4].ps_nb = 5;  // Saudara berikutnya dari D adalah E
    tree[4].ps_pr = 2;  // Parent dari D adalah B

    // Node E - Level 2 (Anak dari B)
    tree[5].info = 'E';
    tree[5].ps_fs = 9;  // Anak pertama dari E adalah I
    tree[5].ps_nb = 0;  // Tidak ada saudara berikutnya
    tree[5].ps_pr = 2;  // Parent dari E adalah B

    // Node F - Level 2 (Anak dari C)
    tree[6].info = 'F';
    tree[6].ps_fs = 0;  // Tidak ada anak
    tree[6].ps_nb = 7;  // Saudara berikutnya dari F adalah G
    tree[6].ps_pr = 3;  // Parent dari F adalah C

    // Node G - Level 2 (Anak dari C)
    tree[7].info = 'G';
    tree[7].ps_fs = 0;  // Tidak ada anak
    tree[7].ps_nb = 8;  // Saudara berikutnya dari G adalah H
    tree[7].ps_pr = 3;  // Parent dari G adalah C

    // Node H - Level 2 (Anak dari C)
    tree[8].info = 'H';
    tree[8].ps_fs = 0;  // Tidak ada anak
    tree[8].ps_nb = 0;  // Tidak ada saudara berikutnya
    tree[8].ps_pr = 3;  // Parent dari H adalah C

    // Node I - Level 3 (Anak dari E)
    tree[9].info = 'I';
    tree[9].ps_fs = 0;  // Tidak ada anak
    tree[9].ps_nb = 10; // Saudara berikutnya dari I adalah J
    tree[9].ps_pr = 5;  // Parent dari I adalah E

    // Node J - Level 3 (Anak dari E)
    tree[10].info = 'J';
    tree[10].ps_fs = 0; // Tidak ada anak
    tree[10].ps_nb = 0; // Tidak ada saudara berikutnya
    tree[10].ps_pr = 5; // Parent dari J adalah E

    // Menampilkan pohon secara visual
    printf("\nPohon yang ditampilkan:\n");
    PrintTree(tree);
    
    // Tampilkan level setiap node
    printf("\nLevel dari setiap node:\n");
    printf("Node A: Level %d\n", Level(tree, 'A'));
    printf("Node B: Level %d\n", Level(tree, 'B'));
    printf("Node C: Level %d\n", Level(tree, 'C'));
    printf("Node D: Level %d\n", Level(tree, 'D'));
    printf("Node E: Level %d\n", Level(tree, 'E'));
    printf("Node F: Level %d\n", Level(tree, 'F'));
    printf("Node G: Level %d\n", Level(tree, 'G'));
    printf("Node H: Level %d\n", Level(tree, 'H'));
    printf("Node I: Level %d\n", Level(tree, 'I'));
    printf("Node J: Level %d\n", Level(tree, 'J'));
    
    // Menampilkan hasil traversal
    printf("\nTraversal PreOrder: ");
    PreOrder(tree);
    
    printf("Traversal InOrder: ");
    InOrder(tree);
    
    printf("Traversal PostOrder: ");
    PostOrder(tree);
    
    printf("Traversal Level Order: ");
    Level_order(tree, jml_node);
    
    printf("\nJumlah node: %d\n", nbElmt(tree));
    printf("Jumlah daun: %d\n", nbDaun(tree));
    printf("Kedalaman pohon: %d\n", Depth(tree));

    return 0;
}
