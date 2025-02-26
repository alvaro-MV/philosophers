## 2. Line too long en philo.h
	-en la funciones run_philo, p_alloc, p_free. Declarar p_free o p_alloc y run_philo como estaticas dentro del archivo main.c y cambiar wait_philo e initialize en otro archivo.

## gen_vars->proc_mutex --> gen_vars->dead_mutex:
	Meter un dead_mutex cuando para evitar que un hilo coma antes de palmarla.

## Cuando hay un solo philo, que no coma, solo la palme.
