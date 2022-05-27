compilar:
	g++ -Ieigen-3.4.0/ PCA.cpp -O3 -march=native -fopenmp -o PCA
	g++ -Ieigen-3.4.0/ knn.cpp -O3 -march=native -fopenmp -o kNN
	g++ -Ieigen-3.4.0/ knn_tiempos.cpp -O3 -march=native -fopenmp -o kNN_tiempos
<<<<<<< HEAD
	mkdir k-fold
	mkdir train_subsets
=======
	mkdir k-fold
>>>>>>> d448a81ec7f6f02f717c71d1006c39ee7449bf0a
