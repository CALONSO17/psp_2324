
/*fork(): Crea un nuevo proceso hijo duplicando el proceso padre, lo que permite la ejecución de múltiples tareas de manera concurrente.

exec(): Reemplaza la imagen del proceso actual con una nueva imagen ejecutable, generalmente utilizada después de una llamada a fork() para iniciar un programa en el proceso hijo.

wait() y waitpid(): Esperan a que un proceso hijo termine su ejecución y recuperan su estado de salida. waitpid() permite un mayor control y la espera de un proceso específico.

exit(): Termina un proceso y devuelve un código de salida al sistema operativo que puede ser recogido por el proceso padre a través de wait() o waitpid().

pipe(): Crea una tubería (pipe) que permite la comunicación unidireccional entre procesos. Se utiliza para la transferencia de datos entre procesos relacionados.

dup() y dup2(): Duplican un descriptor de archivo existente, lo que es útil para redirigir la entrada/salida estándar o establecer la entrada/salida de un proceso a través de un descriptor de archivo personalizado.

kill(): Envía una señal a un proceso o grupo de procesos, lo que permite la comunicación y el control entre procesos.*/