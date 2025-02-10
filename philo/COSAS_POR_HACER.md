## 1.Inconsistencia de nombres:
	- gen_vars <--> general_vars
	- philo <--> philosophers

## 2. Line too long en philo.h
	-en la funciones run_philo, p_alloc, p_free. Declarar p_free o p_alloc y run_philo como estaticas dentro del archivo main.c y cambiar wait_philo e initialize en otro archivo.

## 4. Cambiar todos los args habidos y por haber a dinner.

## 5. En el caso de que usleep() falle
	Cancelar todos los hilos y liberar toda la memoria. O lo que es lo mismo, pasar un 


## 6. Retocar la función de parseo
	Tiene mas de 25 líneas. Presumiblemente hacer una función para parsear el número de veces
	que se tiene que comer.

## Si falla un hilo en run_philos:
	Hay que dar de baja el resto de hilos.

## gen_vars->proc_mutex --> gen_vars->dead_mutex:
	Meter un dead_mutex cuando para evitar que un hilo coma antes de palmarla.

## Casos de fallo:
	100 :--> 17, 11, 15, 16, 12

	50:--> 8, 11, 7, 8, 9, 10, 6, 8