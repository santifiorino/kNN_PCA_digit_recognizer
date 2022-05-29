Basta utilizar el comando `make` para compilar los archivos de C++. Para ejecutar la notebook se necesita Python 3 y Jupyter Notebook. Las librerías externas de Python utilizadas estan detalladas en `requirements.txt`

## PCA.cpp

- Toma 6 parámetros:
  1. **train:** nombre del csv de entrenamiento
  2. **test:** nombre del csv de test
  3. **out:** nombre del csv de salida
  4. **alpha:** parámetro para PCA
  5. **k:** vecinos de kNN
  6. **modo** 0 indica que el .csv de salida contiene linea por linea la clasificación del archivo "test", 1 indica que el .csv de salida contiene los k vecinos más cercanos de cada imagen del "test", ordenados por distancia

## knn.cpp

- Genera un .csv con la clase y la distancia de los k vecinos mas cercanos, ordenados por distancia
- Toma 4 parámetros:
  1. **train:** nombre del csv de entrenamiento
  2. **test:** nombre del csv de test
  3. **out:** nombre del csv de salida
  4. **k:** parámetro para kNN
