# Rescue Line 2020 - Lions Equipo Prepa 3

Este repositorio almacenará los datos del robot Happy para los concursos de Rescue Line durante el año 2020. Aqui, se explicará como modificar el código de este robot para obtener la funcionalidad correcta.

Si quisieran escribir código yo recomiendo que lo hagan dentro de la función **logica** que se encuentra al final del archivo. Las funciones y variables que pueden usar son los siguientes:

## Movimiento del Robot

**avanzar(rapidez)**: Esta función recibe un valor de 0 a 255 indicando que el robot deba avanzar a esa rápidez hacia enfrente.

**regresar(rapidez)**: Esta función recibe un valor de 0 a 255 indicando que el robot debe retroceder sin voltear a esa rápidez.

**girarIzquierda(rapidez)**: Esta función recibe un valor de 0 a 255 indicando que el robot debe girar a la izquierda a esa rápidez.

**girarDerecha(rapidez)**: Esta función recibe un valor de 0 a 255 indicando que el robot debe girar a la derecha a esa rápidez.

**girarAmpliamenteIzquierda(rapidez)**: Esta función recibe un valor de 0 a 255 indicando que el robot debe girar a la izquierda de una manera más amplia que la función girarIzquierda y a cierta rápidez.

**girarAmpliamenteDerecha(rapidez)**: Esta función recibe un valor de 0 a 255 indicando que el robot debe girar a la derecha de una manera más amplia que la función girarDerecha y a cierta rápidez.

**detener()**: Detiene el robot.

Una nota importante es que siempre se debe incluir **delay(milisegundos)** despúes de cada una de estas funciónes para permitir que el robot tenga tiempo de mover antes de que se llame otra función. Las siguientes dos funciones NO deben tener un delay debido a que ya tienen uno incluido.

**orientarIzquierda()**: Orienta el robot 90° a la izquierda.

**orientarDerecha()**: Orienta el robot 90° a la derecha.

## Sensores de color

Una pixy detecta los colores y debe ser calibrado para ver el verde en la signatura 1.

## Sensores de línea

El arreglo **linea** contiene 8 booleanos (verdadero o falso) que indica si se puede observar la linea debajo de ese sensor específico. Esto podría ser util para observar si existe una linea perpendicular al robot.

Además de esto la variable **ubicacionDeLinea** es un entero de 0 a 7000 que indica en que posición se encuentra la línea. Entre más bajo sea el número, más a la izquierda se encuentra la línea. Lo más óptimo es conservar este número justo en medio de los dos valores (osea en 3500).

## Botón frontal

Happy tiene un botón en su frente, el cual se activa con la presión. Si se presiona este botón, se guardara el valor true dentro de la variable **boton**, y false en caso contrario.