# PHILOSOPHERS (@42)

## DEFINITIONS

- <font size="3"><ins>**Threading :**<font> <br>

	A thread of exection is the smallest sequence of programmed instructions that can be managed **independently** by a **scheduler**.

- <font size="3"><ins>**Scheduling :**<font> <br>

	It is the action of assigning **resources to perform tasks**. The resources may be processors & the tasks may be threads, processes. The scheduling activity is carried out by a process called **scheduler**.

- <font size="3"><ins>**Scheduler :**<font> <br>

	Schedulers are often designed so as to keep all computer resources busy (as in load balancing), allow multiple users to share system resources effectively.
	The concept of scheduling makes it possible to have computer multitasking with a single central processing unit


- <font size="3"><ins>**Mutex :**<font> <br>

	A lock or mutex (mutual exclusion) is a synchronization primitive: a mechanism that enforces **limits on access** to a ressource when they are **many threads** of execution.

## RULES

- [x] one or more philosophers sitting at a round table, named starting at 1
- [x] they are seated in order next to each others
- [x] only three actions = eating, thinking, sleeping & can only do one action at a time
- [x] large bowl of spaghetti at the center
- [x] they have one fork to each of their sides
- [x] a philosopher must use 2 forks to eat
- [x] they must eat and musn't starve
- [x] they don't communicate with each others & don't know when someone is about to die
- [x] in order, they take forks, eat, drop the forks, sleep, then think
- [x] simulation stops when one dies
- [x] their status change must be written in full, not untertwined with another
	- timestamp_in_ms X has taken a fork
	- timestamp_in_ms X is eating
	- timestamp_in_ms X is sleeping
	- timestamp_in_ms X is thinking
	- timestamp_in_ms X died
- [x] a max of 10ms is accepted between the death of a philosopher and his printed status

<br>

- [x] use a mutex to avoid duplicating forks states
- [x] each philosopher is a thread
- [x] if only one philosopher present, he must die as he only has 1 fork available

⇨ Perhaps use a **third party** to communicate with the philosophers.<br>
⇨ Possible use of the forks could be : take 0, 1 or 2 at a time.<br>
⇨ Avoid **deadlocks**.<br>
⇨ We don't want a philosopher to pick up a fork that has already been picked up by his neighbor. This is a **race condition**<br>
⇨ Since each philosopher must have access to the two mutex locks that are associated with its left and right forks, the address to the right fork mutex lock is shared.<br>
⇨ Since each philosopher should be run as a thread, we define a **Philosopher structure**.
⇨ A separated thread check each x ms if a philosopher died. A philosopher can die while eating, thinking or sleeping.

## SET OF SHARED ATTRIBUTES

Each program / thread should have the same options.

1.	```number_of_philosophers : the number of philosophers and also the number of forks ```
2.	```time_to_die : (in milliseconds). If a philosopher doesn’t start eating ’time_to_die’ milliseconds after starting his last meal or the beginning of the simulation, it dies.```
3.	```time_to_eat : (in milliseconds). The time it takes for a philosopher to eat. During that time he will need to keep the two forks.```
4.	```time_to_sleep : (in milliseconds). The time the philosopher will spend sleeping.```
5.	```number_of_times_each_philosopher_must_eat : (optional). If all philosophers eat at least ’number_of_times_each_philosopher_must_eat’ the simulation will stop.```

## POSIX THREADS

Thread operations include **thread creation, termination, synchronization (joins,blocking), scheduling, data management and process interaction**.

- POSIX.1 also requires that threads **share a range of other attributes** (i.e., these attributes are process-wide rather than per-thread):

		-  process ID
		-  parent process ID
		-  process group ID and session ID
		-  controlling terminal
		-  user and group IDs
		-  open file descriptors
		-  record locks (see fcntl(2))
		-  signal dispositions
		-  file mode creation mask (umask(2))
		-  current directory (chdir(2)) and root directory (chroot(2))
		-  interval timers (setitimer(2)) and POSIX timers
			(timer_create(2))
		-  nice value (setpriority(2))
		-  resource limits (setrlimit(2))
		-  measurements of the consumption of CPU time (times(2)) and
			resources (getrusage(2))

- As well as the stack, POSIX.1 specifies that various other attributes are distinct for each thread, including:

		-  thread ID (the pthread_t data type)
		-  signal mask (pthread_sigmask(3))
		-  the errno variable
		-  alternate signal stack (sigaltstack(2))
		-  real-time scheduling policy and priority (sched(7))


## STRCUTURES CONSTRUCTION

From the brief, we can already foresee the **philosopher structure**, with **distrinct attributes** in pseudo code :

	typedef struct s_philo
	{
		process_id; (thread id ?)
		philo_id;
		pointer to inputs
		pointer to a set of shared inputs (at least mutext to speak)
		right_fork_id
		left_fork_id
		* to right_fork mutex -> address to left fork of right neighbor
		left_fork mutex
		last time he ate
		number_of_meals_eaten
		dead or alive
	}t_philo;

**innkeeper structure,** where the philosophers are seated in pseudo code :

	typedef struct s_innkeeper
	{
		pointer to inputs
		threads of all the philosophers : t_philo *philosophers
		thread of the death checking clock
		boolean if a death occured and will stop all process
	}t_innkeper;

 **input structure,** from the given argument in pseudo code :

	typedef struct s_inputs
	{
		number_of_philosophers
		time_to_die
		time_to_eat
		time_to_sleep
		number of plates total
		number of plates each philo must eat
	}t_inputs;

**shared input structure** where all main locks will be :

	typedef struct s_inputs
	{
		talk lock
		someone died lock
		plates eaten total lock
	}t_inputs;


## INNKEEPER PSEUDO CODE

- The innkeeper brings *number_of_philosophers* forks to the table, with one fork between each of them.
- She serves *number_of_times_each_philosopher_must_eat* spaghetti plates to the center of the table, or if not specified, she brings a infinite number of spaghetti. They better pay for all that spaghetti !
- She now can spawn *number_of_philosophers* around one table.
- She has to tell them what to start with : taking a fork, sleeping or thinking. Probably based on their id nb.
- She will probably order **each even or odd philosopher to wait** to eat since they need two fork to do that.
- She has to keep a watch on the nb of plates eaten. If none are left, the shuts down the inn.
- She has to make sure which fork is available or not.
- She has to make sure the philosophers don't interrupt each others while speaking.
- If one philosopher dies, she has to shut down the inn. Bad press !

### PHILOSOPHERS PSEUDO CODE

- Philosophers can start to rotate their actions on taking a fork, sleeping or thinking. They refer to the innkeper to know or their id number.
- (They have to inform the innkeeper when they are starting to eat so she can make a priority list.))
- They have to tell her how many times they have eaten.
- They must ask permission to talk.
- They must inform the innkeeper when they die.
- They have to lock the fork they are using in order to prevent the others from taking it.
- They have to make sure a fork is free before taking it.
- Otherwise, they must rotate between their list of actions.

----
	if (id nb is EVEN)
	{
		if (NOT THE LAST philo if tot of philo is ODD)
		{
			THINK
				- Wait for (time to eat * 1)
				- each x time verify i'm not dead otherwise BREAK;
				*(ask permission to speak)*
		}
		if (THE LAST philo if tot of philo is ODD)
			THINK
				- Wait for (time to eat * 2)
				- each x time verify i'm not dead otherwise BREAK;
				*(ask permission to speak)*
	}
---
	if (id nb is ODD)
	{
		if (tot of philo is ODD && i'm the id nb BEFORE the last id)
		{
			THINK
				- Wait for (time to eat * 1)
				- each x time verify i'm not dead otherwise BREAK;
				*(ask permission to speak)*
		}
		otherwise
			EAT
	}
---
EAT
---
	if (time since starting last meal or the beginning of sim >= time_to_die)
	{
		dead = true;
		*(ask permission to speak)*
		BREAK ;
	}
	if (both forks available)
	{
		grab right fork()
			->lock right fork
		grab left fork()
			->lock left fork
			-> *(ask permission to speak)*
	}
	then if (i am still alive)
	{
		- internalize start time of eating
		- eat a plate
		- notify nb of plates total += 1
		- *(ask permission to speak)*
	}
	drop all forks()
	{
		-> unlock left fork
		-> unlock right fork
		-> *(ask permission to speak)*
	}
	go to sleep for sleep_time
		- *(ask permission to speak)*
		- each x time verify i'm not dead otherwise BREAK;
	while (time for others to eat depending if total is odd or even)
			- think
			- *(ask permission to speak)*
			- each x time verify i'm not dead otherwise BREAK;

### HELPFULL COMMANDS

- [x] check leaks : valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --trace-children=yes
- [x] check thread errors = valgrind --tool=drd
- [x] check thread and locking order errors = valgrind --tool=helgrind /!\ Does "possible" locking order error checking without checking if the code avoids locking errors in the first place.

./philo 4 410 200 200
./philo 5 800 200 200
./philo 4 310 200 100 (mort)
./philo 4 1 200 100 (mort)
./philo 5 800 200 200 7
./philo 1 800 200 200

### RECOMMANDATION

I would recommand during dev to have a check on who takes which fork id like so :

// say_status_nb("take left fork", p->p_id, p->l_frk_id, p->in->start_time);
// say_status_nb("take right fork", p->p_id, p->r_frk_id, p->in->start_time);
// say_status_nb("down left fork", p->p_id, p->l_frk_id, p->in->start_time);
// say_status_nb("down right fork", p->p_id, p->r_frk_id, p->in->start_time);
