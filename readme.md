Basta utilizar el comando `make` para compilar los archivos de C++. Para ejecutar la notebook se necesita Python 3 y Jupyter Notebook. Las librerías externas de Python utilizadas estan detalladas en `requirements.txt`

## PCA.cpp

- Genera un .csv con la moda de la clase (ponderada por la distancia) de los k vecinos mas cercanos
- Toma 5 parámetros:
  1. **train:** nombre del csv de entrenamiento
  2. **test:** nombre del csv de test
  3. **out:** nombre del csv de salida
  4. **alpha:** parámetro para PCA
  5. **k:** vecinos de kNN

## knn.cpp

- Genera un .csv con la clase y la distancia de los k vecinos mas cercanos, ordenados por distancia
- Toma 4 parámetros:
  1. **train:** nombre del csv de entrenamiento
  2. **test:** nombre del csv de test
  3. **out:** nombre del csv de salida
  4. **k:** parámetro para kNN
