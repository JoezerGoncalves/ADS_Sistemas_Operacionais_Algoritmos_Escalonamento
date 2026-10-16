# Simulador de Algoritmos de Escalonamento

Trabalho desenvolvido para a disciplina de **Sistemas Operacionais** do curso de **Tecnologia em Análise e Desenvolvimento de Sistemas (ADS)** do **Instituto Federal do Triângulo Mineiro (IFTM) - Campus Patrocínio**.


Alunos:

GABRYEL EDUARDO SOUZA OLIVEIRA

JOÉZER GONÇALVES PEREIRA

RAFAEL DE ÁVILA CARVALHO



Professor 

GILBERTO VIANA DE OLIVEIRA


# 

## Sobre o Projeto

Este projeto tem como objetivo implementar e simular dois algoritmos clássicos de escalonamento de processos estudados na disciplina de Sistemas Operacionais:

- **SRT (Shortest Remaining Time)**
- **Round-Robin (RR)**

A aplicação foi desenvolvida em **linguagem C** e permite a configuração dos processos antes do início da execução da simulação, possibilitando a visualização passo a passo do comportamento de cada algoritmo.

## Objetivos

- Aplicar os conceitos de escalonamento de processos estudados em sala de aula;
- Implementar algoritmos de escalonamento em linguagem C;
- Simular a execução de processos em um sistema operacional;
- Comparar o comportamento dos algoritmos SRT e Round-Robin;
- Exibir a evolução da execução por meio de uma timeline.

## Algoritmos Implementados

### Shortest Remaining Time (SRT)

Algoritmo de escalonamento preemptivo que seleciona para execução o processo com o menor tempo restante de processamento.

### Round-Robin (RR)

Algoritmo de escalonamento preemptivo baseado em fatias de tempo (quantum), distribuindo a CPU de forma equilibrada entre os processos.

## Entradas da Simulação

O programa permite que o usuário informe:

- Nome do processo;
- Tempo de uso da CPU (Burst Time);
- Tempo de chegada (Arrival Time);
- Parâmetros adicionais necessários para o algoritmo escolhido;
- Quantum (para o algoritmo Round-Robin).

## Saída da Simulação

A cada unidade de tempo, a aplicação apresenta uma timeline contendo:

- Processo em execução na CPU;
- Processos que já chegaram ao sistema e estão no estado **Pronto**;
- Tempo restante de processamento de cada processo;
- Evolução da execução até a finalização de todos os processos.


### Exemplo

```text
Tempo: 0
CPU: P1
Fila de Prontos: -

Tempo: 1
CPU: P2
Fila de Prontos: P1 (7)

Tempo: 2
CPU: P3
Fila de Prontos: P1 (7), P2 (3)
