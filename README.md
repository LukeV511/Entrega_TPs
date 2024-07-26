## TP2
## Titulo del trabajo: Medidor Inteligente de Energia
(continuación)
#### Alumno: 
Lucas Veglia

#### Objetivo: 
Desarrollar un sistema que permita monitorear el consumo de energía eléctrica residencial

#### Descripción:
El sistema calcula la energía eléctrica consumida por una residencia en tiempo real. Para ello se integra en el tiempo la potencia instantánea, 
calculada a partir de los valores de tensión y corriente, obtenidos de los siguientes sensores comerciales:
- Sensor de Tensión: ZMPT101B (250 V AC max)
- Sensor de Corriente: ACS712 (5A max)

La placa utilizada como plataforma de desarrollo fue:

- NUCLEO F429ZI

Los datos de tensión, corriente y potencia instantánea son enviados cada 10 milisegundos por el puerto serie, así como también un contador incremental de energía consumida, y un registro de la máxima potencia registrada. Sin embargo, estos son mostrados en pantalla de forma independiente cada un segundo (evitando crear un código bloqueante). Estos tiempos se manejan a traves de la tasa de refresco del sistema, la cual es de 10 milisegundos. Al involucrar todos los procesos tiempos no despreciables frente a 10 ms, se sabe que no se cuenta con demasiada precisión en las lecturas de valores a la larga. Se buscará implementar Tickers en instancias futuras del trabajo para resolverlo

En esta segunda instancia del trabajo se implementó el uso de un teclado matricial, mediante el cual se pueden introducir numeros que formaran un código. Una vez ingresado el mismo, se debe presionar el botón asignado al caracter "#" a modo de enter, mediante el cual el sistema procederá a la verificación de la contraseña. De resultar correcta la verificación, se resetea el contador de energía consumida y el registro de máxima potencia registrada, a la vez que se enciende un LED (azul) de la placa que indica el reseteo. De resultar la verificación erronea, los registros permanecen sin modificaciones y otro LED (rojo) indica que el código introducido fue incorrecto. El código ingresado puede verse en el puerto serie, a modo de control (en versiones posteriores se planea esconder los caracteres)

Para compensar los glitches y rebotes mecánicos de los botones físicos, se implementó una máquina de estados finita que cicla entre los estados de SCANNING (escaneo), DEBOUNCE (rebote) y KEY_HOLD_PRESSED (tecla manteniendose presionada).

Para optimizar el código, aumentar su mantenibilidad y productividad, en esta versión del proyecto se implementó la separación de las distintas funciones del programa en distintos archivos y carpetas, creando módulos y submódulos. A su vez se organizaron las distintas definiciones de las funciones y variables dependiendo de si estas eran de tipo publico o privadas. La estructura de las carpetas y de las definiciones de variables y funciones se basó en el ejemplo dado en 
https://github.com/alutenberg/subsection_5-4-2/tree/master/smart_home_system

![image](https://github.com/user-attachments/assets/53ce07b0-29ee-4b8b-b85e-aa1ee4f99008)

Periféricos utilizados en esta instancia del trabajo TP1:
- MATRIX KEYPAD: Se utiliza para ingresar el código necesario para resetear el contador de energía consumida y el registro de máxima potencia
- LED 1: Se encenderá para indicar que el sistema está en funcionamiento
- LED 2: Se encenderá para indicar el reseteo del contador de energía y registro de máxima potencia
- LED 3: Se encenderá para indicar que el codigo ingresado fue incorrecto
- ANALOG IN 1: Se utiliza para leer el valor de la corriente instantánea
- ANALOG IN 2: Se utiliza para leer el valor de la tensión instantánea
- UART: Se utiliza para enviar la información de estado del sistema a la PC

Ambos sensores convierten la señal alterna senoidal en una señal que varía entre 0 y 5 Vdc, trasladando los 0Vac a 2,5 Vdc. Así, valores negativos de la onda senoidal estarán entre 0 y 2,5 Vdc y valores positivos de la onda senoidal, entre 2,5 y 5 Vdc.

Para alimentar los sensores, se utilizó una salida de 5 V de la placa NUCLEO. Para acondicionar la señal saliente de los sensores y evitar que puedan
dañar la placa (que está preparada para recibir como máximo 3,3V) se utilizaron 3 resistencias de 10 Kohm para crear un divisor resistivo para cada señal.

La placa nucleo normaliza los valores de tensión recibidos de 0 a 3,3 V, a valores de 0 a 1.

Para asignar correctamente los valores de los sensores de tensión y corriente, se realizó el cálculo
(([valor recibido del sensor normalizado por la placa entre 0 y 1] - 0.5) * 3.3 V) / sensibilidad del sensor

(0.5 correspondería al offset que se le asigna a los 0 Vac, 3,3 V el valor de referencia, y la sensibilidad es una constante de cada sensor que se obtuvo analizandolos en el osciloscopio)

Para que se puedan visualizar los valores en pantalla por comunicacion serial, se debió incluir el archivo mbed_app.json para que la combinación
%2.f sea correctamente interpretada en el compilador.

Video mostrando el funcionamiento del sistema:

https://drive.google.com/file/d/13QFiiNaiqyuuqv0mAq1mItITp4Qq1K6K/view?usp=sharing

Para instancias futuras del proyecto, se espera poder implementar y presentar en los próximos trabajos prácticos:
- Que los valores que se muestren al usuario sean los valores RMS
- El cálculo del factor de potencia instantáneo
- Un relé que conecte y desconecte automáticamente capacitores para corregir el factor de potencia de la
instalación
- Un led cuya intensidad sea controlada por un PWM, proporcional a la potencia instantánea.
- Un buzzer que alerte cuando se exceda un valor de potencia predefinido
- Un display LCD que permita visualizar los valores instantáneos de tensión, corriente, potencia y factor de
potencia
- Una app que permita ver los datos y el perfil de carga desde un smartphone/sitio web.






