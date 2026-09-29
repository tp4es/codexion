*Este proyecto ha sido creado como parte del currículo de 42 por tide-oli.*

# Codexion

## Descripción

Codexion simula personas que programan en un hub circular. Cada hilo necesita
los dos dongles vecinos para compilar, y después pasa por las fases de depurar y
refactorizar. La simulación finaliza cuando todas completan el número solicitado
de compilaciones o cuando el monitor detecta agotamiento.

## Instrucciones

```sh
make
./codexion number_of_coders time_to_burnout time_to_compile time_to_debug time_to_refactor number_of_compiles_required dongle_cooldown fifo|edf
```

Por ejemplo: `./codexion 2 800 100 100 100 2 0 fifo`.

## Blocking cases handled

* La adquisición de los dos dongles es atómica bajo un mutex único, por lo que
  nadie conserva un recurso mientras espera otro y se elimina la espera circular.
* Una cola binaria de prioridad arbitra las solicitudes. FIFO conserva su orden
  de llegada y EDF prioriza el deadline de agotamiento más próximo.
* Cada dongle queda indisponible hasta que vence su cooldown.
* Un hilo monitor revisa los deadlines cada 500 microsegundos y detiene a todos
  los hilos tras el primer agotamiento.

## Thread synchronization mechanisms

`pthread_mutex_t lock` protege la cola, los dongles, los deadlines y la parada.
`pthread_cond_t changed` notifica los cambios de recursos y la finalización; las
esperas comprueban periódicamente el cooldown. Un segundo mutex protege `printf`,
por lo que cada cambio de estado se emite como una línea completa, sin mensajes
mezclados.

## Recursos

* `man pthread_create`, `man pthread_mutex_lock`, `man pthread_cond_wait`.
* Enunciado del proyecto Codexion proporcionado en el repositorio.
* Se utilizó IA para revisar la estructura de concurrencia y proponer pruebas;
  la integración, revisión y validación del código se realizaron manualmente.
