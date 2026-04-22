#include <stdio.h>

void matshow(int M, int mat[M][M]);
void idenmat(int M, int mat[M][M]);
void matmul(int M, int mat[M][M], int n, int r[M][M]);

int main() {
	int M;
	printf("Enter the dimension of the matrix(M): ");
	scanf("%d", &M);

	int n;
	printf("\nEnter the exponent(n): ");
	scanf("%d", &n);

	int A[M][M];
	int R[M][M];

	printf("Enter the value of the matrix in this format: \n> [val_1] [val_2] ... [val_M]\n> Repeat M times\n");
	for(int i = 0; i < M; i++)
		for(int j = 0; j < M; j++)
			scanf("%d", &A[i][j]);

	printf("\nResult:\n");

	matmul(M, A, n, R);
	matshow(M, R);
	return 0;
}

void matshow(int M, int mat[M][M]) {
	for(int i = 0; i < M; i++) {
		for(int j = 0; j < M; j++) {
			printf("| %d | ", mat[i][j]);
		}
		printf("\n");
	}
}

void idenmat(int M, int mat[M][M]) {
	for(int i = 0; i < M; i++){
		for(int j = 0; j < M; j++)
			mat[i][j] = (i==j);
	}
}


void matmul(int M, int mat[M][M], int n, int r[M][M]) {
	if (n == 0){
		idenmat(M, r);
		return;
	}
	if (n == 1) {
		for(int i = 0; i < M; i++)
			for(int j = 0; j < M; j++)
				r[i][j] = mat[i][j];
		return;
	}
	int temp[M][M];
	matmul(M, mat, n - 1, r);

	for(int i = 0; i < M; i++){
		for(int j = 0; j < M; j++){
			temp[i][j] = 0;
			for(int k = 0; k < M; k++)
				temp[i][j] += r[i][k] * mat[k][j];
		}
	}	

	for(int i = 0; i < M; i++){
		for(int j = 0; j < M; j++){
			r[i][j] = temp[i][j];
		}
	}
}

