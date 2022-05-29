compilar:
	g++ -Ieigen-3.4.0/ PCA.cpp -O3 -march=native -fopenmp -o PCA
	g++ -Ieigen-3.4.0/ knn.cpp -O3 -march=native -fopenmp -o kNN
	mkdir -p k-fold/pca
	mkdir -p k-fold/knn
	mkdir -p train_subsets
