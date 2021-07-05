# PHILOSOPHERS (@42)

## DEFINITIONS

- <font size="3"><ins>**Threading :**<font> <br>

	A thread of exection is the smallest sequence of programmed instructions that can be managed *independently* by a *scheduler*.

- <font size="3"><ins>**Scheduling :**<font> <br>

	It is the action of assigning *resources to perform tasks*. The resources may be processors & the tasks may be threads, processes. The scheduling activity is carried out by a process called *scheduler*.

- <font size="3"><ins>**Scheduler :**<font> <br>

	Schedulers are often designed so as to keep all computer resources busy (as in load balancing), allow multiple users to share system resources effectively.
	The concept of scheduling makes it possible to have computer multitasking with a single central processing unit


- <font size="3"><ins>**Mutex :**<font> <br>

	A lock or mutex (mutual exclusion) is a synchronization primitive: a mechanism that enforces *limits on access* to a ressource when they are *many threads* of execution.

## RULES

- [ ] one or more philosophers sitting at a round table, named starting at 1
- [ ] they are seated in order next to each others
- [ ] only three actions = eating, thinking, sleeping & can only do one action at a time
- [ ] large bowl of spaghetti at the center
- [ ] they have one fork to each of their sides
- [ ] a philosopher must use 2 forks to eat
- [ ] they must eat and musn't starve
- [ ] they don't communicate with each others & don't know when someone is about to die
- [ ] in order, they take forks, eat, drop the forks, sleep, then think
- [ ] simulation stops when one dies
- [ ] their status change must be written in full, not untertwined with another
	- timestamp_in_ms X has taken a fork
	- timestamp_in_ms X is eating
	- timestamp_in_ms X is sleeping
	- timestamp_in_ms X is thinking
	- timestamp_in_ms X died
- [ ] a max of 10ms is accepted between the death of a philosopher and his printed status

<br>

- [ ] use a mutex to avoid duplicating forks states
- [ ] each philosopher is a thread
- [ ] if only one philosopher present, he must die

⇨ Perhaps use a third party to communicate with the philosophers.<br>
⇨ Possible use of the forks could be : take 0, 1 or 2 at a time.<br>
⇨ Avoid deadlocks<br>

## SET OF SHARED ATTRIBUTES

Each program / thread should have the same options.

1.	```number_of_philosophers : the number of philosophers and also the number of forks ```
2.	```time_to_die : (in milliseconds). If a philosopher doesn’t start eating ’time_to_die’ milliseconds after starting his last meal or the beginning of the simulation, it dies.```
3.	```time_to_eat : (in milliseconds). The time it takes for a philosopher to eat. During that time he will need to keep the two forks.```
4.	```time_to_sleep : (in milliseconds). The time the philosopher will spend sleeping.```
5.	```number_of_times_each_philosopher_must_eat : (optional). If all philosophers eat at least ’number_of_times_each_philosopher_must_eat’ the simulation will stop.```