compilar:
	g++ -Ieigen-3.4.0/ PCA.cpp -O3 -march=native -fopenmp -o PCA
	g++ -Ieigen-3.4.0/ knn.cpp -O3 -march=native -fopenmp -o kNN
	mkdir k-fold