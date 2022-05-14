#include <iostream>
#include <fstream>
#include <cstring>
#include <sstream>
#include <vector>
#include <Eigen/Dense>

using namespace std;
using Eigen::MatrixXd;
using Eigen::VectorXd;

typedef tuple<int, float> neighbour; // "Neighbour type has the class and the distance"

bool sortbysec(neighbour &a, neighbour &b){
    return (get<1>(a) < get<1>(b));
}

double metodo_potencia(MatrixXd &B, VectorXd &v, int niter){
    for(int i = 0; i < niter; i++){
        v = B * v;
        v = v / v.norm();
    }
    return double(v.transpose() * B * v) / double(v.transpose() * v);
}

MatrixXd deflation(MatrixXd &B, MatrixXd &P){
    int n = 784;
    MatrixXd D(n,n);
    Eigen::VectorXd v = Eigen::VectorXd::Constant(n, 1);
    double l = 0;
    for (int i = 0; i < n; i++){
        B = B - l*v*v.transpose();
        l = metodo_potencia(B, v, 1000);
        D(i,i) = l;
        P.col(i) = v;
    }
    return D;
}

int count_lines(char* filename) {
    ifstream file(filename);
    string line;
    int count = 0;
    while (getline(file, line))
        count++;
    return count - 1;
}

int main(int argc, char *argv[]) {
    if (argc != 5){
        cout << "Error: 4 parametros requeridos <train> <test> <alpha> <k>" << endl;
        return 1;
    }
    char* train_file = argv[1];
    char* test_file = argv[2];
    char* a_input = argv[3];
    char* k_input = argv[4];
    int alpha = atoi(a_input);
    int k = atoi(k_input);

    cout << "Leeyendo los datos de entrada" << endl;

    int train_size = count_lines(train_file);
    Eigen::MatrixXd X(train_size, 784);
    Eigen::VectorXd clases(train_size);
    string line, word;
	fstream file (train_file, ios::in);
	if(file.is_open()){
        getline(file, line); // Skip first line (header)
        int i = 0;
		while(getline(file, line)){
			stringstream str(line);
            getline(str, word, ','); // First num has the class
            int clase = stoi(word);
            clases(i) = clase;
            int j = 0;
            while(getline(str, word, ',')){ 
                int num = stoi(word);
                X(i, j) = num;
                j ++;
            }
            i ++;
		}
	}
    int test_size = count_lines(test_file);
    Eigen::MatrixXd test(test_size, 784);
	fstream file2 (test_file, ios::in);
	if(file2.is_open()){
        getline(file2, line); // Skip first line (header)
        int i = 0;
		while(getline(file2, line)){
			stringstream str(line);
            int j = 0;
            while(getline(str, word, ',')){ 
                int num = stoi(word);
                test(i, j) = num;
                j ++;
            }
            i ++;
		}
	}

    cout << "Creando matriz de covarianza" << endl;
    test.rowwise() -= X.colwise().mean();
    X.rowwise() -= X.colwise().mean();
    test *= (1 / sqrt(double(train_size)-1));
    MatrixXd X_aux = X;
    X *= (1 / (double(train_size)-1));
    X = (X.transpose() * X);

    cout << "Diagonalizando" << endl;
    Eigen::MatrixXd V_T(784, 784); // P = V^t
    Eigen::MatrixXd D = deflation(X, V_T);

    cout << "Cambiando de base el train" << endl;
    X_aux *= (1 / sqrt(double(train_size)-1));
    Eigen::MatrixXd new_train(train_size, alpha);
    for (int i = 0; i < train_size; i++){
        for (int j = 0; j < alpha; j++){
            new_train(i, j) = double(V_T.col(j).transpose() * X_aux.row(i).transpose());
        }
    }
    
    cout << "Cambiando de base el test y aplicando tc" << endl;
    
    Eigen::MatrixXd new_test(test_size, alpha);
    for (int i = 0; i < test_size; i++){
        for (int j = 0; j < alpha; j++){
            new_test(i, j) = double(V_T.col(j).transpose() * test.row(i).transpose());
        }
    }

    cout << "Calculando los k vecinos" << endl;
    fstream fout;
    fout.open("PCA_out.csv", ios::out);
    fout << "ImageId,Label" << endl;
    vector<neighbour> neareast_neighbors(k);
    for(int i = 0; i < test_size; i++){
        // Reset the nearest neighbors
        for(int j = 0; j < k; j++){
            get<1>(neareast_neighbors[j]) = numeric_limits<int>::max();
        }
        // Get the nearest neighbors
        for(int j = 0; j < train_size; j++){
            double dist = (new_test.row(i) - new_train.row(j)).norm();
            if(dist < get<1>(neareast_neighbors[k-1])){
                get<0>(neareast_neighbors[k-1]) = clases(j);
                get<1>(neareast_neighbors[k-1]) = dist;
                sort(neareast_neighbors.begin(), neareast_neighbors.end(), sortbysec);
            }
        }

        // Get the most common class
        vector<double> classes_count(10, 0);
        for(int j = 0; j < k; j++){
            classes_count[get<0>(neareast_neighbors[j])] += (1 / get<1>(neareast_neighbors[j]));
        }

        int max_count = 0;
        for (int j = 1; j < 10; j++){
            if(classes_count[j] > classes_count[max_count]){
                max_count = j;
            }
        }
        fout << i + 1 << "," << max_count << endl;
    }
    
    return 0;
}