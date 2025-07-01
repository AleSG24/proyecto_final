
Repositorio de git en el que se desarrollara el proyecto final del curso Programacion Bajo Plataformas Abiertas
# Buscaminas

El clásico buscaminas busca ser un juego breve en el cual se logre distraerse por unos cuantos minutos sin dedicarle demasiado tiempo. En el caso de este proyecto se desarrolla un buscaminas de 10 columnas x 8 filas en las cuales se distribuyen de forma aleatoria 10 minas con el fin de ofrecer una experiencia breve con un nivel de dificultad bajo. Este proyecto fue desarrollado con el fin de demostrar los conocimientos adquiridos durante el curso de porgramación bajo plataformas abiertas por lo tanto el proyecto se realiza en C utilizando las diversas librerias vistas durante el curso con la adición de SDL2 que fue utilizado para el desarrollo de la interfaz gráfica.

# Instalación

## Dependencias
- Se necesita tener instalado SDL2 y GCC.
- Sería optimo utilizar el **Makefile** en una computadora con Linux ya que este está hecho con el proposito de ser ejecutado en dicho sistema operativo.
- Asegurarse de estar en el directorio descargado a partir del git y tener en el los archivos tablero.c, tabla.h, celdas.c, celdas.h y main.c además de los direcotrios images y fuentes.
- Si falta alguna librería o directorio de los mencionados con anterioridad el programa no se instalará correctamente y será imposible de ejecutar.

# Ejecución y uso

- Para ejecutar el buscaminas simplemente se debe correr el archivo ejecutable *"buscaminas"* con **./** que fue generado a partir del Makefile. Luego de ejecutar el programa aparecerá una interfaz gráfica en la cual se puede comenzar a jugar con el ratón apretando las celdas con el click izquierdo o derecho. 
- El click derecho sirve para marcar con una bandera y el click izquierdo revela si hay mina o no en la celda. Al clickear una celda con mina, el juego termina con una pantalla de game over y aparece el temporizador en la parte de abajo de la pantalla con el tiempo transcurrido. 
- Si se marcan todas las banderas de forma correcta se gana en el juego y se muestra una pantalla de vicotria. Para que salir del juego se debe cerrar la ventana y eso sería suficiente para temrinar la ejecución del mismo.
