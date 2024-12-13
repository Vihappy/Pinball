#  PINBALL
Este proyecto es una implementación básica de Pinball en C++ utilizando SFML y Box2D. El juego presenta una bola que desciende al iniciar, rebotando en obstáculos que incrementan el puntaje al tocarlos. En la parte inferior, dos paletas controlables permiten redirigir la bola hacia los obstáculos, manteniéndola en juego. Las físicas del rebote y las colisiones están cuidadosamente integradas para simular un comportamiento realista. Es un ejemplo sencillo pero completo de cómo usar SFML y Box2D para desarrollar mecánicas de un juego clásico.
# Estructura del proyecto
- Assets: Contiene los recursos multimedia que enriquecen el juego con gráficos, audio y tipografías.
- Bin:Carpeta destinada a los ejecutables generados después de compilar el código. Aquí se guardan los programas.
- Docs: Almacena la documentación del proyecto.
- Include: Contiene los archivos de cabecera (.hpp), que declaran las clases, funciones y estructuras del juego. Cada archivo define una parte específica del sistema
- src: Contiene los archivos fuente (.cpp) con la implementación del juego.
- Makefile: Archivo de configuración para automatizar el proceso de compilación y ejecución.
# Imagenes del Juego
![Jueeegoo](https://github.com/user-attachments/assets/8fded0a1-eafc-41fc-b28d-58b5aac01ff1)
# Diagrama de clases
El diagrama incluye las siguiestes clases:
- Ball
Representa la pelota del juego. Controla su comportamiento físico (movimiento, rebotes) y su interacción con los otros objetos en la tabla.
- Paleta
Representa las paletas que el jugador controla. Permite girar en respuesta a las entradas del usuario, impulsando la pelota hacia los obstáculos.
- Bumper (o Rebotador)
Define los obstáculos rebotantes en el tablero. Incrementa el puntaje cuando la pelota los golpea y maneja la restitución física para que la pelota rebote.
- Pared
Representa los límites y bordes del tablero. Evita que la pelota salga del área de juego.
- Colision
Gestiona los eventos de colisión entre los objetos del juego. Se encarga de verificar qué ocurre cuando la pelota golpea un obstáculo, una pared o una paleta.
