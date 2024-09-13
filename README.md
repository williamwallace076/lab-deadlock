# -Atividade-Deadlock-

# Discentes : 

William Wallace Da Costa Pereira - 202204940051

Washington Smith Pinho Macambira - 202204940048


Este projeto tem como objetivo implementar e demonstrar diferentes estratégias de prevenção e detecção de deadlock utilizando a linguagem de programação C e a biblioteca pthread para criar processos que manipulam recursos compartilhados. O projeto apresenta três implementações principais:

Deadlock Induzido: Uma implementação proposital de deadlock, onde dois processos tentam adquirir recursos compartilhados em uma ordem invertida, resultando em um impasse.

Detecção de Deadlock: Um exemplo que detecta deadlock ao identificar que os processos estão presos em um ciclo de espera, e então libera os recursos para resolver o impasse.

Prevenção de Deadlock: Uma implementação de prevenção de deadlock, garantindo que os processos adquiram os recursos na mesma ordem, evitando a condição de espera circular, uma das quatro condições necessárias para o deadlock.

# Tecnologias utilizadas 

Linguagem: C

Bibliotecas: pthread.h (para manipulação de threads e mutexes)

Conceitos Utilizados: Threads, Mutex, Deadlock, Prevenção de Deadlock, Detecção de Deadlock
