//dijkstra udah.

#include <stdio.h>
#include <stdlib.h>

#define max 20
#define INF 999

int jmlh_simpul = 0, jmlh_sisi = 0;
int graf1[max][max], graf2[max][max]; //graf1 sebagai input, graf2 sebagai output

//pilihan yaa wkwwk
char nama_simpul[max];
int pil_nama_simpul = 0;
int tampil_sisi_simpul = 0;
int input_sisi_simpul = 1;



/////definisikan fungsi 
void tampilkan_hasil_graf(int pil9);


//agloritma tsp
//agloritma kruskal
int find(int parents[],int nosimpul)
{
	return(parents[nosimpul]);
}
 
void union1(int parents[],int c1,int c2)
{	
	for(int i=0;i<jmlh_simpul;i++)
		if(parents[i]==c2)
			parents[i]=c1;
}

void kruskal()
{
	typedef struct sisi
	{
		int u,v,w;
	}sisi;
 
	typedef struct graf
	{
		sisi data[max];
		int n;
	}graf;
 
	graf g;
	graf g_hasil;

	int parents[max],cno1,cno2;
	g.n=0;
 
	for(int i=1;i<jmlh_simpul;i++)
		for(int j=0;j<i;j++)
		{
			if(graf1[i][j]!=0)
			{
				g.data[g.n].u=i;
				g.data[g.n].v=j;
				g.data[g.n].w=graf1[i][j];
				g.n++;
			}
		}
 
	//sorting bubble sort
	sisi temp;
	
	for(int i=1;i<g.n;i++)
		for(int j=0;j<g.n-1;j++)
			if(g.data[j].w>g.data[j+1].w)
			{
				temp=g.data[j];
				g.data[j]=g.data[j+1];
				g.data[j+1]=temp;
			} 
	
	for(int i=0;i<jmlh_simpul;i++)
		parents[i]=i;
	
	g_hasil.n=0;
	
	for(int i=0;i<g.n;i++)
	{
		cno1=find(parents,g.data[i].u);
		cno2=find(parents,g.data[i].v);
		
		if(cno1!=cno2)
		{
			g_hasil.data[g_hasil.n]=g.data[i];
			g_hasil.n++;
			union1(parents,cno1,cno2);
		}
	}
	
	int jarak=0; 
	
	puts("\n\nMenampilkan Cost Pohon (MST) : ");
	for(int i=0;i<g_hasil.n;i++)
	{
		jarak=jarak+g_hasil.data[i].w;
	}
	
	
	for(int i=0; i<jmlh_simpul; ++i){
		for(int j=0; j<jmlh_simpul; ++j){
			graf2[i][j]=0; 
			}
		}	
	for(int i=0; i<g_hasil.n; ++i){ //mengubah ke bentuk matriks
			 graf2[g_hasil.data[i].u][g_hasil.data[i].v]=g_hasil.data[i].w;
			 graf2[g_hasil.data[i].v][g_hasil.data[i].u]=g_hasil.data[i].w;
		}
	printf("\n\nJarak minimal pohon adalah = %d",jarak);
	tampilkan_hasil_graf(tampil_sisi_simpul);
}

//agloritma prim
void prims()
{
	int u,v,jarmin,jarak[max],sebelum[max];
	int dikunjungi[max],totaljarmin;
	
	int ulang=0;
			
	jarak[0]=0;
	dikunjungi[0]=1;
	
	for(int i=1;i<jmlh_simpul;i++)
	{
		jarak[i]=graf1[0][i];
		sebelum[i]=0;
		dikunjungi[i]=0;
	}
	
	totaljarmin=0;	
	while(ulang<jmlh_simpul-1)
	{
		jarmin=INF;
		for(int i=1;i<jmlh_simpul;i++)
			if(dikunjungi[i]==0&&jarak[i]<jarmin)
			{
				v=i;
				jarmin=jarak[i];
			}
			
		u=sebelum[v];
		
		graf2[u][v]=jarak[v];
		graf2[v][u]=jarak[v];

		ulang++;
		dikunjungi[v]=1;
		
		for(int i=1;i<jmlh_simpul;i++){
			if(dikunjungi[i]==0 && graf1[i][v]<jarak[i])
			{
				jarak[i]=graf1[i][v];
				sebelum[i]=v;
			}
		}
		totaljarmin=totaljarmin+graf1[u][v];
	}
	
	printf("\n\nJarak minimal pohon adalah = %d",totaljarmin);
	tampilkan_hasil_graf(tampil_sisi_simpul);
}


//untuk short path (agloritma djikstra)
void dijkstra(){
	int dikunjungi[max], jarak_min, sim_sel;
	int jarak[max], sebelum[max];
	int asal;
	int z=0;
	char asalc;
	
	printf("Masukkan simpul asal :");
	if(pil_nama_simpul == 1){
		fflush(stdin);
		scanf("%c", &asalc);
		fflush(stdin);
		asal =(char) asalc - 97;
		fflush(stdin);
		}
	else{
		scanf("%d", &asal);
		}
	asal = asal-1;

	//inisialisai
	for(int i=0; i<jmlh_simpul; ++i){
		jarak[i]=graf1[asal][i];
		sebelum[i]=asal;
		dikunjungi[i]=0;
		}
	jarak[asal]=0;
	dikunjungi[asal]=1;
	
	for(int i=1; i<jmlh_simpul-1; ++i){
		//mencari simpul selanjutnya
		jarak_min=INF;
		for(int j=0; j<jmlh_simpul; ++j){
			if(jarak[j]<jarak_min&&!dikunjungi[j]){
				jarak_min=jarak[j];
				sim_sel=j;
				}
			}
		
		//mengisi tiap simpul dengan jarak terdekatnya
		dikunjungi[sim_sel]=1;
		for(int j=0; j<jmlh_simpul; ++j){
			if(!dikunjungi[j]){
				if(jarak_min+graf1[sim_sel][j]<jarak[j]){
					jarak[j]= jarak_min+graf1[sim_sel][j];
					sebelum[j]=sim_sel;
					}
				}
			}
		}
		
		//menampilkan output
		for(int i=0;i<jmlh_simpul; ++i){
			if(i!=asal)
			{
				if(pil_nama_simpul==1){
					printf("\nJarak Minimum simpul %c adalah %d",nama_simpul[i], jarak[i]);
					printf("\nLintasannya %c",nama_simpul[i]);
					z=i;
					do
					{
						z=sebelum[z];
						printf(" <- %c",nama_simpul[z]);
					}while(z!=asal);
				}
				else{printf("\nJarak Minimum simpul %d adalah %d",i,jarak[i]);
					printf("\nLintasannya %d",i);
					z=i;
					do
					{
						z=sebelum[z];
						printf(" <- %d",z);
					}while(z!=asal);
					
					}
			}
		}
		puts("");
	}

int balik_nol_satu(int key){
	if(key == 1){
		return 0;
		}
	else{
		return 1;
		}
	}











void input_jmlh_simpul(){
	printf("Masukkan jumlah simpul : ");
	scanf("%d", &jmlh_simpul);
	printf("**Data jumlah simpul berhasil dimasukkan**\n");
	}

void input_jmlh_sisi(){
	printf("Masukkan jumlah sisi : ");
	scanf("%d", &jmlh_sisi);
	printf("**Data jumlah sisi berhasil dimasukkan**\n");
	}

void nilai_nol_array(){
	for(int i =0; i<max; i++){
		for(int j=0; j<max; j++){
			}
		}
	}
	
void ganti_nama_simpul(){
	int pil =0 ;
	
	printf("Tampilkan simbol simpul berupa (1)huruf atau (2)angka ? ");
	scanf("%d", &pil);
	if(pil==1){
		for(int i=0; i<max; ++i){
			nama_simpul[i]=97+i;}
			pil_nama_simpul = 1;
			puts("** Simbol simpul dimulai dari huruf a. **");
		}
	else{
		    puts("** Simbol simpul dimulai dari angka 1 . **");
		}
	}

void input_ketanggaan(){
	nilai_nol_array();
	printf("-          ");
	for(int i=0; i<jmlh_simpul; ++i){
		if(pil_nama_simpul==1){
			printf("%c ", nama_simpul[i]);}
		else{printf("%d ", i+1);}
		}
	printf("\n");
	printf("\n");
	for(int i=0;i<jmlh_simpul;++i)
	{
		if(pil_nama_simpul==1){
			printf("Simpul %c : ", nama_simpul[i]);}
		else{
			printf("Simpul %d : ", i+1);}
		
		for(int j=0;j<jmlh_simpul;++j)
		{
			scanf("%d",&graf1[i][j]);
			if(graf1[i][j]==0){
				graf1[i][j]=INF;}
			}
		}
	}

void input_bersisian(){			
	int bobot = 0, simpul1, simpul2;
	char simpul1c, simpul2c;
	input_jmlh_sisi();
	nilai_nol_array();
	for(int i = 0; i<max; i++){
		for(int j=0; j<max; j++){
			graf1[i][j] = INF;
			}}
	printf("Masukkan data simpul-simpul yang terhubung (S-S=Bobot) : ");
	if(pil_nama_simpul==1){
		printf("\nContoh : a b 20 [enter]\n");
		}
	else{
		printf("\nContoh : 1 2 20 [enter]\n");
		}
	for(int i= 0; i<jmlh_sisi; i++){
		if(pil_nama_simpul==1){
			fflush(stdin);
			scanf("%c %c %d", &simpul1c, &simpul2c, &bobot);
			fflush(stdin);
			printf("Berhasil\n");
			simpul1 = (char) simpul1c - 97;
			simpul2 = (char) simpul2c - 97;
			}
		else{
			scanf("%d %d %d", &simpul1, &simpul2, &bobot);
			simpul1--;
			simpul2--;
			printf("Berhasil\n");
			
		}
		graf1[simpul1][simpul2] = bobot;
		graf1[simpul2][simpul1] = bobot;
		}
	}
	
void tampilkan_hasil_graf(int pil9){
	//int pil;
	//printf("Tampilkan dalam bentuk (1)matriks ketetanggaan atau (2)S-S=BOBOT ?");
	//scanf("%d", &pil);
	puts("");
	if(pil9 == 1){
		printf("\n-          ");
		for(int i=0; i<jmlh_simpul; ++i){
			if(pil_nama_simpul==1){
				printf("%c ", nama_simpul[i]);}
			else{printf("%d ", i+1);}	
		printf("\n");
		for(int i=0;i<jmlh_simpul;++i)
		{
			if(pil_nama_simpul==1){
				printf("Simpul %c : ", nama_simpul[i]);}
			else{
				printf("Simpul %d : ", i+1);}
			for(int j=0;j<jmlh_simpul;++j)
				printf("%d ",graf1[i][j]);
				}	
			}
		}
	else{
		for(int i =0; i<jmlh_simpul; ++i){
			for(int j=i; j<jmlh_simpul; ++j){
				if(graf2[i][j]!=0){
					if(pil_nama_simpul==1){
						printf("%c - %c = %d\n", nama_simpul[i] , nama_simpul[j], graf2[i][j]);
						}
					else{
						printf("%d - %d = %d\n", i+1, j+1, graf2[i][j]);
						}
					}
				}
			}
		}
	
	}

void tampilkan_isi_graf1(){
	printf("-          ");
	for(int i=0; i<jmlh_simpul; ++i){
		printf("%d ", i+1);
		}
	printf("\n");
	for(int i=0;i<jmlh_simpul;++i)
	{
		printf("\n");
		printf("Simpul %d : ", i+1);
		for(int j=0;j<jmlh_simpul;++j)
			printf("%d ",graf1[i][j]);
	}
	puts("");	
	}

void pengaturan(){
	puts("");
	int pil;
	do{
	puts("Input dan output antara matriks ketetanggaan atau bentuk simpul-simpul=bobot");
	puts("Pengaturan (0 = Tidak, 1 = Iya) :");
	printf("1. Input Berupa Matriks Ketanggaan  \t [%d]\n", input_sisi_simpul);
	printf("2. Output Berupa Matriks Ketanggaan \t [%d]\n", tampil_sisi_simpul);
	printf("3. Nama simpul berupa Huruf         \t [%d]\n", pil_nama_simpul);
	printf("4. Kembali\n");
	printf("Pilihan yang ingin diganti ? ");
	scanf("%d", &pil);
	if(pil == 1){
		input_sisi_simpul = balik_nol_satu(input_sisi_simpul);
		}
		else if(pil==2){
			tampil_sisi_simpul = balik_nol_satu(tampil_sisi_simpul);
			}
			else if(pil==3){
				pil_nama_simpul = balik_nol_satu(pil_nama_simpul);
				}
				else{
					break;
					}
					}while(1);
	}

void menu_utama(){
	puts("-------------Matematika Diskrit II--------------");
	puts("                 Tugas Akhir                    ");
	puts("");
	puts("");
	puts("Dosen : I Gusti Vida Mastrika Giri, S.Kom., M.Cs");
	puts("");
	puts("");
	puts("** Pengaturan awal **");
	ganti_nama_simpul();
	puts("** Silahkan input graf pada menu nomor 4 **");
	puts("** Tipe input dan output berada di meu nomor 5 **");
	puts("** Selesai **");
	puts("");
	system("pause");
	system("cls");
	}

void menu_utama_lanj(){
	int pil;
	do{
puts("__________________________________________");
	puts("| Selamat datang  **USER**               |");
	puts("| Menu :                                 |");
	puts("| 1. Shortest Path				 |");
	puts("| 2. Implementasi Agloritma Prim         |");
	puts("| 3. Implementasi Agloritma Kruskal      |");
	puts("| 4. Masukkan Graf Baru			 |");
	puts("| 5. Pengaturan & Bantuan			 |");
	puts("| 6. Keluar			      		 |");
	puts("|________________________________________|");	
	puts("");
	printf("Masukkan pilihan : ");
	scanf("%d", &pil);
	if(pil == 1){
		dijkstra();
		}
			else if(pil == 2){
					prims();
					}
					else if(pil == 3){
						kruskal();
						}
						else if(pil == 4){
							input_jmlh_simpul();
							if(input_sisi_simpul==0){
								input_bersisian();
								}
								else{
									input_ketanggaan();
									}
							tampilkan_isi_graf1();
							}else if(pil == 5){
								pengaturan();
								}
								else if(pil == 6){
									exit(0);
									}
									else{
										printf("Pilihan yang kamu masukkan salah !");
										}
										nilai_nol_array();
		}while(1);
	}
int main()
{
	menu_utama();
	menu_utama_lanj();
	return 0;
}

