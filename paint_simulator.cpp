#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define EPERM 1
#define EINVAL 2
#define ENOMEM 3

struct image {
	int width;
	int height;
	int **picture;
	unsigned int R, G, B;
	
	void init(int w, int h) {
		int i, j;
		if(w <= 0 || h <= 0) {
			fflush(stdout);
			fprintf(stderr, "%d\n", EINVAL);
			//printf("Parametru invalid");
			exit(EXIT_FAILURE);
		}
		width = w;
		height = h;
		picture = (int **)malloc(height * sizeof(int*));
		for(i = 0; i < height; i++) picture[i] = (int *)malloc(3*width * sizeof(int));
    	
		for(i = 0; i < height; i++) {
			for(j = 0; j < 3*width; j+=3) {
				scanf("%u%u%u", &R, &G, &B);
				picture[i][j] = R;
				picture[i][j+1] = G;
				picture[i][j+2] = B;
			}
		}
	}
	
	void print() {
		int i, j;
		fflush(stdout);
		printf("%d %d\n", width, height);
		for(i = 0; i < height; i++) {
			for(j = 0; j < 3*width; j+=3) {
				printf("%d ", picture[i][j]);
				printf("%d ", picture[i][j+1]);
				printf("%d ", picture[i][j+2]);
			}
			printf("\n");
		}
		//printf("\n");
	}
	void crop(int start_col, int start_line, int end_col, int end_line) {
		int i, j;
		if(start_col > width || end_col > width || start_line > height || end_line > height || start_col > end_col || start_line > end_line) {
			fflush(stdout);
			fprintf(stderr, "%d\n", EINVAL);
			//printf("Parametru invalid");
			exit(EXIT_FAILURE);
		}
		
		int newWidth, newHeight;
		newWidth = end_col - start_col + 1;
		newHeight = end_line - start_line + 1;
		//int bpicture[newHeight][3*newWidth];
		image b;
		b.width = newWidth;
		b.height = newHeight;
		b.picture = (int **)malloc(newHeight * sizeof(int*));
		for(i = 0; i < newHeight; i++) b.picture[i] = (int *)malloc(3*newWidth * sizeof(int));
		//printf("%d %d\n", newWidth, newHeight);
		int t = 0;
		//i = start_line;
		//j = start_col;
		//while(t < newHeight) {
			//printf("%d %d\n", start_line, start_col);
			for(i = start_line; i <= end_line; i++) {
				int k = 0;
				for(int j = start_col; j <= 3*end_col; j+=3) {
					b.picture[t][k] = picture[i][j];
					b.picture[t][k+1] = picture[i][j+1];
					b.picture[t][k+2] = picture[i][j+2];
					k+=3;
				}	
				t++;
				//i = i + 1;
				//k = 0;
			//}

		}

		//for(i = 0; i < height; i++) free(picture[i]);     //dealloc matricea pentru a-i aloca dimensiuni noi
		//free(picture);
		
		height = newHeight;
		width = newWidth;
		//picture = (int **)malloc(newHeight * sizeof(int*));
		//for(i = 0; i < newHeight; i++) picture[i] = (int *)malloc(3*newWidth * sizeof(int));
		//picture = b.picture;
		for(i = 0; i < height; i++) {
			for(j = 0; j < 3*width; j+=3) {
				picture[i][j] = b.picture[i][j];
				picture[i][j+1] = b.picture[i][j+1];
				picture[i][j+2] = b.picture[i][j+2];
			}
		}
		//for(i = 0; i < b.height; i++) free(b.picture[i]);
		//free(b.picture);
	}
	void resize(int Rwidth, int Rheight) {
		if(Rwidth <= 0 || Rheight <= 0 || Rwidth > 1024 || Rheight > 1024) {
			fflush(stdout);
			fprintf(stderr, "%d\n", EINVAL);
			//printf("Parametru invalid");
			exit(EXIT_FAILURE);
		}
		int i = 0, j = 0;
		image b;
		b.height = Rheight;
		b.width = Rwidth;
		b.picture = (int **)malloc(Rheight * sizeof(int*));
		for(i = 0; i < Rheight; i++) b.picture[i] = (int *)malloc(3*Rwidth * sizeof(int));
		
		for(i = 0; i < Rheight; i++) {
			for(j = 0; j < 3*Rwidth; j+=3) {
				b.picture[i][j] = 255;
				b.picture[i][j+1] = 255;
				b.picture[i][j+2] = 255;
			}
		}
		
		if(Rheight > height && Rwidth <= width) {
			for(i = 0; i < height; i++) {
				for(j = 0; j < 3*Rwidth; j+=3) {
					b.picture[i][j] = picture[i][j];
					b.picture[i][j+1] = picture[i][j+1];
					b.picture[i][j+2] = picture[i][j+2];
				} 
			}
		}
		if(Rwidth > width && Rheight <= height) {
			for(i = 0; i < Rheight; i++) {
				for(j = 0; j < 3*width; j+=3) {
					b.picture[i][j] = picture[i][j];
					b.picture[i][j+1] = picture[i][j+1];
					b.picture[i][j+2] = picture[i][j+2];
				}
			}
		}
		
		if(Rwidth >= width && Rheight >= height) {
			for(i = 0; i < height; i++) {
				for(j = 0; j < 3*width; j+=3) {
					b.picture[i][j] = picture[i][j];
					b.picture[i][j+1] = picture[i][j+1];
					b.picture[i][j+2] = picture[i][j+2];
				}
			}
		}
		if(Rwidth <= width && Rheight <= height) {                     //in acest caz face crop
			for(i = 0; i < Rheight; i++) {
				for(j = 0; j < 3*Rwidth; j+=3) {
					b.picture[i][j] = picture[i][j];
					b.picture[i][j+1] = picture[i][j+1];
					b.picture[i][j+2] = picture[i][j+2];
				}
			}
		}
		for(i = 0; i < height; i++) free(picture[i]);     //dealloc matricea pentru a-i aloca dimensiuni noi
		free(picture);
		height = Rheight;
		width = Rwidth;
		picture = (int **)malloc(height * sizeof(int*));
		for(i = 0; i < height; i++) picture[i] = (int *)malloc(3*width * sizeof(int));
		for(i = 0; i < Rheight; i++) {
			for(j = 0; j < 3*Rwidth; j+=3) {
				picture[i][j] = b.picture[i][j];
				picture[i][j+1] = b.picture[i][j+1];
				picture[i][j+2] = b.picture[i][j+2];
			}
		}
		for(i = 0; i < b.height; i++) free(b.picture[i]);
		free(b.picture);
	}
	
	void color(int start_col, int start_line, int end_col, int end_line, unsigned int r, unsigned int g, unsigned int b) {
		if(start_line > end_line || start_col > end_col || start_line < 0 || end_line < 0 || start_line > height || end_line > height || start_col < 0 || end_col < 0 || start_col > width || end_col > width || r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255) {
			fflush(stdout);
			fprintf(stderr, "%d\n", EINVAL);
			//printf("Parametru invalid");
			exit(EXIT_FAILURE);
		}
		//R = r; G = g; B = b;
		int i, j;
		for(i = start_line; i <= end_line; i++) {
			for(j = 3*start_col; j <= 3*end_col; j+=3) {
				picture[i][j] = r;
				picture[i][j+1] = g;
				picture[i][j+2] = b;
			}
		}
	}
	
	void blur(int num_iter) {
		if(num_iter < 0 || num_iter > 2000) {
			fflush(stdout);
			fprintf(stderr, "%d\n", EINVAL);
			exit(EXIT_FAILURE);
		}
		int i, j;
		
		int bpicture[height][3*width];
		int blur = 0;
		while(blur < num_iter) {
			for(i = 0; i < height; i++) {
				for(j = 0; j < 3*width; j+=3) {
					if(i >= 1 && (i+1) != height && j >= 3 && (j+3) != (3*width)) {                                                     //mijloc
						bpicture[i][j] = (picture[i-1][j] + picture[i+1][j] + picture[i][j+3] + picture[i][j-3]) / 4;
						bpicture[i][j+1] = (picture[i-1][j+1] + picture[i+1][j+1] + picture[i][j+4] + picture[i][j-2]) / 4;
						bpicture[i][j+2] = (picture[i-1][j+2] + picture[i+1][j+2] + picture[i][j+5] + picture[i][j-1]) / 4;
					}
					if(i < 1 && j < 3) {                                                            //colt stanga sus
						bpicture[i][j] = (picture[i][j+3] + picture[i+1][j]) / 2;
						bpicture[i][j+1] = (picture[i][j+4] + picture[i+1][j+1]) / 2;
						bpicture[i][j+2] = (picture[i][j+5] + picture[i+1][j+2]) / 2;
					}
					if(i >= 1 && j < 3 && (i+1) == height) {                                        //colt stanga jos
						bpicture[i][j] = (picture[i-1][j] + picture[i][j+3]) / 2;
						bpicture[i][j+1] = (picture[i-1][j+1] + picture[i][j+4]) / 2;
						bpicture[i][j+2] = (picture[i-1][j+2] + picture[i][j+5]) / 2;
					}
					if(i < 1 && j >= 3 && (j+3) != (3*width)) {                                                     //mijloc sus
						bpicture[i][j] = (picture[i][j-3] + picture[i+1][j] + picture[i][j+3]) / 3;
						bpicture[i][j+1] = (picture[i][j-2] + picture[i+1][j+1] + picture[i][j+4]) / 3;
						bpicture[i][j+2] = (picture[i][j-1] + picture[i+1][j+2] + picture[i][j+5]) / 3;
					}
					if(i < 1 && (j+3) == (3*width)) {                                                 //colt dreapta sus
						bpicture[i][j] = (picture[i][j-3] + picture[i+1][j]) / 2;
						bpicture[i][j+1] = (picture[i][j-2] + picture[i+1][j+1]) / 2;
						bpicture[i][j+2] = (picture[i][j-1] + picture[i+1][j+2]) / 2;
					}
					if(i >= 1 && j >= 3 && (i+1) == height && (j+3) != (3*width)) {                                   //mijloc jos
						bpicture[i][j] = (picture[i][j-3] + picture[i-1][j] + picture[i][j+3]) / 3;
						bpicture[i][j+1] = (picture[i][j-2] + picture[i-1][j+1] + picture[i][j+4]) / 3;
						bpicture[i][j+2] = (picture[i][j-1] + picture[i-1][j+2] + picture[i][j+5]) / 3;
					}
					if(i >= 1 && (j+3) == (3*width) && (i+1) == height) {                              //colt dreapta jos
						bpicture[i][j] = (picture[i][j-3] + picture[i-1][j]) / 2;
						bpicture[i][j+1] = (picture[i][j-2] + picture[i-1][j+1]) / 2;
						bpicture[i][j+2] = (picture[i][j-1] + picture[i-1][j+2]) / 2;
					}
					if(i >= 1 && (i+1) != height && j < 3 ) {                                              //stanga mijloc
						bpicture[i][j] = (picture[i-1][j] + picture[i+1][j] + picture[i][j+3]) / 3;
						bpicture[i][j+1] = (picture[i-1][j+1] + picture[i+1][j+1] + picture[i][j+4]) / 3;
						bpicture[i][j+2] = (picture[i-1][j+2] + picture[i+1][j+2] + picture[i][j+5]) / 3;
					}
					
					if(i >= 1 && (i+1) != height && (j+3) == (3*width)) {
						bpicture[i][j] = (picture[i-1][j] + picture[i+1][j] + picture[i][j-3]) / 3;               //dreapta mijloc
						bpicture[i][j+1] = (picture[i-1][j+1] + picture[i+1][j+1] + picture[i][j-2]) / 3;
						bpicture[i][j+2] = (picture[i-1][j+2] + picture[i+1][j+2] + picture[i][j-1]) / 3;
					}
				}
			}
			for(i = 0; i < height; i++) {
				for(j = 0; j < 3*width; j+=3) {
					picture[i][j] = bpicture[i][j];
					picture[i][j+1] = bpicture[i][j+1];
					picture[i][j+2] = bpicture[i][j+2];
				}
			}
			blur++;
		}
		
	}
	
	void rotate(int rot) {
		if(rot <= 0) {
			fflush(stdout);
			fprintf(stderr, "%d\n", EINVAL);
			exit(EXIT_FAILURE);
		}
		int num_rot = rot%4;
		int roteste = 0;
		if(num_rot == 0) {
			return;
		}
		while(roteste < num_rot) {
			int i, j = 0, t = 0;
			int Nheight = width;
			int Nwidth = height;
			int rotatedpicture[Nheight][3*Nwidth];
			while(j < 3*width && t < Nheight) {
				int k = 0;
				for(i = height-1; i >= 0; i--) {
					rotatedpicture[t][k] = picture[i][j];
					rotatedpicture[t][k+1] = picture[i][j+1];
					rotatedpicture[t][k+2] = picture[i][j+2];
					k = k + 3;
				}
				j = j + 3;                                    //incrementez coloana pe care o intorc
				t = t + 1;									  //incrementez linia noii imagini intoarse
			}
			
			for(i = 0; i < height; i++) free(picture[i]);     //dealloc matricea pentru a-i aloca dimensiuni noi
			free(picture);
			height = Nheight;
			width = Nwidth;
			picture = (int **)malloc(height * sizeof(int*));
			for(i = 0; i < height; i++) picture[i] = (int *)malloc(3*width * sizeof(int));
			
			for(i = 0; i < height; i++) {
				for(j = 0; j < 3*width; j+=3) {
					picture[i][j] = rotatedpicture[i][j];
					picture[i][j+1] = rotatedpicture[i][j+1];
					picture[i][j+2] = rotatedpicture[i][j+2];
				}
			}
			roteste++;
			}
		}
};

int main() {
	image a;
	
	int quit = 0;
	while(!quit) {
		int op;
		scanf("%d", &op);
		switch(op) {
			case 1:
				int width, height;
				scanf("%d%d", &width, &height);
				a.init(width, height);
				break;
			case 2: 
				int start_cols, start_lines, end_cols, end_lines;
				scanf("%d%d%d%d", &start_cols, &start_lines, &end_cols, &end_lines);
				a.crop(start_cols, start_lines, end_cols, end_lines);
				break;
			case 3:
				int nWidth, nHeight;
				scanf("%d%d", &nWidth, &nHeight);
				a.resize(nWidth, nHeight);
				break;
			case 4:
				int startcol, startline, endcol, endline; unsigned int r, g, b;
				scanf("%d%d%d%d%u%u%u", &startcol, &startline, &endcol, &endline, &r, &g, &b);
				a.color(startcol, startline, endcol, endline, r, g, b); 
				break;
			case 5:
				int num;
				scanf("%d", &num);
				a.blur(num);
				break;
			case 6:
				int rot;
				scanf("%d", &rot);
				a.rotate(rot);
				break;
			case 8:
				a.print();
				break;
			case 0:
				free(a.picture);
				exit(EXIT_SUCCESS);
				quit = 1;
				break;
			default:
				free(a.picture); 
				fflush(stdout);
				fprintf(stderr, "%d\n", EPERM);
				exit(EXIT_FAILURE);
				quit = 1;
				break;
		}
	}
	
}
