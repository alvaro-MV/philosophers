## 1.Inconsistencia de nombres:
	- gen_vars <--> general_vars
	- philo <--> philosophers

## 2. Line too long en philo.h
	-en la funciones run_philo, p_alloc, p_free. Declarar p_free o p_alloc y run_philo como estaticas dentro del archivo main.c y cambiar wait_philo e initialize en otro archivo.

## 3. Logs
	- No se a que se refiere con timestamp. Se refiere al tiempo pasado desde un inicio
	  determinado (la primera vez que se come o yo que se) o se refeire al tiempo desde
	  1970. Por ahi

	- En cualquier caso, no tiene sentido comparar desde que empezó a comer, por lo tanto,
	  el cambio sería o para get_actual_time o p.e. sleep_log(gen_vars->init_tmstmp, args);