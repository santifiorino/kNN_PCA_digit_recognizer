compilar:
	g++ -Ieigen-3.4.0/ PCA.cpp -O3 -march=native -fopenmp -o PCA
	mkdir k-fold