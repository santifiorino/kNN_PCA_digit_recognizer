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

int count_lines(char* filename) {
    ifstream file(filename);
    string line;
    int count = 0;
    while (getline(file, line))
        count++;
    return count - 1;
}

int main(int argc, char *argv[]) {
    clock_t start, end;
    start = clock();

    if (argc != 5){
        cout << "Error: 5 parametros requeridos <train> <test> <out> <k>" << endl;
        return 1;
    }
    char* train_file = argv[1];
    char* test_file = argv[2];
    char* out_file = argv[3];
    char* k_input = argv[4];
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

    cout << "Calculando los k vecinos" << endl;
    fstream fout;
    fout.open(out_file, ios::out);
    fout << "ImageId,Class,Distance" << endl;
    vector<neighbour> neareast_neighbors(k);
    for(int i = 0; i < test_size; i++){
        // Reset the nearest neighbors
        for(int j = 0; j < k; j++){
            get<1>(neareast_neighbors[j]) = numeric_limits<int>::max();
        }
        // Get the nearest neighbors
        for(int j = 0; j < train_size; j++){
            double dist = (test.row(i) - X.row(j)).norm();
            if(dist < get<1>(neareast_neighbors[k-1])){
                get<0>(neareast_neighbors[k-1]) = clases(j);
                get<1>(neareast_neighbors[k-1]) = dist;
                sort(neareast_neighbors.begin(), neareast_neighbors.end(), sortbysec);
            }
        }

        // Get the most common class
        for (int j = 0; j < k; j++){
            fout << i + 1 << "," << get<0>(neareast_neighbors[j]) << "," << get<1>(neareast_neighbors[j]) <<endl;
        }
    }
    
    end = clock();
    double time_taken = double(end - start) / double(CLOCKS_PER_SEC);
    cout << "Tardé: " << time_taken << endl;

    return 0;
}