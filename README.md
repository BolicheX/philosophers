# Philosophers
## Descripción
 Principios básicos de hilos, procesos y mutex.
 
## Funcionamiento
* Uno o más filósofos se sientan en una mesa redonda.
* En el centro de la mesa se encuentra un bol de espaguetis.
* Los filósofos solo pueden comer, pensar, o dormir.
* En la mesa hay tantos tenedores como filósofos.
* Para comer, los filósofos deben tomar el tenedor de la derecha y el de la izquierda.
* Cuándo un filósofo termine de comer, dejará los tenedores y empezará a dormir.
* Una vez se despierte, empezará a pensar.
* La simulación se detendrá cuando un filósofo muere por inanición.
* Todos los filósofos necesitan comer y nunca deben morir de hambre.
* Los filósofos no hablan entre ellos.
* Los filósofos no saben si otro filósofo va a morir.

## Funciones autorizadas
`memset`, `printf`, `malloc`, `free`, `write`,
`usleep`, `gettimeofday`, `pthread_create`,
`pthread_detach`, `pthread_join`, `pthread_mutex_init`,
`pthread_mutex_destroy`, `pthread_mutex_lock`,
`pthread_mutex_unlock`

## Reglas
*  Sin variables globales
*  Argumentos:
    * `number_of_philosophers` Número de filósofos y número de tenedores.
    * `time_to_die` (milisegundos) Tiempo que aguanta vivo un filosofo antes de necesitar comer.
    * `time_to_eat` (milisegundos) Tiempo que tarda un filósofo en comer, ocupando 2 tenedores.
    * `time_to_sleep` (milisegundos) Tiempo que tiene un filósofo para dormir.
    *  `number_of_times_each_philosopher_must_eat` (argumento opcional): Si todos los filósofos han comido este nº de veces, la simulación terminará. Si no se             especifica, la simulación se detendrá con la muerte de un filósofo.
* Cada filósofo tendrá asignado un número del 1 al `number_of_philosophers`.
* Los filósofos se sentarán en orden, en círculo, con el primero y el último juntos.
  
## Logs
* Cualquier cambio de estado de un filósofo debe tener el siguiente formato:
    * `timestamp_in_ms` `X` has taken a fork
    * `timestamp_in_ms` `X` is eating
    * `timestamp_in_ms` `X` is sleeping
    * `timestamp_in_ms` `X` is thinking
    * `timestamp_in_ms` `X` died
`timestamp_in_ms`: marca de tiempo actual en milisegundos `X`: número del filósofo.
* El estado impreso no debe estar roto o alterado por el estado de otros filósofos
* No más de 10ms entre la muerte de un filósofo y el momento en el que imprimes su muerte.

## Parte obligatoria
* Cada filósofo debe ser un hilo.
* Hay un tenedor entre cada filósofo; si hay varios filósofos, cada uno
tendrá un tenedor a su izquierda y otro a su derecha. Si solo hay un filósofo,
solo habrá un tenedor.
* Para prevenir que los filósofos dupliquen los tenedores hay que proteger los estados
de los tenedores con un mutex.

## Parte bonus
* Los tenedores están en el centro de la mesa.
* Los tenedores no tienen estados de memoria, pero el numero de disponibilidades
está representados por un semaforo.
* Cada filósofo debe ser un proceso, y el proceso principal no debe ser un filósofo.

## Documentación
* [Subject](https://cdn.intra.42.fr/pdf/pdf/135358/es.subject.pdf)
* [Guide](https://medium.com/@ruinadd/philosophers-42-guide-the-dining-philosophers-problem-893a24bc0fe2)
